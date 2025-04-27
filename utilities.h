#pragma once

void splitMessage(const String& message, String parts[], int maxParts) {
  int partIndex = 0;
  int start = 0;
  int end = message.indexOf(',');

  while (end != -1 && partIndex < maxParts) {
    parts[partIndex++] = message.substring(start, end);
    start = end + 1;
    end = message.indexOf(',', start);
  }

  // Add last part (or whole string if no commas)
  if (partIndex < maxParts) {
    parts[partIndex++] = message.substring(start);
  }
}



class check_timer {
  public:
  check_timer(uint64_t check, uint64_t* store){
    fCheckTime = check;
    fStore = store;
  }

  bool check(){
    if ((*fStore) - esp_timer_get_time() > fCheckTime) {
      (*fStore) += fCheckTime;
      return true;
    }
    return false;
  }

  uint64_t* fStore;
  uint64_t fCheckTime;
};

