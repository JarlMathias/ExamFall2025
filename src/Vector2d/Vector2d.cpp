#include "Vector2d.h"
#include <vector>

float Vector2d::CalculateMagnitude()
{
    float magnitudeSquared = x * x + y * y;
    float magnitude = sqrtf(magnitudeSquared);
    return magnitude;
}

Vector2d Vector2d::SetVectorOffset(Vector2d inVectorToAdd)
{
    float outVectorX = x + inVectorToAdd.x;
    float outVectorY = y + inVectorToAdd.y;
    Vector2d outVector{ outVectorX, outVectorY };

    return outVector;
}

Vector2d Vector2d::ScaleVector(float inScalar)
{
    float scaledXVector = x * inScalar;
    float scaledYVector = y * inScalar;
    Vector2d scaledVector{ scaledXVector, scaledYVector };

    return scaledVector;
}

Vector2d Vector2d::VectorTowardsTarget(Vector2d inTargetVector)
{
    float targetedXVector = inTargetVector.x - x;
    float targetedYVector = inTargetVector.y - y;
    Vector2d targetedVector{ targetedXVector , targetedYVector };

    return targetedVector;
}

float Vector2d::DistanceToTarget(Vector2d inTargetedVector)
{
    Vector2d targetedVector = VectorTowardsTarget(inTargetedVector);
    float distanceToTargetedVector = targetedVector.CalculateMagnitude();

    return distanceToTargetedVector;
}

Vector2d Vector2d::NormalizeVector()
{
    if (CalculateMagnitude() == 0)
    {
        return { 0, 0 };
    }

    float normalizedXVector = x / CalculateMagnitude();
    float normalizedYVector = y / CalculateMagnitude();
    Vector2d normalizedVector{ normalizedXVector,normalizedYVector };

    return normalizedVector;
}

Vector2d Vector2d::CosineMovement(Vector2d inCenter, float inAmplitude, float inAngle)
{
    float x = inCenter.x + inAmplitude * cosf(inAngle);
    float y = inCenter.y;

    return { x, y };
}

Vector2d Vector2d::CircularMotion(Vector2d inCenter, float inRadius, float inAngle)
{
    float cosX = inCenter.x + inRadius * cosf(inAngle);
    float sinY = inCenter.y + inRadius * sinf(inAngle);

    return { cosX, sinY };
}

Vector2d Vector2d::Rotate(float angle)
{
    float cosA = cosf(angle);
    float sinA = sinf(angle);
    return { x * cosA - y * sinA, x * sinA + y * cosA };
}
