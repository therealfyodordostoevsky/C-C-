// rock_paper_scissors.h

#ifndef ROCK_PAPER_SCISSORS_H
#define ROCK_PAPER_SCISSORS_H

#define MAX_PLAYERS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
} Player;

void saveScore(Player player);
void displayTopScores();

#endif // ROCK_PAPER_SCISSORS_H
