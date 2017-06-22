#ifndef __SERIALCOMMUNICATION__
#define __SERIALCOMMUNICATION__

//#include <string.h>
//#include <cstdlib>

namespace Skymaster {
  /*
  SerialCommunication
  The idea is to implement a simple text-based protocol to avoid any conversion problems:
  <command>'='<value>'\n'
  e.g. "H=100\n", "Y=-10\n"
  Valid values for <command>: H (height), Y (yaw)
  Valid values for <value>: Any floating-point number (max 6 digits of precision)
  Messages may not exceed 32 bytes of data.
  */

  enum class ProtocolResult : uint8_t {
    SUCCESS = 0,
    NO_EQUALS,
    EMPTY_VALUE,
    ZERO_VALUE,
    INVALID_TYPE,
    STRING_TOO_SHORT
  };

  class SerialCommunication {
  public:
    SerialCommunication(uint32_t p_BaudRate);

    void Update();
    float GetLatestHeightValue();
    float GetLatestYawValue();
    void ClearHeightValue();
    void ClearYawValue();
  private:
    ProtocolResult ProcessBuffer();
    
    float m_HeightValue;
    float m_YawValue;
    char m_Buffer[32] = { 0 };
    uint8_t m_BufferIndex;
  };

  SerialCommunication::SerialCommunication(uint32_t p_BaudRate)
    : m_HeightValue(100), m_YawValue(0), m_BufferIndex(0) {
    Serial.begin(p_BaudRate);
  }

  float SerialCommunication::GetLatestHeightValue() {
    return this->m_HeightValue;
  }

  float SerialCommunication::GetLatestYawValue() {
    return this->m_YawValue;
  }

  void SerialCommunication::ClearHeightValue() {
    this->m_HeightValue = 0.f;
  }

  void SerialCommunication::ClearYawValue() {
    this->m_YawValue = 0.f;
  }

  ProtocolResult SerialCommunication::ProcessBuffer() {
    float* dst = NULL;

    switch(m_Buffer[0]) {
      case 'H':
        dst = &this->m_HeightValue;
        break;
      case 'Y':
        dst = &this->m_YawValue;
        break;
      default:
        return ProtocolResult::INVALID_TYPE;
    }

    if (m_Buffer[0] == '\0')
      return ProtocolResult::SUCCESS;

    if(m_BufferIndex <= 3)
      return ProtocolResult::STRING_TOO_SHORT;

    //Find char '='
    char* eq = strchr(m_Buffer, '=');
    if (eq == NULL)
      return ProtocolResult::NO_EQUALS; //Didn't find '='

    //Split char
    *eq = '\0';

    if (strlen(eq + 1) <= 0)
      return ProtocolResult::EMPTY_VALUE; //"Value" empty

    float val = (float)atof(eq + 1);
    if (val == 0.f)
      return ProtocolResult::ZERO_VALUE;

    *dst = val;

    return ProtocolResult::SUCCESS;
  }

  void SerialCommunication::Update() {
    while (Serial.available()) {
      //Jump to the buffer's beginning in case of potential overflow
      if (m_BufferIndex >= sizeof(m_Buffer) * sizeof(char))
        m_BufferIndex = 0;

      char c = (char)Serial.read();
      if (c == '.') {
        //Terminator: Process buffer
        m_Buffer[m_BufferIndex++] = '\0';

        Serial.print("SerialInput: \"");
        Serial.print(m_Buffer);
        Serial.print("\"");

        ProtocolResult res = this->ProcessBuffer();

        m_BufferIndex = 0;

        Serial.print("Serial: ");
        Serial.println((int)res);
      } else {
        m_Buffer[m_BufferIndex++] = c;
      }
    }
    Serial.println(m_Buffer);
  }
}

#endif
