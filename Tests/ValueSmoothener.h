//
// Created by Semuel Leijten on 18/03/2025.
//

#ifndef VALUESMOOTHENER_H
#define VALUESMOOTHENER_H



class ValueSmoothener {
public:
  ValueSmoothener();
  ~ValueSmoothener();

  void setNewValue(float newValue);
  float genNextValue();

private:
  float m_currentValue;
  float m_delta;
  unsigned int m_timeInSamples;
};



#endif //VALUESMOOTHENER_H
