#pragma once

#include <GameObject.h>

using namespace SheepyEngine;

class GameLoopTestGameObject : public GameObject
{
public:
	GameLoopTestGameObject();
	~GameLoopTestGameObject();

	void update() override;
	int getNumberOfUpdateCalls();
private:
	int numberOfUpdateCalls = 0;
};