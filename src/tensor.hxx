#pragma once

#include <map>
#include <vector>

#include "preprocessor.dxx"



namespace TENSOR_NAMESPACE_NAME {

  template<
    class VALUE_T,
    class INTEGRAL_T,
    template<class, class> class CONTAINER_T,
    template<class> class KEY_T
  > struct TENSOR_NAME {

    KEY_T m_size;
    VALUE_T m_val;
    CONTAINER_T<KEY_T, VALUE_T> m_data;


    // tensor();
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

    const VECTOR_NAME& operator=(std::initializer_list<VALUE_T> l);
    friend std::ostream& ::operator<< <>(std::ostream& os, const VECTOR_TYPE &v);
    // ull rank() const;
    // ull rank(const rank_t &_rank);

    // ull n_elem() const;
    // rank_t strides() const;

    // bool valid(const ull & _key) const;
    // bool valid(const rank_t &_addr) const;

    // bool key(const rank_t &_addr, ull &_key) const;
    // bool addr(ull _key, rank_t &_addr) const;

    // T& at(const ull &_key);
    // //T& at(const ull &_key) const;
    // T& at(const rank_t &_addr);
    // //T& at(const rank_t &_addr) const;

  };
} // namespace TENSOR_NAMESPACE_NAME


#include "preprocessor.uxx"