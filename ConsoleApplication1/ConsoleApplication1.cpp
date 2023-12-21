#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_ROWS = 5;
const int MAX_COLS = 10;

class Maze {
public:
    Maze();
    void create();
    void print();
    bool move(string direction);
    bool isGameOver();

private:
    char maze[MAX_ROWS][MAX_COLS];
    pair<int, int> start;
    pair<int, int> end;
    pair<int, int> currentPosition;
};

class Player {
public:
    Player(Maze& maze);
    void makeMove(string direction);

private:
    Maze& gameMaze;
};

// Реализация методов класса Maze
Maze::Maze() {
    srand(time(0));
}

void Maze::create() {
    for (int i = 0; i < MAX_ROWS; ++i) {
        for (int j = 0; j < MAX_COLS; ++j) {
            if (rand() % 10 < 3) {
                maze[i][j] = '#';
            }
            else {
                maze[i][j] = ' ';
            }
        }
    }

    start = make_pair(0, 0);
    end = make_pair(MAX_ROWS - 1, MAX_COLS - 1);
    maze[start.first][start.second] = 'A';
    maze[end.first][end.second] = 'X';

    currentPosition = start;
}

void Maze::print() {
    system("cls"); // очистка экрана (для UNIX-подобных систем)
    for (int i = 0; i < MAX_ROWS; ++i) {
        for (int j = 0; j < MAX_COLS; ++j) {
            cout << maze[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

bool Maze::move(string direction) {
    pair<int, int> newPosition = currentPosition;

    if (direction == "UP" && currentPosition.first > 0 && maze[currentPosition.first - 1][currentPosition.second] != '#') {
        newPosition.first = currentPosition.first - 1;
    }
    else if (direction == "DOWN" && currentPosition.first < MAX_ROWS - 1 && maze[currentPosition.first + 1][currentPosition.second] != '#') {
        newPosition.first = currentPosition.first + 1;
    }
    else if (direction == "LEFT" && currentPosition.second > 0 && maze[currentPosition.first][currentPosition.second - 1] != '#') {
        newPosition.second = currentPosition.second - 1;
    }
    else if (direction == "RIGHT" && currentPosition.second < MAX_COLS - 1 && maze[currentPosition.first][currentPosition.second + 1] != '#') {
        newPosition.second = currentPosition.second + 1;
    }

    if (newPosition != currentPosition) {
        maze[currentPosition.first][currentPosition.second] = ' ';
        currentPosition = newPosition;
        maze[currentPosition.first][currentPosition.second] = 'A';
        return true;
    }

    return false;
}

bool Maze::isGameOver() {
    return currentPosition == end;
}

// Реализация методов класса Player
Player::Player(Maze& maze) : gameMaze(maze) {}

void Player::makeMove(string direction) {
    gameMaze.move(direction);
}

int main() {
    Maze gameMaze;
    Player player(gameMaze);

    gameMaze.create();

    while (!gameMaze.isGameOver()) {
        gameMaze.print();

        string userInput;
        cout << "Choose your direction: (UP/DOWN/LEFT/RIGHT): ";
        cin >> userInput;

        if (userInput == "QUIT") {
            break;
        }

        player.makeMove(userInput);
    }

    if (gameMaze.isGameOver()) {
        cout << "Congratulation! You've reached your destination!" << endl;
    }

    return 0;
}