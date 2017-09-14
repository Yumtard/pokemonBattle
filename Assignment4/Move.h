#pragma once

#include "Pokemon.h"
#include <string>

class Move
{
public:
	Move(const std::string& name_in, int damage_in);
	virtual void Use(Pokemon& attacker_in, Pokemon& target_in) = 0;
	int GetDamage() const;

protected:
	int damage;
	std::string name;
};