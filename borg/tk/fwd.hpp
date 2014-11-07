#if !defined(BOOST_PP_IS_ITERATING)

#ifndef TK_FWD_HPP
#define TK_FWD_HPP

#include <boost/preprocessor.hpp>
#include <borg/wrap/wrapper.hpp>

#define TK_FWD_NCLASSES 4
#define TK_FWD_CLASSES \
  (dc, widget, frame, bitmap)

#define BOOST_PP_ITERATION_LIMITS (0, 3)
#define BOOST_PP_FILENAME_1 <borg/tk/fwd.hpp>

#include BOOST_PP_ITERATE()

#undef TK_FWD_NCLASSES
#undef TK_FWD_CLASSES

#ifndef TK_TRAITS_FWD_HPP
#define TK_TRAITS_FWD_HPP
#endif //ndef TK_TRAITS_FWD_HPP

#ifndef TK_WRAPPERS_FWD_HPP
#define TK_WRAPPERS_FWD_HPP
#endif //ndef TK_WRAPPERS_FWD_HPP

/*#ifndef TK_ADAPTERS_FWD_HPP
#define TK_ADAPTERS_FWD_HPP
#endif //ndef TK_ADAPTERS_FWD_HPP*/

#endif //ndef TK_FWD_HPP

#else

#define TK_NAME(y) BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(TK_FWD_NCLASSES, BOOST_PP_ITERATION(), TK_FWD_CLASSES), y)

#define TK_IMPL TK_NAME()
#define TK_TYPE TK_NAME(_type)
#define TK_TRAITS TK_NAME(_traits)
#define TK_WRAPPER TK_NAME(_wrapper)
#define TK_ADAPTER TK_NAME(_adapter)

namespace borg {
namespace tk {

#ifndef TK_TRAITS_FWD_HPP
template<
    class toolkit/*,
    class type = typename toolkit::TK_TYPE,
    class wrapper = borg::wrapper<type>*/
>
struct TK_TRAITS;
#endif //ndef TK_TRAITS_FWD_HPP

#ifndef TK_WRAPPERS_FWD_HPP
template<
    class toolkit/*,
    class type = typename toolkit::TK_TYPE,
    class traits = TK_TRAITS<toolkit, type>*/
>
struct TK_WRAPPER;
#endif //ndef TK_WRAPPERS_FWD_HPP

/*#ifndef TK_ADAPTERS_FWD_HPP
template<
    class toolkit,
    class derived,
    class traits = TK_TRAITS<toolkit, typename toolkit::TK_TYPE>
>
struct TK_ADAPTER;
#endif //ndef TK_ADAPTERS_FWD_HPP*/

/*#ifndef TK_IMPL_HPP
template<
    class toolkit,
    class derived,
    class traits = TK_TRAITS<toolkit, typename toolkit::TK_TYPE>
>
struct TK_IMPL;
#endif //ndef TK_IMPL_HPP*/

} // namespace tk
} // namespace borg

#undef TK_TYPE
#undef TK_TRAITS
#undef TK_WRAPPER
#undef TK_ADAPTER

#endif // !defined(BOOST_PP_IS_ITERATING)
