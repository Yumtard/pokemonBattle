#pragma once

#include "Player.h"
#include "Move.h"
#include "DamagingMove.h"
#include "AbsorbingMove.h"
#include "Pokemon.h"
#include <map>
#include <string>
#include <random>

class BattleManager
{
public:
	BattleManager() = default;
	void Update();
	void GetUserInput();
	void ChangeActivePlayer();

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