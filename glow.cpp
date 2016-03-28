#include <iostream>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

const int MAX_STATE = 1 << 20;

int state[MAX_STATE + 10];

inline bool out(int x, int y) {
    return x < 0 || x >= 4 || y < 0 || y >= 4;
}

inline pair<int, int> get_cord(int x) {
    int cord = (x >> 16);
    return make_pair(cord / 4, cord % 4);
}

int get_state(string board) {
    int xy = 0;
    int ret = 0;
    for (int i = 0; i < board.size(); i++) {
        ret <<= 1;
        if (board[i] == 'B') {
            ret |= 1;
        }
        if (board[i] == 'W') xy = i;
    }
    return ((xy << 16) | ret);
}

int go(int now, int x, int y, int dx, int dy) {
    dx += x;
    dy += y;
    int from = x * 4 + y;
    int to = dx * 4 + dy;
    // get the board;
    int board = (now & ((1 << 16) - 1));
    // swap the bit (from, to);
    int bit_from = (board >> (15 - from)) & 1;
    int bit_to = (board >> (15 - to)) & 1;
    // if the two bits are the same
    if (bit_from == bit_to) {
        return (to << 16) | board;
    }
    int mask = (1 << (15 - from)) | (1 << (15 - to));
    return (to << 16) | (mask ^ board);
}

inline char get_dir(int dx, int dy) {
    if (dx == 0) {
        if (dy == 1) return 'R';
        if (dy == -1) return 'L';
    } else if (dx == -1) {
        if (dy == 0) return 'U';
    } else if (dx == 1) {
        if (dy == 0) return 'D';
    }
    return 'X';
    
}

void build_solution(int now, int& steps, string& path) {
    if (state[now] == 0)
        return;
    int pre = state[now];
    build_solution(pre, steps, path);
    
    pair<int, int> now_cord = get_cord(now);
    pair<int, int> pre_cord = get_cord(pre);
    
    steps += 1;
    path += get_dir(now_cord.first - pre_cord.first, now_cord.second - pre_cord.second);
    return;
}

pair<int, string> bfs(int start, int end) {
    state[start] = 0;
    queue<int> q;
    q.push(start);
    bool found = false;
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        if (now == end) {
            found = true;
            break;
        }
        
        pair<int, int> xy = get_cord(now);
        for (int dx = -1; dx <= 1; dx++)
            for(int dy = -1; dy <= 1; dy++)
                if (abs(dx) + abs(dy) == 1) { // change one direction
                    if (out(xy.first + dx, xy.second + dy)) continue;
                    int next_state = go(now, xy.first, xy.second, dx, dy);
                    if (state[next_state] != -1) continue;
                    state[next_state] = now;
                    q.push(next_state);
                }
    }
    
    if (!found) return make_pair(-1, "no solution");
    int steps = 0;
    string path = "";
    build_solution(end, steps, path);
    return make_pair(steps, path);
}

int main() {
    
    fill (state, state + MAX_STATE, -1);
    string start, end;
    cin >> start >> end;
    int start_state = get_state(start);
    int end_state = get_state(end);
    
    pair<int, string> ret = bfs(start_state, end_state);
    cout << ret.first << " " << ret.second << endl;
}


