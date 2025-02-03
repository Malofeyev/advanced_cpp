#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

int main(int argc, char *argv[]) {
    std::unordered_map<char, int> frequents;
    
    std::string input;
    std::getline(std::cin, input);
    for (char c : input) {
       frequents[c]++;
    }
    std::vector<std::pair<char, int>> res(frequents.begin(), frequents.end());
     
    std::sort(res.begin(), res.end(), [](auto a, auto b) { return a.second > b.second; });
    for (auto p : res) {
        std::cout << p.first << ": " << p.second << "\n";  
    } 
    return 0;
}
