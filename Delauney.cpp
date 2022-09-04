#include "Delauney.h"

std::vector<Vector2> DelauneyTriangulate(std::vector<Vector2> pts)
{
    // Add Super triangle to triangulation.
    std::vector<Triangle> triangulation;
    Triangle superTriangle(CalculateSuperTriangle(pts));
    triangulation.push_back(superTriangle);

    for (Vector2 pt : pts)
    {
        std::vector<Triangle> badTriangles;
        for (Triangle triangle : triangulation)
        {
            if (InCircumCircle(pt, triangle))
            {
                badTriangles.push_back(triangle);
            }
        }

        std::vector<std::array<Vector2, 2>> polygon;

        for (Triangle triangle : badTriangles)
        {
            for (auto edge : triangle.edges)
            {
                bool edgeShared = false;
                for (Triangle otherTriangle : badTriangles)
                {
                    if (!(otherTriangle == triangle) && TriangleContainsEdge(edge, otherTriangle))
                    {
                        edgeShared = true;
                        break;
                    }
                }
                if (!edgeShared)
                {
                    polygon.push_back(edge);
                }
            }
        }

        int currentBadTriangleIndex = badTriangles.size() - 1;
        for (int i = triangulation.size() - 1; i >= 0; i--)
        {
            if (triangulation[i] == badTriangles[currentBadTriangleIndex])
            {
                triangulation.erase(triangulation.begin() + i);
                currentBadTriangleIndex--;
            }
        }

        for (auto edge : polygon)
        {
            // Create a triangle
            Triangle newTri(edge[0], edge[1], pt);
            triangulation.push_back(newTri);
        }
    }

    // Remove all the triangles that contain a vertex from the original super triangle. backwards so indexing doesnt get messed up
    for (int i = triangulation.size() - 1; i >= 0; i--)
    {
        if (TrianglesShareVertex(superTriangle, triangulation[i]))
        {
            triangulation.erase(triangulation.begin() + i);
        }
    }

    // for (Triangle tri : triangulation)
    // {
    //     tri.Show();
    // }

    // Below flatens the triangles into a single array of pts
    std::vector<Vector2> trianglePts(3 * (int)triangulation.size());
    for (int i = 0; i < (int)triangulation.size(); i++)
    {
        int vertexIndex = i * 3;
        trianglePts[vertexIndex + 0] = triangulation[i].vertices[0];
        trianglePts[vertexIndex + 1] = triangulation[i].vertices[2];
        trianglePts[vertexIndex + 2] = triangulation[i].vertices[1];
    }

    return trianglePts;
}

std::vector<int> DelauneyTriangulateIndices(std::vector<Vector2> pts)
{
    std::vector<Vector2> triangulation = DelauneyTriangulate(pts);
    std::vector<int> indices(triangulation.size());
    int index = 0;
    for (size_t i = 0; i < triangulation.size(); i++)
    {
        for (size_t j = 0; j < pts.size(); j++)
        {
            if (VectorsAreEqual(triangulation[i], pts[j]))
            {
                indices[index] = (int)j;
                index++;
            }
        }
    }

    return indices;
}

std::vector<Triangle> DelauneyTriangulateTriangles(std::vector<Vector2> pts)
{
    // Add Super triangle to triangulation.
    std::vector<Triangle> triangulation;
    Triangle superTriangle(CalculateSuperTriangle(pts));
    triangulation.push_back(superTriangle);

    for (Vector2 pt : pts)
    {
        std::vector<Triangle> badTriangles;
        for (Triangle triangle : triangulation)
        {
            if (InCircumCircle(pt, triangle))
            {
                badTriangles.push_back(triangle);
            }
        }

        std::vector<std::array<Vector2, 2>> polygon;

        for (Triangle triangle : badTriangles)
        {
            for (auto edge : triangle.edges)
            {
                bool edgeShared = false;
                for (Triangle otherTriangle : badTriangles)
                {
                    if (!(otherTriangle == triangle) && TriangleContainsEdge(edge, otherTriangle))
                    {
                        edgeShared = true;
                        break;
                    }
                }
                if (!edgeShared)
                {
                    polygon.push_back(edge);
                }
            }
        }

        int currentBadTriangleIndex = badTriangles.size() - 1;
        for (int i = triangulation.size() - 1; i >= 0; i--)
        {
            if (triangulation[i] == badTriangles[currentBadTriangleIndex])
            {
                triangulation.erase(triangulation.begin() + i);
                currentBadTriangleIndex--;
            }
        }

        for (auto edge : polygon)
        {
            // Create a triangle
            Triangle newTri(edge[0], edge[1], pt);
            triangulation.push_back(newTri);
        }
    }

    // Remove all the triangles that contain a vertex from the original super triangle. backwards so indexing doesnt get messed up
    for (int i = triangulation.size() - 1; i >= 0; i--)
    {
        if (TrianglesShareVertex(superTriangle, triangulation[i]))
        {
            triangulation.erase(triangulation.begin() + i);
        }
    }

    for (Triangle tri : triangulation)
    {
        tri.Show();
    }

    return triangulation;
}

// Note: Points must be arranged anti-clockwise
bool InCircumCircle(Vector2 pt, Vector2 A, Vector2 B, Vector2 C)
{
    // Change to doubles if behavior becomes weird
    float a = A.x - pt.x;
    float b = A.y - pt.y;
    float c = ((A.x * A.x) - (pt.x * pt.x)) + ((A.y * A.y) - (pt.y * pt.y));
    float d = B.x - pt.x;
    float e = B.y - pt.y;
    float f = ((B.x * B.x) - (pt.x * pt.x)) + ((B.y * B.y) - (pt.y * pt.y));
    float g = C.x - pt.x;
    float h = C.y - pt.y;
    float i = ((C.x * C.x) - (pt.x * pt.x)) + ((C.y * C.y) - (pt.y * pt.y));

    float determinant = a * e * i - a * f * h - b * d * i + b * f * g + c * d * h - c * e * g;
    return determinant > 0;
}

bool InCircumCircle(Vector2 pt, Triangle tri)
{
    // Change to doubles if behavior becomes weird
    Vector2 A = tri.vertices[0];
    Vector2 B = tri.vertices[1];
    Vector2 C = tri.vertices[2];

    float a = A.x - pt.x;
    float b = A.y - pt.y;
    float c = ((A.x * A.x) - (pt.x * pt.x)) + ((A.y * A.y) - (pt.y * pt.y));
    float d = B.x - pt.x;
    float e = B.y - pt.y;
    float f = ((B.x * B.x) - (pt.x * pt.x)) + ((B.y * B.y) - (pt.y * pt.y));
    float g = C.x - pt.x;
    float h = C.y - pt.y;
    float i = ((C.x * C.x) - (pt.x * pt.x)) + ((C.y * C.y) - (pt.y * pt.y));

    float determinant = a * e * i - a * f * h - b * d * i + b * f * g + c * d * h - c * e * g;
    return determinant > 0;
}

std::array<Vector2, 3> CalculateSuperTriangle(std::vector<Vector2> pts)
{
    std::array<Vector2, 3> superTriangle;
    float minX = 999999, minY = 999999;
    float maxX = 0, maxY = 0;

    for (Vector2 pt : pts)
    {
        minX = pt.x < minX ? pt.x : minX;
        minY = pt.y < minY ? pt.y : minY;
        maxX = pt.x > maxX ? pt.x : maxX;
        maxY = pt.y > maxY ? pt.y : maxY;
    }

    superTriangle[0] = {minX - abs(minX) * 1000, minY - 1000};
    superTriangle[1] = {maxX + abs(maxX) * 1000, minY - 1000};
    superTriangle[2] = {minX + ((maxX - minX) / 2), maxY + abs(maxY) * 1000};

    return superTriangle;
}

bool TriangleContainsEdge(std::array<Vector2, 2> edge, Triangle tri)
{

    for (std::array<Vector2, 2> triEdge : tri.edges)
    {
        if ((VectorsAreEqual(edge[0], triEdge[0]) && VectorsAreEqual(edge[1], triEdge[1])) || (VectorsAreEqual(edge[0], triEdge[1]) && VectorsAreEqual(edge[1], triEdge[0])))
        {
            return true;
        }
    }
    return false;
}

bool VectorsAreEqual(Vector2 a, Vector2 b)
{
    return abs(a.x - b.x) < EPSILON && abs(a.y - b.y) < EPSILON;
}

bool TrianglesShareVertex(Triangle a, Triangle b)
{
    for (Vector2 aVertex : a.vertices)
    {
        for (Vector2 bVertex : b.vertices)
        {
            if (VectorsAreEqual(aVertex, bVertex))
            {
                return true;
            }
        }
    }
    return false;
}