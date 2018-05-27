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
		virtual void update() = 0;

		virtual void draw(long frameRatio) = 0;
	};

	class Transform {
	public:
		Transform(long x = 0, long y = 0);

		long getX();

		long getY();

		void setX(long x);

		void setY(long y);

	private:
		std::vector<long> coords{ 0, 0, 0 };
	};

	long Transform::getX() {
		return coords[0];
	}

	long Transform::getY() {
		return coords[1];
	}

	void Transform::setX(long x) {
		coords[0] = x;
	}

	void Transform::setY(long y) {
		coords[1] = y;
	}

	Transform::Transform(long x, long y) {
		setX(x);
		setY(y);
	}
}
