#include "Random_Point_Generator.h"

std::vector<Vector2> BasicRandomPointGenerator::GeneratePoints(int numPoints)
{
    std::vector<Vector2> pts;
    int maxIterations = 100000;
    int iteration = 0;

    while ((int)pts.size() < numPoints && iteration < maxIterations)
    {
        Vector2 randPt = GenerateRandomPoint();
        if (!CollidesWithOtherPoints(randPt, pts))
        {
            pts.push_back(randPt);
            iteration = 0;
        }
        else
        {
            iteration++;
        }
    }
    return pts;
}

bool BasicRandomPointGenerator::CollidesWithOtherPoints(const Vector2 &pt, const std::vector<Vector2> &pts)
{
    int radiusSqr = radius * radius;
    for (Vector2 currPt : pts)
    {
        int dist = Vector2Length(Vector2Subtract(currPt, pt));

        if (dist < radiusSqr)
        {
            return true;
        }
    }
    return false;
}