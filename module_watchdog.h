#include <esp_task_wdt.h>

#define WDT_TIMEOUT 1

void WD_START() {
  // esp_task_wdt_init(WDT_TIMEOUT, true);
  // esp_task_wdt_add(NULL);
}

void WD(bool okay) {
    // if (okay) esp_task_wdt_reset();
}