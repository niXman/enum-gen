[![Build Status](https://travis-ci.org/niXman/enum-gen.svg?branch=master)](https://travis-ci.org/niXman/enum-gen)

enum-gen
========

'enum's and C++11 'enum class'es preprocessor generator

### ENUM_GEN_ADAPT_ENUM(enum_name, sequence_of_enum_members) example:
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
    ,
    (member1)
    (member2)
    (member3)
)
```

### ENUM_GEN_DECLARE_ENUM(enum_name, sequence_of_enum_members) example:
```cpp
ENUM_GEN_DECLARE_ENUM(
     myenum1
    ,
    (member1, 0x02)
    (member2)
    (member3, 0x04)
)
```

### ENUM_GEN_DECLARE_ENUM_CLASS(enum_name, underlying_type, sequence_of_enum_members) example:
```cpp
ENUM_GEN_DECLARE_ENUM_CLASS(
     myenum1
    ,std::uint8_t
    ,
    (member1, 0x02)
    (member2)
    (member3, 0x04)
)
```

### Using generated meta-code
```cpp
// range-based for
for ( const auto &it: enum_info<myenum1>::values ) {
    std::cout
    << "name=" << it.name // name of member as const char*
    << ", value=" << static_cast<enum_info<myenum1>::underlying_type>(it.value) // enum member
    << ", ivalue=" << it.ivalue // const std::uint8_t, the underlying_type
    << std::endl;
}

// iterators
for ( auto it = enum_info<myenum1>::begin(); it != enum_info<myenum1>::end(); ++it ) {
    std::cout
    << "name=" << it->name // name of member as const char*
    << ", value=" << static_cast<enum_info<myenum1>::underlying_type>(it->value) // enum member
    << ", ivalue=" << it->ivalue // const std::uint8_t, the underlying_type
    << std::endl;
}

myenum1 e0 = myenum1::member2;
const char *name = enum_cast(e0); // cast to cstring
assert(0 == std::strcmp(name, "myenum1::member2"));

myenum1 e1 = enum_cast(myenum1{}, name); // cast from cstring
assert(e1 == e0);

assert(true == has_member(myenum1{}, "myenum1::member2"));
assert(false== has_member(myenum1{}, "myenum1::member4"));

assert(true == has_member(myenum1{}, 0x02));
assert(false== has_member(myenum1{}, 0x05));

const auto &values = get_values(myenum1{}); // array of values of members
MY_ASSERT(values.size() == 4);
MY_ASSERT(values[0] == 1);
MY_ASSERT(values[1] == 2);
MY_ASSERT(values[2] == 4);
MY_ASSERT(values[3] == 16);
```
