#include <bits/stdc++.h>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#define r 10
#define c 19
#define compareBoxes(box1, box2, box3) ((board[box1] == board[box2]) && (board[box2] == board[box3]) && (board[box1] != 0)) //Checkes if three items are the same, and makes sure they're not 0's.
#define numberToLetter(x) ((x > 0) ? (x == 1) ? 'X' : 'O' : ' ') //Takes the number and turns it into the letter or space.
using namespace std;

const int SIZE = 9; // Size of the Sudoku board
const int BLOCK_SIZE = 3; // Size of each block within the board

static int score=0;

void Display_Pattern()
{
    system("color a");
    cout << "_________________________________________________\n";
    cout << " \t\t\t\t\t\t\t\tWELCOME TO GAME-O-THRON \n";
    cout << "_________________________________________________\n\n";
    cout << "Game-o-Thron is a menu driven mini-game platform which enables the user to choose anyone out of the listed \ngames at a moment and enjoy it as a pastime.\nCreated using C++, this projectutilizes a set of data structures and draws the use of backtracking algorithms\n\n";
    cout << "List of Games:\nThe Word Search Game(1)\nTic Tac Toe(2)\nSudoku(3)\nPacking Suitcase(4)\nExit(5)";
}
class TicTacToe{
    public:
    int getWinner(int board[9]) {
	//Finds winner of game, if there is no winner, returns 0.
	int winner = 0;
	for (int x = 0; x < 3; x++) {
		if (compareBoxes(3*x, 3*x+1, 3*x+2)) { //Checks rows
			winner = board[3*x];
			break;
		} else if (compareBoxes(x, x+3, x+6)) { //Checks columns
			winner = board[x];
			break;

		} else if (compareBoxes(2*x, 4, 8-2*x) && (x < 2)) { //Checks diagonals. Doesn't check if x == 2.
			winner = board[4];
			break;
		}
	}
	    return winner;
    }
    bool gameOver(int board[9]){
        //Checks if game is over, and announces who won, or if it was a tie.
        int winner = getWinner(board);
        if (winner > 0) {
            cout << numberToLetter(winner) << " wins!"<< endl;
            if(numberToLetter(winner)=='X')score+=10;
            return true;
        }
        for (int x = 0; x < 9; x++) {
            if (board[x] == 0) return false;
        }
        cout << "Tie!\n\n";
        return true;
    }

    int willWin(int board[9], int player) {
        //Checks if a given player could win in the next plank.
        for (int x = 0; x < 9; x++) {
            int tempBoard[9];
            memcpy(tempBoard, board, 36);
            if (board[x] > 0) continue;
            tempBoard[x] = player;
            if(getWinner(tempBoard) == player) return x;
        }
        return -1;
    }

    int exceptionalCase(int board[9]) {
        //Finds boards that are exceptions to how the algorithm works.
        int cases[2][9] = {{1,0,0,0,2,0,0,0,1}, {0,1,0,1,2,0,0,0,0}}; //Boards that don't work with algorithm.
        int answers[2][4] = {{3,3,3,3}, {2,8,6,0}};
        int rotatedBoard[9] = {6,3,0,7,4,1,8,5,2};
        int newBoard[9];
        int tempBoard[9];
        for(int x = 0; x < 9; x++) {
            newBoard[x] = board[x];
        }
        for (int caseIndex = 0; caseIndex < 2; caseIndex++) {
            for(int rotation = 0; rotation < 4; rotation++) {
                for (int x = 0; x < 9; x++)
                    tempBoard[x] = newBoard[x];

                int match = 0;
                //Rotates board so it works with different versions of the same board.
                for (int box = 0; box < 9; box++) {
                    newBoard[box] = tempBoard[rotatedBoard[box]];
                }

                for (int x = 0; x < 9; x++) {
                    if (newBoard[x] == cases[caseIndex][x]) match++;
                    else break;
                }
                if (match == 9) return answers[caseIndex][rotation];
            }
        }
        return -1;
    }

    int getSpace(int board[9], int spaces[4]) {
        //Gets a random corner or side that's not taken.
        bool isSpaceEmpty = false;
        int y;
        for (int x = 0; x < 4; x++) {
            if (board[spaces[x]] == 0) {
                isSpaceEmpty = true;
                break;
            }
        }
        if (isSpaceEmpty) {
            do {
                y = rand() % 4;
            } while (board[spaces[y]] != 0);
            return spaces[y];
        }
        return -1;
    }

    void outputBoard(int board[9]) {
        for(int line = 0; line < 3; line++){
            for (int box = 0; box < 3; box++) {
                cout << numberToLetter(board[3*line+box]) << ((box < 2) ? '|' : '\n');
            }
            cout << ((line < 2) ? "-----\n" : "\n");
        }
    }

    void run(){
         system("color c");
        int board[9] = {0,0,0,0,0,0,0,0,0}; //Starts empty board.
        int possibleWinner;
        int move;
        bool isInvalid;
        string moveString;
        srand((int) time(0));
        int corners[4] = {0,2,6,8};
        int sides[4] = {1,3,5,7};

        cout << "1|2|3\n-----\n4|5|6\n-----\n7|8|9\n\n";

        while (true) {
            //Player X decides what move they'll do.
            do {
                cout << "X: ";
                getline(cin, moveString);
                move = moveString[0] - '1';
                if (move > 8 || move < 0 || board[move] != 0) {
                    cout << "Invalid input" << endl;
                    isInvalid = true;
                } else {
                    board[move] = 1;
                    isInvalid = false;
                    cout << endl;
                }
            } while (isInvalid);

            //Decides whether or not the game continues.
            if (gameOver(board) > 0) {
                outputBoard(board);
                break;
            }

            //Player O decides which move they'll do.
            bool good = false;
            for (int x = 2; x > 0; x--){
                possibleWinner = willWin(board, x);
                if (possibleWinner != -1) {
                    board[possibleWinner] = 2;
                    good = true;
                    break;
                }
            }
            if (good);
            else if (board[4] == 0) board[4] = 2; //Middle.
            else if (exceptionalCase(board) > -1) board[exceptionalCase(board)] = 2; //Exception boards.
            else if (getSpace(board, corners) != -1) board[getSpace(board, corners)] = 2; //Corners
            else board[getSpace(board, sides)] = 2; //Sides

            //Prints the board to the screen.
            outputBoard(board);

            //Decides whether or not the game continues.
            if(gameOver(board)) break;

        }
    }
};
class Sudoku
{
public:
    void printBoard(vector<vector<int>>& board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << board[i][j] << " ";
                if ((j+1) % 3 == 0) cout << " ";
            }
            cout << endl;
            if ((i+1) % 3 == 0) cout << endl;
        }
    }
    bool isValidSudoku(vector<vector<int>>& board) {
        // Check rows
        for (int i = 0; i < 9; i++) {
            vector<bool> seen(10, false); // 0-9, initialize to false
            for (int j = 0; j < 9; j++) {
                int num = board[i][j];
                if (num != 0) {
                    if (seen[num]) {
                        return false;
                    } else {
                        seen[num] = true;
                    }
                }
            }
        }
        // Check columns
        for (int j = 0; j < 9; j++) {
            vector<bool> seen(10, false); // 0-9, initialize to false
            for (int i = 0; i < 9; i++) {
                int num = board[i][j];
                if (num != 0) {
                    if (seen[num]) {
                        return false;
                    } else {
                        seen[num] = true;
                    }
                }
            }
        }
        // Check 3x3 boxes
        for (int k = 0; k < 9; k++) {
            vector<bool> seen(10, false); // 0-9, initialize to false
            int rowStart = 3*(k/3), colStart = 3*(k%3);
            for (int i = rowStart; i < rowStart+3; i++) {
                for (int j = colStart; j < colStart+3; j++) {
                    int num = board[i][j];
                    if (num != 0) {
                        if (seen[num]) {
                            return false;
                        } else {
                            seen[num] = true;
                        }
                    }
                }
            }
        }
        return true;
    }

    // Check if the current move is valid or not
    bool isValidMove(vector<vector<int>>& board, int row, int col, int num) {
        // Check row
        for (int j = 0; j < 9; j++) {
            if (board[row][j] == num) {
                return false;
            }
        }
        // Check column
        for (int i = 0; i < 9; i++) {
            if (board[i][col] == num) {
                return false;
            }
        }
        // Check 3x3 box
        int startRow = row - row%3, startCol = col - col%3;
        for (int i = startRow; i < startRow+3; i++) {
            for (int j = startCol; j < startCol+3; j++) {
                if (board[i][j] == num) {
                    return false;
                }
            }
        }
        return true;
    }
    // Solve the Sudoku board using backtracking
    bool solveSudoku(vector<vector<int>>& board) {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (board[row][col] == 0) {
                    for (int num = 1; num <= 9; num++) {
                        if (isValidMove(board, row, col, num)) {
                            board[row][col] = num;
                            if (solveSudoku(board)) {
                                return true;
                            }
                            board[row][col] = 0;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
    // Generate a random Sudoku board
    void generateBoard(vector<vector<int>>& board) {
        srand(time(nullptr));
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (rand() % 4 == 0) {
                    int num = rand() % 9 + 1;
                    if (isValidMove(board, i, j, num)) {
                        board[i][j] = num;
                    }
                }
            }
        }
    }
    void run(){
        system("color d");
        vector<vector<int>> board(SIZE, vector<int>(SIZE, 0));

        // Generate the Sudoku board
        generateBoard(board);
        while(!isValidSudoku(board)){
        generateBoard(board);
        }
        // Print the Sudoku board
        printBoard(board);
        //Solve the generated sudoku table
        solveSudoku(board);

        // Take input for the solution of the Sudoku board
        cout << "Enter solution for the board:" << endl;
        vector<vector<int>> solution(9, vector<int>(9));
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cin >> solution[i][j];
            }
        }

        // Compare the solution with the solved board
        if (board == solution) {
            cout << "You win!" << endl;
            score+=50;
        } else {
            cout<<"Sorry wrong answer."<<endl;
            cout << "Solved board:" << endl;
            printBoard(board);
        }
    }
};
class PSKS{
    public:
    int user(int W, vector<int>& sno,vector<string>& item,vector<int>& wt,vector<int>&val, int n)
    {

        cout<<"Maximum capacity : "<<W<<endl;
        cout <<"Sno."<<" "<<"item"<<" "<<"Weight"<<endl;
        for (int i = 0; i < n; i++) {
            cout <<sno[i]<<" "<<item[i]<<" "<<wt[i]<<endl;
        }
        map<int, int>mp;
        int g;
        cout<<"You should preferably select the items in whole to get the correct answer."<<endl;
        cout<<"Enter the no. of items you want to take : ";
        cin>>g;
        cout << "Enter sno and the weight of the items you want to select:" <<endl;
        int s,w;

        for (int i = 0; i < g; i++) {
                cin>>s>>w;
            mp.insert({ s, w });
        }
        int v=0;
        for (auto itr = mp.begin(); itr != mp.end(); ++itr)
        {
            v=v+((val[(itr->first)-1]/(wt[(itr->first)-1]))*(itr->second));
        }
        return v;

    }
    int knapsack(int W, vector<int>& wt, vector<int>& val, vector<string> item, int n) {
        int i, w;
        int K[n + 1][W + 1];
        string items[n + 1][W + 1];

        // Build table K[][] in bottom up manner
        for (i = 0; i <= n; i++) {
            for (w = 0; w <= W; w++) {
                if (i == 0 || w == 0){
                    K[i][w] = 0;
                    items[i][w] = "";
                }
                else if (wt[i - 1] <= w){
                    if(val[i - 1] + K[i - 1][w - wt[i - 1]] > K[i - 1][w]){
                        K[i][w] = val[i - 1] + K[i - 1][w - wt[i - 1]];
                        items[i][w] = items[i - 1][w - wt[i - 1]] + item[i - 1] + ",";
                    }
                    else{
                        K[i][w] = K[i - 1][w];
                        items[i][w] = items[i - 1][w];
                    }
                }
                else{
                    K[i][w] = K[i - 1][w];
                    items[i][w] = items[i - 1][w];
                }
            }
        }

        int res2 = K[n][W];

        string result_items = items[n][W];
        result_items.pop_back(); // to remove the last "," character
        cout << "Items included: " << result_items << endl;
        return res2;
    }

    void run(){
        system("color e");
        int x,W, n;
        srand((unsigned) time(NULL));

        // Get a random number
        W= rand()%10*50;
        while(W==0)W= rand()%10*50;
        cout << "the capacity of the knapsack: "<<W<<endl;
        n=25;
        vector<int>sno{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
        vector<string> item = {"Chicken Breast", "Salmon", "Tuna Salad", "Steak", "Broccoli", "Sweet Potato", "Brown Rice", "Black Beans", "Quinoa", "Greek Yogurt",
        "Almonds", "Eggs", "Avocado", "Banana", "Blueberries", "Oatmeal", "Whole Wheat Bread", "Peanut Butter", "Cheese", "Cottage Cheese", "Carrots", "Spinach", "Tomatoes",
        "Apples", "Dark Chocolate"};
        vector<int> wt = {85, 85, 85, 85, 91, 85, 45, 85, 85, 100, 28, 50, 50, 100, 50, 40, 28, 32, 28, 61, 61, 61, 61, 100, 28};
        vector<int> val = {14025, 17510, 12325, 21250, 5005, 8755, 4995, 10200, 10200, 13000, 4480, 4000, 12500, 10500, 4200, 6000, 2240, 6080, 3080, 4392, 2501, 1403, 1098, 9500, 4760};
        int value=user(W,sno,item,wt,val,n);

        int max_value = knapsack(W, wt, val, item, n);
        cout<<"The calorie intake according to your items : "<<value<<endl;
        cout << "The maximum value that can be carried in the knapsack is: " << max_value << endl;
        int p=max_value-value;
        cout<<"Difference:"<<p<<endl;
        if(p<0)
        {
            cout<<"No Points"<<endl;
        }
        else if(p==0)
        {
            cout<<"You got 10 points"<<endl;
            score+=10;

        }
        else if(p > 0 && p <= 5000)
        {
            cout<<"You got 9 points"<<endl;
            score+=9;
        }
        else if(p>5000 && p <= 10000)
        {
            cout<<"You got 8 points"<<endl;
            score+=8;
        }
        else if(p>10000 && p <= 15000)
        {
            cout<<"You got 7 points"<<endl;
            score+=7;
        }
        else if(p>15000 && p <= 20000)
        {
            cout<<"You got 6 points"<<endl;
            score+=6;
        }
        else if(p>20000 && p <= 25000)
        {
            cout<<"You got 5 points"<<endl;
            score+=5;
        }
        else if(p>25000 && p <= 30000)
        {
            cout<<"You got 4 points"<<endl;
            score+=4;
        }
        else if(p>30000 && p <= 35000)
        {
            cout<<"You got 3 points"<<endl;
            score+=3;
        }
        else if(p>35000 && p <= 40000)
        {
            cout<<"You got 2 points"<<endl;
            score+=2;
        }
        else if(p>40000 && p <= 45000)
        {
            cout<<"You got 1 points"<<endl;
            score+=1;
        }
        else {
            cout<<"You got 0 points"<<endl;
        }
    }
};

class WordSearch
{
public:
    string wordsearch;
    int diff;
    char grid[r][c] = {
        "HORSECHESTNUTOHTSA",
        "ALVULOILOARNOEPILC",
        "FEBRPNAMSBESLIBKAO",
        "GIMKAKIDNELDERTDER",
        "YVETGECYHRSBULOMFN",
        "AYOLSRTEVRBSPAFWHP",
        "SPAHDUSXNILIEJLBAL",
        "HELPAMONCESLCHYMIN",
        "STRIELDRLSIVSWTCHO",
        "BLACKTHORNREKLARKB",
    };
    void toggle(string &wordsearch) // function for making the case uniform
    {
        int length = wordsearch.length();
        for (int i = 0; i < length; i++)
        {
            int cc = wordsearch[i];
            if (islower(cc))
                wordsearch[i] = toupper(cc);
        }
    }
    // Function to check if a word exists in a grid
    // x, y: current position in 2D array
    bool findmatch(char mat[r][c], string pat, int x, int y,
                   int nrow, int ncol, int level)
    {
        int l = pat.length();
        if (level == l)
            return true;
        // Out of Boundary
        if (x < 0 || y < 0 || x >= nrow || y >= ncol)
            return false;
        // If grid matches with a letter while recursion
        if (mat[x][y] == pat[level])
        {
            // Marking this cell as visited
            char temp = mat[x][y];
            mat[x][y] = '#';
            // finding subpattern in 4 directions
            bool res = findmatch(mat, pat, x - 1, y, nrow, ncol, level + 1) |
                       findmatch(mat, pat, x + 1, y, nrow, ncol, level + 1) |
                       findmatch(mat, pat, x, y - 1, nrow, ncol, level + 1) |
                       findmatch(mat, pat, x, y + 1, nrow, ncol, level + 1);
            // marking this cell as unvisited again
            mat[x][y] = temp;
            return res;
        }
        else // Not matching then false
            return false;
    }
    // Function to check if the word exists in the grid or not
    bool checkMatch(char mat[r][c], string pat, int nrow, int ncol)
    {
        int l = pat.length();
        // if total characters in matrix is less then pattern length
        if (l > nrow * ncol)
            return false;
        // Traverse in the grid
        for (int i = 0; i < nrow; i++)
        {
            for (int j = 0; j < ncol; j++)
            {
                // If first letter matches, then recur and check
                if (mat[i][j] == pat[0])
                    if (findmatch(mat, pat, i, j, nrow, ncol, 0))
                        return true;
            }
        }
        return false;
    }
    void Play_WordSearch()
    {
        system("color b");
        int loop;
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                cout << grid[i][j] << " \n"[j == c - 1];
        cout << "\n\nSelect difficulty level\n";
        cout << "1. Easy- find 5 words (1)\n2. Medium- find 10 words (2)\n3. Hard- find 15 words(3)\n\n\n";
        cout << "Your Choice: ";
        cin >> diff;
        if (diff == 1)
        {
            loop = 5;
        }
        else if (diff == 2)
        {
            loop = 10;
        }
        else if (diff == 3)
        {
            loop = 15;
        }
        else
        {
            cout << "Invalid Input! Select a valid difficulty level.";
        }
        for (int i = 0; i < loop; i++)
        {
            cout << "Your Solution: ";
            cin >> wordsearch;
            toggle(wordsearch);
            if (checkMatch(grid, wordsearch, r, c))
            {
                cout << "You scored a point!\n";
                score = score + 10;
            }
            else
            {
                cout << "No such word exists :(\n";
            }
        }
    }
};
int main()
{
    int choice;
    char cont;
    Display_Pattern();
    cout << "\n\nYour choice: ";
    cin >> choice;
    WordSearch game;
    TicTacToe game2;
    Sudoku game3;
    PSKS game4;
    switch (choice)
    {
    case 1:
        cout << "\n\nThe Word Search Game\n\n";
        game.Play_WordSearch();
        cout<<"Your current score is:"<<score<<endl;
        cout << "\nDo you wish to continue?\n";
        cin >> cont;
        if (cont == 'y' || cont == 'Y')
        {
            system("CLS");
            main();
        }
        else
            cout<<"Your final score was:"<<score<<endl;
            cout << "\nGood bye!";
        exit(1);
        break;
    case 2:
        cout << "\n\nTicTacToe\n\n";
        game2.run();
        cout<<"Your current score is:"<<score<<endl;
        cout << "\nDo you wish to continue?\n";
        cin >> cont;
        if (cont == 'y' || cont == 'Y')
        {
            system("CLS");
            main();
        }
        else
            cout<<"Your final score was:"<<score<<endl;
            cout << "\nGood bye!";
        exit(1);
        break;
    case 3:
        cout << "\n\nSudoku\n\n";
        game3.run();
        cout<<"Your current score is:"<<score<<endl;
        cout << "\nDo you wish to continue?\n";
        cin >> cont;
        if (cont == 'y' || cont == 'Y')
        {
            system("CLS");
            main();
        }
        else
            cout<<"Your final score was:"<<score<<endl;
            cout << "\nGood bye!";
        exit(1);
        break;
    case 4:
        cout<<"\n\n\n\n";
        game4.run();
        cout<<"Your current score is:"<<score<<endl;
        cout << "\nDo you wish to continue?\n";
        cin >> cont;
        if (cont == 'y' || cont == 'Y')
        {
            system("CLS");
            main();
        }
        else
            cout<<"Your final score was:"<<score<<endl;
            cout << "\nGood bye!";
        exit(1);
        break;
    case 5:
        cout<<"Your final score was:"<<score<<endl;
        cout << "\nGood Bye!";
        exit(1);
    }
    return 0;
}