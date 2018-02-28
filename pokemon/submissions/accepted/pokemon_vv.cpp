#include <array>
#include <complex>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

constexpr int INF = -1;
constexpr array<complex<int>, 4> directions{{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}};

// hack for set<pair<size_t, complex<int>>>
namespace std {
bool operator<(const complex<int>& lhs, const complex<int>& rhs) {
  return lhs.real() == rhs.real() ? lhs.imag() < rhs.imag()
                                  : lhs.real() < rhs.real();
}
}  // namespace std

int main() {
  // read
  size_t C, R;
  cin >> C >> R;
  vector<vector<char>> maze(R);
  vector<vector<int>> result(R, vector<int>(C, INF));

  for (auto& row : maze) {
    cin.ignore();
    row.resize(C, '#');
    cin.read(&row[0], C);
  }

  // find M
  set<pair<size_t, complex<int>>> Q;
  bool found_start = false;
  for (size_t row = 1; !found_start; ++row) {
    for (size_t col = 1; col + 1 < C; ++col)
      if (maze[row][col] == 'M') {
        found_start = true;
        result[row][col] = 0;
        maze[row][col] = '.';
        Q.emplace(0, complex<int>{(int)row, (int)col});
        break;
      }
  }

  // dijkstra
  while (!Q.empty()) {
    size_t dist = Q.begin()->first + 1;
    complex<int> cur = Q.begin()->second;
    Q.erase(Q.begin());

    // check for each direction
    for (size_t i = 0; i < directions.size(); ++i) {
      const complex<int>& dir = directions[i];
      // if ice then an obstacle must exist in the opposite direction
      if (maze[cur.real()][cur.imag()] == '_') {
        const complex<int>& opp = directions[(i + 2) % directions.size()] + cur;
        if (maze[opp.real()][opp.imag()] != '#') continue;
      }

      // attempt to move..
      auto next = cur + dir;
      bool keep_moving = true;
      while (keep_moving) {
        keep_moving = false;
        switch (maze[next.real()][next.imag()]) {
          case '_':
            keep_moving = true;
          case '.':
            auto& next_dist = result[next.real()][next.imag()];
            if (next_dist != INF && next_dist <= dist) break;
            // update queue
            if (next_dist != INF) Q.erase(Q.find({next_dist, next}));
            next_dist = dist;
            Q.emplace(next_dist, next);
        }
        if (keep_moving) next += dir;
      }
    }
  }

  // print
  for (size_t row = 0; row < R; ++row)
    for (size_t col = 0; col < C; ++col)
      printf("%d%c", result[row][col], col + 1 == C ? '\n' : ' ');

  return 0;
}
