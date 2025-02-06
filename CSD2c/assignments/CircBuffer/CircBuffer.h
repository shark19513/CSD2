//
// Created by Semuel Leijten on 04/02/2025.
//

#ifndef CIRCBUFFER_H
#define CIRCBUFFER_H


class CircBuffer {
public:
    CircBuffer(unsigned int size, unsigned int numSamplesDelay);
    ~CircBuffer();

    float read();
    void write(float input);
    // go to next read/write position
    void tick();

private:
    void incrementHead(unsigned int& head);

    float* m_buffer;
    unsigned int m_bufferSize;
    unsigned int m_readHead;
    unsigned int m_writeHead;
};



#endif //CIRCBUFFER_H
