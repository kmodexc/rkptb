#include <Arduino.h>

#include "Application.h"

Application app;

uint64_t lc;

void setup()
{
  app.initialize();
  lc = 0;
}

void loop()
{
  app.loop(lc);
  lc++;
}