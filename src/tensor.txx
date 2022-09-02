
namespace TNN {
  #pragma region TN {
    TI() TN(const KEY_T &size, const VALUE_T &val, const DATA_T &data)
    : m_size(size),
      m_val(val),
      m_data(data)
    {}
    // TI() TN(
    //   std::initializer_list<INTEGRAL_T> s,
    //   std::initializer_list<std::pair<KEY_T, VALUE_T>> l
    // ) {
    //   m_size = s;
    //   operator=(l);
    // }

    TI(bool) is_valid(const KEY_T &k) {
      if(k.size() !=  m_size.size()) false;
      for(auto j = 0; j < k.size(); j++) if(k[j] >= m_size[j]) return false;

      return true;
    }

    TI(TET) operator[](const KEY_T &k) {
      if(!is_valid(k)) throw;

      TET e(*this, k);
      return e;
    }
    TI(TECT) operator[](const KEY_T &k) const {
      if(!is_valid(k)) throw;

      TECT e(*this, k);
      return e;
    }

    TI(const TTP&)
    operator=(
      std::initializer_list<std::pair<KEY_T, VALUE_T>> l
    ) {

      m_data.clear();
      for(auto it = l.begin(); it != l.end(); it++) {
        m_data.insert(*it);
        // VECTOR_ENTRY_TYPE e = operator[]( std::distance(l.begin(), it) );
        // e = *it;
      }

      return *this;
    }

  #pragma endregion } TN
  #pragma region TEBN {
    TEBI() TEBN(KEY_T k) : m_k(k) {}
  #pragma endregion } TEBN
  #pragma region TEN {
    TEI() TEN(TTP &t, KEY_T k) : TEBT(k), m_t(t) {}
    TEI() operator VALUE_T() const {
      auto it = m_t.m_data.find(this->m_k);
      return (it != m_t.m_data.end() ? it->second : m_t.m_val);
    };
    TEI(VALUE_T) operator=(VALUE_T val) {
      auto it = m_t.m_data.find(this->m_k);

      if(it != m_t.m_data.end())
        if(val != m_t.m_val) {
          it->second = val;
        } else {
          m_t.m_data.erase(this->m_k);
        }
      else {
        if(val != m_t.m_val) {
          m_t.m_data.insert(std::pair(this->m_k, val));
        }
      }

      return val;
    }
  #pragma endregion } TEN
  #pragma region TECN {
    TECI() TECN(const TTP &t, KEY_T k) : TEBT(k), m_t(t) {}
    TECI() operator VALUE_T() const {
      auto it = m_t.m_data.find(this->m_k);
      return (it != m_t.m_data.end() ? it->second : m_t.m_val);
    };
  #pragma endregion } TECN
} // namespace TENSOR_NAMESPACE_NAME
#pragma region ostream& operator<< {
  template<class T>
  std::ostream& operator<< (
    std::ostream& os,
    const std::vector<T> &v
  ) {

    os << "[";
    switch(v.size()) {
      case 0: break;
      case 1: os << v[0]; break;
      default:
        for(auto it = v.begin(); it != --v.end(); it++) {
          os << *it << ", ";
        }
        os << *v.rbegin();
    }
    os << "]";
    return os;
  }

  TTMP std::ostream&
  operator<<(
    std::ostream& os,
    const TNN::TEBT &e
  ) {
    os << static_cast<VALUE_T>(e);
    return os;
  }

  TTMP std::ostream&
  operator<< (
    std::ostream& os,
    const TNN::TTP &t
  ) {
    typename decltype(t.m_data)::const_iterator it;

    switch (t.m_size.size()) {
      case 0:
        os << t.m_val;
        break;
      // case 1:
      //   os << "[";

      //   for(INTEGRAL_T i = 0; i < (t.m_size[0] == 0 ? 0 : t.m_size[0] - 1); i++) {
      //     it = t.m_data.find({i});
      //     os << (it != t.m_data.end() ? it->second : t.m_val) << ", ";
      //   }
      //   it = t.m_data.find({t.m_size[0] - 1});

      //   if(t.m_size[0] != 0)
      //     os << (it != t.m_data.end() ? it->second : t.m_val);

      //   os << "]";

      //   break;
      // case 2:
        // os << "[\n";

        // typename decltype(t.m_data)::const_iterator it;
        // for(INTEGRAL_T i = 0; i < (t.m_size[0] == 0 ? 0 : t.m_size[0] - 1); i++) {
        //   os << "[";

        //   for(INTEGRAL_T j = 0; j < (t.m_size[1] == 0 ? 0 : t.m_size[1] - 1); j++) {
        //     it = t.m_data.find({i, j});
        //     os << (it != t.m_data.end() ? it->second : t.m_val) << ", ";
        //   }
        //   it = t.m_data.find({i, t.m_size[1] - 1});

        //   if(t.m_size[1] != 0)
        //     os << (it != t.m_data.end() ? it->second : t.m_val);

        //   os << "]\n";
        // }
        // it = t.m_data.find({t.m_size[0] - 1, t.m_size[1] - 1});

        // if(t.m_size[0] != 0) {
        //   os << "[";

        //   for(INTEGRAL_T j = 0; j < (t.m_size[1] == 0 ? 0 : t.m_size[1] - 1); j++) {
        //     it = t.m_data.find({t.m_size[0] - 1, j});
        //     os << (it != t.m_data.end() ? it->second : t.m_val) << ", ";
        //   }
        //   it = t.m_data.find({i, t.m_size[1] - 1});

        //   if(t.m_size[1] != 0)
        //     os << (it != t.m_data.end() ? it->second : t.m_val);

        //   os << "]";
        // }

        //   os << (it != t.m_data.end() ? it->second : t.m_val);

        // os << "]";
      default:
        for(auto dit = t.m_data.begin(); dit != t.m_data.end(); dit++) {
          os << dit->first << ": ";
          os << (dit != t.m_data.end() ? dit->second : t.m_val) << "\n";
        }

        break;
    }

    return os;
  }
#pragma endregion } ostream& operator<<