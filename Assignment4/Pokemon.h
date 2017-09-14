#pragma once

#include <string>
#include <iostream>
#include <algorithm>

class Pokemon
{
public:
	Pokemon(char* name_in, int hp_in);
	const char* GetName() const;
	void DisplayMoves() const;
	void TakeDamage(int damage_in);
	const std::string& GetInfo();
	void AddMove(const std::string& move_in);
	const std::string& GetMove(int choice) const;
	bool IsDead() const;
	int GetNumMoves() const;
	int GetHP() const;

private:
	char* name;
	int hp;
	int numMoves;
	static constexpr int numMovesMax = 4;
	std::string availableMoves[numMovesMax];
	std::string info;
};