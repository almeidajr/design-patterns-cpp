#ifndef SOME_PATTERNS_PERSON_BUILDER_H
#define SOME_PATTERNS_PERSON_BUILDER_H

#include "person.h"

class Person;
class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase {
public:
    operator Person() const {
        return std::move(person);
    }

    PersonAddressBuilder lives() const;

    PersonJobBuilder works() const;

protected:
    Person &person;

    explicit PersonBuilderBase(Person &person) : person{person} {}
};


class PersonBuilder : public PersonBuilderBase {
public:
    PersonBuilder() : PersonBuilderBase{p} {}

protected:
    Person p;
};


#endif //SOME_PATTERNS_PERSON_BUILDER_H
