
#ifndef _enums_gen_hpp
#define _enums_gen_hpp

#include <boost/preprocessor.hpp>

#include <cstdint>
#include <cstring>
#include <cassert>

/****************************************************************************/

template<typename T>
T enum_cast(const char *);

#define DECLARE_ENUM_MEMBERS(unused, idx, seq) \
	BOOST_PP_SEQ_ELEM(idx, seq) \
		BOOST_PP_COMMA_IF( \
			BOOST_PP_LESS(idx, \
				BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(seq), 1) \
			) \
		)

#define DECLARE_ENUM_WRITE_CASES(unused, idx, tuple) \
	case BOOST_PP_TUPLE_ELEM(2, 0, tuple)::BOOST_PP_SEQ_ELEM( \
			idx, \
			BOOST_PP_TUPLE_ELEM(2, 1, tuple) \
		): return BOOST_PP_STRINGIZE( \
				BOOST_PP_TUPLE_ELEM(2, 0, tuple)::BOOST_PP_SEQ_ELEM( \
					idx, \
					BOOST_PP_TUPLE_ELEM(2, 1, tuple) \
				) \
			);

#define DECLARE_ENUM_WRITE_CASES2(unused, idx, tuple) \
	case idx: if ( 0 == strcmp(str, \
			BOOST_PP_STRINGIZE( \
				BOOST_PP_TUPLE_ELEM(2, 0, tuple)::BOOST_PP_SEQ_ELEM( \
					idx, \
					BOOST_PP_TUPLE_ELEM(2, 1, tuple) \
				) \
			)) ) return \
		BOOST_PP_TUPLE_ELEM(2, 0, tuple)::BOOST_PP_SEQ_ELEM( \
			idx, \
			BOOST_PP_TUPLE_ELEM(2, 1, tuple) \
		);

/****************************************************************************/

#define DECLARE_ENUM_CLASS(name, type, seq) \
	enum class name : type { \
		BOOST_PP_REPEAT( \
			BOOST_PP_SEQ_SIZE(seq), \
			DECLARE_ENUM_MEMBERS, \
			seq \
		) \
	}; \
	\
	const char *enum_cast(const name &e) { \
		switch ( e ) { \
			BOOST_PP_REPEAT( \
				BOOST_PP_SEQ_SIZE(seq), \
				DECLARE_ENUM_WRITE_CASES, \
				(name, seq) \
			) \
		} \
		return BOOST_PP_STRINGIZE(name::unknown); \
	} \
	\
	template<> \
	name enum_cast<name>(const char *str) { \
		for ( std::size_t idx = 0; idx < BOOST_PP_SEQ_SIZE(seq); ++idx ) { \
			switch ( idx ) { \
				BOOST_PP_REPEAT( \
					BOOST_PP_SEQ_SIZE(seq), \
					DECLARE_ENUM_WRITE_CASES2, \
					(name, seq) \
				) \
			} \
		} \
	} \
	\
	std::ostream& operator<< (std::ostream &os, const name &e) { \
		return (os << enum_cast(e)); \
	}

#define DECLARE_ENUM_CLASS_NS(ns, name, type, seq) \
	namespace ns { \
		enum class name : type { \
			BOOST_PP_REPEAT( \
				BOOST_PP_SEQ_SIZE(seq), \
				DECLARE_ENUM_MEMBERS, \
				seq \
			) \
		}; \
		\
		const char *enum_cast(const name &e) { \
			switch ( e ) { \
				BOOST_PP_REPEAT( \
					BOOST_PP_SEQ_SIZE(seq), \
					DECLARE_ENUM_WRITE_CASES, \
					(name, seq) \
				) \
			} \
			return BOOST_PP_STRINGIZE(name::unknown); \
		} \
		\
		template<> \
		name enum_cast<name>(const char *str) { \
			for ( std::size_t idx = 0; idx < BOOST_PP_SEQ_SIZE(seq); ++idx ) { \
				switch ( idx ) { \
					BOOST_PP_REPEAT( \
						BOOST_PP_SEQ_SIZE(seq), \
						DECLARE_ENUM_WRITE_CASES2, \
						(name, seq) \
					) \
				} \
			} \
		} \
		\
		std::ostream& operator<< (std::ostream &os, const name &e) { \
			return (os << enum_cast(e)); \
		} \
	}

/****************************************************************************/

#define DECLARE_ENUM(name, seq) \
	enum name { \
		BOOST_PP_REPEAT( \
			BOOST_PP_SEQ_SIZE(seq), \
			DECLARE_ENUM_MEMBERS, \
			seq \
		) \
	}; \
	\
	const char *enum_cast(const name &e) { \
		switch ( e ) { \
			BOOST_PP_REPEAT( \
				BOOST_PP_SEQ_SIZE(seq), \
				DECLARE_ENUM_WRITE_CASES, \
				(name, seq) \
			) \
		} \
		return BOOST_PP_STRINGIZE(name::unknown); \
	} \
	\
	template<> \
	name enum_cast<name>(const char *str) { \
		for ( std::size_t idx = 0; idx < BOOST_PP_SEQ_SIZE(seq); ++idx ) { \
			switch ( idx ) { \
				BOOST_PP_REPEAT( \
					BOOST_PP_SEQ_SIZE(seq), \
					DECLARE_ENUM_WRITE_CASES2, \
					(name, seq) \
				) \
			} \
		} \
	} \
	\
	std::ostream& operator<< (std::ostream &os, const name &e) { \
		return (os << enum_cast(e)); \
	}

#define DECLARE_ENUM_NS(ns, name, seq) \
	namespace ns { \
		enum name { \
			BOOST_PP_REPEAT( \
				BOOST_PP_SEQ_SIZE(seq), \
				DECLARE_ENUM_MEMBERS, \
				seq \
			) \
		}; \
		\
		const char *enum_cast(const name &e) { \
			switch ( e ) { \
				BOOST_PP_REPEAT( \
					BOOST_PP_SEQ_SIZE(seq), \
					DECLARE_ENUM_WRITE_CASES, \
					(name, seq) \
				) \
			} \
			return BOOST_PP_STRINGIZE(name::unknown); \
		} \
		\
		template<> \
		name enum_cast<name>(const char *str) { \
			for ( std::size_t idx = 0; idx < BOOST_PP_SEQ_SIZE(seq); ++idx ) { \
				switch ( idx ) { \
					BOOST_PP_REPEAT( \
						BOOST_PP_SEQ_SIZE(seq), \
						DECLARE_ENUM_WRITE_CASES2, \
						(name, seq) \
					) \
				} \
			} \
		} \
		\
		std::ostream& operator<< (std::ostream &os, const name &e) { \
			return (os << enum_cast(e)); \
		} \
	}

/****************************************************************************/

#endif // _enums_gen_hpp
