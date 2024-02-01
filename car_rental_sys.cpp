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
class Car{
protected:
    string licensePlate, brand;
    string status;
    int seats_num=0;
public:
    Car(string brand,string license): licensePlate(std::move(license)), brand(std::move(brand)){}
    Car(string brand,string license,string status): licensePlate(std::move(license)), brand(std::move(brand)), status(std::move(status)){}
    string getlicensePlate(){return licensePlate;}
    void setlicensePlate(string licensePlate){ this->licensePlate=std::move(licensePlate);}
    string getBrand(){return brand;}
    void setBrand(string brand){this->brand=std::move(brand);}
    void setStatus(bool status){this->status=status;}
    string getStatus(){return status;}
    int getCapaciy(){return seats_num;}
};

class SUV:protected Car{
private:
    bool thirdRowOption;
public:
    SUV(string brand,string licensePlate,bool thirdRowOption=false)
    : Car(std::move(brand),std::move(licensePlate)),
    thirdRowOption(thirdRowOption){
        seats_num = !thirdRowOption ? 4 : 7;
    }
    void setThirdRowOption(bool option){thirdRowOption=option;}
    bool getThirdRowOption(){return thirdRowOption;}
};
class Sedan:protected Car{
private:
    bool sportPackageOption;
public:
    Sedan(string brand,string licensePlate,bool sportPackageOption=false)
    :Car(std::move(brand),std::move(licensePlate)),sportPackageOption(sportPackageOption){
        seats_num=4;
    }
    void setSportPackageOption(bool option){sportPackageOption=option;}
    bool getSportPackageOption(){return sportPackageOption;}
};
class CarRental{
public:
    void addCar(const SUV& suv){

    }
    void addCar(const Sedan& sedan){

    }

    vector<Car> getAvailableCars(){

    }
    bool rentCar(const string_view& licensePlate){

    }
    vector<Car> getAvailableCarsByBrand(const string_view& brand){

    }
    bool returnCar(const string_view& licensePlate){

    }
    vector<Car> getAvailableCarsBySeats(int seat_num){

    }
    bool removeCar(const string_view& licensePlate){

    }
    int getCarNumber(){

    }

};
int main() {
    CarRental rentalSystem;

    // Test adding cars
    rentalSystem.addCar(SUV("Toyota", "123ABC"));
    rentalSystem.addCar(Sedan("Honda", "456DEF", true));

    // Test getting available cars
    vector<Car> availableCars = rentalSystem.getAvailableCars();
    cout << "Available cars count: " << availableCars.size() << endl; // Expect 2

    // Test renting a car
    bool rentSuccess = rentalSystem.rentCar("123ABC");
    cout << "Renting 123ABC successful: " << (rentSuccess ? "Yes" : "No") << endl; // Expect Yes

    // Test getting available cars by brand
    vector<Car> availableToyotas = rentalSystem.getAvailableCarsByBrand("Toyota");
    cout << "Available Toyotas count: " << availableToyotas.size() << endl; // Expect 0 after renting

    // Test returning a car
    bool returnSuccess = rentalSystem.returnCar("123ABC");
    cout << "Returning 123ABC successful: " << (returnSuccess ? "Yes" : "No") << endl; // Expect Yes

    // Test getting available cars by seats
    vector<Car> carsWithAtLeast4Seats = rentalSystem.getAvailableCarsBySeats(4);
    cout << "Cars with at least 4 seats count: " << carsWithAtLeast4Seats.size() << endl; // Expect 2

    // Test car removal
    bool removeSuccess = rentalSystem.removeCar("456DEF");
    cout << "Removing 456DEF successful: " << (removeSuccess ? "Yes" : "No") << endl; // Expect Yes

    // Final count of cars
    cout << "Final cars count: " << rentalSystem.getCarNumber() << endl; // Expect 1

    return 0;
}
