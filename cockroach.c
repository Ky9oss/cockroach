#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {

  // Initialization
  //--------------------------------------------------------------------------------------
  const int winWidth = 450;
  const int winHeight = 450;

  SetConfigFlags(FLAG_WINDOW_UNDECORATED);       // 去掉标题栏、边框
  SetConfigFlags(FLAG_WINDOW_TOPMOST);           // 窗口永远置顶
  SetConfigFlags(FLAG_WINDOW_TRANSPARENT);       // 窗口背景透明
  SetConfigFlags(FLAG_WINDOW_MOUSE_PASSTHROUGH); // 鼠标点击穿透

  InitWindow(winWidth, winHeight, "robot");

  int margin = 20;


  int currentMonitor = GetCurrentMonitor(); 

  Vector2 monitorPos = GetMonitorPosition(currentMonitor); // position of the top left corner
  int monitorW = GetMonitorWidth(currentMonitor);
  int monitorH = GetMonitorHeight(currentMonitor);

  SetWindowPosition((int)monitorPos.x + monitorW - winWidth - margin,
                    (int)monitorPos.y + monitorH - winHeight - margin);

  // Define the camera to look into our 3d world
  Camera camera = {0};
  camera.position = (Vector3){6.0f, 6.0f, 6.0f}; // Camera position
  camera.target = (Vector3){0.0f, 2.0f, 0.0f};   // Camera looking at point
  camera.up =
      (Vector3){0.0f, 1.0f, 0.0f}; // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;             // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE; // Camera projection type

  // Load model
  Model model = LoadModel("resources/models/robot.glb");
  Vector3 position = {0.0f, 0.0f, 0.0f}; // Set model world position

  // Load model animations
  int animCount = 0;
  ModelAnimation *anims =
      LoadModelAnimations("resources/models/robot.glb", &animCount);

  // Animation playing variables
  unsigned int animIndex = 0;        // Current animation playing
  unsigned int animCurrentFrame = 0; // Current animation frame

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    UpdateCamera(&camera, CAMERA_ORBITAL);

    // Select current animation
    if (IsKeyPressed(KEY_RIGHT))
      animIndex = (animIndex + 1) % animCount;
    else if (IsKeyPressed(KEY_LEFT))
      animIndex = (animIndex + animCount - 1) % animCount;

    // Update model animation
    animCurrentFrame = (animCurrentFrame + 1) % anims[animIndex].frameCount;
    UpdateModelAnimation(model, anims[animIndex], (float)animCurrentFrame);
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(BLANK);

    BeginMode3D(camera);

    DrawModel(model, position, 1.0f, WHITE);

    // DrawGrid(10, 1.0f);

    EndMode3D();

    // DrawText(TextFormat("Current animation: %s", anims[animIndex].name), 10,
    // 40,
    //          20, MAROON);
    // DrawText("Use the LEFT/RIGHT keys to switch animation", 10, 10, 20,
    // GRAY);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  UnloadModelAnimations(anims, animCount); // Unload model animations data
  UnloadModel(model);                      // Unload model

  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
