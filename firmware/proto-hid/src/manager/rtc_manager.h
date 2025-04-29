#pragma once
#include <Arduino.h>
#if USE_RTC
#include <Wire.h>
#include <RTClib.h>
#endif
class RTCManager {
public:
  static void begin();
  static bool available();
  static String getTimestamp();
  
private:
#if USE_RTC
  static RTC_DS3231 rtc;
  static bool rtcAvailable;
#endif
};
