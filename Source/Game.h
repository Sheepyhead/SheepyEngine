//
// Created by sheepy on 4/25/18.
//
#pragma once 

#include <memory>
#include "GameObject.h"

namespace SheepyEngine
{
namespace Game {

// Game API

void Create();
void Delete();
bool IsRunning();

void AddGameObject(const std::shared_ptr<GameObject>& object);
};
}
