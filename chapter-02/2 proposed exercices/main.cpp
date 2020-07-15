#include <array>
#include <functional>
#include <iostream>
#include <numeric>

/**
 * Implementation of std::any_of, std::all_of, std::find_if algorithms
 * using std::accumulate (left fold algorithm).
 */

// Check if a predicate is true for any of the elements in a collection.
// Return true if a least one element in the collection yields true, false
// otherwise. If the collection is empty returns false.
// O(n)
template <typename C, typename P>
constexpr auto any_of(C collection, P predicate) -> bool {
  return std::accumulate(begin(collection), end(collection), false,
                         [&predicate](const auto &lhs, const auto &rhs) {
                           return lhs || predicate(rhs);
                         });
}

// Check if a predicate is true for all of the elements in a collection.
// Return true if all elements in the collection yield true, false
// otherwise. If the collection is empty returns true.
// O(n)
template <typename C, typename P>
constexpr auto all_of(C collection, P predicate) -> bool {
  return std::accumulate(begin(collection), end(collection), true,
                         [&predicate](const auto &lhs, const auto &rhs) {
                           return lhs && predicate(rhs);
                         });
}

// Searches for the first element which predicate is true.
// Return an iterator to the first element that satisfies the condition or
// last if it's not found.
// Right Fold, using reverse iterators. O(n)
template <typename C, typename P>
constexpr auto find_if(C &&collection, P predicate) {
  return std::accumulate(rbegin(collection), rend(collection), end(collection),
                         [&predicate](const auto iter, const auto &elem) {
                           return predicate(elem) ? &elem : iter;
                         });
}

// Insertion sort
// A simple, stable sorting algorithm.
// It builds the final sorted array introducing one item at a time
// in the right place.
// O(n^2)
template <typename C> constexpr auto insertion_sort(C container) {
  return std::accumulate(
      cbegin(container), cend(container), C(),
      [](auto partial_sorted, const auto &item) {
        auto pos = std::lower_bound(cbegin(partial_sorted),
                                    cend(partial_sorted), item);
        C sorted(cbegin(partial_sorted), pos);
        sorted.emplace_back(item);
        sorted.insert(end(sorted), pos, cend(partial_sorted));
        return sorted;
      });
}

auto main() -> int {

  // Some tests

  auto is_odd = [](const auto &item) { return item % 2 != 0; };

  constexpr std::array<int, 0> items_0;
  constexpr std::array<int, 1> items_1{2};
  constexpr std::array<int, 3> items_2{0, 3, 2};
  constexpr std::array<int, 1000> items_3 = [] {
    std::array<int, 1000> items;
    std::iota(begin(items), end(items), 0);
    return items;
  }();
  constexpr std::array<int, 3> items_4 = [] {
    std::array<int, 3> items;
    std::fill(begin(items), end(items), 1);
    return items;
  }();

  // any_of

  // O(n)
  static_assert(any_of(items_0, is_odd) == false);
  static_assert(any_of(items_1, is_odd) == false);
  static_assert(any_of(items_2, is_odd) == true);
  static_assert(any_of(items_3, is_odd) == true);

  // O(n) with break.
  static_assert(std::any_of(begin(items_0), end(items_0), is_odd) == false);
  static_assert(std::any_of(begin(items_1), end(items_1), is_odd) == false);
  static_assert(std::any_of(begin(items_2), end(items_2), is_odd) == true);
  static_assert(std::any_of(begin(items_3), end(items_3), is_odd) == true);

  // all_of

  // O(n)
  static_assert(all_of(items_0, is_odd) == true);
  static_assert(all_of(items_1, is_odd) == false);
  static_assert(all_of(items_2, is_odd) == false);
  static_assert(all_of(items_4, is_odd) == true);

  // O(n) with break.
  static_assert(std::all_of(begin(items_0), end(items_0), is_odd) == true);
  static_assert(std::all_of(begin(items_1), end(items_1), is_odd) == false);
  static_assert(std::all_of(begin(items_2), end(items_2), is_odd) == false);
  static_assert(std::all_of(begin(items_4), end(items_4), is_odd) == true);

  // find_if

  // Right Fold
  // O(n)
  static_assert(find_if(items_0, is_odd) == end(items_0));
  static_assert(find_if(items_1, is_odd) == end(items_1));
  static_assert(*find_if(items_2, is_odd) == 3);
  static_assert(*find_if(items_3, is_odd) == 1);
  static_assert(find_if(items_4, std::not_fn(is_odd)) == end(items_4));

  // O(n) with break
  static_assert(std::find_if(begin(items_0), end(items_0), is_odd) ==
                end(items_0));
  static_assert(std::find_if(begin(items_1), end(items_1), is_odd) ==
                end(items_1));
  static_assert(*std::find_if(begin(items_2), end(items_2), is_odd) == 3);
  static_assert(*std::find_if(begin(items_3), end(items_3), is_odd) == 1);
  static_assert(std::find_if(begin(items_4), end(items_4),
                             std::not_fn(is_odd)) == end(items_4));

  // insertion_sort
  // O(n^2)
  if (insertion_sort(std::vector<int>()) != std::vector<int>())
    throw;
  if (insertion_sort(std::vector{2}) != std::vector{2})
    throw;
  if (insertion_sort(std::vector{2, 0}) != std::vector{0, 2})
    throw;
  if (insertion_sort(std::vector{3, 2, 0}) != std::vector{0, 2, 3})
    throw;

  return 0;
}
