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

// These functions are inefficient, they just
// exist to demonstrate the recursive implementation
// of the names_for function.

template <typename T> auto tail(const T &collection) -> T {
  return T(collection.cbegin() + 1, collection.cend());
}

template <typename T, typename C> auto prepend(T &&item, C collection) -> C {
  C result(collection.size() + 1);
  result[0] = std::forward<T>(item);
  std::copy(collection.cbegin(), collection.cend(), result.begin() + 1);
  return result;
}

// These can be used to activate different implementations:

// #define USE_LOOP_IMPLEMENTATION
// #define USE_RECURSIVE_IMPLEMENTATION
#define USE_TAIL_RECURSIVE_IMPLEMENTATION

#ifdef USE_LOOP_IMPLEMENTATION
template <typename FilterFunction>
auto names_for(const std::vector<person_t> &people, FilterFunction filter)
    -> std::vector<std::string> {
  std::vector<std::string> result;

  for (const person_t &person : people) {
    if (filter(person))
      result.push_back(name(person));
  }
  return result;
}
#endif

#ifdef USE_RECURSIVE_IMPLEMENTATION
template <typename FilterFunction>
auto names_for(const std::vector<person_t> &people, FilterFunction filter)
    -> std::vector<std::string> {
  if (people.empty()) {
    return {};
  } else {
    const auto head = people.front();
    const auto processed_tail = names_for(tail(people), filter);
    if (filter(head)) {
      return prepend(name(head), processed_tail);
    } else {
      return processed_tail;
    }
  }
}
#endif

#ifdef USE_TAIL_RECURSIVE_IMPLEMENTATION
template <typename FilterFunction, typename Iterator>
auto names_for_helper(Iterator people_begin, Iterator people_end,
                      FilterFunction filter,
                      std::vector<std::string> previously_collected)
    -> std::vector<std::string> {
  if (people_begin == people_end) {
    return previously_collected;
  } else {
    const auto head = *people_begin;
    if (filter(head)) {
      previously_collected.push_back(name(head));
      return names_for_helper(people_begin + 1, people_end, filter,
                              previously_collected);
    } else {
      return names_for_helper(people_begin + 1, people_end, filter,
                              previously_collected);
    }
  }
}

template <typename FilterFunction, typename Iterator>
auto names_for(Iterator people_begin, Iterator people_end,
               FilterFunction filter) -> std::vector<std::string> {
  return names_for_helper(people_begin, people_end, filter, {});
}
#endif

auto main(int argc, char *argv[]) -> int {
  std::vector<person_t> people{
      {"David", person_t::male},    {"Jane", person_t::female},
      {"Martha", person_t::female}, {"Peter", person_t::male},
      {"Rose", person_t::female},   {"Tom", person_t::male}};
#ifdef USE_TAIL_RECURSIVE_IMPLEMENTATION
  auto names = names_for(people.begin(), people.end(), is_female);
#else
  auto names = names_for(people, is_female);
#endif

  for (const auto &name : names)
    std::cout << name << '\n';
  return 0;
}
