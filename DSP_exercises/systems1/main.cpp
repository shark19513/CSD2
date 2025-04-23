#include <iostream>
#include <audiocomponent.h>
#include <sine.h>
#include <audioToFile.h>


#define SAMPLE_RATE 44100
#define WRITE_TO_FILE 1

struct CustomCallback : AudioCallback {
    explicit CustomCallback(double Fs) : AudioCallback(Fs), sine(0) {
    }

    ~CustomCallback() override {
    }

    void prepare(int sampleRate = SAMPLE_RATE) override {
        sine.prepare(static_cast<float>(sampleRate));
    }

    void process(AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;
        float frequency = 0;

        for (auto sample = 0u; sample < numFrames; ++sample) {
            float oscSample = sine.genNextSample();
            float processedOutput = system6(oscSample);
            for(auto channel = 0u; channel < numOutputChannels; ++channel) {
                outputChannels[channel][sample] = processedOutput;
                frequency ++;
                sine.setFrequency(frequency);
            }
        }
    }
private:
    Sine sine;

    float system1(float inputSample) {
        static float prevSample = 0.0f;
        static float prevprevSample = 0.0f;
        float outputSample = 0.25f * prevSample + 0.25f * prevprevSample;
        prevprevSample = prevSample;
        prevSample = inputSample;
        return outputSample;
    }

    float system2(float inputSample) {
        static float prevSample = 0.0f;
        static float prevprevSample = 0.0f;
        float outputSample = 0.5f * inputSample + 0.5f * prevprevSample;
        prevprevSample = prevSample;
        prevSample = inputSample;
        return outputSample;
    }

    float system3(float inputSample) {
        static float feedback = 0.0f;
        feedback = 0.5f * feedback + 0.5f * inputSample;
        return feedback;
    }

    float system4(float inputSample) {
        static float prevSample = 0.0f;
        static float prevprevSample = 0.0f;
        static float prevprevprevSample = 0.0f;
        float outputSample = 0.25f * inputSample - 0.25f * prevprevprevSample;
        prevprevprevSample = prevprevSample;
        prevprevSample = prevSample;
        prevSample = inputSample;
        return outputSample;
    }

    float system5(float inputSample) {
        static float prevSample = 0.0f;
        static float prevprevSample = 0.0f;
        static float prevprevprevSample = 0.0f;
        float outputSample = 0.75f * inputSample + 0.25f * prevprevprevSample;
        prevprevprevSample = prevprevSample;
        prevprevSample = prevSample;
        prevSample = inputSample;
        return outputSample;
    }

    float system6(float inputSample) {
        static float prevSample = 0.0f;
        static float feedback = 0.0f;
        feedback = 0.5f * prevSample - 0.5f * feedback;
        prevSample = inputSample;
        return feedback;
    }

    float system7(float inputSample) {
        static float prevSample = 0.0f;
        static float prevprevSample = 0.0f;
        float outputSample = 0.5 * inputSample - 0.5 * prevprevSample;
        prevprevSample = prevSample;
        prevSample = inputSample;
        return outputSample;
    }

    float system10(float inputSample) {
        static float prevSample = 0.0f;
        static float prevprevSample = 0.0f;
        static float prevprevprevSample = 0.0f;
        float outputSample = 0.25 * inputSample - 0.5 * prevSample + 0.25 * prevprevSample;
        prevprevprevSample = prevprevSample;
        prevprevSample = prevSample;
        prevSample = inputSample;
        return outputSample;
    }
};


int main() {
    ScopedMessageThreadEnabler scopedMessageThreadEnabler;
    CustomCallback audioSource{44100};

    JUCEModule juceModule(audioSource);
    juceModule.init(1,1);

    #if WRITE_TO_FILE
        const std::string sourcePath = SOURCE_DIR;
        AudioToFile audioToFile(sourcePath + "/output.csv");
        audioToFile.write(audioSource);

    #else
        bool running = true;
        while (running) {
            switch (std::cin.get()) {
                case 'q':
                    running = false;
            }
        }
    #endif

    return 0;
}