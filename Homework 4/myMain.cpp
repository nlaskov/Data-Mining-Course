//homework 4
#include<iostream>
using namespace std;

int  MAXSCORE =10; 
int MINSCORE =-10; 

#define SIDE 3

#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'
#define EMPTYSPACE ' '

int minimize(char board[][SIDE],int alpha, int beta,int depth, int movesCounter);
int maximize(char board[][SIDE],int alpha, int beta,int depth, int movesCounter);

void showBoard(char board[][SIDE]) 
{ 
	
	cout<<"\n\n\t\t\t "<< board[0][0]<<" | "<< board[0][1]<<" | "<<board[0][2]<<endl; 
	cout<<"\t\t\t-----------\n"; 
	cout<<"\t\t\t "<< board[1][0]<<" | "<< board[1][1]<<" | "<<board[1][2]<<endl; 
	cout<<"\t\t\t-----------\n"; 
	cout<<"\t\t\t "<< board[2][0]<<" | "<< board[2][1]<<" | "<<board[2][2]<<endl<<endl<<endl; 
} 

void initialiseBoard(char board[][SIDE]) 
{	
	// Initially the board is empty 
	for (int i=0; i<SIDE; i++) 
	{ 
		for (int j=0; j<SIDE; j++) 
			board[i][j] = EMPTYSPACE; 
	}
} 

void declareWinner(bool isPerson) 
{ 
	if (isPerson) 
		cout<<"HUMAN has won\n"; 
	else
		cout<<"COMPUTER has won\n"; 
} 

int gameOver(char board[][SIDE]) 
{ 
	for (int row = 0; row < 3; row++)
    {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2])
        {
            if (board[row][0] == COMPUTERMOVE)
            {
                return 1;
            }
            else if (board[row][0] == HUMANMOVE)
            {
                return -1;
            }
        }
    }
    for (int col = 0; col < 3; col++)
    {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col])
        {
            if (board[0][col] == COMPUTERMOVE)
            {
                return 1;
            }
            else if (board[0][col] == HUMANMOVE)
            {
                return -1;
            }
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == COMPUTERMOVE)
        {
            return 1;
        }
        else if (board[0][0] == HUMANMOVE)
        {
            return -1;
        }
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == COMPUTERMOVE)
        {
            return 1;
        }
        else if (board[0][2] == HUMANMOVE)
        {
            return -1;
        }
    }
    return 0;
}

int evaluateBoard(char board[][SIDE], int depth) 
{
    for (int row = 0; row < 3; row++)
    {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2])
        {
            if (board[row][0] == COMPUTERMOVE)
            {
                return MINSCORE + depth;
                //return MAXSCORE - depth;
            }
            else if (board[row][0] == HUMANMOVE)
            {
                return MAXSCORE - depth;
                //return MINSCORE + depth;
            }
        }
    }
    for (int col = 0; col < 3; col++)
    {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col])
        {
            if (board[0][col] == COMPUTERMOVE)
            {
                return MINSCORE + depth;
                //return MAXSCORE - depth;
            }
            else if (board[0][col] == HUMANMOVE)
            {
                return MAXSCORE - depth;
                //return MINSCORE + depth;
            }
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == COMPUTERMOVE)
        {
            //return MAXSCORE - depth;
            return MINSCORE + depth;
        }
        else if (board[0][0] == HUMANMOVE)
        {
            return MAXSCORE - depth;
            //return MINSCORE + depth;
        }
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == COMPUTERMOVE)
        {
            return MINSCORE + depth;
            //return MAXSCORE - depth;
        }
        else if (board[0][2] == HUMANMOVE)
        {
            //return MINSCORE + depth;
            return MAXSCORE - depth;
        }
    }
    return 0;
}

bool makeAMove(char board[][SIDE],int x, int y,bool isPerson){
    if(board[x][y] != EMPTYSPACE) return false;

    if(isPerson) board[x][y] = HUMANMOVE;
    else board[x][y] = COMPUTERMOVE;

    return true;
}

int maximize(char board[][SIDE],int alpha, int beta,int depth, int movesCounter){
    int currentScore = evaluateBoard(board,depth);
    //If win or draw now go back
    if(currentScore !=0) return currentScore;
    if(movesCounter == 9) return 0;


    int bestValue = INT_MIN;

    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            if (board[i][j] == EMPTYSPACE)
            {

                board[i][j] = COMPUTERMOVE;
                bestValue = max(bestValue, minimize(board,alpha, beta, depth + 1,movesCounter+1));
                board[i][j] = EMPTYSPACE;

                // Alpha - Beta
                if (bestValue >= beta)
                {
                    return bestValue;
                }
                alpha = max(alpha, bestValue);
            }
        }
    }
    return bestValue;
}

int minimize(char board[][SIDE],int alpha, int beta,int depth, int movesCounter){



    int currentScore = evaluateBoard(board,depth);
    
    //If win or draw now go back
    if(currentScore !=0) return currentScore;
    if(movesCounter == 9) return 0;

    int bestValue = INT_MAX;

    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            if (board[i][j] == EMPTYSPACE)
            {

                board[i][j] = HUMANMOVE;
                bestValue = min(bestValue, maximize(board,alpha, beta, depth + 1,movesCounter+1));
                board[i][j] = EMPTYSPACE;

                // Alpha - Beta
                if (bestValue <= alpha)
                {
                    return bestValue;
                }
                beta = min(beta, bestValue);
            }
        }
    }
    return bestValue;
}

pair<int,int> minMax(char board[][SIDE],int moveCounter){
    pair<int,int> result;
    
    int bestValue = INT_MIN;
    result.first=-1;
    result.second=-1;

    for(int i=0;i<SIDE;i++){
        for(int j=0;j<SIDE;j++){
            if(board[i][j] == EMPTYSPACE){
                board[i][j] = COMPUTERMOVE;
                int temp = minimize(board,INT_MIN, INT_MAX,0,moveCounter+1);
                board[i][j] = EMPTYSPACE;

                if(temp>bestValue){
                    bestValue=temp;
                    result.first = i;
                    result.second = j;
                }
            }
        }
    }
    return result;
}

void playTicTacToe(bool isPerson){

    char board[SIDE][SIDE];

    //Create and show board
    initialiseBoard(board);
    showBoard(board);    

    int movesCounter=0;
    int x=1,y=1;
    
    //Play while there isn`t winner
    while(movesCounter<9 && gameOver(board)==0){
        if(isPerson){
            do{
                cout << "Row:"; 
                cin >> x;
                cout << "Column:"; 
                cin >> y;
            }while(!makeAMove(board,x-1,y-1,isPerson));
        }
        else{
            pair<int,int> move = minMax(board,movesCounter);
            makeAMove(board,move.first,move.second,isPerson);
            showBoard(board);
        }
        isPerson=!isPerson;
        movesCounter++;
           

    }

    //Check for draw
    int temp = gameOver(board);
    if(temp == 0 && movesCounter==9){
        cout<<"It's a draw\n";
        showBoard(board);
    }

    //Print winner and board
    else if(temp == 1) declareWinner(false);
        
    else {
        declareWinner(true);
        showBoard(board);
    }
}

int main(){
    printf("\n-------------------------------------------------------------------\n\n");
	printf("\t\t\t Tic-Tac-Toe\n"); 
	printf("\n-------------------------------------------------------------------\n\n");

    char cmd='y';

    do{
        cout<<"Dou you want to start first? (y/n): ";
        cin>>cmd;

        if(cmd != 'y'){
            playTicTacToe(false);
        }
        else playTicTacToe(true);

        

        cout<<"Do you want to play again? (y/n): ";
        cin>>cmd;
    }while(cmd!='n');
}
