
// Copyright (c) 2014-2015 niXman (i dot nixman dog gmail dot com). All
// rights reserved.
//
// This file is part of ENUM-GEN(https://github.com/niXman/enum-gen) project.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

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
	,
	(member0)
	(member1)
	(member2)
)

ENUM_GEN_DECLARE_ENUM_CLASS(
	 myenum1
	,std::uint8_t
	,
	(member1, 1<<0)
	(member2, 1<<1)
	(member3, 1<<2)
	(member4, 1<<3)
);

ENUM_GEN_DECLARE_ENUM_CLASS(
	 myenum2
	,std::uint8_t
	,
	(member4)
	(member5,0x10)
	(member6)
);

ENUM_GEN_DECLARE_ENUM_CLASS(
	 myenum3
	,std::uint32_t
	,
	(member7)
	(member8)
	(member9)
);

ENUM_GEN_DECLARE_ENUM_CLASS(
	 myenum4
	,std::uint64_t
	,
	(member10)
	(member11)
	(member12)
);

ENUM_GEN_DECLARE_ENUM(
	 myenum5
	,
	(member13)
	(member14)
	(member15)
);

/***************************************************************************/

void test_for_each() {
	int idx = 0;
	for ( const auto &it: enum_info<myenum0>::values ) {
		switch ( idx ) {
			case 0: MY_ASSERT(
				0         == strcmp(it.name, "myenum0::member0") &&
				0         == strcmp("myenum0::member0", enum_cast(it.value)) &&
				it.ivalue == static_cast<enum_info<myenum0>::underlying_type>(it.value) &&
				0         == it.ivalue
			);
			break;
			case 1: MY_ASSERT(
				0         == strcmp(it.name, "myenum0::member1") &&
				0         == strcmp("myenum0::member1", enum_cast(it.value)) &&
				it.ivalue == static_cast<enum_info<myenum0>::underlying_type>(it.value) &&
				1         == it.ivalue
			);
			break;
			case 2: MY_ASSERT(
				0         == strcmp(it.name, "myenum0::member2") &&
				0         == strcmp("myenum0::member2", enum_cast(it.value)) &&
				it.ivalue == static_cast<enum_info<myenum0>::underlying_type>(it.value) &&
				2         == it.ivalue
			);
			break;
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

	std::stringstream s5;
	myenum5 e5 = myenum5::member13;
	s5 << e5;
	MY_ASSERT(0 == strcmp(s5.str().c_str(), "myenum5::member13"));

	std::cout << "test_out() PASSED" << std::endl;
}

void test_cast_to_char() {
	MY_ASSERT(0 == strcmp("myenum1::member2", enum_cast(myenum1::member2)));
	MY_ASSERT(0 == strcmp("myenum2::member5", enum_cast(myenum2::member5)));
	MY_ASSERT(0 == strcmp("myenum3::member8", enum_cast(myenum3::member8)));
	MY_ASSERT(0 == strcmp("myenum4::member11", enum_cast(myenum4::member11)));
	MY_ASSERT(0 == strcmp("myenum5::member13", enum_cast(myenum5::member13)));

	MY_ASSERT(0 == strcmp("member2", enum_cast(myenum1::member2, false)));
	MY_ASSERT(0 == strcmp("member5", enum_cast(myenum2::member5, false)));
	MY_ASSERT(0 == strcmp("member8", enum_cast(myenum3::member8, false)));
	MY_ASSERT(0 == strcmp("member11", enum_cast(myenum4::member11, false)));
	MY_ASSERT(0 == strcmp("member13", enum_cast(myenum5::member13, false)));

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
	MY_ASSERT(myenum5::member13 == enum_cast<myenum5>("myenum5::member13"));
	MY_ASSERT(myenum5::member13 == enum_cast<myenum5>("member13"));

	std::cout << "test_cast_from_char() PASSED" << std::endl;
}

void test_operators() {
	static_assert(
		 std::is_same<std::underlying_type<myenum1>::type, std::uint8_t>::value
		 && std::is_same<decltype(myenum1::member1 | myenum1::member2), std::underlying_type<myenum1>::type>::value
		,"type error!"
	);

	constexpr auto v0 = myenum1::member1 | myenum1::member2;
	static_assert(v0 == 3, "'operator|' error!");

	constexpr auto v1 = (v0 & myenum1::member2);
	static_assert(
		 std::is_same<std::remove_const<decltype(v1)>::type, std::uint8_t>::value && v1 == (std::uint8_t)2
		,"'operator&' error!"
	);

	constexpr auto v2 = (v0 & myenum1::member3);
	static_assert(
		 std::is_same<std::remove_const<decltype(v1)>::type, std::uint8_t>::value && v2 == (std::uint8_t)0
		,"'operator&' error!"
	);

	std::cout << "test_operators() PASSED" << std::endl;
}

/***************************************************************************/

int main() {
	test_for_each();
	test_out();
	test_cast_to_char();
	test_cast_from_char();
	test_operators();

	return EXIT_SUCCESS;
}

/***************************************************************************/
