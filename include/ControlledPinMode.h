#pragma once
#include <stdint.h>

enum class ControlledPinMode
{
	Voltage,
	Current
};

#define CPM_NEXT(val) (val == ControlledPinMode::Voltage ? ControlledPinMode::Current : ControlledPinMode::Voltage)
#define CPM_SWITCH(val) val = CPM_NEXT(val)