/*
File: ml.cpp
Author: Amaan Zaidi
Date: 1/29/2025
Description:
    Takes First and Last names aswell as address, City, and State (From a .txt in CSV format). Prints a mailing Label.
*/

// Include Headers
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <map>


class Customer 
{
private:
    std::string firstName;
    std::string lastName;
    std::string Address;
    std::string City;
    std::string State;
    std::string Zipcode;
public:

    Customer()
    {
        firstName = "N/A";
        lastName = "N/A";
        Address = "N/A";
        City = "N/A";
        State = "N/A";
        Zipcode = "N/A";
    }
    // Overloaded Constructor to obtain important information.
    Customer(const std::string& fName, const std::string& lName, const std::string& addr, const std::string& cty, const std::string& st, const std::string& zip)
    {
        firstName = fName;
        lastName = lName;
        Address = addr;
        City = cty;
        State = st;
        Zipcode = zip;
        std::cout << "Customer object created: " << firstName << ", " << lastName << ", " << Address << ", " << City << ", " << State << ", " << Zipcode << std::endl;
    }
    // Getter and Setter for firstName
    std::string getFirstName() const { return firstName; }
    void setFirstName(const std::string& fName) { firstName = fName; }

    // Getter and Setter for lastName
    std::string getLastName() const { return lastName; }
    void setLastName(const std::string& lName) { lastName = lName; }

    // Getter and Setter for address
    std::string getAddress() const { return Address; }
    void setAddress(const std::string& addr) { Address = addr; }

    // Getter and Setter for city
    std::string getCity() const { return City; }
    void setCity(const std::string& cty) { City = cty; }

    // Getter and Setter for state
    std::string getState() const { return State; }
    void setState(const std::string& st) { State = st; }

    // Getter and Setter for zipcode
    std::string getZipcode() const { return Zipcode; }
    void setZipcode(const std::string& zip) { Zipcode = zip; }

    // Display the customer info
    void display() const {
        std::cout << "First Name: " << firstName << "\n"
                  << "Last Name: " << lastName << "\n"
                  << "Address: " << Address << "\n"
                  << "City: " << City << "\n"
                  << "State: " << State << "\n"
                  << "Zipcode: " << Zipcode << std::endl;
    }

    // Create Mailing Label
    void Label() const {
        std::cout << getLastName() << ", " << getFirstName() << std::endl
                  << getAddress() << std::endl
                  << getCity() << ", " << getState() << " " << getZipcode() << std::endl << std::endl;
    }
};


std::vector<Customer> fetchCustomerData(const std::string& filename) {

    std::ifstream File(filename); // Open File "Customers.txt"
    std::string line; // store file line
    std::vector<Customer> Customers; // vector to store customers, returns to the counterpart in "int main()"

    
    if(!File.is_open()) { // check if open, if not throw error.
        throw std::runtime_error("Customers.txt file not found");
        return Customers; // returns empty vector, effectively null.
    }

    
    while (std::getline(File, line)) { // Read each line
        std::stringstream ss(line); // Convert line to stringstream
        std::string firstName, lastName, Address, City, State, Zipcode; // Individual information variables

        // Parse individual Information here.
        while (std::getline(ss, lastName, ',') && std::getline(ss, firstName, ',') && std::getline(ss, Address, ',') && std::getline(ss, City, ',') && std::getline(ss, State, ',') && std::getline(ss, Zipcode, ',')) { // Split information between commas
            Customers.emplace_back(firstName, lastName, Address, City, State, Zipcode); // push parsed data into vector, where each index is a Customer Object, and the parsed data is theirs.
        }

    }

    File.close(); // Close File
    return Customers; // return vector holding each "Customer" object

}

void orderAndSortLabels(std::vector<Customer>& C) {
    std::vector<Customer> Customers = C; // initializing vector to store customer objects.
    std::map<std::string, std::vector<Customer>> groupedByZipcode; // Map to group customers by zipcode

    // Group customers by zipcode
    for (const auto& Customer : Customers) { // Iterate through Each Customer in Customers
        groupedByZipcode[Customer.getZipcode()].push_back(Customer); // push back Customers zipcodes to map i.e. [key: zipcode of customer, value: list of customers with the key/zipcode]
    }

    // Iterate through each customer grouped by zipcode and sort them by lastName
    for (auto it = groupedByZipcode.begin(); it != groupedByZipcode.end(); ++it) {
        std::vector<Customer>& group = it->second; // Get the group of customers (value)

        // Sort customers in the current group by lastName
        std::sort(group.begin(), group.end(), [](const Customer& a, const Customer& b) {
            return a.getLastName() < b.getLastName(); // Compare last names
        });

        for (const auto& Customer : group) {
            Customer.Label();
        }
    }
}

int main() {

    std::string filename = "Customers.txt"; // Customers data file
    std::vector<Customer> Customers; // initializing vector to store customer objects.
    
    try {
        Customers = fetchCustomerData(filename); // call fetch function to fill Customers vector with information for each Customer object
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    try {
    orderAndSortLabels(Customers); // call function to print labels for all Customer objects in order of zipcode sorted by lastname.
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    // holds the program so it doesn't close when you run from the .executable (can still be closed by pressing enter, or simply exiting the program.)
    // has no other function, so can be deleted safely without nuking the program.
    //int hang;
    //std::cin >> hang;


    return 0;
}


// 1. Read all records from "Customers.txt" ----CHECK
    // 1.1. Validate the input file exists. ----check
    // 1.2. If valid, create a data structure of Customer objects ----check
// 2. Create class "Customer" ----CHECK
    // 2.1 Six (6) member Variables to account for each of the six (6) fields below: ----check
        // 2.1.1 string Last_Name
        // 2.1.2 string First_Name
        // 2.1.3 string Street_Address
        // 2.1.4 string City
        // 2.1.5 string State
        // 2.1.5 int Zip_Code // might use string instead.
    // 2.2 overloaded constructor that takes CSV record for each customer ----check
    // 2.3 Setter and getter methods to fill fields above (6 fields) ----check
    // 2.4 Method "Label" returns a single string that contains the record in mailing label format. ----check
        // 2.4.1 The "Last name, First name" on the first line
        // 2.4.2 The "Street address" on the second line
        // 2.4.3 The "City, State Zip" on the third line
// 3. Print all mailing labels in one column to the terminal ----CHECK
    // 3.1 Labels must be formatted like Figure 1 with two blank lines between each record. ----check
    // 3.2 Labels must be grouped by zip code and then sorted by last name. ----check
        // 3.2.1 i.e, all addresses with the zip code "12345" would appear together and before "23456".
        // 3.2.2 And within zip code "12345", "Jones" would appear before "Smith".
// 4. The Code must be commented, and the variables must have proper and consistent naming conventions. ----CHECK

// FIGURE 1:
/*
Johnson, Emily
123 Maple Street
Columbus OH 43201
*/