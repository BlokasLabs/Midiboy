#ifndef MIDIBOY_DIN5_MIDI_H
#define MIDIBOY_DIN5_MIDI_H

#include <Arduino.h>

class MidiboyDIN5MIDI
{
public:
	// Initialize DIN-5 MIDI serial ports.
	void begin();

	// Get the DIN-5 MIDI I/O stream. Use it the same way as you'd use Arduino's Serial for MIDI.
	Stream &dinMidi() const;
};

#endif // MIDIBOY_DIN5_MIDI_H
