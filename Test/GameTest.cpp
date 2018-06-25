#include "test.h"
#include <Game.h>
#include "Stubs/GameLoopTestGameObject.h"
#include "trompeloeil.hpp"

extern template struct trompeloeil::reporter<trompeloeil::specialized>;

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


			THEN("The game object is updated more than once") {
				auto numberOfUpdateCalls = gameObject->getNumberOfUpdateCalls();
				WARN("Number of update calls: " << numberOfUpdateCalls);
				REQUIRE(numberOfUpdateCalls > 1);
			}

			THEN("The game object is drawn more than once") {
				auto numberOfDrawCalls = gameObject->getNumberOfDrawCalls();
				WARN("Number of draw calls: " << numberOfDrawCalls);
				REQUIRE(numberOfDrawCalls > 1);
			}
		}
	}

	Game::Delete();
}