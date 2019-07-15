#include "MidiboyDIN5MIDI.h"

void MidiboyDIN5MIDI::begin()
{
	Serial.begin(31250);
}

Stream &MidiboyDIN5MIDI::dinMidi() const
{
	return Serial;
}
