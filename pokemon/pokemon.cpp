#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum class Square {
    Ice, Wall, Walkable, Grass
};

struct Position {
    int x, y;

    Position(int _x, int _y) : x(_x), y(_y) {
    }

    Position operator+(const Position& other) const {
        return Position(x + other.x, y + other.y);
    }

    Position operator-(const Position& other) const {
        return Position(x - other.x, y - other.y);
    }

    Position& operator+= (const Position& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Position& operator-= (const Position& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
};

struct Distance {
    bool reachable;
    int distance;

    Distance() : reachable(false), distance(0) {
    }

    Distance(int _distance) : reachable(true), distance(_distance) {
    }

    Distance operator+(int _distance) {
        if (reachable)
            return Distance(distance + _distance);
        else
            return Distance();
    }

    bool operator<(const Distance& other) const {
        if (reachable != other.reachable) {
            return reachable;
        }
        return distance < other.distance;
    }

    bool operator==(const Distance& other) const {
        return reachable == other.reachable && distance == other.distance;
    }
};

template <class T>
class Map {
    private:
        vector<vector<T>> squares;

        bool isOnMap(const Position& position) {
            return position.x >= 0 && position.y >= 0 && position.x < w && position.y < h;
        }

    protected:
        size_t w, h;

    public:
        
        Map(vector<vector<T>>&& _squares) : squares(_squares) {
            w = getWidth();
            h = getHeight();
        }

        size_t getWidth() {
            return squares[0].size();
        }

        size_t getHeight() {
            return squares.size();
        }

        T& at(const Position& position) {
            return squares[position.y][position.x];
        }
};

class InputMap : public Map<Square> {
    private:

        Position goal;

        vector<Position> getAdjacent(const Position& pos) {
            vector<Position> adjacent;
            int dx[] = {1, 0, -1, 0};
            int dy[] = {0, 1, 0, -1};
            for (size_t i = 0; i < 4; i++) {
                Position to(pos.x + dx[i], pos.y + dy[i]);
                adjacent.push_back(to);
            }
            return adjacent;
        }

        vector<Position> getOrigins(const Position& pos) {
            vector<Position> origins;
            auto adjacentSquares = getAdjacent(pos);
            for (auto adjacent : adjacentSquares) {
                auto direction = adjacent - pos;
                if (at(pos) != Square::Ice || at(pos - direction) == Square::Wall) {
                    auto currentPosition = adjacent;
                    while (at(currentPosition) == Square::Ice) {
                        origins.push_back(currentPosition);
                        currentPosition += direction;
                    }
                    if (at(currentPosition) != Square::Wall) {
                        origins.push_back(currentPosition);
                    }
                }
            }
            return origins;
        }

    public:

        InputMap(vector<vector<Square>>&& squares, const Position& _goal) : Map<Square>(move(squares)), goal(_goal) {
        }

        Map<Distance> getDistancesToGoal() {
            Map<Distance> distance(vector<vector<Distance>>(h, vector<Distance>(w)));
            switch(at(goal)) {
                case Square::Wall: return distance;
                case Square::Ice: {
                    distance.at(goal) = Distance(0);
                    break;
                }
                case Square::Walkable: {
                    distance.at(goal) = Distance(0);
                    break;
                }
                case Square::Grass: {
                    distance.at(goal) = Distance(1);
                    break;
                }
            }
            queue<Position> currentPositions;
            queue<Position> nextPositions;
            nextPositions.push(goal);
            while (!nextPositions.empty()) {
                swap(currentPositions, nextPositions);
                while (!currentPositions.empty()) {
                    auto currentPosition = currentPositions.front();
                    currentPositions.pop();
                    for (auto to : getOrigins(currentPosition)) {
                        //auto newDistance = distance.at(currentPosition) + (at(currentPosition) == Square::Grass ? 1 : 0);
                        auto newDistance = distance.at(currentPosition) + 1;
                        if (newDistance < distance.at(to)) {
                            distance.at(to) = newDistance;
                            if (distance.at(to) == distance.at(currentPosition)) {
                                currentPositions.push(to);
                            }
                            else {
                                nextPositions.push(to);
                            }
                        }
                    }
                }
            }
            return distance;
        }
};

InputMap readMap() {
    int w, h;
    cin >> w >> h;
    vector<string> input(h);
    vector<vector<Square>> squares(h, vector<Square>(w));
    int numGoals = 0;
    Position goal(-1, -1);
    for (int i = 0; i < h; i++) {
        cin >> input[i];
        for (int j = 0; j < w; j++) {
            switch(input[i][j]) {
                case '.' : {
                    squares[i][j] = Square::Walkable;
                    break;
                }
                case ',' : {
                    squares[i][j] = Square::Grass;
                    break;
                }
                case '_' : {
                    squares[i][j] = Square::Ice;
                    break;
                }
                case '#' : {
                    squares[i][j] = Square::Wall;
                    break;
                }
                case 'M' : {
                    numGoals++;
                    squares[i][j] = Square::Walkable;
                    goal = Position(j, i);
                    break;
                }
                default : {
                    throw invalid_argument("Unknown square type.");
                }
            }
        }
    }

    if (numGoals != 1) {
        throw invalid_argument("Must have exactly one goal");
    }

    return InputMap(move(squares), goal);
}

int main() {
    auto inputMap = readMap();

    // The 1-indexed row and column of the goal
    int goalRow, goalColumn;
    cin >> goalRow >> goalColumn;

    Position goal(goalRow - 1, goalColumn - 1);

    auto distance = inputMap.getDistancesToGoal();
    for (size_t i = 0; i < distance.getHeight(); i++) {
        for (size_t j = 0; j < distance.getWidth(); j++) {
            if (j > 0)
                cout << "\t";
            Position pos((int)j, (int)i);
            if (distance.at(pos).reachable)
                cout << distance.at(pos).distance;
            else
                cout << "-1";
        }
        cout << endl;
    }
}
