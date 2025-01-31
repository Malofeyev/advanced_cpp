#include <iostream>
#include <vector>

template <class T> T sqr(const T &arg);

template <> int sqr(const int &arg) { return arg * arg; }

template <> std::vector<int> sqr(const std::vector<int> &arg) {
  std::vector<int> res;
  for (int i : arg) {
    res.push_back(i * i);
  }
  return res;
}

int main() {
  char c;
  int val;
  std::vector<int> vals;
  std::cout << "[IN] ";
  std::cin >> val;
  if (std::cin >> c) {
    vals.push_back(val);
    while (std::cin >> val) {
      std::cin >> c;
      vals.push_back(val);
    }
    std::cout << "[OUT] ";
    auto res = sqr(vals);
    for (int i = 0; i + 1 < res.size(); ++i) {
      std::cout << res[i] << ", ";
    }
    std::cout << res.back() << std::endl;

  } else {
    std::cout << "[OUT] " << sqr(val) << std::endl;
  }
}

