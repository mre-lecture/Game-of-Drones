#ifndef __ULTRASONIC__
#define __ULTRASONIC__

#define __US_TMPLT_DCL uint8_t T_PIN_ECHO, uint8_t T_PIN_TRIGGER
#define __US_TMPLT_IML T_PIN_ECHO, T_PIN_TRIGGER

namespace Skymaster {
  template<__US_TMPLT_DCL>
  class UltraSonic {
  public:
    UltraSonic(/*uint8_t p_PinEcho, uint8_t p_PinTrigger*/);
    float GetDistanceCm();
  private:
    /*uint8_t m_PinEcho;
    uint8_t m_PinTrigger;*/
  };


  template<__US_TMPLT_DCL>
  UltraSonic<__US_TMPLT_IML>::UltraSonic(/*uint8_t p_PinEcho, uint8_t p_PinTrigger*/) {
    /*m_PinEcho = p_PinEcho;
    m_PinTrigger = p_PinTrigger*/;
    pinMode(T_PIN_TRIGGER, OUTPUT);
    pinMode(T_PIN_ECHO, INPUT);
  }

  template<__US_TMPLT_DCL>
  float UltraSonic<__US_TMPLT_IML>::GetDistanceCm() {
    digitalWrite(T_PIN_TRIGGER, LOW);
    delayMicroseconds(2);

    digitalWrite(T_PIN_TRIGGER, HIGH);
    delayMicroseconds(10);

    digitalWrite(T_PIN_TRIGGER, LOW);
    long duration = pulseIn(T_PIN_ECHO, HIGH);

    return (float)((double)duration / 58.2);
  }
}

#endif
