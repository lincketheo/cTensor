/**
 * @author      : theo (theo@$HOSTNAME)
 * @file        : MatrixInterface
 * @created     : Monday Sep 30, 2019 15:16:32 MDT
 */

#ifndef MATRIXINTERFACE_HPP

#define MATRIXINTERFACE_HPP

struct dim
{
  dim(const size_t x_, const size_t y_)
    : x(_x)
    , y(_y)
  {}
  size_t x;
  size_t y;
};

template<typename T>
class MatrixInterface
{
public:
  virtual ~MatrixInterface() = default;

  MatrixInterface<T> operator-(const MatrixInterface<T>&) const;
  MatrixInterface<T> operator+(const MatrixInterface<T>&) const;
  void operator+=(const MatrixInterface<T>&);
  void operator-=(const MatrixInterface<T>&);
  void operator*=(const MatrixInterface<T>&);
  void operator/=(const MatrixInterface<T>&);

  bool operator<(const MatrixInterface<T>&) const;
  bool operator>(const MatrixInterface<T>&) const;
  bool operator>=(const MatrixInterface<T>&) const;
  bool operator<=(const MatrixInterface<T>&) const;
  bool operator==(const MatrixInterface<T>&) const;

  MatrixInterface<T>& operator[](size_t col);

  // Type casting
  T operator float() const;

  // Operations
  MatrixInterface<T> operator!();
  MatrixInterface<T> operator*();
  MatrixInterface<T> operator~();

  // Equality
  void operator=(const MatrixInterface<T>&);

  // get the dimension
  inline dim get_dimension() { return dim; }

protected:
  dim dimension;

private:
  // Arithmetic
  virtual void __add__(const MatrixInterface<T>&) = 0;
  virtual void __stdMult__(const MatrixInterface<T>&) = 0;

  // Data structure
  virtual void __copy__(const MatrixInterface<T>&) = 0;

  virtual void __deep_copy__(const MatrixInterface<T>& input)
  {
    __copy__(input);
  }
  virtual void __shallow_copy__(const MatrixInterface<T>& input)
  {
    __copy__(input);
  }

  // Relational
  virtual bool __compare_greater_than__(const MatrixInterface<T>&) = 0;
  virtual bool __compare_less_than__(const MatrixInterface<T>&) = 0;
  virtual bool __compare_greater_or_equal__(const MatrixInterface<T>&) = 0;
  virtual bool __compare_less_or_equal__(const MatrixInterface<T>&) = 0;
  virtual bool __compare_equal__(const MatrixInterface<T>&) = 0;
  virtual bool __compare_weak_equal__(const MatrixInterface<T>&) = 0;

  // MatrixInterface operations
  virtual T __trace__() = 0;

  virtual bool __to_inverse__() = 0;
  virtual MatrixInterface<T> __inverse__() = 0;

  virtual bool __to_transpose__() = 0;
  virtual MatrixInterface<T> __transpose__() = 0;

  // Accessors
  virtual const MatrixInterface<T>& get_row(size_t index) const = 0;
  virtual const MatrixInterface<T>& get_col(size_t index) const = 0;
  virtual const T& get(size_t row, size_t col) const = 0;
};

#endif /* end of include guard MATRIXINTERFACE_HPP */
