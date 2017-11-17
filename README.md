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
for ( const auto &it: enum_info<myenum1>::values ) {
    std::cout
    << "name=" << it.name // name of member as const char*
    << ", value=" << static_cast<enum_info<myenum1>::underlying_type>(it.value) // enum member
    << ", ivalue=" << it.ivalue // const std::uint8_t
    << std::endl;
}

myenum1 e0 = myenum1::member2;
const char *name = enum_cast(e0); // cast to cstring
assert(0 == std::strcmp(name, "myenum1::member2"));

myenum1 e1 = enum_cast<myenum1>(name); // cast from cstring
assert(e1 == e0);
```

### Using iterators with generated meta-code
```cpp
for ( auto it = enum_info<myenum1>::begin(); it != enum_info<myenum1>::end(); ++it ) {
    std::cout
    << "name=" << it->name // name of member as const char*
    << ", value=" << static_cast<enum_info<myenum1>::underlying_type>(it->value) // enum member
    << ", ivalue=" << it->ivalue // const std::uint8_t
    << std::endl;
}
```

### Example of generated meta-code
Using this macro:
```cpp
ENUM_GEN_DECLARE_ENUM(
     myenum1
    ,
    (member1, 0x02)
    (member2)
    (member3, 0x04)
    (member4)
)
```
This code will be generated:
```cpp
enum myenum1 {
     member1 = 0x02
    ,member2
    ,member3 = 0x04
    ,member4
};

template <typename>
struct enum_info;

template <>
struct enum_info<myenum1> {
    using underlying_type = std::underlying_type<myenum1>::type;
    struct value_type {
        const char* name;
        const myenum1 value;
        const underlying_type ivalue;
        
        using const_iterator = value_type const*;
        static const_iterator begin() { return &values[0]; }
        static const_iterator end() { return &values[4]; }
    };
    static const value_type values[];
};
const enum_info<myenum1>::value_type enum_info<myenum1>::values[] = {
     { "myenum1::member1", myenum1::member1, static_cast<enum_info<myenum1>::underlying_type>(myenum1::member1) }
    ,{ "myenum1::member2", myenum1::member2, static_cast<enum_info<myenum1>::underlying_type>(myenum1::member2) }
    ,{ "myenum1::member3", myenum1::member3, static_cast<enum_info<myenum1>::underlying_type>(myenum1::member3) }
    ,{ "myenum1::member4", myenum1::member4, static_cast<enum_info<myenum1>::underlying_type>(myenum1::member4) }
};

inline const char* enum_cast(const myenum1 e, const bool full_name = true) {
    const std::size_t offset = (true == full_name ? 0 : sizeof("myenum1::")-1);
    switch (e) {
        case myenum1::member1: return enum_info<myenum1>::values[0].name+offset;
        case myenum1::member2: return enum_info<myenum1>::values[1].name+offset;
        case myenum1::member3: return enum_info<myenum1>::values[2].name+offset;
        case myenum1::member4: return enum_info<myenum1>::values[3].name+offset;
    }

    assert("bad enum value #1" == 0);
}

inline myenum1 enum_cast(myenum1, const char* str) {
    const std::size_t offset = (0 != std::strchr(str, ':') ? 0 : sizeof("myenum1::")-1);
    for (const auto& it : enum_info<myenum1>::values) {
        if (0 == std::strcmp(it.name + offset, str))
            return it.value;
    }

    assert("bad enum value #2" == 0);
}

inline bool has_member(myenum1, const char* str) {
    const std::size_t offset = (0 != std::strchr(str, ':') ? 0 : sizeof("myenum1::")-1);
    for (const auto& it : enum_info<myenum1>::values) {
        if (0 == std::strcmp(it.name + offset, str))
            return true;
    }

    return false;
}

std::ostream& operator<<(std::ostream& os, const myenum1 e) {
    return (os << enum_cast(e));
}

inline constexpr enum_info<myenum1>::underlying_type operator|(const myenum1 l, const myenum1 r) {
    return static_cast<enum_info<myenum1>::underlying_type>(l) | static_cast<enum_info<myenum1>::underlying_type>(r);
}

inline constexpr enum_info<myenum1>::underlying_type operator&(const myenum1 l, const enum_info<myenum1>::underlying_type r) {
    return static_cast<enum_info<myenum1>::underlying_type>(l) & r;
}

inline constexpr enum_info<myenum1>::underlying_type operator&(const enum_info<myenum1>::underlying_type l, const myenum1 r) {
    return l & static_cast<enum_info<myenum1>::underlying_type>(r);
}
```
