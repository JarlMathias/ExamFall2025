#pragma once
#include "src/ColorDimension.h"
#include <vector>
#include <iostream>
#include <algorithm>

class Ability
{
public:
	std::vector <ColorDimension> holdingColors;

	void InsertColor(ColorDimension color);

	bool IsHoldingColor(ColorDimension color);

	void Use();
};