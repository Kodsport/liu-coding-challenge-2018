#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <random>
#include <algorithm>

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

    bool operator== (const Position& other) const {
        return x == other.x && y == other.y;
    }
};

class Map {
    private:
        vector<vector<Square>> squares;

        bool isOnMap(const Position& position) {
            return position.x >= 0 && position.y >= 0 && position.x < w && position.y < h;
        }

    protected:
        size_t w, h;

    public:

        Map() {
        }
        
        Map(vector<vector<Square>>&& _squares) : squares(_squares) {
            w = getWidth();
            h = getHeight();
        }

        size_t getWidth() {
            return squares[0].size();
        }

        size_t getHeight() {
            return squares.size();
        }

        const Square& at(const Position& position) const {
            return squares[position.y][position.x];
        }

        Square& at(const Position& position) {
            return squares[position.y][position.x];
        }
};

class Generator {

    protected:
        Square getRandomSquare(const map<Square, double>& probabilities, mt19937& randomnessEngine) {
            uniform_real_distribution<double> realDistribution(0.0, 1.0);
            double x = realDistribution(randomnessEngine);
            for (auto& it : probabilities) {
                x -= it.second;
                if (x <= 0) {
                    return it.first;
                }
            }
            return Square::Walkable;
        }
};

class RandomGenerator : public Generator {

    public:
        Map generate(int height, int width, map<Square, double> probabilities, mt19937& randomnessEngine) {
            double totalWeight = 0.0;
            for (const auto& it : probabilities)
                totalWeight += it.second;
            for (auto& it : probabilities)
                it.second /= totalWeight;

            vector<vector<Square>> squares(height, vector<Square>(width));
            for (size_t y = 0; y < height; y++) {
                for (size_t x = 0; x < width; x++) {
                    if (x == 0 || x+1 == width || y == 0 || y+1 == height) {
                        squares[y][x] = Square::Wall;
                    }
                    else {
                        squares[y][x] = getRandomSquare(probabilities, randomnessEngine);
                    }
                }
            }
            return Map(move(squares));
        }
};

class LabyrinthGenerator : public Generator {

    protected:
        vector<vector<bool>> visited;
        
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

        virtual void dfs(const Position& pos, const Map& m, mt19937& randomnessEngine) = 0;

    public:
        Map generate(int height, int width, map<Square, double> probabilities, mt19937& randomnessEngine) {
            double totalWeight = 0.0;
            for (const auto& it : probabilities)
                totalWeight += it.second;
            for (auto& it : probabilities)
                it.second /= totalWeight;

            vector<vector<Square>> squares(height, vector<Square>(width));
            for (size_t y = 0; y < height; y++) {
                for (size_t x = 0; x < width; x++) {
                    if (x == 0 || x+1 == width || y == 0 || y+1 == height) {
                        squares[y][x] = Square::Wall;
                    }
                    else {
                        squares[y][x] = Square::Walkable;
                    }
                }
            }
            Map m(move(squares));

            visited = vector<vector<bool>>(height, vector<bool>(width, false));
            dfs(Position(1, 1), m, randomnessEngine);

            for (size_t y = 0; y < height; y++) {
                for (size_t x = 0; x < width; x++) {
                    Position pos(x, y);
                    if (visited[y][x]) {
                        m.at(pos) = getRandomSquare(probabilities, randomnessEngine);
                    }
                    else {
                        m.at(pos) = Square::Wall;
                    }
                }
            }
            
            return m;
        }
};

class RandomLabyrinthGenerator : public LabyrinthGenerator {
    private:
        void dfs(const Position& pos, const Map& m, mt19937& randomnessEngine) {
            visited[pos.y][pos.x] = true;

            auto adjacent = getAdjacent(pos);
            shuffle(adjacent.begin(), adjacent.end(), randomnessEngine);
            for (const Position& to : adjacent) {
                if (m.at(to) == Square::Wall || visited[to.y][to.x]) {
                    continue;
                }
                int adjacentVisited = 0;
                for (const Position& adj : getAdjacent(to)) {
                    if (visited[adj.y][adj.x]) {
                        ++adjacentVisited;
                    }
                }
                if (adjacentVisited > 1) {
                    continue;
                }
                dfs(to, m, randomnessEngine);
            }
        }
};

class LongPathLabyrinthGenerator : public LabyrinthGenerator {
    private:

        Position previousPosition;

        void dfs(const Position& pos, const Map& m, mt19937& randomnessEngine) {
            visited[pos.y][pos.x] = true;

            auto adjacent = getAdjacent(pos);
            sort(adjacent.begin(), adjacent.end(), [&](const Position& p1, const Position& p2) -> bool{
                int dx1 = p1.x - previousPosition.x;
                int dy1 = p1.y - previousPosition.y;
                int dx2 = p2.x - previousPosition.x;
                int dy2 = p2.y - previousPosition.y;
                int d1 = dx1+dy1;
                int d2 = dx2+dy2;
                double sum1 = 0.2*max(p1.x, p1.y)+p1.x+p1.y+2*d1*d1-0.1*dx1*dx1-0.1*dy1*dy1;
                double sum2 = 0.2*max(p2.x, p2.y)+p2.x+p2.y+2*d2*d2-0.1*dx2*dx2-0.1*dy2*dy2;
                if (sum1 != sum2) {
                    return sum1 < sum2;
                }
                return p1.x < p2.x;
            });
            for (const Position& to : adjacent) {
                if (m.at(to) == Square::Wall || visited[to.y][to.x]) {
                    continue;
                }
                vector<Position> adjacentVisited;
                for (const Position& adj : getAdjacent(to)) {
                    if (visited[adj.y][adj.x]) {
                        adjacentVisited.push_back(adj);
                    }
                }
                if (adjacentVisited.size() > 2) {
                    continue;
                }
                if (adjacentVisited.size() == 2){ 
                    auto diff = adjacentVisited[1] - adjacentVisited[0];
                    if (diff.x*diff.x + diff.y*diff.y > 2) {
                        continue;
                    }
                    auto otherPoint = adjacentVisited[0] + adjacentVisited[1] - to;
                    if (!visited[otherPoint.y][otherPoint.x]) {
                        continue;
                    }
                }
                previousPosition = pos;
                dfs(to, m, randomnessEngine);
            }
        }

    public:
        LongPathLabyrinthGenerator() : previousPosition(-1, -1) {
        }
};

class RandomGoalGenerator {

    public:
        Position getGoal(Map& m, mt19937& randomnessEngine) {
            uniform_int_distribution<int> yDistribution(1, m.getHeight()-2);
            uniform_int_distribution<int> xDistribution(1, m.getWidth()-2);
            Position pos(xDistribution(randomnessEngine), yDistribution(randomnessEngine));
            return pos;
        }
};

void writeOutput(Map& m, const Position& goal) {
    cout << m.getWidth() << " " << m.getHeight() << endl;
    for (size_t y = 0; y < m.getHeight(); y++) {
        for (size_t x = 0; x < m.getWidth(); x++) {
            Position pos(x, y);
            if (pos == goal)
                cout << "M";
            else {
                switch(m.at(pos)) {
                    case Square::Ice : {
                        cout << "_";
                        break;
                    }
                    case Square::Wall : {
                        cout << "#";
                        break;
                    }
                    case Square::Walkable : {
                        cout << ".";
                        break;
                    }
                    case Square::Grass : {
                        cout << ",";
                        break;
                    }
                }
            }
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]) {
    string allInput;
    for (int i = 1; i < argc; i++) {
        allInput += string(argv[i]) + " ";
    }
    seed_seq seed(allInput.begin(), allInput.end());
    mt19937 randomnessEngine(seed);
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    string type = argv[3];
    map<Square, double> probabilities;
    probabilities[Square::Ice] = atof(argv[4]);
    probabilities[Square::Wall] = atof(argv[5]);
    probabilities[Square::Walkable] = atof(argv[6]);
    string goalType = argv[7];
    Map m;
    if (type == "random") {
        RandomGenerator generator;
        m = generator.generate(width, height, probabilities, randomnessEngine);
    }
    else if (type == "labyrinth") {
        RandomLabyrinthGenerator generator;
        m = generator.generate(width, height, probabilities, randomnessEngine);
    }
    else if (type == "long_path") {
        LongPathLabyrinthGenerator generator;
        m = generator.generate(width, height, probabilities, randomnessEngine);
    }

    Position goal(-1, -1);
    if (goalType == "random_goal") {
        RandomGoalGenerator goalGenerator;
        goal = goalGenerator.getGoal(m, randomnessEngine);
    }
    else if (goalType == "fixed_goal") {
        int x = atoi(argv[8]);
        int y = atoi(argv[9]);
        goal = Position(x, y);
    }
    m.at(goal) = Square::Walkable;
    writeOutput(m, goal);
}
