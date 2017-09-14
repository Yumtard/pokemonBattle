#include "BattleManager.h"

void BattleManager::Update()
{
	//create moves
	// create pokemons
	//give pokemons moves
	//create players
	//give players pokemons

	moves["Tackle"] = new DamagingMove("Tackle", 10);
	moves["Leech Life"] = new AbsorbingMove("Leech Life", 8);
	moves["Thunder Shock"] = new DamagingMove("Thunder Shock", 12);
	moves["Fire Blast"] = new DamagingMove("Fire Blast", 15);
	moves["Ember"] = new DamagingMove("Ember", 10);
	moves["Water Gun"] = new DamagingMove("Water Gun", 10);
	moves["Slam"] = new DamagingMove("Slam", 12);
	moves["Quick Attack"] = new DamagingMove("Quick Attack", 10);
	moves["Scratch"] = new DamagingMove("Scratch", 12);

	Pokemon* pikachu = new Pokemon("Pikachu", 20);
	Pokemon* charmander = new Pokemon("Charmander", 20);
	Pokemon* bulbasaur = new Pokemon("Bulbasaur", 20);
	Pokemon* squirtle = new Pokemon("Squirtle", 20);

	pikachu->AddMove("Tackle");
	pikachu->AddMove("Thunder Shock");
	pikachu->AddMove("Slam");
	pikachu->AddMove("Quick Attack");

	charmander->AddMove("Tackle");
	charmander->AddMove("Scratch");
	charmander->AddMove("Ember");
	charmander->AddMove("Fire Blast");

	bulbasaur->AddMove("Tackle");
	bulbasaur->AddMove("Leech Life");
	bulbasaur->AddMove("Slam");
	bulbasaur->AddMove("Scratch");

	squirtle->AddMove("Tackle");
	squirtle->AddMove("Scratch");
	squirtle->AddMove("Water Gun");
	squirtle->AddMove("Scratch");

	players[0] = new Player("Ash");
	players[0]->AddPokemon(pikachu);
	players[0]->AddPokemon(charmander);

	players[1] = new Player("Gary");
	players[1]->AddPokemon(bulbasaur);
	players[1]->AddPokemon(squirtle);
	

	while(!players[activePlayer]->HasLost() || !players[1 - activePlayer]->HasLost())
	{
		switch (state)
		{
		case menu:
			if ((players[activePlayer]->GetPokemon().IsDead()))
			{
				state = choosingPokemon;
				break;
			}
			
			std::cout << "Current Pokemon: " << players[activePlayer]->GetPokemon().GetName() << std::endl;
			std::cout << "(1) Moves" << std::endl;
			std::cout << "(2) Pokemons";

			GetUserInput();

			if (userInput == 1)
			{
				state = choosingMove;
				break;
			}
			else if (userInput == 2)
			{
				state = choosingPokemon;
				break;
			}			

			break;

		case choosingPokemon:
			std::cout << "Choose a pokemon" << std::endl;
			players[activePlayer]->ViewPokemons();

			GetUserInput();

			players[activePlayer]->SwitchPokemon(userInput);

			state = menu;

			break;

		case choosingMove:
			std::cout << "Choose move" << std::endl;
			players[activePlayer]->GetPokemon().DisplayMoves();

			GetUserInput();

			curMove = players[activePlayer]->GetPokemon().GetMove(userInput);

			state = battling;

			break;
		case battling:
			Pokemon& attacker = players[activePlayer]->GetPokemon();
			Pokemon& target = players[1 - activePlayer]->GetPokemon();

			moves[curMove]->Use(attacker, target);
			std::cout << attacker.GetName() << " used " << curMove << std::endl;
			std::cout << target.GetName() << " took " << moves[curMove]->GetDamage() << " damage." << std::endl;

			if (activePlayer == player1)
			{
				activePlayer = player2;
			}
			else
			{
				activePlayer = player1;
			}

			break;
		}
	}
}

void BattleManager::GetUserInput()
{
	std::mt19937 rng(std::random_device rd());
	bool invalidInput = true;

	while (invalidInput)
	{
		switch (state)
		{
		case menu:
			std::uniform_int_distribution<int> dist(1, 2);
			const int choice = dist(rng);

			if (choice > 0 && choice < 3)
			{
				invalidInput = false;
				std::cout << "You chose " << choice << std::endl;
				userInput = choice;
			}

			break;

		case choosingMove:
			const int numMoves = players[activePlayer]->GetPokemon().GetNumMoves();
			std::uniform_int_distribution<int> dist(0, numMoves - 1);
			const int choice = dist(rng);

			if (choice >= 0 && choice < numMoves)
			{
				invalidInput = false;
				std::cout << "You chose " << choice << std::endl;
				userInput = choice;
			}

			break;

		case choosingPokemon:
			const int numPokemons = players[activePlayer]->GetNumPokemons();
			std::uniform_int_distribution<int> dist(0, numPokemons - 1);
			const int choice = dist(rng);

			if (choice >= 0 && choice < numPokemons)
			{
				invalidInput = false;
				std::cout << "You chose " << choice << std::endl;
				userInput = choice;
			}

			break;
		}
	}
}
