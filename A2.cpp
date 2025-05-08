#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int N = 3;

struct PuzzleState {
    int puzzle[N][N];
    int zeroRow, zeroCol;
    int g, h;

    bool operator<(const PuzzleState &other) const {
        return (g + h) > (other.g + other.h); // Min-heap
    }
};

bool isEqual(const PuzzleState &a, const PuzzleState &b) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (a.puzzle[i][j] != b.puzzle[i][j])
                return false;
    return true;
}

int calculateMisplaced(const PuzzleState &a, const PuzzleState &goal) {
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (a.puzzle[i][j] != 0 && a.puzzle[i][j] != goal.puzzle[i][j])
                count++;
    return count;
}

bool isValid(int r, int c) {
    return r >= 0 && r < N && c >= 0 && c < N;
}

vector<PuzzleState> getNextStates(PuzzleState current, const PuzzleState &goal) {
    vector<PuzzleState> next;
    int dr[4] = {-1, 1, 0, 0}; // Up, Down
    int dc[4] = {0, 0, -1, 1}; // Left, Right

    for (int i = 0; i < 4; i++) {
        int nr = current.zeroRow + dr[i];
        int nc = current.zeroCol + dc[i];

        if (isValid(nr, nc)) {
            PuzzleState temp = current;
            swap(temp.puzzle[current.zeroRow][current.zeroCol], temp.puzzle[nr][nc]);
            temp.zeroRow = nr;
            temp.zeroCol = nc;
            temp.g = current.g + 1;
            temp.h = calculateMisplaced(temp, goal);
            next.push_back(temp);
        }
    }

    return next;
}

void printPuzzle(const PuzzleState &state) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << state.puzzle[i][j] << " ";
        cout << endl;
    }
}

void showChildrenStates(const vector<PuzzleState> &children) {
    cout << "\nGenerated Children:\n";
    for (const auto &child : children) {
        cout << "g(n): " << child.g << ", h(n): " << child.h << ", f(n): " << child.g + child.h << endl;
        printPuzzle(child);
        cout << "----\n";
    }

    // Also show the best one (minimum f(n))
    auto best = min_element(children.begin(), children.end(), [](const PuzzleState &a, const PuzzleState &b) {
        return (a.g + a.h) < (b.g + b.h);
    });

    if (best != children.end()) {
        cout << "Selected Next Move (Best f(n)):\n";
        cout << "g(n): " << best->g << ", h(n): " << best->h << ", f(n): " << best->g + best->h << endl;
        printPuzzle(*best);
        cout << "=========================\n";
    }
}

void aStar(PuzzleState start, PuzzleState goal) {
    priority_queue<PuzzleState> pq;
    start.h = calculateMisplaced(start, goal);
    pq.push(start);

    while (!pq.empty()) {
        PuzzleState current = pq.top();
        pq.pop();

        cout << "Current State (g = " << current.g << ", h = " << current.h << ", f = " << current.g + current.h << "):\n";
        printPuzzle(current);
        cout << "--------------------\n";

        if (isEqual(current, goal)) {
            cout << "Goal Reached in " << current.g << " moves!\n";
            return;
        }

        vector<PuzzleState> children = getNextStates(current, goal);
        showChildrenStates(children);

        for (auto &child : children)
            pq.push(child);
    }
}

int main() {
    // You can modify this for testing any other case
    PuzzleState start = {{{1, 2, 3}, {4, 0, 5}, {7, 8, 6}}, 1, 1, 0, 0};
    PuzzleState goal  = {{{1, 2, 3}, {4, 5, 6}, {7, 8, 0}}, 2, 2, 0, 0};

    cout << "Initial Puzzle:\n";
    printPuzzle(start);
    cout << "\nStarting A* Search...\n";
    aStar(start, goal);

    return 0;
}