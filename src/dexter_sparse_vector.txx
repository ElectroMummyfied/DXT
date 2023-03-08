
namespace dexter::sparse
{

  template <class VALUE>
  vector<VALUE>::vector(
    VALUE default_value,
    unsigned short size
  ) : m_default_value(default_value), m_size(size) {}

  template <class VALUE>
  unsigned short vector<VALUE>::size() const { return this->m_size; }
  template <class VALUE>
  vector_entry<VALUE> vector<VALUE>::operator[](int index)
  {
    return vector_entry<VALUE>(*this, index);
  }

  template <class VALUE>
  const VALUE vector<VALUE>::operator[](int index) const
  {
    auto it = this->m_map.find(index);
    return (it != this->m_map.end() ? it->second : this->m_default_value);
  }
  template <class VALUE>
  std::ostream &operator<<(std::ostream &os, const vector<VALUE> &vec)
  {
    os << "{ ";
    for (unsigned int i = 0; i < vec.m_size; i++)
    {
      os << vec[i] << " ";
    }
    os << "}\n";
    return os;
  }

  template <class VALUE>
  vector_entry<VALUE>::vector_entry(
    vector<VALUE> &vec,
    unsigned short index
  ) : m_vec(vec), m_index(index)
  {
    if (index >= vec.m_size)
      throw std::out_of_range("Index out of range");
  }

  template <class VALUE>
  vector_entry<VALUE>::operator VALUE()
  {
    auto it = this->m_vec.m_map.find(this->m_index);
    return (it != this->m_vec.m_map.end() ? this->m_vec.m_map[this.m_index] : this->m_vec.m_default_value);
  }

  template <class VALUE>
  vector_entry<VALUE> &vector_entry<VALUE>::operator=(const VALUE &value)
  {
    if (value != this->m_vec.m_default_value)
      this->m_vec.m_map[this->m_index] = value;
    return *this;
  }
} // namespace dexter::sparse
