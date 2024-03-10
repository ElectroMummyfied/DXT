#include "tensor.hxx"
#include <array>

using namespace dexter;

int reduce(
  int* start,
  int* end,
  int (* hop_n)(int, int),
  int dlhs,
  int drhs,
  int (* hop_np1)(int, int),
  int id,
  int ann
) {
  int res = id;

  res = hop_np1(dlhs, drhs);

  for(int *it = start; (it != end) && (res != ann); it++) {
    res = hop_n(res, *it);
  }
  return res;
}

int main(int argc, char *argv[]) {

  std::array<int, 5> a = {1, 2, 3, 4, 5};


  std
  // tensor a (
  //   {5}, 0,
  //   { {{0}, 1},
  //     {{1}, 2},
  //     {{2}, 4}  }
  // );

  // // double e = a[{1, 0}];
  // std::cout << a << "\n";

  std::cout << "\n\nEnd of program. (press any key to continue... )\n";
  std::cin.get();
  return 0;
}

// #include "vector.hxx"
// #include "vector.dxx"

// using namespace dexter;

// int main(int argc, char *argv[]) {
//   vector<double> a(0, 3) , b, c;

//   a = {1, 1, 3, 0, 5, 0};
//   b = {5, 4, 3, 2, 1, 1};

//   auto d = reduce(b, root);

//   std::cout << "a = " << a.m_data.size() << "\n";
//   std::cout << "b = " << b.m_data.size() << "\n";
//   std::cout << "c = " << c << "\n";
//   std::cout << "d = " << d << "\n";

//   std::cout << BOOST_PP_STRINGIZE(SEQ_PREFIX((a)(b), _)) << std::endl;
//   std::cout << BOOST_PP_STRINGIZE(SEQ_POSTFIX((a)(b), _)) << std::endl;
//   std::cout << BOOST_PP_STRINGIZE(VEC_OP_NAMES_SEQ) << std::endl;

//   std::cout << "\n\nEnd of program. (press any key to continue... )\n";
//   std::cin.get();
//   return 0;
// }