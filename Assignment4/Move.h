#pragma once

#include "Pokemon.h"
#include <string>

class Move
{
public:
	Move();
	virtual void Use(Pokemon& attacker_in, Pokemon& target_in) = 0;
	int GetDamage() const;

private:
	int damage;
	std::string name;
};