#include "GameLoopTestGameObject.h"



GameLoopTestGameObject::GameLoopTestGameObject()
{
}


GameLoopTestGameObject::~GameLoopTestGameObject()
{
}

void GameLoopTestGameObject::update()
{
	numberOfUpdateCalls++;
}

int GameLoopTestGameObject::getNumberOfUpdateCalls()
{
	return numberOfUpdateCalls;
}
