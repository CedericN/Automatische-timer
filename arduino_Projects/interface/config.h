#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <U8g2lib.h>
#include "RTClib.h"
#include <EEPROM.h>
#include <avr/sleep.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

//#define DEBUG
//#define DEBUGTIME
//#define DEBUGSTATE
//#define DEBUGBUTTON
//#define DEBUGSLEEP

#define TimeBetweenUpdate 5000
#define debounceDelay 50
#define holdDelay 3000
#define SettingsEscDelay 30000
#define SingelPress 200
//#define TimeForRolOpen 5000
#define TimeForRolOpen 30000
#define RolMovingIconRot 1000
#define SleepDelay 30000
//#define SleepDelay 5000

#define buttonConfirm 4 
#define buttonUp 7
#define buttonDown 5
#define buttonBack 6
#define RelayOmhoog 3 //wit
#define RelayOmlaag 2 //blauw

#define AdressRolOpen 0
#define AdressDispSize 1
#define AdressHUp1 2
#define AdressMUp1 3
#define AdressHDown1 5
#define AdressMDown1 6

char daysOfTheWeek[7][12] = {"Zondag", "Maandag", "Dinsdag", "Woensdag", "Donderdag", "Vrijdag", "Zaterdag"};
typedef enum {small, big}interface;
typedef enum {sleeping, idle, opening, closing, settings} states;
typedef enum {startSet, editClock, editUp, editDown, editDisp} settingsFS;
typedef enum {look, select, edit} menuSetFS;

uint8_t posRol;
uint8_t yearTemp;
uint8_t monthTemp;
uint8_t dayTemp;
uint8_t hourTemp;
uint8_t minuteTemp;
uint8_t yearClockTemp;
uint8_t monthClockTemp;
uint8_t dayClockTemp;
uint8_t hourClockTemp;
uint8_t minuteClockTemp;
uint8_t hourUpTemp;
uint8_t minuteUpTemp;
uint8_t hourDownTemp;
uint8_t minuteDownTemp;
uint8_t hourUp1;
uint8_t minuteUp1;
uint8_t hourDown1;
uint8_t minuteDown1;
uint8_t editPos;
uint8_t holdDelayDone = false;
uint8_t movingIconDir = 0;

interface inter;
volatile states FS;
settingsFS SetFS;
menuSetFS mSetFS;

boolean active;
boolean manualOverride;
boolean interTemp;
boolean RolOpen;
boolean setupState = false;
boolean BSConfirm = false;
boolean BSUp = false;
boolean BSDown = false;
boolean BSBack = false;
boolean LBSConfirm = false;
boolean LBSUp = false;
boolean LBSDown = false;
boolean LBSBack = false;
boolean RolMoving = false;
volatile boolean TimeInt = false;
volatile boolean ButtonInt = false;

unsigned long LDTConfirm = 0;
unsigned long LDTUp = 0;
unsigned long LDTDown = 0;
unsigned long LDTBack = 0;
unsigned long lastMillis = 0;
unsigned long LastPressSet = 0;
unsigned long RolMovementStart = 0;
unsigned long lastRolMovementIcon = 0;
unsigned long Millis = 0;
unsigned long lastActive = 0;

DateTime TijdNu;
RTC_PCF8523 rtc;

U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R2, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

#endif
