#include <iostream>
#include <stdexcept>

template <class T> class table {
public:
  struct row_t {
  public:
    row_t(T *array) : array_(array) {}
    T &operator[](size_t i) { return array_[i]; }
    const T &operator[](size_t i) const {
      return array_[i];
    }

  private:
    T *array_;
  };

  table(int num_rows, int num_cols) : num_rows_(num_rows), num_cols_(num_cols) {
    array_ = new T[num_rows_ * num_cols_];
  }

  table(const table& other) 
    : num_rows_(other.num_rows_)
    , num_cols_(other.num_cols_) {
    array_ = new T[num_rows_ * num_cols_];
    for (int i = 0; i < num_rows_  * num_cols_; i++) {
      array_[i] = other.array_[i];    
    }
  }

  table& operator=(const table& other) {
    if (this != &other) {
      delete[] array_;
      num_rows_ = other.num_rows_;
      num_cols_ = other.num_cols_;
      array_ = new T[num_rows_ * num_cols_];
      for (int i = 0; i < num_rows_  * num_cols_; i++) {
        array_[i] = other.array_[i];    
      }
    }
    return *this;
  }



  row_t operator[](size_t row) const { return row_t{array_ + row * num_cols_}; }

  ~table() { delete[] array_; }

private:
  T *array_;
  int num_rows_;
  int num_cols_;
};

int main() {
  const auto test = table<int>(2, 3);
  test[0][0] = 4;
  std::cout << test[0][0];
}
