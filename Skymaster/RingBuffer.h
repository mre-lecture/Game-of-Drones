#ifndef __RINGBUFFER__
#define __RINGBUFFER__

#include "Debug.h"
  
#define __RB_TMPLT_DCL typename T, uint16_t T_SIZE
#define __RB_TMPLT_IMPL T, T_SIZE

namespace Skymaster {
  template <__RB_TMPLT_DCL>
  class RingBuffer {
  public:
    RingBuffer() : m_NumUpdates(0), m_Index(0), m_Updated(false), m_Duration(0) { }

    void Add(T p_Value);
    bool IsFilled();
    T GetMedian();

    #ifdef __DEBUG__
    void PrintBuffer();
    #endif
  private:
    T m_Buffer[T_SIZE] = { T() };
    T m_BufferSorted[T_SIZE] = { T() };
    T m_Median = T();
    uint64_t m_NumUpdates;
    uint16_t m_Index;
    bool m_Updated;
    uint64_t m_Duration;
    
    T CalculateMedian();
    static int SortFunc(const void *cmp1, const void *cmp2);
  };  

  #ifdef __DEBUG__
  template<__RB_TMPLT_DCL>
  void RingBuffer<__RB_TMPLT_IMPL>::PrintBuffer() {
    DebugPrint("-> Duration: ");
    DebugPrint((uint32_t)m_Duration);
    DebugPrint("us Data[");
    if (m_NumUpdates >= T_SIZE) {
      for (int i = 0; i < T_SIZE; i++) {
        DebugPrint(" ");
        DebugPrint(m_BufferSorted[i]);
      }
    }
    DebugPrint(" ]");
  }
  #endif

  template<__RB_TMPLT_DCL>
  void RingBuffer<__RB_TMPLT_IMPL>::Add(T p_Value) {
    m_Buffer[m_Index++] = p_Value;
    m_Index %= T_SIZE;
    m_NumUpdates++;
    m_Updated = true;
  }

  template<__RB_TMPLT_DCL>
  bool RingBuffer<__RB_TMPLT_IMPL>::IsFilled() {
    return m_NumUpdates >= T_SIZE;
  }

  template<__RB_TMPLT_DCL>
  T RingBuffer<__RB_TMPLT_IMPL>::GetMedian() {
    if (m_Updated)
      return m_Median = CalculateMedian();
    
    if (!IsFilled())
      return T();
      
    return m_Median;
  }

  template<__RB_TMPLT_DCL>
  T RingBuffer<__RB_TMPLT_IMPL>::CalculateMedian() {
    if (!IsFilled())
      return T();

    uint64_t m = micros();
    memcpy(m_BufferSorted, m_Buffer, sizeof(T) * T_SIZE);
    qsort(m_BufferSorted, T_SIZE, sizeof(T), RingBuffer<T, T_SIZE>::SortFunc);
    m_Duration = micros() - m;

    m_Updated = false;
    return m_BufferSorted[T_SIZE / 2];
  }

  template<__RB_TMPLT_DCL>
  int RingBuffer<__RB_TMPLT_IMPL>::SortFunc(const void *cmp1, const void *cmp2)
  {
    T a = *(const T*) cmp1;
    T b = *(const T*) cmp2;
    return (a > b) - (a < b);
  }
}

#endif 
