#include "Delay.h"

#define MAX_STEP_SIZE 3 // maximum step size
#define NUM_SMOOTHING_STEPS 11025 // delta gets divided by this number inside setDelayTimeSamples

Delay::Delay(float delayTimeMillis, float maxDelayTimeMillis) :
    m_sampleRate(0), m_delayTimeMillis(delayTimeMillis),
    m_maxDelayTimeMillis(maxDelayTimeMillis),
    m_delayTimeSamples(0), m_feedback(0),
    m_buffer(nullptr), m_bufferSize(0),
    m_writeH(0), m_targetDelayTimeSamples(0),
    m_theTimesTheyAreAChanging(false), m_smoothingStepSize(0)
{
    // prepare() should always be called before use
}

Delay::~Delay() {
    releaseBuffer();
}

void Delay::prepare(float sampleRate) {
    this->m_sampleRate = sampleRate;
    // init the buffer size to the max delay time and init the delay time
    m_bufferSize = static_cast<unsigned int>(millisecondsToSamples(m_maxDelayTimeMillis));
    allocateBuffer();
    setDelayTime(m_delayTimeMillis);
}

void Delay::applyEffect(const float& input, float& output)
{
    /* i thought the code below made sense but it just fucks everything up */
    // if(m_theTimesTheyAreAChanging) {
    //     // calculate the current difference
    //     float delta = m_targetDelayTimeSamples - m_delayTimeSamples;
    //     // check if we reached the target
    //     // or are close enough to make the jump straight away
    //     /* NOTE: i think this avoids overshooting but not sure if necessary
    //         also realistically delta will prob never be 0 but i guess it's possible? */
    //     if (delta >= MAX_STEP_SIZE && delta <= -MAX_STEP_SIZE || delta == 0) {
    //         m_delayTimeSamples = m_targetDelayTimeSamples;
    //         m_theTimesTheyAreAChanging = false;
    //     } else {
    //     // else add the step size
    //         m_delayTimeSamples += m_smoothingStepSize;
    //     }
    // }

    if (m_theTimesTheyAreAChanging) {
        m_delayTimeSamples += m_smoothingStepSize;
        // calculate current difference
        float delta = m_targetDelayTimeSamples - m_delayTimeSamples;
        // check if we reached the target or are close enough to make a jump to it
        /* NOTE: Ciska Said: "to ensure proper handling of m_smoothDeltaSamples below 1,
                              we need to make this check a bit more neatly, by considering the
                              m_smoothDeltaSamples value instead of 1.0f"
         *  m_smoothDeltaSamples is called m_smoothingStepSize in my code
         *  i am not sure what that means though */
        if (delta > -1.0f && delta < 1.0f) {
            m_delayTimeSamples = m_targetDelayTimeSamples;
            m_theTimesTheyAreAChanging = false;
        }
    }

    // calculate read head based on position of write head
    float readPos = m_writeH - m_delayTimeSamples + m_bufferSize;
    unsigned int readH = static_cast<int>(readPos); //get rid of fractional part for read head
    unsigned int nextReadHPos = readH + 1; // indicates next element in buffer
    float readHFraction = readPos - readH; // store fractional part separately
    wrapH(readH);
    wrapH(nextReadHPos);

    /* interpolate between the current buffer element and the next one with readHFraction as value */
    output = Interpolation::linMap(readHFraction, m_buffer[readH], m_buffer[nextReadHPos]);

    // write input to write head position together with the feedback from the output
    m_buffer[m_writeH] = input + output * m_feedback;
    incrWriteH(); // tick write head
}

void Delay::setFeedback(float feedback) {
    if (feedback >= 0.0f && feedback <= 1.0f) {
        this->m_feedback = feedback;
    } else {
        std::cout << "-- Delay::setFeedback --\n"
                  << "! invalid input !\n"
                  << "- please enter a value between 0.0 and 1.0 -\n";
    }
}

void Delay::setDelayTime(float delayTimeMillis) {
    /* delay time must be 0.1ms minimum to prevent interpolation from 0 to 0 */
    if (delayTimeMillis > 0.1f && delayTimeMillis < m_maxDelayTimeMillis ) {
        m_delayTimeMillis = delayTimeMillis;
        setDelayTimeSamples(millisecondsToSamples(m_delayTimeMillis));
    } else {
        std::cout << "-- Delay::setDelayTime -- \n"
                  << "! invalid input !\n"
                  << "- please enter a value between " << "0.1"
                  << " and " << m_maxDelayTimeMillis-1 << " -\n";
    }
}

float Delay::getFeedback() {
    return m_feedback;
}

float Delay::getDelayTime() {
    return m_delayTimeMillis;
}

float Delay::millisecondsToSamples(float millis) {
    float delayTimeSamples = millis / 1000.0f * m_sampleRate;
    return delayTimeSamples;
}

float Delay::samplesToMilliseconds(unsigned int samples) {
    return static_cast<float>(samples) / m_sampleRate * 1000.0f;
}

void Delay::allocateBuffer() {
    // allocate buffer and set all samples to 0
    m_buffer = new float[m_bufferSize];
    for (unsigned int i = 0; i < m_bufferSize; i++) {
        m_buffer[i] = 0;
    }
}

void Delay::releaseBuffer() {
    delete[] m_buffer;
    m_buffer = nullptr;
}

// set the number of samples to delay with interpolation smoothing
void Delay::setDelayTimeSamples(unsigned int delayTimeSamples) {
    //TODO: comparing floats is unsafe. what do?
    if (delayTimeSamples != m_delayTimeSamples) {
        // calculate smooth interpolation
        m_theTimesTheyAreAChanging = true; // gets set to false in applyEffect
        m_targetDelayTimeSamples = delayTimeSamples; // set target
        // calculate delta and divide by a number of steps
        m_smoothingStepSize = (m_targetDelayTimeSamples - m_delayTimeSamples)
                                    / NUM_SMOOTHING_STEPS;
        std::cout << "______________________________" << std::endl;
        std::cout << "new delay time samples: " << delayTimeSamples << std::endl;
        std::cout << "current m_delayTimeSamples: " << m_delayTimeSamples << std::endl;
        std::cout << "m_smoothingStepSize: " << m_smoothingStepSize << std::endl;

        // check if step size exceeds MAX_STEP_SIZE
        if (m_smoothingStepSize > 0 && m_smoothingStepSize > MAX_STEP_SIZE) {
        // if the new time is greater than it was before and exceeds the max step size
            m_smoothingStepSize = MAX_STEP_SIZE;
        } else if (m_smoothingStepSize < 0 && m_smoothingStepSize < -MAX_STEP_SIZE) {
        // if the new time is smaller than it was before and exceeds the negative max step size
            m_smoothingStepSize = -MAX_STEP_SIZE;
        }
    }
}