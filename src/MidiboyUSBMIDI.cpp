#include "MidiboyUSBMIDI.h"

#include <usbmidi.h>

void MidiboyUSBMIDI::think()
{
	USBMIDI.poll();
}

Stream &MidiboyUSBMIDI::usbMidi() const
{
	return USBMIDI;
}
