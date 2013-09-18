enum-gen
========

'enum's and C++11 'enum class'es preprocessor generator

### "Example"

For this macro record:
```cpp
DECLARE_ENUM_CLASS(
   myenum1, std::uint8_t,
   (member1)
   (member2)
   (member3)
);
```

will be generated this code:
```cpp
template<typename T>
T enum_cast(const char *);

enum class myenum1 : std::uint8_t {
	 member1
	,member2
	,member3
};

const char *enum_cast(const myenum1 &e) {
	switch ( e ) {
		case myenum1::member1:
			return "myenum1::member1";
		case myenum1::member2:
			return "myenum1::member2";
		case myenum1::member3:
			return "myenum1::member3";
	}
	
	return "myenum1::unknown";
}

template<>
myenum1 enum_cast<myenum1>(const char *str) {
	for ( std::size_t idx = 0; idx < 3; ++idx ) {
		switch ( idx ) {
			case 0:
				if ( 0 == strcmp(str, "myenum1::member1") )
					return myenum1::member1;
			case 1:
				if ( 0 == strcmp(str, "myenum1::member2") ) 
					return myenum1::member2;
			case 2:
				if ( 0 == strcmp(str, "myenum1::member3") )
					return myenum1::member3;
		}
	}
}

std::ostream& operator<< (std::ostream &os, const myenum1 &e) {
	return (os << enum_cast(e));
}
```
