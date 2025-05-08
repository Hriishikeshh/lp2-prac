#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

const int N=3;

struct PuzzleState{
    int puzzle[N][N];
    int zeroCol,zeroRow;
    int g,h;

    bool operator<(const PuzzleState &other) const{
        return (g+h) > (other.g+other.h);
    }

};

int mismatch(const PuzzleState &a, const PuzzleState &goal) {
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (a.puzzle[i][j] != 0 && a.puzzle[i][j] != goal.puzzle[i][j])
                count++;
    return count;
}

bool isequal(PuzzleState a,PuzzleState b){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(a.puzzle[i][j]!=b.puzzle[i][j]) return false;
        }
    }
    return true;;
}

bool isvalid(int row,int col){
    return row>=0 && row<N && col>=0 && col<N;
}

vector<PuzzleState> getchildrenstates(PuzzleState current,const PuzzleState& goal){
    int dr[]={-1,0,+1,0};
    int dc[]={0,+1,0,-1};
    vector<PuzzleState> next;

    for(int i=0;i<N;i++){
        int nr=current.zeroRow+dr[i];
        int nc=current.zeroCol+dc[i];

        if(isvalid(nr,nc)){
            PuzzleState temp=current;
            swap(temp.puzzle[current.zeroRow][current.zeroCol],temp.puzzle[nr][nc]);
            temp.zeroRow=nr;
            temp.zeroCol=nc;
            temp.g=current.g+1;
            temp.h=mismatch(temp,goal);
            next.push_back(temp);
        }
    }

    return next;
}

void printpuzzle(const PuzzleState &state){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<state.puzzle[i][j]<<" ";
        }
        cout<<endl;
    }
}

void aStar(PuzzleState start,PuzzleState goal){
    priority_queue<PuzzleState> pq;
    start.h=mismatch(start,goal);
    pq.push(start);

    while(!pq.empty()){
        PuzzleState current=pq.top();
        pq.pop();

        cout<<"current g(x) :"<<current.g<<" h(x) :"<<current.h<<" f(x) :"<<current.g+current.h<<endl;
        printpuzzle(current);

        if(isequal(current,goal)){
            cout<<"The final is achieved in "<<current.g<<endl;
            return;
        }

        vector<PuzzleState> v=getchildrenstates(current,goal);
        // showchildrenstates(v);

        for(auto &it:v) pq.push(it);

    }

}


int main(){
    PuzzleState start = {{{1, 2, 3}, {4, 0, 5}, {7, 8, 6}}, 1, 1, 0, 0};
    PuzzleState goal  = {{{1, 2, 3}, {4, 5, 6}, {7, 8, 0}}, 2, 2, 0, 0};
    cout<<"start goal :"<<endl;
    printpuzzle(start);
    cout<<"goal to achieve:"<<endl;
    printpuzzle(goal);

    aStar(start,goal);

    cout<<"hello world"<<endl;
}