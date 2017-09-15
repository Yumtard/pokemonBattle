#pragma once

#include "Pokemon.h"
#include <string>
#include <iostream>

class Player
{
public:
	Player(char* name_in, bool AI_in);
	~Player();
	void ViewPokemons();
	bool SwitchPokemon(int nextPokemon_in);
	void AddPokemon(Pokemon* pokemon_in);
	Pokemon& GetCurPokemon() const;
	Pokemon& GetPokemon(int index_in) const;
	const char* GetName() const;
	bool HasNotLost() const;
	int GetNumPokemons() const;
	bool GetHasAttacked() const;
	void SetHasAttacked(bool attacked_in);

private:
	char* m_Name;
	int m_NumPokemons;
	int m_CurPokemon;
	static constexpr int m_MaxNumPokemons = 6;
	Pokemon* m_Pokemons[m_MaxNumPokemons];
	bool m_AI;
	bool hasAttacked = false;
};