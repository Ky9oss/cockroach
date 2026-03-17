#include "raylib.h"

#include "raymath.h"

#define BONE_SOCKETS        3
#define BONE_SOCKET_HAT     0
#define BONE_SOCKET_HAND_R  1
#define BONE_SOCKET_HAND_L  2

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)

{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - bone socket");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 5.0f, 5.0f, 5.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };  // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };      // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                            // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;         // Camera projection type


    // Load gltf model
    Model characterModel = LoadModel("resources/models/cockroach.glb"); // Load character model

    // Load gltf model animations
    int animsCount = 0;
    unsigned int animIndex = 0;
    unsigned int animCurrentFrame = 0;
    // ModelAnimation *modelAnimations = LoadModelAnimations("resources/models/gltf/greenman.glb", &animsCount);

    // Indices of bones for sockets
    // int boneSocketIndex[BONE_SOCKETS] = { -1, -1, -1 };

    // Search bones for sockets
    // for (int i = 0; i < characterModel.skeleton.boneCount; i++)
    // {
    //     if (TextIsEqual(characterModel.skeleton.bones[i].name, "socket_hat"))
    //     {
    //         boneSocketIndex[BONE_SOCKET_HAT] = i;
    //         continue;
    //     }
    //
    //     if (TextIsEqual(characterModel.skeleton.bones[i].name, "socket_hand_R"))
    //     {
    //         boneSocketIndex[BONE_SOCKET_HAND_R] = i;
    //         continue;
    //     }
    //
    //     if (TextIsEqual(characterModel.skeleton.bones[i].name, "socket_hand_L"))
    //     {
    //         boneSocketIndex[BONE_SOCKET_HAND_L] = i;
    //         continue;
    //     }
    // }

    Vector3 position = { 0.0f, 0.0f, 0.0f }; // Set model position
    unsigned short angle = 0;           // Set angle for rotate character

    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);

        // Rotate character
        if (IsKeyDown(KEY_F)) angle = (angle + 1)%360;
        else if (IsKeyDown(KEY_H)) angle = (360 + angle - 1)%360;

        // Select current animation
        // if (IsKeyPressed(KEY_T)) animIndex = (animIndex + 1)%animsCount;
        // else if (IsKeyPressed(KEY_G)) animIndex = (animIndex + animsCount - 1)%animsCount;

        // Update model animation
        // ModelAnimation anim = modelAnimations[animIndex];
        // animCurrentFrame = (animCurrentFrame + 1)%anim.keyframeCount;
        // UpdateModelAnimation(characterModel, anim, (float)animCurrentFrame);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                // Draw character
                Quaternion characterRotate = QuaternionFromAxisAngle((Vector3){ 0.0f, 1.0f, 0.0f }, angle*DEG2RAD);
                characterModel.transform = MatrixMultiply(QuaternionToMatrix(characterRotate), MatrixTranslate(position.x, position.y, position.z));

                // UpdateModelAnimation(characterModel, anim, (float)animCurrentFrame);
                // DrawMesh(characterModel.meshes[0], characterModel.materials[1], characterModel.transform);


                DrawGrid(10, 1.0f);
            EndMode3D();

            // DrawText("Use the T/G to switch animation", 10, 10, 20, GRAY);
            DrawText("Use the F/H to rotate character left/right", 10, 35, 20, GRAY);
            // DrawText("Use the 1,2,3 to toggle shown of hat, sword and shield", 10, 60, 20, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // UnloadModelAnimations(modelAnimations, animsCount);
    UnloadModel(characterModel);         // Unload character model and meshes/material

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


