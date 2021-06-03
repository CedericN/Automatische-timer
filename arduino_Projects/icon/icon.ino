#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

uint8_t dir = 0;

U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R2, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

void setup(void) {
  u8g2.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  u8g2.firstPage();
  do {
        draw_curtains_closed(0, 32);
        draw_curtains_open(95, 32);
    //    opening_curtains(48, 16);
    //    delay (2000);
    //    close_curtains(48, 16);
    //    delay (2000);
//    display_big ();
//    draw_window_big();
//    u8g2.setFont(u8g2_font_crox3h_tr);
//    u8g2.drawStr(57, 37, "M");
    u8g2.setFont(u8g2_font_crox3h_tr);
    u8g2.drawStr(10,24,"M");
//    u8g2.setFont(u8g2_font_open_iconic_embedded_2x_t);
//    u8g2.drawGlyph(56,37,0x004E);
//    u8g2.setFont(u8g2_font_open_iconic_embedded_2x_t);
//    u8g2.drawGlyph(9,24,0x004E);
    switch (dir)
    {
      case 0:
        u8g2.setFontDirection(0);
        u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
        //        u8g2.drawGlyph(55,62,0x0057); //big
        u8g2.drawGlyph(103, 25, 0x0057); //small
        u8g2.setFontDirection(0);
        u8g2.setFont(u8g2_font_crox3h_tr);
        u8g2.drawStr(100, 56, "1");
        dir ++;
        break;
      case 1:
        u8g2.setFontDirection(3);
        u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
//        u8g2.drawGlyph(71, 62, 0x0057); //big
        u8g2.drawGlyph(119,25,0x0057); //small
        u8g2.setFontDirection(0);
        u8g2.setFont(u8g2_font_crox3h_tr);
        u8g2.drawStr(100, 56, "2");
        dir ++;
        break;
      case 2:
        u8g2.setFontDirection(2);
        u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
//        u8g2.drawGlyph(70, 45, 0x0057); //big
        u8g2.drawGlyph(118, 8, 0x0057); //small
        u8g2.setFontDirection(0);
        u8g2.setFont(u8g2_font_crox3h_tr);
        u8g2.drawStr(100, 56, "3");
        dir ++;
        break;
      case 3:
        u8g2.setFontDirection(1);
        u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
        //        u8g2.drawGlyph(54,47,0x0057); //big
        u8g2.drawGlyph(102, 10, 0x0057); //small
        u8g2.setFontDirection(0);
        u8g2.setFont(u8g2_font_crox3h_tr);
        u8g2.drawStr(100, 56, "4");
        dir = 0;
        break;
    }
  } while ( u8g2.nextPage() );
  delay(500);
}

void display_big ()
{
  u8g2.setFont(u8g2_font_crox3h_tr);
  u8g2.drawStr(0 , 13, "Zondag");

  u8g2.setFont(u8g2_font_crox3h_tn);
  u8g2.drawStr(0, 37, "12");
  u8g2.drawStr(17, 37, "/");
  u8g2.drawStr(21, 37, "03");

  u8g2.drawStr(0, 61, "09");
  u8g2.drawStr(17, 61, ":");
  u8g2.drawStr(21, 61, "11");
}

void draw_window_big()
{
  uint8_t x = 80;
  uint8_t y = 0;
  draw_window_frame_big(x, y);
  u8g2.drawLine(x + 15, y + 15, x + 9, y + 33);
  u8g2.drawLine(x + 18, y + 18, x + 15, y + 27);
}

void opening_curtains(uint8_t x, uint8_t y)
{
  for (uint8_t j = 28; j > 0; j --)
  {
    u8g2.setDrawColor(0);
    u8g2.drawBox(x, y, 32, 32);
    u8g2.setDrawColor(1);
    draw_window_frame(x, y);
    u8g2.drawBox(x + 7, y + 2, 1, j);
    u8g2.drawBox(x + 24, y + 2, 1, j);

    u8g2.drawLine(x + 10, y + 10, x + 6, y + 22);
    u8g2.drawLine(x + 12, y + 12, x + 10, y + 18);
    for (uint8_t i = 4 + (j % 3); i < j; i += 3)
    {
      u8g2.drawBox(x + 4, y + i, 24, 2);
    }
    u8g2.sendBuffer();
    delay(100);
  }
}

void close_curtains(uint8_t x, uint8_t y)
{
  for (uint8_t j = 0; j < 28; j ++)
  {
    u8g2.setDrawColor(0);
    u8g2.drawBox(x, y, 32, 32);
    u8g2.setDrawColor(1);
    draw_window_frame(x, y);
    u8g2.drawBox(x + 7, y + 2, 1, j);
    u8g2.drawBox(x + 24, y + 2, 1, j);

    u8g2.drawLine(x + 10, y + 10, x + 6, y + 22);
    u8g2.drawLine(x + 12, y + 12, x + 10, y + 18);
    for (uint8_t i = 4 + (j % 3); i < j; i += 3)
    {
      u8g2.drawBox(x + 4, y + i, 24, 2);
    }
    u8g2.sendBuffer();
    delay(100);
  }
}

void draw_curtains_closed(uint8_t x, uint8_t y)
{
  draw_window_frame(x, y);
  u8g2.drawBox(x + 7, y + 2, 1, 28);
  u8g2.drawBox(x + 24, y + 2, 1, 28);

  for (uint8_t i = 6; i < 28; i += 3)
  {
    u8g2.drawBox(x + 4, y + i, 24, 2);
  }
}

void draw_curtains_open(uint8_t x, uint8_t y)
{
  draw_window_frame(x, y);
  u8g2.drawLine(x + 10, y + 10, x + 6, y + 22);
  u8g2.drawLine(x + 12, y + 12, x + 10, y + 18);
}

void draw_window_frame (uint8_t x, uint8_t y)
{
  u8g2.drawFrame(x, y, 32, 32);
  u8g2.drawBox(x, y + 3, 32, 1);
  u8g2.drawBox(x + 3, y + 2, 26, 3);
}

void draw_window_frame_big (uint8_t x, uint8_t y)
{
  u8g2.drawFrame(x, y, 48, 64);
  u8g2.drawBox(x, y + 5, 63, 2);
  u8g2.drawBox(x + 4, y + 3, 40, 6);
}
