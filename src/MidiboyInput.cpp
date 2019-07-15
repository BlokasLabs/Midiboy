#include "MidiboyInput.h"

#include <fifo.h> // From USBMIDI library.

enum { MAX_EVENTS = 8 };
enum { INPUT_DEBOUNCE_MS = 50 };
enum { INPUT_REPEAT_DELAY_MS = 300 };

struct packed_event_t
{
	uint8_t m_button:3;
	uint8_t m_type:1;
};

static TFifo<packed_event_t, uint8_t, MAX_EVENTS> g_eventQueue;
static uint8_t g_state;
static uint8_t g_repeating;
static unsigned long g_lastUpdated[BUTTON_COUNT];
static uint16_t g_inputRepeatMs = 300;

static inline uint8_t readRawInput()
{
	// Read the state of the button pins directly, they map to the bit numbers of Button enum.
	return PINC & 0x3f;
}

static void updateState()
{
	uint8_t state = readRawInput();

	uint8_t diff = state ^ g_state;

	if (diff)
	{
		unsigned long ms = millis();
		for (uint8_t i=0; i<BUTTON_COUNT; ++i)
		{
			uint8_t bit = 1 << i;
			if ((diff & bit) && (ms - g_lastUpdated[i]) >= INPUT_DEBOUNCE_MS)
			{
				packed_event_t e;
				e.m_button = i;
				e.m_type = (state & bit) ? EVENT_UP : EVENT_DOWN;
				g_eventQueue.push(e);
				g_lastUpdated[i] = ms;
				if (e.m_type == EVENT_UP)
				{
					g_state |= bit;
					g_repeating &= ~bit;
				}
				else
				{
					g_state &= ~bit;
				}
			}
		}
	}
}

void MidiboyInput::begin()
{
	g_state = readRawInput();
	g_repeating = 0;

	pinMode(PIN_BTN_A,     INPUT_PULLUP);
	pinMode(PIN_BTN_B,     INPUT_PULLUP);
	pinMode(PIN_BTN_UP,    INPUT_PULLUP);
	pinMode(PIN_BTN_DOWN,  INPUT_PULLUP);
	pinMode(PIN_BTN_LEFT,  INPUT_PULLUP);
	pinMode(PIN_BTN_RIGHT, INPUT_PULLUP);

	for (int i=0; i<BUTTON_COUNT; ++i)
	{
		g_lastUpdated[i] = millis();
	}
}

void MidiboyInput::think()
{
	updateState();

	if (g_inputRepeatMs == 0)
		return;

	unsigned long ms = millis();
	for (int i=0; i<BUTTON_COUNT; ++i)
	{
		uint8_t bit = 1 << i;
		if ((g_state & bit) == 0)
		{
			if (!(g_repeating & bit))
			{
				if ((ms - g_lastUpdated[i]) >= INPUT_REPEAT_DELAY_MS)
				{
					g_repeating |= bit;
					g_lastUpdated[i] = ms;
				}
			}
			else
			{
				if ((ms - g_lastUpdated[i]) >= g_inputRepeatMs)
				{
					packed_event_t e;
					e.m_button = i;
					e.m_type = EVENT_DOWN;
					g_eventQueue.push(e);
					g_lastUpdated[i] = ms;
				}
			}
		}
	}
}

void MidiboyInput::setButtonRepeatMs(uint16_t milliseconds)
{
	g_inputRepeatMs = milliseconds;
}

uint16_t MidiboyInput::getButtonRepeatMs() const
{
	return g_inputRepeatMs;
}

bool MidiboyInput::readInputEvent(InputEvent & result)
{
	packed_event_t e;
	if (g_eventQueue.pop(e))
	{
		result.m_button = (Button)e.m_button;
		result.m_type = (InputEventType)e.m_type;
		return true;
	}
	else return false;
}