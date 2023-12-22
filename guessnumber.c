#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Function prototypes
void initializeSDL(SDL_Window **window, SDL_Renderer **renderer);
void closeSDL(SDL_Window **window, SDL_Renderer **renderer);
void renderText(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect textRect, const char *text, int fontSize, SDL_Color textColor);
void renderNumberInput(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect inputRect, int inputNumber, int fontSize);
void renderBackground(SDL_Renderer *renderer);
void handleEvents(SDL_Event *e, int *inputNumber, int *quit, int *checkGuess);
void evaluateGuess(int secretNumber, int playerGuess, int *checkGuess);
int generateRandomNumber(int min, int max);
void playSoundEffect(const char *soundFile);

int totalAttempts = 0;
int totalTime = 0;
int roundsPlayed = 0;

int main() {
    // Seed for random number generation
    srand(time(NULL));

    // SDL variables
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *textTexture = NULL;
    SDL_Texture *inputTexture = NULL;
    SDL_Texture *backgroundTexture = NULL;
    SDL_Texture *buttonTexture = NULL;
    SDL_Rect textRect = {10, 10, 0, 0};
    SDL_Rect inputRect = {10, 60, 0, 0};
    SDL_Rect startButtonRect = {350, 450, 100, 40};
    SDL_Rect quitButtonRect = {450, 450, 100, 40};

    // Game variables
    int minRange = 1;
    int maxRange = 100;
    int secretNumber = generateRandomNumber(minRange, maxRange);
    int inputNumber = 50; // Initial value
    int quit = 0;
    int checkGuess = 0; // Flag to check the guess
    int attempts = 0;

    // Timer variables
    Uint32 startTime;
    Uint32 currentTime;
    int timeLimit = 10; // 10 seconds

    // Initialize SDL
    initializeSDL(&window, &renderer);

    // Initialize SDL_mixer for sound effects
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }

    // Load sound effects
    Mix_Chunk *correctSound = Mix_LoadWAV("path/to/correct_sound.wav");
    Mix_Chunk *incorrectSound = Mix_LoadWAV("path/to/incorrect_sound.wav");

    // Main game loop
    startTime = SDL_GetTicks();
    while (!quit) {
        // Handle events and check the guess only if the timer is running
        if (!checkGuess) {
            handleEvents(&e, &inputNumber, &quit, &checkGuess);
        }

        // Render background
        renderBackground(renderer);

        // Render text with randomized font color
        char textBuffer[100];
        sprintf(textBuffer, "Guess the Number: %d", inputNumber);
        SDL_Color textColor = {rand() % 256, rand() % 256, rand() % 256, 255};
        renderText(renderer, textTexture, textRect, textBuffer, 28, textColor);

        // Visual feedback on guess
        if (checkGuess) {
            evaluateGuess(secretNumber, inputNumber, &checkGuess);
        }

        // Render number input
        renderNumberInput(renderer, inputTexture, inputRect, inputNumber, 28);

        // Check the guess after the time limit
        if (checkGuess) {
            currentTime = SDL_GetTicks();
            if ((currentTime - startTime) / 1000 >= timeLimit) {
                // Check the guess
                if (inputNumber == secretNumber) {
                    playSoundEffect(correctSound);
                    printf("Congratulations! You guessed the correct number.\n");
                    totalAttempts += attempts;
                    totalTime += timeLimit - ((currentTime - startTime) / 1000);
                } else {
                    playSoundEffect(incorrectSound);
                    printf("Sorry! The correct number was %d.\n", secretNumber);
                }

                // Reset for the next round
                secretNumber = generateRandomNumber(minRange, maxRange);
                inputNumber = 50;
                checkGuess = 0;
                startTime = SDL_GetTicks();
                attempts = 0;

                // Increment rounds played
                roundsPlayed++;

                // Display game over screen after 3 rounds
                if (roundsPlayed == 3) {
                    printf("\nGame Over! Final Score: %d points in %d seconds\n", totalAttempts, totalTime);

                    // Render game-over screen with animated transition
                    for (int alpha = 0; alpha <= 255; alpha += 5) {
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
                        SDL_RenderClear(renderer);

                        // Render text and buttons on the game-over screen
                        renderText(renderer, textTexture, textRect, "Game Over!", 36, (SDL_Color){255, 255, 255, alpha});
                        renderText(renderer, textTexture, (SDL_Rect){300, 250, 0, 0}, "Final Score:", 28, (SDL_Color){255, 255, 255, alpha});
                        char scoreBuffer[50];
                        sprintf(scoreBuffer, "%d points in %d seconds", totalAttempts, totalTime);
                        renderText(renderer, textTexture, (SDL_Rect){300, 300, 0, 0}, scoreBuffer, 28, (SDL_Color){255, 255, 255, alpha});

                        // Render buttons with hover effect
                        SDL_Color startButtonColor = {255, 255, 255, alpha};
                        SDL_Color quitButtonColor = {255, 255, 255, alpha};

                        if (e.motion.x >= startButtonRect.x && e.motion.x <= startButtonRect.x + startButtonRect.w &&
                            e.motion.y >= startButtonRect.y && e.motion.y <= startButtonRect.y + startButtonRect.h) {
                            startButtonColor = (SDL_Color){255, 0, 0, alpha}; // Hover effect
                            if (e.type == SDL_MOUSEBUTTONDOWN) {
                                // Start a new game
                                roundsPlayed = 0;
                                totalAttempts = 0;
                                totalTime = 0;
                            }
                        }

                        if (e.motion.x >= quitButtonRect.x && e.motion.x <= quitButtonRect.x + quitButtonRect.w &&
                            e.motion.y >= quitButtonRect.y && e.motion.y <= quitButtonRect.y + quitButtonRect.h) {
                            quitButtonColor = (SDL_Color){255, 0, 0, alpha}; // Hover effect
                            if (e.type == SDL_MOUSEBUTTONDOWN) {
                                // Quit the game
                                quit = 1;
                            }
                        }

                        renderText(renderer, buttonTexture, startButtonRect, "New Game", 20, startButtonColor);
                        renderText(renderer, buttonTexture, quitButtonRect, "Quit", 20, quitButtonColor);

                        SDL_RenderPresent(renderer);
                        SDL_Delay(16); // Cap frame rate to approximately 60 fps
                    }

                    quit = 1; // Exit the loop after the transition
                }
            }
        }

        // Render buttons with hover effect
        SDL_Color startButtonColor = {255, 255, 255, 255};
        SDL_Color quitButtonColor = {255, 255, 255, 255};

        if (e.motion.x >= startButtonRect.x && e.motion.x <= startButtonRect.x + startButtonRect.w &&
            e.motion.y >= startButtonRect.y && e.motion.y <= startButtonRect.y + startButtonRect.h) {
            startButtonColor = (SDL_Color){255, 0, 0, 255}; // Hover effect
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                // Start a new game
                roundsPlayed = 0;
                totalAttempts = 0;
                totalTime = 0;
            }
        }

        if (e.motion.x >= quitButtonRect.x && e.motion.x <= quitButtonRect.x + quitButtonRect.w &&
            e.motion.y >= quitButtonRect.y && e.motion.y <= quitButtonRect.y + quitButtonRect.h) {
            quitButtonColor = (SDL_Color){255, 0, 0, 255}; // Hover effect
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                // Quit the game
                quit = 1;
            }
        }

        renderText(renderer, buttonTexture, startButtonRect, "New Game", 20, startButtonColor);
        renderText(renderer, buttonTexture, quitButtonRect, "Quit", 20, quitButtonColor);

        // Update screen
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Cap frame rate to approximately 60 fps
    }

    // Free resources and close SDL
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(inputTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(buttonTexture);
    Mix_FreeChunk(correctSound);
    Mix_FreeChunk(incorrectSound);
    closeSDL(&window, &renderer);

    // Quit SDL_mixer
    Mix_Quit();

    return 0;
}
void initializeSDL(SDL_Window **window, SDL_Renderer **renderer) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Create window
    *window = SDL_CreateWindow("Guess the Number", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (*window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Create renderer
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Set renderer color
    SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);

    // Initialize SDL_ttf
    if (TTF_Init() < 0) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

void closeSDL(SDL_Window **window, SDL_Renderer **renderer) {
    // Destroy window and renderer
    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow(*window);

    // Quit SDL_ttf
    TTF_Quit();

    // Quit SDL
    SDL_Quit();
}

void renderText(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect textRect, const char *text) {
    // Load font (Change the path to your font file)
    TTF_Font *font = TTF_OpenFont("path/to/your/font.ttf", 28);
    if (font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // Create surface from text
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, (SDL_Color){0, 0, 0, 255});
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // Create texture from surface
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (texture == NULL) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Get image dimensions
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;

    // Free surface
    SDL_FreeSurface(textSurface);

    // Render texture to screen
    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    // Free texture
    SDL_DestroyTexture(texture);

    // Close font
    TTF_CloseFont(font);
}

void renderNumberInput(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect inputRect, int inputNumber) {
    char inputBuffer[10];
    sprintf(inputBuffer, "%d", inputNumber);

    // Load font (Change the path to your font file)
    TTF_Font *font = TTF_OpenFont("path/to/your/font.ttf", 28);
    if (font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // Create surface from text
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, inputBuffer, (SDL_Color){0, 0, 0, 255});
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // Create texture from surface
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (texture == NULL) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Get image dimensions
    inputRect.w = textSurface->w;
    inputRect.h = textSurface->h;

    // Free surface
    SDL_FreeSurface(textSurface);

    // Render texture to screen
    SDL_RenderCopy(renderer, texture, NULL, &inputRect);

    // Free texture
    SDL_DestroyTexture(texture);

    // Close font
    TTF_CloseFont(font);
}

void renderBackground(SDL_Renderer *renderer) {
    // Render a dynamic background (for demonstration purposes)
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderClear(renderer);
}

void handleEvents(SDL_Event *e, int *inputNumber, int *quit, int *checkGuess) {
    while (SDL_PollEvent(e) != 0) {
        if (e->type == SDL_QUIT) {
            *quit = 1;
        } else if (e->type == SDL_KEYDOWN) {
            switch (e->key.keysym.sym) {
                case SDLK_UP:
                    if (*inputNumber < 100) {
                        (*inputNumber)++;
                    }
                    break;
                case SDLK_DOWN:
                    if (*inputNumber > 1) {
                        (*inputNumber)--;
                    }
                    break;
                case SDLK_RETURN:
                    // Check the guess
                    *checkGuess = 1;
                    break;
                default:
                    break;
            }
        }
    }
}

void playSoundEffect(const char *soundFile) {
    // Play a sound effect
    Mix_Chunk *soundEffect = Mix_LoadWAV(soundFile);
    if (soundEffect == NULL) {
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }

    Mix_PlayChannel(-1, soundEffect, 0);

    // Free sound effect
    Mix_FreeChunk(soundEffect);
}

    // Quit SDL_image and SDL_mixer
    IMG_Quit();
    Mix_Quit();

    return 0;
}

void renderTexture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int width, int height) {
    SDL_Rect destination = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &destination);
}

SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *path) {
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        exit(EXIT_FAILURE);
    }

    return texture;
}