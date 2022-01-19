#include "Date.h"

tuple<int, int, int> Date::Today() const
{
	return tuple(_day, _month, _year);
}