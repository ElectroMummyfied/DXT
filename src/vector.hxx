#pragma once

#include <map>
#include <cstdint>
#include <iostream>

#include "vector.dxx"
#include "vector.uxx"

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

          VECTOR_OPERATOR__TYPE operator[](const VECTOR_ENTRY_PLACEHOLDER_NAME &h);
    VECTOR_OPERATOR__CONST_TYPE operator[](const VECTOR_ENTRY_PLACEHOLDER_NAME &h) const;

    VALUE_T operator+() const;
    VALUE_T operator*() const;
    // VECTOR_TYPE operator>(const VALUE_T val) const;
            // VECTOR_ENTRY_TYPE operator[]();

                    //  VECTOR_BOOL operator<(const VALUE_T val) const;
                    //  VECTOR_BOOL operator>(const VALUE_T val) const;

    VECTOR_NAME& operator=(std::initializer_list<VALUE_T> l);
    friend std::ostream& ::operator<< <>(std::ostream& os, const VECTOR_TYPE &v);
  };
  
  STRUCT VECTOR_ENTRY_NAME {
    const KEY_T m_k;
    VECTOR_TYPE &m_vec;
    VALUE_T m_v;

    VECTOR_ENTRY_NAME(VECTOR_TYPE &v, KEY_T k);
    // VECTOR_ENTRY_NAME(const VECTOR_T TYPE &v, KEY_T id);

    operator VALUE_T() const;

    VALUE_T operator=(VALUE_T val);

    friend std::ostream& ::operator<< <>(std::ostream& os, const VECTOR_ENTRY_TYPE &v);
  };
  STRUCT VECTOR_ENTRY_CONST_NAME {
    const KEY_T m_k;
    const VECTOR_TYPE &m_vec;
    VALUE_T m_v;

    VECTOR_ENTRY_CONST_NAME(const VECTOR_TYPE &v, KEY_T id);
    operator VALUE_T() const;

    friend std::ostream& ::operator<< <>(std::ostream &os, const VECTOR_ENTRY_CONST_TYPE &e);
  };

  STRUCT VECTOR_OPERATOR_BASE_NAME {

  };
  STRUCT VECTOR_OPERATOR__NAME
    : VECTOR_OPERATOR_BASE_NAME TYPE {
    VECTOR_TYPE &m_vec;

    VECTOR_OPERATOR__NAME(VECTOR_TYPE &vec);
  };
  STRUCT VECTOR_OPERATOR__CONST_NAME
    : VECTOR_OPERATOR_BASE_NAME TYPE {
    const VECTOR_TYPE &m_vec;

    VECTOR_OPERATOR__CONST_NAME(const VECTOR_TYPE &vec);
  };
};

#ifndef VECTOR_NO_HEADER_TEMPLATES
  #include "vector.txx"
#endif

#include "vector.uxx"