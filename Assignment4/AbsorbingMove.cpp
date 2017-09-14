#include "AbsorbingMove.h"

AbsorbingMove::AbsorbingMove(char* name_in, int damage_in)
	:
	Move(name_in, damage_in)
{}

void AbsorbingMove::Use(Pokemon & attacker_in, Pokemon & target_in)
{
	target_in.TakeDamage(damage);
	attacker_in.TakeDamage(-(damage / 2));
	std::cout << attacker_in.GetName() << "s HP was replenished by " << damage / 2 << " points." << std::endl;
}
