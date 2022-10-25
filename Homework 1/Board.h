#include<vector>
#include<iostream>
using namespace std;
class Board{
    public:
    int N;
    int final_zero_position;
    int current_zero_position;
    int manhattan;
    int linear;
    vector<string> path;
    vector< vector<int> > blocks;

    public:

    Board(int _N, int _position, int arr[]){
        N = _N;
        if(_position == -1) final_zero_position = N*N -1;
        else final_zero_position = _position -1;

        //loop for the numbers (if _position != -1 everything after _position should be with +1)
        for(int i=0;i<N;i++){
            vector<int> v;
            for(int j=0;j<N;j++){
                if(arr[i*N + j] > final_zero_position) v.push_back(arr[i*N + j]);
                else if(arr[i*N + j] == 0) {
                    v.push_back(final_zero_position);
                    current_zero_position = i*N + j;
                }
                else  v.push_back(arr[i*N + j]-1);
            }
            blocks.push_back(v);
        }

        manhattan = manhattan_distance();
        linear = linear_conflict();
    }

    Board(Board model, string newMove){
        this->N = model.N;
        this->final_zero_position = model.final_zero_position;
        this->current_zero_position = model.current_zero_position;
        this->path = model.path;
        this->blocks = model.blocks;

        this->swapBlocks(newMove);

        this->manhattan = manhattan_distance();
        this->linear = linear_conflict();
    }

    void printBoard(){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                cout<<blocks[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    void swapBlocks(string move){
        int temp = blocks[current_zero_position/N][current_zero_position%N];
        if(move == "up"){
            blocks[current_zero_position/N][current_zero_position%N] = blocks[current_zero_position/N +1][current_zero_position%N];
            blocks[current_zero_position/N +1][current_zero_position%N] = temp;
            current_zero_position +=N;
        }
        else if(move == "down"){
            blocks[current_zero_position/N][current_zero_position%N] = blocks[current_zero_position/N -1][current_zero_position%N];
            blocks[current_zero_position/N -1][current_zero_position%N] = temp;
            current_zero_position -=N;
        }
        else if(move == "left"){
            blocks[current_zero_position/N][current_zero_position%N] = blocks[current_zero_position/N][current_zero_position%N +1];
            blocks[current_zero_position/N][current_zero_position%N +1] = temp;
            current_zero_position +=1;
        }
        else{
            blocks[current_zero_position/N][current_zero_position%N] = blocks[current_zero_position/N][current_zero_position%N -1];
            blocks[current_zero_position/N][current_zero_position%N -1] = temp;
            current_zero_position -=1;
        }


        path.push_back(move);
    }

    int manhattan_distance(){

        int row,column, distance=0;

        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                row = (blocks[i][j])/N;
                column = (blocks[i][j])%N;
                distance+= abs(i-row) + abs(j-column);
            }
        }
        return distance;
    }

    int linear_conflict(){
        int counter=0;
        for(int i=0;i<N*N;i++){
            if(blocks[i/N][i%N]/N == i/N){
                for(int j=i;j<N;j++){
                    if(blocks[i/N][i%N] > blocks[i/N][j] && blocks[i/N][j]/N == i/N){
                        counter+=2;
                        
                    }
                }
            }
            if(blocks[i/N][i%N]%N == i%N){
                for(int j=i;j<N;j++){
                    if(blocks[i/N][i%N] > blocks[j][i%N] && blocks[j][i%N]%N == i%N){
                        counter+=2;
                        
                    }
                }
            }   
        }
        return counter;
    }

    int hamming(){
        int counter = 0;
        for(int i=0;i<N*N;i++){
            if(blocks[i/N][i%N] == i){
                counter+=1;
            }
        }
        return counter;
    }

    bool isMyGoal(){
        if(hamming() == N*N) return true;
        else return false;
    }

    bool isSolavable(){
        int counter = 0;
        for(int i=0;i<N*N;i++){
            if(i == current_zero_position){
                continue;
            }
            for(int j=i;j<N*N;j++){
                if(j==current_zero_position) continue;
                if(blocks[i/N][i%N] > blocks[j/N][j%N]) counter++;
            }
        }

        if(N%2 == 1 && counter%2 == 1) return false;
        else if(N%2 == 0 && (counter%2+current_zero_position/N)%2 == 0 && (final_zero_position/N)%2 == 1) return false;
        else if(N%2 == 0 && (counter%2+current_zero_position/N)%2 == 1 && (final_zero_position/N)%2 == 0) return false;
        return true;
    }

    void printPath(){
        cout<<"Number of moves for solution: "<<path.size()<<endl;
        cout<<"Moves:"<<endl;
        for(int i=0; i<path.size();i++){
            cout<<path[i]<<endl;
        }
    }

    vector<string> possible_moves(){
        vector<string> result;
        string last_move = "";
        if(path.size() != 0){
            last_move = path.back();
        }
        if(current_zero_position/N != 0 && last_move!="up") result.push_back("down");
        if(current_zero_position/N != N-1 && last_move!="down") result.push_back("up");
        if(current_zero_position%N != 0 && last_move!="left") result.push_back("right");
        if(current_zero_position%N != N-1 && last_move!="right") result.push_back("left");
        return result;
    }
};