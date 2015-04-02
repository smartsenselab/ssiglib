#ifndef _SSF_CORE_CAMERA_HPP_
#define _SSF_CORE_CAMERA_HPP_

namespace ssf{

	class Camera{
	
	public:
		Camera(void);
		virtual ~Camera(void);
		Camera(const Camera& rhs);
		Camera& operator=(const Camera& rhs);

	private:
		//private members

	};

}

#endif // !_SSF_CORE_CAMERA_HPP_