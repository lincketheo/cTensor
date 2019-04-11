#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <string>

namespace matlib{
	struct element{
		element *left = NULL;
		element *right = NULL;
		element *up = NULL;
		element *down = NULL;

		bool visited;

		int val;
	};

	class Matrix{
		public:
			Matrix();
			Matrix(std::string str);
			~Matrix();
			
			void augment(Matrix m);
			
		private:
		
	};

	Matrix transpose(Matrix m);
}

#endif
