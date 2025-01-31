#include <iostream>
#include <algorithm>
#include <vector>

class Counter {
public:
    Counter() : sum(0), count(0) {}

    Counter(Counter&&) noexcept = default;

    void operator()(int num) {
        if (num % 3 == 0) {
            sum += num;
            count += 1;
        }
    }

    int get_sum() {
        return sum;
    }

    int get_count() {
        return count;
    }
private:
    int sum, count;
};

int main(int argc, char *argv[]) {
    std::vector<int> vals = { 4, 1, 3, 6, 25, 54 };
    auto counter = std::for_each(vals.begin(), vals.end(), Counter());
    std::cout << "get_sum()=" << counter.get_sum();
    std::cout << "\nget_count()=" << counter.get_count();

    return 0;
}
