// 

#include <iostream>
#include <vector>
#include <string_view>
#include <iterator>
#include <cstddef>
#include <cstdlib>

using std::vector;
using std::next;
using std::ptrdiff_t;
using std::string_view;

// Jason Turner better main
auto main( const int argc, const char * const * argv) -> int
{
  // argv are converted to string_views args
  vector<string_view> args(argv, next(argv, static_cast<ptrdiff_t>(argc)));

  // Do Work Here
  std::cout << "Hello,World!\n";
  
  return EXIT_SUCCESS;
}
