/* Uno
Izzah Shafique - 27100032
*/

#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

int deck[6][20] = {
    {100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109}, // Red 10
    {200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209}, // Blue 20
    {300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309}, // Green 30
    {400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409}, // Yellow 40
    {110, 120, 210, 220, 310, 320, 410, 420, 110, 120, 210, 220, 310, 320, 410, 420, 500, 500, 500, 500}, // Wild cards, 2nd digit 1 means skip, 2 means reverse
    {130, 130, 230, 230, 330, 330, 430, 430, 130, 130, 230, 230, 330, 330, 430, 430, 600, 600, 600, 600} // 2nd digit 3 maeans draw 2
};

// Initializing the discard pile
int discard[120];
int discardIndex = 0;

// ANSI escape codes for text color
#define RED_TEXT "\033[1;31m"
#define BLUE_TEXT "\033[1;34m"
#define GREEN_TEXT "\033[1;32m"
#define YELLOW_TEXT "\033[93m"
#define RESET_TEXT "\033[0m"

void refillDeck()
/*
    Once all cards are finished from the deck, this function utilises nested loops to refill the 2D array "deck" from the 1D array "discard"
*/
{
    int k = 0;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            deck[i][j] = discard[k++];
        }
    }
}

void displayDiscardPile()
/*
    Prints out cards that have been thrown as part of the discard pile so that players are able to see identify suitable next move.
    Displays cards according to their respective colors, which are represented by the 1st digit (prefix)
    The variable seconddigit represents value: 1 means skip, 2 means reverse, last digit represents the value of the card
*/
{
    cout << "Discard Pile: "<<endl;
    for (int i = 0; i < discardIndex; i++)
    {
        int prefix = discard[i] / 100;
        int secdigit = (discard[i] / 10) % 10;
        switch (prefix)
        {
        case 1:
            if (secdigit == 1)
            {
                cout << RED_TEXT << "S" << RESET_TEXT << " ";
            }
            else if (secdigit == 2)
            {
                cout << RED_TEXT << "R" << RESET_TEXT << " ";
            }
            else if (secdigit == 3)
            {
                cout << RED_TEXT << "+2" << RESET_TEXT << " ";
            }
            else
            {
                cout << RED_TEXT << discard[i] % 10 << RESET_TEXT << " ";
            }
            break;
        case 2:
            if (secdigit == 1)
            {
                cout << BLUE_TEXT << "S" << RESET_TEXT << " ";
            }
            else if (secdigit == 2)
            {
                cout << BLUE_TEXT << "R" << RESET_TEXT << " ";
            }
            else if (secdigit == 3)
            {
                cout << BLUE_TEXT << "+2" << RESET_TEXT << " ";
            }
            else
            {
                cout << BLUE_TEXT << discard[i] % 10 << RESET_TEXT << " ";
            }
            break;
        case 3:
            if (secdigit == 1)
            {
                cout << GREEN_TEXT << "S" << RESET_TEXT << " ";
            }
            else if (secdigit == 2)
            {
                cout << GREEN_TEXT << "R" << RESET_TEXT << " ";
            }
            else if (secdigit == 3)
            {
                cout << GREEN_TEXT << "+2" << RESET_TEXT << " ";
            }
            else
            {
                cout << GREEN_TEXT << discard[i] % 10 << RESET_TEXT << " ";
            }
            break;
        case 4:
            if (secdigit == 1)
            {
                cout << YELLOW_TEXT << "S" << RESET_TEXT << " ";
            }
            else if (secdigit == 2)
            {
                cout << YELLOW_TEXT << "R" << RESET_TEXT << " ";
            }
            else if (secdigit == 3)
            {
                cout << YELLOW_TEXT << "+2" << RESET_TEXT << " ";
            }
            else
            {
                cout << YELLOW_TEXT << discard[i] % 10 << RESET_TEXT << " ";
            }
            break;
        case 5:
            cout << "W" << " ";
            break;
        case 6:
            cout << "+4" << " ";
        }
    }
    cout << endl;
}

void displayRules()
{
    cout <<endl <<setw(80)<< "WELCOME TO UNO!!!" << endl;
    string response;
    do
    {
        cout << "Would you like to view the rules? (y/n)"<<endl;
        cin >> response;
        if (response == "y" || response == "Y")
        {
            cout << "- The game is for 2 players, ages 7 and over. Every player starts with seven cards. The rest of the cards are placed in a Draw Pile face down. Next to the pile, a space should be designated for a Discard Pile. The top card should be placed in the Discard Pile, and the game begins!" << endl;
            cout << "- Every player views his/her cards and tries to match the card in the Discard Pile." << endl;
            cout << "- You have to match either by the number or color." << endl;
            cout << "- For instance, if the Discard Pile has a red card that is an 8, you have to place either a red card or a card with an 8 on it." << endl;
            cout << "- If the player has no matches or they choose not to play any of their cards even though they might have a match, they must draw a card from the Draw pile. If that card can be played, play it. Otherwise, keep the card, and the game moves on to the next person in turn." << endl;
            cout << "- At any time during the game, if the Draw Pile becomes depleted and no one has yet won the round, take the Discard Pile, shuffle it, and turn it over to regenerate a new Draw Pile." << endl;
            cout << "- Take note that you can only put down one card at a time; you cannot stack two or more cards together on the same turn." << endl;
        }
    } while (response != "y" && response != "Y" && response != "n" && response != "N" );
    cout << "\nLoading Game...\n\n";
}

void displayHand(int* arr, int index)
/*
    Loops through player's hand (using pointers just because we didnt use them anywhere else) and prints cards according to color
*/
{
    for (int i = 0; i < index; i++)
    {
        int prefix = *(arr+i) / 100;
        int secdigit = (*(arr+i) / 10) % 10;
        
        switch (prefix)
        {
        case 1:
            if (secdigit == 1)
            {
                cout << RED_TEXT << "S" << RESET_TEXT << " ";
            }
            else if (secdigit == 2)
            {
                cout << RED_TEXT << "R" << RESET_TEXT << " ";
            }
            else if (secdigit == 3)
            {
                cout << RED_TEXT << "+2" << RESET_TEXT << " ";
            }
            else
            {
                cout << RED_TEXT << *(arr+i) % 10 << RESET_TEXT << " ";
            }
            break;
        case 2:
            if (secdigit == 1)
            {
                cout << BLUE_TEXT << "S" << RESET_TEXT << " ";
            }
            else if (secdigit == 2)
            {
                cout << BLUE_TEXT << "R" << RESET_TEXT << " ";
            }
            else if (secdigit == 3)
            {
                cout << BLUE_TEXT << "+2" << RESET_TEXT << " ";
            }
            else
            {
                cout << BLUE_TEXT << *(arr+i) % 10 << RESET_TEXT << " ";
            }
            break;
        case 3:
            if (secdigit == 1)
            {
                cout << GREEN_TEXT << "S" << RESET_TEXT << " ";
            }
            else if (secdigit == 2)
            {
                cout << GREEN_TEXT << "R" << RESET_TEXT << " ";
            }
            else if (secdigit == 3)
            {
                cout << GREEN_TEXT << "+2" << RESET_TEXT << " ";
            }
            else
            {
                cout << GREEN_TEXT << *(arr+i) % 10 << RESET_TEXT << " ";
            }
            break;
        case 4:
            if (secdigit == 1)
            {
                cout << YELLOW_TEXT << "S" << RESET_TEXT << " ";
            }
            else if (secdigit == 2)
            {
                cout << YELLOW_TEXT << "R" << RESET_TEXT << " ";
            }
            else if (secdigit == 3)
            {
                cout << YELLOW_TEXT << "+2" << RESET_TEXT << " ";
            }
            else
            {
                cout << YELLOW_TEXT << *(arr+i) % 10 << RESET_TEXT << " ";
            }
            break;
        case 5:
            cout << "W"
                 << " ";
            break;
        case 6:
            cout << "+4" << " ";
        
        }
    }
    cout << endl;
}

int pickCard(int b[], int &index)
/*
Uses the rand() function to randomly assign players cards from the 2D array deck, replacing the element in the 2D array by -1
*/
{
    srand(time(0));
    int randomRow, randomCol;

    // Find a non-empty position in the deck
    do
    {
        randomRow = rand() % 6;
        randomCol = rand() % 20;
    } while (deck[randomRow][randomCol] == -1);

    int selectedCard = deck[randomRow][randomCol];

    // Update the deck after picking the card
    deck[randomRow][randomCol] = -1; // You can choose a value that represents an empty position

    b[index++] = selectedCard;

    return selectedCard;
}

void displayDeck()
/*
Displays 2D array deck
*/
{
    cout << "Deck:" << endl;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            cout << deck[i][j] << " ";
        }
        cout << endl;
    }
}

void initializeHand(int arr1[], int arr2[], int &index1, int &index2)
/*
Randomly assigns 7 cards to each player
*/
{
    for (int i = 0; i < 7; i++)
    {
        pickCard(arr1, index1);
        pickCard(arr2, index2);
    }
    cout << "Player 1: " << endl;
    displayHand(arr1, index1);
    cout << endl;
    cout << "Player 2: " << endl;
    displayHand(arr2, index2);
    cout << endl;
}

void throwcard(int b[], int &index, bool &extraTurn, bool& D2, bool& D4)
/*
The function initialises variables for chosen position of the card to be thrown, flags for skip/reverse and variables to store information about color/number of card thrown
Prompts user to input the index of the card they want to throw until they stay within bounds
*/
{
    int position = 0; // Initialize position before using it
    bool skip = false, reverse = false, DrawTwo = false;
    int thrownColor, thrownNumber, secdigit, SecDiscardDigit;
    do
    {
        // Reset extraTurn for the current turn
        extraTurn = false;
        // Reset D2 for the current turn
        D2 = false;
        // Ask user for the index of the card to be thrown
        while (position < 1 || position > index)
        {
            cout << "Enter the index of the card you want to throw: ";
            cin >> position;
        }

        // Validate the color and number of the thrown card with the top card in the discard pile

        // Extracts relevant information about the card thrown
        thrownColor = b[position - 1] / 100;
        thrownNumber = b[position - 1] % 100;
        secdigit = (b[position - 1] / 10) % 10;
        SecDiscardDigit = (discard[discardIndex-1]/10)%10;

        // Checks if the thrown card is a special card (skip/reverse)
        if (secdigit == 1)
        {
            skip = true;
        }
        else if (secdigit == 2)
        {
            reverse = true;
        }
        else if (secdigit == 3)
        {
            DrawTwo = true;
        }
        
        // Check if the color of the skip or reverse matches the color of the top card on the discard pile
        if (discardIndex > 0)
        {
            int topColor = discard[discardIndex - 1] / 100;
            if ((skip && secdigit == 1 && SecDiscardDigit == 1) || (reverse && secdigit == 2 && SecDiscardDigit == 2) || DrawTwo && secdigit == 3 && SecDiscardDigit == 3)
            // If the thrown card and the top card is a skip then it is valid, no need to check any other conditions(same with reverses and Draw 2s)
            {
                continue;
            }
            
            // Check if the color of the skip or reverse matches the color of the top card on the discard pile
            if ((skip && secdigit == 1 && thrownColor != topColor) ||
            (reverse && secdigit == 2 && thrownColor != topColor) ||
            (DrawTwo && secdigit == 3 && thrownColor != topColor)) 
            {
                cout << "Invalid move. The thrown skip or reverse must match the color of the top card on the discard pile." << endl;
                position = 0; // Reset position to ask for input again
                pickCard(b, index);
                displayHand(b, index);
                displayDiscardPile();
            }
            // Check if neither skip nor reverse and the color or number matches
            else if (!skip && !reverse && !DrawTwo && (thrownColor != topColor && thrownNumber != (discard[discardIndex - 1] % 100) && b[position - 1] != 500 && b[position - 1] != 600))
            {
                cout << "Invalid move. The thrown card must match either the color or the number of the top card on the discard pile." << endl;
                position = 0; // Reset position to ask for input again
                pickCard(b, index);
                displayHand(b, index);
                //displayDiscardPile();
            }
        }

    } while (position == 0); // Keep asking until a valid card is entered

    // Add the thrown card to the discard pile
    if (discardIndex < 120)
    {
        discard[discardIndex++] = b[position - 1];
    }
    else
    {
        refillDeck();
    }

    // If a valid skip or reverse is thrown, set extraTurn to true
    if ((skip && secdigit == 1) || (reverse && secdigit == 2))
    {
        extraTurn = true;
    }
    else if (b[position - 1] == 500) // wild card
    {
        char color;
        do
        {
            cout << "Enter a valid color (r/b/g/y): ";
            cin >> color;
        } while (color != 'r' && color != 'b' && color != 'g' && color != 'y');
        /* According to the color user picks, a random card of the same color is added to the discard pile 
        so that the same logic is used to extract information about color to allow next card to be thrown */
        switch (color)
        {
        case 'r':
            discard[discardIndex++] = 150;
            break;
        case 'b':
            discard[discardIndex++] = 250;
            break;
        case 'g':
            discard[discardIndex++] = 350;
            break;
        case 'y':
            discard[discardIndex++] = 450;
            break;
        }
    }
    else if (DrawTwo && secdigit == 3)
    {
        D2 = true;
    }
    else if (b[position - 1] == 600)
    {
        char color;
        do
        {
            cout << "Enter a valid color (r/b/g/y): ";
            cin >> color;
        } while (color != 'r' && color != 'b' && color != 'g' && color != 'y');
        /* According to the color user picks, a random card of the same color is added to the discard pile 
        so that the same logic is used to extract information about color to allow next card to be thrown */
        switch (color)
        {
        case 'r':
            discard[discardIndex++] = 150;
            break;
        case 'b':
            discard[discardIndex++] = 250;
            break;
        case 'g':
            discard[discardIndex++] = 350;
            break;
        case 'y':
            discard[discardIndex++] = 450;
            break;
        }
        D4 = true;
    }

    // Shift all the cards in the hand 1 to the left from where the card was thrown - removes the thrown car from a player's hand
    for (int i = position - 1; i < index - 1; i++)
    {
        b[i] = b[i + 1];
    }
    index--; // Index is 1 less as the effective size of the array has decreased.

    cout << "Hand after turn:" << endl;
    displayHand(b, index);
}

void PlayGame(int &index1, int &index2, int p1[], int p2[])
{
    // Players taking turns to throw cards until either one runs out
    int currentPlayer = 1;    // Player 1 starts
    bool extraTurn = false;   // Flag to track if a skip or reverse was thrown
    bool D2 = false; // Flag to see if draw 2 was thrown, will be used to make other player pick 2 cards
    bool D4 = false; // Flag to see if draw 4 was thrown, will be used to make other player pick 4 cards

    while (index1 > 0 && index2 > 0) // The main loop continues as long as both players have cards in their hands 
    {
        displayDiscardPile();
        cout <<endl;

        if (currentPlayer == 1)
        {
            cout << "Player 1 it is your turn now.\n\n";
            // Display player 1's current cards and call the throwcard function to allow them to make a valid move
            cout << "Your cards: " << endl;
            if (D2 == true)
            {
                pickCard(p1, index1);
                pickCard(p1, index1);
                D2 = false;
            }
            else if (D4 == true)
            {
                pickCard(p1, index1);
                pickCard(p1, index1);
                pickCard(p1, index1);
                pickCard(p1, index1);
                D4 = false;
            }
            
            displayHand(p1, index1);
            cout<<endl;
            throwcard(p1, index1, extraTurn, D2, D4);
        }
        else
        {
            // If it is Player 2's turn, they are shown their cards and prompted to throw allowed cards
            cout << "Player 2 it is your turn now.\n\n";
            cout << "Your cards: " << endl;

            if (D2 == true) // If draw 2 thrown, pickCard function is called twice to add 2 cards to the other player's hand
            {
                pickCard(p2, index2);
                pickCard(p2, index2);
                D2 = false;
            }
            else if (D4 == true) // If draw 4 thrown, pickCard function is called four times to add 4 cards to the other player's hand
            {
                pickCard(p1, index1);
                pickCard(p1, index1);
                pickCard(p1, index1);
                pickCard(p1, index1);
                D4 = false;
            }
            
            displayHand(p2, index2);
            cout<<endl;
            throwcard(p2, index2, extraTurn, D2, D4);
        }

        displayDiscardPile();
        cout << endl;

        // Check if a skip or reverse was thrown to give the player an extra turn
        if (!extraTurn)
        {
            // Switch to the next player
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }
        else
        {
            extraTurn = false; // Reset the extraTurn flag
        }
        
    }
}

void CheckWin(int &index1, int &index2)
{
    // Checking who won by seeing whose cards ran out first

    if (index1 == 0)
    {
        cout << "Player 1 wins." << endl;
    }
    else
    {
        cout << "Player 2 wins." << endl;
    }
}

int main()
{
    // Initializing each player's cards
    int index1 = 0, index2 = 0;
    int p1[120];
    int p2[120];

    displayRules();
    //displayDeck();
    initializeHand(p1, p2, index1, index2);
    PlayGame(index1, index2, p1, p2);
    CheckWin(index1, index2);
    return 0;
}