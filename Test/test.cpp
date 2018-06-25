#include "test.h"
#include "trompeloeil.hpp"

namespace trompeloeil
{
	template <>
	void reporter<specialized>::send(
		const severity s,
		const char* file,
		const unsigned long line,
		const char* msg)
	{
		std::ostringstream os;
		if (line) os << file << ':' << line << '\n';
		os << msg;
		const auto failure = os.str();
		if (s == severity::fatal)
		{
			FAIL(failure);
		}
		else
		{
			CAPTURE(failure);
			CHECK(failure.empty());
		}
	}
}