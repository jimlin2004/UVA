#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
 
struct Pt{
    int x, y, z;
    int t;
};
 
int L, R, C;
int a[31][31][31]; //3D dungeon
int dx[6] = {0, 0, 0, 0, 1, -1};
int dy[6] = {0, 0, -1, 1, 0, 0};
int dz[6] = {1, -1, 0, 0, 0, 0};
int visited[31][31][31];
Pt S, E; //start, end
 
int bfs(){
    //BFS
    memset(visited, 0, sizeof(visited));
    queue <Pt> q;
    q.push(S);
    visited[S.x][S.y][S.z] = 1;
    while (q.size()){
        Pt now = q.front();
        q.pop();
        if (now.x == E.x && now.y == E.y && now.z == E.z){
            return now.t;
        }
        for (int i=0; i<6; i++){
            int nx = now.x + dx[i];
            int ny = now.y + dy[i];
            int nz = now.z + dz[i];
            if (nx >= 0 && nx < L && ny >= 0 && ny < R && nz >= 0 && nz < C && a[nx][ny][nz] != '#' && visited[nx][ny][nz] == 0){
                q.push({nx, ny, nz, now.t + 1});
                visited[nx][ny][nz] = 1;
            }
        }
    }
    return -1;
}
 
int main() {
    string s;
    while (cin >> L >> R >> C){
        if (L == 0 && R == 0 && C == 0) break;
        // build the 3D dungeon
        for (int i=0; i<L; i++){
            for (int j=0; j<R; j++){
                cin >> s;
                for (int k=0; k<C; k++){
                    a[i][j][k] = s[k];
                    if (s[k] == 'S'){
                        S = {i, j, k, 0};
                    }
                    if (s[k] == 'E'){
                        E = {i, j, k, 0};
                    }
                }
            }
        }
        int Time = bfs();
         
        if (Time > -1) cout << "Escaped in " << Time << " minute(s).\n";
        else cout << "Trapped!\n";
    }
    return 0;
}