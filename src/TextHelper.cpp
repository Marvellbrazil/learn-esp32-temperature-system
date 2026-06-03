#include "TextHelper.h"
#include <stdio.h>

void formatLine16(char *dest, size_t destSize, const char *src)
{
    snprintf(dest, destSize, "%-16s", src);
}

void formatFloatLine16(char *dest, size_t destSize, float value, const char *unit)
{
    char valueBuffer[10];

    dtostrf(value, 4, 1, valueBuffer);
    snprintf(dest, destSize, "%s %s               ", valueBuffer, unit);

    if (destSize > 16)
    {
        dest[16] = '\0';
    }
}