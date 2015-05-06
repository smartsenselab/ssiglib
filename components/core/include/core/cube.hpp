#ifndef _SSF_CORE_CUBE_HPP_
#define _SSF_CORE_CUBE_HPP_

namespace ssf{

	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	class Cube{
	
	public:
		Cube(T x = 0, T y = 0, T z = 0, T width = 0, T height = 0, T length = 0)
			: mPosition(Point3D<T>(x, y, z)),
			mWidht(width), mHeight(height), mLength(length){
		}

		virtual ~Cube(void){
		}

		Cube(const Cube& rhs){
			this->mPosition = rhs.mPosition;
			this->mWidht = rhs.mWidht;
			this->mHeight = rhs.mHeight;
			this->mLength = rhs.mLength;
		}

		Cube& operator=(const Cube& rhs){
			if (this != &rhs){
				this->mPosition = rhs.mPosition;
				this->mWidht = rhs.mWidht;
				this->mHeight = rhs.mHeight;
				this->mLength = rhs.mLength;
			}
			return *this;
		}

		Point3D<T> getPosition() const { return this->mPosition; }
		void setPosition(const Point3D<T>& position) { this->mPosition = position; }

		inline T getPositionX() const { return this->mPosition.getX(); }
		inline void setPositionX(const T& x) { this->mPosition.setX(x); }
		inline T getPositionY() const { return this->mPosition.getY(); }
		void setPositionY(const T& y) { this->mPosition.setY(y); }
		inline T getPositionZ() const { return this->mPosition.getZ(); }
		void setPositionZ(const T& z) { this->mPosition.setZ(z); }

		T getLength() const { return this->mLength; }
		void setLength(const T& length) { this->mLength = length; }

		T getHeight() const { return this->mHeight;}
		void setHeight(const T& height) { this->mHeight = height; }

		T getWidht() const { return this->mWidht;}
		void setWidht(const T& widht) { this->mWidht = widht; }

	private:
		Point3D<T> mPosition;
		T mWidht, mHeight, mLength;
		
	};

}

#endif // !_SSF_CORE_CUBE_HPP_