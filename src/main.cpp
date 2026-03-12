#include "raylib.h"
#include <vector>

const int screenWidth = 800;
const int screenHeight = 450;
const int cellSize = 20;

struct SnakeSegment {
  Vector2 pos;
};

std::vector<SnakeSegment> snake;
Vector2 dir = {1, 0};

Vector2 food;

int score = 0;
bool gameOver = false;

Vector2 RandomFoodPosition() {
  return {static_cast<float>(
              (GetRandomValue(0, screenWidth / cellSize - 1) * cellSize)),
          static_cast<float>(
              (GetRandomValue(0, screenHeight / cellSize - 1) * cellSize))};
}

void ResetGame() {
  snake.clear();

  snake.push_back({{200, 200}});
  snake.push_back({{180, 200}});
  snake.push_back({{160, 200}});
  snake.push_back({{140, 200}});

  dir = {1, 0};
  food = RandomFoodPosition();
  score = 0;
  gameOver = false;
}

void MoveSnake() {
  Vector2 newHead = {snake[0].pos.x + dir.x * cellSize,
                     snake[0].pos.y + dir.y * cellSize};

  snake.insert(snake.begin(), {newHead});

  if (newHead.x == food.x && newHead.y == food.y) {
    score++;
    food = RandomFoodPosition();
  } else {
    snake.pop_back();
  }
}

bool CheckSelfCollision() {
  for (int i = 1; i < snake.size(); i++) {
    if (snake[0].pos.x == snake[i].pos.x && snake[0].pos.y == snake[i].pos.y)
      return true;
  }
  return false;
}

bool CheckWallCollision() {
  if (snake[0].pos.x - 20 < 0 || snake[0].pos.x + cellSize >= screenWidth ||
      snake[0].pos.y - 20 < 0 || snake[0].pos.y + cellSize >= screenHeight)
    gameOver = true;
  return false;
}

int main(void) {
  InitWindow(screenWidth, screenHeight, "Snake Game");
  SetTargetFPS(60);

  ResetGame();
  int frameCounter = 0;

  while (!WindowShouldClose()) {
    if (!gameOver) {
      if (IsKeyPressed(KEY_RIGHT) && dir.x == 0)
        dir = {1, 0};
      if (IsKeyPressed(KEY_LEFT) && dir.x == 0)
        dir = {-1, 0};
      if (IsKeyPressed(KEY_UP) && dir.y == 0)
        dir = {0, -1};
      if (IsKeyPressed(KEY_DOWN) && dir.y == 0)
        dir = {0, 1};

      frameCounter++;

      if (frameCounter >= 8) {
        MoveSnake();
        frameCounter = 0;
      }

      if (CheckSelfCollision() || CheckWallCollision()) {
        gameOver = true;
      }
    } else {
      if (IsKeyPressed(KEY_R)) {
        ResetGame();
      }
    }

    BeginDrawing();

    ClearBackground(DARKGRAY);

    DrawRectangle(food.x, food.y, cellSize, cellSize, RED);

    for (auto segment : snake) {
      DrawRectangle(segment.pos.x, segment.pos.y, cellSize, cellSize, GREEN);
    }

    const char *text = TextFormat("Score: %d", score);
    int textWidth = MeasureText(text, 20);

    DrawText(text, (screenWidth - textWidth) / 2, 10, 20, RED);

    if (gameOver) {
      DrawText("Game Over", screenWidth / 2 - 100, screenHeight / 2 - 20, 40,
               RED);
      DrawText("Press R to Restart", screenWidth / 2 - 110,
               screenHeight / 2 + 20, 20, WHITE);
    }

    EndDrawing();
  }

  CloseWindow();
}
