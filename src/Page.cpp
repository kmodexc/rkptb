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

uint8_t Page::getTouchValue()
{
	return eventVal;
}

void Page::loop(uint64_t loopCount, Graphics *disp)
{
	readSendBuffer(disp);
}

void Page::readSendBuffer(Graphics *pgr)
{
	// wait until prev message was pulled
	if (touchEvent == nothing && pgr->requestBuffer(rec_buffer, 5))
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

			case 11:
				touchEvent = ps_val_1;
				break;
			case 12:
				touchEvent = ps_val_2;
				break;
			case 13:
				touchEvent = ps_val_3;
				break;
			case 14:
				touchEvent = ps_val_4;
				break;
			case 15:
				touchEvent = ps_val_5;
				break;
			case 16:
				touchEvent = ps_val_6;
				break;
			case 17:
				touchEvent = ps_val_7;
				break;
			case 18:
				touchEvent = ps_val_8;
				break;
			case 19:
				touchEvent = ps_val_9;
				break;

			case 30:
				touchEvent = menu_page_back;
				break;

			default:
				TRACELN(rec_buffer[3]);
				break;
			}
		}

		if (rec_buffer[0] == BIN_ESC && rec_buffer[1] == 'B' && rec_buffer[2] == 2)
		{
			eventVal = rec_buffer[4];
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
	}
}