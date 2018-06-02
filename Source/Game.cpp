//
// Created by sheepy on 4/25/18.
//

#include "Game.h"
#include <chrono>

using namespace SheepyEngine;
namespace Game
{
	namespace
	{
		//Internals
		
		//Internal fields

		static const int FPS = 60;
		inline static const double MS_PER_UPDATE = 100.0 / FPS;
		std::vector<std::shared_ptr<GameObject>> OBJECTS;

		//Internal methods

		std::chrono::high_resolution_clock::time_point GetCurrentTime() {
			return std::chrono::high_resolution_clock::now();
		}

		void Initialize() {

		}

		//Game loop methods

		void Update() {
			for (auto& object : OBJECTS) {
				object->update();
			}
		}

		void Draw(long frameRatio) {
			for (const auto& object : OBJECTS) {
				object->draw(frameRatio);
			}
		}
		cimg_library::CImgDisplay MAIN_CANVAS{};
	}

	// Game API

	void Create() {
		Initialize();

		auto previous = GetCurrentTime();
		auto lag = 0.0;
		while (true) {
			const auto current = GetCurrentTime();
			const auto sinceLast = current - previous;
			auto deltaTime = (std::chrono::duration_cast<std::chrono::nanoseconds>(sinceLast)) / 1000.0;

			previous = current;
			lag += deltaTime.count();

			while (lag >= MS_PER_UPDATE)
			{
				Update();

				// Clamp lag to be min 0
				lag -= MS_PER_UPDATE == 0 ? 0 : lag;
			}

			Draw(static_cast<const long>(lag / MS_PER_UPDATE));
		}
	}

	void Delete() {
	}

	void AddGameObject(std::unique_ptr<GameObject> object) {
		OBJECTS.push_back(std::move(object));
	}
}

#ifndef _DEBUG
int main() {
	Game game{};
	return 0;
}
#endif // _DEBUG