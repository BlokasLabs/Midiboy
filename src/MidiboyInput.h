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

#ifndef MIDIBOY_INPUT_H
#define MIDIBOY_INPUT_H

#include <stdint.h>
#include <Arduino.h>

enum Button
{
	BUTTON_A     = digitalPinToBit(PIN_BTN_A),
	BUTTON_B     = digitalPinToBit(PIN_BTN_B),
	BUTTON_UP    = digitalPinToBit(PIN_BTN_UP),
	BUTTON_DOWN  = digitalPinToBit(PIN_BTN_DOWN),
	BUTTON_LEFT  = digitalPinToBit(PIN_BTN_LEFT),
	BUTTON_RIGHT = digitalPinToBit(PIN_BTN_RIGHT),

	BUTTON_COUNT = 6
};

enum InputEventType
{
	EVENT_DOWN = 0,
	EVENT_UP   = 1,
};

struct InputEvent
{
	Button         m_button;
	InputEventType m_type;
};

class MidiboyInput
{
public:
	// Initialize the Midiboy Input.
	void begin();

	// Checks the state of the Buttons, queues up detected events for processing.
	void think();

	// Accepted milliseconds range: [0;65536]. If set to 0, input repeat is disabled.
	void setButtonRepeatMs(uint16_t milliseconds);
	uint16_t getButtonRepeatMs() const;

	// Retrieves a pending input event. If it returned true, the event will be provided via the result argument,
	// if false was returned, there were no pending Input events.
	//
	// Recommended pattern to iterate over the events:
	//
	// InputEvent event;
	// while (readInputEvent(event))
	// {
	//     switch (event.m_button)
	//     {
	//     case BUTTON_A:
	//         if (event.m_type == EVENT_DOWN)
	//             run();
	//         break;
	//     ...
	//     }
	// }
	bool readInputEvent(InputEvent &result);
};

#endif // MIDIBOY_INPUT_H
