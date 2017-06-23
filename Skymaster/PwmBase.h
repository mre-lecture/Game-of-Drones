#ifndef __PWMBASE__
#define __PWMBASE__

namespace Skymaster {
  class PwmBase {
  public:
    PwmBase(uint8_t p_Pin);

    uint16_t GetValue();
  protected:
    uint16_t m_Value;
    uint8_t m_Pin;
    uint64_t m_Start;
  private:
  };

  PwmBase::PwmBase(uint8_t p_Pin) : m_Pin(p_Pin), m_Value(0), m_Start(0) {
    
  }

  uint16_t PwmBase::GetValue() {
    return m_Value;
  }
}

#endif
