#include "AbsorbingMove.h"

AbsorbingMove::AbsorbingMove(const std::string& name_in, int damage_in)
	:
	Move(name_in, damage_in)
{}

void AbsorbingMove::Use(Pokemon & attacker_in, Pokemon & target_in)
{
	target_in.TakeDamage(m_Damage);
	attacker_in.TakeDamage(-(m_Damage / 2));
	std::cout << attacker_in.GetName() << "s HP was replenished by " << m_Damage / 2 << " points." << std::endl;
}
