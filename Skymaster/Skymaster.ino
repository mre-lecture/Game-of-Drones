//TODO: Moving Median für Inputs!

#include "PwmIn.h"
//#include "Pins/PwmOut.h"
#include <TimerOne.h>
#include "UltraSonic.h"
#include "ControlSystem.h"
#include "SerialCommunication.h"

#define PIN_THROTTLE_IN 2
#define PIN_THROTTLE_OUT 9
#define PIN_AUX_IN 3
#define PIN_ULTRASONIC_A_TRIGGER 8 //TODO: Specify pins
#define PIN_ULTRASONIC_A_ECHO 9
#define PIN_ULTRASONIC_B_TRIGGER 10
#define PIN_ULTRASONIC_B_ECHO 11
#define VAL_AUX_AUTOMATIC_MODE 1500 
#define VAL_CONTROL_SYSTEM_PULSE_MAX 2000
#define VAL_CONTROL_SYSTEM_PULSE_MIN 1000
#define VAL_CONTROL_SYSTEM_HEIGHT_MAX 150.0
#define VAL_CONTROL_SYSTEM_HEIGHT_MIN 50.0
#define VAL_CONTROL_SYSTEM_BAUD_RATE 9600
#define VAL_PWM_PERIOD 2000

Skymaster::PwmIn g_ThrottleIn(PIN_THROTTLE_IN);
Skymaster::PwmIn g_AuxIn(PIN_AUX_IN);
//Skymaster::UltraSonic<PIN_ULTRASONIC_A_ECHO, PIN_ULTRASONIC_A_TRIGGER> g_UltraSonicA;
Skymaster::UltraSonic<PIN_ULTRASONIC_B_ECHO, PIN_ULTRASONIC_B_TRIGGER> g_UltraSonicB;
Skymaster::ControlSystem<VAL_CONTROL_SYSTEM_PULSE_MIN, VAL_CONTROL_SYSTEM_PULSE_MAX> g_ControlSystem(VAL_CONTROL_SYSTEM_HEIGHT_MIN, VAL_CONTROL_SYSTEM_HEIGHT_MAX);
Skymaster::SerialCommunication g_SerialCommunication(VAL_CONTROL_SYSTEM_BAUD_RATE);


void setup() {
  pinMode(PIN_THROTTLE_OUT, OUTPUT);
  Serial.begin(9600);

  //Install interrupts
  attachInterrupt(digitalPinToInterrupt(PIN_THROTTLE_IN), isrThrottle, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_AUX_IN), isrAux, CHANGE);

  Timer1.initialize(2000);
  Timer1.pwm(PIN_THROTTLE_OUT, 755, 2000);
}

volatile uint64_t _micros = 0;
volatile uint16_t g_Throttle = 0;

void loop() {
  Serial.print("G: ");
  Serial.print(g_ThrottleIn.GetValue());
  
  if (g_AuxIn.GetValue() >= VAL_AUX_AUTOMATIC_MODE) {
    //Get current ultrasonic-readings
    //float h1 = g_UltraSonicA.GetDistanceCm();
    float h2 = g_UltraSonicB.GetDistanceCm();
    //Use higher reading to compensate for occluded sensors
    float heightCurrent = h2;//max(h1, h2);
    
    Serial.print("\tH: ");
    Serial.print(heightCurrent);
    
    //Update control-system, feed calculated throttle-level to throttle-output
    g_ControlSystem.Update(g_SerialCommunication.GetLatestHeightValue(), heightCurrent);
    g_Throttle = g_ControlSystem.GetCurrentValue();

    Serial.print("\tS: ");
    Serial.print(g_SerialCommunication.GetLatestHeightValue());
  } else {
    //Send throttle-input to throttle-output; do not use control-system
    g_Throttle = g_ThrottleIn.GetValue();
    //Timer1.pwm(PIN_THROTTLE_OUT, g_ThrottleIn.GetValue(), VAL_PWM_PERIOD);
  }

  //Timer1.pwm(PIN_THROTTLE_OUT, g_ThrottleIn.GetValue(), VAL_PWM_PERIOD);
  uint16_t _val = (int)((g_Throttle / 2000.0f) * 1023.0f);
  Timer1.setPwmDuty(PIN_THROTTLE_OUT, _val);
  Serial.print("\t P:");
  Serial.print(_val);
  
   
  //uint8_t val = (int)(255.0f * (g_Throttle / 2000.0f));
  //analogWrite(PIN_THROTTLE_OUT, val);
  //Serial.print("\t T:");
  //Serial.print(val);
  
  Serial.println();
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
