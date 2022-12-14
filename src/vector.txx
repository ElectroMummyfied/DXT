namespace dexter {

  BINARY_OPERATORS_DECL(1);

  #pragma region VECTOR_NAME_ {
    IMPL() VECTOR_NAME(KEY_T size, VALUE_T dval)
    : m_size(size),
      m_val(dval),
      m_operator_x(multiply),
      m_operator_y(add)
    {}

    IMPL()
    VECTOR_NAME(std::initializer_list<VALUE_T> l)
    : m_size(l.size()),
      m_val(0),
      m_operator_x(multiply),
      m_operator_y(add)
    {
      operator=(l);
    }

    IMPL(const VECTOR_TYPE&)
    operator=(std::initializer_list<VALUE_T> l) {
      m_size = l.size();
      m_data.clear();
      for(auto it = l.begin(); it != l.end(); it++) {
        VECTOR_ENTRY_TYPE e = operator[]( std::distance(l.begin(), it) );
        e = *it;
      }

      return *this;
    }

    IMPL(VECTOR_TYPE)
    x(const VECTOR_NAME &rhs) const {
      VECTOR_NAME vec(m_size);

      for(KEY_T i = 0; i < m_size; i++) {
        vec[i] = m_operator_x((*this)[i], rhs[i]);
      }

      return vec;
    }

    IMPL(VALUE_T)
    y() const {
      VALUE_T val;
      if(m_size == 0) goto eof;

      val = (*this)[0];
      for(KEY_T i = 1; i < m_size; i++) {
        val = m_operator_y(val, (*this)[i]);
      }

      eof:
        return val;
    }

    IMPL(VECTOR_ENTRY_TYPE)
    operator[](const KEY_T &id) {
      if(!(id < m_size)) throw;
      VECTOR_ENTRY_TYPE e(*this, id);
      return e;
    };

    IMPL(VECTOR_ENTRY_CONST_TYPE)
    operator[](const KEY_T &id) const {
      if(!(id < m_size)) throw;
      VECTOR_ENTRY_CONST_TYPE e(*this, id);
      return e;
    };

    IMPL(VALUE_T)
    operator+() const {
      VALUE_T res;

      res = 0;
      for(auto e: m_data) {
        res += e.second;
      }
      res += (m_data.size() - m_size) * m_val;

      return res;
    }

    IMPL(VALUE_T)
    operator*() const {
      VALUE_T res;

      res = 1;
      for(auto e: m_data) {
        res *= e.second;
      }
      res *= std::pow(m_val, m_data.size() - m_size);

      return res;
    }
    // IMPL(VECTOR_BOOL)
    // operator<(const VALUE_T val) const {
    //   VECTOR_BOOL vec(m_size);
    //   for(KEY_T it = 0; it < m_size; it++)
    //     vec[it] = operator[](it) < val;

    //   return vec;
    // }
    // IMPL(VECTOR_BOOL)
    // operator>(const VALUE_T val) const {
    //   VECTOR_BOOL vec(m_size);
    //   for(KEY_T it = 0; it < m_size; it++)
    //     vec[it] = operator[](it) > val;

    //   return vec;
    // }
  #pragma endregion } VECTOR_NAME_
  #pragma region VECTOR_ENTRY_NAME_ {
    eIMPL()
    VECTOR_ENTRY_NAME (VECTOR_TYPE &vec, KEY_T k)
    : m_vec(vec),
      m_k(k)
    {};
    // eIMPL()
    // VECTOR_ENTRY_NAME (const VECTOR_T TYPE &vec, KEY_T k)
    // : m_vec(vec),
    //   m_k(k)
    // {};

    eIMPL(VALUE_T)
    operator=(VALUE_T val) {
      auto it = m_vec.m_data.find(m_k);

      if(it != m_vec.m_data.end())
        if(val != m_vec.m_val) {
          it->second = val;
        } else {
          m_vec.m_data.erase(m_k);
        }
      else {
        if(val != m_vec.m_val) {
          m_vec.m_data.insert(std::pair(m_k, val));
        }
      }

      return val;
    }

    eIMPL()
    operator VALUE_T() const {
      auto it = m_vec.m_data.find(m_k);
      return (it != m_vec.m_data.end() ? it->second : m_vec.m_val);
    };
  #pragma endregion } VECTOR_ENTRY_NAME_
  #pragma region VECTOR_ENTRY_CONST_NAME_ {
    ecIMPL()
    VECTOR_ENTRY_CONST_NAME(const VECTOR_TYPE &vec, KEY_T k)
    : m_vec(vec),
      m_k(k)
    {};

    ecIMPL()
    operator VALUE_T() const {
      auto it = m_vec.m_data.find(m_k);
      return (it != m_vec.m_data.end() ? it->second : m_vec.m_val);
    };
  #pragma endregion } VECTOR_ENTRY_CONST_NAME_


  TMPLT__
  VALUE_T reduce (
    const VECTOR_TYPE &vec,
    VALUE_T (*const cb)(const VALUE_T &, const VALUE_T &)
  ) {
    if(vec.m_size == 0) throw;

    VALUE_T res;

    // upper echelon operator needs to be known for this to work
    // res = *vec.m_data.begin();
    // for(auto it = ++vec.m_data.begin(); it != vec.m_data.end(); it++) {
    //   res = cb(res, it->second);
    // }

    // operator inverses do not work properly
    res = vec[0];
    for(std::size_t i = 1; i < vec.m_size; i++) {
      res = cb(res, vec[i]);
    }

    return res;
  }

  TMPLT__
  VECTOR_TYPE entrywise (
    const VECTOR_TYPE &lhs,
    const VECTOR_TYPE &rhs,
    VALUE_T (*const cb)(const VALUE_T &, const VALUE_T &)
  ) {
    if(lhs.m_size == 0 || rhs.m_size == 0) throw;
    if(lhs.m_size != rhs.m_size) throw;

    VECTOR_TYPE res(lhs.m_size, cb(lhs.m_val, rhs.m_val));

    for(auto lhs_it = lhs.m_data.begin(); lhs_it != lhs.m_data.end(); lhs_it++) {
      auto rhs_it = rhs.m_data.find(lhs_it->first);
      res[lhs_it->first] =
        ((rhs_it != rhs.m_data.end()) ?
          cb(lhs_it->second, rhs_it->second) :
          cb(lhs_it->second, rhs.m_val)  );
    }

    for(auto rhs_it = rhs.m_data.begin(); rhs_it != rhs.m_data.end(); rhs_it++) {
      auto lhs_it = lhs.m_data.find(rhs_it->first);
      if(lhs_it != lhs.m_data.end()) continue;
      res[rhs_it->first] = cb(rhs_it->second, lhs.m_val);
    }

    return res;
  }

  TMPLT__
  VECTOR_TYPE cartesian (
    const VECTOR_TYPE &lhs,
    const VECTOR_TYPE &rhs,
    VALUE_T (*const cb)(const VALUE_T &, const VALUE_T &)
  ) {

  }

  // TMPLT_
  // VECTOR_TYPE entrywise_add(const VECTOR_TYPE &lhs, const VECTOR_TYPE &rhs) {
  //     if(lhs.m_size == 0 || rhs.m_size == 0) throw;
  //     if(lhs.m_size != rhs.m_size) throw;

  //     VECTOR_TYPE res(lhs.m_size, lhs.m_val + rhs.m_val);

  //     for(auto lhs_it = lhs.m_data.begin(); lhs_it != lhs.m_data.end(); lhs_it++) {
  //       auto rhs_it = rhs.m_data.find(lhs_it->first);
  //       res[lhs_it->first] =
  //         ((rhs_it != rhs.m_data.end()) ?
  //           lhs_it->second + rhs_it->second :
  //           lhs_it->second + rhs.m_val  );
  //     }

  //     for(auto rhs_it = rhs.m_data.begin(); rhs_it != rhs.m_data.end(); rhs_it++) {
  //       auto lhs_it = lhs.m_data.find(rhs_it->first);
  //       if(lhs_it != lhs.m_data.end()) continue;
  //       res[rhs_it->first] = rhs_it->second + lhs.m_val;
  //     }

  //     return res;
  // }
};


TMPLT_ std::ostream&
operator<<(std::ostream& os, const dexter::VECTOR_TYPE &vec) {
  os << "[";

  typename decltype(vec.m_data)::const_iterator it;
  for(KEY_T i = 0; i < (vec.m_size == 0 ? 0 : vec.m_size - 1); i++) {
    it = vec.m_data.find(i);
    os << (it != vec.m_data.end() ? it->second : vec.m_val) << ", ";
  }
  it = vec.m_data.find(vec.m_size - 1);

  if(vec.m_size != 0)
    os << (it != vec.m_data.end() ? it->second : vec.m_val);
    os << "]";

  return os;
}

TMPLT_ std::ostream&
operator<<(std::ostream& os, const dexter::VECTOR_ENTRY_CONST_TYPE &e) {
  os << static_cast<VALUE_T>(e);
  return os;
}

TMPLT_ std::ostream&
operator<<(std::ostream& os, const dexter::VECTOR_ENTRY_TYPE &e) {
  os << static_cast<VALUE_T>(e);
  return os;
}