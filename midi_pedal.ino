#include <Bounce.h>

// the MIDI channel number to send messages
const int MIDI_CHAN = 3;
const int MIDI_VALUE = 127;
const int MIDI_CC = 24;


// Create Bounce objects for each button and switch. The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.
// 5 = 5 ms debounce time which is appropriate for good quality mechanical push buttons.
// If a button is too "sensitive" to rapid touch, you can increase this time.

//button debounce time
const int DEBOUNCE_TIME = 5;

Bounce buttons[1] =
{
  Bounce (1, DEBOUNCE_TIME),
};

//The setup function. Called once when the Teensy is turned on or restarted
void setup()
{
    pinMode (1, INPUT_PULLUP);
}

//The loop function. Called over-and-over once the setup function has been called.
void loop()
{
  {
    buttons[0].update();
  }

  // Check the status of each push button
    // Check each button for "falling" edge.
    // Falling = high (not pressed - voltage from pullup resistor) to low (pressed - button connects pin to ground)
    if (buttons[0].fallingEdge())
  {
   usbMIDI.sendControlChange (MIDI_CC, MIDI_VALUE, MIDI_CHAN);
  }

    // Check each button for "rising" edge
    // Rising = low (pressed - button connects pin to ground) to high (not pressed - voltage from pullup resistor)
    else if (buttons[0].risingEdge())
  {
        usbMIDI.sendControlChange (MIDI_CC, 0, MIDI_CHAN);
  }
  while (usbMIDI.read())
  {
    // ignoring incoming messages, so don't do anything here.
  } 
}
