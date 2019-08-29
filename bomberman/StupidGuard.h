#pragma once
#include "Guard.h"

//--------------------------------------------------------
class StupidGuard : public Guard {
	using Guard::Guard;
	void move() override;

};