//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___ALGORITHM_UNIQUE_H
#define _LIBCPP___ALGORITHM_UNIQUE_H

#include <__config>
#include <__algorithm/adjacent_find.h>
#include <__iterator/iterator_traits.h>
#include <type_traits>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_PUSH_MACROS
#include <__undef_macros>

_LIBCPP_BEGIN_NAMESPACE_STD

// unique

template <class _ForwardIterator, class _BinaryPredicate>
_LIBCPP_NODISCARD_EXT _LIBCPP_CONSTEXPR_AFTER_CXX17 _ForwardIterator
unique(_ForwardIterator __first, _ForwardIterator __last, _BinaryPredicate __pred)
{
    __first = _VSTD::adjacent_find<_ForwardIterator, typename add_lvalue_reference<_BinaryPredicate>::type>
                                 (__first, __last, __pred);
    if (__first != __last)
    {
        // ...  a  a  ?  ...
        //      f     i
        _ForwardIterator __i = __first;
        for (++__i; ++__i != __last;)
            if (!__pred(*__first, *__i))
                *++__first = _VSTD::move(*__i);
        ++__first;
    }
    return __first;
}

template <class _ForwardIterator>
_LIBCPP_NODISCARD_EXT inline
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX17
_ForwardIterator
unique(_ForwardIterator __first, _ForwardIterator __last)
{
    typedef typename iterator_traits<_ForwardIterator>::value_type __v;
    return _VSTD::unique(__first, __last, __equal_to<__v>());
}

// unique_copy

template <class _BinaryPredicate, class _InputIterator, class _OutputIterator>
_LIBCPP_CONSTEXPR_AFTER_CXX17 _OutputIterator
__unique_copy(_InputIterator __first, _InputIterator __last, _OutputIterator __result, _BinaryPredicate __pred,
              input_iterator_tag, output_iterator_tag)
{
    if (__first != __last)
    {
        typename iterator_traits<_InputIterator>::value_type __t(*__first);
        *__result = __t;
        ++__result;
        while (++__first != __last)
        {
            if (!__pred(__t, *__first))
            {
                __t = *__first;
                *__result = __t;
                ++__result;
            }
        }
    }
    return __result;
}

template <class _BinaryPredicate, class _ForwardIterator, class _OutputIterator>
_LIBCPP_CONSTEXPR_AFTER_CXX17 _OutputIterator
__unique_copy(_ForwardIterator __first, _ForwardIterator __last, _OutputIterator __result, _BinaryPredicate __pred,
              forward_iterator_tag, output_iterator_tag)
{
    if (__first != __last)
    {
        _ForwardIterator __i = __first;
        *__result = *__i;
        ++__result;
        while (++__first != __last)
        {
            if (!__pred(*__i, *__first))
            {
                *__result = *__first;
                ++__result;
                __i = __first;
            }
        }
    }
    return __result;
}

template <class _BinaryPredicate, class _InputIterator, class _ForwardIterator>
_LIBCPP_CONSTEXPR_AFTER_CXX17 _ForwardIterator
__unique_copy(_InputIterator __first, _InputIterator __last, _ForwardIterator __result, _BinaryPredicate __pred,
              input_iterator_tag, forward_iterator_tag)
{
    if (__first != __last)
    {
        *__result = *__first;
        while (++__first != __last)
            if (!__pred(*__result, *__first))
                *++__result = *__first;
        ++__result;
    }
    return __result;
}

template <class _InputIterator, class _OutputIterator, class _BinaryPredicate>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX17
_OutputIterator
unique_copy(_InputIterator __first, _InputIterator __last, _OutputIterator __result, _BinaryPredicate __pred)
{
    return _VSTD::__unique_copy<typename add_lvalue_reference<_BinaryPredicate>::type>
                              (__first, __last, __result, __pred,
                               typename iterator_traits<_InputIterator>::iterator_category(),
                               typename iterator_traits<_OutputIterator>::iterator_category());
}

template <class _InputIterator, class _OutputIterator>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX17
_OutputIterator
unique_copy(_InputIterator __first, _InputIterator __last, _OutputIterator __result)
{
    typedef typename iterator_traits<_InputIterator>::value_type __v;
    return _VSTD::unique_copy(__first, __last, __result, __equal_to<__v>());
}

_LIBCPP_END_NAMESPACE_STD

_LIBCPP_POP_MACROS

#endif // _LIBCPP___ALGORITHM_UNIQUE_H
