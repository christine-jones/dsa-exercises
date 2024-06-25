#include <iostream>

int main(int argc, char* argv[]) {

    if (argc != 3) {

        std::cout << "Usage: <program name> <name> <name>" << '\n';
        return 1;        
    }

    constexpr int first_name_index{1};
    constexpr int second_name_index{2};

    std::cout << "Hello "
              << argv[first_name_index] << " and "
              << argv[second_name_index] << ".\n";
    std::cout << "Goodbye "
              << argv[second_name_index] << " and "
              << argv[first_name_index] << ".\n";

    return 0;
}
