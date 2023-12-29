#include <iostream>
#include <optional>
#include <string>

std::optional<std::string> getFullName(bool provide) {
    if (provide) {
        return "John Doe";  // Returns a valid string inside an optional.
    } else {
        return std::nullopt;  // Returns an empty optional object.
    }
}

int main() {
    std::optional<std::string> fullName = getFullName(true);

    // Check if there's a value
    if (fullName) {
        std::cout << "Full name is: " << *fullName << std::endl;
    } else {
        std::cout << "No name provided." << std::endl;
    }

    // Trying with no name
    fullName = getFullName(false);
    if (fullName) {
        std::cout << "Full name is: " << *fullName << std::endl;
    } else {
        std::cout << "No name provided." << std::endl;
    }

    return 0;
}
