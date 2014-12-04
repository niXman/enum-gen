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

inline const char* enum_cast(const myenum1& e) {
   switch (e) {
      case myenum1::member1: return "myenum1::member1";
      case myenum1::member2: return "myenum1::member2";
      case myenum1::member3: return "myenum1::member3";
   }
   assert("bad enum value #1" == 0);
}

template <typename E>
E enum_cast(const char*);

template <>
myenum1 enum_cast<myenum1>(const char *str) {
   static const std::size_t preflen = sizeof("myenum1::")-1;
   static const char *with_pref[] = {
		 "myenum1::member1"
		,"myenum1::member2"
		,"myenum1::member3"
		,0
	};
   static const char *without_pref[] = {
		 with_pref[0]+preflen
		,with_pref[1]+preflen
		,with_pref[2]+preflen
		,0
	};
   const char **names = (std::strchr(str, ':') != 0 ? with_pref : without_pref);
   for (std::size_t idx = 0; idx < 3; ++idx) {
      switch (idx) {
         case 0: if (0 == std::strcmp(names[0], str)) return myenum1::member1;
         case 1: if (0 == std::strcmp(names[1], str)) return myenum1::member2;
         case 2: if (0 == std::strcmp(names[2], str)) return myenum1::member3;
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
};

```
