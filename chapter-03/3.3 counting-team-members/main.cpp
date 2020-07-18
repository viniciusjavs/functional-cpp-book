#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "person.h"

// See section 3.2.2
class company_t {
public:
  company_t(std::vector<person_t> employees) : m_employees(employees) {}
  std::string team_name_for(const person_t &) const;
  int count_team_members(const std::string &team_name) const;
  void create_team(std::string, std::vector<std::string>);

private:
  std::vector<person_t> m_employees;
  std::unordered_map<std::string, std::vector<std::string>> m_teams;
};

std::string company_t::team_name_for(const person_t &person) const {
  for (const auto &[key, value] : m_teams)
    if (std::find_if(cbegin(value), cend(value), [&person](const auto &name) {
          return name == person.name();
        }) != end(value))
      return key;
  return "";
}

int company_t::count_team_members(const std::string &team_name) const {
  // Counting the number of members in the specified team
  // using a lambda.
  //
  // The lambda needs to capture `this` because it needs to access
  // the `m_employees` member variable, and it captures the
  // `team_name` to check whether an employee belongs to that team
  return std::count_if(cbegin(m_employees), cend(m_employees),
                       [this, &team_name](const person_t &employee) {
                         return team_name_for(employee) == team_name;
                       });
}

void company_t::create_team(std::string team_name,
                            std::vector<std::string> members) {
  m_teams.insert({team_name, members});
}

int main(int argc, char *argv[]) {
  person_t p1{};
  person_t p2("Vick", person_t::gender_t::male);
  std::vector<person_t> employees{p1, p2};

  company_t company{employees};
  company.create_team("Blue", {"John"});
  company.create_team("Red", {"Vick"});
  company.create_team("Green", {});

  // some tests
  if (company.count_team_members("Blue") != 1)
    throw;
  if (company.count_team_members("Red") != 1)
    throw;
  if (company.count_team_members("Green") != 0)
    throw;
  if (company.count_team_members("Yellow") != 0)
    throw;
}
