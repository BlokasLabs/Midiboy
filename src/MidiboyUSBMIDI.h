/*
 * Midiboy Core Library.
 * Copyright (C) 2019  Vilniaus Blokas UAB, https://blokas.io/midiboy
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2 of the
 * License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

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
