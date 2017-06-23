#ifndef __CONTROLSYSTEM__
#define __CONTROLSYSTEM__

#define __CS_TMPLT_DCL uint16_t T_PULSE_MIN, uint16_t T_PULSE_MAX
#define __CS_TMPLT_IMPL T_PULSE_MIN, T_PULSE_MAX

namespace Skymaster {
  template <__CS_TMPLT_DCL>
  class ControlSystem {
  public:
    ControlSystem(float p_HeightMin, float p_HeightMax)
      : m_HeightMin(p_HeightMin), m_HeightMax(p_HeightMax), m_HeightTarget((p_HeightMax - p_HeightMin) / 2.f), m_HeightCurrent(0.f) { }

    void Update(float p_HeightTarget, float p_HeightCurrent);
    uint16_t GetCurrentValue();
  private:
    uint16_t Calc();

    /* For some reason, float-types can not be used in templates.
     * - Wasting another 8 bytes of member-variables: They could have been compiled right into the code.
     * - Grabbing the value by dereferencing the self-reference and adding an offset just makes the code execute slower.
     * - This probably bothers me too much.
     */
    float m_HeightMin, m_HeightMax;
    float m_HeightTarget, m_HeightCurrent;
    uint16_t m_CalcCurrent, m_CalcLast;
  };

  template<__CS_TMPLT_DCL>
  uint16_t ControlSystem<__CS_TMPLT_IMPL>::GetCurrentValue() {
    return m_CalcCurrent;
  }

  template<__CS_TMPLT_DCL>
  void ControlSystem<__CS_TMPLT_IMPL>::Update(float p_HeightTarget, float p_HeightCurrent) {
      
    p_HeightTarget = max(m_HeightMin, min(m_HeightMax, p_HeightTarget));   

    m_HeightTarget = p_HeightTarget;
    m_HeightCurrent = p_HeightCurrent;

    m_CalcLast = m_CalcCurrent;
    m_CalcCurrent = Calc();
  }

  template<__CS_TMPLT_DCL>
  uint16_t ControlSystem<__CS_TMPLT_IMPL>::Calc() {
    float P = T_PULSE_MAX - T_PULSE_MIN;
    float H = (m_HeightTarget - m_HeightMin) * 2.0f;

    float dh = ((m_HeightCurrent - m_HeightMin) / H) - 0.5f;
    float dp = ((P/2.f) * dh);
    float p = (float)T_PULSE_MIN + ((P/2.f) - dp);

    return min(T_PULSE_MAX, (uint16_t)p);
  }
}

#endif
