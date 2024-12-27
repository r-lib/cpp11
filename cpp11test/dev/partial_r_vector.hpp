class const_iterator {
    // Iterator references:
    // https://cplusplus.com/reference/iterator/
    // https://stackoverflow.com/questions/8054273/how-to-implement-an-stl-style-iterator-and-avoid-common-pitfalls
    // It seems like our iterator doesn't fully implement everything for
    // `random_access_iterator_tag` (like an `[]` operator, for example). If we discover
    // issues with it, we probably need to add more methods.
   private:
    const r_vector* data_;
    R_xlen_t pos_;
    std::array<underlying_type, 64 * 64> buf_;
    R_xlen_t block_start_ = 0;
    R_xlen_t length_ = 0;

   public:
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::random_access_iterator_tag;

    const_iterator(const r_vector* data, R_xlen_t pos);

    const_iterator operator+(R_xlen_t pos);
    ptrdiff_t operator-(const const_iterator& other) const;

    const_iterator& operator++();
    const_iterator& operator--();

    const_iterator& operator+=(R_xlen_t pos);
    const_iterator& operator-=(R_xlen_t pos);

    bool operator!=(const const_iterator& other) const;
    bool operator==(const const_iterator& other) const;

    T operator*() const;

    friend class writable::r_vector<T>::iterator;

   private:
    /// Implemented in specialization
    static bool use_buf(bool is_altrep);
    void fill_buf(R_xlen_t pos);
  };

template <typename T>
inline bool r_vector<T>::const_iterator::operator==(
    const r_vector::const_iterator& other) const {
  return pos_ == other.pos_;
}

template <typename T>
bool operator==(const r_vector<T>& lhs, const r_vector<T>& rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }

  auto lhs_it = lhs.begin();
  auto rhs_it = rhs.begin();

  auto end = lhs.end();
  while (lhs_it != end) {
    if (!(*lhs_it == *rhs_it)) {
      return false;
    }
    ++lhs_it;
    ++rhs_it;
  }
  return true;
}
