#pragma once

#include "Move.h"
#include "Pokemon.h"

class DamagingMove
	: public Move
{
public:
	DamagingMove(const std::string& name_in, int damage_in);
	void Use(Pokemon& attacker_in, Pokemon& target_in);

private:
};