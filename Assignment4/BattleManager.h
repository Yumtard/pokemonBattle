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
	BattleManager();
	~BattleManager();
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
	ActivePlayer m_ActivePlayer = player1;
	BattleState m_State = menu;
	Player *m_Players[2];
	std::map<std::string, Move*> m_Moves;
	int m_UserInput;
	std::string m_CurMove;
	int numMovesLoaded;
};