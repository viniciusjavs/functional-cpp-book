#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

#define parallel

#if 0
// Imperative version
double average_score(const std::vector<int> &scores)
{
    int sum = 0;
    for (int score : scores){
	sum += score;
    }
    return sum / static_cast<double>(scores.size());
}
#endif // Imperative version

#ifndef parallel
// Calculating the average score with std::accumulate.
// By default, accumulate uses addition as the folding operation
// over a collection
// (see section 2.2.1)
double average_score(const std::vector<int> &scores) {
  return std::accumulate(scores.cbegin(), scores.cend(), 0) /
         static_cast<double>(scores.size());
}
#else
double average_score(const std::vector<int> &scores) {
  return std::reduce(std::execution::par, scores.cbegin(), scores.cend(), 0) /
         static_cast<double>(scores.size());
}
#endif // folding (sequential or parallelized) version

// We can provide a custom operation. In this case,
// we are multiplying all the scores
double scores_product(const std::vector<int> &scores) {
  return std::accumulate(scores.cbegin(), scores.cend(), 1,
                         std::multiplies<int>());
}

int main(int argc, char *argv[]) {
  std::cout << average_score({1, 2, 3, 4}) << '\n';
  std::cout << scores_product({1, 2, 3, 4}) << '\n';
}
