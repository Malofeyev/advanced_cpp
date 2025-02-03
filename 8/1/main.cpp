#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
    std::vector<int> res;
    int num;

    while (std::cin >> num) {
        res.push_back(num);
    }

    std::sort(res.begin(), res.end());

    auto last = std::unique(res.begin(), res.end());

    res.erase(last, res.end());

    for (int num : res) {
        std::cout << num << " ";
    }

    return 0;
}
