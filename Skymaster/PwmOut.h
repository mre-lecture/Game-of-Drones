#ifndef __PwmOut__
#define __PwmOut__

#include "./PwmBase.h"

namespace Skymaster {
  class PwmOut : public PwmBase {
  public:
    PwmOut(uint8_t p_Pin, uint16_t p_Frequency);

    void SetDuty(uint16_t p_Duty);
  private:
    uint16_t m_Duty;
  };

  PwmOut::PwmOut(uint8_t p_Pin, uint16_t p_Frequency) : PwmBase(p_Pin) {
    pinMode(p_Pin, OUTPUT);
    PWMC_ConfigureClocks(p_Frequency * PWM_MAX_DUTY_CYCLE , 0, VARIANT_MCK);
  }

  void PwmOut::SetDuty(uint16_t p_Duty) {
    if (p_Duty != m_Value) {
      m_Value = p_Duty;
      PWMC_SetDutyCycle(PWM_INTERFACE, this->m_Pin, m_Value);
    }
  }
}

#endif 
