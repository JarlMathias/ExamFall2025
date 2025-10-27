#include "Ability.h"

// Adds color to be held
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

// Checks if the player is holding a specific color
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

// Runs different ability outcomes based on held colors
int Ability::Use(Player player, std::vector<Bullet> bullets, std::vector<Enemy> enemies)
{	
	int returnValue = 0;

	// Smite --- DONE?
	if (IsHoldingColor(BLUE_COLOR) && IsHoldingColor(RED_COLOR) && IsHoldingColor(YELLOW_COLOR))
	{
		std::cout << "Using ALL" << std::endl;
		returnValue = 1;
	}

	// Bullet speed --- DONE
	else if (IsHoldingColor(BLUE_COLOR) && IsHoldingColor(RED_COLOR))
	{
		std::cout << "Using BLUE and RED" << std::endl;
		returnValue = 2;
	}

	// Enemy slow --- DONE
	else if (IsHoldingColor(BLUE_COLOR) && IsHoldingColor(YELLOW_COLOR))
	{
		std::cout << "Using BLUE and YELLOW" << std::endl;
		returnValue = 3;
	}

	// Explosion --- DONE
	else if (IsHoldingColor(RED_COLOR) && IsHoldingColor(YELLOW_COLOR))
	{
		std::cout << "Using RED and YELLOW" << std::endl;
		returnValue = 4;
	}

	// Shield --- DONE
	else if (IsHoldingColor(BLUE_COLOR))
	{
		std::cout << "Using BLUE" << std::endl;
		returnValue = 5;
	}

	// Bullet spread --- DONE
	else if (IsHoldingColor(RED_COLOR))
	{
		std::cout << "Using RED" << std::endl;
		returnValue = 6;
	}

	// Speed --- DONE
	else if (IsHoldingColor(YELLOW_COLOR))
	{
		std::cout << "Using YELLOW" << std::endl;

		returnValue = 7;
	}

	else
	{
		std::cout << "ERROR: Not holding any valid colors" << std::endl;
	}

	cooldown = 3.0f;
	lastUsedTime = GetTime();
	isReady = false;

	holdingColors.clear();
	return returnValue;
}