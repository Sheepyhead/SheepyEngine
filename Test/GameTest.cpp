#include "test.h"
#include <Game.h>
#include "Stubs/GameLoopTestGameObject.h"



SCENARIO("The game loop is executed", "[Game]")
{
	using namespace SheepyEngine;

	GIVEN("A running game")
	{
		Game::Create();

		REQUIRE(Game::IsRunning());

		WHEN("Adding a game object to the running game and letting it run for a second") 
		{
			auto gameObject = std::make_shared<GameLoopTestGameObject>();

			Game::AddGameObject(gameObject);

			Sleep(1000);

			THEN("The game object is updated") {
				auto numberOfUpdateCalls = gameObject->getNumberOfUpdateCalls();
				REQUIRE(numberOfUpdateCalls > 0);

				THEN("The game object is updated more than once") {
					INFO("Number of update calls: " << numberOfUpdateCalls);
					REQUIRE(numberOfUpdateCalls > 1);
				}
			}
		}
	}

	Game::Delete();
}