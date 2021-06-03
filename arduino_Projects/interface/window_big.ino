  /* state is de variable die de functie doet werken
   * state = 0 het normaal omhoog gaan van de rolluik
   * state = 1 het normaal omlaag gaan van de rolluik
   * state = 2 het starten om de rolluik omhoog te laten gaan
   * state = 3 het starten om de rolluik omlaag te laten gaan
   */
boolean moving_curtains_big(uint8_t x, uint8_t y,uint8_t state)
{
  if (state == 2)
  {
    posRol = 59;
    return true;
  }
  else if (state == 3)
  {
    posRol = 0;
    return true;
  }
  else
  {
    u8g2.setDrawColor(0);
    u8g2.drawBox(x, y, 48, 64);
    u8g2.setDrawColor(1);
    draw_window_frame_big(x, y);
    u8g2.drawBox(x + 11, y + 3, 2, posRol);
    u8g2.drawBox(x + 36, y + 3, 2, posRol);
  
    u8g2.drawLine(x + 15, y + 15, x + 9, y + 33);
    u8g2.drawLine(x + 18, y + 18, x + 15, y + 27);
    for (uint8_t i = 7 + (posRol % 5); i < posRol; i += 5)
    {
      u8g2.drawBox(x + 6, y + i, 36, 3);
    }
    if (state == 0)
    {
      posRol --;
      if (posRol == 0)
      {
        return true;
      }
    }
    else if (state == 1)
    {
      posRol ++;
      if (posRol == 59)
      {
        return true;  
      }
    }
  }
  return false; 
}

void draw_curtains_closed_big(uint8_t x, uint8_t y)
{
  draw_window_frame_big(x, y);
  u8g2.drawBox(x + 11, y + 3, 2, 59);
  u8g2.drawBox(x + 36, y + 3, 2, 59);
  u8g2.drawLine(x + 15, y + 15, x + 9, y + 33);
  u8g2.drawLine(x + 18, y + 18, x + 15, y + 27);

  for (uint8_t i = 11; i < 59; i += 5)
  {
    u8g2.drawBox(x + 6, y + i, 36, 3);
  }
}

void draw_curtains_open_big(uint8_t x, uint8_t y)
{
  draw_window_frame_big(x, y);
  u8g2.drawLine(x + 15, y + 15, x + 9, y + 33);
  u8g2.drawLine(x + 18, y + 18, x + 15, y + 27);
}

void draw_window_frame_big (uint8_t x, uint8_t y)
{
  u8g2.drawFrame(x, y, 48, 64);
  u8g2.drawBox(x, y + 5, 63, 2);
  u8g2.drawBox(x + 4, y + 3, 40, 6);
}
