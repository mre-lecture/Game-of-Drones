#include "Pins/PwmIn.h"
#include "Pins/PwmOut.h"
#include "TimerOne/TimerOne.h"
#include "UltraSonic.h"

#define PIN_THROTTLE_IN 2
#define PIN_THROTTLE_OUT 4
#define PIN_AUX_IN 3
#define PIN_ULTRASONIC_A_TRIGGER 0 //TODO: Specify pins
#define PIN_ULTRASONIC_A_ECHO 0
#define PIN_ULTRASONIC_B_TRIGGER 0
#define PIN_ULTRASONIC_B_ECHO 0
#define VAL_AUX_AUTOMATIC_MODE 0 //TODO: Specify AUX-levels
#define VAL_CONTROL_SYSTEM_PULSE_MAX 2000
#define VAL_CONTROL_SYSTEM_PULSE_MIN 1000
#define VAL_CONTROL_SYSTEM_HEIGHT_MAX 150.0
#define VAL_CONTROL_SYSTEM_HEIGHT_MIN 50.0
#define VAL_CONTROL_SYSTEM_BAUD_RATE 9600
#define VAL_PWM_PERIOD 2000

Skymaster::PwmIn g_ThrottleIn(PIN_THROTTLE_IN);
Skymaster::PwmIn g_AuxIn(PIN_AUX_IN);
Skymaster::UltraSonic<PIN_ULTRASONIC_A_ECHO, PIN_ULTRASONIC_A_TRIGGER> g_UltraSonicA;
Skymaster::UltraSonic<PIN_ULTRASONIC_B_ECHO, PIN_ULTRASONIC_B_TRIGGER> g_UltraSonicB;
Skymaster::ControlSystem<VAL_CONTROL_SYSTEM_PULSE_MIN, VAL_CONTROL_SYSTEM_PULSE_MAX,
                         VAL_CONTROL_SYSTEM_HEIGHT_MIN, VAL_CONTROL_SYSTEM_HEIGHT_MAX>
                          g_ControlSystem;
Skymaster::SerialCommunication g_SerialCommunication(VAL_CONTROL_SYSTEM_BAUD_RATE);

void setup() {
  Timer1.initialize(VAL_PWM_PERIOD);

  //Install interrupts
  attachInterrupt(digitalPinToInterrupt(PIN_THROTTLE_IN), isrThrottle, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_AUX_IN), isrAux, CHANGE);
}

void loop() {
  if (g_AuxIn.GetValue() >= VAL_AUX_AUTOMATIC_MODE) {
    //Get current ultrasonic-readings
    float h1 = g_UltraSonicA.GetDistanceCm();
    float h2 = g_UltraSonicB.GetDistanceCm();
    //Use higher reading to compensate for occluded sensors
    float heightCurrent = max(h1, h2);

    //Update control-system, feed calculated throttle-level to throttle-output
    g_ControlSystem.Update(g_SerialCommunication.GetLatestHeightValue(), heightCurrent);
    Timer1.pwm(PIN_THROTTLE_OUT, g_ControlSystem.GetCurrentValue(), VAL_PWM_PERIOD);
  } else {
    //Send throttle-input to throttle-output; do not use control-system
    Timer1.pwm(PIN_THROTTLE_OUT, g_ThrottleIn.GetValue(), VAL_PWM_PERIOD);
  }
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
  g_ThrottleIn.Udate();
}
