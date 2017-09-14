#include "Player.h"

Player::Player(const std::string & name_in)
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

void Player::AddPokemon(const std::string & pokemonName_in, int hp_in, std::string * move_in)
{
	if (numPokemons < maxNumPokemons)
	{
		pokemons[numPokemons] = new Pokemon(pokemonName_in, hp_in, move_in);
		numPokemons++;
	}
}

Pokemon & Player::GetPokemon()
{
	return *pokemons[curPokemon];
}

const std::string & Player::GetName() const
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
