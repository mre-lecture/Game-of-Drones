#ifndef __PWMBASE__
#define __PWMBASE__

namespace Skymaster {
  class PwmBase {
  public:
    PwmBase(uint8_t p_Pin);

    virtual void Update() = 0;
    uint16_t GetValue();

  protected:
    uint8_t Read();
    void Write(uint8_t value);

    uint16_t m_Value;
    uint8_t m_Pin;
    uint64_t m_Start;
  private:
    static uint8_t FastRead(uint8_t pin);
    static void FastWrite(uint8_t pin, uint8_t value);
  };

  PwmBase::PwmBase(uint8_t p_Pin) : m_Pin(p_Pin), m_Value(0), m_Start(0) {
    
  }

  uint16_t PwmBase::GetValue() {
    return m_Value;
  }

  inline uint8_t PwmBase::FastRead(uint8_t pin) {
    return (PORTD & (1<<pin)) != 0;
  }

  inline void PwmBase::FastWrite(uint8_t pin, uint8_t value) {
    if (value)
      PORTD |= (1 << pin);
    else
      PORTD &= ~(1 << pin);
  }

  uint8_t PwmBase::Read() {
    //return m_Port != NULL ? PwmBase::FastRead(m_Pin, PORTD) : 0;
    PwmBase::FastRead(m_Pin);
  }

  void PwmBase::Write(uint8_t value) {
    //if (PORTD != null)
      PwmBase::FastWrite(m_Pin, value);
  }
}

#endif
