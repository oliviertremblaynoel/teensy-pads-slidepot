#include <ResponsiveAnalogRead.h>
#include <Wire.h> 
#include <Bounce.h>
#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))

int MIDI_CHAN = 3; 
int THRESH = 60; 
Bounce btn(2, 5);
int btn_cc = 9;

int piezo_pin[] = {A0, A1, A6, A7, A8, A9};
int piezo_cc[] = {0, 1, 2, 3, 4, 5};
int piezo_state[] = {0,0,0,0,0,0};
int piezo_cur[] = {0,0,0,0,0,0};
int piezo_prev[] = {0,0,0,0,0,0};
uint32_t piezo_lastOnTime[6];

int slidepot_pin[] = {A4,A5};
int slidepot_cc[] = {6, 7};
int slidepot_prev[] = {0,0};

ResponsiveAnalogRead analog[] = {
  ResponsiveAnalogRead(A4, true),
  ResponsiveAnalogRead(A5, true)
  };

void setup() {
// BTN
	pinMode(2, INPUT_PULLUP);
};

void loop() {
// btn
	btn.update();
	if (btn.fallingEdge()) {
		usbMIDI.sendControlChange (btn_cc, 64, MIDI_CHAN);
	} else if (btn.risingEdge()) {
		usbMIDI.sendControlChange (btn_cc, 0, MIDI_CHAN);
	}
// Piezo
  for (uint16_t i = 0; i < ARRAY_SIZE(piezo_pin); i++) {
		int v = analogRead(piezo_pin[i]);
		switch(piezo_state[i]) {
			case 0:
				if (v > THRESH) {
					piezo_prev[i] = v;
					piezo_state[i] = 1;
				}
			break;
			case 1: 
				if (v > piezo_prev[i]) piezo_prev[i] = v;
				else {
					piezo_state[i] = 2;
				}
				break;
			case 2:
  			usbMIDI.sendControlChange(piezo_cc[i], piezo_prev[i]/8, MIDI_CHAN);
				piezo_lastOnTime[i] = millis();
				piezo_state[i] = 3;
			break;
			case 3: // ignore signals during the exclusion time
				if (millis() - piezo_lastOnTime[i] >= 100) piezo_state[i] = 0;
			break;
		}
	};
// Slidepot
	for (uint16_t i = 0; i < ARRAY_SIZE(slidepot_pin); i++) {
      analog[i].update();
      int scaled = analog[i].getValue() / 8;
      if (scaled != slidepot_prev[i]) {
				usbMIDI.sendControlChange(slidepot_cc[i], scaled, MIDI_CHAN);
  			slidepot_prev[i] = scaled;
	  	};
	};
};
