#include <algorithm>
#include <iostream>
#include <list>
#include <set>
#include <vector>

template<class Container>
void print_container(const Container& container) {
    std::for_each(container.begin(), container.end(), [](auto val) { std::cout << val << " "; });
    std::cout << std::endl; 
}

int main(int argc, char *argv[]) {
    std::set<std::string> test_set = { "one", "two", "three", "four" };
    print_container(test_set); // four one three two. помните почему такой порядок? :)
    
    std::list<std::string> test_list = { "one", "two", "three", "four" };
    print_container(test_list); // one, two, three, four
    
    std::vector<std::string> test_vector = { "one", "two", "three", "four" };
    print_container(test_vector); // one, two, three, four    
}
