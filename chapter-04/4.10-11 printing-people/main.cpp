#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "person.h"

auto print_person(const person_t &person, std::ostream &out,
                  person_t::output_format_t format) -> void {
  if (format == person_t::name_only) {
    out << person.name() << '\n';
  } else if (format == person_t::full_name) {
    out << person.name() << ' ' << person.surname() << '\n';
  }
}

auto main() -> int {
  using namespace std::placeholders;

  std::vector<person_t> people{
      {"David", person_t::male},    {"Jane", person_t::female},
      {"Martha", person_t::female}, {"Peter", person_t::male},
      {"Rose", person_t::female},   {"Tom", person_t::male}};

  std::ofstream file("test");

  // Passing a non-member function as the function object to std::bind
  std::for_each(
      cbegin(people), cend(people),
      std::bind(print_person, _1, std::ref(std::cout), person_t::name_only));

  std::for_each(
      cbegin(people), cend(people),
      std::bind(print_person, _1, std::ref(file), person_t::full_name));

  // Passing a lambda function instead of using std::bind
  std::for_each(cbegin(people), cend(people), [](const person_t &person) {
    print_person(person, std::cout, person_t::name_only);
  });

  std::for_each(cbegin(people), cend(people), [&file](const person_t &person) {
    print_person(person, file, person_t::full_name);
  });

  return 0;
}
