#include "MeasurePin.h"


MeasurePin::MeasurePin(uint8_t p){
    pin = p;
    reset();
}

void MeasurePin::reset(){
    updated = false;
}

uint32_t MeasurePin::getVal(){
    if(!updated){
        val = rkp::stab_ana_read(pin);
        updated = true;
    }
    return val;
}