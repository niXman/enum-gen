
#include "enum-gen.hpp"

#include <iostream>
#include <sstream>

/***************************************************************************/

ENUM_GEN_DECLARE_ENUM(
   myenum1, std::uint8_t,
   (member1,2)
   (member2)
   (member3,0x44)
);

ENUM_GEN_DECLARE_ENUM(
   myenum2, std::uint8_t,
   (member4)
   (member5,0x10)
   (member6)
);

ENUM_GEN_DECLARE_ENUM(
   myenum3, std::uint32_t,
   (member7)
   (member8)
   (member9)
);

ENUM_GEN_DECLARE_ENUM(
   myenum4, std::uint64_t,
   (member10)
   (member11)
   (member12)
);

/***************************************************************************/

void test_out() {
   std::stringstream s1;
   myenum1 e1 = myenum1::member2;
   s1 << e1;
   assert(0 == strcmp(s1.str().c_str(), "myenum1::member2"));

   std::stringstream s2;
   myenum2 e2 = myenum2::member5;
   s2 << e2;
   assert(0 == strcmp(s2.str().c_str(), "myenum2::member5"));

   std::stringstream s3;
   myenum3 e3 = myenum3::member8;
   s3 << e3;
   assert(0 == strcmp(s3.str().c_str(), "myenum3::member8"));

   std::stringstream s4;
   myenum4 e4 = myenum4::member11;
   s4 << e4;
   assert(0 == strcmp(s4.str().c_str(), "myenum4::member11"));

   std::cout << "test_out() PASSED" << std::endl;
}

void test_cast_to_char() {
   assert(0 == strcmp("myenum1::member2", enum_cast(myenum1::member2)));
   assert(0 == strcmp("myenum2::member5", enum_cast(myenum2::member5)));
   assert(0 == strcmp("myenum3::member8", enum_cast(myenum3::member8)));
   assert(0 == strcmp("myenum4::member11", enum_cast(myenum4::member11)));

   std::cout << "test_cast_to_char() PASSED" << std::endl;
}

void test_cast_from_char() {
   assert(myenum1::member2 == enum_cast<myenum1>("myenum1::member2"));
   assert(myenum2::member5 == enum_cast<myenum2>("myenum2::member5"));
   assert(myenum3::member8 == enum_cast<myenum3>("myenum3::member8"));
   assert(myenum4::member11 == enum_cast<myenum4>("myenum4::member11"));
   std::cout << "test_cast_from_char() PASSED" << std::endl;
}

/***************************************************************************/

int main() {
   test_out();
   test_cast_to_char();
   test_cast_from_char();
}

/***************************************************************************/
