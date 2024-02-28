#ifndef _ERZC_COMMON_ASSERT_H
#define _ERZC_COMMON_ASSERT_H

/**
 * \file assert.h
 *
 * \brief Assert macros.
 */

#include <mir/common/assert.h>

#ifdef ERZC_NDEBUG
#    define ERZC_ASSERT(expr) ((void)0)
#    define ERZC_ASSERT_MSG(expr, msg) ((void)0)
#else
#    define ERZC_ASSERT(expr) MIR_ASSERT(expr)
#    define ERZC_ASSERT_MSG(expr, msg) MIR_ASSERT_MSG(expr, msg)
#endif

/**
 * \def ERZC_ASSERT
 *
 * \brief Simple wrapper around standard library's `assert`.
 *
 * \note If `NDEBUG` or `ERZC_NDEBUG` is defined, then `ERZC_ASSERT` does nothing.
 *
 * \param expr expression
 */

/**
 * \def ERZC_ASSERT_MSG
 *
 * \brief Simple wrapper around standard library's `assert`.
 *
 * \note If `NDEBUG` or `ERZC_NDEBUG` is defined, then `ERZC_ASSERT_MSG` does nothing.
 *
 * \param expr expression
 * \param msg  message
 */

#endif /* _ERZC_COMMON_ASSERT_H */
