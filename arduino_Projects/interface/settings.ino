void settingsDisp()
{
  lastActive = millis();
  if(millis()- LastPressSet > SettingsEscDelay)
  {
    FS = idle;
    TijdNu = rtc.now();
    lastMillis = millis();
    if(active == 1){checkTime();}  
  }
  else
  {
    u8g2.setFont(u8g2_font_open_iconic_embedded_2x_t);
    u8g2.drawGlyph(112,16,0x0048);
    switch (SetFS)
    {
      case startSet:
        u8g2.setFont(u8g2_font_crox3h_tr);
        u8g2.drawStr(32 ,38,"Settings");  
        break;
      case editClock:
      {
        u8g2.setFont(u8g2_font_open_iconic_app_2x_t);
        u8g2.drawGlyph(0,16,0x0045);
        switch(mSetFS)
        {
          case look:
          {
            yearTemp = yearClockTemp;
            monthTemp = monthClockTemp;
            dayTemp = dayClockTemp;
            hourTemp = hourClockTemp;
            minuteTemp = minuteClockTemp;
            break;
          }
          case select:
          {
            switch(editPos)
            {
              case 0:
                u8g2.drawLine(38,38,54,38);
                break;
              case 1:
                u8g2.drawLine(59,38,75,38);
                break;
              case 2:
                u8g2.drawLine(80,38,96,38);
                break;
              case 3:
                u8g2.drawLine(46,62,62,62);
                break;
              case 4:
                u8g2.drawLine(67,62,83,62);
                break;
            }
            break;
          }
          case edit:
          {
            switch(editPos)
            {
              case 0:
                drawDottedLine(38,54,38);
                break;
              case 1:
                drawDottedLine(59,75,38);
                break;
              case 2:
                drawDottedLine(80,96,38);
                break;
              case 3:
                drawDottedLine(46,62,62);
                break;
              case 4:
                drawDottedLine(67,83,62);
                break;
            }
            break;
          }
        }
        u8g2.setFont(u8g2_font_crox3h_tn);
        u8g2.drawStr(38,37,u8x8_u8toa(dayTemp,2));
        u8g2.drawStr(55,37,"/");
        u8g2.drawStr(59,37,u8x8_u8toa(monthTemp,2));
        u8g2.drawStr(76,37,"/");
        u8g2.drawStr(80,37,u8x8_u8toa(yearTemp,2));
      
        u8g2.drawStr(46,61,u8x8_u8toa(hourTemp,2));
        u8g2.drawStr(63,61,":");
        u8g2.drawStr(67,61,u8x8_u8toa(minuteTemp,2));
        break;
      }
      case editUp:
        u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
        u8g2.drawGlyph(0,16,0x004B);
        switch(mSetFS)
        {
          case look:
          {
            hourTemp = hourUpTemp;
            minuteTemp = minuteUpTemp;
            break;
          }
          case select:
          {
            switch(editPos)
            {
              case 3:
                u8g2.drawLine(46,38,62,38);
                break;
              case 4:
                u8g2.drawLine(67,38,83,38);
                break;
            }
            break;
          }
          case edit:
          {
            switch(editPos)
            {
              case 3:
                drawDottedLine(46,62,38);
                break;
              case 4:
                drawDottedLine(67,83,38);
                break;
            }
            break;
          }
        }
        u8g2.setFont(u8g2_font_crox3h_tn);
        u8g2.drawStr(46,37,u8x8_u8toa(hourTemp,2));
        u8g2.drawStr(63,37,":");
        u8g2.drawStr(67,37,u8x8_u8toa(minuteTemp,2));  
        break;
      case editDown:
        u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
        u8g2.drawGlyph(0,16,0x0048); 
        switch(mSetFS)
        {
          case look:
          {
            hourTemp = hourDownTemp;
            minuteTemp = minuteDownTemp;
            break;
          }
          case select:
          {
            switch(editPos)
            {
              case 3:
                u8g2.drawLine(46,38,62,38);
                break;
              case 4:
                u8g2.drawLine(67,38,83,38);
                break;
            }
            break;
          }
          case edit:
          {
            switch(editPos)
            {
              case 3:
                drawDottedLine(46,62,38);
                break;
              case 4:
                drawDottedLine(67,83,38);
                break;
            }
            break;
          }
        }
        u8g2.setFont(u8g2_font_crox3h_tn);
        u8g2.drawStr(46,37,u8x8_u8toa(hourTemp,2));
        u8g2.drawStr(63,37,":");
        u8g2.drawStr(67,37,u8x8_u8toa(minuteTemp,2));
        break;
      case editDisp:
        u8g2.setFont(u8g2_font_open_iconic_thing_2x_t);
        u8g2.drawGlyph(0,16,0x0050);
        u8g2.setFont(u8g2_font_crox3h_tr);
        u8g2.drawStr(50,30,"disp"); 
        if(interTemp == 0){u8g2.drawStr(45, 53, "small");}
        else{u8g2.drawStr(55, 53, "big");}
        break;
      default:
        u8g2.setFont(u8g2_font_crox3h_tr);
        u8g2.drawStr(0 ,13,"ERROR Set not found");  
        break;
    }
  }
}

void drawDottedLine(uint8_t x1, uint8_t x2, uint8_t y)
{
  while(x1 < x2)
  {
    u8g2.drawPixel(x1,y);
    x1 += 2;
  }
}
