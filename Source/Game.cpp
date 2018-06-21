//
// Created by sheepy on 4/25/18.
//

#include "Game.h"
#include <chrono>
#include <future>
#include <atomic>
#include <mutex>
#include <queue>
#include <optional>
#include <iostream>
#include <cstdio>
#include <CImg.h>
#include <vector>

using namespace SheepyEngine;
namespace SheepyEngine
{
namespace Game
{
namespace
{
//Internals

enum class Message
{
	quit
};

//Internal fields

const int FPS = 60;
constexpr double MS_PER_UPDATE = 100.0 / FPS;

std::future<void> gameLoop;
cimg_library::CImgDisplay canvas{};

std::mutex toGameLoopMessageMutex{};
std::queue<Message> toGameLoopMessageQueue{};

std::vector<std::shared_ptr<GameObject>> objects;

//Internal methods

std::chrono::high_resolution_clock::time_point GetCurrentTime() {
	return std::chrono::high_resolution_clock::now();
}

void AddMessage(const Message& message)
{
	toGameLoopMessageMutex.lock();

	toGameLoopMessageQueue.push(message);

	toGameLoopMessageMutex.unlock();
}

std::optional<Message> PopMessage()
{
	toGameLoopMessageMutex.lock();

	if (toGameLoopMessageQueue.empty())
	{
		toGameLoopMessageMutex.unlock();
		
		return std::nullopt;
	}

	const auto message = toGameLoopMessageQueue.front();
	toGameLoopMessageQueue.pop();

	toGameLoopMessageMutex.unlock();

	return std::optional<Message>{message};
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

void Initialize() {

}

void RunGameLoop()
{
	auto stopped = false;
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

		if (auto message = PopMessage())
		{
			switch (*message)
			{
			case Message::quit:
				stopped = true;
				break;
			}
		}
	}

}
}

// Game API

void Create() {
	Initialize();

	gameLoop = std::async(RunGameLoop);
}

void Delete()
{
	AddMessage(Message::quit);
	gameLoop.get();
}

bool IsRunning()
{
	// Check that the game loop has not finished running
	return gameLoop.wait_for(std::chrono::seconds(0)) != std::future_status::ready;
}

void AddGameObject(const std::shared_ptr<GameObject>& object) {
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