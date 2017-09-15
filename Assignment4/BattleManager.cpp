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
	Pokemon* pikachu = new Pokemon(pikachuName, 20);
	Pokemon* charmander = new Pokemon(charmanderName, 20);
	Pokemon* bulbasaur = new Pokemon(bulbasaurName, 20);
	Pokemon* squirtle = new Pokemon(squirtleName, 20);

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

	m_Players[0] = new Player("Ash", false);
	m_Players[0]->AddPokemon(pikachu);
	m_Players[0]->AddPokemon(charmander);

	m_Players[1] = new Player("Gary", false);
	m_Players[1]->AddPokemon(bulbasaur);
	m_Players[1]->AddPokemon(squirtle);
}

BattleManager::~BattleManager()
{
	delete m_Players[0];
	delete m_Players[1];

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
	std::cout << m_Players[0]->GetName() << ": GO! " << m_Players[0]->GetCurPokemon().GetName() << "!" << std::endl;
	std::cout << m_Players[1]->GetName() << ": GO! " << m_Players[1]->GetCurPokemon().GetName() << "!\n" << std::endl;

	while(m_Players[m_ActivePlayer]->HasNotLost() && m_Players[1 - m_ActivePlayer]->HasNotLost())
	{
		if (m_Players[m_ActivePlayer]->GetCurPokemon().IsDead())
		{
			m_State = choosingPokemon;
		}

		switch (m_State)
		{
		case menu:
		{
			std::cout << "(1) Moves" << std::endl;
			std::cout << "(2) Pokemons\n" << std::endl;

			GetUserInput();

			if (m_UserInput == 1)
			{
				m_State = choosingMove;
				break;
			}
			else if (m_UserInput == 2)
			{
				m_State = choosingPokemon;
				break;
			}
		}	

		break;

		case choosingPokemon:
		{
			std::cout << "Choose a pokemon" << std::endl;
			m_Players[m_ActivePlayer]->ViewPokemons();

			GetUserInput();

			if (m_Players[m_ActivePlayer]->SwitchPokemon(m_UserInput))
			{
				ChangeActivePlayer();
			}

			m_State = menu;
		}

		break;

		case choosingMove:
		{
			Pokemon& curPokemon = m_Players[m_ActivePlayer]->GetCurPokemon();
			std::cout << "Choose move" << std::endl;
			curPokemon.DisplayMoves();

			GetUserInput();

			m_CurMove = curPokemon.GetMove(m_UserInput);

			std::cout << m_Players[m_ActivePlayer]->GetName() << " chose " << m_CurMove << std::endl;

			m_State = battling;
		}
			
		break;

		case battling:
		{
			Pokemon& attacker = m_Players[m_ActivePlayer]->GetCurPokemon();

			if (!attacker.IsDead())
			{
				Pokemon& target = m_Players[1 - m_ActivePlayer]->GetCurPokemon();

				m_Moves[m_CurMove]->Use(attacker, target);
				std::cout << attacker.GetName() << " used " << m_CurMove << std::endl;
				std::cout << target.GetName() << " took " << m_Moves[m_CurMove]->GetDamage() << " damage." << std::endl;
				std::cout << target.GetName() << " has " << target.GetHP() << " HP left.\n" << std::endl;

				ChangeActivePlayer();

				m_State = menu;
			}
			else
			{
				std::cout << attacker.GetName() << " fainted...\n\n";
				m_State = choosingPokemon;
			}
		}

		break;
		}
	}
}

void BattleManager::GetUserInput()
{
	std::mt19937 rng(std::random_device {}());
	
	switch (m_State)
	{
	case menu:
	{
		std::uniform_int_distribution<int> menuDist(1, 2);
		int menuChoice;

		do
		{
			menuChoice = menuDist(rng);
		} while (menuChoice < 1 && menuChoice > 2);

		m_UserInput = menuChoice;
	}
		
	break;

	case choosingMove:
	{
		const int numMoves = m_Players[m_ActivePlayer]->GetCurPokemon().GetNumMoves();
		std::uniform_int_distribution<int> moveDist(0, numMoves - 1);
		int moveChoice;

		do
		{
			moveChoice = moveDist(rng);
		} while (moveChoice < 0 && moveChoice >(numMoves - 1));

		m_UserInput = moveChoice;
	}
			
	break;

	case choosingPokemon:
	{
		const int numPokemons = m_Players[m_ActivePlayer]->GetNumPokemons();
		std::uniform_int_distribution<int> pokemonDist(0, numPokemons - 1);
		int pokemonChoice;

		do
		{
			pokemonChoice = pokemonDist(rng);
		} while ((pokemonChoice < 0 && pokemonChoice >= numPokemons) || m_Players[m_ActivePlayer]->GetPokemon(pokemonChoice).IsDead());

		m_UserInput = pokemonChoice;
	}
	
	break;
	}
}

void BattleManager::ChangeActivePlayer()
{
	if (m_ActivePlayer == player1)
	{
		m_ActivePlayer = player2;
	}
	else
	{
		m_ActivePlayer = player1;
	}

	std::cout << m_Players[m_ActivePlayer]->GetName() << "s turn...\n" << std::endl;
}

void BattleManager::GetInput()
{
}

