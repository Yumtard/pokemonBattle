#pragma once

#include "Move.h"
#include "Pokemon.h"

class AbsorbingMove
	: public Move
{
public:
	AbsorbingMove();
	void Use(Pokemon& attacker_in, Pokemon& target_in);

private:
};