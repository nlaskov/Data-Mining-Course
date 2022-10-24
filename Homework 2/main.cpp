#include<iostream>
#include<set>
#include<chrono>
#include<vector>
using namespace std;
std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;

class Board{
    private:
        int N;
        vector< int > board;
        vector< int > f_col,f_mdiag,f_sdiag;
    
    public:

        Board(int _N){
            this->N = _N;
            for(int i=0;i<N;i++){
                f_col.push_back(0);
            }
            for(int i=0;i<(N-1)+N;i++){
                f_mdiag.push_back(0);
                f_sdiag.push_back(0);
            }
            setRandomBoard();
        }

        void swapQueens(int i,int j){
            f_col[board[i]]--;
            f_mdiag[i +board[i]]--;
            f_sdiag[N - i - 1 + board[i]]--;    
            
            board[i] = j;

            f_col[board[i]]++;  
            f_mdiag[i +board[i]]++;
            f_sdiag[N - i - 1 + board[i]]++;    
        }

        void setRandomBoard(){
            for(int i=0;i<N;i++){
                board.push_back(i);
                f_col[i]++;
                f_mdiag[i+i]++;
                f_sdiag[N - i - 1 + i]++;
            }
            
            for(int i = 0;i<N;i++){
                int j = rand()%N;
                f_mdiag[i +board[i]]--;
                f_sdiag[N - i - 1 + board[i]]--;
                f_mdiag[j +board[j]]--;
                f_sdiag[N - j - 1 + board[j]]--;

                int swap = board[i];
                board[i] = board[j];
                board[j] = swap;

                f_mdiag[i +board[i]]++;
                f_sdiag[N - i - 1 + board[i]]++;
                f_mdiag[j +board[j]]++;
                f_sdiag[N - j - 1 + board[j]]++;
            }
        }

        void solver(){
            int moves =0;
            vector<int> candidates;
           
           while(true){
            int maxConflict = 0;
            candidates.clear();
            for(int i=0;i<N;i++){
                int conflict = f_col[board[i]]-1 + f_mdiag[i+board[i]]-1 + f_sdiag[N - i - 1 + board[i]] - 1;
                if(conflict == maxConflict)candidates.push_back(i);
                else if(conflict > maxConflict){
                    maxConflict = conflict;
                    candidates.clear();
                    candidates.push_back(i);
                }
            }

            if(maxConflict == 0){
                return;
            }

            int worstQueen = candidates[rand()%candidates.size()];
            int minConflict = N;
            candidates.clear();

            for(int i=0;i<N;i++){
                int conflict = 0;
                if(board[worstQueen] == i){
                    conflict = f_col[i]-1 + f_mdiag[worstQueen+i]-1 + f_sdiag[N - worstQueen - 1 + i] - 1;
                }
                else{
                    conflict = f_col[i] + f_mdiag[worstQueen+i] + f_sdiag[N - worstQueen - 1 + i];
                }

                if(conflict == minConflict)candidates.push_back(i);
                else if(conflict < minConflict){
                    minConflict = conflict;
                    candidates.clear();
                    candidates.push_back(i);
                }
            }

            if(!candidates.empty()){
                swapQueens(worstQueen,candidates[rand()%candidates.size()]);
            }

            moves++;

            if(moves == N*N){
                setRandomBoard();
                moves=0;
            }
           }
        }

        void printBoard(){
            for(int i=0;i<N;i++){
                for(int j=0;j<N;j++){
                    if(j == board[i]) cout<<"* ";
                    else cout<<"_ ";
                }
                cout<<endl;
            }
        }
};

int main(){
    int N;
    //cin>>N;
    N=10000;
    srand(time(NULL));
    start = chrono::high_resolution_clock::now();
    Board board(N);

    //board.printBoard();
    board.solver();
    cout<<"++++++++++++++++"<<endl;
    //board.printBoard();
    stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    printf("Time to find solution: %.3f seconds.\n", duration.count() * 0.001);

}