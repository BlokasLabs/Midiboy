#include "Midiboy.h"

_Midiboy Midiboy;

void _Midiboy::begin()
{
	MidiboyDisplay::begin();
	MidiboyDIN5MIDI::begin();
	MidiboyInput::begin();
}

void _Midiboy::think()
{
	MidiboyUSBMIDI::think();
	MidiboyInput::think();
}
