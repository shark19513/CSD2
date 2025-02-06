//
// Created by Semuel Leijten on 04/02/2025.
//

#include "CircBuffer.h"


CircBuffer::CircBuffer(unsigned int size, unsigned int numSamplesDelay)
    : m_bufferSize(size), m_readHead(0), m_writeHead(numSamplesDelay) {
    // allocate buffer array to size
    m_buffer = new float[m_bufferSize];
}

CircBuffer::~CircBuffer() {
    delete[] m_buffer;
}

float CircBuffer::read() {
    return m_buffer[m_readHead];
}

void CircBuffer::write(float input) {
    m_buffer[m_writeHead] = input;
}

void CircBuffer::tick() {
    incrementHead(m_readHead);
    incrementHead(m_writeHead);
}

void CircBuffer::incrementHead(unsigned int &head) {
    head++;
    if (head >= m_bufferSize) {
        head -= m_bufferSize;
    }
}
