#include "arduino.h"
#include <avr/sleep.h>
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned long Millis = 0;
char output[20];

volatile unsigned int sleepCnt = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("start");
  for (unsigned char i; i < 22; i++)
  {
    pinMode(i, INPUT_PULLUP);
  }
  //pinMode(7,INPUT_PULLUP);
  //pinMode(6,INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  setupSleep();
  
  //digitalWrite(LED_BUILTIN, LOW);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  doBlink();
  if(Millis + 10000 < millis())
  {
      GoToSleep();
  }
}

void setupSleep() 
{
  //To operate the PIT, follow these steps:
  //1. Configure the RTC clock CLK_RTC as described in   Configure the Clock CLK_RTC.
  /* 0x00 32768Hz clock
   * 0x01 1024Hz clock
   */
  RTC.CLKSEL = 0x01; //Use OSCULP32K oscillator
   
  //2. Enable the interrupt by writing a '1' to the Periodic Interrupt bit (PI) in the PIT Interrupt Control
  //register (RTC.PITINTCTRL).

  while (1 & RTC.PITSTATUS); //check if register isn't busy
 
  RTC.PITINTCTRL = 0x1; //Enable interrupts
 
  //3. Select the period for the interrupt and enable the PIT by writing the desired value to the PERIOD bit
  //field and a '1' to the PIT Enable bit (PITEN) in the PIT Control A register (RTC.PITCTRLA).

  while (1 & RTC.STATUS); //check if register isn't busy
  /* 0x00 off
   * 0x09 4 cycles
   * 0x11 8 cycles
   * 0x19 16 cycles
   * 0x21 32 cycles
   * 0x29 64 cycles
   * 0x31 128 cycles
   * 0x39 256 cycles
   * 0x41 512 cycles
   * 0x49 1024 cycles
   * 0x51 2048 cycles
   * 0x59 4096 cycles
   * 0x61 8192 cycles
   * 0x69 16384 cycles
   * 0x71 32768 cycles
   */
  RTC.PITCTRLA = 0x71;
  
  //BOD uitzetten in power down mode 
  return;
}

ISR(RTC_PIT_vect) 
{  
  sleepCnt ++;
  RTC.PITINTFLAGS = 1; // reset interrupt
}

void GoToSleep()
{
  //detachInterrupt(digitalPinToInterrupt(6));
  //attachInterrupt(digitalPinToInterrupt(7), WakeUp, LOW);
  
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  
  sleepCnt = 0;
  
  while (sleepCnt < 1)
  { 
    sprintf(output,"Slaap goed:%d",sleepCnt);
    Serial.println(output); 
    Serial.flush();
  
    //in slaapmodus gaan
    sleep_cpu();
  }
  //arduino is aan het slapen
  
  Serial.println("Ik ben wakker!!!");
  
  sleepCnt = 0;
  Millis = millis();
  sprintf(output,"%ld",Millis);
  Serial.println(output);
}
    

void WakeUp()
{
  sleep_disable();
  //detachInterrupt(digitalPinToInterrupt(7));
}

void doBlink() 
{
  static unsigned long lastMillis = 0;

  if (millis() > lastMillis + 1000) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    lastMillis = millis();
  }
}
