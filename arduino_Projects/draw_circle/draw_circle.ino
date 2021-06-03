#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

uint8_t progress = 100;

void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
}

void loop() {
//  if(progress == 100)
//  {
//      progress = 0;
//      delay(1000);
//  }
//  else
//  {
//    progress ++;
//  }
  // put your main code here, to run repeatedly:
  u8g2.firstPage();
  do {
    /* all graphics commands have to appear within the loop body. */    
    u8g2.setDrawColor(1);
    float end_angle = myMap(progress,0,100,-PI/2,3*PI/2);
    DrawArc(-PI/2,end_angle,64,32,25);
    u8g2.setFont(u8g2_font_open_iconic_arrow_4x_t);
    //u8g2.drawGlyph(46,46,0x004B); //UP
    //u8g2.drawGlyph(46,46,0x0048); //DOWN
    u8g2.setFont(u8g2_font_open_iconic_embedded_4x_t);
    u8g2.drawGlyph(46,46,0x0048); //SETTINGS
  } while ( u8g2.nextPage() );
  delay(1);
}

void DrawArc(float start_angle, float end_angle, int x, int y, int r)
{
  for (float i = start_angle; i < end_angle; i = i + 0.05)
  {
    u8g2.drawLine(x + cos(i) * r, y + sin(i) * r,x + cos(i) * r-4, y + sin(i) * r-4);
  }   
}

float myMap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return ((x - in_min) * (out_max - out_min)) / ((in_max - in_min)) + out_min;
}
