#ifndef SOME_PATTERNS_PERSON_JOB_BUILDER_H
#define SOME_PATTERNS_PERSON_JOB_BUILDER_H

#include <string>
#include <utility>
#include "person_builder.h"

class PersonJobBuilder : public PersonBuilderBase {
public:
    explicit PersonJobBuilder(Person &person) : PersonBuilderBase{person} {}

    PersonJobBuilder &at(const std::string &company_name) {
        person.company_name = company_name;
        return *this;
    }

    PersonJobBuilder &as_a(const std::string &position) {
        person.position = position;
        return *this;
    }

    PersonJobBuilder &earning(int annual_income) {
        person.annual_income = annual_income;
        return *this;
    }
};


#endif //SOME_PATTERNS_PERSON_JOB_BUILDER_H
