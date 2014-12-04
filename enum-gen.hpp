
#ifndef _enum_gen__enum_gen_hpp
#define _enum_gen__enum_gen_hpp

#include <boost/preprocessor.hpp>

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

#define ENUM_GEN_DECLARE_ENUM_MEMBERS(unused, data, idx, elem) \
	BOOST_PP_COMMA_IF(idx) BOOST_PP_IF( \
		 BOOST_PP_EQUAL(2, BOOST_PP_TUPLE_SIZE(elem)) \
		,BOOST_PP_TUPLE_ELEM(0, elem)=BOOST_PP_TUPLE_ELEM(1, elem) /* member = value */ \
		,BOOST_PP_TUPLE_ELEM(0, elem) /* member */ \
	)

#define ENUM_GEN_DECLARE_ENUM_WRITE_CASES(unused, data, idx, elem) \
	case BOOST_PP_TUPLE_ELEM(0, data)::BOOST_PP_TUPLE_ELEM(0, elem): \
		return BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(0, data)::BOOST_PP_TUPLE_ELEM(0, elem)) \
	;

#define ENUM_GEN_DECLARE_ENUM_WRITE_CASES2(unused, data, idx, elem) \
	case idx: if ( 0 == std::strcmp(names[idx], str) ) return data::BOOST_PP_TUPLE_ELEM(0, elem);

/****************************************************************************/

#define ENUM_GEN_DECLARE_ENUM_MEMBERS_NAMES_AUX(unused, data, idx, elem) \
	BOOST_PP_STRINGIZE(data::BOOST_PP_TUPLE_ELEM(0, elem)),

#define ENUM_GEN_DECLARE_ENUM_MEMBERS_NAMES_AUX2(unused, data, idx, elem) \
	with_pref[idx]+preflen,

#define ENUM_GEN_DECLARE_ENUM_MEMBERS_NAMES(name, seq) \
	static const char *with_pref[] = { \
	BOOST_PP_SEQ_FOR_EACH_I( \
			 ENUM_GEN_DECLARE_ENUM_MEMBERS_NAMES_AUX \
			,name \
			,seq \
		) \
		0 \
	}; \
	static const char *without_pref[] = { \
	BOOST_PP_SEQ_FOR_EACH_I( \
			 ENUM_GEN_DECLARE_ENUM_MEMBERS_NAMES_AUX2 \
			,name\
			,seq \
		) \
		0 \
	};

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

#define ENUM_GEN_DECLARE_ENUM_IMPL(name, type, seq) \
	enum class name : type { \
	BOOST_PP_SEQ_FOR_EACH_I( \
			 ENUM_GEN_DECLARE_ENUM_MEMBERS \
			,~ \
			,seq \
		) \
	}; \
	\
	inline const char *enum_cast(const name &e) { \
		switch ( e ) { \
			BOOST_PP_SEQ_FOR_EACH_I( \
				 ENUM_GEN_DECLARE_ENUM_WRITE_CASES \
				,(name, seq) \
				,seq \
			) \
		} \
		return BOOST_PP_STRINGIZE(name::unknown); \
	} \
	\
	template<typename E> \
	E enum_cast(const char *); \
	\
	template<> \
	name enum_cast<name>(const char *str) { \
		static const std::size_t preflen = sizeof(BOOST_PP_STRINGIZE(name::))-1; \
		ENUM_GEN_DECLARE_ENUM_MEMBERS_NAMES(name, seq) \
		\
		const char **names = (std::strchr(str, ':') != 0 ? with_pref : without_pref); \
		for ( std::size_t idx = 0; idx < BOOST_PP_SEQ_SIZE(seq); ++idx ) { \
			switch ( idx ) { \
				BOOST_PP_SEQ_FOR_EACH_I( \
					 ENUM_GEN_DECLARE_ENUM_WRITE_CASES2 \
					,name\
					,seq \
				) \
			} \
		} \
		assert("bad enum value" == 0); \
	} \
	\
	std::ostream& operator<< (std::ostream &os, const name &e) { \
		return (os << enum_cast(e)); \
	} \
	\
	ENUM_GEN_DECLARE_ENUM_OPERATORS(name, type, (&)(|)(^))

#define ENUM_GEN_DECLARE_ENUM(name, type, seq) \
	ENUM_GEN_DECLARE_ENUM_IMPL( \
		 name \
		,type \
		,BOOST_PP_CAT(ENUM_GEN_WRAP_SEQUENCE_X seq, 0) \
	)

#define ENUM_GEN_DECLARE_ENUM_NS(ns, name, type, seq) \
	namespace ns { \
		ENUM_GEN_DECLARE_ENUM(name, type, seq) \
	}

/****************************************************************************/

#endif // _enum_gen__enum_gen_hpp
