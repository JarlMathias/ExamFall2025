#include "Ability.h"

void Ability::InsertColor(ColorDimension color)
{
	if (holdingColors.size() < 3)
	{
		holdingColors.push_back(color);
		std::cout << "INSERTED: " << color << std::endl;
	}
	else
	{
		std::cout << "MAX HOLDING" << std::endl;
	}
}

bool Ability::IsHoldingColor(ColorDimension color)
{
	if (std::find(holdingColors.begin(), holdingColors.end(), color) != holdingColors.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Ability::Use()
{	
	if (IsHoldingColor(BLUE_COLOR) && IsHoldingColor(RED_COLOR) && IsHoldingColor(YELLOW_COLOR))
	{
		std::cout << "Holding ALL" << std::endl;
	}
	else if (IsHoldingColor(BLUE_COLOR) && IsHoldingColor(RED_COLOR))
	{
		std::cout << "Holding BLUE and RED" << std::endl;
	}
	else if (IsHoldingColor(BLUE_COLOR) && IsHoldingColor(YELLOW_COLOR))
	{
		std::cout << "Holding BLUE and YELLOW" << std::endl;
	}
	else if (IsHoldingColor(RED_COLOR) && IsHoldingColor(YELLOW_COLOR))
	{
		std::cout << "Holding RED and YELLOW" << std::endl;
	}
	else if (IsHoldingColor(BLUE_COLOR))
	{
		std::cout << "Holding BLUE" << std::endl;
	}
	else if (IsHoldingColor(RED_COLOR))
	{
		std::cout << "Holding RED" << std::endl;
	}
	else if (IsHoldingColor(YELLOW_COLOR))
	{
		std::cout << "Holding YELLOW" << std::endl;
	}
	else
	{
		std::cout << "ERROR: Not holding any valid colors" << std::endl;
	}

	holdingColors.clear();
}