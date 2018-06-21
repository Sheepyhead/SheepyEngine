#include "test.h"
#include <Game.h>



SCENARIO("The game loop is executed", "[Game]")
{
	using namespace SheepyEngine;

	GIVEN("A running game")
	{
		Game::Create();

		REQUIRE(Game::IsRunning());
	}

	Game::Delete();
}