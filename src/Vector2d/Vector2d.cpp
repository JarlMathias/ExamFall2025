#include "Vector2d.h"
#include <vector>

// Returns magnitude of vector
float Vector2d::CalculateMagnitude()
{
    float magnitudeSquared = x * x + y * y;
    float magnitude = sqrtf(magnitudeSquared);
    return magnitude;
}

// Returns an offset of two vectors added
Vector2d Vector2d::SetVectorOffset(Vector2d inVectorToAdd)
{
    float outVectorX = x + inVectorToAdd.x;
    float outVectorY = y + inVectorToAdd.y;
    Vector2d outVector{ outVectorX, outVectorY };

    return outVector;
}

// Returns a scaled vector
Vector2d Vector2d::ScaleVector(float inScalar)
{
    float scaledXVector = x * inScalar;
    float scaledYVector = y * inScalar;
    Vector2d scaledVector{ scaledXVector, scaledYVector };

    return scaledVector;
}

// Returns a vector between two vectors
Vector2d Vector2d::VectorTowardsTarget(Vector2d inTargetVector)
{
    float targetedXVector = inTargetVector.x - x;
    float targetedYVector = inTargetVector.y - y;
    Vector2d targetedVector{ targetedXVector , targetedYVector };

    return targetedVector;
}

// Returns the distance between two vectors
float Vector2d::DistanceToTarget(Vector2d inTargetedVector)
{
    Vector2d targetedVector = VectorTowardsTarget(inTargetedVector);
    float distanceToTargetedVector = targetedVector.CalculateMagnitude();

    return distanceToTargetedVector;
}

// Returns the normalized version of a vector
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

// Returns cosine movement of a vector using amplitude and angle
Vector2d Vector2d::CosineMovement(Vector2d inCenter, float inAmplitude, float inAngle)
{
    float x = inCenter.x + inAmplitude * cosf(inAngle);
    float y = inCenter.y;

    return { x, y };
}

// Returns the circular motion of a vector using radius and angle
Vector2d Vector2d::CircularMotion(Vector2d inCenter, float inRadius, float inAngle)
{
    float cosX = inCenter.x + inRadius * cosf(inAngle);
    float sinY = inCenter.y + inRadius * sinf(inAngle);

    return { cosX, sinY };
}

// Rotates vector around an angle
Vector2d Vector2d::Rotate(float angle)
{
    float cosA = cosf(angle);
    float sinA = sinf(angle);
    return { x * cosA - y * sinA, x * sinA + y * cosA };
}
