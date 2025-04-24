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
