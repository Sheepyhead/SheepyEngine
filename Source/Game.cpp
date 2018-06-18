//
// Created by sheepy on 4/25/18.
//

#include "Game.h"
#include <chrono>
#include <future>
#include <atomic>
#include <map>

using namespace SheepyEngine;
namespace SheepyEngine
{
namespace Game
{
namespace
{
//Internals

//Internal fields

const int FPS = 60;
const double MS_PER_UPDATE = 100.0 / FPS;

std::atomic<bool> isRunning;
std::atomic<bool> testbool = false;
std::future<void> gameLoop;
cimg_library::CImgDisplay MAIN_CANVAS{};

std::vector<std::shared_ptr<GameObject>> objects;

//Internal methods

std::chrono::high_resolution_clock::time_point GetCurrentTime() {
	return std::chrono::high_resolution_clock::now();
}


//Game loop methods

void Update() {
	for (auto& object : objects) {
		object->update();
	}
}

void Draw(const long frameRatio) {
	for (const auto& object : objects) {
		object->draw(frameRatio);
	}
}


std::atomic<bool> stopped = false;
void Initialize() {
	stopped = false;
	isRunning = false;
	testbool = true;
}
void SetStopped(bool stoppedValue)
{
	stopped = true;
}
void RunGameLoop()
{
	auto previous = GetCurrentTime();
	auto lag = 0.0;
	while (!stopped) {
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
	throw std::runtime_error("AAH");
}
}

// Game API

void Create() {
	Initialize();

	gameLoop = std::async([=] {return RunGameLoop(); });
}

void Delete()
{
	stopped = true;
	testbool = false;
	gameLoop.get();
}

bool IsRunning()
{
	return isRunning;
}

void AddGameObject(const std::shared_ptr<GameObject> object) {
	objects.push_back(object);
}
}
}

#ifndef _DEBUG
int main() {
	Game game{};
	return 0;
}
#endif // _DEBUG