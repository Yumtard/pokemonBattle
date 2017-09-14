#pragma once

#include "Move.h"
#include "Pokemon.h"

class DamagingMove
	: public Move
{
public:
	DamagingMove();
	void Use(Pokemon& attacker_in, Pokemon& target_in);

private:
};