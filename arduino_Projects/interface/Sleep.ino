
void sleep()
{
  TimeInt = false;
  ButtonInt = false;
  //detachInterrupt(digitalPinToInterrupt(6));
  TijdNu = rtc.now();
  lastMillis = millis();
  if(active == 1){checkTime();}
  if(RolMoving == true)
  {
#ifdef DEBUGSLEEP
    Serial.println("Mag in nu echt niet slapen?"); 
    Serial.flush();
#endif
    FS = sleeping;
    delay(TimeForRolOpen);
    digitalWrite(RelayOmhoog, LOW);
    digitalWrite(RelayOmlaag, LOW);
    RolMoving = false;
  }
//  attachInterrupt(digitalPinToInterrupt(buttonConfirm), WakeUp, LOW);
  attachInterrupt(1, WakeUp, LOW);
//  attachInterrupt(digitalPinToInterrupt(buttonUp), WakeUp, LOW);
  
  u8g2.setPowerSave(1);
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  
  while (FS == sleeping)
  { 
#ifdef DEBUGSLEEP
    Serial.println("Slaap goed!"); 
    Serial.flush();
#endif
    //in slaapmodus gaan
    sleep_cpu();
#ifdef DEBUGSLEEP
    Serial.println(FS);
    Serial.println("Moet ik echt kijken?"); 
    Serial.flush();
#endif
    TijdNu = rtc.now();
    lastMillis = millis();
    if(active == 1){checkTime();}
    if(RolMoving == true)
    {
#ifdef DEBUGSLEEP
      Serial.println("Mag in nu echt niet slapen?"); 
      Serial.flush();
#endif
      FS = sleeping;
      detachInterrupt(1); 
      delay(TimeForRolOpen);
      digitalWrite(RelayOmhoog, LOW);
      digitalWrite(RelayOmlaag, LOW);
      RolMoving = false;
      attachInterrupt(1, WakeUp, LOW);
    }
    if(TimeInt == true)
    {
      TimeInt = false;
      ButtonInt = false;  
    }
    else if(ButtonInt == true){FS = idle;}
  }
  
  sleep_disable();
  u8g2.setPowerSave(0);
#ifdef DEBUGSLEEP
  Serial.println("Ik ben wakker!!!");
#endif
  delay(100);
  BSConfirm = digitalRead(buttonConfirm);
  lastActive = millis();
}

void WakeUp()
{
  detachInterrupt(1);
  ButtonInt = true;
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
//  RTC.PITCTRLA = 0x71;
  RTC.PITCTRLA = 0x71;
  
  //BOD uitzetten in power down mode 
  return;
}

ISR(RTC_PIT_vect) 
{  
  RTC.PITINTFLAGS = 1; // reset interrupt
  TimeInt = true;
}
