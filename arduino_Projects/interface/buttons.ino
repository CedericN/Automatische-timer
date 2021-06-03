void buttonCheck()
{
  boolean readingConfirm = digitalRead(buttonConfirm);
  boolean readingUp = digitalRead(buttonUp);
  boolean readingDown = digitalRead(buttonDown);
  boolean readingBack = digitalRead(buttonBack);
  
  if (readingConfirm != LBSConfirm)
  {
      LDTConfirm = millis();
  }
  if (readingUp != LBSUp)
  {
      LDTUp = millis();
  }
  if (readingDown != LBSDown)
  {
      LDTDown = millis();
  }
  if (readingBack != LBSBack)
  {
      LDTBack = millis();
  }
  
  if((millis()- LDTConfirm) > debounceDelay)
  {
    if (readingConfirm != BSConfirm)
    {
      BSConfirm = readingConfirm;
      if(BSConfirm == LOW)
      {
        lastActive = millis();
#ifdef DEBUGBUTTON
        Serial.println("button Confirm pressed");
#endif
        LastPressSet = millis();
        switch(FS)
        {
          case idle:
            holdDelayDone = hold(buttonConfirm);
            if(holdDelayDone == 1)
            {
              SetFS = startSet;
              FS = settings;
              mSetFS = look;
              yearClockTemp = TijdNu.year()-2000;
              monthClockTemp = TijdNu.month();
              dayClockTemp = TijdNu.day();
              hourClockTemp = TijdNu.hour();
              minuteClockTemp = TijdNu.minute();
              hourUpTemp = hourUp1;
              minuteUpTemp = minuteUp1;
              hourDownTemp = hourDown1;
              minuteDownTemp = minuteDown1;
              if(inter == big){interTemp = 1;}
              else {interTemp = 0;}
            }
          break;
          case settings:
            //in dit settings menu gaan
            switch (mSetFS)
            {
              case look:
                holdDelayDone = hold(buttonConfirm);
                if(holdDelayDone == 1)
                {
                  FS = idle;
                  //code bijverlaten van instellingen (tijd omhoog en omlaag in EEPROM en RTC aanpassen indien nodig)
                  hourUp1 = hourUpTemp;
                  EEPROM.update(AdressHUp1,hourUp1);
                  minuteUp1 = minuteUpTemp;
                  EEPROM.update(AdressMUp1,minuteUp1);
                  hourDown1 = hourDownTemp;
                  EEPROM.update(AdressHDown1,hourDown1);
                  minuteDown1 = minuteDownTemp;
                  EEPROM.update(AdressMDown1,minuteDown1);
                  if(TijdNu.year()-2000 != yearClockTemp || TijdNu.month() != monthClockTemp || TijdNu.day() != dayClockTemp || TijdNu.hour() != hourClockTemp || TijdNu.minute() != minuteClockTemp){rtc.adjust(DateTime(yearClockTemp+2000, monthClockTemp, dayClockTemp, hourClockTemp, minuteClockTemp,0));}
                  if(interTemp == 1){inter = big;}
                  else {inter = small;}
                  EEPROM.update(AdressDispSize,interTemp);
                  TijdNu = rtc.now();
                  lastMillis = millis();
                  if(active == 1){checkTime();}
                }
                else if (holdDelayDone == false && SetFS != startSet)
                {
                  if(SetFS == editClock || SetFS == editUp || SetFS == editDown)
                  {
                    mSetFS = select;
                    if(SetFS == editClock){editPos = 0;}
                    else{editPos = 3;}
                  }
                  else if(SetFS == editDisp){mSetFS = edit;}
                  
                }
              break;
              case select:
                mSetFS = edit;
              break;
            }
          break;
        }
      }
    }
  }
  if((millis()- LDTUp) > debounceDelay)
  {
    if (readingUp != BSUp)
    {
      BSUp = readingUp;
      if(BSUp == LOW)
      {
        lastActive = millis();
#ifdef DEBUGBUTTON
        Serial.println("button Up pressed");
#endif
        LastPressSet = millis();
        switch(FS)
        {
          case idle:
            if(RolOpen == false)
            {
              holdDelayDone = hold(buttonUp);
              if(holdDelayDone == true)
              {
                FS = opening;
                manualOverride = 1;
                startRol(2);
                EEPROM.update(AdressRolOpen,(manualOverride << 2 | active << 1 | RolOpen));
              }
            }
            break;
            
          case settings:
            switch(mSetFS)
            {
              case look:
                switch (SetFS)
                {
                  case startSet:
                    SetFS = editClock;  
                    break;
                  case editClock:
                    SetFS = editUp;  
                    break;
                  case editUp:
                    SetFS = editDown;  
                    break;
                  case editDown:
                    SetFS = editDisp;  
                    break;
                  case editDisp: 
                    break;
                  default:
                    u8g2.setFont(u8g2_font_crox3h_tr);
                    u8g2.drawStr(0 ,13,"ERROR Set not found"); 
                    break;
                }
                break;
              case select:
                if(SetFS == editClock)
                {
                  if(editPos < 4)
                  {
                    editPos ++;
                  }
                }
                else
                {
                  if(editPos == 3)
                  {
                    editPos ++;
                  }  
                }
                break;
              case edit:
                BSUp = HIGH;
                if (SetFS == editDisp)
                {
                  if(interTemp == 0){interTemp = 1;}
                }
                else
                {
                  switch(editPos)
                  {
                    case 0:
                      if(dayTemp < 31)
                      {
                        dayTemp ++;
                      }
                      break;
                    case 1:
                      if(monthTemp < 12)
                      {
                        monthTemp ++;
                      }
                      break;
                    case 2:
                      if(yearTemp < 99)
                      {
                        yearTemp ++;
                      }
                      break;
                    case 3:
                      if(hourTemp < 23)
                      {
                        hourTemp ++;
                      }
                      break;
                    case 4:
                      if(minuteTemp < 59)
                      {
                        minuteTemp ++;
                      }
                      break;
                  }
                }
                delay(100);
            }
        }
      }    
    }
  }
  if((millis()- LDTDown) > debounceDelay)
  {
    if (readingDown != BSDown)
    {
      BSDown = readingDown;

      if(BSDown == LOW)
      {
        lastActive = millis();
#ifdef DEBUGBUTTON
        Serial.println("button Down pressed");
#endif
        LastPressSet = millis();
        switch(FS)
        {
          case idle:
            if(RolOpen == true)
            {
              holdDelayDone = hold(buttonDown);
              if(holdDelayDone == true)
              {
                FS = closing;
                manualOverride = 1;
                startRol(3);
                EEPROM.update(AdressRolOpen,(manualOverride << 2 | active << 1 | RolOpen));
              }
            }
            break;
            
          case settings:
          switch(mSetFS)
            {
              case look:
                switch (SetFS)
                {
                  case startSet:
                    break;
                  case editClock:
                    SetFS = startSet;  
                    break;
                  case editUp:
                    SetFS = editClock;  
                    break;
                  case editDown:
                    SetFS = editUp;  
                    break;
                  case editDisp:
                    SetFS = editDown;  
                    break;
                  default:
                    u8g2.setFont(u8g2_font_crox3h_tr);
                    u8g2.drawStr(0 ,13,"ERROR Set not found"); 
                    break;
                }
                break;
              case select:
                if(SetFS == editClock)
                {
                  if(editPos != 0)
                  {
                    editPos --;
                  }
                }
                else
                {
                  if(editPos == 4)
                  {
                    editPos --;  
                  }
                }
                break;
              case edit:
                BSDown = HIGH;
                if (SetFS == editDisp)
                {
                  if(interTemp == 1){interTemp = 0;}
                }
                else
                {
                  switch(editPos)
                  {
                    case 0:
                      if(dayTemp > 1)
                      {
                        dayTemp --;
                      }
                      break;
                    case 1:
                      if(monthTemp > 1)
                      {
                        monthTemp --;
                      }
                      break;
                    case 2:
                      if(yearTemp > 21)
                      {
                        yearTemp --;
                      }
                      break;
                    case 3:
                      if(hourTemp != 0)
                      {
                        hourTemp --;
                      }
                      break;
                    case 4:
                      if(minuteTemp != 0)
                      {
                        minuteTemp --;
                      }
                      break;
                  }
                }
                delay(100);
            }
        }
      }
    }
  }
  if((millis()- LDTBack) > debounceDelay)
  {
    if (readingBack != BSBack)
    {
      BSBack = readingBack;
      
      if(BSBack == LOW)
      {
        lastActive = millis();
#ifdef DEBUGBUTTON
        Serial.println("button Back pressed");
#endif
        LastPressSet = millis();
        switch(FS)
        {
          case idle:
            holdDelayDone = hold(buttonBack);
            if(holdDelayDone == true)
            {
              if(active == 1){active = 0;}
              else {active = 1;}
              EEPROM.update(AdressRolOpen,(manualOverride << 2 | active << 1 | RolOpen));
            }
            break;
            break;
          case settings:
            switch(mSetFS)
            {
              case look:
                holdDelayDone = hold(buttonBack);
                if(holdDelayDone == true)
                {
                  FS = idle;
                  TijdNu = rtc.now();
                  lastMillis = millis();
                  if(active == 1){checkTime();}
                }
                break;
              case select:
                mSetFS = look;
                switch(SetFS)
                {
                  case editClock:
                    yearClockTemp = yearTemp;
                    monthClockTemp = monthTemp;
                    dayClockTemp = dayTemp;
                    hourClockTemp = hourTemp;
                    minuteClockTemp = minuteTemp;
                    break;
                  case editUp:
                    hourUpTemp = hourTemp;
                    minuteUpTemp = minuteTemp;
                    break;
                  case editDown:
                    hourDownTemp = hourTemp;
                    minuteDownTemp = minuteTemp;
                    break;
                }
                break;
              case edit:
                if(SetFS == editDisp){mSetFS = look;}
                else {mSetFS = select;}
                break;
            }
            break;
        }
      }
    }
  }
  holdDelayDone = false;
  
  LBSConfirm = readingConfirm;
  LBSUp = readingUp;
  LBSDown = readingDown;
  LBSBack = readingBack;
}

void DrawArc(float start_angle, float end_angle, int x, int y, int r)
{
  u8g2.setDrawColor(1);
  for (float i = start_angle; i < end_angle; i = i + 0.05)
  {
    u8g2.drawLine(x + cos(i) * r, y + sin(i) * r,x + cos(i) * r-4, y + sin(i) * r-4);
  }   
}

float myMap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return ((x - in_min) * (out_max - out_min)) / ((in_max - in_min)) + out_min;
}

uint8_t hold(uint8_t button)
{
  unsigned long wait = millis();
  while ((millis() - wait) < holdDelay && digitalRead(button) == LOW)
  {
    if((millis() - wait) > SingelPress)
    {
      u8g2.firstPage();
      do 
      {
        float end_angle = myMap(millis() - wait,0,holdDelay,-PI/2,3*PI/2);
        DrawArc(-PI/2,end_angle,64,32,25);
        switch(button)
        {
          case buttonConfirm: 
            switch(FS)
            {
              case idle:
                u8g2.setFont(u8g2_font_open_iconic_embedded_4x_t);
                u8g2.drawGlyph(46,46,0x0048); //SETTINGS
                break;
              case settings:
                u8g2.setFont(u8g2_font_open_iconic_check_4x_t);
                u8g2.drawGlyph(46,46,0x0040); //check
                break;
            }
            break;
          case buttonUp:
            u8g2.setFont(u8g2_font_open_iconic_arrow_4x_t);
            u8g2.drawGlyph(46,46,0x004B); //UP
            break;
          case buttonDown:
            u8g2.setFont(u8g2_font_open_iconic_arrow_4x_t);
            u8g2.drawGlyph(46,46,0x0048); //DOWN
            break;
          case buttonBack:
            switch(FS)
            {
              case idle:
                u8g2.setFont(u8g2_font_open_iconic_embedded_4x_t);
                u8g2.drawGlyph(46,46,0x004E); //cancel
                break;
              case settings:
                u8g2.setFont(u8g2_font_open_iconic_check_4x_t);
                u8g2.drawGlyph(46,46,0x0044); //cancel
                break;
            }
        }
      } while ( u8g2.nextPage() );
    }
  }
#ifdef DEBUGBUTTON
  Serial.println(millis()-wait);
#endif
  if((millis() - wait) < SingelPress)
  {
#ifdef DEBUGBUTTON
    Serial.println("returning 0");
#endif
    return false;
  }
  else if((millis() - wait) < holdDelay)
  {
#ifdef DEBUGBUTTON
    Serial.println("returning 2");
#endif
    return 2;
  }
  else
  {
#ifdef DEBUGBUTTON
    Serial.println("returning 1");
#endif
    return true;  
  }
}
