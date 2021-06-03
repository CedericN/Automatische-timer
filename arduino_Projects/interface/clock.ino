void checkTime()
{
  boolean upFirst;
  boolean RolNormOpen = true;
  boolean RolNormOpenMO = false;
  boolean option = false;
  boolean RolOpenTemp;
  boolean NeedToStart = false;
  uint8_t hour1 = 0;
  uint8_t minute1 = 0;
  uint8_t hour2 = 0;
  uint8_t minute2 = 0;
  
  if(hourUp1 < hourDown1){upFirst = true;}
  else if(hourUp1 > hourDown1){upFirst = false;}
  else
  {
    if(minuteUp1 < minuteDown1){upFirst = true;}
    else{upFirst = false;}
  }

  if(upFirst)
  {
    hour1 = hourUp1;
    minute1 = minuteUp1;
    hour2 = hourDown1;
    minute2 = minuteDown1;
    if(RolOpen == 0){RolOpenTemp = 0;}
    else{RolOpenTemp = 1;}
  }
  else
  {
    hour2 = hourUp1;
    minute2 = minuteUp1;
    hour1 = hourDown1;
    minute1 = minuteDown1;
    if(RolOpen == 1){RolOpenTemp = 0;}
    else{RolOpenTemp = 1;}
  }

    #ifdef DEBUG
  Serial.print("hourUp1:");
  Serial.print(hourUp1);
  Serial.print("\tminuteUp1:");
  Serial.print(minuteUp1); 
  Serial.print("\thourDown1:");
  Serial.print(hourDown1); 
  Serial.print("\tminuteDown1:");
  Serial.print(minuteDown1); 
  Serial.print("\tRolOpenTemp:");
  Serial.print(RolOpenTemp);  
  Serial.print("\tRolOpen:");
  Serial.print(RolOpen);
  Serial.print("\tupFirst:");
  Serial.println(upFirst); 
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
      
  if(TijdNu.hour() >= hour1 && TijdNu.hour() <= hour2)
  {
    if(TijdNu.hour() == hour1 && TijdNu.minute() < minute1)
    {
#ifdef DEBUG
      Serial.println("voor opening");
#endif
      RolNormOpen = false;
    }
    else if(TijdNu.hour() == hour2 && TijdNu.minute() >= minute2)
    {
#ifdef DEBUG
      Serial.println("na sluiten");
#endif
      RolNormOpen = false;
    }
    if(RolNormOpen == true)
    {
      if(upFirst)
      {
        RolNormOpenMO = true;
#ifdef DEBUG
        Serial.println("rol normaal open in");
#endif
      }
      else
      {
        RolNormOpenMO = false;
#ifdef DEBUG
        Serial.println("rol normaal dicht in ");
#endif
      }
    }
    else
    {
      if(upFirst == 0)
      {
        RolNormOpenMO = true;
#ifdef DEBUG 
        Serial.println("rol normaal open uit"); 
#endif
      }
      else
      {
        RolNormOpenMO = false;
#ifdef DEBUG
        Serial.println("rol normaal dicht uit");
#endif
      }
    }
    if(RolOpenTemp != true && RolNormOpen == true)
    {
#ifdef DEBUG
      Serial.println("option 0");
#endif
      option = 0;
      NeedToStart = true;
      //startRol(2);
    }
    else if(RolOpenTemp != false && RolNormOpen == false)
    {
#ifdef DEBUG
      Serial.println("option 1");
#endif
      option = 1;
      NeedToStart = true;
      //startRol(3);
    }
  }
  else if(RolOpenTemp != false)
  {
#ifdef DEBUG
    Serial.println("option 1e");
#endif
    option = 1;
    NeedToStart = true;
    //startRol(3);
  }

  if(manualOverride == 1)
  {
    NeedToStart = false;
    if(RolNormOpenMO)
    {
      if(RolOpen == 1){manualOverride = 0;}
    }
    else
    {
      if(RolOpen == 0){manualOverride = 0;}
    }
  }
  
  if(NeedToStart)
  {
    if(upFirst)
    {
      if(option == 0){startRol(2);}
      else{startRol(3);}
    }
    else
    {
      if(option == 1){startRol(2);}
      else{startRol(3);}
    }
  }
  EEPROM.update(AdressRolOpen,(manualOverride << 2 | active << 1 | RolOpen));
}

void startRol(uint8_t state)
{
  RolMoving = true;
  digitalWrite(RelayOmhoog, LOW);
  digitalWrite(RelayOmlaag, LOW);
  if(state == 2)
  {
#ifdef DEBUG
    Serial.println("Opening");
#endif
    FS = opening;
    RolOpen = true;
    digitalWrite(RelayOmhoog, HIGH);
  }
  else if(state == 3)
  {
#ifdef DEBUG
    Serial.println("Closing");
#endif
    FS = closing;
    RolOpen = false;
    digitalWrite(RelayOmlaag, HIGH);
  }
  
  RolMovementStart = millis();
  if (state == 2 || state == 3)
  {
    switch(inter)
    {
      case small:
        moving_curtains_small(0, 32,95, 32, state);
        break;
      case big:
        moving_curtains_big(80, 0,state);
        break;
      default: 
        u8g2.setFont(/*u8g2_font_crox5t_tr*/u8g2_font_crox3h_tr);
        u8g2.drawStr(0 ,13,"ERROR with closing/opening curtains");
        break;
    }
  }
}
