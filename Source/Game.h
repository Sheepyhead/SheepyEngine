//
// Created by sheepy on 4/25/18.
//
#pragma once 

#include <iostream>
#include <cstdio>
#include <CImg.h>
#include <chrono>
#include <vector>
#include <memory>
#include "GameObject.h"

namespace SheepyEngine
{
	namespace Game {
		// Game API
		void Create();
		void Delete();
		
		static void AddGameObject(std::unique_ptr<GameObject> object);
	};
}
