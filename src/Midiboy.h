#ifndef MIDIBOY_H
#define MIDIBOY_H

#include "MidiboyDisplay.h"
#include "MidiboyDIN5MIDI.h"
#include "MidiboyUSBMIDI.h"
#include "MidiboyInput.h"

// Midiboy class connects all of Midiboy functionality to a single class.
// Check out the API documentation for each parent class to see what's available.
// You can access all the APIs via the global Midiboy object, for example:
//
// Midiboy.begin();
//
// You may also make use of each individual parent class directly and avoid Midiboy
// global object entirely, that makes the sketch include only the relevant code and
// optimize the rest of it out. But in most usual cases, using Midiboy directly
// should be preferred.
class _Midiboy : public MidiboyDisplay, public MidiboyDIN5MIDI, public MidiboyUSBMIDI, public MidiboyInput
{
public:
	// Initialize Midiboy and all its parent classes. Call this function from your setup().
	void begin();

	// Tells Midiboy to think a bit, should be called from your loop(), in case you have blocking internal event
	// loops within your loop() logic, the think() should be called from inside them, to keep USB and button input responsive.
	void think();
};

extern _Midiboy Midiboy;

#endif // MIDIBOY_H
