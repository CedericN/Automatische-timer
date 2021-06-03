void Display_small()
{
  u8g2.setFont(u8g2_font_crox3h_tr);
  u8g2.drawStr(30 ,13,daysOfTheWeek[TijdNu.dayOfTheWeek()]);
  
  u8g2.setFont(u8g2_font_crox3h_tn);
  u8g2.drawStr(46,37,u8x8_u8toa(TijdNu.day(),2));
  u8g2.drawStr(63,37,"/");
  u8g2.drawStr(67,37,u8x8_u8toa(TijdNu.month(),2));

  u8g2.drawStr(46,61,u8x8_u8toa(TijdNu.hour(),2));
  u8g2.drawStr(63,61,":");
  u8g2.drawStr(67,61,u8x8_u8toa(TijdNu.minute(),2));
  
}

void draw_window_small()
{
  if (RolOpen == true)
  {
    draw_curtains_open_small(0, 32);
    draw_curtains_open_small(95, 32);
  }
  else
  {
    draw_curtains_closed_small(0, 32);
    draw_curtains_closed_small(95, 32);
  }
}

void display_big ()
{
  u8g2.setFont(u8g2_font_crox3h_tr);
  u8g2.drawStr(0 ,13,daysOfTheWeek[TijdNu.dayOfTheWeek()]);
  
  u8g2.setFont(u8g2_font_crox3h_tn);
  u8g2.drawStr(0,37,u8x8_u8toa(TijdNu.day(),2));
  u8g2.drawStr(17,37,"/");
  u8g2.drawStr(21,37,u8x8_u8toa(TijdNu.month(),2));

  u8g2.drawStr(0,61,u8x8_u8toa(TijdNu.hour(),2));
  u8g2.drawStr(17,61,":");
  u8g2.drawStr(21,61,u8x8_u8toa(TijdNu.minute(),2));
}

void draw_window_big()
{
  if (RolOpen == true)
  {
    draw_curtains_open_big(80, 0);
  }
  else
  {
    draw_curtains_closed_big(80, 0);
  }
}
