//TODO: Moving Median für Inputs!

#define __DEBUG__

#include "Debug.h"
#include "PwmIn.h"
#include "PwmOut.h"
#include "UltraSonic.h"
#include "ControlSystem.h"
#include "SerialCommunication.h"
#include "RingBuffer.h"

#define PIN_THROTTLE_IN 2
#define PIN_THROTTLE_OUT PWM_CH7
#define PIN_AUX_IN 3
#define PIN_ULTRASONIC_A_TRIGGER 52 //TODO: Specify pins
#define PIN_ULTRASONIC_A_ECHO 53
#define PIN_ULTRASONIC_B_TRIGGER 50
#define PIN_ULTRASONIC_B_ECHO 51

#define VAL_ULTRASONIC_DIST_MIN 0
#define VAL_ULTRASONIC_DIST_MAX 200
#define VAL_AUX_AUTOMATIC_MODE 1500 
#define VAL_CONTROL_SYSTEM_HEIGHT_MAX 150.0f
#define VAL_CONTROL_SYSTEM_HEIGHT_MIN 50.0f
#define VAL_CONTROL_SYSTEM_BAUD_RATE 115200
#define VAL_PWM_PERIOD 2000
#define VAL_PWM_MIN 1000

#define CC3D_TO_ARDUINO_PWM(val) (uint8_t)((val / (float)VAL_PWM_PERIOD) * 255.f)

Skymaster::PwmIn g_ThrottleIn(PIN_THROTTLE_IN);
Skymaster::PwmIn g_AuxIn(PIN_AUX_IN);
Skymaster::PwmOut g_ThrottleOut(PIN_THROTTLE_OUT, VAL_PWM_PERIOD);
Skymaster::UltraSonic<PIN_ULTRASONIC_A_ECHO, PIN_ULTRASONIC_A_TRIGGER, VAL_ULTRASONIC_DIST_MIN, VAL_ULTRASONIC_DIST_MAX> g_UltraSonicA;
Skymaster::UltraSonic<PIN_ULTRASONIC_B_ECHO, PIN_ULTRASONIC_B_TRIGGER, VAL_ULTRASONIC_DIST_MIN, VAL_ULTRASONIC_DIST_MAX> g_UltraSonicB;
Skymaster::ControlSystem<VAL_PWM_MIN, VAL_PWM_PERIOD> g_ControlSystem(VAL_CONTROL_SYSTEM_HEIGHT_MIN, VAL_CONTROL_SYSTEM_HEIGHT_MAX);
Skymaster::SerialCommunication g_SerialCommunication(VAL_CONTROL_SYSTEM_BAUD_RATE);


void setup() {
  Serial.begin(115200);
  Serial.println("Still alive.");
  
  //Install interrupts
  //attachInterrupt(digitalPinToInterrupt(PIN_THROTTLE_IN), isrThrottle, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(PIN_AUX_IN), isrAux, CHANGE);
  attachInterrupt(PIN_ULTRASONIC_A_ECHO, isrUltraSonicA, CHANGE);
  attachInterrupt(PIN_ULTRASONIC_B_ECHO, isrUltraSonicB, CHANGE);

  g_UltraSonicA.StartMeasure();
  delay(500);
  g_UltraSonicB.StartMeasure();
  
}

volatile uint64_t _micros = 0;
volatile uint16_t g_Throttle = 0;

void loop() {
  /*DebugPrint("i(T): ");
  DebugPrint(g_ThrottleIn.GetValue());
  DebugPrint("\ti(A): ");
  DebugPrint(g_AuxIn.GetValue());
  
  if (g_AuxIn.GetValue() >= VAL_AUX_AUTOMATIC_MODE) {
    //Get current ultrasonic-readings
    float h1 = g_UltraSonicA.GetDistanceCm();
    float h2 = g_UltraSonicB.GetDistanceCm();
    //Use higher reading to compensate for occluded sensors
    float heightCurrent = max(h1, h2);
    
    DebugPrint("\ti(H): ");
    DebugPrint(heightCurrent);
    
    //Update control-system, feed calculated throttle-level to throttle-output
    g_ControlSystem.Update(g_SerialCommunication.GetLatestHeightValue(), heightCurrent);
    g_ThrottleOut.SetDuty(CC3D_TO_ARDUINO_PWM(g_ControlSystem.GetCurrentValue()));

    DebugPrint("\ti(S): ");
    DebugPrint(g_SerialCommunication.GetLatestHeightValue());
  } else {
    //Send throttle-input to throttle-output; do not use control-system
    g_ThrottleOut.SetDuty(CC3D_TO_ARDUINO_PWM(g_ThrottleIn.GetValue()));
  }
  
  DebugPrint("\to(T):");
  DebugPrint(g_ThrottleOut.GetValue());
  
  DebugPrintLn("");*/
  DebugPrint("i(US_A): ");
  DebugPrint(g_UltraSonicA.GetDistanceCm());
  g_UltraSonicA.m_Median.PrintBuffer();
  DebugPrintLn("");
  
  DebugPrint("i(US_B): ");
  DebugPrint(g_UltraSonicB.GetDistanceCm());
  g_UltraSonicB.m_Median.PrintBuffer();
  DebugPrintLn("");

  g_UltraSonicA.StartMeasure();
  g_UltraSonicB.StartMeasure();
  delay(100);
}

//Async: Serial data available
void serialEvent() {
  g_SerialCommunication.Update();
}

//Async: External interrupt at PIN_AUX_IN changed
void isrAux() {
  g_AuxIn.Update();
}

//Async: External interrupt at PIN_THROTTLE_IN changed
void isrThrottle() {
  g_ThrottleIn.Update();
}

//Async: External interrupt at PIN_ULTRASONIC_A_ECHO
void isrUltraSonicA() {
  g_UltraSonicA.Update();
}

//Async: External interrupt at PIN_ULTRASONIC_B_ECHO
void isrUltraSonicB() {
  g_UltraSonicB.Update();
}
