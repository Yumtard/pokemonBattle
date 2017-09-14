#include "Pokemon.h"

Pokemon::Pokemon(char* name_in, int hp_in)
	:
	name(name_in),
	hp(hp_in),
	numMoves(0)
{}

const char* Pokemon::GetName() const
{
	return name;
}

void Pokemon::DisplayMoves() const
{
	for (int i = 0; i < numMoves; i++)
	{
		std::cout << "(" << i << ") " << availableMoves[i] << std::endl;
	}
	std::cout << "\n";
}

void Pokemon::TakeDamage(int damage_in)
{
	hp -= std::min(damage_in, hp);
}

const std::string & Pokemon::GetInfo()
{
	std::string moves;
	for (int i = 0; i < numMoves; i++)
	{
		moves += availableMoves[i] + ", ";
	}
	std::string stringName(name);
	info = stringName + ", HP: " + std::to_string(hp) + ", Moves: " + moves;
	return info;
}

void Pokemon::AddMove(const std::string& move_in)
{
	if (numMoves < numMovesMax)
	{
		availableMoves[numMoves] = move_in;
		numMoves++;
	}
}

const std::string& Pokemon::GetMove(int choice) const
{
	return availableMoves[choice];
}

bool Pokemon::IsDead() const
{
	return hp == 0;
}

int Pokemon::GetNumMoves() const
{
	return numMoves;
}

int Pokemon::GetHP() const
{
	return hp;
}
