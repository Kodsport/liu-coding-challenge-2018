#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

template <class T>
class ExtendedEuclidean {
    private:
        T a[2];
        T x[2];

        void computeSolution() {
            if(x[1] == 0) {
                a[0] = 1;
                a[1] = 0;
            }
            else {
                ExtendedEuclidean reduced(x[1], x[0] % x[1]);
                a[0] = reduced.a2();
                a[1] = reduced.a1() - reduced.a2() * (x[0] / x[1]);
                if (a[0] < 0) {
                    T addMultiple = (-a[0] + x[1] - 1) / x[1];
                    a[0] += addMultiple * x[1];
                    a[1] -= addMultiple * x[0];
                }
                if (a[0] >= x[1]) {
                    T addMultiple = a[0] / x[1];
                    a[0] -= addMultiple * x[1];
                    a[1] += addMultiple * x[0];
                }
            }
        }

    public:
        ExtendedEuclidean(T x1, T x2) {
            x[0] = x1;
            x[1] = x2;
            computeSolution();
        }

        T a1() const {
            return a[0];
        }

        T a2() const {
            return a[1];
        }
};

template <class T>
T gcd(T a, T b) {
    return b ? gcd(b, a % b) : a;
}

template <class T>
T gcd(vector<T> v) {
    T g = 0;
    for (const T& x : v) {
        g = gcd(g, x);
    }
    return g;
}

template <class T>
void minimizeSolution(vector<T>& solution, const vector<T>& bottleSize) {
    for (size_t i = 1; i < solution.size(); i++) {
        if (solution[i] <= -bottleSize[0]) {
            T multiple = (-solution[i]) / bottleSize[0];
            solution[0] -= multiple * bottleSize[i];
            solution[i] += multiple * bottleSize[0];
        }
        if (solution[i] > 0) {
            T multiple = (solution[i] + bottleSize[0] - 1) / bottleSize[0];
            solution[0] += multiple * bottleSize[i];
            solution[i] -= multiple * bottleSize[0];
        }
    }
}

template <class T>
vector<T> produceGcd(const vector<T>& bottleSize) {
    if (bottleSize.empty())
        return {};

    T lastElement = bottleSize.back();
    auto newBottleSize = bottleSize;
    newBottleSize.pop_back();

    auto solution = produceGcd(newBottleSize);
    ExtendedEuclidean<T> euclidean(gcd(newBottleSize), lastElement);
    for (T& x : solution) {
        x *= euclidean.a1();
    }
    solution.push_back(euclidean.a2());
    minimizeSolution(solution, bottleSize);
    return solution;
}

class State {
    public:
        vector<int> bottleSize;
        vector<int> amount;

        State(const vector<int>& _bottleSize) : bottleSize(_bottleSize) {
            amount = vector<int>(bottleSize.size());
        }

        void fill(int i) {
            cout << "fill " << i+1 << endl;
            amount[i] = bottleSize[i];
        }

        void discard(int i) {
            cout << "discard " << i+1 << endl;
            amount[i] = 0;
        }

        void transfer(int i, int j) {
            cout << "transfer " << i+1 << " " << j+1 << endl;
            int transferredAmount = min(amount[i], bottleSize[j] - amount[j]);
            amount[i] -= transferredAmount;
            amount[j] += transferredAmount;
        }
};

int main() {
    size_t N;
    cin >> N;
    vector<int> bottleSize(N);
    for (size_t i = 0; i < N; i++) {
        cin >> bottleSize[i];
    }

    int T;
    cin >> T;
    
    if (T % gcd(bottleSize) != 0) {
        cout << "impossible" << endl;
        return 0;
    }
    
    auto solution = produceGcd(bottleSize);
    for (int& x : solution) {
        x *= T / gcd(bottleSize);
    }

    minimizeSolution(solution, bottleSize);

    State state(bottleSize);
    for (size_t i = 1; i < N; i++) {
        for (int j = 0; j < -solution[i]; j++) {
            while (state.amount[i] < bottleSize[i]) {
                if (state.amount[0] == 0) {
                    state.fill(0);
                }
                state.transfer(0, (int)i);
            }
            state.discard((int)i);
        }
    }
    T -= state.amount[0];
    cout << "transfer 1 0" << endl;
    while (T > 0) {
        cout << "fill 1" << endl;
        cout << "transfer 1 0" << endl;
        T -= bottleSize[0];
    }
    assert(T == 0);
}
