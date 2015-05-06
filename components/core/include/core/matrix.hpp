#ifndef _SSF_CORE_MATRIX_HPP_
#define _SSF_CORE_MATRIX_HPP_

#include <opencv/cv.h>

namespace ssf{

	class Matrix{
	
	public:
		Matrix(void);
		virtual ~Matrix(void);
		Matrix(const Matrix& rhs);
		Matrix& operator=(const Matrix& rhs);

	private:
		//private members

	};

}

#endif // !_SSF_CORE_MATRIX_HPP_