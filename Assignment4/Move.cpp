#include "Move.h"

Move::Move(char* name_in, int damage_in)
	:
	m_Name(name_in),
	m_Damage(damage_in)
{}

int Move::GetDamage() const
{
	return m_Damage;
}
