#pragma once

#include <vector>
#include "DiceSide.h"

class Dice
{
public:
	std::vector<DiceSide> sides;
	DiceSide* active;
	void display(int y, int x);
	int roll();
	bool keep;
};

