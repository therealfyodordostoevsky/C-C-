# Tic-Tac-Toe Game

# Initialize the board
board = [" " for _ in range(9)]

# Function to display the Tic-Tac-Toe board
def display_board():
    print("|", board[0], "|", board[1], "|", board[2], "|")
    print("|", board[3], "|", board[4], "|", board[5], "|")
    print("|", board[6], "|", board[7], "|", board[8], "|")

# Function to check for a win
def check_win(player):
    win_combinations = [(0, 1, 2), (3, 4, 5), (6, 7, 8), (0, 3, 6), (1, 4, 7), (2, 5, 8), (0, 4, 8), (2, 4, 6)]
    for combo in win_combinations:
        if board[combo[0]] == board[combo[1]] == board[combo[2]] == player:
            return True
    return False

# Main game loop
current_player = "X"
while True:
    display_board()
    position = int(input("Player " + current_player + ", choose a position (1-9): ")) - 1

    if board[position] == " ":
        board[position] = current_player
    else:
        print("That position is already taken. Try again.")
        continue

    if check_win(current_player):
        display_board()
        print("Player " + current_player + " wins!")
        break

    if " " not in board:
        display_board()
        print("It's a tie!")
        break

    current_player = "O" if current_player == "X" else "X"