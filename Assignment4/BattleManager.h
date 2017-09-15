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
	void HandleUserInput();
	void ProcessAI(); //user and ai.....
	void Battle(Player* attacker_in, Player* target_in);

private:
	enum BattleState
	{
		menu, battling, choosingPokemon, choosingMove
	};

private:
	BattleState m_State = menu;
	Player* m_Player;
	Player* m_AI;
	std::map<std::string, Move*> m_Moves;
	int m_UserInput;
	std::string m_CurMove;
	bool m_ForcedSwitch = false;
};