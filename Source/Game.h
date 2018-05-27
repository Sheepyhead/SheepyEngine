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
	class Game {
	public:
		Game();
		~Game();

		// Game API
		
		static void addGameObject(std::unique_ptr<GameObject> object);

	private:
		//Internal methods

		static std::chrono::high_resolution_clock::time_point getCurrentTime();
		static void initialize();

		// Game loop methods
		
		static void update();
		static void draw(long frameRatio);


		static const int _FPS = 60;
		inline static const double _MS_PER_UPDATE = 100.0 / _FPS;
		static std::vector<std::unique_ptr<GameObject>> _OBJECTS;

	};

	extern cimg_library::CImgDisplay MAIN_CANVAS;

}
