#ifndef __ULTRASONIC__
#define __ULTRASONIC__

#include "RingBuffer.h"

#define __US_TMPLT_DCL uint8_t T_PIN_ECHO, uint8_t T_PIN_TRIGGER, uint16_t T_DIST_MIN, uint16_t T_DIST_MAX
#define __US_TMPLT_IML T_PIN_ECHO, T_PIN_TRIGGER, T_DIST_MIN, T_DIST_MAX

namespace Skymaster {
  template<__US_TMPLT_DCL>
  class UltraSonic {
  public:
    UltraSonic();
    float GetDistanceCm();
    void StartMeasure();
    void Update();

    RingBuffer<float, 5> m_Median;
  private:
    uint64_t m_Start;
    uint64_t m_Duration;
    float m_Distance;
    bool m_Measuring;
  };


  template<__US_TMPLT_DCL>
  UltraSonic<__US_TMPLT_IML>::UltraSonic() : m_Start(0), m_Duration(0), m_Distance(0.f), m_Measuring(false) {
    pinMode(T_PIN_TRIGGER, OUTPUT);
    pinMode(T_PIN_ECHO, INPUT);
  }
  
  template<__US_TMPLT_DCL>
  void UltraSonic<__US_TMPLT_IML>::StartMeasure() {
    if (!m_Measuring) {
      digitalWrite(T_PIN_TRIGGER, LOW);
      delayMicroseconds(2);
  
      digitalWrite(T_PIN_TRIGGER, HIGH);
      delayMicroseconds(10);
  
      digitalWrite(T_PIN_TRIGGER, LOW);
      m_Measuring = true;
    } else if (micros() - m_Start > 1000 * 500) {
      m_Measuring = false;
    }
  }
  
  template<__US_TMPLT_DCL>
  void UltraSonic<__US_TMPLT_IML>::Update() {
    if (digitalRead(T_PIN_ECHO))
      this->m_Start = micros();
    else {
      this->m_Duration = micros() - m_Start;
      m_Distance = (float)((double)m_Duration / 58.2);
      m_Median.Add(m_Distance);
      m_Measuring = false;
    }
  }

  template<__US_TMPLT_DCL>
  float UltraSonic<__US_TMPLT_IML>::GetDistanceCm() {
    return m_Median.GetMedian();
  }  
}

#endif
