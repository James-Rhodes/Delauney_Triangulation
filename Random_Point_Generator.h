#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"

class RandomPointGenerator
{
public:
    int radius;
    Vector2 minBounds;
    Vector2 maxBounds;

    RandomPointGenerator(int _radius, Vector2 _minBounds, Vector2 _maxBounds) : radius(_radius), minBounds(_minBounds), maxBounds(_maxBounds){};

    virtual std::vector<Vector2> GeneratePoints(int numPoints) = 0;
    Vector2 GenerateRandomPoint()
    {
        Vector2 pt = {(float)GetRandomValue(minBounds.x, maxBounds.x), (float)GetRandomValue(minBounds.y, maxBounds.y)};
        return pt;
    };
};

class BasicRandomPointGenerator : public RandomPointGenerator
{
public:
    BasicRandomPointGenerator(int _radius, Vector2 _minBounds, Vector2 _maxBounds) : RandomPointGenerator(_radius, _minBounds, _maxBounds){};
    std::vector<Vector2> GeneratePoints(int numPoints) override;
    bool CollidesWithOtherPoints(const Vector2 &pt, const std::vector<Vector2> &pts);
};