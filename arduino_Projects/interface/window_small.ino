/* state is de variable die de functie doet werken
   state = 0 het normaal omhoog gaan van de rolluik
   state = 1 het normaal omlaag gaan van de rolluik
   state = 2 het starten om de rolluik omhoog te laten gaan
   state = 3 het starten om de rolluik omlaag te laten gaan
*/
boolean moving_curtains_small(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t state)
{
  if (state == 2)
  {
    posRol = 28;
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
    u8g2.drawBox(x1, y1, 32, 32);
    u8g2.drawBox(x2, y2, 32, 32);
    u8g2.setDrawColor(1);
    draw_window_frame_small(x1, y1);
    draw_window_frame_small(x2, y2);
    u8g2.drawBox(x1 + 7, y1 + 2, 1, posRol);
    u8g2.drawBox(x1 + 24, y1 + 2, 1, posRol);
    u8g2.drawBox(x2 + 7, y2 + 2, 1, posRol);
    u8g2.drawBox(x2 + 24, y2 + 2, 1, posRol);

    u8g2.drawLine(x1 + 10, y1 + 10, x1 + 6, y1 + 22);
    u8g2.drawLine(x1 + 12, y1 + 12, x1 + 10, y1 + 18);
    u8g2.drawLine(x2 + 10, y2 + 10, x2 + 6, y2 + 22);
    u8g2.drawLine(x2 + 12, y2 + 12, x2 + 10, y2 + 18);
    for (uint8_t i = 4 + (posRol % 3); i < posRol; i += 3)
    {
      u8g2.drawBox(x1 + 4, y1 + i, 24, 2);
      u8g2.drawBox(x2 + 4, y2 + i, 24, 2);
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
      if (posRol == 28)
      {
        return true;
      }
    }
  }
  return false;
}

void draw_curtains_closed_small(uint8_t x, uint8_t y)
{
  draw_window_frame_small(x, y);
  u8g2.drawBox(x + 7, y + 2, 1, 28);
  u8g2.drawBox(x + 24, y + 2, 1, 28);

  for (uint8_t i = 6; i < 28; i += 3)
  {
    u8g2.drawBox(x + 4, y + i, 24, 2);
  }
}

void draw_curtains_open_small(uint8_t x, uint8_t y)
{
  draw_window_frame_small(x, y);
  u8g2.drawLine(x + 10, y + 10, x + 6, y + 22);
  u8g2.drawLine(x + 12, y + 12, x + 10, y + 18);
}

void draw_window_frame_small (uint8_t x, uint8_t y)
{
  u8g2.drawFrame(x, y, 32, 32);
  u8g2.drawBox(x, y + 3, 32, 1);
  u8g2.drawBox(x + 3, y + 2, 26, 3);
}
