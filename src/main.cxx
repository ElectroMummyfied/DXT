
#include "tensor.hxx"

// #include "vector.hxx"
// #include "vector.dxx"

using namespace dexter;

int main(int argc, char *argv[]) {
  tensor a(
    {5}, 0,
    { {{0}, 1},
      {{1}, 2},
      {{2}, 4}  }
  );

  // double e = a[{1, 0}];
  std::cout << a << "\n";

  #pragma region vector testing... {
  // vector<double> a(0, 3) , b, c;

  // a = {1, 1, 3, 0, 5, 0};
  // b = {5, 4, 3, 2, 1, 1};

  // auto d = reduce(b, root);

  // std::cout << "a = " << a.m_data.size() << "\n";
  // std::cout << "b = " << b.m_data.size() << "\n";
  // std::cout << "c = " << c << "\n";
  // std::cout << "d = " << d << "\n";

  // std::cout << BOOST_PP_STRINGIZE(SEQ_PREFIX((a)(b), _)) << std::endl;
  // std::cout << BOOST_PP_STRINGIZE(SEQ_POSTFIX((a)(b), _)) << std::endl;
  // std::cout << BOOST_PP_STRINGIZE(VEC_OP_NAMES_SEQ) << std::endl;
  #pragma endregion } vector testing...

  std::cout << "\n\nEnd of program. (press any key to continue... )\n";
  std::cin.get();
  return 0;
}