#ifndef __PwmIn__
#define __PwmIn__

#include "./PwmBase.h"

namespace Skymaster {
  class PwmIn : public PwmBase {
  public:
    PwmIn(uint8_t p_Pin) : PwmBase(p_Pin) { }

    void Update();
    bool HasChanged() {
      return m_Value != m_LastValue;
    }
  private:
    uint16_t m_LastValue;
  };

  void PwmIn::Update() {
    m_LastValue = m_Value;
    if (digitalRead(this->m_Pin)) //this->Read())
      this->m_Start = micros();
    else
      this->m_Value = (uint16_t)(micros() - m_Start);
  }
}

#endif
