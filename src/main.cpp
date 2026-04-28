#include <Arduino.h>
#include "app/Application.h"

lorascope::app::Application app;

void setup() {
  app.begin();
}

void loop() {
  app.loop();
}
