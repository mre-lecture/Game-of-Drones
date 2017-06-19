#ifndef __PWMOUT__
#define __PWMOUT__
//Unused thanks to TimerOne-lib

/*#include "./PwmBase.h"

namespace Skymaster {
  class PwmOut : public PwmBase {
  public:
    PwmOut(uint8_t p_Pin, uint16_t p_Interval) : PwmBase(p_Pin), m_Interval(p_Interval) { }

    void Update();
    void SetValue(uint16_t p_Value);
  private:
    uint16_t m_Interval;
  };

  PwmOut::PwmOut() {
  }

  void PwmOut::Update() {
    uint64_t currentInterval = (micros() - this->m_Start) % this->m_Interval;

    if (currentInterval < this->m_Value)
      this->Write(1);
    else
      this->Write(0);
  }

  void PwmOut::SetValue(uint16_t p_Value) {
    this->m_Value = p_Value;
    if (this->m_Value > 2000)
      this->m_Value = 1999;
  }
}*/

#endif
