#include "BattleManager.h"

BattleManager::BattleManager()
{
	char* tackle = "Tackle";
	char* leechLife = "Leech Life";
	char* thunderShock = "Thunder Shock";
	char* fireBlast = "Fire Blast";
	char* ember = "Ember";
	char* waterGun = "Water Gun";
	char* slam = "Slam";
	char* quickAttack = "Quick Attack";
	char* scratch = "Scratch";

	m_Moves[tackle] = new DamagingMove(tackle, 10);
	m_Moves[leechLife] = new AbsorbingMove(leechLife, 8);
	m_Moves[thunderShock] = new DamagingMove(thunderShock, 12);
	m_Moves[fireBlast] = new DamagingMove(fireBlast, 15);
	m_Moves[ember] = new DamagingMove(ember, 10);
	m_Moves[waterGun] = new DamagingMove(waterGun, 10);
	m_Moves[slam] = new DamagingMove(slam, 12);
	m_Moves[quickAttack] = new DamagingMove(quickAttack, 10);
	m_Moves[scratch] = new DamagingMove(scratch, 12);

	char* pikachuName = "Pikachu";
	char* charmanderName = "Charmander";
	char* bulbasaurName = "Bulbasaur";
	char* squirtleName = "Squirtle";
	Pokemon* pikachu = new Pokemon(pikachuName, 10);
	Pokemon* charmander = new Pokemon(charmanderName, 10);
	Pokemon* bulbasaur = new Pokemon(bulbasaurName, 10);
	Pokemon* squirtle = new Pokemon(squirtleName, 10);

	pikachu->AddMove(tackle);
	pikachu->AddMove(thunderShock);
	pikachu->AddMove(slam);
	pikachu->AddMove(quickAttack);

	charmander->AddMove(tackle);
	charmander->AddMove(scratch);
	charmander->AddMove(ember);
	charmander->AddMove(fireBlast);

	bulbasaur->AddMove(tackle);
	bulbasaur->AddMove(leechLife);
	bulbasaur->AddMove(slam);
	bulbasaur->AddMove(scratch);

	squirtle->AddMove(tackle);
	squirtle->AddMove(scratch);
	squirtle->AddMove(waterGun);
	squirtle->AddMove(slam);

	m_Player = new Player("Ash", false);
	m_Player->AddPokemon(pikachu);
	m_Player->AddPokemon(charmander);

	m_AI = new Player("Gary", true);
	m_AI->AddPokemon(bulbasaur);
	m_AI->AddPokemon(squirtle);
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
		if (m_Player->GetHasAttacked() && m_AI->GetHasAttacked())
		{
			m_State = menu;
			m_Player->SetHasAttacked(false);
			m_AI->SetHasAttacked(false);
		}

		if (m_Player->GetCurPokemon().IsDead())
		{
			m_ForcedSwitch = true;
			m_State = choosingPokemon;
		}

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

			if (menuChoice == 1)
			{
				m_State = choosingMove;
			}
			else
			{
				m_State = choosingPokemon;
			}
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
			m_State = battling;
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

			if (m_Player->SwitchPokemon(pokemonChoice))
			{
				if (m_ForcedSwitch)
				{
					m_State = menu;
					m_ForcedSwitch = false;
				}
				else
				{
					m_Player->SetHasAttacked(true);
					m_State = battling;
				}
			}
			else
			{
				m_State = menu;
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

