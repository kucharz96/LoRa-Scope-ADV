#pragma once
#include <Arduino.h>
#include <M5Cardputer.h>
#include "../radio/RadioEngine.h"
#include "../radio/ScanEngine.h"
#include "../ui/UiRenderer.h"
#include "../ui/UiState.h"
#include "../input/InputController.h"
#include "../storage/LogWriter.h"

namespace lorascope::app {

class Application {
public:
  void begin();
  void loop();

private:
  void handleCommand(input::Command command);
  void refreshUi(const radio::SweepLine* line = nullptr);
  uint8_t batteryPercent() const;
  void cyclePreset();

  radio::RadioEngine _radio;
  radio::ScanEngine _scanner{_radio};
  ui::UiRenderer _ui;
  ui::UiState _state;
  input::InputController _input;
  storage::LogWriter _log;

  uint32_t _lastSweepMs = 0;
  uint32_t _lastUiMs = 0;
  float _antennaRssiSum = 0;
  float _antennaBestScore = 0;
  uint32_t _antennaSamples = 0;
  radio::Preset _preset = radio::Preset::Custom;
};

} // namespace lorascope::app
