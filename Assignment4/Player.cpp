#include "Player.h"

Player::Player(char* name_in)
	:
	m_Name(name_in)
{
	m_NumPokemons = 0;
	m_CurPokemon = 0;
}

Player::~Player()
{
	for (int i = 0; i < m_NumPokemons; i++)
	{
		delete m_Pokemons[i];
		m_Pokemons[i] = nullptr;
	}
}

void Player::ViewPokemons()
{
	for (int i = 0; i < m_NumPokemons; i++)
	{
		if (m_Pokemons[i]->IsDead())
		{
			std::cout << "(DEAD) " << m_Pokemons[i]->GetName() << std::endl;
		}
		else
		{
			std::cout << "(" << i << ") " << m_Pokemons[i]->GetInfo() << std::endl;
		}
	}
	std::cout << "\n";
}

bool Player::SwitchPokemon(int nextPokemon_in)
{
	if (m_CurPokemon == nextPokemon_in)
	{
		std::cout << m_Name << " is sticking with " << m_Pokemons[m_CurPokemon]->GetName() << "\n" << std::endl;
		return false;
	}
	
	std::cout << m_Name << ": " << m_Pokemons[m_CurPokemon]->GetName() << "! That's enough! Come back!" << std::endl;

	m_CurPokemon = nextPokemon_in;

	std::cout << m_Name << " sent out " << m_Pokemons[m_CurPokemon]->GetName() << "\n" << std::endl;

	return true;
}

void Player::AddPokemon(Pokemon* pokemon_in)
{
	if (m_NumPokemons < m_MaxNumPokemons)
	{
		m_Pokemons[m_NumPokemons] = pokemon_in;
		m_NumPokemons++;
	}
}

Pokemon & Player::GetCurPokemon() const
{
	return *m_Pokemons[m_CurPokemon];
}

Pokemon & Player::GetPokemon(int index_in) const
{
	return *m_Pokemons[index_in];
}

const char* Player::GetName() const
{
	return m_Name;
}

bool Player::HasNotLost() const
{
	for (int i = 0; i < m_NumPokemons; i++)
	{
		if (!m_Pokemons[i]->IsDead())
		{
			return true;
		}
	}
	return false;
}

int Player::GetNumPokemons() const
{
	return m_NumPokemons;
}

bool Player::GetHasAttacked() const
{
	return m_HasAttacked;
}

void Player::SetHasAttacked(bool attacked_in)
{
	m_HasAttacked = attacked_in;
}

