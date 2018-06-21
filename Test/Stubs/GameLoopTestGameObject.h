#pragma once

#include <GameObject.h>

using namespace SheepyEngine;

class GameLoopTestGameObject : public GameObject
{
public:
	GameLoopTestGameObject();
	~GameLoopTestGameObject();

	void update() override;
	const void draw(long frameRatio) const override;
	int getNumberOfUpdateCalls();
	int getNumberOfDrawCalls();
private:
	int numberOfUpdateCalls = 0;
};