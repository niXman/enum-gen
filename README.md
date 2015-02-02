[![Build Status](https://travis-ci.org/niXman/enum-gen.svg?branch=master)](https://travis-ci.org/niXman/enum-gen)

enum-gen
========

'enum's and C++11 'enum class'es preprocessor generator

### "Example"

For this macro record:
```cpp
ENUM_GEN_DECLARE_ENUM(
   myenum1, std::uint8_t,
   (member1,2)
   (member2)
   (member3,0x44)
)
```

will be generated this code:
```cpp
enum class myenum1: std::uint8_t {
	 member1 = 2
	,member2
	,member3 = 0x44
};

inline const char* enum_cast(const myenum1& e, const bool flag = true) {
	const std::size_t offset = (true == flag ? 0 : sizeof("myenum1::") - 1);
	switch (e) {
		case myenum1::member1: return "myenum1::member1"+offset;
		case myenum1::member2: return "myenum1::member2"+offset;
		case myenum1::member3: return "myenum1::member3"+offset;
	}
	assert("bad enum value #1" == 0);
}

template <typename E>
E enum_cast(const char*);

template <>
myenum1 enum_cast<myenum1>(const char* str) {
	static const char* members[] = {
		 "myenum1::member1"
		,"myenum1::member2"
		,"myenum1::member3"
		,0
	};
	const std::size_t offset = (0 != std::strchr(str, ':') ? 0 : sizeof("myenum1::") - 1);
	for (std::size_t idx = 0; idx < 3; ++idx) {
		switch (idx) {
			case 0: if (0 == std::strcmp(members[0]+offset, str)) return myenum1::member1;
			case 1: if (0 == std::strcmp(members[1]+offset, str)) return myenum1::member2;
			case 2: if (0 == std::strcmp(members[2]+offset, str)) return myenum1::member3;
		}
	}
	assert("bad enum value #2" == 0);
}

std::ostream& operator<<(std::ostream& os, const myenum1& e) {
	return (os << enum_cast(e));
}

inline constexpr myenum1 operator&(const myenum1& l, const myenum1& r) {
	return static_cast<myenum1>(static_cast<std::uint8_t>(l) & static_cast<std::uint8_t>(r));
}

inline constexpr myenum1 operator|(const myenum1& l, const myenum1& r) {
	return static_cast<myenum1>(static_cast<std::uint8_t>(l) | static_cast<std::uint8_t>(r));
}

inline constexpr myenum1 operator^(const myenum1& l, const myenum1& r) {
	return static_cast<myenum1>(static_cast<std::uint8_t>(l) ^ static_cast<std::uint8_t>(r));
}
```
