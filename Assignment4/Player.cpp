#include "Player.h"

Player::Player(char* name_in, bool AI_in)
	:
	name(name_in),
	AI(AI_in)
{
	numPokemons = 0;
	curPokemon = 0;
}

void Player::ViewPokemons()
{
	for (int i = 0; i < numPokemons; i++)
	{
		std::cout << "(" << i << ") " << pokemons[i]->GetInfo() << std::endl;
	}
	std::cout << "\n";
}

bool Player::SwitchPokemon(int nextPokemon_in)
{
	if (curPokemon == nextPokemon_in)
	{
		std::cout << name << " is sticking with " << pokemons[curPokemon]->GetName() << "\n" << std::endl;
		return false;
	}
	
	std::cout << name << ": " << pokemons[curPokemon]->GetName() << "! That's enough! Come back!" << std::endl;

	curPokemon = nextPokemon_in;

	std::cout << name << " sent out " << pokemons[curPokemon]->GetName() << "\n" << std::endl;

	return true;
}

void Player::AddPokemon(Pokemon* pokemon_in)
{
	if (numPokemons < maxNumPokemons)
	{
		pokemons[numPokemons] = pokemon_in;
		numPokemons++;
	}
}

Pokemon & Player::GetCurPokemon() const
{
	return *pokemons[curPokemon];
}

Pokemon & Player::GetPokemon(int index) const
{
	return *pokemons[index];
}

const char* Player::GetName() const
{
	return name;
}

bool Player::HasNotLost() const
{
	for (int i = 0; i < numPokemons; i++)
	{
		if (!pokemons[i]->IsDead())
		{
			return true;
		}
	}
	return false;
}

int Player::GetNumPokemons() const
{
	return numPokemons;
}

bool Player::IsAI() const
{
	return AI;
}
