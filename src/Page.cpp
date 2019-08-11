#include "Page.h"

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
	touchEvent = nothing;

	mVisible = false;
}

void Page::repaint(Graphics *pg)
{
	mVisible = true;
}

void Page::set_q_set(_float val, Unit un)
{
}

void Page::set_q_is(_float val, Unit un)
{
}

void Page::set_p_set(_float val, Unit un)
{
}

void Page::set_p_is(_float val, Unit un)
{
}

void Page::set_ps_pre_set(_float val, Unit un)
{
}

void Page::set_ps_set(_float val, Unit un)
{
}

TouchEvent Page::getTouchEvent()
{
	TouchEvent ret_ev = touchEvent;
	touchEvent = nothing;
	return ret_ev;
}

uint8_t *Page::getTouchData()
{
	return eventData;
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
	if (touchEvent == nothing && pgr->requestBuffer(rec_buffer, 9))
	{

		// touch button response
		if (rec_buffer[0] == BIN_ESC && rec_buffer[1] == 'A' && rec_buffer[2] == 1)
		{
			switch (rec_buffer[3])
			{
			case 1:
				touchEvent = q_set_mode_change;
				break;
			case 2:
				touchEvent = p_set_mode_change;
				break;
			case 3:
				touchEvent = q_is_mode_change;
				break;
			case 4:
				touchEvent = p_is_mode_change;
				break;
			case 5:
				touchEvent = go_menu_page;
				break;
			case 6:
				touchEvent = mem_q_tgl;
				break;
			case 7:
				touchEvent = mem_p_tgl;
				break;
			case 8:
				touchEvent = mem_ps_tgl;
				break;
			case 9:
				touchEvent = go_numpad_q;
				break;
			case 10:
				touchEvent = go_numpad_p;
				break;
			case 11:
				touchEvent = go_numpad_ps;
				break;

			case 51:
				touchEvent = ps_val_1;
				break;
			case 52:
				touchEvent = ps_val_2;
				break;
			case 53:
				touchEvent = ps_val_3;
				break;
			case 54:
				touchEvent = ps_val_4;
				break;
			case 55:
				touchEvent = ps_val_5;
				break;
			case 56:
				touchEvent = ps_val_6;
				break;
			case 57:
				touchEvent = ps_val_7;
				break;
			case 58:
				touchEvent = ps_val_8;
				break;
			case 59:
				touchEvent = ps_val_9;
				break;

			case 30:
				touchEvent = menu_page_back;
				break;
			case 31:
				touchEvent = precision_toggle;
				break;
			case 32:
				touchEvent = go_current_page;
				break;
			case 33:
				touchEvent = go_about_page;
				break;
			case 34:
				touchEvent = go_analog_page;
				break;
			case 35:
				touchEvent = go_number_page;
				break;

			default:
				TRACELN(rec_buffer[3]);
				break;
			}
		}

		// Bargraph
		if (rec_buffer[0] == BIN_ESC && rec_buffer[1] == 'B' && rec_buffer[2] == 2)
		{
			eventData[0] = rec_buffer[4];
			switch (rec_buffer[3])
			{
			case 2:
				touchEvent = bar_graph_q;
				break;
			case 3:
				touchEvent = bar_graph_p;
				break;
			case 4:
				touchEvent = bar_graph_ps;
				break;
			default:
				break;
			}
		}

		// Editbox
		if (rec_buffer[0] == BIN_ESC && rec_buffer[1] == 'E')
		{
			// to do...
			uint8_t len = rec_buffer[2];
			uint8_t *tdit = eventData;
			uint8_t *rbit = rec_buffer;
			while (rbit < (rec_buffer + len + 3) && rbit < (rec_buffer + DISPM_REC_BUFFER_SIZE) && tdit < (eventData + TOUCH_EVENT_DATA_SIZE))
			{
				*(tdit++) = *(rbit++);
			}
			touchEvent = editbox_data_avail;
		}
	}
}