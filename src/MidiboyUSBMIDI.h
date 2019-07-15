#ifndef MIDIBOY_USB_MIDI_H
#define MIDIBOY_USB_MIDI_H

#include <Arduino.h>

class MidiboyUSBMIDI
{
public:
	// Poll the USBMIDI events. Make sure to call it often enough from your loop().
	void think();

	// Get the USB MIDI I/O stream. Use it the same way as you'd use Arduino's Serial for MIDI.
	Stream &usbMidi() const;
};

#endif // MIDIBOY_USB_MIDI_H
