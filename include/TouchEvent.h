#pragma once

enum class TouchEvent
{
	nothing,
	q_set_mode_change = 1,
	p_set_mode_change,
	q_is_mode_change,
	p_is_mode_change,
	go_menu_page,
	mem_q_tgl,
	mem_p_tgl,
	mem_ps_tgl,
	go_numpad_q,
	go_numpad_p,
	go_numpad_ps,
	release_toggle,

	release_on,
	release_off,
	ps_switch_val,

	menu_page_back = 30,
	precision_toggle,
	go_current_page,
	go_about_page,
	go_analog_page,
	go_number_page,
	number_page_back,
	pid_enable_toggle,
	q_set_u_convert_param_open_numpad,

	ps_val_1 = 51,
	ps_val_2,
	ps_val_3,
	ps_val_4,
	ps_val_5,
	ps_val_6,
	ps_val_7,
	ps_val_8,
	ps_val_9,

	bar_graph_p,
	bar_graph_q,
	bar_graph_ps,

	editbox_data_avail,
	number_page_enter,

	numpad_q_enter,
	numpad_p_enter,
	numpad_ps_enter,

	q_set_new_value,
	p_set_new_value,
	ps_set_new_value,

	numpad_dispman_q_enter,
	numpad_dispman_p_enter,
	numpad_dispman_ps_enter
};