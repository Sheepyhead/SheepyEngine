#pragma once
#include <vector>

class Transform {
public:
	explicit Transform(long x = 0, long y = 0);

	long getX();

	long getY();

	void setX(long x);

	void setY(long y);

private:
	std::vector<long> coords{ 0, 0, 0 };
};
