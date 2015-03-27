#ifndef _SSF_CORE_CLASS_TEST_HPP_
#define _SSF_CORE_CLASS_TEST_HPP_

namespace ssf{

	class ClassTest{
	
	public:
		ClassTest(void);
		virtual ~ClassTest(void);
		ClassTest(const ClassTest& rhs);
		ClassTest& operator=(const ClassTest& rhs);

	private:
		//private members

	};

}

#endif // !_SSF_CORE_CLASS_TEST_HPP_