#ifdef VECTOR_NO_HEADER_TEMPLATES
  #include "vector.hxx"
  #include "vector.dxx"

  #include "vector.txx"
  #include <cstdint>

  using namespace std;
  using namespace dexter;

  LINK_VECTOR_DEF_BASIC_TYPES(std::map);

  #include "vector.uxx"
#endif

