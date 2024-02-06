/*
**Question: Implement a Car Rental Management System for an Agency in C++**

Design and implement a car rental management system for a rental agency in C++. The system should manage two types of vehicles: SUVs and Sedans. SUVs can seat up to 7 passengers, while Sedans are standard four-seaters. Your system should encapsulate the details of these vehicles and provide functionality to manage the car rental process effectively.

**Requirements:**

1. **Car Class:**
- Create a base class `Car` with attributes for the license plate, brand, status (available or rented out), and number of seats. Ensure attributes have appropriate access specifiers and provide member functions for setting and getting these attributes. Also, include a constructor for initializing these attributes.

2. **SUV and Sedan Classes:**
- Derive two classes from `Car`: `SUV` and `Sedan`.
- `SUV` should initialize with a seating capacity of 7 passengers.
- `Sedan` should be initialized with a seating capacity of 4 passengers.
- Both classes should allow for the inclusion of additional features specific to their type in the future, such as four-wheel drive for SUVs or a sport package for Sedans. Each class should have constructors, setters, and getters for its unique and inherited attributes.

3. **CarRental Management Class:**
- Implement a `CarRental` class to manage the inventory of cars available for rent. This class should maintain a collection of cars and support adding, removing, renting out, and returning cars based on their license plate.
- Implement methods to query available cars, with the capability to filter by type (SUV or Sedan) or by other criteria such as brand or seating capacity.

4. **Functionality and Operations:**
- The system should allow users to add cars of both types to the inventory, mark cars as rented out or available, and remove cars from the inventory as needed.
- Provide functionality to list all available cars and to filter these cars by their type (SUV or Sedan), making it easier for customers to find a car that meets their needs.

5. **Design Considerations:**
- Your design should use inheritance and polymorphism where appropriate, particularly for managing different types of cars.
- Use standard C++ libraries for data storage and retrieval, ensuring efficient operations for adding, removing, and querying cars.
- Implement error checking and ensure that your code is robust against invalid operations such as attempting to rent out an already rented car.

**Deliverables:**

Provide a comprehensive implementation of the system, including:
- Class definitions for `Car`, `SUV`, `Sedan`, and `CarRental`.
- A main function that demonstrates the functionality of your system,
 including adding cars, renting them out, returning them,
 and listing available cars
 with the ability to filter by type or other criteria.

Ensure your code is well-commented and uses C++ best practices. Your implementation should highlight your ability to design using object-oriented principles in C++.
*/
#include <bits/stdc++.h>

using namespace std;

// Include the classes Car, SUV, Sedan, and CarRental here
class Car {
protected:
    string licensePlate, brand;
    bool available = false;
    int seats_num = 0;
public:
    Car(string brand, string license, bool status = true) : licensePlate(std::move(license)), brand(std::move(brand)),
                                                            available(status) {}

//    Car(const Car& other)//copy constructor
//    :licensePlate(other.licensePlate),
//    brand(other.brand),
//    available(other.available){};
//    Car& operator=(const Car& other){
//        if(this!=&other){
//            licensePlate=other.licensePlate;
//            brand=other.brand;
//            available=other.available;
//        }
//        return *this;
//    }
    Car() = default;//default constructor
    string getlicensePlate() const { return licensePlate; }

    void setlicensePlate(string licensePlate) { this->licensePlate = std::move(licensePlate); }

    string getBrand() const { return brand; }

    void setBrand(string brand) { this->brand = std::move(brand); }

    void setStatus(bool status) { this->available = status; }

    bool getStatus() const { return available; }

    int getCapaciy() const { return seats_num; }
};

class SUV : public Car {
private:
    bool thirdRowOption;
public:
    SUV(string brand, string licensePlate, bool thirdRowOption = false)
            : Car(std::move(brand), std::move(licensePlate)),
              thirdRowOption(thirdRowOption) {
        seats_num = !thirdRowOption ? 4 : 7;
    }

    void setThirdRowOption(bool option) { thirdRowOption = option; }

    bool getThirdRowOption() const { return thirdRowOption; }
};

class Sedan : public Car {
private:
    bool sportPackageOption;
public:
    Sedan(string brand, string licensePlate, bool sportPackageOption = false)
            : Car(std::move(brand), std::move(licensePlate)), sportPackageOption(sportPackageOption) {
        seats_num = 4;
    }

    void setSportPackageOption(bool option) { sportPackageOption = option; }

    bool getSportPackageOption() const { return sportPackageOption; }
};

class CarRental {
private:
    unordered_map<string, Car> plateCarMap;
    unordered_map<string, unordered_set<string>> brandPlateListMap;
public:
    void addCar(const Car &car) {
        string plate = car.getlicensePlate();
        string brand = car.getBrand();
        plateCarMap[plate] = car;
        brandPlateListMap[brand].insert(plate);
    }

    vector<Car> getAvailableCars() {
        vector<Car> availCars;
        for (const auto &[_, car]: plateCarMap) {
            if (!car.getStatus()) continue;
            availCars.emplace_back(car);
        }
        return availCars;
    }

    bool rentCar(const string &licensePlate) {
        auto it = plateCarMap.find(licensePlate);
        if (it == plateCarMap.end()) return false;
        Car &car = it->second;
        if (!car.getStatus()) return false;
        car.setStatus(false);
        return true;
    }

    vector<Car> getAvailableCarsByBrand(const string &brand) {
        if (!brandPlateListMap.contains(brand)) {
            cout << "Brand not found" << endl;
            return {};
        };
        vector<Car> availCar;
        for (const auto &plate: brandPlateListMap[brand]) {
            const Car &car = plateCarMap[plate];//allocate ptr no need to use unique_ptr
            if (!car.getStatus()) continue;
            availCar.emplace_back(plateCarMap[plate]);
        }
        return availCar;
    }

    bool returnCar(const string &licensePlate) {
        auto it = plateCarMap.find(licensePlate);
        if (it == plateCarMap.end()) return false; // Car not in database
        Car &car = it->second;
        if (car.getStatus()) return false; // Cannot return a car that is already in the parking lot
        car.setStatus(true); // Mark the car as available
        return true;
    }

    vector<Car> getAvailableCarsBySeats(int seat_num) {
        if (seat_num != 4 && seat_num != 7) return {};
        vector<Car> availCar;
        for (const auto &[_, car]: plateCarMap) {
            if (car.getCapaciy() == seat_num) availCar.emplace_back(car);
        }
        return availCar;
    }

    bool removeCar(const string &licensePlate) {
        // First, find the car to get its brand for updating brandPlateListMap
        auto it = plateCarMap.find(licensePlate);
        if (it == plateCarMap.end()) return false; // Car not in database, so nothing to remove

        string brand = it->second.getBrand();
        plateCarMap.erase(it);
        // Now, remove the license plate from the corresponding brand in brandPalteListMap
        auto &plates = brandPlateListMap[brand];
        auto plateIt = plates.find(licensePlate);
        if (plateIt != plates.end()) {
            plates.erase(plateIt); // Remove the stale license plate
        }
        // If there are no more cars under this brand, remove the brand entry as well
        if (plates.empty()) {
            brandPlateListMap.erase(brand);
        }

        return true;
    }

    int getCarNumber() {
        return static_cast<int>(plateCarMap.size());
    }
};


// ANSI color codes
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string RESET = "\033[0m";

void printStatus(bool success, const string &message) {
    if (success) {
        cout << message << GREEN << " - Pass" << RESET << endl;
    } else {
        cout << message << RED << " - Fail" << RESET << endl;
    }
}

int main() {
    CarRental rentalSystem;

    // Test adding cars
    rentalSystem.addCar(SUV("Toyota", "123ABC"));
    rentalSystem.addCar(Sedan("Honda", "456DEF", true));

    // Test getting available cars
    vector<Car> availableCars = rentalSystem.getAvailableCars();
    cout << "Expected: 2, Actual: " << availableCars.size() << "\t";
    printStatus(availableCars.size() == 2, "Available cars count");

    // Test renting a car
    bool rentSuccess = rentalSystem.rentCar("123ABC");
    cout << "Expected: Yes, Actual: " << (rentSuccess ? "Yes" : "No") << "\t";
    printStatus(rentSuccess, "Renting 123ABC successful");

    // Test getting available cars by brand
    vector<Car> availableToyotas = rentalSystem.getAvailableCarsByBrand("Toyota");
    cout << "Expected: 0, Actual: " << availableToyotas.size() << "\t";
    printStatus(availableToyotas.empty(), "Available Toyota's count");

    // Test returning a car
    bool returnSuccess = rentalSystem.returnCar("123ABC");
    cout << "Expected: Yes, Actual: " << (returnSuccess ? "Yes" : "No") << "\t";
    printStatus(returnSuccess, "Returning 123ABC successful");

    // Test getting available cars by seats
    vector<Car> carsWithAtLeast4Seats = rentalSystem.getAvailableCarsBySeats(4);
    cout << "Expected: 2, Actual: " << carsWithAtLeast4Seats.size() << "\t";
    printStatus(carsWithAtLeast4Seats.size() == 2, "Cars with at least 4 seats count");

    // Test car removal
    bool removeSuccess = rentalSystem.removeCar("456DEF");
    cout << "Expected: Yes, Actual: " << (removeSuccess ? "Yes" : "No") << "\t";
    printStatus(removeSuccess, "Removing 456DEF successful");

    // Final count of cars
    int finalCarCount = rentalSystem.getCarNumber();
    cout << "Expected: 1, Actual: " << finalCarCount << "\t";
    printStatus(finalCarCount == 1, "Final cars count");

    // Try to rent a car that is already rented
    rentSuccess = rentalSystem.rentCar("123ABC");//Rent his car first.
    printStatus(rentSuccess, "First rent of 123ABC successful");
    rentSuccess = rentalSystem.rentCar("123ABC"); // This car is already rented from previous test
    cout << "Expected: No, Actual: " << (rentSuccess ? "Yes" : "No") << "\t";
    printStatus(!rentSuccess, "Renting an already rented car 123ABC should fail");

    // Try to return a car that was not rented
    returnSuccess = rentalSystem.returnCar("456DEF"); // Assuming this car was not rented
    cout << "Expected: No, Actual: " << (returnSuccess ? "Yes" : "No") << "\t";
    printStatus(!returnSuccess, "Returning a car that was not rented 456DEF should fail");

    // Try to rent a car that does not exist
    rentSuccess = rentalSystem.rentCar("000XYZ");
    cout << "Expected: No, Actual: " << (rentSuccess ? "Yes" : "No") << "\t";
    printStatus(!rentSuccess, "Renting a non-existent car 000XYZ should fail");

    // Try to return a car that does not exist
    returnSuccess = rentalSystem.returnCar("000XYZ");
    cout << "Expected: No, Actual: " << (returnSuccess ? "Yes" : "No") << "\t";
    printStatus(!returnSuccess, "Returning a non-existent car 000XYZ should fail");

    // Try to remove a car that does not exist
    removeSuccess = rentalSystem.removeCar("000XYZ");
    cout << "Expected: No, Actual: " << (removeSuccess ? "Yes" : "No") << "\t";
    printStatus(!removeSuccess, "Removing a non-existent car 000XYZ should fail");

    // Try to get available cars by a brand that does not exist

    availableCars = rentalSystem.getAvailableCarsByBrand("NonExistentBrand");
    cout << "Expected: Exception, Actual: " << availableCars.size() << " cars found\t";
    if (availableCars.empty())
        printStatus(true, "Querying cars by a non-existent brand threw an exception as expected");
    else printStatus(false, "Querying cars by a non-existent brand should throw an exception");



    // Try to add a car with a license plate that already exists
    rentalSystem.addCar(SUV("Toyota", "123ABC")); // Duplicate plate
    finalCarCount = rentalSystem.getCarNumber();
    cout << "Expected: No change, Actual: " << finalCarCount << "\t";
    printStatus(finalCarCount == 1, "Adding a car with a duplicate license plate should not change the car count");

    // Check the number of available cars after a failed rent operation
    availableCars = rentalSystem.getAvailableCars();
    cout << "Expected: Unchanged, Actual: " << availableCars.size() << "\t";
    printStatus(availableCars.size() == 1, "Available cars count should be unchanged after failed rent operation");

    SUV toyotaSUV("Toyota", "789GHI", true);
    rentalSystem.addCar(toyotaSUV);

    // Test getting third-row option for SUV
    bool thirdRowOption = toyotaSUV.getThirdRowOption();
    cout << "Expected: Yes, Actual: " << (thirdRowOption ? "Yes" : "No") << "\t";
    printStatus(thirdRowOption, "Toyota SUV should have third-row seating");

    // Test setting third-row option for SUV
    toyotaSUV.setThirdRowOption(false); // Update the third-row option
    thirdRowOption = toyotaSUV.getThirdRowOption();
    cout << "Expected: No, Actual: " << (thirdRowOption ? "Yes" : "No") << "\t";
    printStatus(!thirdRowOption, "Toyota SUV third-row seating should be updated to No");

    // Create a Sedan with a sports package
    Sedan hondaSedan("Honda", "321JKL", true);
    rentalSystem.addCar(hondaSedan);

    // Test getting sports package option for Sedan
    bool sportPackageOption = hondaSedan.getSportPackageOption();
    cout << "Expected: Yes, Actual: " << (sportPackageOption ? "Yes" : "No") << "\t";
    printStatus(sportPackageOption, "Honda Sedan should have a sports package");

    // Test setting sports package option for Sedan
    hondaSedan.setSportPackageOption(false); // Update the sports package option
    sportPackageOption = hondaSedan.getSportPackageOption();
    cout << "Expected: No, Actual: " << (sportPackageOption ? "Yes" : "No") << "\t";
    printStatus(!sportPackageOption, "Honda Sedan sports package should be updated to No");

    // Add cars to the system for initial setup
    rentalSystem.addCar(SUV("Toyota", "123ABC"));
    rentalSystem.addCar(Sedan("Honda", "456DEF", true));

    // Remove a car from the system
    removeSuccess = rentalSystem.removeCar("123ABC");
    cout << "Removing 123ABC: " << (removeSuccess ? "Success" : "Fail") << endl;
    // Ensure the car is removed
    printStatus(removeSuccess, "123ABC removed from the system");

    // Attempt to rent a removed car
    rentSuccess = rentalSystem.rentCar("123ABC");
    cout << "Expected: No, Actual: " << (rentSuccess ? "Yes" : "No") << "\t";
    printStatus(!rentSuccess, "Attempting to rent a removed car 123ABC should fail");

    // Attempt to return a removed car
    returnSuccess = rentalSystem.returnCar("123ABC");
    cout << "Expected: No, Actual: " << (returnSuccess ? "Yes" : "No") << "\t";
    printStatus(!returnSuccess, "Attempting to return a removed car 123ABC should fail");

    return 0;
}
