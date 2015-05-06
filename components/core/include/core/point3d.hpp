#ifndef _SSF_CORE_POINT3D_HPP_
#define _SSF_CORE_POINT3D_HPP_

namespace ssf{

	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	class SSF_EXPORT Point3D{

	public:

		Point3D(T x = 0, T y = 0, T z = 0)
			: mX(x), mY(y), mZ(z){
		}

		virtual ~Point3D(void){
		}

		Point3D(const Point3D& rhs){
			this->mX = rhs.mX;
			this->mY = rhs.mY;
			this->mZ = rhs.mZ;
		}

		Point3D& operator=(const Point3D& rhs){
			if (this != &rhs){
				this->mX = rhs.mX;
				this->mY = rhs.mY;
				this->mZ = rhs.mZ;
			}
			return *this;
		}

		inline T getX() const { return this->mX; }
		inline void setX(const T& x) { this->mX = x; }
		inline T getY() const { return this->mY; }
		void setY(const T& y) { this->mY = y; }
		inline T getZ() const { return this->mZ; }
		void setZ(const T& z) { this->mZ = z; }

	private:
		T mX, mY, mZ;

	};

	typedef Point3D<int> Point3Di;
	typedef Point3D<float> Point3Df;
	typedef Point3D<double> Point3Dd;

}

#endif // !_SSF_CORE_POINT3D_HPP_