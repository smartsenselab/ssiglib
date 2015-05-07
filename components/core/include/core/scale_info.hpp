#ifndef _SSF_CORE_SCALE_INFO_HPP_
#define _SSF_CORE_SCALE_INFO_HPP_

#include "core/ssfdef.hpp"
#include "core/rect.hpp"

namespace ssf{

	class ScaleInfo{
	
	public:
		ScaleInfo(void);
		virtual ~ScaleInfo(void);
		ScaleInfo(const ScaleInfo& rhs);
		ScaleInfo& operator=(const ScaleInfo& rhs);

		int getStrideY() const;
		void setStrideY(const int& strideY);

		int getStrideX() const;
		void setStrideX(const int& stideX);

		int getInterpolationMethod() const;
		void setInterpolationMethod(const int& interpolationMethod);

		Rect<int> getObjectSize() const;
		void setObjectSize(const Rect<int>& objectSize);

		Rect<int> getDetWindowSize() const;
		void setDetWindowSize(const Rect<int>& detWindowSize);

	private:
		int strideX, strideY;
		int interpolationMethod;
		float scale;
		Rect<int> objectSize;
		Rect<int> detWindowSize;

	};

}

#endif // !_SSF_CORE_SCALE_INFO_HPP_