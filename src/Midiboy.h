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

#ifndef MIDIBOY_H
#define MIDIBOY_H

#include "MidiboyDisplay.h"
#include "MidiboyDIN5MIDI.h"
#include "MidiboyUSBMIDI.h"
#include "MidiboyInput.h"
#include "MidiboyFonts.h"

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
