#pragma once

#include <string>
#include <iostream>
#include <algorithm>

class Pokemon
{
public:
	Pokemon(const std::string& name_in, int hp_in);
	const std::string& GetName() const;
	void DisplayMoves() const;
	void TakeDamage(int damage_in);
	const std::string& GetInfo();
	void AddMove(const std::string& move_in);
	const std::string& GetMove() const; 
	bool IsDead() const;
	int GetNumMoves() const;
	int GetHP() const;
	void SetNextMove(int nextMove_in);

private:
	std::string m_Name;
	int m_hp;
	int m_NumMoves;
	static constexpr int m_NumMovesMax = 4;
	std::string m_AvailableMoves[m_NumMovesMax];
	std::string m_Info;
	int m_NextMove;
};