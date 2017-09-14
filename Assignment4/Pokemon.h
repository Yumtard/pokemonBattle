#pragma once

#include <string>
#include <iostream>

class Pokemon
{
public:
	Pokemon(std::string name_in, int hp_in);
	const std::string& GetName() const;
	void DisplayMoves() const;
	void TakeDamage(int damage_in);
	const std::string& GetInfo() const;
	void AddMove(const std::string& move_in);
	const std::string& GetMove(int choice) const;
	bool IsDead() const;

private:
	std::string name;
	int hp;
	int numMoves;
	static constexpr int numMovesMax = 4;
	std::string availAbleMoves[numMovesMax];
};