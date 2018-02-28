#include <iostream>

using namespace std;

int main() {
  int total = 0, count = 0;
  string word;
  while (cin >> word) {
    ++total;
    if (word.find("ae") != string::npos) ++count;
  }
  cout << (5 * count >= 2 * total ? "dae ae ju traeligt va\n"
                                  : "haer talar vi rikssvenska\n");
  return 0;
}
