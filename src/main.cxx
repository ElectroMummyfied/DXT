#include "vector.hxx"
#include <iostream>

using namespace dexter;

int main(int argc, char *argv[]) {

  vector<double> a , b;
  vector<bool> c;

  a = {1, 1, 3, 0, 5};
  b = {5, 4, 0, 2, 1};

  c = a > 1.0;

  std::cout << "a = " << a.m_data.size() << "\n";
  std::cout << "b = " << b.m_data.size() << "\n";
  std::cout << "c = " << c << "\n";

  std::cout << "\n\nEnd of program. (press any key to continue... )\n";
  std::cin.get();
  return 0;
}