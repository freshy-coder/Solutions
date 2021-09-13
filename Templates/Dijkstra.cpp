// For Distant Pastures problem
// A good example for flat graph is in Week 4 Shortcut

#include <bits/stdc++.h>
using namespace std;
 
#define int long long // we can do this! but must get rid of int before main()
//Global Variables
int N, A, B;
char grid[30][30];
bool visited[30][30];
priority_queue< pair<int, pair<int, int> > > next1; //(-moves, (x, y) ). The reason why we do negative is because pq goes to the largest value first (so we want that to be lowest weight)
int out = 0;
 
void add (int x, int y, int old_x, int old_y, int moves) {
    // check base case
    if (x < 0 || x >= N || y < 0 || y >= N || visited[x][y]) {
        return;
    }

    // implement transition, add to pq
    if (grid[x][y] == grid[old_x][old_y]) {
        next1.push(make_pair(moves-A, make_pair(x, y)));
    }
    else {
        next1.push(make_pair(moves-B, make_pair(x, y)));
    }
}

main() {
    ifstream cin ("distant.in");
    ofstream cout ("distant.out");
    
    cin >> N >> A >> B;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cin >> grid[i][j];
        }
    }
    
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) { // we're setting every single node as start node at some point, we're running dijkstra on them all
            memset(visited, false, sizeof(visited) ); // reset visited array
            next1.push(make_pair(0, make_pair(i, j))); // add start state (-moves, (x, y) ) 
            while (!next1.empty()) {

                // extract item from pq
                int moves = next1.top().first;
                int x = next1.top().second.first;
                int y = next1.top().second.second;
                next1.pop();
                
                if (visited[x][y]) { // don't visit if already done so
                    continue;
                }
                visited[x][y] = true; // current spot is visited
                out = max(out, -moves);
                
                // transitions - check add function
                add(x-1, y, x, y, moves);
                add(x+1, y, x, y, moves);
                add(x, y-1, x, y, moves);
                add(x, y+1, x, y, moves);
            }
        }
    }
    
    cout << out << endl;
}