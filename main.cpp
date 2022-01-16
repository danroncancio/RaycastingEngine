#include <iostream>
#include <cmath>
#include "raylib.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 800
#define screenHeight 640

typedef struct Vector2Dd {
    double x;
    double y;
} Vector2Dd;

typedef struct Vector2Di {
    int x;
    int y;
} Vector2Di;

void drawMap2D(bool *showMap);

void drawPlayer(Vector2Dd *position, bool showPlayer);

void movePlayer(Vector2Dd *position, Vector2Dd *direction, Vector2Dd *plane, float delta);


int worldMap[mapWidth][mapHeight] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 3, 0, 3, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int main() {
    Vector2Dd position = {22.0, 12.0};
    Vector2Dd direction = {-1.0, 0.0};
    Vector2Dd plane = {0.0, 0.66};

    double time = 0.0;
    double oldTime = 0.0;

    bool show = false;

    InitWindow(screenWidth, screenHeight, "Raycaster Engine");

    while (!WindowShouldClose()) {
        /* Lenght of the ray from the current position to the next x or y side */\

        float deltaTime = GetFrameTime();

        movePlayer(&position, &direction, &plane, deltaTime);

        BeginDrawing();

        ClearBackground(BLACK);

        for (int x = 0; x < screenWidth; x++) {
            /* Position and direction */
            Vector2Dd camera = {2 * x / (double) screenWidth - 1, 0};
            Vector2Dd rayDirection = {direction.x + plane.x * camera.x, direction.y + plane.y * camera.x};
            /* Box of the map the player is in */
            Vector2Di map = {(int) position.x, (int) position.y};

            Vector2Dd sideDistance;

            /* Length of the ray from one x or y side to next one */
            Vector2Dd deltaDistance = {std::abs(1 / rayDirection.x), std::abs(1 / rayDirection.y)};
            double perpWallDistance;

            Vector2Di step;

            int hit = 0;
            int side;

            /* Calculate step and initial sideDist */
            if (rayDirection.x < 0) {
                step.x = -1;
                sideDistance.x = (position.x - map.x) * deltaDistance.x;
            } else {
                step.x = 1;
                sideDistance.x = (map.x + 1.0 - position.x) * deltaDistance.x;
            }
            if (rayDirection.y < 0) {
                step.y = -1;
                sideDistance.y = (position.y - map.y) * deltaDistance.y;
            } else {
                step.y = 1;
                sideDistance.y = (map.y + 1.0 - position.y) * deltaDistance.y;
            }
            /* Digital differential analyser */
            while (hit == 0) {
                if (sideDistance.x < sideDistance.y) {
                    sideDistance.x += deltaDistance.x;
                    map.x += step.x;
                    side = 0;
                } else {
                    sideDistance.y += deltaDistance.y;
                    map.y += step.y;
                    side = 1;
                }
                if (worldMap[map.x][map.y] > 0)
                    hit = 1;
            }
            /* Calculate distance projected on camera direction */
            if (side == 0)
                perpWallDistance = (sideDistance.x - deltaDistance.x);
            else
                perpWallDistance = (sideDistance.y - deltaDistance.y);

            /* Calculate height of the line to be drawn on screen */
            int lineHeight = (int) (screenHeight / perpWallDistance);
            /* Calculate lowest and highest pixel to fill */
            int drawStart = -lineHeight / 2 + screenHeight / 2;
            if (drawStart < 0)
                drawStart = 0;
            int drawEnd = lineHeight / 2 + screenHeight / 2;
            if (drawEnd >= screenHeight)
                drawEnd = screenHeight - 1;

            Color wallColor;
            switch (worldMap[map.x][map.y]) {
                case 1:
                    wallColor = WHITE;
                    break;
                case 2:
                    wallColor = VIOLET;
                    break;
                case 3:
                    wallColor = RED;
                    break;
                case 4:
                    wallColor = BLUE;
                    break;
            }
            if (side == 1)
                wallColor = {wallColor.r / 2, wallColor.g / 2, wallColor.b / 2, wallColor.a / 2};
            DrawLine(x, drawStart, x, drawEnd, wallColor);
            // DrawLine((position.y * 20) + 4, (position.x * 20) + 4, map.y * 20, map.x * 20, BLUE);
        }
        drawMap2D(&show);
        drawPlayer(&position, show);
        DrawFPS(540, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void drawMap2D(bool *showMap) {
    /* Using pointers like this feels dumb */
    if (IsKeyPressed(KEY_M)) {
        *showMap = !*showMap;
    }
    if (*showMap) {
        for (int x = 0; x < mapWidth; ++x) {
            for (int y = 0; y < mapHeight; ++y) {
                switch (worldMap[x][y]) {
                    case 0:
                        DrawRectangle(y * 20, x * 20, 20 - 2, 20 - 2, GRAY);
                        break;
                    case 1:
                        DrawRectangle(y * 20, x * 20, 20 - 2, 20 - 2, WHITE);
                        break;
                    case 2:
                        DrawRectangle(y * 20, x * 20, 20 - 2, 20 - 2, VIOLET);
                        break;
                    case 3:
                        DrawRectangle(y * 20, x * 20, 20 - 2, 20 - 2, RED);
                        break;
                    case 4:
                        DrawRectangle(y * 20, x * 20, 20 - 2, 20 - 2, BLUE);
                        break;
                    case 5:
                        DrawRectangle(y * 20, x * 20, 20 - 2, 20 - 2, YELLOW);
                        break;
                }
            }
        }
    }
}

void drawPlayer(Vector2Dd *position, bool showPlayer) {
    if (showPlayer)
        DrawRectangle(position->y * 20.0, position->x * 20.0, 8, 8, PURPLE);
}

void movePlayer(Vector2Dd *position, Vector2Dd *direction, Vector2Dd *plane, float delta) {
    double moveSpeed = 2.0 * delta;
    double rotationSpeed = 3.0 * delta;

    if (IsKeyDown(KEY_A)) {
        Vector2Dd oldDirection = *direction;
        direction->x = direction->x * std::cos(rotationSpeed) - direction->y * std::sin(rotationSpeed);
        direction->y = oldDirection.x * std::sin(rotationSpeed) + direction->y * std::cos(rotationSpeed);
        Vector2Dd oldPlane = *plane;
        plane->x = plane->x * std::cos(rotationSpeed) - plane->y * std::sin(rotationSpeed);
        plane->y = oldPlane.x * std::sin(rotationSpeed) + plane->y * std::cos(rotationSpeed);
    }
    if (IsKeyDown(KEY_D)) {
        Vector2Dd oldDirection = *direction;
        direction->x = direction->x * std::cos(-rotationSpeed) - direction->y * std::sin(-rotationSpeed);
        direction->y = oldDirection.x * std::sin(-rotationSpeed) + direction->y * std::cos(-rotationSpeed);
        Vector2Dd oldPlane = *plane;
        plane->x = plane->x * std::cos(-rotationSpeed) - plane->y * std::sin(-rotationSpeed);
        plane->y = oldPlane.x * std::sin(-rotationSpeed) + plane->y * std::cos(-rotationSpeed);
    }
    if (IsKeyDown(KEY_W)) {
        if (worldMap[int(position->x + direction->x * moveSpeed)][int(position->y)] == false)
            position->x += direction->x * moveSpeed;
        if (worldMap[int(position->x)][int(position->y + direction->y * moveSpeed)] == false)
            position->y += direction->y * moveSpeed;
    }
    if (IsKeyDown(KEY_S)) {
        if (worldMap[int(position->x + direction->x * moveSpeed)][int(position->y)] == false)
            position->x -= direction->x * moveSpeed;
        if (worldMap[int(position->x)][int(position->y + direction->y * moveSpeed)] == false)
            position->y -= direction->y * moveSpeed;
    }
}