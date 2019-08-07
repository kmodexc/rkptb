/*
* DisplayManager.cpp
*
* Created: 24.07.2019 15:58:37
* Author: Marius
*/


#include "DisplayManager.h"

// default constructor
DisplayManager::DisplayManager()
{
	dt_q.drawCharwise = true;
	dt_q.x = 100;
	dt_q.y = 100;
	disp.clearStr(dt_q.new_str,DisplayText::STRLEN);
	disp.clearStr(dt_q.old_str,DisplayText::STRLEN);
	disp.cpystr(dt_q.new_str,"Menge :");
	
	dt_p.drawCharwise = true;
	dt_p.x = 100;
	dt_p.y = 150;
	disp.clearStr(dt_p.new_str,DisplayText::STRLEN);
	disp.clearStr(dt_p.old_str,DisplayText::STRLEN);
	disp.cpystr(dt_p.new_str,"Druck :");
	
	dt_ps.drawCharwise = true;
	dt_ps.x = 100;
	dt_ps.y = 200;
	disp.clearStr(dt_ps.new_str,DisplayText::STRLEN);
	disp.clearStr(dt_ps.old_str,DisplayText::STRLEN);
	disp.cpystr(dt_ps.new_str,"Param :");
	
	
	// init receive buffer
	for(size_t cnt=0;cnt < DISPM_REC_BUFFER_SIZE; cnt++){
		rec_buffer[cnt] = 0;
	}
	// init touch event
	te = nothing;
} //DisplayManager

// default destructor
DisplayManager::~DisplayManager()
{
} //~DisplayManager

void DisplayManager::initialize()
{
	disp.initialize();
	
	
	// display settings
	
	disp.command("#TA");	// terminal off
	disp.command("#ZF6,");	// text font (6)
	disp.command("#DL");	// clear display
	disp.command("#AQ1,");	// send bar graph value after each setting
	disp.flush();
	
	// measurement mode switch buttons
	
	disp.command("#FE0,0,0,0,0,0,");	// make colorless buttons
	disp.flush();
	disp.command("#AT420,100,460,120,1,0,\x0d");
	disp.flush();
	disp.command("#AT420,150,460,170,2,0,\x0d");
	disp.flush();
	disp.command("#AT620,100,660,120,3,0,\x0d");
	disp.flush();
	disp.command("#AT620,150,660,170,4,0,\x0d");
	disp.flush();
	
	
	// bar graphs
	
	disp.command("#BF6,");	// Bar graph font
	disp.flush();
	
	// bar graph q
	disp.command("#BR1,100,250,750,300,0,100,5,");
	disp.flush();
	disp.command("#BX1,90,260,0=0.0;100=11.0\x0d");
	disp.flush();
	disp.command("#BA1,0,");
	disp.flush();
	disp.command("#AB1,");
	disp.flush();
	disp.command("#ZL0,260,Q\x0d");
	disp.flush();
	
	// bar graph p
	disp.command("#BR2,100,320,750,370,0,100,5,");
	disp.flush();
	disp.command("#BX2,90,330,0=0.0;100=11.0\x0d");
	disp.flush();
	disp.command("#BA2,0,");
	disp.flush();
	disp.command("#AB2,");
	disp.flush();
	disp.command("#ZL0,330,P\x0d");
	disp.flush();
	
	// bar graph ps
	disp.command("#BR3,100,390,750,440,0,100,5,");
	disp.flush();
	disp.command("#BX3,90,400,0=0.0;100=11.0\x0d");
	disp.flush();
	disp.command("#BA3,0,");
	disp.flush();
	disp.command("#AB3,");
	disp.flush();
	disp.command("#ZL0,400,PS\x0d");
	disp.flush();	
	
}

void DisplayManager::set_q_set(_float val,Unit un)
{
	val.print(dt_q.new_str+10);
	unit_print(dt_q.new_str+16,un);
	dt_q.update = true;
}

void DisplayManager::set_q_is(_float val,Unit un)
{
	val.print(dt_q.new_str+20);
	unit_print(dt_q.new_str+26,un);
	dt_q.update = true;
}

void DisplayManager::set_p_set(_float val,Unit un)
{
	val.print(dt_p.new_str+10);
	unit_print(dt_p.new_str+16,un);
	dt_p.update = true;
}

void DisplayManager::set_p_is(_float val,Unit un)
{
	val.print(dt_p.new_str+20);
	unit_print(dt_p.new_str+26,un);
	dt_p.update = true;
}

void DisplayManager::set_ps_pre_set(_float val,Unit un)
{
	val.print(dt_ps.new_str+20);
	unit_print(dt_ps.new_str+26,un);
	dt_ps.update = true;
}

void DisplayManager::set_ps_set(_float val,Unit un)
{
	val.print(dt_ps.new_str+10);
	unit_print(dt_ps.new_str+16,un);
	dt_ps.update = true;
}

TouchEvent DisplayManager::getTouchEvent()
{
	TouchEvent ret_ev = te;
	te = nothing;
	return ret_ev;
}

uint8_t DisplayManager::getBarValue()
{
	return barval;
}

void DisplayManager::readSendBuffer()
{
	// wait until prev message was pulled
	if(te == nothing && disp.requestBuffer(rec_buffer,5)){
		
		// touch button response
		if(rec_buffer[0] == BIN_ESC && rec_buffer[1] == 'A' && rec_buffer[2] == 1){
			switch(rec_buffer[3]){
				case 1:
				te = q_set_mode_change;
				break;
				case 2:
				te = p_set_mode_change;
				break;
				case 3:
				te = q_is_mode_change;
				break;
				case 4:
				te = p_is_mode_change;
				break;
				
				case 11:
				te = ps_val_1;
				break;
				case 12:
				te = ps_val_2;
				break;
				case 13:
				te = ps_val_3;
				break;
				case 14:
				te = ps_val_4;
				break;
				case 15:
				te = ps_val_5;
				break;
				case 16:
				te = ps_val_6;
				break;
				case 17:
				te = ps_val_7;
				break;
				case 18:
				te = ps_val_8;
				break;
				case 19:
				te = ps_val_9;
				break;
				
				
				default:
				TRACELN(rec_buffer[3]);
				break;
			}
		}
		
		if(rec_buffer[0] == BIN_ESC && rec_buffer[1] == 'B' && rec_buffer[2] == 2){
			barval = rec_buffer[4];
			switch(rec_buffer[3]){
				case 2:
				te = bar_graph_q;
				break;
				case 3:
				te = bar_graph_p;
				break;
				case 4:
				te = bar_graph_ps;
				break;
				default:
				break;
			}			
		}
	}
}

void DisplayManager::loop(uint64_t loopCount)
{
	bool drawn_this_iter = false;
	
	if(!drawn_this_iter && ((loopCount/5) % 4) == 0){
		drawn_this_iter = disp.text(&dt_q,2);
	}
	
	if(!drawn_this_iter && (((loopCount/5) + 1) % 4) == 0){
		drawn_this_iter = disp.text(&dt_p,2);
	}
	
	if(!drawn_this_iter && (((loopCount/5) + 2) % 4) == 0){
		drawn_this_iter = disp.text(&dt_ps,2);
	}
	
	if(!drawn_this_iter && (((loopCount/5) + 3) % 4) == 0 && ((loopCount % 5) == 0)){
		drawn_this_iter = true;
		readSendBuffer();
	}
	
	disp.loop(loopCount);
}

void DisplayManager::unit_print(char* str,Unit u)
{
	if (u == Unit::Volt) {
		str[0] = 'V';
		str[1] = ' ';
	}
	else {
		str[0] = 'm';
		str[1] = 'A';
	}
}
