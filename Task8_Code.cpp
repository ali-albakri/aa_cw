// ___       _ _   ___          _     ___      _             
//| _ ) __ _| | | / __| ___ _ _| |_  / __| ___| |_ _____ _ _ 
//| _ \/ _` | | | \__ \/ _ \ '_|  _| \__ \/ _ \ \ V / -_) '_|
//|___/\__,_|_|_| |___/\___/_|  \__| |___/\___/_|\_/\___|_|  
// Using A* Search

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <random>
#include <chrono> 

using namespace std;

const string colors[] = {
    "Red", "Orange", "Yellow", "Green", "Blue", "Purple",
    "Pink", "Cyan", "Gold", "Lime", "Brown", "Magenta"
};

struct Move {
    int indexfrom;
    int indexto;
};

struct State {
    vector<vector<string>> stacks;
    //f(n) = g(n) + h(n)
    int g = 0;
    int h = 0;
    int f = 0;

    // reconstructing path vector (for paths taken)
    vector<Move> paths;

    // priority queue comparator
    bool operator>(const State& other) const {
        return f > other.f;
    }

    // unique key for visited set and they are canonical meaning order of the
    // vector doesn't matter but rather the content itself.
    string fetchstatekey() const {
        vector<string> stackStrings;

        for (size_t i = 0; i < stacks.size(); i++) {
            string str = "";
            for (size_t j = 0; j < stacks[i].size(); j++) {
                str += stacks[i][j] + ",";
            }
            stackStrings.push_back(str);
        }

        sort(stackStrings.begin(), stackStrings.end());

        string key = "";
        for (size_t i = 0; i < stackStrings.size(); i++) {
            key += "{" + stackStrings[i] + "}";
        }

        return key;
    }
};

class ballsortfunc {
private:
    int colorsnum;
    int ballsperstack;
    int extraemptystack;
    int totalstackcount;

    int heuristicCalc(const vector<vector<string>>& stacks) {
        int penalty = 0;

        for (size_t i = 0; i < stacks.size(); i++) {
            const auto& stack = stacks[i];
            if (stack.empty()) continue;

            string baseColor = stack[0];
            bool mismatchFound = false;

            for (size_t i = 1; i < stack.size(); i++) {
                if (mismatchFound) {
                    penalty++;
                }
                else if (stack[i] != baseColor) {
                    mismatchFound = true;
                    penalty++;
                }
            }
        }
        return penalty;
    }

    bool goalstatus(const State& state) {
        for (size_t i = 0; i < state.stacks.size(); i++) {
            const auto& stack = state.stacks[i];
            if (stack.empty()) continue;
            if (stack.size() != ballsperstack) return false;

            string color = stack[0];
            for (size_t j = 0; j < stack.size(); j++) {
                if (stack[j] != color) return false;
            }
        }
        return true;
    }

public:
    ballsortfunc(int colors, int balls, int extra)
        : colorsnum(colors), ballsperstack(balls), extraemptystack(extra) {
        totalstackcount = colorsnum + extraemptystack;
    }

    vector<vector<string>> generateboard() {
        vector<vector<string>> board(totalstackcount);
        vector<string> tempballs;

        for (int i = 0; i < colorsnum; i++) {
            for (int j = 0; j < ballsperstack; j++) {
                tempballs.push_back(colors[i]);
            }
        }

        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(tempballs.begin(), tempballs.end(), default_random_engine(seed));

        int ballIndex = 0;
        for (int i = 0; i < colorsnum; i++) {
            for (int j = 0; j < ballsperstack; j++) {
                board[i].push_back(tempballs[ballIndex++]);
            }
        }
        return board;
    }

    void printboard(const vector<vector<string>>& stacks) {
        cout << "- Board State -" << endl;
        for (int i = 0; i < stacks.size(); i++) {
            cout << "Stack " << i + 1 << ": ";
            if (stacks[i].empty()) {
                cout << "[Empty]";
            }
            else {
                for (const string& b : stacks[i]) {
                    cout << b << " ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    // this is used to print the moves and return the final solved board state & its run after A* is complete
    vector<vector<string>> printsolutionandpath(vector<vector<string>> simulationBoard, const vector<Move>& history) {
        cout << "- Solution Found -" << endl;
        cout << "Moves Required: " << history.size() << endl;

        int step = 1;
        for (size_t i = 0; i < history.size(); i++) {
            const Move& move = history[i];
            string ballcolor = simulationBoard[move.indexfrom].back();

            cout << "(" << step++ << ") Move " << ballcolor << " from Stack " << move.indexfrom + 1 << " to Stack " << move.indexto + 1 << endl;

            simulationBoard[move.indexto].push_back(ballcolor);
            simulationBoard[move.indexfrom].pop_back();
        }

        return simulationBoard;
    }

    vector<vector<string>> solve(vector<vector<string>> initialConfig) {
        priority_queue<State, vector<State>, greater<State>> openset;
        set<string> closedset;

        State startstate;
        startstate.stacks = initialConfig;
        startstate.g = 0;
        startstate.h = heuristicCalc(initialConfig);
        startstate.f = startstate.g + startstate.h;

        openset.push(startstate);

        cout << "Solver is thinking... (Algorithm: A*)" << endl;

        int nodesexploredcount = 0;

        while (!openset.empty()) {
            State current = openset.top();
            openset.pop();

            nodesexploredcount++;
            // this is a safety limit prevents infinite freezing on situations such as impossible random seeds
            if (nodesexploredcount > 250000) {
                cout << "Complexity limit reached (250k nodes). Try a simpler board or more empty stacks." << endl;
                return {};
            }

            if (goalstatus(current)) {
                cout << "\nNodes Explored: " << nodesexploredcount << endl;

                // Call printSolutionPath, which prints the moves and returns the solved board.
                vector<vector<string>> solvedBoard = printsolutionandpath(initialConfig, current.paths);

                // Return the final solved board state
                return solvedBoard;
            }

            string key = current.fetchstatekey();
            if (closedset.count(key)) continue;
            closedset.insert(key);

            for (int i = 0; i < totalstackcount; i++) {
                if (current.stacks[i].empty()) continue;

                for (int j = 0; j < totalstackcount; j++) {
                    if (i == j) continue;
                    if (current.stacks[j].size() >= ballsperstack) continue;

                    string ball = current.stacks[i].back();
                    if (current.stacks[j].empty() || current.stacks[j].back() == ball) {

                        if (current.stacks[j].empty()) {
                            bool sameColor = true;
                            for (const string& s : current.stacks[i])
                                if (s != current.stacks[i][0]) sameColor = false;
                            if (sameColor) continue;
                        }

                        State next = current;
                        next.stacks[j].push_back(ball);
                        next.stacks[i].pop_back();
                        next.paths.push_back({ i, j });

                        next.g = current.g + 1;
                        next.h = heuristicCalc(next.stacks);
                        next.f = next.g + next.h;

                        openset.push(next);
                    }
                }
            }
        }

        cout << "No solution found." << endl;
        return {}; // no solution = empty board
    }
};


int main() {
    int numberofcolors, numberofballs, numberofextra;

    cout << "- Ball Sorting Game Solver -\n";

    cout << "Input number of Colors (ex. 1-12): ";
    while (!(cin >> numberofcolors) || numberofcolors < 1 || numberofcolors > 12) {
        cout << "Invalid. Enter 1-12: ";
        cin.clear(); cin.ignore(1000, '\n');
    }

    cout << "Input Balls per Stack (ex. 4): ";
    cin >> numberofballs;

    cout << "Input Extra Empty Stacks (ex. 2): ";
    cin >> numberofextra;

    ballsortfunc game(numberofcolors, numberofballs, numberofextra);

    cout << endl << "Generating solvable scrambled board..." << endl;
    vector<vector<string>> board = game.generateboard();

    cout << endl << "- Start State -" << endl;
    game.printboard(board);

    cout << "Click 'Enter' to proceed and solve...";
    cin.ignore(); cin.get();

    vector<vector<string>> solvedBoard = game.solve(board);

    // if solution is found and board isnt empty
    if (!solvedBoard.empty()) {
        cout << endl << "- Final State -" << endl;
        game.printboard(solvedBoard);
    }

    cout << endl << "Process complete. Click 'Enter' to exit program.";
    cin.get();
    return 0;
}