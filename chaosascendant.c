#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SOIL/SOIL.h>

#define MAZE_SIZE 10
#define MAZE_CELL_SIZE 5.0f

// Camera parameters
float cameraRadius = 5.0f;
float cameraHeight = 2.0f;
float cameraAngle = 0.0f;

// Light parameters
GLfloat lightDirection[] = {0.0f, -1.0f, -1.0f, 0.0f}; // Directional light pointing downward

// Inventory variables
int selectedWeapon = 0;  // Index of the selected weapon in the inventory
float playerHeight = 2.0f;  // Default player height

// Function to initialize SDL, create a window, and set up OpenGL
int initSDL() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 0;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("ChaosAscendant.c", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        return 0;
    }

    // Create an OpenGL context
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        fprintf(stderr, "OpenGL context creation failed: %s\n", SDL_GetError());
        return 0;
    }

    // Set up OpenGL
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightDirection);
    gluOrtho2D(0, 800, 0, 600);

    return 1;
}

// Function to load textures
GLuint loadTexture(const char* path) {
    GLuint textureID = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (!textureID) {
        fprintf(stderr, "Failed to load texture: %s\n", SOIL_last_result());
    }
    return textureID;
}

float characterSpeed = 0.1f;

// Update handleInput() function to control character speed
void handleInput() {
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_LEFT]) {
        cameraAngle -= 0.05f * characterSpeed;
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        cameraAngle += 0.05f * characterSpeed;
    }
    if (state[SDL_SCANCODE_UP]) {
        cameraRadius -= 0.1f * characterSpeed;
    }
    if (state[SDL_SCANCODE_DOWN]) {
        cameraRadius += 0.1f * characterSpeed;
    }
    // ... other controls
}

// Add variables for dialogue
int showDialogue = 0;
const char* dialogueText = "Hello, adventurer! Welcome to the game.";

// Update handleInput() to trigger dialogue
void handleInput() {
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_SPACE]) {
        // Toggle dialogue display
        showDialogue = !showDialogue;
    }
}

// Update drawScene() to display dialogue
void drawScene() {
    // ... previous code

    if (showDialogue) {
        // Display dialogue box
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(300.0f, 400.0f);
        glVertex2f(500.0f, 400.0f);
        glVertex2f(500.0f, 500.0f);
        glVertex2f(300.0f, 500.0f);
        glEnd();

        // Display dialogue text
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(320.0f, 450.0f);
        for (const char *c = dialogueText; *c != '\0'; ++c) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }
    }

    // ... other code
}

// Function to handle keyboard input
void handleInput() {
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_LEFT]) {
        cameraAngle -= 0.05f;
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        cameraAngle += 0.05f;
    }
    if (state[SDL_SCANCODE_UP]) {
        cameraRadius -= 0.1f;
    }
    if (state[SDL_SCANCODE_DOWN]) {
        cameraRadius += 0.1f;
    }
    if (state[SDL_SCANCODE_SPACE]) {
        // Switch to the next weapon in the inventory
        selectedWeapon = (selectedWeapon + 1) % 3;  // Assuming there are three weapons in the inventory
    }
    if (state[SDL_SCANCODE_W]) {
        // Increase player height
        playerHeight += 0.1f;
    }
    if (state[SDL_SCANCODE_S]) {
        // Decrease player height, but prevent it from going below 0.1
        playerHeight = fmax(0.1f, playerHeight - 0.1f);
    }
}

// Function to update the camera position
void updateCamera() {
    float cameraX = cameraRadius * cos(cameraAngle);
    float cameraY = cameraHeight + playerHeight;  // Adjust camera height based on player's height
    float cameraZ = cameraRadius * sin(cameraAngle);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, 0, playerHeight, 0, 0, 1, 0);
}

// Function to draw the maze
void drawMaze() {
    for (int i = 0; i < MAZE_SIZE; ++i) {
        for (int j = 0; j < MAZE_SIZE; ++j) {
            if (maze[i][j] == 1) {
                // Draw iron-like structure
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, loadTexture("path/to/iron_texture.jpg"));
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(j * MAZE_CELL_SIZE, 0.0f, i * MAZE_CELL_SIZE);
                glTexCoord2f(1.0f, 0.0f); glVertex3f((j + 1) * MAZE_CELL_SIZE, 0.0f, i * MAZE_CELL_SIZE);
                glTexCoord2f(1.0f, 1.0f); glVertex3f((j + 1) * MAZE_CELL_SIZE, MAZE_CELL_SIZE, i * MAZE_CELL_SIZE);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(j * MAZE_CELL_SIZE, MAZE_CELL_SIZE, i * MAZE_CELL_SIZE);
                glEnd();
                glDisable(GL_TEXTURE_2D);
            }
        }
    }
}

// Function to draw the scene
void drawScene() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw ground with texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, loadTexture("path/to/ground_texture.jpg"));
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, 0.0f, -10.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 0.0f, -10.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 0.0f, 10.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 0.0f, 10.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Draw cube with texture (as a placeholder for the player or weapon)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, loadTexture("path/to/cube_texture.jpg"));
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 2.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 2.0f, -1.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Draw inventory panel
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(10.0f, 10.0f);
    glVertex2f(200.0f, 10.0f);
    glVertex2f(200.0f, 100.0f);
    glVertex2f(10.0f, 100.0f);
    glEnd();

    // Draw selected weapon in the inventory panel
    // You can replace this with your actual weapon models
    switch (selectedWeapon) {
        case 0:
            glColor3f(1.0f, 0.0f, 0.0f);  // Red for Weapon 1
            break;
        case 1:
            glColor3f(0.0f, 1.0f, 0.0f);  // Green for Weapon 2
            break;
        case 2:
            glColor3f(0.0f, 0.0f, 1.0f);  // Blue for Weapon 3
            break;
    }
    glBegin(GL_QUADS);
    glVertex2f(20.0f, 20.0f);
    glVertex2f(40.0f, 20.0f);
    glVertex2f(40.0f, 40.0f);
    glVertex2f(20.0f, 40.0f);
    glEnd();

    // Draw the maze
    drawMaze();

    // Swap buffers
    SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());
}

int main() {
    if (!initSDL()) {
        return 1;
    }

    // Main loop
    int quit = 0;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        handleInput();
        updateCamera();
        drawScene();
    }

    // Clean up
    SDL_Quit();

    return 0;
}