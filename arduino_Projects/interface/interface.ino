#include "config.h" 

void setup(void) {
#ifdef DEBUG || DEBUGTIME || DEBUGSTATE || DEBUGBUTTON || DEBUGSLEEP
  Serial.begin(9600);
  Serial.println("setup Start");
  active = 0; 
  RolOpen = 0;
  Serial.print("active 0, RolOpen 0: ");
  Serial.print((active << 1 | RolOpen));
  active = 0; 
  RolOpen = 1;
  Serial.print("\tactive 0, RolOpen 1: ");
  Serial.print((active << 1 | RolOpen));
  active = 1; 
  RolOpen = 0;
  Serial.print("\tactive 1, RolOpen 0: ");
  Serial.print((active << 1 | RolOpen));
  active = 1; 
  RolOpen = 1;
  Serial.print("\tactive 1, RolOpen 1: ");
  Serial.println((active << 1 | RolOpen));
#endif
  for (unsigned char i; i < 22; i++)
  {
    pinMode(i, INPUT);
  }
  u8g2.begin();
  do 
  {
    u8g2.setFont(u8g2_font_crox3h_tr);
    u8g2.drawStr(0 ,13,"Even Geduld");
    u8g2.drawStr(1 ,38,"ik ben aan ");
    u8g2.drawStr(1 ,63,"het opstarten");
  } while(u8g2.nextPage());
#ifdef DEBUG
  Serial.println("disp started");
#endif
  
  pinMode(buttonConfirm, INPUT_PULLUP);
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonBack, INPUT_PULLUP);
  
  pinMode(RelayOmhoog, OUTPUT);
  digitalWrite(RelayOmhoog, LOW);
  pinMode(RelayOmlaag, OUTPUT);
  digitalWrite(RelayOmhoog, LOW);

  hourUp1 = EEPROM.read(AdressHUp1);
  minuteUp1 = EEPROM.read(AdressMUp1);
  hourDown1 = EEPROM.read(AdressHDown1);
  minuteDown1 = EEPROM.read(AdressMDown1);
  RolOpen = EEPROM.read(AdressRolOpen) & 0b00000001;
  active = EEPROM.read(AdressRolOpen) & 0b00000010;
  manualOverride = EEPROM.read(AdressRolOpen) & 0b00000100;
  if(EEPROM.read(AdressDispSize) == 0){inter = small;}
  else{inter = big;}
  

  if (! rtc.begin()) {
#ifdef DEBUGTIME
    Serial.println("Couldn't find RTC");
    Serial.flush();
#endif
    abort();
  }


  if (! rtc.initialized() || rtc.lostPower()) {
#ifdef DEBUGTIME
    Serial.println("RTC is NOT initialized, let's set the time!");
#endif
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  rtc.start();
  FS = idle;
  setupSleep();
  delay(5000);
#ifdef DEBUG || DEBUGTIME || DEBUGSTATE || DEBUGBUTTON || DEBUGSLEEP
  Serial.println("setup done");
#endif
  TijdNu = rtc.now();
  lastMillis = millis();
  if(active == 1){checkTime();}
  lastActive = millis();
}

void loop(void) {
  if (RolMoving == false)
  {
    buttonCheck();
    if(millis() - lastMillis > TimeBetweenUpdate && FS == idle)
    {
      TijdNu = rtc.now();
      lastMillis = millis();
      if(active == 1){checkTime();}
      lastMillis = millis();
#ifdef DEBUGTIME
      Serial.print(TijdNu.year(), DEC);
      Serial.print('/');
      Serial.print(TijdNu.month(), DEC);
      Serial.print('/');
      Serial.print(TijdNu.day(), DEC);
      Serial.print(" (");
      Serial.print(daysOfTheWeek[TijdNu.dayOfTheWeek()]);
      Serial.print(") ");
      Serial.print(TijdNu.hour(), DEC);
      Serial.print(':');
      Serial.print(TijdNu.minute(), DEC);
      Serial.print(':');
      Serial.print(TijdNu.second(), DEC);
      Serial.println();
#endif
    }
  }
  else if(millis() - RolMovementStart > TimeForRolOpen)
  {
    digitalWrite(RelayOmhoog, LOW);
    digitalWrite(RelayOmlaag, LOW);
    RolMoving = false;
  }
  
#ifdef DEBUGSTATE
  Serial.println(FS);
#endif
  u8g2.firstPage();
  do 
  {
    switch(FS)
    {
      case sleeping:
        sleep();
        break;
      case idle:
        if(millis()- lastActive > SleepDelay)
        {
          FS = sleeping;
        }
        switch (inter)
        {           
          case small :
            Display_small();
            draw_window_small();
            break;
          case big :
            display_big();
            draw_window_big();
            break;
          default:
            u8g2.setFont(u8g2_font_crox3h_tr);
            u8g2.drawStr(0 ,13,"ERROR with state idle");
            break;
        }
        break;
      case opening:
        switch (inter)
        { 
          case small :
            Display_small();
            if(moving_curtains_small(0, 32,95, 32,0) == 1)
            {
              FS = idle;
            }
            break;
          case big :
            display_big();
            if(moving_curtains_big(80, 0,0) == 1)
            {
              FS = idle;
            }
            break;
          default:
            u8g2.setFont(u8g2_font_crox3h_tr);
            u8g2.drawStr(0 ,13,"ERROR with state opening");
            break; 
        }
        break;
      case closing:
        switch (inter)
        { 
          case small :
            Display_small();
            if(moving_curtains_small(0, 32,95, 32,1) == 1)
            {
              FS = idle;
            }
            break;
          case big :
            display_big();
            if(moving_curtains_big(80, 0,1) == 1)
            {
              FS = idle;
            }
            break;
          default:
            u8g2.setFont(u8g2_font_crox3h_tr);
            u8g2.drawStr(0 ,13,"ERROR with state opening");
            break;
        }
        break;
      case settings:
        settingsDisp();
        break;
      default:
        u8g2.setFont(u8g2_font_crox3h_tr);
        u8g2.drawStr(0 ,13,"ERROR with state's");
        break;
    }
    if (FS != settings)
    {
      if (active == 0)
      {
        switch(inter)
        {
          case small:
            u8g2.setFont(u8g2_font_open_iconic_embedded_2x_t);
            u8g2.drawGlyph(9,24,0x004E);
            break;
          case big:
            u8g2.setFont(u8g2_font_open_iconic_embedded_2x_t);
            u8g2.drawGlyph(56,37,0x004E);
            break;
        }
      }
      else if (manualOverride == 1)
      {
        switch(inter)
        {
          case small:
            u8g2.setFont(u8g2_font_crox3h_tr);
            u8g2.drawStr(10,24,"M");
            break;
          case big:
            u8g2.setFont(u8g2_font_crox3h_tr);
            u8g2.drawStr(57,37,"M");
            break;
        }
      }

      if (RolMoving == true)
      {
        switch(inter)
        {
          case small:
            switch(movingIconDir)
            {
              case 0: 
                u8g2.setFontDirection(0);
                u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
                u8g2.drawGlyph(103,25,0x0057);
                break;
              case 1: 
                u8g2.setFontDirection(3);
                u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
                u8g2.drawGlyph(119,25,0x0057);
                break;
              case 2: 
                u8g2.setFontDirection(2);
                u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
                u8g2.drawGlyph(118,8,0x0057);
                break;
              case 3: 
                u8g2.setFontDirection(1);
                u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
                u8g2.drawGlyph(102,10,0x0057);
                break;
            }
            break;
          case big:
            switch(movingIconDir)
            {
              case 0: 
                u8g2.setFontDirection(0);
                u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
                u8g2.drawGlyph(55,62,0x0057);
                break;
              case 1: 
                u8g2.setFontDirection(3);
                u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
                u8g2.drawGlyph(71,62,0x0057);
                break;
              case 2: 
                u8g2.setFontDirection(2);
                u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
                u8g2.drawGlyph(70,45,0x0057);
                break;
              case 3: 
                u8g2.setFontDirection(1);
                u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
                u8g2.drawGlyph(54,47,0x0057);
                break;
            }
            break;
        }
        if (millis() - lastRolMovementIcon > RolMovingIconRot)
        {
          if (movingIconDir != 3){movingIconDir ++;}
          else {movingIconDir = 0;}
          lastRolMovementIcon = millis();
        }
        u8g2.setFontDirection(0);
        lastActive = millis();
      }
    }
  } while ( u8g2.nextPage() );
}
