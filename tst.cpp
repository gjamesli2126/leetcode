#include <iostream>

class PreMainSingleton {
private:
    // Private constructor prevents direct instantiation
    PreMainSingleton() {
        std::cout << "Private constructor executed before main." << std::endl;
    }

public:
    // Delete copy constructor and assignment operator
    PreMainSingleton(const PreMainSingleton&) = delete;
    PreMainSingleton& operator=(const PreMainSingleton&) = delete;

    // Static method to access the singleton instance
    static PreMainSingleton& getInstance() {
        static PreMainSingleton instance;
        return instance;
    }

    // A method that returns the current id and then increments it.
    int GetId() {
        return id++;
    }

private:
    int id = 0;
};

// Helper struct that forces the singleton to be instantiated before main()
struct PreMainCaller {
    PreMainCaller() {
        // This call ensures that the singleton instance is created before main()
        PreMainSingleton::getInstance();
    }
};

// Global instance triggers the helper's constructor
PreMainCaller preMainCaller;

int main() {
    // Using the singleton's GetId method
    int firstId = PreMainSingleton::getInstance().GetId();
    int secondId = PreMainSingleton::getInstance().GetId();

    std::cout << "First id: " << firstId << "\n";
    std::cout << "Second id: " << secondId << "\n";

    return 0;
}