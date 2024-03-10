#pragma once

#include <map>
#include <iostream>

namespace dexter
{
  namespace sparse
  {
    template<class VALUE> class vector;
    template<class VALUE> class vector_entry;

    template<class VALUE>
    std::ostream &operator<<(std::ostream &os, const vector<VALUE> &vec);
  } // namespace sparse
} // namespace dexter



template<class VALUE>
class dexter::sparse::vector
{
private:
  VALUE m_default_value;
  unsigned short m_size;
  std::map<unsigned short, VALUE> m_map;

public:
  vector(VALUE default_value = 0, unsigned short size = 0);
  unsigned short size() const;
  vector_entry<VALUE> operator[](int index);
  const VALUE operator[](int index) const;

  friend class vector_entry<VALUE>;
  friend std::ostream &operator<<<>(std::ostream &os, const vector<VALUE> &vec);
};

template<class VALUE>
class dexter::sparse::vector_entry
{
private:
  unsigned short m_index;
  vector<VALUE> &m_vec;

public:
  vector_entry(
      vector<VALUE> &vec,
      unsigned short index);

public:
  operator VALUE();
  vector_entry<VALUE> &operator=(const VALUE &value);
};

#include "dexter_sparse_vector.txx"