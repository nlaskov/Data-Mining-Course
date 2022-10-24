#include<iostream>
#include<set>
#include<vector>
using namespace std;

class Board{
    private:
        int N;
        vector< pair<int, set<int> > > board;
        set<int> queens_conflicts;

    public:

        Board(int _N){
            this->N = _N;
            for(int i=0;i<N;i++){
                set<int> temp;
                board.push_back(pair<int, set<int> >(rand()%N ,temp));
            }

            setConflict();
        }

        int randomQueen(){
            int queen_ind = rand()%queens_conflicts.size();

            auto ind = queens_conflicts.begin();
            for(int i=0;i<queen_ind;i++){
                ind++;
            }
            return *ind;
        }

        void setConflict(){
            for(int i=0;i<N;i++){
                board[i].second = checkConflict(i,board[i].first);
                if(!board[i].second.empty())queens_conflicts.insert(i);
            }
        }

        set<int> checkConflict(int queen_row, int queen_col){
            set<int> conflicts;

            for(int i=0;i<N;i++){
                if(i == queen_row)continue;
                if(board[i].first == queen_col) conflicts.insert(i);
                else if(board[i].first == queen_col + (i-queen_row))conflicts.insert(i);
                else if(board[i].first == queen_col - (i-queen_row))conflicts.insert(i);
            }

            return conflicts;
        }

        void findMinConflict(int queen_row){
            int min_conflicts_ind = board[queen_row].first;
            set<int> min_conflicts = board[queen_row].second;
            for(int i=0;i<N;i++){
                set<int> temp = checkConflict(queen_row,i);
                if(temp.size() < min_conflicts.size()){
                    min_conflicts = temp;
                    min_conflicts_ind = i;
                }
                else if(temp.size() == min_conflicts.size()){
                    if(rand()%2 == 0){
                        min_conflicts = temp;
                        min_conflicts_ind = i;
                    }
                }
            }

            setNewPosition(queen_row,min_conflicts_ind,min_conflicts);
        }

        void setNewPosition(int queen_row,int queen_col,set<int> newConflicts){
            for(auto& ind: board[queen_row].second){
                board[ind].second.erase(board[ind].second.find(queen_row));
                if(board[ind].second.empty())queens_conflicts.erase(queens_conflicts.find(ind));
            }

            board[queen_row].first = queen_col;
            board[queen_row].second.clear();
            board[queen_row].second = newConflicts;
            if(board[queen_row].second.empty()){
                queens_conflicts.erase(queens_conflicts.find(queen_row));
            }
            for(auto& ind: board[queen_row].second){
                board[ind].second.insert(queen_row);
                queens_conflicts.insert(ind);
            }
        }

        bool solver(){

            for(int i=0;i<100;i++){
                int queen = randomQueen();
                //printBoard();
                findMinConflict(queen);
                //cout<<"----------------"<<endl;
                if(queens_conflicts.empty())return true;
            }

            return false;
        }

        void printBoard(){
            for(int i=0;i<N;i++){
                for(int j=0;j<N;j++){
                    if(j == board[i].first) cout<<"* ";
                    else cout<<"_ ";
                }
                cout<<endl;
            }
        }
};