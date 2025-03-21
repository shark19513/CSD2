//
// Created by Dean on 27/02/2024.
// Editted by Semuel Leijten
//
#pragma once

class Filter {
public:
    Filter() : m_bypassed(false) {}
    virtual ~Filter() {}

    void processFrame(const float& input, float& output) {
        if (m_bypassed) {
            output = input;
        } else {
            applyFilter(input, output);
        }
    }

    virtual void applyFilter(const float& input, float& output) = 0;
    virtual void setCoefficient(float coefficient) = 0;

    void setBypassState(bool bypass) {
        this->m_bypassed = bypass;
    }

    bool getBypassState() {
        return m_bypassed;
    }

private:
    bool m_bypassed;

};
//                   IIRFilter
//   X[n] ---->(+)--->[ 1 sample ] ---> Y[n]
//              |                   |
//             (a)<-----------------
//
class IIRFilter : public Filter {
    public:
    IIRFilter() {}
    ~IIRFilter() override {}
    void applyFilter(const float& input, float& output) override {
        // Y[n] = X[n] + aY[n-1]
        feedback = input + (a * feedback);
        output = feedback;
    }

    void setCoefficient(float coefficient) override {
        if (coefficient >= 0.0f && coefficient <= 1.0f) {
            a = coefficient;
        } else {
            std::cout << "- IIRFilter::setCoefficient -\n"
            << "! invalid input !\n"
            << "- please enter a value between 0.0 and 1.0 -\n";
        }
    }

private:
    float feedback { 0.0 };
    float a { 0.0 }; // Coefficient "a" is mostly used for feedback lines

};


//                    OneZero
//   X[n] ---->(+)--------------------> Y[n]
//              |                  |
//             (b)-->[ 1 sample ]-->
//
class FIRFilter : public Filter {
    public:
    FIRFilter() {}
    ~FIRFilter() override {}

    void applyFilter(const float& input, float& output) override {
        // Y[n] = X[n] - bX[n-1]
        output = input - (b * x1);
        x1 = input; // Recaching Delay
    }

    void setCoefficient(float coefficient) override {
        if (coefficient >= 0.0f && coefficient <= 1.0f) {
            b = coefficient;
        } else {
            std::cout << "- FIRFilter::setCoefficient -\n"
            << "! invalid input !\n"
            << "- please enter a value between 0.0 and 1.0 -\n";
        }
    }

private:
    float x1 {0.0 }; // x1 for a single sample delay
    float b { 0.0 };  // Coefficient "b" is usually used for feed forward lines

};


//                   OnePole
//   X[n] --(b)->(+)--->[ 1 sample ] ---> Y[n]
//              |                   |
//             (a)<-----------------
//
class OnePole : public Filter {
    public:
    OnePole() {}
    ~OnePole() override {}

    void applyFilter(const float& input, float& output) override {
        // Y[n] = bX[n] + aY[n-1]
        feedback = b * input + a * feedback;
        output = feedback;
    }

    void setCoefficient(float coefficient) override {
        if (coefficient >= 0.0f && coefficient <= 1.0f) {
            a = coefficient;
            b = 1.0f - a;
        } else {
            std::cout << "- OnePole::setCoefficient -\n"
            << "! invalid input !\n"
            << "- please enter a value between 0.0 and 1.0 -\n";
        }
    }

private:
    float feedback { 0.0 };
    std::atomic<float> a { 0.0 };
    std::atomic<float> b { 0.0 };
};


//                   4_Pole / Simple Cascade
//   X[n]--->[OnePole][OnePole][OnePole][OnePole]--->Y[n]
//
#define NUM_ONEPOLES 4
class SimpleLadder :  public Filter {
    public:
    SimpleLadder() {}
    ~SimpleLadder() override {}

    void applyFilter(const float& input, float& output) override {
        float sample1, sample2;

        onePoles[0].applyFilter(input, sample1);
        onePoles[1].applyFilter(sample1, sample2);
        onePoles[2].applyFilter(sample2, sample1);
        onePoles[3].applyFilter(sample2, output);
    }

    void setCoefficient(float coefficient) override {
        if (coefficient >= 0.0f && coefficient <= 1.0f) {
            for (unsigned int i = 0; i < NUM_ONEPOLES; i++) {
                onePoles[i].setCoefficient(coefficient);
            }
        } else {
            std::cout << "- SimpleLadder::setCoefficient -\n"
            << "! invalid input !\n"
            << "- please enter a value between 0.0 and 1.0 -\n";
        }
    }

private:
    OnePole onePoles[NUM_ONEPOLES];
};