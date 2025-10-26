#pragma once
#include "src/Vector2d/Vector2d.h"
#include <iostream>
#include <raylib.h>
#include "src/ColorDimension.h"

class Enemy
{
public:
    Vector2d position;
    float speed = 150.f;
    float size = 20.f;
    bool isAlive{ true };
    ColorDimension color;

    void Spawn(int inScreenWidth, int inScreenHeight, Vector2d inTargetPosition);

    void Update(Vector2d inTargetPosition);

    void Draw(ColorDimension worldColor);
};

