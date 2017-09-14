#pragma once

#include "Pokemon.h"
#include <string>
#include <iostream>

class Player
{
public:
	Player(const std::string& name_in);
	void ViewPokemons();
	void SwitchPokemon(int curPokemon_in);
	void AddPokemon(Pokemon* pokemon_in);
	Pokemon& GetPokemon();
	const std::string& GetName() const;
	bool HasLost() const;
	int GetNumPokemons() const;

private:
	std::string name;
	int numPokemons;
	int curPokemon;
	static constexpr int maxNumPokemons = 6;
	Pokemon* pokemons[maxNumPokemons];
};