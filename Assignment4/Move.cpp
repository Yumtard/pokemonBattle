#include "Move.h"

Move::Move(char* name_in, int damage_in)
	:
	name(name_in),
	damage(damage_in)
{}

int Move::GetDamage() const
{
	return damage;
}
