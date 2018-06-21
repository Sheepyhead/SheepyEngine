//
// Created by sheepy on 4/26/18.
//
#pragma once

#include <vector>

namespace SheepyEngine
{
/// GameObject - Represents an object in the game world.
class GameObject {
public:
	virtual void update();

	const virtual void draw(long frameRatio) const;
};
}
