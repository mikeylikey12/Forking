#include <stdio.h>
#include <stdlib.h>

// Function prototypes
int roll_a_dice();
void play_computer(int *computer_score);
void play_user(int *user_score);
void scoresheet(int computer_score, int user_score);
int calculate_score(int dice1, int dice2, int dice3); // Added function for scoring

int main() {
    // Declare variables
    int rounds, computer_score, user_score;

    // Welcome message
    printf("Welcome to Crag game.\nLet's get started!\n");

    // Get the number of rounds from the user
    printf("How many rounds would you like to play? ");
    scanf("%d", &rounds);

    // Initialize scores
    computer_score = 0;
    user_score = 0;

    // Play the game for the specified number of rounds
    for (int i = 1; i <= rounds; i++) {
        printf("\nRound %d -- Your Turn:\n", i);

        // Play user's turn
        play_user(&user_score);

        printf("\nRound %d -- My Turn:\n", i);
        // Play computer's turn
        play_computer(&computer_score);

        // Display scoresheet
        scoresheet(computer_score, user_score);
    }

    // Determine the winner
    if (computer_score > user_score) {
        printf("\nYOU LOST!\n");
    } else if (computer_score < user_score) {
        printf("\nYOU WON!\n");
    } else {
        printf("\nIT'S A TIE!\n");
    }

    return 0;
}

// Function to simulate rolling a dice
int roll_a_dice() {
    // Generate a random number between 1 and 6
    return (rand() % 6) + 1;
}

// Function to handle the computer's turn
void play_computer(int *computer_score) {
    int dice1, dice2, dice3;

    printf("I rolled the dice and got:\n");

    // Roll the dice for the computer
    dice1 = roll_a_dice();
    dice2 = roll_a_dice();
    dice3 = roll_a_dice();

    printf("-> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d\n", dice1, dice2, dice3);

    // Calculate computer's score
    *computer_score += calculate_score(dice1, dice2, dice3);
    printf("My score: %d Total score: %d\n", calculate_score(dice1, dice2, dice3), *computer_score);
}

// Function to handle the user's turn
void play_user(int *user_score) {
    int dice1, dice2, dice3;

    printf("You rolled the dice and got:\n");

    // Roll the dice for the user
    dice1 = roll_a_dice();
    dice2 = roll_a_dice();
    dice3 = roll_a_dice();

    printf("-> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d\n", dice1, dice2, dice3);

    // Ask the user if they want to re-roll
    char re_roll_choice;
    do {
        printf("Shall I roll for you (Y/N)? ");
        scanf(" %c", &re_roll_choice);

        if (re_roll_choice == 'Y') {
            // Get dice numbers to keep
            int keep1, keep2;
            printf("Which ones do you want to keep? ");
            scanf("%d %d", &keep1, &keep2);

            // Validate input
            if ((keep1 < 1 || keep1 > 3) || (keep2 < 1 || keep2 > 3) || keep1 == keep2) {
                printf("Sorry, wrong input! Please try again.\n");
            } else {
                // Calculate the index of the dice to re-roll
                int re_roll = 6 - keep1 - keep2;

                // Re-roll the unselected dice
                if (re_roll == 1) {
                    dice1 = roll_a_dice();
                } else if (re_roll == 2) {
                    dice2 = roll_a_dice();
                } else {
                    dice3 = roll_a_dice();
                }

                printf("You got:\n-> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d\n", dice1, dice2, dice3);
            }
        } else if (re_roll_choice != 'N') {
            printf("Invalid choice! Please enter Y or N.\n");
        }
    } while (re_roll_choice != 'N');

    // Calculate user's score
    *user_score += calculate_score(dice1, dice2, dice3);
    printf("Your score: %d Total score: %d\n", calculate_score(dice1, dice2, dice3), *user_score);
}

// Function to display the scoresheet
void scoresheet(int computer_score, int user_score) {
    printf("\nScoresheet: A Scoresheet looks as follows:\n");
    printf("Computer     Player 2\n");
    printf("%-11d %-11d\n", computer_score, user_score);
}

// Function to calculate the score based on the dice values
int calculate_score(int dice1, int dice2, int dice3) {
    int score = 0;

    // Check for specific scoring combinations
    if (dice1 == dice2 && dice2 == dice3) { // Three of a kind
        score = dice1 * 10;
    } else if ((dice1 == dice2) || (dice2 == dice3) || (dice1 == dice3)) { // Two of a kind
        score = dice1 + dice2 + dice3 - 6; // Remove the repeated value
    } else if ((dice1 == 1 && dice2 == 2 && dice3 == 3) || // Low Straight
               (dice1 == 4 && dice2 == 5 && dice3 == 6)) { // High Straight
        score = 20;
    } else if ((dice1 == 1 && dice2 == 3 && dice3 == 5) || // Odd Straight
               (dice1 == 2 && dice2 == 4 && dice3 == 6)) { // Even Straight
        score = 20;
    } else if (dice1 + dice2 + dice3 == 13) { // Thirteen
        score = 26;
    } else if (dice1 == 6 && dice2 == 6 && dice3 == 1) { // Crag
        score = 50;
    } else { // Sum
        score = dice1 + dice2 + dice3;
    }

    return score;
}
