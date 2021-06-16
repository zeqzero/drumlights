#include <MIDI.h>  // Add Midi Library
#include "midi_notenums.h"
MIDI_CREATE_DEFAULT_INSTANCE();

#include "FastLED.h"

#define LED 13    // Arduino Board LED is on Pin 13
#define NUM_LEDS 38

CRGB kick_leds[NUM_LEDS_KICK];
CRGB snare_leds[NUM_LEDS_SNARE];
CRGB tom1_leds[NUM_LEDS_TOM1];
CRGB tom2_leds[NUM_LEDS_TOM2];
CRGB tom3_leds[NUM_LEDS_TOM3];
CRGB hhat_leds[NUM_LEDS_HHAT];
CRGB crash1_leds[NUM_LEDS_CRASH1];
CRGB crash2_leds[NUM_LEDS_CRASH2];
CRGB ride_leds[NUM_LEDS_RIDE];

unsigned long previousTime = 0;

void lightLEDs(CRGB leds[], int num_leds, int r, int g, int b) {
  for (int led=0; led<num_leds; led++) {
    leds[led].setRGB(r, g, b);
  }
  FastLED.show();
}

void MyHandleNoteOn(byte channel, byte note, byte velocity) {
  digitalWrite(LED,HIGH);  //Turn system LED on

  if (note == NOTENUM_KICK_HEAD) {
    lightLEDs(kick_leds, NUM_LEDS_KICK, 0, 255, 255);
  }
  else if ((note == NOTENUM_SNARE_RIM) || (note == NOTENUM_SNARE_HEAD)) {
    lightLEDs(snare_leds, NUM_LEDS_SNARE, 255, 255, 0);
  }
  else if ((note == NOTENUM_TOM1_RIM) || (note == NOTENUM_TOM1_HEAD)) {
    lightLEDs(tom1_leds, NUM_LEDS_TOM1, 255, 0, 0);
  }
  else if ((note == NOTENUM_TOM2_RIM) || (note == NOTENUM_TOM2_HEAD)) {
    lightLEDs(tom2_leds, NUM_LEDS_TOM2, 0, 255, 0);
  }
  else if ((note == NOTENUM_TOM3_RIM) || (note == NOTENUM_TOM3_HEAD)) {
    lightLEDs(tom3_leds, NUM_LEDS_TOM3, 0, 0, 255);
  }
  else if ((note == NOTENUM_HHAT_OPEN_RIM) || (note == NOTENUM_HHAT_CLOSED_RIM) || (note == NOTENUM_HHAT_OPEN_HEAD) || (note == NOTENUM_HHAT_CLOSED_HEAD)) {
    lightLEDs(hhat_leds, NUM_LEDS_HHAT, 255, 0, 255);
  }
  else if ((note == NOTENUM_CRASH1_RIM) || (note == NOTENUM_CRASH1_HEAD)) {
    lightLEDs(crash1_leds, NUM_LEDS_CRASH1, 255, 127, 63);
  }
  else if ((note == NOTENUM_RIDE_RIM) || (note == NOTENUM_RIDE_HEAD)) {
    lightLEDs(ride_leds, NUM_LEDS_RIDE, 127, 63, 255);
  }
  else if ((note == NOTENUM_CRASH2_RIM) || (note == NOTENUM_CRASH2_HEAD)) {
    lightLEDs(crash2_leds, NUM_LEDS_CRASH2, 63, 255, 127);
  }
}

void MyHandleNoteOff(byte channel, byte note, byte velocity) {
  digitalWrite(LED,LOW);//Turn system LED off

  if (note == NOTENUM_KICK_HEAD) {
    lightLEDs(kick_leds, NUM_LEDS_KICK, 0, 0, 0);
  }
  else if ((note == NOTENUM_SNARE_RIM) || (note == NOTENUM_SNARE_HEAD)) {
    lightLEDs(snare_leds, NUM_LEDS_SNARE, 0, 0, 0);
  }
  else if ((note == NOTENUM_TOM1_RIM) || (note == NOTENUM_TOM1_HEAD)) {
    lightLEDs(tom1_leds, NUM_LEDS_TOM1, 0, 0, 0);
  }
  else if ((note == NOTENUM_TOM2_RIM) || (note == NOTENUM_TOM2_HEAD)) {
    lightLEDs(tom2_leds, NUM_LEDS_TOM2, 0, 0, 0);
  }
  else if ((note == NOTENUM_TOM3_RIM) || (note == NOTENUM_TOM3_HEAD)) {
    lightLEDs(tom3_leds, NUM_LEDS_TOM3, 0, 0, 0);
  }
  else if ((note == NOTENUM_HHAT_OPEN_RIM) || (note == NOTENUM_HHAT_CLOSED_RIM) || (note == NOTENUM_HHAT_OPEN_HEAD) || (note == NOTENUM_HHAT_CLOSED_HEAD)) {
    lightLEDs(hhat_leds, NUM_LEDS_HHAT, 0, 0, 0);
  }
  else if ((note == NOTENUM_CRASH1_RIM) || (note == NOTENUM_CRASH1_HEAD)) {
    lightLEDs(crash1_leds, NUM_LEDS_CRASH1, 0, 0, 0);
  }
  else if ((note == NOTENUM_RIDE_RIM) || (note == NOTENUM_RIDE_HEAD)) {
    lightLEDs(ride_leds, NUM_LEDS_RIDE, 0, 0, 0);
  }
  else if ((note == NOTENUM_CRASH2_RIM) || (note == NOTENUM_CRASH2_HEAD)) {
    lightLEDs(crash2_leds, NUM_LEDS_CRASH2, 0, 0, 0);
  }
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
}

void setup() {
  Serial.begin(115200);
  
  pinMode (LED, OUTPUT); // Set Arduino board pin 13 to output

  MIDI.setHandleNoteOn(MyHandleNoteOn); 
  MIDI.setHandleNoteOff(MyHandleNoteOff);

  MIDI.begin(MIDI_CHANNEL_OMNI); // Initialize the Midi Library.

  FastLED.addLeds<NEOPIXEL, 2>(kick_leds, NUM_LEDS_KICK);
  FastLED.addLeds<NEOPIXEL, 3>(snare_leds, NUM_LEDS_SNARE);
  FastLED.addLeds<NEOPIXEL, 4>(tom1_leds, NUM_LEDS_TOM1);
  FastLED.addLeds<NEOPIXEL, 5>(tom2_leds, NUM_LEDS_TOM2);
  FastLED.addLeds<NEOPIXEL, 6>(tom3_leds, NUM_LEDS_TOM3);
  FastLED.addLeds<NEOPIXEL, 7>(hhat_leds, NUM_LEDS_HHAT);
  FastLED.addLeds<NEOPIXEL, 8>(crash1_leds, NUM_LEDS_CRASH1);
  FastLED.addLeds<NEOPIXEL, 9>(crash2_leds, NUM_LEDS_CRASH2);
  FastLED.addLeds<NEOPIXEL, 10>(ride_leds, NUM_LEDS_RIDE);
}

void loop() { // Main loop
  MIDI.read(); // Continually check what Midi Commands have been received.

}
