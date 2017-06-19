#ifndef __CONTROLSYSTEM__
#define __CONTROLSYSTEM__

#define __CS_TMPLT_DCL uint16_t T_PULSE_MIN, uint16_t T_PULSE_MAX, float T_HEIGHT_MIN, float T_HEIGHT_MAX
#define __CS_TMPLT_IML T_PULSE_MIN, T_PULSE_MAX, T_HEIGHT_MIN, T_HEIGHT_MAX

namespace Skymaster {
  template <__CS_TMPLT_DCL>
  class ControlSystem {
  public:
    ControlSystem()
      : m_HeightTarget((T_HEIGHT_MAX - T_HEIGHT_MIN) / 2.f), m_HeightCurrent(0.f) { }

    void Update(float p_HeightTarget, float p_HeightCurrent);
    uint16_t GetCurrentValue();
  private:
    uint16_t Calc();

    float m_HeightTarget, m_HeightCurrent;
    uint16_t m_CalcCurrent, m_CalcLast;
  };

  template<__CS_TMPLT_DCL>
  uint16_t ControlSystem<__CS_TMPLT_IML>::GetCurrentValue() {
    return m_CalcCurrent;
  }

  template<__CS_TMPLT_DCL>
  void ControlSystem<__CS_TMPLT_IML>::Update(float p_HeightTarget, float p_HeightCurrent) {
    if (p_HeightTarget > T_HEIGHT_MAX)
      p_HeightTarget = T_HEIGHT_MAX;
    if (p_HeightTarget < T_HEIGHT_MIN)
      p_HeightTarget = T_HEIGHT_MIN;

    m_HeightTarget = p_HeightTarget;
    m_HeightCurrent = p_HeightCurrent;

    m_CalcLast = m_CalcCurrent;
    m_CalcCurrent = Calc();
  }

  template<__CS_TMPLT_DCL>
  uint16_t ControlSystem<__CS_TMPLT_IML>::Calc() {
    float P = T_PULSE_MAX - T_PULSE_MIN;
    float H = (m_HeightTarget - T_HEIGHT_MIN) * 2.0f;

    float dh = ((m_HeightCurrent - T_HEIGHT_MIN) / H) - 0.5f;
    float dp = ((P/2.f) * dh);
    float p = (float)T_PULSE_MIN + ((P/2.f) - dp);

    return min(T_PULSE_MAX, (uint16_t)p);
  }
}

#endif __CONTROLSYSTEM__
