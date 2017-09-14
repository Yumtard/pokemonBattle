#pragma once

#include "Pokemon.h"
#include <string>

class Player
{
public:
	Player();
	void ViewPokemons();
	void SwitchPokemon(int curPokemon_in);
	void AddPokemon();
	Pokemon& GetPokemon();
	const std::string& GetName() const;
	bool HasLost() const;

private:
	std::string name;
	int numPokemons;
	int curPokemon;
	Pokemon* pokemons[6];
};