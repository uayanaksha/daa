#include <bits/stdc++.h>
#include <vector>

using namespace std;

class Board {
    private:
        vector<vector<int>> board;
        vector<int> ld;
        vector<int> rd;
        vector<int> cl;
        unsigned n;

    public:
        Board(const unsigned &n) {
            this->n = n;
            board = vector<vector<int>>(n, vector<int>(n, 0));
            ld = vector<int>((2*n - 1), 0);
            rd = vector<int>((2*n - 1), 0);
            cl = vector<int>(n, 0);
        }

        void print(){
            cout << "Board[" << n << "x" << n << "]: {" << endl;
            for(vector<int> rows : board){
                cout << "    ";
                for(int cell : rows){
                    cout << " " << (cell == 0 ? "." : "Q");
                }   cout << endl;
            }   cout << "}" << endl;
        }

        void solveNQ(){
            if(solveNQ_priv(0)) cout << "Nqueen solved" << endl;
            else cout << "Cannot be solved" << endl;
        }

    private:
        bool solveNQ_priv(int col){
            if(col >= n) return true;
            int ldIdx, rdIdx;
            for (int row = 0; row < n; row++) {
                ldIdx = (n-1) + (row-col);
                rdIdx = row + col;
                if(ld[ldIdx] != 1 && rd[rdIdx] != 1 && cl[row] != 1){
                    board[col][row] = ld[ldIdx] = rd[rdIdx] = cl[row] = 1;
                    if(solveNQ_priv(col + 1)) return true;
                    board[col][row] = ld[ldIdx] = rd[rdIdx] = cl[row] = 0;
                }
            }   return false;
        }
};

int main(void){
    unsigned n;
    cout << "Enter N queen: " && cin >> n;
    Board board(n);
    board.print();
    board.solveNQ();
    board.print();
}
