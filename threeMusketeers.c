/**
 * @mainpage HomeWork1-ThreeMusketeers
 * 
 * @author Michalis Christodoulou
 * 
 * The Three Musketeers is a strategic board game. The board consists of 3 musketeers and 22 soldiers.
 * Players take turns and are allowed to move, their piece up, down, right and left.
 * Musketeers win when there are not enemies on the neighbour blocks.
 * Soldiers win, when they can make the all three Musketeers go on the same row or collumn.
 * 
 * @bug No known bugs.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define N 5

/**
 * @brief Reads the board from a file.
 * 
 * This function reads the board from a file, given by the user on the command line.
 * It checks if the number of arguements is correct and if the input file given by the user exists.
 * If any of the above is not correct, the function prints an error message and returns false, else returns true.
 * 
 * @param board The 2D character array that represents the game board.
 * @param argc The number of command-line arguements.
 * @param argv The command-line arguement  -  name of the input file.
*/
bool readBoard(char board[N][N], int argc, char **argv);

/**
 * @brief Displays the board in the console.
 * 
 * This function prints the current state of your board to the console.
 * 
 * @param board The 2D character array that represents the game board.
 */
void displayBoard(char board[N][N]);

/**
 * @brief Reads and chacks the player's move.
 * 
 * This function reads the players move, and checks it's format.
 * While there is a mistake, a mistake message is printed and the user is asked to make a new move.
 * 
 * @param str A character array to store the players input.
 * @param player The player that makes a move('M' - Musketeer, 'o' soldier).
 * @return false Returns false when player wants to exit the game.
 * @return true Returns true when player does not want to exit the game.
 */
bool readInputMove(char *str, char player);

/**
 * @brief Checks if the destination block is correct.
 * 
 * Checks if the destination block for Musketeers is 'o' and if
 * the destination block for the enemy is '.'.
 * 
 * @param player The player that makes a move('M' - Musketeer, 'o' soldier).
 * @param destinationBlock The character in the destination block.
 * @return true Returns true when destination is valid.
 * @return false Returns false when destination block is not valid.
 */
bool checkDestinationBlock(char player, char destinationBlock);

/**
 * @brief Check if the current block is valid.
 * 
 * Check if the block that is trying to by moved is a Musketeer, when musketeer makes a move,
 * and check if it is a soldier, when the enemy makes a move.
 * 
 * @param player The player that makes a move('M' - Musketeer, 'o' soldier).
 * @param currentBlock The character in the current block.
 * @return true Returns true when character in the current block is valid.
 * @return false Returns false when character in the current block is not valid.
 */
bool checkCurrentBlock(char player, char currentBlock);

/**
 * @brief Checks if the move is in the board limit.
 * 
 * The function checks if the direction the user gives, takes the piece out of the board limits.
 * 
 * @param row The row character of the current piece.
 * @param col The collumn character of the current piece.
 * @param direction The direction character(U\u D\d R\r L\l).
 * @return true Returns true if the move is within the board limits.
 * @return false Returns false if the move is not within the board limits.
 */
bool checkBoardLimit(char row, char col, char direction);

/**
 * @brief Converts row input.
 * 
 * This function converts the row input to its integer equivalent to control the board.
 * 
 * @param row The row character.
 * @return char The integer representation of the row character.
 */
char convertRowInput(char row);

/**
 * @brief Moves the player's piece on the board.
 * 
 * This function moves the player's piece on the board after checking if the move is valid.
 * It calls the functions checkBoardLimit, readInputMove, checkCurrentBlock, checkDestinationBlock to check if the move is valid.
 * If the move is not valid, it prints error message and asks for player make a move again, and repeats until given move is correct.
 * When correct input is given, the destination blocks of Musketeers become 'M' and 'o' for soldiers. Their previous blocks, become empty('.').
 * 
 * @param input The players input move.
 * @param board The 2D character array that represents the game board.
 * @param player The player that makes the move('M' - Musketeer, 'o' soldier).
 * @return false Returns false, if player wants to exit the game - If readInputMove returns false, moveBoard returns false too, to exit the program in main.
 * @return true Returns true, if player does not want to exit the game.
 */
bool moveBoard(char input[6], char board[N][N], char player);

/**
 * @brief Check for winner in the game.
 * 
 * This function checks if there is a winner in the game.
 * Checks if there is a line or a collumn with 3 musketeers to find if The soldiers of Richeliu won.
 * Checks if Musketeers have no neighbour soldiers to move, to find if Musketeers won.
 * If there is a winner, a message is printed.
 * 
 * @param board The 2D character array that represents the game board.
 * @return true Returns true if winner is found.
 * @return false Returns false if winner if not found.
 */
bool checkForWinner(char board[N][N]);

/**
 * @brief Starts the game.
 * 
 * This function, manages the game loop and player turns.
 * Calls the readInputMove function to ask the player for input, the moveBoard function to 
 * make changes to the board, and the checkForWinner function to determine whether loop is going to continue.
 * 
 * @param board The 2D character array that represents the game board.
 */
void play(char board[N][N]);

/**
 * @brief Writes the current board state to a file.
 * 
 * After game is done, this function is called to save the final board to
 * a file with name "out-input-file.txt" where input-file.txt is the file that user typed on the command line
 * before the start of the game.
 * 
 * @param board The 2D character array that represents the game board.
 * @param argv The command-line arguement  - name of the input file.
 * @return true 
 * @return false 
 */
bool writeBoard(char board[N][N], char **argv);

/**
 * @brief The main function is the core of the program.
 * 
 * It initializes the game board, displays instructions to players and 
 * manages the game loop. It checks for winners and saves the final board
 * to a file.
 * 
 * @param argc Number of command-line arguements.
 * @param argv Command-line arguements  -  name of input file.
 * @return int 
 */
int main(int argc, char **argv) {

    char board[N][N];                      // Declare the board

    // Print game instructions
    printf("***   The Three Musketeers Game   ***\n"
    "To make a move, enter the location of the piece you want to move,\n"
    "and the direction you want it to move. Locations are indicated as\n"
    "a letter (A, B, C, D, E) followed by a number (1, 2, 3, 4, or 5).\n"
    "Directions are indicated as left, right, up, down (L/l, R/r, U/u, D/d).\n"
    "For example, to move the Musketeer from the top right-hand corner\n"
    "to the row below, enter 'A,5=L' or 'a,5=l'(without quotes).\n"
    "For convenience in typing, use lowercase letters.\n"
    "Musketeers can move anywhere and soldiers can only move on empty blocks.\n\n");

    if(!readBoard(board, argc, argv))        // Call readBoard to read the board from a file specified in the command line arguements
        exit(1);                             // - if it returns false, exit the program.
    
    displayBoard(board);                     // Display the initial board.

    if(!checkForWinner(board))               // Call checkForWinner - if it returns false, start the game loop.
        play(board);                         // Play prompts the players to move and update the board until a winner is determined.
                                            

    if(!writeBoard(board, argv))             // Call writeBoard to save the final game board to an output file.
        exit(1);                             // - if it returns false, exit the program.

    return 0;
}

bool readBoard(char board[N][N], int argc, char **argv){
    FILE *fp;                                                 // File pointer for output file.
    char *p = NULL;                                           // Pointer to go through the array

    if(argc!=2){                                              // If wrong number of arguements
        printf("Wrong number of arguments\n");                // print error message and return false.
        printf("./nameOfExecutable nameOfInputFile\n");
        return false;
    }
    if((fp = fopen(argv[1], "r")) == NULL){                   // If input is not found
        printf("File not found\n");                           // print error message and return false.
        return false;
    }
    for (p = &board[0][0]; p < &board[N][N]; p++)             // Read a character from file, and store it in the board.
        fscanf(fp, " %c", p);
    fclose(fp);
    return true;
}

void displayBoard(char board[N][N]){
    int i, j;
    printf("    1   2   3   4   5  \n");
    for(i = 0; i < N; i++){
        printf("  +---+---+---+---+---+\n%c |", 'A'+i);
        for(j = 0; j < N; j++){
            printf(" %c |",board[i][j]);
        }
        printf("\n");
    }
    printf("  +---+---+---+---+---+\n");
}

bool readInputMove(char *str, char player){

    bool correctInput = false;                          // Boolean Variable turns true if input is correct.
    
    while(!correctInput){                               // Read Input until correct input is given by the user.

        correctInput = true;

        if(player == 'M')                               // Print Input message depending on the player.
            printf("Give the Musketeer's move\n>");
        else printf("Give the enemy's move \n>");                    
        scanf("%s", str);
                                                                             // If input is "0,0=E" or "0,0=e" , return false.
        if(*str == '0' && *(str+1) == ',' && *(str+2) == '0' && *(str+3) == '=' && (*(str+4) == 'E' || *(str+4) == 'e')){       
            return false;
        }
        if(strlen(str)!=5){                                                  // If Wrong input length, correctInput=false, read again.
            printf("Wrong Input Lenght.\n");
            correctInput = false;
        }
        if((!(*str>='a' && *str<='e') && !(*str>='A' && *str<='E'))){        // If Wrong row input, correctInput=false, read again.
            printf("Wrong Row Input.\n");
            correctInput = false;
        }
        if(*(str+1)!=','){                                                   // If Wrong input syntax, correctInput=false, read again.
            printf("Wrong Input Syntax.\n");
            correctInput = false;
        }
        if((*(str+2)<'1' || *(str+2)>'5') ){                                 // If Wrong collumn input, correctInput=false, read again.
            printf("Wrong Collumn Input.\n");
            correctInput = false;
        }
        if(*(str+3)!='='){                                                   // If Wrong input syntax, correctInput=false, read again.
            printf("Wrong Input Syntax.\n");
            correctInput = false;
        }
                                                                             // If Wrong direction input, correctInput=false, read again.
        if(*(str+4)!='R' && *(str+4)!='r' && *(str+4)!='L' && *(str+4)!='l' && *(str+4)!='U' && *(str+4)!='u' && *(str+4)!='D' && *(str+4)!='d'){
            printf("Wrong direction Input.\n");
            correctInput = false;
        }
    }
    return true;
}

/**
 * @brief Checks if the destination block is correct.
 * 
 * Checks if the destination block for Musketeers is 'o' and if
 * the destination block for the enemy is '.'.
 * 
 * @param player The player that makes a move('M' - Musketeer, 'o' soldier).
 * @param destinationBlock The character in the destination block.
 * @return true Returns true when destination is valid.
 * @return false Returns false when destination block is not valid.
 */
bool checkDestinationBlock(char player, char destinationBlock){

    if(player == 'M')                                          // Check if player is a musketeer.         
        if(destinationBlock != 'o'){                           // If musketeer's destination block is not a soldier print error message and return false.
            printf("Destination Block is not a soldier\n"); 
            return false;
        }
    if(player == 'o')                                          // Check if player is a enemy.
        if(destinationBlock != '.'){                           // If enemy's destination block is not an empty block, print error message and return false.
            printf("Destination Block is not an empty block\n");
            return false;
        }
    return true;
}

bool checkCurrentBlock(char player, char currentBlock){
    if(player == 'M')                                         // Check if player is a musketeer. 
        if(currentBlock != 'M'){                              // If block that the musketeer is trying to move is not musketeer, print message and return false.
            printf("Block that you are trying to move is not Musketeer\n");
            return false;
        }
    if(player == 'o')                                         // Check if player is enemy.
            if(currentBlock != 'o'){                          // If block that the enemy is trying to move is not a soldier, print message and return false.
                printf("Block you are trying to move is not a soldier\n");
                return false;
            }
    return true;
}

bool checkBoardLimit(char row, char col, char direction){           
     if(((row == 'A' || row == 'a') && (direction == 'U' || direction == 'u'))    // If move is out of the board limit,
      || ((row == 'E' || row == 'e') && (direction == 'D' || direction == 'd'))
       || (col == '1' && (direction == 'L' || direction == 'l'))
        || (col == '5' && (direction == 'R' || direction == 'r'))){ 
            printf("This move gets out of the board.\n");                         // Print error message and return false. 
            return false;     

    }
    else return true;
}

char convertRowInput(char row){
    if(row == 'A' || row == 'B' || row == 'C' || row == 'D' || row == 'E')      // Convert character to the integer equivalent to control the board
            row = row-'A';
        else row = row-'a';
    return row;
}

bool moveBoard(char input[6], char board[N][N], char player){                 
    char row = input[0];                                                      
    char col = input[2];
    char direction = input [4];
    char destinationBlock;                                                 // Will be used in check methods
    char currentBlock;                                                     // Will be used in check methods

    while(!checkBoardLimit(row, col, direction)){                          // Check if the move is not inside the board limit, and read again until it is.
        if(!readInputMove(input, player))
            return false; 
        row = input[0];
        col = input[2];
        direction = input [4];
    }

    row = convertRowInput(row);                                            // Convert characters to integer to control the board.
    currentBlock = board[(int)row][(int)(col-'1')];                        // Declaring current block character.

    if(direction == 'r' || direction == 'R')                               // Depending on the direction, the method declares the destination block character.
        destinationBlock = board[(int)row][(int)(col-'1'+1)];

    else if(direction == 'l' || direction == 'L')
        destinationBlock = board[(int)row][(int)(col-'1'-1)];

    else if(direction == 'u' || direction == 'U')
        destinationBlock = board[(int)(row-1)][(int)(col-'1')];

    else if(direction == 'd' || direction == 'D')
        destinationBlock = board[(int)(row+1)][(int)(col-'1')];
    
    // While current block or destination block don't meet the checks, input has to be given again.
    while(!checkCurrentBlock(player, currentBlock) || !checkDestinationBlock(player, destinationBlock)){       

        if(!readInputMove(input, player))                          // Read input and if player wants to exit the game return false, to exit the program in main.
            return false;

                row = input[0];
                col = input[2];
                direction = input [4];  
                
                while(!checkBoardLimit(row, col, direction)){      // While new move is not inside the board limit, read again.
                    if(!readInputMove(input, player))
                        return false;

                    row = input[0];
                    col = input[2];
                    direction = input [4];
                }
                row = convertRowInput(row);                                  // Convert characters to integer to control the board.

                currentBlock = board[(int)row][(int)(col-'1')];              // Declaring current block character.

                if(direction == 'r' || direction == 'R')                     // Depending on the direction, the function declares the direction block character.
                    destinationBlock = board[(int)row][(int)(col-'1'+1)];
                    
                else if(direction == 'l' || direction == 'L')
                    destinationBlock = board[(int)row][(int)(col-'1'-1)];
                    
                else if(direction == 'u' || direction == 'U')
                    destinationBlock = board[(int)(row-1)][(int)(col-'1')];
                    
                else if(direction == 'd' || direction == 'D')
                    destinationBlock = board[(int)(row+1)][(int)(col-'1')];
    }

    // Depending on the player and the direction that is given, changes will be made to the board.
    if(player == 'M'){                                                         
                                                                               
        if(direction == 'r' || direction == 'R'){
            board[row][col-'1'] = '.';
            board[row][col-'1'+1] = 'M';
            displayBoard(board);
        }
        else if(direction == 'l' || direction == 'L'){
            board[row][col-'1'] = '.';
            board[row][col-'1'-1] = 'M';
            displayBoard(board);
            }
        else if(direction == 'u' || direction == 'U'){
            board[row][col-'1'] = '.';
            board[row-1][col-'1'] = 'M';
            displayBoard(board);
            }
        else if(direction == 'd' || direction == 'D'){
            board[row][col-'1'] = '.';
            board[row+1][col-'1'] = 'M';
            displayBoard(board);                
            } 
    }
    else if(player == 'o'){
        if(direction == 'r' || direction == 'R'){
            board[row][col-'1'] = '.';
            board[row][col-'1'+1] = 'o';
            displayBoard(board);
        }
        else if(direction == 'l' || direction == 'L'){
            board[row][col-'1'] = '.';
            board[row][col-'1'-1] = 'o';
            displayBoard(board);
            }
        else if(direction == 'u' || direction == 'U'){
            board[row][col-'1'] = '.';
            board[row-1][col-'1'] = 'o';
            displayBoard(board);
            }
        else if(direction == 'd' || direction == 'D'){
            board[row][col-'1'] = '.';
            board[row+1][col-'1'] = 'o';
            displayBoard(board);                
            } 
    }
    return true;    // Return true if player does not want to exit the game.
}

bool checkForWinner(char board[N][N]){
    bool musketeersWin = false, soldiersWin = false;
    
    int i, j;
    int muskCollumnCount = 0, muskRowCount = 0, winningMusketeersCount = 0;
    
    for(i = 0; i < N; i++){
            muskRowCount = 0;
            for(j = 0; j < N; j++){
                if(board[i][j] == 'M')
                    muskRowCount++;
            }
            if(muskRowCount == 3){                              // If three musketeers are found on the same row
                    printf("Cardinal Richelieu's men win!\n");  // Print winning message.
                    soldiersWin = true;                         
            }
        }
        for(j = 0; j < N; j++){                                 
            muskCollumnCount = 0;                               
            for(i = 0; i < N; i++){
                if(board[i][j] == 'M')
                    muskCollumnCount++;
            }
            if(muskCollumnCount == 3){                          // If three musketeers are found on the same collumn
                    printf("Cardinal Richelieu's men win!\n");  // Print winning message.
                    soldiersWin = true;
            }
        }
        winningMusketeersCount = 0;
        for(i = 0; i < N; i++)
            for(j = 0; j < N; j++){
                if(board[i][j] == 'M'){

                    // Depending on the place of Musketeers on the board, check if they 
                    // have no more soldiers around them to move, to decide if Musketeers won.
                    
                    if(i > 0 && i < 4 && j > 0 && j < 4){
                        if(board[i-1][j] != 'o' && board[i+1][j] != 'o' && board[i][j-1] != 'o' && board[i][j+1] != 'o')
                            winningMusketeersCount++;
                    }
                    if(i == 0 && j > 0 && j < 4){
                        if(board[i+1][j] != 'o' && board[i][j-1] != 'o' && board[i][j+1] != 'o')
                            winningMusketeersCount++;
                    }
                    if(i == 4 && j > 0 && j < 4){
                        if(board[i-1][j] != 'o' && board[i][j-1] != 'o' && board[i][j+1] != 'o')
                            winningMusketeersCount++;
                    }
                    if(i > 0 && i < 4 && j == 0){
                        if(board[i-1][j] != 'o' && board[i+1][j] != 'o' && board[i][j+1] != 'o')
                            winningMusketeersCount++;
                    }
                    if(i > 0 && i < 4 && j == 4){
                        if(board[i-1][j] != 'o' && board[i+1][j] != 'o' && board[i][j-1] != 'o')
                            winningMusketeersCount++;
                    }
                    if(i == 0 & j == 0){
                        if(board[i+1][j] != 'o' && board[i][j+1] != 'o')
                            winningMusketeersCount++;
                    }
                    if(i == 0 & j == 4){
                        if(board[i+1][j] != 'o' && board[i][j-1] != 'o')
                            winningMusketeersCount++;
                    }
                    if(i == 4 & j == 0){
                        if(board[i-1][j] != 'o' && board[i][j+1] != 'o')
                            winningMusketeersCount++;
                    }
                    if(i == 4 & j == 4){
                        if(board[i-1][j] != 'o' && board[i][j-1] != 'o')
                            winningMusketeersCount++;
                    }
                    if(winningMusketeersCount == 3){                       // If all 3 musketeers cannot move, 
                        printf("The Musketeers win!");                     // Print winning message of masketeers.
                        musketeersWin = true;
                    }
                }
            }
            if(soldiersWin == true || musketeersWin == true)               // If a winner is found return true.
                return true;
            else return false;
}

void play(char board[N][N]){
    int n = 0;                                               // n is used to determine which player is playing
    char player;
    bool endOfGame = false;
    
    while(!endOfGame){
        
        if(n % 2 == 0)                                       // If n is even, Musketeer plays else the enemy
            player = 'M';
        else player = 'o';
            
        char str[6];

        if(!readInputMove(str, player))                      // If player wants to exit return
            return;

        if(!moveBoard(str, board, player))
            return;

        if(checkForWinner(board) ==true)                     // If winner is found, end the game loop
            endOfGame=true;
         n++;
        }
}

bool writeBoard(char board[N][N], char **argv){
    FILE *fpout = NULL;                                           // File pointer for output file.
    int i, j;                                                     // Loop counters.
    char str[100] = "out-";                                       // Initial part of output file.
    char str1[50];                                                
    strcpy(str1, argv[1]);                                        // Copy the second command line arguement to str1

    strncat(str, argv[1], sizeof(str) - strlen(argv[1]) - 1);     // Concatenate str and str1

    if((fpout = fopen(str, "w")) == NULL){                        // If file open fails,
        printf("Error opening file\n");                           // Print eror message and return false.
        return false;                                               
    }
    fprintf(fpout, "    1   2   3   4   5  \n");
    
    for(i = 0; i < N; i++){
        fprintf(fpout, "  +---+---+---+---+---+\n%c |", 'A'+i);
        for(j = 0; j < N; j++){
            fprintf(fpout, " %c |",board[i][j]);
        }
        fprintf(fpout, "\n");
    }

    fprintf(fpout, "  +---+---+---+---+---+\n");

    fclose(fpout);                                               // Close the output file
    printf("Saving %s...Done\nAu Revoir!\n", str);               // Print success message with filename
    
    return true;
}


