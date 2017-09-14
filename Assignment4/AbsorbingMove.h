#pragma once

#include "Move.h"
#include "Pokemon.h"
#include <iostream>

class AbsorbingMove
	: public Move
{
public:
	AbsorbingMove(const std::string& name_in, int damage_in);
	void Use(Pokemon& attacker_in, Pokemon& target_in);

private:
};