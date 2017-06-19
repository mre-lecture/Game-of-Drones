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
    uint8_t &m_Port;
    uint64_t m_Start;
  private:
    static uint8_t FastRead(uint8_t pin, uint8_t port);
    static void FastWrite(uint8_t pin, uint8_t port, uint8_t value);
  };

  PwmBase::PwmBase(uint8_t p_Pin) : m_Pin(p_Pin), m_Value(0), m_Start(0) {
    switch(m_Pin) {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
        m_Port = &PORTD;
      case 8:
      case 9:
      case 10:
      case 11:
      case 12:
      case 13:
        m_Port = &PORTB;
      default:
        m_Port = NULL;
    }
  }

  uint16_t PwmBase::GetValue() {
    return m_Value;
  }

  inline uint8_t PwmBase::FastRead(uint8_t pin, uint8_t port) {
    return (port & (1<<pin)) != 0;
  }

  inline void PwmBase::FastWrite(uint8_t pin, uint8_t &port, uint8_t value) {
    if (value)
      port |= (1 << pin);
    else
      port &= ~(1 << pin);
  }

  uint8_t PwmBase::Read() {
    return m_Port != NULL ? PwmBase::FastRead(m_Pin, m_Port) : 0;
  }

  void PwmBase::Write(uint8_t value) {
    if (m_Port != null)
      PwmBase::FastWrite(m_Pin, m_Port, value);
  }
}

#endif
