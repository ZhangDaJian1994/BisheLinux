#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "generateIrram.h"

TEST_CASE()
{
	std::string s = "y=x*x";
	generateFloatCpp(s);
	int a = 1;
	REQUIRE(a == 1);
}