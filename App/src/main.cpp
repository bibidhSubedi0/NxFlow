#include <iostream>
#include "../include/MathFunctions.h" // Include CoreLibrary's header

int main() {
    int result = CoreLibrary::add(5, 3); // Use the add function from CoreLibrary
    std::cout << "Result of addition: " << result << std::endl;
    return 0;
}
