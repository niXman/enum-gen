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
   myenum1, std::uint8_t,
   (member1,2)
   (member2)
   (member3,0x44)
)
```

### Using generated meta-code
```cpp
// using generated meta-code
for ( const auto &it: enum_info<myenum1>::values ) {
	std::cout
		<< "name=" << it.name // const char *
		<< ", value=" << static_cast<std::uint8_t>(it.value) // const myenum1, cast to underlying type
		<< ", ivalue=" << it.ivalue // const std::uint8_t
	<< std::endl;
}

myenum1 e0 = myenum1::member2;
const char *name = enum_cast(e0); // cast to string
assert(0 == std::strcmp(name, "myenum1::member2"));

myenum1 e1 = enum_cast<myenum1>(name);
assert(e1 == e0);
```
