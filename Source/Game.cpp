//
// Created by sheepy on 4/25/18.
//

#include "Game.h"
#include <chrono>

using namespace SheepyEngine;

Game::Game() {
	initialize();

	auto previous = getCurrentTime();
	auto lag = 0.0;
	while (true) {
		const auto current = getCurrentTime();
		const auto sinceLast = current - previous;
		auto deltaTime = (std::chrono::duration_cast<std::chrono::nanoseconds>(sinceLast)) / 1000.0;

		previous = current;
		lag += deltaTime.count();

		while (lag >= _MS_PER_UPDATE)
		{
			update();

			// Clamp lag to be min 0
			lag -= _MS_PER_UPDATE == 0 ? 0 : lag;
		}

		draw(static_cast<const long>(lag / _MS_PER_UPDATE));
	}
}

Game::~Game() {
}

std::chrono::high_resolution_clock::time_point Game::getCurrentTime() {
	return std::chrono::high_resolution_clock::now();
}

void Game::update() {
	for (auto& object : _OBJECTS) {
		object->update();
	}
}

void Game::draw(long frameRatio) {
	for (const auto& object : _OBJECTS) {
		object->draw(frameRatio);
	}
}

void Game::initialize() {

}

void Game::addGameObject(std::unique_ptr<GameObject> object) {
	_OBJECTS.push_back(std::move(object));
}

int main() {
	Game game{};
	return 0;
}

namespace SheepyEngine 
{
	cimg_library::CImgDisplay MAIN_CANVAS{};
}