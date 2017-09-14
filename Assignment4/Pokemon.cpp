#include "Pokemon.h"

Pokemon::Pokemon(const std::string& name_in, int hp_in)
	:
	name(name_in),
	hp(hp_in),
	numMoves(1)
{}

const std::string & Pokemon::GetName() const
{
	name;
}

void Pokemon::DisplayMoves() const
{
	for (int i = 0; i < numMoves; i++)
	{
		std::cout << "(" << i << ") " << availableMoves[i] << std::endl;
	}
}

void Pokemon::TakeDamage(int damage_in)
{
	hp -= std::min(damage_in, hp);
}

const std::string & Pokemon::GetInfo() const
{
	std::string moves;
	for (int i = 0; i < numMoves; i++)
	{
		moves += *availableMoves[i] + " ";
	}

	std::string info = name + "HP: " + std::to_string(hp) + "\nMoves: " + moves;
	return info;
}

const std::string & Pokemon::GetMove(int choice) const
{
	return *availableMoves[choice];
}

bool Pokemon::IsDead() const
{
	return hp == 0;
}

int Pokemon::GetNumMoves() const
{
	return numMoves;
}
