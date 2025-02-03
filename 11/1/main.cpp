#include <iostream>
#include <string>
#include <vector>

void move_vectors(std::vector<std::string>& to_vec, std::vector<std::string>&& from_vector) {
    for (auto& str : from_vector) {
        to_vec.push_back(std::move(str));
    }
}

int main() {
    std::vector <std::string> one = { "test_string1", "test_string2" };
    std::vector <std::string> two;
    move_vectors(two, std::move(one));
    for (auto str : one) { std::cout << str << " "; }
    std::cout << std::endl << "size of one: " << one.size() <<  std::endl;
    for (auto str : two) { std::cout << str << " "; }
}
