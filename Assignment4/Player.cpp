#include "Player.h"

Player::Player(char* name_in)
	:
	name(name_in)
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
}

void Player::SwitchPokemon(int curPokemon_in)
{
	if (curPokemon_in >= 0 && curPokemon_in < numPokemons)
	{
		curPokemon = curPokemon_in;
	}
}

void Player::AddPokemon(Pokemon* pokemon_in)
{
	if (numPokemons < maxNumPokemons)
	{
		pokemons[numPokemons] = pokemon_in;
		numPokemons++;
	}
}

Pokemon & Player::GetPokemon()
{
	return *pokemons[curPokemon];
}

const char* Player::GetName() const
{
	return name;
}

bool Player::HasLost() const
{
	for (int i = 0; i < numPokemons; i++)
	{
		if (!pokemons[i]->IsDead())
		{
			return false;
		}
	}
	return true;
}

int Player::GetNumPokemons() const
{
	return numPokemons;
}
