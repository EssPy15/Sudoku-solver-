#include<bits/stdc++.h>
using namespace std;

const int boardsize = 9;
const int cellsize = 3;

int board[boardsize][boardsize];

/*
0 1 0 0
0 0 4 0
0 4 0 0
0 0 3 0
*/

int takenRow[boardsize];
int takenCol[boardsize];
int takenGrid[cellsize][cellsize];

int ans = 0;

void makemove(int ch, int row, int col) {
    board[row][col]=ch;
    takenRow[row]^=(1<<ch);
    takenCol[col]^=(1<<ch);
    takenGrid[row/cellsize][col/cellsize]^=(1<<ch);
}

void revertmove(int ch, int row, int col) {
    board[row][col]=0;
    takenRow[row]^=(1<<ch);
    takenCol[col]^=(1<<ch);
    takenGrid[row/cellsize][col/cellsize]^=(1<<ch);
}

int getchoices(int row, int col) {
    int taken = (takenRow[row]|takenCol[col]|takenGrid[row/cellsize][col/cellsize]);
    int nottaken = ((1<<(boardsize+1))-1)^taken;
    //int nottaken = (~taken) & ((1<<(boardsize+1))-1);
    if(nottaken & 1) nottaken^=1;
    return nottaken;
}

void rec(int row, int col) {
    if(col == boardsize) {
        rec(row+1,0);
        return;
    }
    if(row == boardsize) {
        //base case
        ans++;
        cout << "ans " << ans << endl;
        for(int i = 0; i < boardsize; i++) {
            for(int j = 0; j < boardsize; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

    if(board[row][col] == 0) {
        // we need to fill
        int chmask = getchoices(row, col);

        for(int ch = 1; ch <= boardsize; ch++) {
            if(chmask & (1<<ch)) {
                makemove(ch, row, col);
                rec(row, col+1);
                revertmove(ch, row, col);
            }
        }
    } else {
        // pre-filled (Assume there is a sol)
        rec(row, col+1);
    }
}

void solve(){
    for(int i=0; i<boardsize; i++) {
        for (int j = 0; j < boardsize; j++) {
            int ch;
            cin>>ch;
            makemove(ch,i,j);
        }
    }
    rec(0,0);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
    
}