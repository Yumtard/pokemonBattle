#pragma once

#include "Player.h"
#include "Move.h"
#include <map>
#include <string>
#include <random>

class BattleManager
{
public:
	BattleManager();
	void Update();
	void GetUserInput();

private:
	enum ActivePlayer
	{
		player1, player2
	};
	enum BattleState
	{
		menu, battling, choosingPokemon, choosingMove
	};

private:
	ActivePlayer activePlayer = player1;
	BattleState state = menu;
	Player *players[2];
	std::map<std::string, Move*>  moves;
	int userInput;
	std::string curMove;
};