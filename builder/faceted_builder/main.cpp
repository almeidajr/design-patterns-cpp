#include <vector>
#include <iostream>
#include "person.h"
#include "person_builder.h"
#include "person_address_builder.h"
#include "person_job_builder.h"


int main() {
    Person p = Person::create()
            .lives().at("123 London Road").with_postcode("SW1P 3QP").in("London")
            .works().at("Google").as_a("Software Engineer").earning(10e5);

    std::cout << p << std::endl;
    return 0;
}
