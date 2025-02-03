#include <iostream>
#include <set>

int main(int argc, char *argv[]) {
    int n, num;
    std::set<int, std::greater<int>> nums;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> num;
        nums.insert(num);
    }    

    for (int num : nums) {
        std::cout << num << std::endl;
    }

    return 0;
}
