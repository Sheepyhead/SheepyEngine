#include "Transform.h"

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