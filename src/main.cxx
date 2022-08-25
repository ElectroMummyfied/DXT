#include "vector.hxx"
#include <iostream>
#include <map>

using namespace dexter;

int main(int argc, char *argv[]) {
  vector<double> a , b, c;

  a = {1, 1, 3, 0, 5};
  b = {5, 4, 0, 2, 1};

  auto d = *a;

  std::cout << "a = " << a.m_data.size() << "\n";
  std::cout << "b = " << b.m_data.size() << "\n";
  std::cout << "c = " << c << "\n";
  std::cout << "d = " << d << "\n";

  std::cout << "\n\nEnd of program. (press any key to continue... )\n";
  std::cin.get();
  return 0;
}