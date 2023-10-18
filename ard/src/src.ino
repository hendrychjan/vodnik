namespace config {

const uint8_t SEGMENTS[] = {12, 11, 10, 9, 8, 7, 6};

const int CHAR_INTERVAL_DELAY = 500;
const int WORD_INTERVAL_DELAY = 2000;

const bool DECODE_TABLE[18][7] = {
    /*0: 0*/ {1, 1, 1, 1, 1, 1, 0},
    /*1: 1*/ {0, 1, 1, 0, 0, 0, 0},
    /*2: 2*/ {1, 1, 0, 1, 1, 0, 1},
    /*3: 3*/ {1, 1, 1, 1, 0, 0, 1},
    /*4: 4*/ {0, 1, 1, 0, 0, 1, 1},
    /*5: 5*/ {1, 0, 1, 1, 0, 1, 1},
    /*6: 6*/ {1, 0, 1, 1, 1, 1, 1},
    /*7: 7*/ {1, 1, 1, 0, 0, 0, 0},
    /*8: 8*/ {1, 1, 1, 1, 1, 1, 1},
    /*9: 9*/ {1, 1, 1, 1, 0, 1, 1},
    /*10: °*/ {1, 1, 0, 0, 0, 1, 1},
    /*11: C*/ {1, 0, 0, 1, 1, 1, 0},
    /*12: %100*/ {1, 1, 1, 1, 1, 1, 1},
    /*13: %75*/ {0, 1, 1, 1, 1, 1, 1},
    /*14: %50*/ {0, 0, 1, 1, 1, 0, 1},
    /*15: %25*/ {0, 0, 1, 1, 1, 0, 0},
    /*16: %0*/ {0, 0, 0, 1, 0, 0, 0},
    /*17:  */ {0, 0, 0, 0, 0, 0, 0},
};

}  // namespace config

void seg_initSegmentPins();
void seg_segmentWrite(int target, int delayTime);
void seg_printValueByDigits(int value, int delayTime);
void seg_printWaterLevel(int waterLevel);
void seg_printTemperature(int temperature);

void setup() { seg_initSegmentPins(); }

void loop() {
  seg_printWaterLevel(95);
  seg_printTemperature(7);
}

// ==== Segment display ====

void seg_initSegmentPins() {
  for (uint8_t i = 0; i < 7; i++) {
    pinMode(config::SEGMENTS[i], OUTPUT);
  }
}

void seg_segmentWrite(int target, int delayTime = config::CHAR_INTERVAL_DELAY) {
  for (uint8_t i = 0; i < 7; i++) {
    digitalWrite(config::SEGMENTS[i], !config::DECODE_TABLE[target][i]);
  }
  delay(delayTime);
}

void seg_printValueByDigits(int value,
                            int delayTime = config::CHAR_INTERVAL_DELAY) {
  // Note: the value should never be more than 100 and less than 0
  if (value < 10) {
    seg_segmentWrite(value);
  } else if (value < 100) {
    seg_segmentWrite(value / 10);
    seg_segmentWrite(value % 10);
  } else {
    seg_segmentWrite(1);
    seg_segmentWrite(0);
    seg_segmentWrite(0);
  }
}

void seg_printWaterLevel(int waterLevel) {
  seg_printValueByDigits(waterLevel);

  // %
  for (uint8_t i = 12; i <= 16; i++) {
    seg_segmentWrite(i, 180);
  }

  // _
  seg_segmentWrite(17, config::WORD_INTERVAL_DELAY);
}

void seg_printTemperature(int temperature) {
  seg_printValueByDigits(temperature);

  // °
  seg_segmentWrite(10);

  // C
  seg_segmentWrite(11);

  // _
  seg_segmentWrite(17,config::WORD_INTERVAL_DELAY);
}
