#include <Wire.h>
#include "Application.h"
#include "Measurement.h"

Application app;
unsigned long loopCount = 0;

void setup()
{
  app.initialize();
}

void loop()
{
  app.loop(loopCount++);
}
