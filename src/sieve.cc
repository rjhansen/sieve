/* Copyright 2023, Robert J. Hansen <rob@hansen.engineering>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   This implements the Sieve of Eratosthenes using modern C++ idioms.  It
   is not presented as an example of good style or something a sane
   programmer would want to maintain.  However, it's exceedingly useful at
   its purpose, which is showing people exactly just how scary modern
   compilers are at optimizing source code and how much trouble they can
   give reverse engineers.  For maximum scariness, turn your compiler's
   optimizations to maximum, disable all profiling and debugging support,
   and compile to Assembly instructions.  It'll make you believe in God, if
   only because you're looking at Assembly instructions crafted by the
   Devil.*/

#include <algorithm>
#include <charconv>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <exception>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

using std::bad_alloc;
using std::cerr;
using std::cout;
using std::decay;
using std::exception;
using std::from_chars;
using std::logic_error;
using std::ostream_iterator;
using std::remove_if;
using std::tuple;
using std::vector;
using std::errc::invalid_argument;
using std::errc::result_out_of_range;
using std::ranges::copy;

auto get_range(int argc, char *argv[]) {
  if (argc != 2)
    throw logic_error("insufficient args");

  int32_t parameter{0};
  auto [_, ec]{from_chars(argv[1], argv[1] + strlen(argv[1]), parameter)};

  switch (ec) {
  case invalid_argument:
    throw logic_error("not a number");
    break;
  case result_out_of_range:
    throw logic_error("number out of range");
    break;
  default:
    if (parameter < 2 || parameter > 1000000000)
      throw logic_error("number out of range");
    break;
  }

  return parameter;
}

int main(int argc, char *argv[]) {
  try {
    // Allocate and initialize our working data.
    auto up_to{get_range(argc, argv)};
    auto stop_at{static_cast<int32_t>(ceil(sqrt(static_cast<double>(up_to))))};
    vector<int32_t> candidates((up_to - 1) / 2 + 1, 0);
    candidates.at(0) = 2;

    // Structured binding declarations married to std::tuples let us declare
    // multiple types of data within a for loop.  Please note that if you do
    // this in production code I reserve the right to kill you.
    for (auto [iter, val] =
             tuple{candidates.begin() + 1,
                   decay<decltype(candidates.at(0))>::type{1}};
         iter != candidates.end(); *iter++ = (val += 2));

    // ... and the sieve is straightforward.
    for (auto iter = candidates.begin(); *iter <= stop_at; ++iter)
      candidates.erase(remove_if(iter + 1, candidates.end(),
                                 [&iter](const auto &value) {
                                   return 0 == (value % *iter);
                                 }),
                       candidates.end());

    // Render output.
    copy(candidates, ostream_iterator<decltype(candidates.at(0))>(cout, " "));
    cout << "\n";
  }
  catch (logic_error &) {
    cerr << "Usage: " << argv[0] << " [upto]\n\n"
         << "Upto must be between two and one billion.\n";
    return -1;
  } catch (bad_alloc &) {
    cerr << "Error allocating memory.  Aborting...\n";
    return -2;
  } catch (exception &e) {
    cerr << "Unknown exception: " << e.what() << ".  Aborting...\n";
    return -4;
  }
  return 0;
}
