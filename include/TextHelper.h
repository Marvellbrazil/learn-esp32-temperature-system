#ifndef TEXT_HELPER_H
#define TEXT_HELPER_H

#include <Arduino.h>

void formatLine16(char *dest, size_t destSize, const char *src);
void formatFloatLine16(char *dest, size_t destSize, float value, const char *unit);

#endif