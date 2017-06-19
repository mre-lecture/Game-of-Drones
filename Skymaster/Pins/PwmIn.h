#ifndef __PwmIn__
#define __PwmIn__

#include "./PwmBase.h"

namespace Skymaster {
  class PwmIn : public PwmBase {
  public:
    PwmIn(uint8_t p_Pin) : PwmBase(p_Pin) { }

    void Update();
  private:
  };

  void PwmIn::Update() {
    if (this->Read())
      this->m_Start = micros();
    else
      this->m_Value = (uint16_t)(micros() - m_Start);
  }
}

#endif
