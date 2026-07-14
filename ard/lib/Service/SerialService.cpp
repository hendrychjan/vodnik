#include "SerialService.hpp"

void SerialService::setup() {}

static void handleCommand(const String& atCommand, StateService& stateService) {
  if (atCommand.startsWith("pump ")) {
    // "pump <index> <state>"  e.g. "pump 2 1"
    const String args = atCommand.substring(5);
    const int spaceIdx = args.indexOf(' ');
    if (spaceIdx < 0) return;

    const uint8_t index = args.substring(0, spaceIdx).toInt();
    const bool state = args.substring(spaceIdx + 1).toInt() != 0;

    if (index < Config::NUMBER_OF_PUMPS) {
      stateService.pumpsActivated[index] = state;
    }
  } else if (atCommand.startsWith("mode ")) {
    // "mode <value>"  1 = automatic, 2 = override
    const int value = atCommand.substring(5).toInt();

    if (value == 1) {
      stateService.setMode(AUTOMATIC);
    } else if (value == 2) {
      stateService.setMode(OVERRIDE);
    }
  }
}

void SerialService::hook() {
  static String inputBuffer;

  while (Serial.available() > 0) {
    const char ch = static_cast<char>(Serial.read());

    if (ch == '\n' || ch == '\r') {
      inputBuffer.trim();
      if (inputBuffer.length() > 0) {
        handleCommand(inputBuffer, _stateService);
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