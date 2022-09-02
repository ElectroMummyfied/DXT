#pragma once

#include <map>
#include <vector>
#include <iostream>


#include "tensor.dxx"

// #include "tensor.uxx"
// #include "tensor.dxx"

#include "tensor.fxx"



namespace TNN {
  TTMP struct TN {
    typedef ARRAY_T<INTEGRAL_T> KEY_T;
    typedef MAP_T<KEY_T, VALUE_T> DATA_T;

    KEY_T m_size;
    VALUE_T m_val;
    DATA_T m_data;

    // tensor();
    // VALUE_T (*m_operator_x)(const VALUE_T&, const VALUE_T&);
    // VALUE_T (*m_operator_y)(const VALUE_T&, const VALUE_T&);

    TN(const KEY_T &size = {}, const VALUE_T &dval = 0, const DATA_T &data = {});
    // TN(
    //   std::initializer_list<INTEGRAL_T> size,
    //   std::initializer_list<std::pair<KEY_T, VALUE_T>> vals );

    bool is_valid(const KEY_T &k);

     TET operator[](const KEY_T &k);
    TECT operator[](const KEY_T &k) const;
        // VALUE_T w(const VECTOR_NAME& rhs) const; //    nPr operator
    // VECTOR_NAME x(const VECTOR_NAME& rhs) const; // e-wise operator
    //     VALUE_T y() const;                       // reduce operator

    // VECTOR_NAME operator+(const VECTOR_NAME& rhs);
    // val_t operator*(const VECTOR_NAME& rhs);

    // ull rank() const;
    // ull rank(const rank_t &_rank);
    // ull n_elem() const;
    // rank_t strides() const;
    // bool valid(const ull & _key) const;
    // bool valid(const rank_t &_addr) const;


    //       VECTOR_OPERATOR__TYPE operator[](const VECTOR_ENTRY_PLACEHOLDER_NAME &h);
    // VECTOR_OPERATOR__CONST_TYPE operator[](const VECTOR_ENTRY_PLACEHOLDER_NAME &h) const;

    // T& at(const ull &_key) const;
    // T& at(const ull &_key);
    // T& at(const rank_t &_addr);
    // T& at(const rank_t &_addr) const;

    // VALUE_T operator+() const;
    // VALUE_T operator*() const;
    // VECTOR_TYPE operator>(const VALUE_T val) const;
            // VECTOR_ENTRY_TYPE operator[]();

                    //  VECTOR_BOOL operator<(const VALUE_T val) const;
                    //  VECTOR_BOOL operator>(const VALUE_T val) const;

    const TN& operator=(
      std::initializer_list<std::pair<KEY_T, VALUE_T>> l  );
    friend std::ostream& ::operator<< <>(std::ostream& os, const TTP &t);

  };
  TTMP struct TEBN {
    typedef ARRAY_T<INTEGRAL_T> KEY_T;
    typedef MAP_T<KEY_T, VALUE_T> DATA_T;

    const KEY_T m_k;
    VALUE_T m_v;

    TEBN(KEY_T k);
    virtual operator VALUE_T() const = 0;

    friend std::ostream& ::operator<< <>(std::ostream& os, const TEBT &e);
  };
  TTMP struct TEN : public TEBT {
    using typename TEBT::KEY_T;

    TTP &m_t;

    TEN(TTP &v, KEY_T k);
    operator VALUE_T() const final;

    VALUE_T operator=(VALUE_T val);
  };
  TTMP struct TECN : public TEBT {
    using typename TEBT::KEY_T;

    const TTP &m_t;

    TECN(const TTP &v, KEY_T k);
    operator VALUE_T() const final;
  };
} // namespace TENSOR_NAMESPACE_NAME

#ifndef TENSOR_NO_HEADER_TEMPLATES
  #include "tensor.txx"
#endif

// #include "tensor.uxx"