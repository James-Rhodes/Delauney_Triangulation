#include "raylib.h"
#include "raymath.h"
#include "Delauney.h"
#include "Random_Point_Generator.h"
#include <iostream>
#include <string>

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Raylib Template");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    BasicRandomPointGenerator ptGen(3, {0, 0}, {screenWidth, screenHeight});
    std::vector<Vector2> pts = ptGen.GeneratePoints(100);

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        //----------------------------------------------------------------------------------
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            pts = ptGen.GeneratePoints(100);
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (Vector2 pt : pts)
        {
            DrawCircle(pt.x, pt.y, 5, BLACK);
        }
        std::vector<Triangle> triangles = DelauneyTriangulateTriangles(pts);
        for (Triangle tri : triangles)
        {
            tri.Show();
        }

        DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}