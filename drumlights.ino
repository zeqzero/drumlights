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
  lightLEDs(kick_leds, NUM_LEDS_KICK, 0, 0, 0);
  lightLEDs(snare_leds, NUM_LEDS_SNARE, 0, 0, 0);
  lightLEDs(tom1_leds, NUM_LEDS_TOM1, 0, 0, 0);
  lightLEDs(tom2_leds, NUM_LEDS_TOM2, 0, 0, 0);
  lightLEDs(tom3_leds, NUM_LEDS_TOM3, 0, 0, 0);
  lightLEDs(hhat_leds, NUM_LEDS_HHAT, 0, 0, 0);
  lightLEDs(crash1_leds, NUM_LEDS_CRASH1, 0, 0, 0);
  lightLEDs(crash2_leds, NUM_LEDS_CRASH2, 0, 0, 0);
  lightLEDs(ride_leds, NUM_LEDS_RIDE, 0, 0, 0);
  lightLEDs(test_leds, NUM_LEDS_TEST, 0, 0, 0);
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

  FastLED.addLeds<NEOPIXEL, 2>(kick_leds, NUM_LEDS_KICK);
  FastLED.addLeds<NEOPIXEL, 3>(snare_leds, NUM_LEDS_SNARE);
  FastLED.addLeds<NEOPIXEL, 4>(tom1_leds, NUM_LEDS_TOM1);
  FastLED.addLeds<NEOPIXEL, 5>(tom2_leds, NUM_LEDS_TOM2);
  FastLED.addLeds<NEOPIXEL, 6>(tom3_leds, NUM_LEDS_TOM3);
  FastLED.addLeds<NEOPIXEL, 7>(hhat_leds, NUM_LEDS_HHAT);
  FastLED.addLeds<NEOPIXEL, 8>(crash1_leds, NUM_LEDS_CRASH1);
  FastLED.addLeds<NEOPIXEL, 9>(crash2_leds, NUM_LEDS_CRASH2);
  FastLED.addLeds<NEOPIXEL, 10>(ride_leds, NUM_LEDS_RIDE);
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

    if (lightStripNo == 2) {
      lightLEDs(kick_leds, NUM_LEDS_KICK, r, g, b);
      //Serial.println("<Kick lightstrip command processed>");
    } else if (lightStripNo == 3) {
      lightLEDs(snare_leds, NUM_LEDS_SNARE, r, g, b);
      //Serial.println("<Snare lightstrip command processed>");
    } else if (lightStripNo == 4) {
      lightLEDs(tom1_leds, NUM_LEDS_TOM1, r, g, b);
      //Serial.println("<Tom1 lightstrip command processed>");
    }  else if (lightStripNo == 5) {
      lightLEDs(tom2_leds, NUM_LEDS_TOM2, r, g, b);
      //Serial.println("<Tom2 lightstrip command processed>");
    }  else if (lightStripNo == 6) {
      lightLEDs(tom3_leds, NUM_LEDS_TOM3, r, g, b);
      //Serial.println("<Tom3 lightstrip command processed>");
    }  else if (lightStripNo == 7) {
      lightLEDs(hhat_leds, NUM_LEDS_HHAT, r, g, b);
      //Serial.println("<Hihat lightstrip command processed>");
    }  else if (lightStripNo == 8) {
      lightLEDs(crash1_leds, NUM_LEDS_CRASH1, r, g, b);
      //Serial.println("<Crash1 lightstrip command processed>");
    }  else if (lightStripNo == 9) {
      lightLEDs(crash2_leds, NUM_LEDS_CRASH2, r, g, b);
      //Serial.println("<Crash2 lightstrip command processed>");
    }  else if (lightStripNo == 10) {
      lightLEDs(ride_leds, NUM_LEDS_RIDE, r, g, b);
      //Serial.println("<Ride lightstrip command processed>");
    }  else if (lightStripNo == 11) {
      lightLEDs(test_leds, NUM_LEDS_TEST, r, g, b);
      //Serial.println("<Test lightstrip command processed>");
    } else {
      Serial.println("<Command failure>");
    }
    
    Serial.println("<Command success>");
    newData = false;
  }
}
