#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RAYGUI_IMPLEMENTATION
#if defined(__APPLE__)
#include "raylib-5.5_macos/include/raylib.h"
#include "raylib-5.5_macos/include/raygui.h"
#elif defined(_WIN32)
#include "raylib-5.5_win64_msvc16/include/raylib.h"
#include "raylib-5.5_win64_msvc16/include/raygui.h"
#elif defined(__linux__)
#include "raylib-5.5_linux_amd64/include/raylib.h"
#include "raylib-5.5_linux_amd64/include/raygui.h"
#endif

bool UseTime = true;
bool SeedTextBoxEditMode = false;
bool StartRangeTextBoxEditMode = false;
bool EndRangeTextBoxEditMode = false;
char Seed[16] = "69";
char StartRange[16] = "0";
char EndRange[16] = "256";
char StrResult[16];
int Result;


int main(void) {
  InitWindow(400, 250, "randy");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      if (CheckCollisionPointRec(GetMousePosition(),
                                 (Rectangle){138, 56, 64, 20})) {
	StartRangeTextBoxEditMode = !StartRangeTextBoxEditMode;
      } else if (CheckCollisionPointRec(GetMousePosition(),
					(Rectangle){285, 56, 64, 20})) {
	EndRangeTextBoxEditMode = !EndRangeTextBoxEditMode;
      }
    }
    GuiCheckBox((Rectangle){10, 10, 15, 15}, "Use time as seed", &UseTime);
    if (!UseTime) {
      if (CheckCollisionPointRec(GetMousePosition(),
                                 (Rectangle){64, 32, 64, 20}) &&
          IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
	SeedTextBoxEditMode = !SeedTextBoxEditMode;
      }
      DrawText("Seed: ", 10, 32, 16, WHITE);
      GuiTextBox((Rectangle){64, 32, 64, 20}, Seed, 16, SeedTextBoxEditMode);
    }
    DrawText("Range Start: ", 10, 56, 16, WHITE);
    DrawText("Range End: ", 196, 56, 16, WHITE);
    GuiTextBox((Rectangle){115, 56, 64, 20}, StartRange, 20,
               StartRangeTextBoxEditMode);
    GuiTextBox((Rectangle){285, 56, 64, 20}, EndRange, 20,
               EndRangeTextBoxEditMode);
    GuiButton((Rectangle){150, 128, 100, 32}, "Calculate");
    DrawText("Result: ", 150, 175, 16, WHITE);
    DrawText(StrResult, 208, 175, 16, WHITE);
    if (GuiButton((Rectangle){150, 128, 100, 32}, "Calculate")) {
      if (UseTime) {
	srand(time(NULL));
      } else {
	srand(atoi(Seed));
      }
      Result = rand() % atoi(EndRange) + atoi(StartRange);
      snprintf(StrResult, sizeof(StrResult), "%d", Result);
    }
    EndDrawing();
  }
  return 0;
}
