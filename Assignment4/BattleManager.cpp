#include "BattleManager.h"

void BattleManager::Update()
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

	moves[tackle] = new DamagingMove(tackle, 10);
	moves[leechLife] = new AbsorbingMove(leechLife, 8);
	moves[thunderShock] = new DamagingMove(thunderShock, 12);
	moves[fireBlast] = new DamagingMove(fireBlast, 15);
	moves[ember] = new DamagingMove(ember, 10);
	moves[waterGun] = new DamagingMove(waterGun, 10);
	moves[slam] = new DamagingMove(slam, 12);
	moves[quickAttack] = new DamagingMove(quickAttack, 10);
	moves[scratch] = new DamagingMove(scratch, 12);

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

	players[0] = new Player("Ash");
	players[0]->AddPokemon(pikachu);
	players[0]->AddPokemon(charmander);

	players[1] = new Player("Gary");
	players[1]->AddPokemon(bulbasaur);
	players[1]->AddPokemon(squirtle);
	
	std::cout << players[0]->GetName() << ": GO! " << players[0]->GetPokemon().GetName() << "!" << std::endl;
	std::cout << players[1]->GetName() << ": GO! " << players[1]->GetPokemon().GetName() << "!\n" << std::endl;

	while(!players[activePlayer]->HasLost() && !players[1 - activePlayer]->HasLost())
	{
		if (players[activePlayer]->GetPokemon().IsDead())
		{
			state = choosingPokemon;
			break;
		}

		switch (state)
		{
		case menu:
			std::cout << "(1) Moves" << std::endl;
			std::cout << "(2) Pokemons\n" << std::endl;

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

			std::cout << players[activePlayer]->GetName() << " chose " << players[activePlayer]->GetPokemon().GetName() << std::endl;

			state = menu;

			break;

		case choosingMove:
			std::cout << "Choose move" << std::endl;
			players[activePlayer]->GetPokemon().DisplayMoves();

			GetUserInput();

			curMove = players[activePlayer]->GetPokemon().GetMove(userInput);

			std::cout << players[activePlayer]->GetName() << " chose " << curMove << std::endl;

			state = battling;

			break;
		case battling:
			Pokemon& attacker = players[activePlayer]->GetPokemon();
			Pokemon& target = players[1 - activePlayer]->GetPokemon();

			moves[curMove]->Use(attacker, target);
			std::cout << attacker.GetName() << " used " << curMove << std::endl;
			std::cout << target.GetName() << " took " << moves[curMove]->GetDamage() << " damage." << std::endl;
			std::cout << target.GetName() << " has " << target.GetHP() << " HP left.\n" << std::endl;

			if (activePlayer == player1)
			{
				activePlayer = player2;
			}
			else
			{
				activePlayer = player1;
			}

			state = menu;

			break;
		}
	}
}

void BattleManager::GetUserInput()
{
	const int numPokemons = players[activePlayer]->GetNumPokemons();
	const int numMoves = players[activePlayer]->GetPokemon().GetNumMoves();

	std::mt19937 rng(std::random_device {}());
	bool invalidInput = true;

	std::uniform_int_distribution<int> menuDist(1, 2);
	const int menuChoice = menuDist(rng);

	std::uniform_int_distribution<int> moveDist(0, numMoves - 1);
	const int moveChoice = moveDist(rng);

	std::uniform_int_distribution<int> pokemonDist(0, numPokemons - 1);
	const int pokemonChoice = pokemonDist(rng);

	while (invalidInput)
	{
		switch (state)
		{
		case menu:
			if (menuChoice > 0 && menuChoice < 3)
			{
				invalidInput = false;
				userInput = menuChoice;
			}

			break;

		case choosingMove:
			if (moveChoice >= 0 && moveChoice < numMoves)
			{
				invalidInput = false;
				userInput = moveChoice;
			}

			break;

		case choosingPokemon:
			if (pokemonChoice >= 0 && pokemonChoice < numPokemons)
			{
				invalidInput = false;
				userInput = pokemonChoice;
			}

			break;
		}
	}
}
