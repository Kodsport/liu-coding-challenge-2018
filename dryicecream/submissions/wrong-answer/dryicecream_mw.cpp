#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

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
    
    State state(bottleSize);
    while (T > 0) {
        int i = rand() % N;
        int j = rand() % N;
        if (state.amount[i] <= T && state.amount[i] > 0) {
            cout << "transfer " << i+1 << " 0" << endl;
            T -= state.amount[i];
            state.amount[i] = 0;
        }
        if (state.amount[j] <= T && state.amount[j] > 0) {
            cout << "transfer " << j+1 << " 0" << endl;
            T -= state.amount[j];
            state.amount[j] = 0;
        }
        if (rand()%3 == 0) {
            if (state.amount[i] == 0) {
                state.fill(i);
            }
        }
        else if(rand()%2 == 0) {
            if (state.amount[i] != 0) {
                state.discard(i);
            }
        }
        else if (state.amount[i] > 0 && state.amount[j] < bottleSize[j]){
            state.transfer(i, j);
        }
    }
    assert(T == 0);
}
