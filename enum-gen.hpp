
#ifndef _enum_gen__enum_gen_hpp
#define _enum_gen__enum_gen_hpp

#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>

#include <cstdint>
#include <cstring>
#include <cassert>

/****************************************************************************/

#define ENUM_GEN_WRAP_SEQUENCE_X(...) \
	((__VA_ARGS__)) ENUM_GEN_WRAP_SEQUENCE_Y
#define ENUM_GEN_WRAP_SEQUENCE_Y(...) \
	((__VA_ARGS__)) ENUM_GEN_WRAP_SEQUENCE_X

#define ENUM_GEN_WRAP_SEQUENCE_X0
#define ENUM_GEN_WRAP_SEQUENCE_Y0

/****************************************************************************/

#define ENUM_GEN_DECLARE_ENUM_OPERATORS_IMPL(unused, data, elem) \
	inline constexpr BOOST_PP_TUPLE_ELEM(0, data) operator elem ( \
		 const BOOST_PP_TUPLE_ELEM(0, data) &l \
		,const BOOST_PP_TUPLE_ELEM(0, data) &r \
	) { \
		return static_cast<BOOST_PP_TUPLE_ELEM(0, data)> \
		( \
			static_cast<BOOST_PP_TUPLE_ELEM(1, data)>(l) \
			elem \
			static_cast<BOOST_PP_TUPLE_ELEM(1, data)>(r) \
		); \
	}

#define ENUM_GEN_DECLARE_ENUM_OPERATORS(name, type, seq) \
	BOOST_PP_SEQ_FOR_EACH( \
		 ENUM_GEN_DECLARE_ENUM_OPERATORS_IMPL \
		,(name, type) \
		,seq \
	)

/****************************************************************************/

#define ENUM_GEN_ADAPT_ENUM_GENERATE_CASES2(unused, data, idx, elem) \
	case idx: if ( 0 == std::strcmp(enum_info<data>::values[idx].name+offset, str) ) return data::BOOST_PP_TUPLE_ELEM(0, elem);

#define ENUM_GEN_ADAPT_ENUM_GENERATE_CASES(unused, data, idx, elem) \
	case data::BOOST_PP_TUPLE_ELEM(0, elem): \
		return enum_info<data>::values[idx].name+offset \
	;

#define ENUM_GEN_ADAPT_ENUM_GENERATE_VALUES(unused, data, idx, elem) \
	{   BOOST_PP_STRINGIZE(data::BOOST_PP_TUPLE_ELEM(0, elem)) \
		,data::BOOST_PP_TUPLE_ELEM(0, elem) \
		,static_cast<enum_info<data>::underlying_type>(data::BOOST_PP_TUPLE_ELEM(0, elem)) \
	},

#define ENUM_GEN_ADAPT_ENUM_IMPL(name_, type_, seq) \
	template<typename> \
	struct enum_info; \
	\
	template<> \
	struct enum_info<name_> { \
		using underlying_type = std::underlying_type<name_>::type; \
		static const char *names[]; \
		struct value_type { \
			const char *name; \
			const name_ value; \
			const underlying_type ivalue; \
		}; \
		static const value_type values[]; \
	}; \
	const \
	enum_info<name_>::value_type \
	enum_info<name_>::values[] = { \
		BOOST_PP_SEQ_FOR_EACH_I( \
			 ENUM_GEN_ADAPT_ENUM_GENERATE_VALUES \
			,name_ \
			,seq \
		) \
	}; \
	inline const char *enum_cast(const name_ &e, const bool flag = true) { \
		const std::size_t offset = (true == flag ? 0 : sizeof(BOOST_PP_STRINGIZE(name_::))-1); \
		switch ( e ) { \
			BOOST_PP_SEQ_FOR_EACH_I( \
				 ENUM_GEN_ADAPT_ENUM_GENERATE_CASES \
				,name_ \
				,seq \
			) \
		} \
		assert("bad enum value #1" == 0); \
	} \
	\
	template<typename E> \
	E enum_cast(const char *); \
	\
	template<> \
	name_ enum_cast<name_>(const char *str) { \
		const std::size_t offset = (0 != std::strchr(str, ':') ? 0 : sizeof(BOOST_PP_STRINGIZE(name_::))-1); \
		for ( std::size_t idx = 0; idx < BOOST_PP_SEQ_SIZE(seq); ++idx ) { \
			switch ( idx ) { \
				BOOST_PP_SEQ_FOR_EACH_I( \
					 ENUM_GEN_ADAPT_ENUM_GENERATE_CASES2 \
					,name_ \
					,seq \
				) \
			} \
		} \
		assert("bad enum value #2" == 0); \
	} \
	\
	std::ostream& operator<< (std::ostream &os, const name_ &e) { \
		return (os << enum_cast(e)); \
	}


#define ENUM_GEN_ADAPT_ENUM(name, type, seq) \
	ENUM_GEN_ADAPT_ENUM_IMPL( \
		 name \
		,type \
		,BOOST_PP_CAT(ENUM_GEN_WRAP_SEQUENCE_X seq, 0) \
	)

/****************************************************************************/

#define ENUM_GEN_DECLARE_ENUM_MEMBERS(unused, data, idx, elem) \
	BOOST_PP_COMMA_IF(idx) BOOST_PP_IF( \
		 BOOST_PP_EQUAL(2, BOOST_PP_TUPLE_SIZE(elem)) \
		,BOOST_PP_TUPLE_ELEM(0, elem)=BOOST_PP_TUPLE_ELEM(1, elem) /* member = value */ \
		,BOOST_PP_TUPLE_ELEM(0, elem) /* member */ \
	)

#define ENUM_GEN_DECLARE_ENUM_IMPL(name, type, seq) \
	enum class name : type { \
	BOOST_PP_SEQ_FOR_EACH_I( \
			 ENUM_GEN_DECLARE_ENUM_MEMBERS \
			,~ \
			,seq \
		) \
	}; \
	ENUM_GEN_ADAPT_ENUM_IMPL(name, type, seq)

#define ENUM_GEN_DECLARE_ENUM(name, type, seq) \
	ENUM_GEN_DECLARE_ENUM_IMPL( \
		 name \
		,type \
		,BOOST_PP_CAT(ENUM_GEN_WRAP_SEQUENCE_X seq, 0) \
	)

/****************************************************************************/

#endif // _enum_gen__enum_gen_hpp
