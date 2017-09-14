#pragma once

#include "Pokemon.h"
#include <string>

class Move
{
public:
	Move(char* name_in, int damage_in);
	virtual void Use(Pokemon& attacker_in, Pokemon& target_in) = 0;
	int GetDamage() const;

protected:
	int damage;
	char* name;
};