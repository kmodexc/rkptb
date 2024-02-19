#include "Page.h"

using namespace rkp;

void rkp::unit_print(char *str, Unit u)
{
	if (u == Unit::Volt)
	{
		str[0] = 'V';
		str[1] = ' ';
	}
	else
	{
		str[0] = 'm';
		str[1] = 'A';
	}
}

void Page::initialize(Graphics *pg)
{
	// init receive buffer
	for (size_t cnt = 0; cnt < DISPM_REC_BUFFER_SIZE; cnt++)
	{
		rec_buffer[cnt] = 0;
	}

	// init touch event
	touchEvent = TouchEvent::nothing;

	mVisible = false;
}

void Page::set_cont_output(IControlledOutput *, IControlledOutput *, IControlledOutput *)
{
}

void Page::repaint(Graphics *pg)
{
	mVisible = true;
}

void Page::update_context(const Context &)
{
}

void Page::set_q_set(const PhysicalValue &val)
{
}

void Page::set_q_is(const PhysicalValue &val)
{
}

void Page::set_p_set(const PhysicalValue &val)
{
}

void Page::set_p_is(const PhysicalValue &val)
{
}

void Page::set_ps_pre_set(const PhysicalValue &val)
{
}

void Page::set_ps_set(const PhysicalValue &val)
{
}

void Page::set_error(const bool val, const bool newVal)
{
}

void Page::set_release(const bool val, const bool newVal)
{
}

TouchEvent Page::getTouchEvent()
{
	TouchEvent ret_ev = touchEvent;
	touchEvent = TouchEvent::nothing;
	return ret_ev;
}

void *Page::getTouchData()
{
	return static_cast<void *>(eventData);
}

void Page::loop(uint64_t loopCount, Graphics *disp)
{
	readSendBuffer(disp);
}

void Page::unshow(Graphics *pg)
{
	pg->clearScreen();
	mVisible = false;
}

bool Page::isVisible()
{
	return mVisible;
}

void Page::readSendBuffer(Graphics *pgr)
{
	// wait until prev message was pulled
	if (touchEvent == TouchEvent::nothing && pgr->requestBuffer(rec_buffer, 9))
	{

		memset(eventData, 0, TOUCH_EVENT_DATA_SIZE);

		// touch button response
		if (rec_buffer[0] == BIN_ESC && rec_buffer[1] == 'A' && rec_buffer[2] == 1)
		{
			touchEvent = static_cast<TouchEvent>(rec_buffer[3]);
		}

		// Bargraph
		if (rec_buffer[0] == BIN_ESC && rec_buffer[1] == 'B' && rec_buffer[2] == 2)
		{
			*eventData = rec_buffer[4];
			switch (rec_buffer[3])
			{
			case 2:
				touchEvent = TouchEvent::bar_graph_q;
				break;
			case 3:
				touchEvent = TouchEvent::bar_graph_p;
				break;
			case 4:
				touchEvent = TouchEvent::bar_graph_ps;
				break;
			default:
				break;
			}
		}

		// Editbox
		if (rec_buffer[0] == BIN_ESC && rec_buffer[1] == 'E')
		{
			uint8_t len = rec_buffer[2];
			uint8_t *tdit = eventData;
			uint8_t *rbit = rec_buffer;
			while (rbit < (rec_buffer + len + 3) && rbit < (rec_buffer + DISPM_REC_BUFFER_SIZE) && tdit < (eventData + TOUCH_EVENT_DATA_SIZE))
			{
				*(tdit++) = *(rbit++);
			}
			touchEvent = TouchEvent::editbox_data_avail;
		}
	}
}