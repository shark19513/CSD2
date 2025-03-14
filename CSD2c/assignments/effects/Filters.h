//
// Created by Dean on 27/02/2024.
//
#pragma once

class Filter {
public:
    virtual void processFrame(const float& input, float& output) = 0;
};


//                   IIRFilter
//   X[n] ---->(+)--->[ 1 sample ] ---> Y[n]
//              |                   |
//             (a)<-----------------
//
class IIRFilter : public Filter {
    public:
    void processFrame(const float& input, float& output) override {
        // Y[n] = X[n] + aY[n-1]
        feedback = input + (a * feedback);
        output = feedback;
    }

    void setCoefficient(float coefficient) {
        // Do not exceed 1, for the safety of all our ears
        a = coefficient;
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
    void processFrame(const float& input, float& output) override {
        // Y[n] = X[n] - bX[n-1]
        output = input - (b * x1);
        x1 = input; // Recaching Delay
    }

    void setCoefficient(float coefficient) {
        b = coefficient;
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
    void processFrame(const float& input, float& output) override {
        // Y[n] = bX[n] + aY[n-1]
        feedback = b * input + a * feedback;
        output = feedback;
    }

    void setCoefficient(float coefficient) {
        a = coefficient;
        b = 1.0f - a;
    }

private:
    float feedback { 0.0 };
    float a { 0.0 };
    float b { 0.0 };
};


//                   4_Pole / Simple Cascade
//   X[n]--->[OnePole][OnePole][OnePole][OnePole]--->Y[n]
//
class SimpleLadder :  public Filter {
    public:
    void processFrame(const float& input, float& output) override {
        float sample1, sample2;

        onePole_A.processFrame(input, sample1);
        onePole_B.processFrame(sample1, sample2);
        onePole_C.processFrame(sample2, sample1);
        onePole_D.processFrame(sample2, output);
    }

    void setCoefficient(float coefficient) {
        onePole_A.setCoefficient(coefficient);
        onePole_B.setCoefficient(coefficient);
        onePole_C.setCoefficient(coefficient);
        onePole_D.setCoefficient(coefficient);
    }

private:
    OnePole onePole_A;
    OnePole onePole_B;
    OnePole onePole_C;
    OnePole onePole_D;
};


//                   4 Sample
//   X[n] --(b)->(+)--->[ 4 sample ] ---> Y[n]
//              |                   |
//             (a)<-----------------
//
class FourSample :  public Filter {
    public:
    void processFrame(const float& input, float& output) override {
        // Y[n] = X[n] + aY[n-4]

    }

    void setCoefficient(float coefficient) {
        a = coefficient;
        b = 1.0f - a;
    }


private:
    float feedback { 0.0 };
    float b { 0.0 };
    float a { 0.0 };
};


//                   Halve Biquad
//   X[n] --(b)->(+)--------------------> Y[n]
//                |                  |
//               (a1)<----------[ 1 sample ]
//                |                  |
//               (a2)<----------[ 1 sample ]
//
//
class HalfBiquad :  public Filter {
    public:
    void processFrame(const float& input, float& output) override {
      // y[n] = bX[n] - a1Y[n-1] - a2Y[n-2]

    }

    void setBCoefficient(float coefficient){
        b = coefficient;
    }

    void setA1Coefficient(float coefficient) {
        a1 = coefficient;
    }

    void setA2Coefficient(float coefficient) {
        a2 = coefficient;
    }


private:
    float b;
    float a1;
    float a2;
};


class Biquad :  public Filter {
public:
    // Zoek een Biquad, en maak  'm :- )
    // Probeer het internet, of Will Pirkle, zijn verschillende benaderingen
    // Succes.

};
