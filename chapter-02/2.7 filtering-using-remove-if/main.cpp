#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "person.h"

auto name(const person_t &person) -> std::string { return person.name(); }

auto is_female(const person_t &person) -> bool {
  return person.gender() == person_t::female;
}

auto is_not_female(const person_t &person) -> bool {
  return !is_female(person);
}

auto main(int argc, char *argv[]) -> int {
  std::vector<person_t> people{
      {"David", person_t::male},   {"Jane", person_t::female},
      {"Marth", person_t::female}, {"Peter", person_t::male},
      {"Rose", person_t::female},  {"Tom", person_t::male}};

  // Filtering with the erase-remove idiom (section 2.2.5, page 35)
  people.erase(std::remove_if(people.begin(), people.end(), is_not_female),
               people.end());
  for (const person_t &person : people)
    std::cout << person.name() << '\n';
}
