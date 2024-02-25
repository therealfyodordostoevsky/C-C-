#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include "rsp.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Function to get the computer's move
int getComputerMove() {
    // Generate a random number between 0 and 2
    return rand() % 3;
}

// Function to determine the winner of the round
int determineWinner(int player1, int player2) {
    // Returns 0 for a tie, 1 for player 1 win, 2 for player 2 win
    if (player1 == player2) {
        return 0; // Tie
    } else if ((player1 == 0 && player2 == 2) || (player1 == 1 && player2 == 0) || (player1 == 2 && player2 == 1)) {
        return 1; // Player 1 win
    } else {
        return 2; // Player 2 win
    }
}

void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y) {
    SDL_Rect rect = { x, y, 200, 200 };
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void saveScore(Player player) {
    // Save the player's score
    players[numPlayers++] = player;
}

// Function to compare scores for qsort
int compareScores(const void* a, const void* b) {
    return ((Player*)b)->score - ((Player*)a)->score;
}

void displayTopScores() {
    // Sort players by score
    qsort(players, numPlayers, sizeof(Player), compareScores);

    // Display the top 3 scores
    printf("Top 3 High Scores:\n");
    for (int i = 0; i < numPlayers && i < 3; ++i) {
        printf("%d. %s: %d\n", i + 1, players[i].name, players[i].score);
    }
}
// Inside the main game loop after determining the winner

// Save player's score
Player currentPlayer;
strcpy(currentPlayer.name, "Player 1");  // Replace with the actual player's name
currentPlayer.score = (result == 1) ? 1 : 0;  // Assuming 1 point for a win, 0 for a tie or loss
saveScore(currentPlayer);

// Display top scores
displayTopScores();


int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Rock Paper Scissors", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Load enhanced images for Rock, Paper, Scissors
    SDL_Surface* rockSurface = SDL_LoadBMP("rock_enhanced.bmp");
    SDL_Surface* paperSurface = SDL_LoadBMP("paper_enhanced.bmp");
    SDL_Surface* scissorsSurface = SDL_LoadBMP("scissors_enhanced.bmp");

    if (!rockSurface || !paperSurface || !scissorsSurface) {
        printf("Failed to load enhanced images! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create textures from surfaces
    SDL_Texture* rockTexture = SDL_CreateTextureFromSurface(renderer, rockSurface);
    SDL_Texture* paperTexture = SDL_CreateTextureFromSurface(renderer, paperSurface);
    SDL_Texture* scissorsTexture = SDL_CreateTextureFromSurface(renderer, scissorsSurface);

    // Free the surfaces
    SDL_FreeSurface(rockSurface);
    SDL_FreeSurface(paperSurface);
    SDL_FreeSurface(scissorsSurface);

    // Seed the random number generator
    srand(time(NULL));

    // Render labels
    SDL_Color textColor = { 255, 255, 255 };
    TTF_Font* font = TTF_OpenFont("font.ttf", 36); // Replace "font.ttf" with your font file
    if (!font) {
        printf("Failed to load font! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* labelSurface = TTF_RenderText_Solid(font, "Player 1", textColor);
    SDL_Texture* labelTexture = SDL_CreateTextureFromSurface(renderer, labelSurface);
    SDL_Rect labelRect = { 50, 350, labelSurface->w, labelSurface->h };
    SDL_FreeSurface(labelSurface);

    SDL_Surface* label2Surface = TTF_RenderText_Solid(font, "Player 2", textColor);
    SDL_Texture* label2Texture = SDL_CreateTextureFromSurface(renderer, label2Surface);
    SDL_Rect label2Rect = { 550, 350, label2Surface->w, label2Surface->h };
    SDL_FreeSurface(label2Surface);

    TTF_CloseFont(font);

    // Main loop
    int quit = 0;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Player 1 input
        int player1;
        printf("Player 1, enter your move (0 for Rock, 1 for Paper, 2 for Scissors): ");
        scanf("%d", &player1);

        // Validate player 1 input
        if (player1 < 0 || player1 > 2) {
            printf("Invalid input for Player 1. Exiting.\n");
            return 1;
        }

        // Get computer's move for player 2
        int player2 = getComputerMove();

        // Render images based on player moves
        SDL_RenderClear(renderer);

        renderTexture(renderer, labelTexture, labelRect.x, labelRect.y);
        renderTexture(renderer, label2Texture, label2Rect.x, label2Rect.y);

        renderTexture(renderer, rockTexture, 50, 50);
        renderTexture(renderer, paperTexture, 300, 50);
        renderTexture(renderer, scissorsTexture, 550, 50);

        renderTexture(renderer, rockTexture, 550, 50);
        renderTexture(renderer, paperTexture, 300, 300);
        renderTexture(renderer, scissorsTexture, 50, 300);

        switch (player1) {
            case 0:
                renderTexture(renderer, rockTexture, 50, 350);
                break;
            case 1:
                renderTexture(renderer, paperTexture, 50, 350);
                break;
            case 2:
                renderTexture(renderer, scissorsTexture, 50, 350);
                break;
        }

        switch (player2) {
            case 0:
                renderTexture(renderer, rockTexture, 550, 350);
                break;
            case 1:
                renderTexture(renderer, paperTexture, 550, 350);
                break;
            case 2:
                renderTexture(renderer, scissorsTexture, 550, 350);
                break;
        }

        // Present the renderer
        SDL_RenderPresent(renderer);

        // Determine the winner
        int result = determineWinner(player1, player2);

        // Display the result
        if (result == 0) {
            printf("It's a tie!\n");
        } else if (result == 1) {
            printf("Player 1 wins!\n");
        } else {
            printf("Player 2 wins!\n");
        }

        // Delay to show the result (in milliseconds)
        SDL_Delay(3000);
    }

    // Free textures and close SDL
    SDL_DestroyTexture(rockTexture);
    SDL_DestroyTexture(paperTexture);
    SDL_DestroyTexture(scissorsTexture);
    SDL_DestroyTexture(labelTexture);
    SDL_DestroyTexture(label2Texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
