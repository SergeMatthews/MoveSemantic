#include <iostream>
#include <vector>

template<typename TYPE>
void move_vectors(std::vector<TYPE>& first, std::vector<TYPE>& second)
{
    second = std::move(first);
}

int main()
{
    std::vector<std::string> one{ "test_string1", "test_string2" };
    std::vector<std::string> two;

    std::cout << "one - " << one.size() << " - " << *(one.begin()) << std::endl;
    std::cout << "two - " << two.size() << std::endl;
    
    move_vectors(one, two);
    std::cout << "After moving: " << std::endl;

    std::cout << "one - " << one.size() << std::endl;
    std::cout << "two - " << two.size() << " - " << *(two.begin()) << std::endl;

    return EXIT_SUCCESS;
}