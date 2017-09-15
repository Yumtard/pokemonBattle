#include "Pokemon.h"

Pokemon::Pokemon(const std::string& name_in, int hp_in)
	:
	m_Name(name_in),
	m_hp(hp_in),
	m_NumMoves(0)
{}

const std::string& Pokemon::GetName() const
{
	return m_Name;
}

void Pokemon::DisplayMoves() const
{
	for (int i = 0; i < m_NumMoves; i++)
	{
		std::cout << "(" << i << ") " << m_AvailableMoves[i] << std::endl;
	}
	std::cout << "\n";
}

void Pokemon::TakeDamage(int damage_in)
{
	m_hp -= std::min(damage_in, m_hp);
}

const std::string & Pokemon::GetInfo()
{
	std::string moves;
	for (int i = 0; i < m_NumMoves; i++)
	{
		moves += m_AvailableMoves[i] + ", ";
	}
	std::string stringName(m_Name);
	m_Info = stringName + ", HP: " + std::to_string(m_hp) + ", Moves: " + moves;
	return m_Info;
}

void Pokemon::AddMove(const std::string& move_in)
{
	if (m_NumMoves < m_NumMovesMax)
	{
		m_AvailableMoves[m_NumMoves] = move_in;
		m_NumMoves++;
	}
}

const std::string& Pokemon::GetMove() const
{
	return m_AvailableMoves[m_NextMove];
}

bool Pokemon::IsDead() const
{
	return m_hp == 0;
}

int Pokemon::GetNumMoves() const
{
	return m_NumMoves;
}

int Pokemon::GetHP() const
{
	return m_hp;
}

void Pokemon::SetNextMove(int nextMove_in)
{
	m_NextMove = nextMove_in;
}
