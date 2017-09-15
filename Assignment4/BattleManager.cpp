#include "BattleManager.h"

BattleManager::BattleManager()
{
	{
		std::ifstream in("damaging.txt");
		int dmg;
		std::string name;

		while (in.good())
		{
			in >> name >> dmg;
			m_Moves[name] = new DamagingMove(name, dmg);
		}
	}

	{
		std::ifstream in("absorbing.txt");
		int dmg;
		std::string name;

		while (in.good())
		{
			in >> name >> dmg;
			m_Moves[name] = new AbsorbingMove(name, dmg);
		}
	}

	{
		m_Player = new Player("Ash");
		std::ifstream in("player1pokemons.txt");
		int hp;
		std::string name, att1, att2, att3, att4;

		while (in.good())
		{
			in >> name >> att1 >> att2 >> att3 >> att4 >> hp;
			m_Pokemons[name] = new Pokemon(name, hp);
			m_Pokemons[name]->AddMove(att1);
			m_Pokemons[name]->AddMove(att2);
			m_Pokemons[name]->AddMove(att3);
			m_Pokemons[name]->AddMove(att4);
			m_Player->AddPokemon(m_Pokemons[name]);
		}
	}

	{
		m_AI = new Player("Gary");
		std::ifstream in("player2pokemons.txt");
		int hp;
		std::string name, att1, att2, att3, att4;

		while (in.good())
		{
			in >> name >> att1 >> att2 >> att3 >> att4 >> hp;
			m_Pokemons[name] = new Pokemon(name, hp);
			m_Pokemons[name]->AddMove(att1);
			m_Pokemons[name]->AddMove(att2);
			m_Pokemons[name]->AddMove(att3);
			m_Pokemons[name]->AddMove(att4);
			m_AI->AddPokemon(m_Pokemons[name]);
		}
	}
}

BattleManager::~BattleManager()
{
	delete m_Player;
	delete m_AI;

	std::map<std::string, Move*>::iterator it = m_Moves.begin();
	for (; it != m_Moves.end(); it++)
	{
		if (it != m_Moves.end())
		{
			delete it->second;
			it->second = nullptr;
		}
	}
}

void BattleManager::Update()
{
	std::cout << m_Player->GetName() << ": GO! " << m_Player->GetCurPokemon().GetName() << "!" << std::endl;
	std::cout << m_AI->GetName() << ": GO! " << m_AI->GetCurPokemon().GetName() << "!\n" << std::endl;

	while(m_Player->HasNotLost() && m_AI->HasNotLost())
	{
		switch (m_State)
		{
		case menu:
		{
			std::cout << "(1) Moves" << std::endl;
			std::cout << "(2) Pokemons\n" << std::endl;
		}

		break;

		case choosingPokemon:
		{
			std::cout << "Choose a pokemon" << std::endl;
			m_Player->ViewPokemons();
		}

		break;

		case choosingMove:
		{
			Pokemon& curPokemon = m_Player->GetCurPokemon();
			std::cout << "Choose move" << std::endl;
			curPokemon.DisplayMoves();
		}

		break;

		case battling:
		
			Battle(m_Player, m_AI);
			Battle(m_AI, m_Player);

		break;
		}

		HandleUserInput();
		ProcessAI();
		HandleStates();
	}	

	if (m_Player->HasNotLost())
	{
		std::cout << m_Player->GetName() << " has defeated " << m_AI->GetName() << "!!" << std::endl;
	}
	else
	{
		std::cout << m_AI->GetName() << " has defeated " << m_Player->GetName() << "!!" << std::endl;
	}
}

void BattleManager::HandleUserInput()
{
	{
		switch (m_State)
		{
		case menu:
		{
			int menuChoice;

			do
			{
				std::cin >> menuChoice;
			} while (menuChoice < 1 || menuChoice > 2);

			m_UserInput = menuChoice;
		}

		break;

		case choosingMove:
		{
			const int numMoves = m_Player->GetCurPokemon().GetNumMoves();
			int moveChoice;

			do
			{
				std::cin >> moveChoice;
			} while (moveChoice < 0 || moveChoice >(numMoves - 1));

			m_Player->GetCurPokemon().SetNextMove(moveChoice);
		}

		break;

		case choosingPokemon:
		{
			const int numPokemons = m_Player->GetNumPokemons();
			int pokemonChoice;

			do
			{
				std::cin >> pokemonChoice;
			} while ((pokemonChoice < 0 || pokemonChoice >= numPokemons) || m_Player->GetPokemon(pokemonChoice).IsDead());

			if (!m_Player->SwitchPokemon(pokemonChoice))
			{
				m_ForcedSwitch = true;
			}
		}

		break;
		}
	}
}

void BattleManager::ProcessAI()
{
	if (m_AI->HasNotLost())
	{
		std::mt19937 rng(std::random_device{}());

		if (m_AI->GetCurPokemon().IsDead())
		{
			const int numPokemons = m_AI->GetNumPokemons();
			std::uniform_int_distribution<int> pokemonDist(0, numPokemons - 1);
			int pokemonChoice;

			do
			{
				pokemonChoice = pokemonDist(rng);
			} while ((pokemonChoice < 0 && pokemonChoice >= numPokemons) || m_AI->GetPokemon(pokemonChoice).IsDead());

			m_AI->SwitchPokemon(pokemonChoice);
		}

		const int numMoves = m_AI->GetCurPokemon().GetNumMoves();
		std::uniform_int_distribution<int> moveDist(0, numMoves - 1);
		int moveChoice;

		do
		{
			moveChoice = moveDist(rng);
		} while (moveChoice < 0 && moveChoice >(numMoves - 1));

		m_AI->GetCurPokemon().SetNextMove(moveChoice);
	}
}

void BattleManager::Battle(Player * attacker_in, Player * target_in)
{
	if (!attacker_in->GetHasAttacked() && !attacker_in->GetCurPokemon().IsDead())
	{
		Pokemon& attacker = attacker_in->GetCurPokemon();
		Pokemon& target = target_in->GetCurPokemon();
		m_CurMove = attacker.GetMove();

		std::cout << attacker.GetName() << " used " << m_CurMove << std::endl;
		m_Moves[m_CurMove]->Use(attacker, target);
		std::cout << target.GetName() << " took " << m_Moves[m_CurMove]->GetDamage() << " damage." << std::endl;
		std::cout << target.GetName() << " has " << target.GetHP() << " HP left.\n" << std::endl;

		attacker_in->SetHasAttacked(true);

		if (target.IsDead())
		{
			std::cout << target.GetName() << " fainted...\n\n";
		}
	}
}

void BattleManager::HandleStates()
{
	if (m_Player->GetCurPokemon().IsDead())
	{
		m_ForcedSwitch = true;
		m_State = choosingPokemon;
		return;
	}

	if (m_Player->GetHasAttacked() && m_AI->GetHasAttacked())
	{
		m_State = menu;
		m_Player->SetHasAttacked(false);
		m_AI->SetHasAttacked(false);
		return;
	}

	if (m_State == menu)
	{
		if (m_UserInput == 1)
		{
			m_State = choosingMove;
		}
		else if(m_UserInput == 2)
		{
			m_State = choosingPokemon;
		}
		return;
	}

	if (m_State == choosingMove)
	{
		m_State = battling;
		return;
	}

	if (m_State == choosingPokemon)
	{
		if (m_ForcedSwitch)
		{
			m_State = menu;
			m_ForcedSwitch = false;
			return;
		}
		else
		{
			m_Player->SetHasAttacked(true);
			m_State = battling;
			return;
		}
	}
}

