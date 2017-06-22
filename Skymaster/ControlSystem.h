#ifndef __CONTROLSYSTEM__
#define __CONTROLSYSTEM__

namespace Skymaster {
  template <uint16_t T_PULSE_MIN, uint16_t T_PULSE_MAX>
  class ControlSystem {
  public:
    ControlSystem(float p_HeightMin, float p_HeightMax)
      : m_HeightMin(p_HeightMin), m_HeightMax(p_HeightMax), m_HeightTarget((p_HeightMax - p_HeightMin) / 2.f), m_HeightCurrent(0.f) { }

    void Update(float p_HeightTarget, float p_HeightCurrent);
    uint16_t GetCurrentValue();
  private:
    uint16_t Calc();

    float m_HeightMin, m_HeightMax;
    float m_HeightTarget, m_HeightCurrent;
    uint16_t m_CalcCurrent, m_CalcLast;
  };

  template<uint16_t T_PULSE_MIN, uint16_t T_PULSE_MAX>
  uint16_t ControlSystem<T_PULSE_MIN, T_PULSE_MAX>::GetCurrentValue() {
    return m_CalcCurrent;
  }

  template<uint16_t T_PULSE_MIN, uint16_t T_PULSE_MAX>
  void ControlSystem<T_PULSE_MIN, T_PULSE_MAX>::Update(float p_HeightTarget, float p_HeightCurrent) {
    if (p_HeightTarget > m_HeightMax)
      p_HeightTarget = m_HeightMax;
    if (p_HeightTarget < m_HeightMin)
      p_HeightTarget = m_HeightMin;

    m_HeightTarget = p_HeightTarget;
    m_HeightCurrent = p_HeightCurrent;

    m_CalcLast = m_CalcCurrent;
    m_CalcCurrent = Calc();
  }

  template<uint16_t T_PULSE_MIN, uint16_t T_PULSE_MAX>
  uint16_t ControlSystem<T_PULSE_MIN, T_PULSE_MAX>::Calc() {
    float P = T_PULSE_MAX - T_PULSE_MIN;
    float H = (m_HeightTarget - m_HeightMin) * 2.0f;

    float dh = ((m_HeightCurrent - m_HeightMin) / H) - 0.5f;
    float dp = ((P/2.f) * dh);
    float p = (float)T_PULSE_MIN + ((P/2.f) - dp);

    return min(T_PULSE_MAX, (uint16_t)p);
  }
}

#endif
