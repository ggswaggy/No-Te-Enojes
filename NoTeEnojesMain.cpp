#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;

struct Data
{
    int redCaps;
    int blueCaps;
    int redWins;
    int blueWins;
};

struct Pawn
{
    char color;
    int boardPosition;
    int ownPosition;
    int start;
    int endLane;
    int shortcut;
};

struct Player
{
    char color;
    Pawn pawns[5];
    int win;
};

void bugFinder(Player *player, int board[], int endVec[], int col, Player redPlayer, Player bluePlayer); //reports if the wrong number of pawns are on the board
int diceRoll(); //returns a random integer between 1 and 6
int checkFull(int vec[]); //checks if a given array is all nonzero
int checkStart(Player *player); //checks if there are any pawns in the starting lane for given player
Pawn *locatePawn(int loc, Player *red, Player *blue); //returns the address of a pawn at a given space
int choosePawnRandom(Player *player, int roll, int board[], int col, int endVec[]); //selects a random, valid pawn to move
int choosePawnAggressive(Player *player, int col, int board[], int roll, int endVec[]); //selects a valid pawn that will send opponent's pawn back to start
int choosePawnDefensive(Player *player, int col, int board[], int roll, int endVec[]); //selects a pawn that can get away from an opponent's pawn and not be sent back
int findShortcutPawn(Player *player); //finds the pawn occupying the shortcut space




int main()
{
    srand(time(NULL));
    //initialize general board
    int board[56];
    //red start: 0
    //blue start: 28
    int i;
    for(i=0;i<56;i++)
        board[i] = 0;
    //0 = empty space ; 1 = red occupied ; 2 = blue occupied
    int shrtcut;
    shrtcut = 0;
    int win; //game end marked by win = 1
    int checkWin;
    win = 0;
    int dice;
    dice = 0;
    int laneCheck;
    laneCheck = 0;
    int sixCounter;
    sixCounter = 0;
    int empt;
    empt = 0;
    int full;
    full = 0;
    int turnDone;
    turnDone = 0;
    int auxPawn;
    auxPawn = -1;
    Pawn *auxPtr;
    auxPtr = 0;
    int dif;
    dif = 0;
    int auxPos;
    auxPos = 0;

    //initialize data counter
    Data counter;
    counter.redCaps = 0;
    counter.blueCaps = 0;
    counter.redWins = 0;
    counter.blueWins = 0;


    //initialize red player
    Pawn r1;
    r1.boardPosition = -1;
    r1.ownPosition = -1;
    r1.color = 'R';
    r1.start = 1;
    r1.endLane = 0;
    r1.shortcut = 0;

    Pawn r2;
    r2.boardPosition = -1;
    r2.ownPosition = -1;
    r2.color = 'R';
    r2.start = 1;
    r2.endLane = 0;
    r2.shortcut = 0;

    Pawn r3;
    r3.boardPosition = -1;
    r3.ownPosition = -1;
    r3.color = 'R';
    r3.start = 1;
    r3.endLane = 0;
    r3.shortcut = 0;

    Pawn r4;
    r4.boardPosition = -1;
    r4.ownPosition = -1;
    r4.color = 'R';
    r4.start = 1;
    r4.endLane = 0;
    r4.shortcut = 0;

    Pawn r5;
    r5.boardPosition = -1;
    r5.ownPosition = -1;
    r5.color = 'R';
    r5.start = 1;
    r5.endLane = 0;
    r5.shortcut = 0;

    Player redPlayer;
    redPlayer.color = 'R';
    redPlayer.pawns[0] = r1;
    redPlayer.pawns[1] = r2;
    redPlayer.pawns[2] = r3;
    redPlayer.pawns[3] = r4;
    redPlayer.pawns[4] = r5;
    redPlayer.win = 0;

    //initialize blue player
    Pawn b1;
    b1.boardPosition = -1;
    b1.ownPosition = -1;
    b1.color = 'B';
    b1.start = 1;
    b1.endLane = 0;
    b1.shortcut = 0;

    Pawn b2;
    b2.boardPosition = -1;
    b2.ownPosition = -1;
    b2.color = 'B';
    b2.start = 1;
    b2.endLane = 0;
    b2.shortcut = 0;

    Pawn b3;
    b3.boardPosition = -1;
    b3.ownPosition = -1;
    b3.color = 'B';
    b3.start = 1;
    b3.endLane = 0;
    b3.shortcut = 0;

    Pawn b4;
    b4.boardPosition = -1;
    b4.ownPosition = -1;
    b4.color = 'B';
    b4.start = 1;
    b4.endLane = 0;
    b4.shortcut = 0;

    Pawn b5;
    b5.boardPosition = -1;
    b5.ownPosition = -1;
    b5.color = 'B';
    b5.start = 1;
    b5.endLane = 0;
    b5.shortcut = 0;


    Player bluePlayer;
    bluePlayer.color = 'B';
    bluePlayer.pawns[0] = b1;
    bluePlayer.pawns[1] = b2;
    bluePlayer.pawns[2] = b3;
    bluePlayer.pawns[3] = b4;
    bluePlayer.pawns[4] = b5;
    bluePlayer.win = 0;

    //initialize starting lanes
    int redStart[5];
    for(i=0;i<5;i++)
        redStart[i] = 1;
    int blueStart[5];
    for(i=0;i<5;i++)
        blueStart[i] = 2;

    //initialize ending lanes
    int redEnd[5];
    for(i=0;i<5;i++)
        redEnd[i] = 0;
    int blueEnd[5];
    for(i=0;i<5;i++)
        blueEnd[i] = 0;


    int randomStart;

    int r;
    r = 0;
    for(r=0;r<1000000;r++)
    {
        randomStart = rand() % 2;
        while(win!=1)
        {
            //red turn
            if(randomStart == 1)
            {
                turnDone = 1;
                randomStart = 0;
            }
            while(turnDone!=1)
            {
                bugFinder(&redPlayer, board, redEnd, 1, redPlayer, bluePlayer);
                bugFinder(&bluePlayer, board, blueEnd, 2, redPlayer, bluePlayer);


                dice = diceRoll();
                laneCheck = 0;
                for(i=0;i<5;i++) //checks to see if any pawns are in the starting lane
                {
                    if(redPlayer.pawns[i].start == 1)
                        laneCheck = 1;
                }
                if((dice == 6 && board[0] == 1 && laneCheck != 0) || (dice == 6 && laneCheck == 0)) //increments six counter if not used to take a pawn out
                    sixCounter++;
                if(sixCounter == 3) //rolling 6 three times in a row takes your furthest pawn back to the starting lane
                {
                    auxPawn = 0;
                    auxPos = 0;
                    for(i=0;i<5;i++)
                    {
                        if(redPlayer.pawns[i].ownPosition > auxPos && redPlayer.pawns[i].shortcut == 0 && redPlayer.pawns[i].endLane == 0 && redPlayer.pawns[i].start == 0)
                        {
                            auxPawn = i;
                            auxPos = redPlayer.pawns[i].ownPosition;
                        }
                    }
                    if(auxPos == 0)
                        break;
                    board[redPlayer.pawns[auxPawn].boardPosition] = 0;
                    redPlayer.pawns[auxPawn].boardPosition = -1;
                    redPlayer.pawns[auxPawn].ownPosition = -1;
                    redPlayer.pawns[auxPawn].start = 1;
                    turnDone = 1;
                    break;
                }
                if((dice == 6 || dice == 1) && board[0] != 1 && turnDone != 1) //new pawn taken out if 6 or 1 is rolled and space isn't blocked
                {
                    auxPawn = checkStart(&redPlayer);
                    if(auxPawn == -1)
                        turnDone = 0;
                    else
                    {
                        auxPtr = locatePawn(0, &redPlayer, &bluePlayer);
                        if(auxPtr == NULL)
                        {
                            redPlayer.pawns[auxPawn].boardPosition = 0;
                            redPlayer.pawns[auxPawn].ownPosition = 0;
                            redPlayer.pawns[auxPawn].start = 0;
                            board[0] = 1;
                            turnDone = 1;
                        }
                        else
                        {
                            counter.redCaps++;
                            auxPtr->boardPosition = -1;
                            auxPtr->ownPosition = -1;
                            auxPtr->start = 1;
                            redPlayer.pawns[auxPawn].boardPosition = 0;
                            redPlayer.pawns[auxPawn].ownPosition = 0;
                            redPlayer.pawns[auxPawn].start = 0;
                            board[0] = 1;
                            turnDone = 1;
                        }
                    }
                    dice = 1; //this doesn't count as a "new turn" 6 roll, dice value is changed so turn isn't repeated
                }
                if(dice == 1 && shrtcut == 1 && board[47] != 1 && turnDone != 1) //get out of shortcut space
                {
                    auxPawn = findShortcutPawn(&redPlayer);
                    if(auxPawn == -1)
                    {
                        turnDone = 0;
                    }
                    else
                    {
                        if(board[47] == 2) //change this for 4 players
                        {
                            counter.redCaps++;
                            auxPtr = locatePawn(47, &redPlayer, &bluePlayer);
                            auxPtr->boardPosition = -1;
                            auxPtr->ownPosition = -1;
                            auxPtr->start = 1;
                        }
                        redPlayer.pawns[auxPawn].shortcut = 0;
                        redPlayer.pawns[auxPawn].boardPosition = 47;
                        redPlayer.pawns[auxPawn].ownPosition = 47;
                        shrtcut = 0;
                        board[47] = 1;
                        turnDone = 1;
                    }
                }
                if(turnDone != 1)
                {
                    //!!! these are the different strategies, simply comment the ones that won't be taken and uncomment the one that will be
                    //random choice:
                    //auxPawn = choosePawnRandom(&redPlayer, dice, board, 1, redEnd);

                    //aggressive choice:
                    /*auxPawn = choosePawnAggressive(&redPlayer, 1, board, dice, redEnd);
                    if(auxPawn == -1)
                        auxPawn = choosePawnRandom(&redPlayer, dice, board, 1, redEnd); //if no aggressive move available, choose random*/

                    //defensive choice:
                    auxPawn = choosePawnDefensive(&redPlayer, 1, board, dice, redEnd);
                    if(auxPawn == -1) //if no valid pawn is chosen by the strategy, default to random choice
                        auxPawn = choosePawnRandom(&redPlayer, dice, board, 1, redEnd);//*/

                    if(auxPawn == -1) //if no valid pawn is available at all, skip turn
                        turnDone = 1;
                    else //if valid pawn was chosen, move the pawn
                    {
                        if(((redPlayer.pawns[auxPawn].boardPosition + dice) % 56) == 6 && shrtcut == 0) //places pawn in shortcut space if unoccupied
                        {
                            board[redPlayer.pawns[auxPawn].boardPosition] = 0;
                            redPlayer.pawns[auxPawn].shortcut = 1;
                            redPlayer.pawns[auxPawn].ownPosition = 200;
                            redPlayer.pawns[auxPawn].boardPosition = 200;
                            shrtcut = 1;
                            turnDone = 1;
                        }
                        else if(redPlayer.pawns[auxPawn].ownPosition + dice > 54) //changes movement mechanics if in the final lane (allows hopping)
                        {
                            if(redPlayer.pawns[auxPawn].endLane == 1)
                            {
                                redEnd[redPlayer.pawns[auxPawn].ownPosition - 55] = 0;
                                redEnd[redPlayer.pawns[auxPawn].ownPosition - 55 + dice] = 1;
                                redPlayer.pawns[auxPawn].ownPosition += dice;
                                turnDone = 1;
                            }
                            else
                            {
                                dif = 55 - redPlayer.pawns[auxPawn].ownPosition;
                                redEnd[dice - dif] = 1;
                                board[redPlayer.pawns[auxPawn].boardPosition] = 0;
                                redPlayer.pawns[auxPawn].boardPosition = 100;
                                redPlayer.pawns[auxPawn].ownPosition += dice;
                                redPlayer.pawns[auxPawn].endLane = 1;
                                turnDone = 1;
                            }
                        }
                        else
                        {
                            auxPtr = locatePawn((redPlayer.pawns[auxPawn].boardPosition + dice) % 56, &redPlayer, &bluePlayer); //finds opponent pawn to return to start if necessary
                            if(auxPtr == NULL) //if none found, simply occupy the space
                            {
                                board[redPlayer.pawns[auxPawn].boardPosition + dice] = 1;
                                board[redPlayer.pawns[auxPawn].boardPosition] = 0;
                                redPlayer.pawns[auxPawn].boardPosition = (redPlayer.pawns[auxPawn].boardPosition + dice) % 56;
                                redPlayer.pawns[auxPawn].ownPosition += dice;
                                turnDone = 1;
                            }
                            else //if one is found, send it back then occupy the space
                            {
                                counter.redCaps++;
                                auxPtr->boardPosition = -1;
                                auxPtr->ownPosition = -1;
                                auxPtr->start = 1;
                                board[redPlayer.pawns[auxPawn].boardPosition + dice] = 1;
                                board[redPlayer.pawns[auxPawn].boardPosition] = 0;
                                redPlayer.pawns[auxPawn].boardPosition = (redPlayer.pawns[auxPawn].boardPosition + dice) % 56;
                                redPlayer.pawns[auxPawn].ownPosition += dice;
                                turnDone = 1;
                            }
                        }
                    }
                }

                if(dice == 6) //6 roll grants new turn (recall that taking a new pawn out changes this value)
                    turnDone = 0;

                checkWin = checkFull(redEnd); //if the final lane is full, game has been won
                if(checkWin == 1)
                {
                    redPlayer.win = 1;
                    win = 1;
                }
                checkWin = checkFull(blueEnd); //same here but for the blue player
                if(checkWin == 1)
                {
                    bluePlayer.win = 1;
                    win = 1;
                }
            }
            sixCounter = 0;
            turnDone = 0;


            //blue turn
            //note that, even if red has already won, blue plays. this doesn't mess with the results as will be noted later
            //blue turn code is identical to the red turn code, just switching labels (starting space for blue is 28 instead of 0)
            while(turnDone!=1)
            {
                dice = diceRoll();
                laneCheck = 0;
                for(i=0;i<5;i++)
                {
                    if(bluePlayer.pawns[i].start == 1)
                        laneCheck = 1;
                }
                if((dice == 6 && board[28] == 2 && laneCheck != 0) || (dice == 6 && laneCheck == 0))
                    sixCounter++;
                if(sixCounter == 3)
                {
                    auxPawn = 0;
                    auxPos = 0;
                    for(i=0;i<5;i++)
                    {
                        if(bluePlayer.pawns[i].ownPosition > auxPos && bluePlayer.pawns[i].shortcut == 0 && bluePlayer.pawns[i].endLane == 0 && bluePlayer.pawns[i].start == 0)
                        {
                            auxPawn = i;
                            auxPos = bluePlayer.pawns[i].ownPosition;
                        }
                    }
                    if(auxPos == 0)
                        break;
                    board[bluePlayer.pawns[auxPawn].boardPosition] = 0;
                    bluePlayer.pawns[auxPawn].boardPosition = -1;
                    bluePlayer.pawns[auxPawn].ownPosition = -1;
                    bluePlayer.pawns[auxPawn].start = 1;
                    turnDone = 1;
                    break;
                }
                if((dice == 6 || dice == 1) && board[28] != 2 && turnDone != 1)
                {
                    auxPawn = checkStart(&bluePlayer);
                    if(auxPawn == -1)
                        turnDone = 0;
                    else
                    {
                        auxPtr = locatePawn(28, &redPlayer, &bluePlayer);
                        if(auxPtr == NULL)
                        {
                            bluePlayer.pawns[auxPawn].boardPosition = 28;
                            bluePlayer.pawns[auxPawn].ownPosition = 0;
                            bluePlayer.pawns[auxPawn].start = 0;
                            board[28] = 2;
                            turnDone = 1;
                        }
                        else
                        {
                            counter.blueCaps++;
                            auxPtr->boardPosition = -1;
                            auxPtr->ownPosition = -1;
                            auxPtr->start = 1;
                            bluePlayer.pawns[auxPawn].boardPosition = 28;
                            bluePlayer.pawns[auxPawn].ownPosition = 0;
                            bluePlayer.pawns[auxPawn].start = 0;
                            board[28] = 2;
                            turnDone = 1;
                        }
                    }
                    dice = 1;
                }
                if(dice == 1 && shrtcut == 2 && board[19] != 2 && turnDone != 1) //get out of shortcut space
                {
                    auxPawn = findShortcutPawn(&bluePlayer);
                    if(auxPawn == -1)
                    {
                        turnDone = 0;
                    }
                    else
                    {
                        if(board[19] == 1)
                        {
                            counter.blueCaps++;
                            auxPtr = locatePawn(19, &redPlayer, &bluePlayer);
                            auxPtr->boardPosition = -1;
                            auxPtr->ownPosition = -1;
                            auxPtr->start = 1;
                        }
                        bluePlayer.pawns[auxPawn].shortcut = 0;
                        bluePlayer.pawns[auxPawn].boardPosition = 19;
                        bluePlayer.pawns[auxPawn].ownPosition = 47;
                        shrtcut = 0;
                        board[19] = 2;
                        turnDone = 1;
                    }
                }
                if(turnDone != 1)
                {
                    //random choice:
                    //auxPawn = choosePawnRandom(&bluePlayer, dice, board, 2, blueEnd);

                    //aggressive choice:
                    /*auxPawn = choosePawnAggressive(&bluePlayer, 2, board, dice, blueEnd);
                    if(auxPawn == -1)
                        auxPawn = choosePawnRandom(&bluePlayer, dice, board, 2, blueEnd); //if no aggressive move available, choose random*/

                    //defensive choice:
                    auxPawn = choosePawnDefensive(&bluePlayer, 2, board, dice, blueEnd);
                    if(auxPawn == -1)
                        auxPawn = choosePawnRandom(&bluePlayer, dice, board, 2, blueEnd);//*/

                    if(auxPawn == -1)
                        turnDone = 1;

                    else
                    {
                        if(((bluePlayer.pawns[auxPawn].boardPosition + dice) % 56) == 34 && shrtcut == 0)
                        {
                            board[bluePlayer.pawns[auxPawn].boardPosition] = 0;
                            bluePlayer.pawns[auxPawn].shortcut = 1;
                            bluePlayer.pawns[auxPawn].ownPosition = 200;
                            bluePlayer.pawns[auxPawn].boardPosition = 200;
                            shrtcut = 2;
                            turnDone = 1;
                        }
                        else if(bluePlayer.pawns[auxPawn].ownPosition + dice > 54)
                        {
                            if(bluePlayer.pawns[auxPawn].endLane == 1)
                            {
                                blueEnd[bluePlayer.pawns[auxPawn].ownPosition - 55] = 0;
                                blueEnd[bluePlayer.pawns[auxPawn].ownPosition - 55 + dice] = 2;
                                bluePlayer.pawns[auxPawn].ownPosition += dice;
                                turnDone = 1;
                            }
                            else
                            {
                                dif = 55 - bluePlayer.pawns[auxPawn].ownPosition;
                                blueEnd[dice - dif] = 2;
                                board[bluePlayer.pawns[auxPawn].boardPosition] = 0;
                                bluePlayer.pawns[auxPawn].boardPosition = 100;
                                bluePlayer.pawns[auxPawn].ownPosition += dice;
                                bluePlayer.pawns[auxPawn].endLane = 1;
                                turnDone = 1;
                            }
                        }
                        else
                        {
                            auxPtr = locatePawn((bluePlayer.pawns[auxPawn].boardPosition + dice) % 56, &redPlayer, &bluePlayer);
                            if(auxPtr == NULL)
                            {
                                board[((bluePlayer.pawns[auxPawn].boardPosition + dice) % 56)] = 2;
                                board[bluePlayer.pawns[auxPawn].boardPosition] = 0;
                                bluePlayer.pawns[auxPawn].boardPosition = (bluePlayer.pawns[auxPawn].boardPosition + dice) % 56;
                                bluePlayer.pawns[auxPawn].ownPosition += dice;
                                turnDone = 1;
                            }
                            else
                            {
                                counter.blueCaps++;
                                auxPtr->boardPosition = -1;
                                auxPtr->ownPosition = -1;
                                auxPtr->start = 1;
                                board[((bluePlayer.pawns[auxPawn].boardPosition + dice) % 56)] = 2;
                                board[bluePlayer.pawns[auxPawn].boardPosition] = 0;
                                bluePlayer.pawns[auxPawn].boardPosition = (bluePlayer.pawns[auxPawn].boardPosition + dice) % 56;
                                bluePlayer.pawns[auxPawn].ownPosition += dice;
                                turnDone = 1;
                            }
                        }
                    }
                }

                if(dice == 6)
                    turnDone = 0;

                checkWin = checkFull(redEnd);
                if(checkWin == 1)
                {
                    redPlayer.win = 1;
                    win = 1;
                }
                checkWin = checkFull(blueEnd);
                if(checkWin == 1)
                {
                    bluePlayer.win = 1;
                    win = 1;
                }
            }

            //end blue turn
            sixCounter = 0;
            turnDone = 0;
            //getchar();


        }
        //here is where we fix the worry that the blue player a turn may play after the red player has won
        //the code checks for a red win first, so even if the blue player finishes in that one extra turn, it isn't counted as a win
        if(redPlayer.win == 1)
        {
            counter.redWins++;
        }
        else if(bluePlayer.win == 1)
        {
            counter.blueWins++;
        }


        // reinitialize

        //initialize general board

        for(i=0;i<56;i++)
            board[i] = 0;
        shrtcut = 0;
        win = 0;
        dice = 0;
        laneCheck = 0;
        sixCounter = 0;
        empt = 0;
        full = 0;
        turnDone = 0;
        auxPawn = -1;
        auxPtr = 0;
        dif = 0;
        auxPos = 0;


        //initialize red player
        r1.boardPosition = -1;
        r1.ownPosition = -1;
        r1.color = 'R';
        r1.start = 1;
        r1.endLane = 0;
        r1.shortcut = 0;

        r2.boardPosition = -1;
        r2.ownPosition = -1;
        r2.color = 'R';
        r2.start = 1;
        r2.endLane = 0;
        r2.shortcut = 0;

        r3.boardPosition = -1;
        r3.ownPosition = -1;
        r3.color = 'R';
        r3.start = 1;
        r3.endLane = 0;
        r3.shortcut = 0;

        r4.boardPosition = -1;
        r4.ownPosition = -1;
        r4.color = 'R';
        r4.start = 1;
        r4.endLane = 0;
        r4.shortcut = 0;

        r5.boardPosition = -1;
        r5.ownPosition = -1;
        r5.color = 'R';
        r5.start = 1;
        r5.endLane = 0;
        r5.shortcut = 0;

        redPlayer.color = 'R';
        redPlayer.pawns[0] = r1;
        redPlayer.pawns[1] = r2;
        redPlayer.pawns[2] = r3;
        redPlayer.pawns[3] = r4;
        redPlayer.pawns[4] = r5;
        redPlayer.win = 0;

        //initialize blue player
        b1.boardPosition = -1;
        b1.ownPosition = -1;
        b1.color = 'B';
        b1.start = 1;
        b1.endLane = 0;
        b1.shortcut = 0;

        b2.boardPosition = -1;
        b2.ownPosition = -1;
        b2.color = 'B';
        b2.start = 1;
        b2.endLane = 0;
        b2.shortcut = 0;

        b3.boardPosition = -1;
        b3.ownPosition = -1;
        b3.color = 'B';
        b3.start = 1;
        b3.endLane = 0;
        b3.shortcut = 0;

        b4.boardPosition = -1;
        b4.ownPosition = -1;
        b4.color = 'B';
        b4.start = 1;
        b4.endLane = 0;
        b4.shortcut = 0;

        b5.boardPosition = -1;
        b5.ownPosition = -1;
        b5.color = 'B';
        b5.start = 1;
        b5.endLane = 0;
        b5.shortcut = 0;

        bluePlayer.color = 'B';
        bluePlayer.pawns[0] = b1;
        bluePlayer.pawns[1] = b2;
        bluePlayer.pawns[2] = b3;
        bluePlayer.pawns[3] = b4;
        bluePlayer.pawns[4] = b5;
        bluePlayer.win = 0;

        //initialize starting lanes
        for(i=0;i<5;i++)
            redStart[i] = 1;
        for(i=0;i<5;i++)
            blueStart[i] = 2;

        //initialize ending lanes
        for(i=0;i<5;i++)
            redEnd[i] = 0;
        for(i=0;i<5;i++)
            blueEnd[i] = 0;
    }

    cout << endl << endl << "stats: " << endl;
    cout << "blue caps: " << counter.blueCaps << endl;
    cout << "blue wins: " << counter.blueWins << endl;
    cout << "red caps: " << counter.redCaps << endl;
    cout << "red wins: " << counter.redWins << endl;

    return 0;
}


int diceRoll()
{
    return(((rand() % 6) + 1));
}

int checkFull(int vec[])
{
    int k;
    for(k = 0; k<5; k++)
    {
        if(vec[k] == 0)
            return 0;
    }
    return 1;
}

int checkStart(Player *player)
{
    int i;
    for(i=0;i<5;i++)
    {
        if(player->pawns[i].start == 1)
            return i;
    }
    return -1;
}

Pawn *locatePawn(int loc, Player *red, Player *blue)
{
    int i;
    for(i=0;i<5;i++)
    {
        if(red->pawns[i].boardPosition == loc)
            return &(red->pawns[i]);
    }
    for(i=0;i<5;i++)
    {
        if(blue->pawns[i].boardPosition == loc)
            return &(blue->pawns[i]);
    }
    return 0;
}

int findShortcutPawn(Player *player)
{
    int i;
    for(i=0;i<5;i++)
    {
        if(player->pawns[i].shortcut == 1)
            return i;
    }
    return -1;
}

int choosePawnRandom(Player *player, int roll, int board[], int col, int endVec[])
{
    int order[5];
    int i;
    int j;
    int dif;
    int valid;
    int aux;
    int cont;
    cont = -1;
    for(i=0;i<5;i++)
        order[i] = -1;
    for(i=0;i<5;i++)
    {
        cont = -1;
        while(cont != 1)
        {
            aux = rand() % 5;
            if(order[0] == aux || order[1] == aux || order[2] == aux || order[3] == aux || order[4] == aux)
                continue;
            else
            {
                order[i] = aux;
                cont = 1;
            }
        }
    }
    valid = 1;
    for(i=0;i<5;i++)
    {
        for(j=1;j<=roll;j++)
        {
            if(player->pawns[order[i]].endLane == 1)
            {
                if(endVec[player->pawns[order[i]].ownPosition - 55 + roll] == col || player->pawns[order[i]].ownPosition + roll > 59)
                    valid = -1;
            }
            else if(player->pawns[order[i]].ownPosition + j > 54)
            {
                dif = 55 - player->pawns[order[i]].ownPosition;
                if(endVec[roll - dif] == col || player->pawns[order[i]].ownPosition + roll > 59)
                    valid = -1;
            }
            else if(board[player->pawns[order[i]].boardPosition + j] == col)
                valid = -1;
            else if(player->pawns[order[i]].shortcut == 1)
                valid = -1;
        }
        if(valid == 1 && player->pawns[order[i]].start != 1)
            return order[i];
        valid = 1;
    }
    return -1;
}

int choosePawnAggressive(Player *player, int col, int board[], int roll, int endVec[])
{
    int i;
    int j;
    int auxPos;
    int flag;
    int valid;
    int dif;
    dif = 0;
    valid = 0;
    flag = 0;

    for(i=0;i<56;i++)
    {
        if(board[i] == col)
            flag++;
    }
    if(flag == 0)
        return -1;

    for(i=0;i<5;i++)
    {
        if(player->pawns[i].start == 1 || player->pawns[i].endLane == 1 || player->pawns[i].shortcut == 1)
            continue;
        else
        {
            valid = 1;
            for(i=0;i<5;i++)
            {
                for(j=1;j<=roll;j++)
                {
                    if(player->pawns[i].ownPosition + j > 54)
                    {
                        dif = 55 - player->pawns[i].ownPosition;
                        if(endVec[roll - dif] == col || player->pawns[i].ownPosition + roll > 59)
                            valid = -1;
                    }
                    else if(board[player->pawns[i].boardPosition + j] == col)
                        valid = -1;
                    else if(player->pawns[i].start == 1)
                        valid = -1;
                }
                if(valid == 1)
                {
                    auxPos = player->pawns[i].boardPosition;
                    auxPos = (auxPos + roll) % 56;
                    if(board[auxPos] != 0 && board[auxPos] != col && player->pawns[i].ownPosition + roll < 55)
                        return i;
                }
                valid = 1;
            }
        }
    }
    return -1;
}

int choosePawnDefensive(Player* player, int col, int board[], int roll, int endVec[])
{
    int i;
    int j;
    int k;
    int auxPos;
    int dist;
    int neg;
    int valid;
    int dif;
    int flag;
    flag = 0;
    dif = 0;
    valid = 1;
    neg = 0;
    dist = 0;

    for(i=0;i<56;i++)
    {
        if(board[i] == col)
            flag++;
    }
    if(flag == 0)
        return -1;

    for(i=0;i<5;i++)
    {
        if(player->pawns[i].start == 1 || player->pawns[i].endLane == 1 || player->pawns[i].shortcut == 1)
            continue;
        else
        {
            valid = 1;
            for(i=0;i<5;i++)
            {
                for(j=1;j<=roll;j++)
                {
                    if(player->pawns[i].ownPosition + j > 54)
                    {
                        dif = 55 - player->pawns[i].ownPosition;
                        if(endVec[roll - dif] == col || player->pawns[i].ownPosition + roll > 59)
                            valid = -1;
                    }
                    else if(board[player->pawns[i].boardPosition + j] == col)
                        valid = -1;
                    else if(player->pawns[i].start == 1)
                        valid = -1;
                }
                if(valid == 1)
                {
                    auxPos = player->pawns[i].boardPosition;
                    for(k=1;k<=6;k++)
                    {
                        if(auxPos - k < 0)
                            neg = 56 + (auxPos - k);
                        else
                            neg = auxPos - k;
                        if(board[neg] != 0 && board[neg] != col)
                        {
                            dist = k;
                            if(dist + roll > 6)
                                return i;
                        }
                    }
                }
                valid = 1;
            }
        }
    }
    return -1;
}

void bugFinder(Player *player, int board[], int endVec[], int col, Player redPlayer, Player bluePlayer)
{
    int i;
    int sum;
    sum = 0;
    for(i=0;i<56;i++)
    {
        if(board[i] == col)
            sum++;
    }
    for(i=0;i<5;i++)
    {
        if(player->pawns[i].start == 1)
            sum++;
        if(player->pawns[i].shortcut == 1)
            sum++;
        if(endVec[i] == col)
            sum++;
    }
    if(sum != 5)
    {
        getchar();
        cout << endl << endl << "bug" << endl << endl;

        cout << endl;
        cout << "Red Stats: " << endl;

        cout << "r1:   " << "own pos: " << redPlayer.pawns[0].ownPosition << " || board pos: " << redPlayer.pawns[0].ownPosition << " || start: " << redPlayer.pawns[0].start << " || end: " << redPlayer.pawns[0].endLane;
        cout << " || shrtcut: " << redPlayer.pawns[0].shortcut << endl << endl;

        cout << "r2:   " << "own pos: " << redPlayer.pawns[1].ownPosition << " || board pos: " << redPlayer.pawns[1].ownPosition << " || start: " << redPlayer.pawns[1].start << " || end: " << redPlayer.pawns[1].endLane;
        cout << " || shrtcut: " << redPlayer.pawns[1].shortcut << endl << endl;

        cout << "r3:   " << "own pos: " << redPlayer.pawns[2].ownPosition << " || board pos: " << redPlayer.pawns[2].ownPosition << " || start: " << redPlayer.pawns[2].start << " || end: " << redPlayer.pawns[2].endLane;
        cout << " || shrtcut: " << redPlayer.pawns[2].shortcut << endl << endl;

        cout << "r4:   " << "own pos: " << redPlayer.pawns[3].ownPosition << " || board pos: " << redPlayer.pawns[3].ownPosition << " || start: " << redPlayer.pawns[3].start << " || end: " << redPlayer.pawns[3].endLane;
        cout << " || shrtcut: " << redPlayer.pawns[3].shortcut << endl << endl;

        cout << "r5:   " << "own pos: " << redPlayer.pawns[4].ownPosition << " || board pos: " << redPlayer.pawns[4].ownPosition << " || start: " << redPlayer.pawns[4].start << " || end: " << redPlayer.pawns[4].endLane;
        cout << " || shrtcut: " << redPlayer.pawns[4].shortcut << endl << endl;

        cout << endl;
        cout << "Blue Stats: " << endl;

        cout << "b1:   " << "own pos: " << bluePlayer.pawns[0].ownPosition << " || board pos: " << bluePlayer.pawns[0].ownPosition << " || start: " << bluePlayer.pawns[0].start << " || end: " << bluePlayer.pawns[0].endLane;
        cout << " || shrtcut: " << bluePlayer.pawns[0].shortcut << endl << endl;

        cout << "b2:   " << "own pos: " << bluePlayer.pawns[1].ownPosition << " || board pos: " << bluePlayer.pawns[1].ownPosition << " || start: " << bluePlayer.pawns[1].start << " || end: " << bluePlayer.pawns[1].endLane;
        cout << " || shrtcut: " << bluePlayer.pawns[1].shortcut << endl << endl;

        cout << "b3:   " << "own pos: " << bluePlayer.pawns[2].ownPosition << " || board pos: " << bluePlayer.pawns[2].ownPosition << " || start: " << bluePlayer.pawns[2].start << " || end: " << bluePlayer.pawns[2].endLane;
        cout << " || shrtcut: " << bluePlayer.pawns[2].shortcut << endl << endl;

        cout << "b4:   " << "own pos: " << bluePlayer.pawns[3].ownPosition << " || board pos: " << bluePlayer.pawns[3].ownPosition << " || start: " << bluePlayer.pawns[3].start << " || end: " << bluePlayer.pawns[3].endLane;
        cout << " || shrtcut: " << bluePlayer.pawns[3].shortcut << endl << endl;

        cout << "b5:   " << "own pos: " << bluePlayer.pawns[4].ownPosition << " || board pos: " << bluePlayer.pawns[4].ownPosition << " || start: " << bluePlayer.pawns[4].start << " || end: " << bluePlayer.pawns[4].endLane;
        cout << " || shrtcut: " << bluePlayer.pawns[4].shortcut << endl << endl;
    }
}
