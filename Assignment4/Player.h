#pragma once

#include "Pokemon.h"
#include <string>
#include <iostream>

class Player
{
public:
	Player(char* name_in, bool AI_in);
	void ViewPokemons();
	bool SwitchPokemon(int nextPokemon_in);
	void AddPokemon(Pokemon* pokemon_in);
	Pokemon& GetCurPokemon() const;
	Pokemon& GetPokemon(int index) const;
	const char* GetName() const;
	bool HasNotLost() const;
	int GetNumPokemons() const;
	bool IsAI() const;

private:
	char* name;
	int numPokemons;
	int curPokemon;
	static constexpr int maxNumPokemons = 6;
	Pokemon* pokemons[maxNumPokemons];
	bool AI;
};