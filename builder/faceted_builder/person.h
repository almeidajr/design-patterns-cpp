#ifndef SOME_PATTERNS_PERSON_H
#define SOME_PATTERNS_PERSON_H

#include <string>
#include <iostream>

class PersonBuilder;

class Person {
public:
    friend class PersonBuilder;

    friend class PersonAddressBuilder;

    friend class PersonJobBuilder;

    static PersonBuilder create();

    Person(Person &&other) noexcept: street_address{std::move(other.street_address)},
                                     city{std::move(other.city)},
                                     post_code{std::move(other.post_code)},
                                     company_name{std::move(other.company_name)},
                                     annual_income{other.annual_income} {}

    Person &operator=(Person &&other)  noexcept {
        if (this == &other) {
            return *this;
        }
        street_address = std::move(other.street_address);
        city = std::move(other.city);
        post_code = std::move(other.post_code);
        company_name = std::move(other.company_name);
        annual_income = other.annual_income;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Person &p) {
        os << "Street address: " << p.street_address << std::endl;
        os << "City: " << p.city << std::endl;
        os << "Post code: " << p.post_code << std::endl;
        os << "Company name: " << p.company_name << std::endl;
        os << "Annual income: " << p.annual_income << std::endl;
        return os;
    }

    ~Person() {
        std::cout << "Person destroyed" << std::endl;
    };

protected:
    std::string street_address;
    std::string city;
    std::string post_code;

    std::string company_name;
    std::string position;
    int annual_income{};

    Person() {
        std::cout << "Person created" << std::endl;
    }
};


#endif //SOME_PATTERNS_PERSON_H
