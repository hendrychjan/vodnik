#include "SerialService.hpp"

void SerialService::setup() {}

void SerialService::_handleCommand(const String& atCommand,
                                   StateService& stateService) {
  if (atCommand.startsWith("pump ")) {
    // "pump <index> <state>"  e.g. "pump 2 1"
    const String args = atCommand.substring(5);
    const int spaceIdx = args.indexOf(' ');
    if (spaceIdx < 0) return;

    const uint8_t index = args.substring(0, spaceIdx).toInt();
    const bool state = args.substring(spaceIdx + 1).toInt() != 0;

    if (state) {
      _stateService.queuePumpCycle(index);
    } else {
      _stateService.clearPumpTimeQueued(index);
    }
  } else if (atCommand.startsWith("refresh")) {
    _stateService.setSensorsToRefreshNow();
  } else if (atCommand.startsWith("stop")) {
    _stateService.clearAllPumpsTimeQueued();
  }
}

void SerialService::hook() {
  static String inputBuffer;

  while (Serial.available() > 0) {
    const char ch = static_cast<char>(Serial.read());

    if (ch == '\n' || ch == '\r') {
      inputBuffer.trim();
      if (inputBuffer.length() > 0) {
        _handleCommand(inputBuffer, _stateService);
      }
      inputBuffer = "";
      continue;
    }

    // Keep memory bounded if the sender never terminates a line.
    if (inputBuffer.length() < 63) {
      inputBuffer += ch;
    }
  }
}