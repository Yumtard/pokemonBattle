#include "BattleManager.h"

void BattleManager::Update()
{
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

			while (true)
			{
				GetUserInput();

				if (userInput == 1)
				{
					state = choosingMove;
					break;
				}
				else if (userInput == 2)
				{
					state = choosingPokemon;
				}
				else
				{
					std::cout << "Invalid choice" << std::endl; //detta kan göras i getuserinput
					continue;
				}
			}

			break;
		case choosingPokemon:
			std::cout << "Choose a pokemon" << std::endl;
			//display pokemons

			while (true)
			{
				GetUserInput();
				if (userInput >= 0 && userInput <= 5) //less than numpokemons
				{
					//set curpokemon to daaat
					state = menu;
					break;
				}
				else
				{
					continue;
				}
			}

			break;
		case choosingMove:
			std::cout << "Choose move" << std::endl;
			//display moves

			while (true)
			{
				GetUserInput();
				if (userInput >= 0 && userInput <= 3) //less than num available moves
				{
					//set  cur move by getting string from pokemon
					state = battling;
					break;
				}
				else
				{
					continue;
				}
			}

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
