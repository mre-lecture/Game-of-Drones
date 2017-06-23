#ifndef __DEBUG_UTILS__
#define __DEBUG_UTILS__

#ifdef __DEBUG__
  #define DebugPrintLn(x) Serial.println(x)
  #define DebugPrint(x) Serial.print(x)
#else
  #define DebugPrintLn(x)
  #define DebugPrint(x)
#endif 

#endif
