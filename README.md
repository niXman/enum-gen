[![Build Status](https://travis-ci.org/niXman/enum-gen.svg?branch=master)](https://travis-ci.org/niXman/enum-gen)

enum-gen
========

'enum's and C++11 'enum class'es preprocessor generator

### ENUM_GEN_ADAPT_ENUM() example:
```cpp
// existing enum
enum class myenum1: std::uint8_t {
	 member1
	,member2
	,member3
};

// ...

// meta-code generation
ENUM_GEN_ADAPT_ENUM(
	 myenum1
	,std::uint8_t
	,
	(member1)
	(member2)
	(member3)
)
```

### ENUM_GEN_DECLARE_ENUM() example:
```cpp
ENUM_GEN_DECLARE_ENUM(
    myenum1
   ,std::uint8_t
   ,
   (member1,2)
   (member2)
   (member3,0x44)
)
```

### Using generated meta-code
```cpp
for ( const auto &it: enum_info<myenum1>::values ) {
	std::cout
		<< "name=" << it.name // const char *
		<< ", value=" << static_cast<std::uint8_t>(it.value) // const myenum1, casting to underlying type
		<< ", ivalue=" << it.ivalue // const std::uint8_t
	<< std::endl;
}

myenum1 e0 = myenum1::member2;
const char *name = enum_cast(e0); // cast to string
assert(0 == std::strcmp(name, "myenum1::member2"));

myenum1 e1 = enum_cast<myenum1>(name);
assert(e1 == e0);
```

### Example of generated meta-code
Using this macro:
```cpp
ENUM_GEN_DECLARE_ENUM(
    myenum1
   ,std::uint8_t
   ,
   (member1,2)
   (member2)
   (member3,0x44)
)
```
This code will be generated:
```cpp
enum class myenum1 : std::uint8_t { member1 = 2, member2, member3 = 0x44 };

template <typename>
struct enum_info;

template <>
struct enum_info<myenum1> {
	using underlying_type = std::underlying_type<myenum1>::type;
	static const char* names[];
	struct value_type {
		const char* name;
		const myenum1 value;
		const underlying_type ivalue;
	};
	static const value_type values[];
};
const enum_info<myenum1>::value_type enum_info<myenum1>::values[] = {
	{ "myenum1::member1", myenum1::member1, static_cast<enum_info<myenum1>::underlying_type>(myenum1::member1) },
	{ "myenum1::member2", myenum1::member2, static_cast<enum_info<myenum1>::underlying_type>(myenum1::member2) },
	{ "myenum1::member3", myenum1::member3, static_cast<enum_info<myenum1>::underlying_type>(myenum1::member3) },
};

inline const char* enum_cast(const myenum1& e, const bool flag = true) {
	const std::size_t offset = (true == flag ? 0 : sizeof("myenum1::") - 1);
	switch (e) {
		case myenum1::member1: return enum_info<myenum1>::values[0].name + offset;
		case myenum1::member2: return enum_info<myenum1>::values[1].name + offset;
		case myenum1::member3: return enum_info<myenum1>::values[2].name + offset;
	}
	assert("bad enum value #1" == 0);
}

template <typename E>
E enum_cast(const char*);

template <>
myenum1 enum_cast<myenum1>(const char* str) {
	const std::size_t offset = (0 != std::strchr(str, ':') ? 0 : sizeof("myenum1::") - 1);
	for (std::size_t idx = 0; idx < 3; ++idx) {
		switch (idx) {
			case 0: if (0 == std::strcmp(enum_info<myenum1>::values[0].name + offset, str)) return myenum1::member1;
			case 1: if (0 == std::strcmp(enum_info<myenum1>::values[1].name + offset, str)) return myenum1::member2;
			case 2: if (0 == std::strcmp(enum_info<myenum1>::values[2].name + offset, str)) return myenum1::member3;
		}
	}
	assert("bad enum value #2" == 0);
}
std::ostream& operator<<(std::ostream& os, const myenum1& e) {
	return (os << enum_cast(e));
}

```
