#pragma once

#include <vector>
#include <array>
#include "raylib.h"
#include <math.h>
#include <iostream>
#include <bits/stdc++.h>

#define EPSILON 0.000000001

struct Triangle
{
    std::array<Vector2, 3> vertices;
    std::array<std::array<Vector2, 2>, 3> edges;
    Triangle(Vector2 a, Vector2 b, Vector2 c)
    {
        vertices[0] = a;
        vertices[1] = b;
        vertices[2] = c;

        edges = {{{{vertices[0], vertices[1]}}, {{vertices[1], vertices[2]}}, {{vertices[2], vertices[0]}}}};
    }
    Triangle(std::array<Vector2, 3> _vertices)
    {
        vertices = _vertices;
        edges = {{{{vertices[0], vertices[1]}}, {{vertices[1], vertices[2]}}, {{vertices[2], vertices[0]}}}};
    };
    Triangle(){};
    bool operator==(Triangle const &rhs)
    {
        int index = 0;
        std::array<bool, 3> truthArray = {false, false, false};
        for (Vector2 pt : vertices)
        {
            for (Vector2 otherPt : rhs.vertices)
            {
                if (abs(pt.x - otherPt.x) < EPSILON && abs(pt.y - otherPt.y) < EPSILON)
                {
                    truthArray[index] = true;
                    index++;
                    break;
                }
            }
        }
        return truthArray[0] && truthArray[1] && truthArray[2];
    };

    void Show()
    {
        DrawLine(vertices[0].x, vertices[0].y, vertices[1].x, vertices[1].y, BLACK);
        DrawLine(vertices[1].x, vertices[1].y, vertices[2].x, vertices[2].y, BLACK);
        DrawLine(vertices[0].x, vertices[0].y, vertices[2].x, vertices[2].y, BLACK);
    };
};

// Function returns a vector of the points/vertices required for triangulation
std::vector<Vector2> DelauneyTriangulate(std::vector<Vector2> pts);

// Returns the vector of triangles used for delauney triangulation
std::vector<Triangle> DelauneyTriangulateTriangles(std::vector<Vector2> pts);

std::vector<int> DelauneyTriangulateIndices(std::vector<Vector2> pts);

// Determines if a point is in the circumCircle of the other 3 points
bool InCircumCircle(Vector2 pt, Vector2 A, Vector2 B, Vector2 C);
bool InCircumCircle(Vector2 pt, Triangle tri);

// Use below to calculate the Super triangle (the triangle that wraps all the points)
std::array<Vector2, 3> CalculateSuperTriangle(std::vector<Vector2> pts);

bool TriangleContainsEdge(std::array<Vector2, 2> edge, Triangle tri);

bool VectorsAreEqual(Vector2 a, Vector2 b);

bool TrianglesShareVertex(Triangle a, Triangle b);
