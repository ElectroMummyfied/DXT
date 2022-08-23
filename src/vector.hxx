#pragma once

#include <map>
#include <cstdint>
#include <iostream>

#include "vector.dxx"
#include "vector.fxx"

namespace dexter {

  enum class VECTOR_ENTRY_PLACEHOLDER_NAME {i, j};

  STRUCT VECTOR_NAME {
    KEY_T m_size;
    VALUE_T m_val;

    CONTAINER_T<KEY_T, VALUE_T> m_data;

    VALUE_T (*m_operator_x)(const VALUE_T&, const VALUE_T&);
    VALUE_T (*m_operator_y)(const VALUE_T&, const VALUE_T&);

    VECTOR_NAME(KEY_T size = 0, VALUE_T val = 0);
    VECTOR_NAME(std::initializer_list<VALUE_T> l);

        // VALUE_T w(const VECTOR_NAME& rhs) const; //    nPr operator
    VECTOR_NAME x(const VECTOR_NAME& rhs) const; // e-wise operator
        VALUE_T y() const;                       // reduce operator

    // VECTOR_NAME operator+(const VECTOR_NAME& rhs);
    // val_t operator*(const VECTOR_NAME& rhs);

            VECTOR_ENTRY_TYPE operator[](const KEY_T &i);
      VECTOR_ENTRY_CONST_TYPE operator[](const KEY_T &i) const;

            VECTOR_ENTRY_TYPE operator[](const VECTOR_ENTRY_PLACEHOLDER_TYPE &h);
      VECTOR_ENTRY_CONST_TYPE operator[](const VECTOR_ENTRY_PLACEHOLDER_TYPE &h) const;

            // VECTOR_ENTRY_TYPE operator[]();

                     VECTOR_BOOL operator<(const VALUE_T val) const;
                     VECTOR_BOOL operator>(const VALUE_T val) const;

    VECTOR_NAME& operator=(std::initializer_list<VALUE_T> l);
    friend std::ostream& ::operator<< <>(std::ostream& os, const VECTOR_TYPE &v);
  };

  STRUCT VECTOR_ENTRY_NAME {
    const KEY_T m_k;
    VECTOR_NAME TYPE &m_vec;
    VALUE_T m_v;

    VECTOR_ENTRY_NAME(VECTOR_NAME TYPE &v, KEY_T k);
    operator VALUE_T() const;

    VALUE_T operator=(VALUE_T val);

    friend std::ostream& ::operator<< <>(std::ostream& os, const VECTOR_ENTRY_NAME TYPE &v);
  };

  STRUCT VECTOR_ENTRY_CONST_NAME {
    const KEY_T m_k;
    const VECTOR_NAME TYPE &m_vec;
    VALUE_T m_v;

    vector_entry_const(const VECTOR_NAME TYPE &v, KEY_T id);
    operator VALUE_T() const;

    friend std::ostream& ::operator<< <>(std::ostream &os, const VECTOR_ENTRY_CONST_NAME TYPE &e);
  };
};

#ifndef VECTOR_NO_HEADER_TEMPLATES
  #include "vector.txx"
#endif

#include "vector.uxx"