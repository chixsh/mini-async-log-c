#ifndef __MALC_PRIVATE_H__
#define __MALC_PRIVATE_H__

#if !defined (__MALC_H__)
  #error "This file should be included through malc.h"
#endif

#include <bl/base/integer.h>
#include <bl/base/integer_manipulation.h>
#include <bl/base/error.h>
#include <bl/base/preprocessor.h>
#include <bl/base/utility.h>

#include <malc/libexport.h>
/*----------------------------------------------------------------------------*/
#ifdef __cplusplus
  extern "C" {
#endif
/*----------------------------------------------------------------------------*/
typedef enum malc_encodings {
  malc_end          = 0,
  malc_type_float   = 'a',
  malc_type_double  = 'b',
  malc_type_i8      = 'c',
  malc_type_u8      = 'd',
  malc_type_i16     = 'e',
  malc_type_u16     = 'f',
  malc_type_i32     = 'g',
  malc_type_u32     = 'h',
  malc_type_i64     = 'i',
  malc_type_u64     = 'j',
  malc_type_vptr    = 'k',
  malc_type_lit     = 'l',
  malc_type_str     = 'm',
  malc_type_bytes   = 'n',
  malc_type_error   = 'o',
  malc_sev_debug    = '3',
  malc_sev_trace    = '4',
  malc_sev_note     = '5',
  malc_sev_warning  = '6',
  malc_sev_error    = '7',
  malc_sev_critical = '8',
  malc_sev_off      = '9',
}
malc_type_ids;
/*----------------------------------------------------------------------------*/
typedef struct malc_lit {
  char const* lit;
}
malc_lit;
/*----------------------------------------------------------------------------*/
typedef struct malc_mem {
  u8 const* mem;
  u16       size;
}
malc_mem;
/*----------------------------------------------------------------------------*/
typedef struct malc_str {
  char const* str;
  u16         len;
}
malc_str;
/*----------------------------------------------------------------------------*/
typedef struct malc_const_entry {
  char const* format;
  char const* info;
  u16         compressed_count;
}
malc_const_entry;
/*----------------------------------------------------------------------------*/
struct malc;
/*----------------------------------------------------------------------------*/
extern MALC_EXPORT uword malc_get_min_severity (struct malc const* l);
/*----------------------------------------------------------------------------*/
extern MALC_EXPORT bl_err malc_log(
  struct malc*            l,
  malc_const_entry const* e,
  uword                   va_min_size,
  uword                   va_max_size,
  int                     argc,
  ...
  );
/*----------------------------------------------------------------------------*/
#define malc_is_compressed(x) \
  ((int) (malc_get_type_code ((x)) >= malc_type_i32 && \
    malc_get_type_code ((x)) <= malc_type_u64))
/*----------------------------------------------------------------------------*/
#ifndef __cplusplus

#define malc_tgen_cv_cases(type, expression)\
  type:                (expression),\
  const type:          (expression),\
  volatile type:       (expression),\
  const volatile type: (expression)

#define malc_get_type_code(expression)\
  _Generic ((expression),\
    malc_tgen_cv_cases (float,       (char) malc_type_float),\
    malc_tgen_cv_cases (double,      (char) malc_type_double),\
    malc_tgen_cv_cases (i8,          (char) malc_type_i8),\
    malc_tgen_cv_cases (u8,          (char) malc_type_u8),\
    malc_tgen_cv_cases (i16,         (char) malc_type_i16),\
    malc_tgen_cv_cases (u16,         (char) malc_type_u16),\
    malc_tgen_cv_cases (i32,         (char) malc_type_i32),\
    malc_tgen_cv_cases (u32,         (char) malc_type_u32),\
    malc_tgen_cv_cases (i64,         (char) malc_type_i64),\
    malc_tgen_cv_cases (u64,         (char) malc_type_u64),\
    malc_tgen_cv_cases (void*,       (char) malc_type_vptr),\
    malc_tgen_cv_cases (void* const, (char) malc_type_vptr),\
    malc_lit:                        (char) malc_type_lit,\
    malc_str:                        (char) malc_type_str,\
    malc_mem:                        (char) malc_type_bytes,\
    default:                         (char) malc_type_error\
    )
#define malc_get_type_min_size(value)\
  _Generic ((value),\
    malc_tgen_cv_cases (float,       (uword) sizeof (float)),\
    malc_tgen_cv_cases (double,      (uword) sizeof (double)),\
    malc_tgen_cv_cases (i8,          (uword) sizeof (i8)),\
    malc_tgen_cv_cases (u8,          (uword) sizeof (u8)),\
    malc_tgen_cv_cases (i16,         (uword) sizeof (i16)),\
    malc_tgen_cv_cases (u16,         (uword) sizeof (u16)),\
    malc_tgen_cv_cases (i32,         (uword) 1),\
    malc_tgen_cv_cases (u32,         (uword) 1),\
    malc_tgen_cv_cases (i64,         (uword) 1),\
    malc_tgen_cv_cases (u64,         (uword) 1),\
    malc_tgen_cv_cases (void*,       (uword) sizeof (void*)),\
    malc_tgen_cv_cases (void* const, (uword) sizeof (void*)),\
    malc_lit:                        (uword) sizeof_member (malc_lit, lit),\
    malc_str:                        (uword) sizeof_member (malc_str, len),\
    malc_mem:                        (uword) sizeof_member (malc_mem, size),\
    default:                         (uword) 0\
    )
#define malc_get_type_max_size(value)\
  _Generic ((value),\
    malc_tgen_cv_cases (float,       (uword) sizeof (float)),\
    malc_tgen_cv_cases (double,      (uword) sizeof (double)),\
    malc_tgen_cv_cases (i8,          (uword) sizeof (i8)),\
    malc_tgen_cv_cases (u8,          (uword) sizeof (u8)),\
    malc_tgen_cv_cases (i16,         (uword) sizeof (i16)),\
    malc_tgen_cv_cases (u16,         (uword) sizeof (u16)),\
    malc_tgen_cv_cases (i32,         (uword) sizeof (i32)),\
    malc_tgen_cv_cases (u32,         (uword) sizeof (u32)),\
    malc_tgen_cv_cases (i64,         (uword) sizeof (i64)),\
    malc_tgen_cv_cases (u64,         (uword) sizeof (u64)),\
    malc_tgen_cv_cases (void*,       (uword) sizeof (void*)),\
    malc_tgen_cv_cases (void* const, (uword) sizeof (void*)),\
    malc_lit:                        (uword) sizeof_member (malc_lit, lit),\
    malc_str:\
      (uword) sizeof_member (malc_str, len) +\
      u_bit (sizeof_member (malc_str, len) * 8) - 1,\
    malc_mem:\
      (uword) sizeof_member (malc_mem, size) +\
      u_bit (sizeof_member (malc_mem, size) * 8) - 1,\
    default:                         (uword) 0\
    )
/*----------------------------------------------------------------------------*/
#else

template<typename T> struct malc_type_traits {};

template<> struct malc_type_traits<float> {
  static const char  code = malc_type_float;
  static const uword min  = sizeof (float);
  static const uword max  = min;
};
template<> struct malc_type_traits<double> {
  static const char  code = malc_type_double;
  static const uword min  = sizeof (double);
  static const uword max  = min;
};
template<> struct malc_type_traits<i8> {
  static const char  code = malc_type_i8;
  static const uword min  = sizeof (i8);
  static const uword max  = min;
};
template<> struct malc_type_traits<u8> {
  static const char  code = malc_type_u8;
  static const uword min  = sizeof (u8);
  static const uword max  = min;
};
template<> struct malc_type_traits<i16> {
  static const char  code = malc_type_i16;
  static const uword min  = sizeof (i16);
  static const uword max  = min;
};
template<> struct malc_type_traits<u16> {
  static const char  code = malc_type_u16;
  static const uword min  = sizeof (u16);
  static const uword max  = min;
};
template<> struct malc_type_traits<i32> {
  static const char  code = malc_type_i32;
  static const uword min  = 1;
  static const uword max  = sizeof (i32);
};
template<> struct malc_type_traits<u32> {
  static const char  code = malc_type_u32;
  static const uword min  = 1;
  static const uword max  = sizeof (u32);
};
template<> struct malc_type_traits<i64> {
  static const char  code = malc_type_i64;
  static const uword min  = 1;
  static const uword max  = sizeof (i64);
};
template<> struct malc_type_traits<u64> {
  static const char  code = malc_type_u64;
  static const uword min  = 1;
  static const uword max  = sizeof (u64);
};
template<> struct malc_type_traits<void*> {
  static const char  code = malc_type_vptr;
  static const uword min  = sizeof (void*);
  static const uword max  = min;
};
template<> struct malc_type_traits<const void*> :
  public malc_type_traits<void*> {};

template<> struct malc_type_traits<volatile void*> :
  public malc_type_traits<void*> {};

template<> struct malc_type_traits<const volatile void*> :
  public malc_type_traits<void*> {};

template<> struct malc_type_traits<void* const> :
  public malc_type_traits<void*> {};

template<> struct malc_type_traits<const void* const> :
  public malc_type_traits<void*> {};

template<> struct malc_type_traits<volatile void* const> :
  public malc_type_traits<void*> {};

template<> struct malc_type_traits<const volatile void* const> :
  public malc_type_traits<void*> {};

template<> struct malc_type_traits<malc_lit> {
  static const char  code = malc_type_lit;
  static const uword min  = sizeof (void*);
  static const uword max  = min;
};
template<> struct malc_type_traits<malc_str> {
  static const char code  = malc_type_str;
  static const uword min  = sizeof (u16);
  static const uword max  = sizeof (u16) + utype_max (u16);
};
template<> struct malc_type_traits<malc_mem> {
  static const char  code = malc_type_bytes;
  static const uword min  = sizeof (u16);
  static const uword max  = sizeof (u16) + utype_max (u16);
};

#include <type_traits>

#define malc_get_type_code(value)\
  malc_type_traits< \
    typename std::remove_cv< \
      typename std::remove_reference< \
        decltype (value) \
        >::type \
      >::type \
    >::code

#define malc_get_type_min_size(value)\
  malc_type_traits< \
    typename std::remove_cv< \
      typename std::remove_reference< \
        decltype (value) \
        >::type \
      >::type \
    >::min

#define malc_get_type_max_size(value)\
  malc_type_traits< \
    typename std::remove_cv< \
      typename std::remove_reference< \
        decltype (value) \
        >::type \
      >::type \
    >::max

#endif /* __cplusplus*/
/*----------------------------------------------------------------------------*/
/* used for testing, ignore */
#ifndef MALC_GET_MIN_SEVERITY_FNAME
  #define MALC_GET_MIN_SEVERITY_FNAME malc_get_min_severity
#endif
#ifndef MALC_LOG_FNAME
  #define MALC_LOG_FNAME malc_log
#endif
/*----------------------------------------------------------------------------*/
#define MALC_LOG_CREATE_CONST_ENTRY(sev, ...) \
  static const char pp_tokconcat(malc_const_info_, __LINE__)[] = { \
    (char) (sev), \
    /* this block builds the "info" string (the conditional is to skip*/ \
    /* the comma when empty */ \
    pp_if (pp_has_vargs (pp_vargs_ignore_first (__VA_ARGS__)))( \
      pp_apply( \
        malc_get_type_code, pp_comma, pp_vargs_ignore_first (__VA_ARGS__) \
        ) \
      pp_comma() \
    ) /* endif */ \
    (char) malc_end \
  }; \
  static const malc_const_entry pp_tokconcat(malc_const_entry_, __LINE__) = { \
    /* "" is prefixed to forbid compilation of non-literal format strings*/ \
    "" pp_vargs_first (__VA_ARGS__), \
    pp_tokconcat(malc_const_info_, __LINE__), \
    /* this block builds the compressed field count (0 if no vargs) */ \
    pp_if_else (pp_has_vargs (pp_vargs_ignore_first (__VA_ARGS__)))( \
      pp_apply( \
        malc_is_compressed, pp_plus, pp_vargs_ignore_first (__VA_ARGS__) \
        ) \
    ,/* else */ \
      0 \
    )/* endif */\
  }
/*----------------------------------------------------------------------------*/
#define MALC_LOG_PRIVATE_IMPL(err, malc_ptr, sev, ...) \
  MALC_LOG_CREATE_CONST_ENTRY ((sev), __VA_ARGS__); \
  (err) = MALC_LOG_FNAME( \
    (malc_ptr), \
    &pp_tokconcat (malc_const_entry_, __LINE__), \
    /* min_size (0 if no args) */ \
    pp_if_else (pp_has_vargs (pp_vargs_ignore_first (__VA_ARGS__)))( \
      pp_apply( \
        malc_get_type_min_size, pp_plus, pp_vargs_ignore_first (__VA_ARGS__) \
        ) \
    ,/* else */ \
      0 \
    ),/* endif */ \
    /* max_size (0 if no args) */ \
    pp_if_else (pp_has_vargs (pp_vargs_ignore_first (__VA_ARGS__)))( \
      pp_apply( \
        malc_get_type_max_size, pp_plus, pp_vargs_ignore_first (__VA_ARGS__) \
        ) \
    ,/* else */ \
      0 \
    ),/* endif */ \
    /* arg count */ \
    pp_vargs_count (pp_vargs_ignore_first (__VA_ARGS__)) \
    /* vargs (conditional to skip the trailing comma when ther are no vargs */ \
    pp_if (pp_has_vargs (pp_vargs_ignore_first (__VA_ARGS__)))( \
      pp_comma() \
        pp_apply( \
          pp_pass, pp_comma, pp_vargs_ignore_first (__VA_ARGS__) \
          ) \
      ) /* endif */ \
    )
/*----------------------------------------------------------------------------*/
#define MALC_LOG_IF_PRIVATE(condition, err, malc_ptr, sev, ...) \
  do { \
    if ((condition) && ((sev) >= MALC_GET_MIN_SEVERITY_FNAME ((malc_ptr)))) { \
      MALC_LOG_PRIVATE_IMPL ((err), (malc_ptr), (sev), __VA_ARGS__); \
    } \
    else { \
      (err) = bl_ok; \
    } \
    --(err); ++(err); /*remove unused warnings */ \
  } \
  while (0)

#define MALC_LOG_PRIVATE(err, malc_ptr, sev, ...) \
  MALC_LOG_IF_PRIVATE (1, (err), (malc_ptr), (sev), __VA_ARGS__)
/*----------------------------------------------------------------------------*/
#if !defined (MALC_STRIP_LOG_FILELINE)
  #define MALC_TO_STR(s) #s
  #define MALC_CONCAT_FILELINE(file, line) "(" file ":" MALC_TO_STR (lin) ") "
  #define malc_fileline MALC_CONCAT_FILELINE (__FILE__, __LINE__)
#else
  #define malc_fileline
#endif
/*----------------------------------------------------------------------------*/
#if !defined (MALC_GET_LOGGER_INSTANCE_FUNCNAME)
    #define MALC_GET_LOGGER_INSTANCE_FUNC get_malc_logger_instance()
#else
    #define MALC_GET_LOGGER_INSTANCE_FUNC MALC_GET_LOGGER_INSTANCE_FUNCNAME()
#endif
/*----------------------------------------------------------------------------*/
#ifdef MALC_STRIP_LOG_DEBUG
  #ifndef MALC_STRIP_LOG_SEVERITY
    #define MALC_STRIP_LOG_SEVERITY 0
  #else
    #error "use either MALC_STRIP_LOG_SEVERITY or MALC_STRIP_LOG_DEBUG"
  #endif
#endif

#ifdef MALC_STRIP_LOG_TRACE
  #ifndef MALC_STRIP_LOG_SEVERITY
    #define MALC_STRIP_LOG_SEVERITY 1
  #else
    #error "use either MALC_STRIP_LOG_SEVERITY or MALC_STRIP_LOG_TRACE"
  #endif
#endif

#ifdef MALC_STRIP_LOG_NOTICE
  #ifndef MALC_STRIP_LOG_SEVERITY
    #define MALC_STRIP_LOG_SEVERITY 2
  #else
    #error "use either MALC_STRIP_LOG_SEVERITY or MALC_STRIP_LOG_NOTICE"
  #endif
#endif

#ifdef MALC_STRIP_LOG_WARNING
  #ifndef MALC_STRIP_LOG_SEVERITY
    #define MALC_STRIP_LOG_SEVERITY 3
  #else
    #error "use either MALC_STRIP_LOG_SEVERITY or MALC_STRIP_LOG_WARNING"
  #endif
#endif

#ifdef MALC_STRIP_LOG_ERROR
  #ifndef MALC_STRIP_LOG_SEVERITY
    #define MALC_STRIP_LOG_SEVERITY 4
  #else
    #error "use either MALC_STRIP_LOG_SEVERITY or MALC_STRIP_LOG_ERROR"
  #endif
#endif

#if defined (MALC_STRIP_LOG_CRITICAL) || defined (MALC_STRIP_ALL)
  #ifndef MALC_STRIP_LOG_SEVERITY
    #define MALC_STRIP_LOG_SEVERITY 5
  #else
    #error "use either MALC_STRIP_LOG_SEVERITY or MALC_STRIP_LOG_CRITICAL"
  #endif
#endif

#if defined (MALC_STRIP_LOG_SEVERITY) &&\
  MALC_STRIP_LOG_SEVERITY >= 0 &&\
  !defined (MALC_STRIP_LOG_DEBUG)
    #define MALC_STRIP_LOG_DEBUG
#endif

#if defined(MALC_STRIP_LOG_SEVERITY) &&\
  MALC_STRIP_LOG_SEVERITY >= 1 &&\
  !defined (MALC_STRIP_LOG_TRACE)
    #define MALC_STRIP_LOG_TRACE
#endif

#if defined(MALC_STRIP_LOG_SEVERITY) &&\
  MALC_STRIP_LOG_SEVERITY >= 2 &&\
  !defined (MALC_STRIP_LOG_NOTICE)
    #define MALC_STRIP_LOG_NOTICE
#endif

#if defined(MALC_STRIP_LOG_SEVERITY) &&\
  MALC_STRIP_LOG_SEVERITY >= 3 &&\
  !defined (MALC_STRIP_LOG_WARNING)
    #define MALC_STRIP_LOG_WARNING
#endif

#if defined(MALC_STRIP_LOG_SEVERITY) &&\
  MALC_STRIP_LOG_SEVERITY >= 4 &&\
  !defined (MALC_STRIP_LOG_ERROR)
    #define MALC_STRIP_LOG_ERROR
#endif

#if defined(MALC_STRIP_LOG_SEVERITY) &&\
  MALC_STRIP_LOG_SEVERITY >= 5 &&\
  !defined (MALC_STRIP_LOG_CRITICAL)
    #define MALC_STRIP_LOG_CRITICAL
#endif
/*----------------------------------------------------------------------------*/
static inline bl_err malc_warning_silencer() { return bl_ok; }
/*----------------------------------------------------------------------------*/
#ifndef MALC_STRIP_LOG_DEBUG

#define malc_debug(err, ...)\
  MALC_LOG_PRIVATE( \
    (err), MALC_GET_LOGGER_INSTANCE_FUNC, malc_sev_debug, __VA_ARGS__ \
    )

#define malc_debug_if(err, condition, ...)\
  MALC_LOG_IF_PRIVATE(\
    (err), \
    MALC_GET_LOGGER_INSTANCE_FUNC, \
    (condition), \
    malc_sev_debug, \
    __VA_ARGS__\
    )

#define malc_debug_i(err, malc_ptr, ...)\
  MALC_LOG_PRIVATE ((err), (malc_ptr), malc_sev_debug, __VA_ARGS__)

#define malc_debug_i_if(err, malc_ptr, condition, ...)\
  MALC_LOG_IF_PRIVATE(\
    (err), (malc_ptr), (condition), malc_sev_debug, __VA_ARGS__\
    )

#else

#define malc_debug(...)      malc_warning_silencer()
#define malc_debug_if(...)   malc_warning_silencer()
#define malc_debug_i(...)    malc_warning_silencer()
#define malc_debug_i_if(...) malc_warning_silencer()

#endif

/*----------------------------------------------------------------------------*/
#ifndef MALC_STRIP_LOG_TRACE

#define malc_trace(err, ...)\
  MALC_LOG_PRIVATE( \
    (err), MALC_GET_LOGGER_INSTANCE_FUNC, malc_sev_trace, __VA_ARGS__ \
    )

#define malc_trace_if(err, condition, ...)\
  MALC_LOG_IF_PRIVATE(\
    (err), \
    MALC_GET_LOGGER_INSTANCE_FUNC, \
    (condition), \
    malc_sev_trace, \
    __VA_ARGS__\
    )

#define malc_trace_i(err, malc_ptr, ...)\
  MALC_LOG_PRIVATE ((err), (malc_ptr), malc_sev_trace, __VA_ARGS__)

#define malc_trace_i_if(err, malc_ptr, condition, ...)\
  MALC_LOG_IF_PRIVATE(\
    (err), (malc_ptr), (condition), malc_sev_trace, __VA_ARGS__\
    )

#else

#define malc_trace(...)      malc_warning_silencer()
#define malc_trace_if(...)   malc_warning_silencer()
#define malc_trace_i(...)    malc_warning_silencer()
#define malc_trace_i_if(...) malc_warning_silencer()

#endif

/*----------------------------------------------------------------------------*/
#ifndef MALC_STRIP_LOG_NOTICE

#define malc_notice(err, ...)\
  MALC_LOG_PRIVATE( \
    (err), MALC_GET_LOGGER_INSTANCE_FUNC, malc_sev_notice, __VA_ARGS__ \
    )

#define malc_notice_if(err, condition, ...)\
  MALC_LOG_IF_PRIVATE(\
    (err), \
    MALC_GET_LOGGER_INSTANCE_FUNC, \
    (condition), \
    malc_sev_notice, \
    __VA_ARGS__\
    )

#define malc_notice_i(err, malc_ptr, ...)\
  MALC_LOG_PRIVATE ((err), (malc_ptr), malc_sev_notice, __VA_ARGS__)

#define malc_notice_i_if(err, malc_ptr, condition, ...)\
  MALC_LOG_IF_PRIVATE(\
    (err), (malc_ptr), (condition), malc_sev_notice, __VA_ARGS__\
    )

#else

#define malc_notice(...)      malc_warning_silencer()
#define malc_notice_if(...)   malc_warning_silencer()
#define malc_notice_i(...)    malc_warning_silencer()
#define malc_notice_i_if(...) malc_warning_silencer()

#endif

/*----------------------------------------------------------------------------*/
#ifndef MALC_STRIP_LOG_WARNING

#define malc_warning(err, ...)\
  MALC_LOG_PRIVATE( \
    (err), MALC_GET_LOGGER_INSTANCE_FUNC, malc_sev_warning, __VA_ARGS__ \
    )

#define malc_warning_if(err, condition, ...)\
  MALC_LOG_IF_PRIVATE(\
    (err), \
    MALC_GET_LOGGER_INSTANCE_FUNC, \
    (condition), \
    malc_sev_warning, \
    __VA_ARGS__\
    )

#define malc_warning_i(err, malc_ptr, ...)\
  MALC_LOG_PRIVATE ((err), (malc_ptr), malc_sev_warning, __VA_ARGS__)

#define malc_warning_i_if(err, malc_ptr, condition, ...)\
  MALC_LOG_IF_PRIVATE(\
    (err), (malc_ptr), (condition), malc_sev_warning, __VA_ARGS__\
    )

#else

#define malc_warning(...)      malc_warning_silencer()
#define malc_warning_if(...)   malc_warning_silencer()
#define malc_warning_i(...)    malc_warning_silencer()
#define malc_warning_i_if(...) malc_warning_silencer()

#endif

/*----------------------------------------------------------------------------*/
#ifndef MALC_STRIP_LOG_ERROR

#define malc_error(err, ...)\
  MALC_LOG_PRIVATE( \
    (err), MALC_GET_LOGGER_INSTANCE_FUNC, malc_sev_error, __VA_ARGS__ \
    )

#define malc_error_if(err, condition, ...)\
  MALC_LOG_IF_PRIVATE(\
    (err), \
    MALC_GET_LOGGER_INSTANCE_FUNC, \
    (condition), \
    malc_sev_error, \
    __VA_ARGS__\
    )

#define malc_error_i(err, malc_ptr, ...)\
  MALC_LOG_PRIVATE ((err), (malc_ptr), malc_sev_error, __VA_ARGS__)

#define malc_error_i_if(err, malc_ptr, condition, ...)\
  MALC_LOG_IF_PRIVATE(\
    (err), (malc_ptr), (condition), malc_sev_error, __VA_ARGS__\
    )

#else

#define malc_error(...)      malc_warning_silencer()
#define malc_error_if(...)   malc_warning_silencer()
#define malc_error_i(...)    malc_warning_silencer()
#define malc_error_i_if(...) malc_warning_silencer()

#endif

/*----------------------------------------------------------------------------*/
#ifndef MALC_STRIP_LOG_CRITICAL

#define malc_critical(err, ...)\
  MALC_LOG_PRIVATE( \
    (err), MALC_GET_LOGGER_INSTANCE_FUNC, malc_sev_critical, __VA_ARGS__ \
    )

#define malc_critical_if(err, condition, ...)\
  MALC_LOG_IF_PRIVATE(\
    (err), \
    MALC_GET_LOGGER_INSTANCE_FUNC, \
    (condition), \
    malc_sev_critical, \
    __VA_ARGS__\
    )

#define malc_critical_i(err, malc_ptr, ...)\
  MALC_LOG_PRIVATE ((err), (malc_ptr), malc_sev_critical, __VA_ARGS__)

#define malc_critical_i_if(err, malc_ptr, condition, ...)\
  MALC_LOG_IF_PRIVATE(\
    (err), (malc_ptr), (condition), malc_sev_critical, __VA_ARGS__\
    )

#else

#define malc_critical(...)      malc_warning_silencer()
#define malc_critical_if(...)   malc_warning_silencer()
#define malc_critical_i(...)    malc_warning_silencer()
#define malc_critical_i_if(...) malc_warning_silencer()

#endif

#ifdef __cplusplus
}
#endif

#endif /*include guard*/