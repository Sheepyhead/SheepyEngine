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

namespace {
	auto numberOfDrawCalls = 0;
}

const void GameLoopTestGameObject::draw(long frameRatio) const
{
	numberOfDrawCalls++;
}

int GameLoopTestGameObject::getNumberOfUpdateCalls()
{
	return numberOfUpdateCalls;
}

int GameLoopTestGameObject::getNumberOfDrawCalls()
{
	return numberOfDrawCalls;
}
