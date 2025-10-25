
#ifndef FINTAMATH_EXPORT_H
#define FINTAMATH_EXPORT_H

#ifdef FINTAMATH_STATIC_DEFINE
#  define FINTAMATH_EXPORT
#  define FINTAMATH_NO_EXPORT
#else
#  ifndef FINTAMATH_EXPORT
#    ifdef fintamath_EXPORTS
        /* We are building this library */
#      define FINTAMATH_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define FINTAMATH_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef FINTAMATH_NO_EXPORT
#    define FINTAMATH_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef FINTAMATH_DEPRECATED
#  define FINTAMATH_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef FINTAMATH_DEPRECATED_EXPORT
#  define FINTAMATH_DEPRECATED_EXPORT FINTAMATH_EXPORT FINTAMATH_DEPRECATED
#endif

#ifndef FINTAMATH_DEPRECATED_NO_EXPORT
#  define FINTAMATH_DEPRECATED_NO_EXPORT FINTAMATH_NO_EXPORT FINTAMATH_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef FINTAMATH_NO_DEPRECATED
#    define FINTAMATH_NO_DEPRECATED
#  endif
#endif

#endif /* FINTAMATH_EXPORT_H */
