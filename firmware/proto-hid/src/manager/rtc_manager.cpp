#include "rtc_manager.h"
#include "config.h"
#include "cli_parser.h"
#if USE_RTC
RTC_DS3231 RTCManager::rtc;
bool RTCManager::rtcAvailable = false;
void RTCManager::begin() {
  logInfo("RTC Manager initializing...");
  if (!rtc.begin()) {
    logWarn("RTC not found. RTC support disabled.");
    rtcAvailable = false;
    return;
  }
  if (rtc.lostPower()) {
    logWarn("RTC lost power, setting time from build timestamp.");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  rtcAvailable = true;
  logInfo("RTC initialized successfully.");
}
bool RTCManager::available() {
  return rtcAvailable;
}
String RTCManager::getTimestamp() {
  if (!rtcAvailable) {
    return String("RTC_UNAVAILABLE");
  }
  DateTime now = rtc.now();
  char buf[20];
  snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
           now.year(), now.month(), now.day(),
           now.hour(), now.minute(), now.second());
  return String(buf);
}
#else
void RTCManager::begin() { logInfo("RTC Manager disabled at compile time."); }
bool RTCManager::available() { return false; }
String RTCManager::getTimestamp() { return String("RTC_DISABLED"); }
#endif
