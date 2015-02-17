
#include "enum-gen.hpp"

#include <iostream>
#include <sstream>

/***************************************************************************/

#define MY_ASSERT(...) \
	if ( !(__VA_ARGS__) ) { \
		std::cerr << "expression error(" __FILE__ ":" BOOST_PP_STRINGIZE(__LINE__) "): \"" #__VA_ARGS__ "\"" << std::endl; \
		std::abort(); \
	}

/***************************************************************************/

enum class myenum0: std::uint8_t {
	 member0
	,member1
	,member2
};
ENUM_GEN_ADAPT_ENUM(
	 myenum0
	,std::uint8_t
	,
	(member0)
	(member1)
	(member2)
)

ENUM_GEN_DECLARE_ENUM(
	 myenum1
	,std::uint8_t
	,
	(member1,2)
	(member2)
	(member3,0x44)
);

ENUM_GEN_DECLARE_ENUM(
	 myenum2
	,std::uint8_t
	,
	(member4)
	(member5,0x10)
	(member6)
);

ENUM_GEN_DECLARE_ENUM(
	 myenum3
	,std::uint32_t
	,
	(member7)
	(member8)
	(member9)
);

ENUM_GEN_DECLARE_ENUM(
	 myenum4
	,std::uint64_t
	,
	(member10)
	(member11)
	(member12)
);

/***************************************************************************/

void test_for_each() {
	int idx = 0;
	for ( const auto &it: enum_info<myenum0>::values ) {
//		std::cout << "name=" << it.name << ", value=" << enum_cast(it.value, false) << ", ivalue=" << (int)it.ivalue << std::endl;
		switch ( idx ) {
			case 0: MY_ASSERT(0 == strcmp(it.name, "myenum0::member0") && 0 == strcmp("myenum0::member0", enum_cast(it.value)) && it.ivalue == 0); break;
			case 1: MY_ASSERT(0 == strcmp(it.name, "myenum0::member1") && 0 == strcmp("myenum0::member1", enum_cast(it.value)) && it.ivalue == 1); break;
			case 2: MY_ASSERT(0 == strcmp(it.name, "myenum0::member2") && 0 == strcmp("myenum0::member2", enum_cast(it.value)) && it.ivalue == 2); break;
			default: MY_ASSERT(0)
		}
		++idx;
	}

	std::cout << "test_for_each() PASSED" << std::endl;
}

void test_out() {
	std::stringstream s1;
	myenum1 e1 = myenum1::member2;
	s1 << e1;
	MY_ASSERT(0 == strcmp(s1.str().c_str(), "myenum1::member2"));

	std::stringstream s2;
	myenum2 e2 = myenum2::member5;
	s2 << e2;
	MY_ASSERT(0 == strcmp(s2.str().c_str(), "myenum2::member5"));

	std::stringstream s3;
	myenum3 e3 = myenum3::member8;
	s3 << e3;
	MY_ASSERT(0 == strcmp(s3.str().c_str(), "myenum3::member8"));

	std::stringstream s4;
	myenum4 e4 = myenum4::member11;
	s4 << e4;
	MY_ASSERT(0 == strcmp(s4.str().c_str(), "myenum4::member11"));

	std::cout << "test_out() PASSED" << std::endl;
}

void test_cast_to_char() {
	MY_ASSERT(0 == strcmp("myenum1::member2", enum_cast(myenum1::member2)));
	MY_ASSERT(0 == strcmp("myenum2::member5", enum_cast(myenum2::member5)));
	MY_ASSERT(0 == strcmp("myenum3::member8", enum_cast(myenum3::member8)));
	MY_ASSERT(0 == strcmp("myenum4::member11", enum_cast(myenum4::member11)));

	MY_ASSERT(0 == strcmp("member2", enum_cast(myenum1::member2, false)));
	MY_ASSERT(0 == strcmp("member5", enum_cast(myenum2::member5, false)));
	MY_ASSERT(0 == strcmp("member8", enum_cast(myenum3::member8, false)));
	MY_ASSERT(0 == strcmp("member11", enum_cast(myenum4::member11, false)));

	std::cout << "test_cast_to_char() PASSED" << std::endl;
}

void test_cast_from_char() {
	MY_ASSERT(myenum1::member2 == enum_cast<myenum1>("myenum1::member2"));
	MY_ASSERT(myenum1::member2 == enum_cast<myenum1>("member2"));
	MY_ASSERT(myenum2::member5 == enum_cast<myenum2>("myenum2::member5"));
	MY_ASSERT(myenum2::member5 == enum_cast<myenum2>("member5"));
	MY_ASSERT(myenum3::member8 == enum_cast<myenum3>("myenum3::member8"));
	MY_ASSERT(myenum3::member8 == enum_cast<myenum3>("member8"));
	MY_ASSERT(myenum4::member11 == enum_cast<myenum4>("myenum4::member11"));
	MY_ASSERT(myenum4::member11 == enum_cast<myenum4>("member11"));

	std::cout << "test_cast_from_char() PASSED" << std::endl;
}

/***************************************************************************/

int main() {
	test_for_each();
	test_out();
	test_cast_to_char();
	test_cast_from_char();

	return EXIT_SUCCESS;
}

/***************************************************************************/
