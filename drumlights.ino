#include "FastLED.h"
#include "midi_notenums.h"

CRGB kick_leds[NUM_LEDS_KICK];
CRGB snare_leds[NUM_LEDS_SNARE];
CRGB tom1_leds[NUM_LEDS_TOM1];
CRGB tom2_leds[NUM_LEDS_TOM2];
CRGB tom3_leds[NUM_LEDS_TOM3];
CRGB hhat_leds[NUM_LEDS_HHAT];
CRGB crash1_leds[NUM_LEDS_CRASH1];
CRGB crash2_leds[NUM_LEDS_CRASH2];
CRGB ride_leds[NUM_LEDS_RIDE];
CRGB test_leds[NUM_LEDS_TEST];

void lightLEDs(CRGB leds[], int num_leds, int r, int g, int b) {
  for (int led = 0; led < num_leds; led++) {
    leds[led].setRGB(r, g, b);
  }
  FastLED.show();
}

void clearAllLEDs() {
  lightLEDs(test_leds, NUM_LEDS_TEST, 0, 0, 0);
  lightLEDs(kick_leds, NUM_LEDS_KICK, 0, 0, 0);
  lightLEDs(snare_leds, NUM_LEDS_SNARE, 0, 0, 0);
  lightLEDs(tom1_leds, NUM_LEDS_TOM1, 0, 0, 0);
  lightLEDs(tom2_leds, NUM_LEDS_TOM2, 0, 0, 0);
  lightLEDs(tom3_leds, NUM_LEDS_TOM3, 0, 0, 0);
  lightLEDs(hhat_leds, NUM_LEDS_HHAT, 0, 0, 0);
  lightLEDs(crash1_leds, NUM_LEDS_CRASH1, 0, 0, 0);
  lightLEDs(crash2_leds, NUM_LEDS_CRASH2, 0, 0, 0);
  lightLEDs(ride_leds, NUM_LEDS_RIDE, 0, 0, 0);
}

const byte numChars = 32;
char receivedChars[numChars];
char messageFromRPI[32] = {0};

boolean newData = false;

int lightStripNo;
int r;
int g;
int b;

void setup() {
  Serial.begin(115200);
  Serial.println("<Arduino is ready>");

  FastLED.addLeds<NEOPIXEL, 11>(test_leds, NUM_LEDS_TEST);
}

void loop() {
  receiveCommand();
  parseData();
  executeCommand();
}

void receiveCommand() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

void parseData() {
  if (newData == true) {
    char* strtokIndx;
  
    strtokIndx = strtok(receivedChars, ",");
    lightStripNo = atoi(strtokIndx);
  
    strtokIndx = strtok(NULL, ",");
    r = atoi(strtokIndx);
  
    strtokIndx = strtok(NULL, ",");
    g = atoi(strtokIndx);
  
    strtokIndx = strtok(NULL, ",");
    b = atoi(strtokIndx);
  }
}

void executeCommand() {
  if (newData == true) {
    lightLEDs(test_leds, NUM_LEDS_TEST, r, g, b);
    Serial.println("<Command received and processed>");
    newData = false;
  }
}
