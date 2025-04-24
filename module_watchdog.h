#pragma once
#include <esp_task_wdt.h>
#include "module_config.h"

#define WDT_TIMEOUT 15000

esp_task_wdt_config_t wdt_config;

void WD_START() {
  if (CONFIG::WATCHDOG_ENABLED){
    wdt_config.timeout_ms = WDT_TIMEOUT;
    esp_task_wdt_init(&wdt_config);
    esp_task_wdt_add(NULL);
  }
}

void WD(bool okay) {
  if (CONFIG::WATCHDOG_ENABLED){
    if (okay) esp_task_wdt_reset();
  } 
}