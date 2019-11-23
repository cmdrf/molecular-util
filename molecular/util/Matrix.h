/*	Matrix.h

MIT License

Copyright (c) 2018 Fabian Herb

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef MOLECULAR_MATRIX_H
#define MOLECULAR_MATRIX_H

#include <iostream>
#include <initializer_list>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <Eigen/Dense>

namespace molecular
{
namespace util
{

/// Generic matrix template class
template<int rows, int cols, typename T = float>
class Matrix
{
public:
	using ValueType = T;

	static const int kRows = rows;
	static const int kCols = cols;

	/// Default constructor
	Matrix() = default;

	/// Construct matrix from an array in row-major order
	Matrix(const T values[rows * cols])
	{
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < cols; j++)
				m[i][j] = values[i * cols + j];
		}
	}

	/// Construct matrix from two-dimensional array
	Matrix(const T values[rows][cols])
	{
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < cols; j++)
				m[i][j] = values[i][j];
		}
	}

	Matrix(std::initializer_list<T> init)
	{
		assert(init.size() == rows * cols);
		auto it = init.begin();
		for(int i = 0; i < rows; i++)
			for(int j = 0; j < cols; j++, ++it)
				m[i][j] = *it;
	}

	/// Construct from Eigen expression
	template<typename OtherDerived>
	Matrix(const Eigen::MatrixBase<OtherDerived>& other)
	{
		ToEigen() = other;
	}

	/// Assign from Eigen expression
	template<typename OtherDerived>
	Matrix& operator=(const Eigen::MatrixBase <OtherDerived>& other)
	{
		ToEigen() = other;
		return *this;
	}

	/// Returns array of matrix elements in row-major order
	/** OpenGL wants column-major order. */
	inline const T* Get() const {return &m[0][0];}
	inline T* operator[](int row) {return m[row];}
	inline const T* operator[](int row) const {return m[row];}

	/** Eigen compatibility. */
	inline T operator()(int row, int col) const {return m[row][col];}

	/** Eigen compatibility. */
	inline T& operator()(int row, int col) {return m[row][col];}

	auto ToEigen() {return Eigen::Map<Eigen::Matrix<T, rows, cols, Eigen::DontAlign | Eigen::RowMajor>>(m[0]);}
	auto ToEigen() const {return Eigen::Map<const Eigen::Matrix<T, rows, cols, Eigen::DontAlign | Eigen::RowMajor>>(m[0]);}

	/// Matrix-matrix multiplication
	template<class M>
	Matrix<rows, M::kCols, T> operator*(const M& mat) const
	{
		static_assert(cols == M::kRows, "Columns of left operand must equal rows of right operand");
//		static_assert(rows == M::kCols);

		Matrix<rows, M::kCols, T> newMat;
		for(int r = 0; r < rows; r++)
		{
			for(int c = 0; c < M::kCols; c++)
			{
				T sum = 0;
				for(int k = 0; k < cols; ++k)
				{
					sum += m[r][k] * mat(k, c);
				}
				newMat(r, c) = sum;
			}
		}
		return newMat;
	}

	/// Matrix-scalar multiplication
	Matrix operator*(ValueType s) const
	{
		Matrix newMat;
		for(int r = 0; r < rows; r++)
		{
			for(int c = 0; c < cols; c++)
				newMat(r, c) = m[r][c] * s;
		}
		return newMat;
	}

	Matrix operator+(const Matrix& mat) const
	{
		Matrix newMat;
		for(int r = 0; r < rows; r++)
		{
			for(int c = 0; c < cols; c++)
				newMat(r, c) = m[r][c] + mat(r, c);
		}
		return newMat;
	}

	Matrix& operator+=(const Matrix& mat)
	{
		for(int r = 0; r < rows; r++)
			for(int c = 0; c < cols; c++)
				m[r][c] += mat(r, c);
		return *this;
	}

	Matrix& operator*=(const Matrix& mat)
	{
		*this = *this * mat;
		return *this;
	}

	Matrix& operator*=(ValueType s)
	{
		for(int r = 0; r < rows; r++)
			for(int c = 0; c < cols; c++)
				m[r][c] *= s;
		return *this;
	}

	Matrix& operator/=(ValueType s)
	{
		for(int r = 0; r < rows; r++)
			for(int c = 0; c < cols; c++)
				m[r][c] /= s;
		return *this;
	}

	static Matrix Identity()
	{
		Matrix newMat;
		for(int i = 0; i < rows; ++i)
		{
			for(int j = 0; j < cols; ++j)
			{
				if(i == j)
					newMat(i, j) = 1;
				else
					newMat(i, j) = 0;
			}
		}
		return newMat;
	}

	static Matrix Zeros()
	{
		Matrix newMat;
		for(int i = 0; i < rows; ++i)
			for(int j = 0; j < cols; ++j)
					newMat(i, j) = 0;
		return newMat;
	}

	void SetIdentity()
	{
		for(int i = 0; i < rows; ++i)
		{
			for(int j = 0; j < cols; ++j)
			{
				if(i == j)
					m[i][j] = 1;
				else
					m[i][j] = 0;
			}
		}
	}

	/// Returns the matrix with mat concatenated to the right side
	/** Both matrices must have the same number of rows. The resulting matrix
		has as many columns as both input matrices together. */
	template<class M>
	Matrix<M::kRows, M::kCols + cols, T> Augmented(const M& mat) const
	{
		static_assert(M::kRows == rows, "Both matrices must have the same number of rows");

		Matrix<M::kRows, M::kCols + cols, T> newMat;
		for(int r = 0; r < rows; ++r)
		{
			for(int c = 0; c < cols; ++c)
				newMat(r, c) = m[r][c];
		}

		for(int r = 0; r < rows; ++r)
		{
			for(int c = 0; c < M::kCols; ++c)
				newMat(r, c + cols) = mat(r, c);
		}
		return newMat;
	}

	/// Returns the right portion of the matrix with the given width
	template<int newcols>
	Matrix<rows, newcols, T> SubMatrixRight() const;

	/// Returns the left portion of the matrix with the given width
	template<int newcols>
	Matrix<rows, newcols, T> SubMatrixLeft() const;

	void Print() const
	{

		for(int r = 0; r < rows; ++r)
		{
			for(int c = 0; c < cols; ++c)
			{
				std::cout.width(3);
				std::cout << m[r][c] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	/// Returns the inverse of the matrix
	Matrix<rows, cols, T> Inverse() const;

	/// Returns the transposed of the matrix
	Matrix<cols, rows, T> Transposed() const
	{
		Matrix<cols, rows, T> newMat;
		for(int r = 0; r < rows; ++r)
		{
			for(int c = 0; c < cols; ++c)
				newMat(c, r) = m[r][c];
		}
		return newMat;
	}

	/// Returns the sum of the diagonal elements
	T Trace() const
	{
		static_assert(rows == cols, "Number of rows must equal number of columns");
		T sum = 0;
		for(int i = 0; i < rows; ++i)
			sum += m[i][i];

		return sum;
	}

protected:
	/** Row-major order. */
	T m[rows][cols];
};

/*****************************************************************************/

template<int rows, int cols, typename T>
template<int newcols>
Matrix<rows, newcols, T> Matrix<rows, cols, T>::SubMatrixRight() const
{
	static_assert(newcols < cols, "Can only extract submatrix that is smaller");

	Matrix<rows, newcols, T> newMat;
	for(int r = 0; r < rows; ++r)
	{
		for(int c = 0; c < newcols; ++c)
		{
			newMat(r, c) = m[r][c + cols - newcols];
		}
	}
	return newMat;
}

template<int rows, int cols, typename T>
template<int newcols>
Matrix<rows, newcols, T> Matrix<rows, cols, T>::SubMatrixLeft() const
{
	static_assert(newcols < cols, "Can only extract submatrix that is smaller");

	Matrix<rows, newcols, T> newMat;
	for(int r = 0; r < rows; ++r)
	{
		for(int c = 0; c < newcols; ++c)
		{
			newMat[r][c] = m[r][c];
		}
	}
	return newMat;
}

template<int rows, int cols, typename T>
Matrix<rows, cols, T> Matrix<rows, cols, T>::Inverse() const
{
	return ToEigen().inverse();
}

/*****************************************************************************/

/// Scalar multiplication
template<int rows, int cols, typename T>
Matrix<rows, cols, T> operator*(T f, Matrix<rows, cols, T> m)
{
	Matrix<rows, cols, T> newMat;
	for(int r = 0; r < rows; ++r)
	{
		for(int c = 0; c < cols; ++c)
			newMat[r][c] = m[r][c] * f;
	}
	return newMat;
}

template<int rows, int cols, typename T>
std::ostream& operator<<(std::ostream& o, const Matrix<rows, cols, T>& m)
{
	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < cols; ++c)
			o << m[r][c] << " ";
		o << '\n';
	}
	return o;
}

}
} // namespace molecular

#endif // MATRIX_H
