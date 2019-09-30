/**
 * @author      : theo (theo@$HOSTNAME)
 * @file        : MatrixInterface
 * @created     : Monday Sep 30, 2019 15:16:32 MDT
 */

#ifndef MATRIXINTERFACE_HPP

#define MATRIXINTERFACE_HPP


template <typename T>
class MatrixInterface
{
    public:
        virtual ~MatrixInterface () = default;

        Matrix operator-() const;
        Matrix operator+() const;
        void operator=(const Matrix&);



      
    private:
      // Arithmetic
      virtual void __add__(const Matrix&) = 0;
      virtual void __stdMult__(const Matrix&) = 0;

      // Data structure
      virtual void __copy__(const Matrix&) = 0;

      virtual void __deep_copy__(const Matrix& input) { __copy__(input); }
      virtual void __shallow_copy__(const Matrix& input) { __copy__(input); }

      // Relational 
      virtual bool __compare_greater_than__(const Matrix&) = 0;
      virtual bool __compare_less_than__(const Matrix&) = 0;
      virtual bool __compare_greater_or_equal__(const Matrix&) = 0;
      virtual bool __compare_less_or_equal__(const Matrix&) = 0;
      virtual bool __compare_equal__(const Matrix&) = 0;
      virtual bool __compare_weak_equal__(const Matrix&) = 0;

      // Matrix operations
      virtual T __trace__ () = 0;

      virtual bool __to_inverse__() = 0;
      virtual Matrix __inverse__() = 0;

      virtual bool __to_transpose__() = 0;
      virtual Matrix __transpose__ () = 0;
};

#endif /* end of include guard MATRIXINTERFACE_HPP */

