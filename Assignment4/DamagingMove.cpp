#include "DamagingMove.h"

DamagingMove::DamagingMove(char* name_in, int damage_in)
	: 
	Move(name_in, damage_in)
{}

void DamagingMove::Use(Pokemon & attacker_in, Pokemon & target_in)
{
	target_in.TakeDamage(damage);
}
