#if !defined(BOOST_PP_IS_ITERATING)

#ifndef TK_TRAITS_FWD_HPP
#define TK_TRAITS_FWD_HPP

#include <boost/preprocessor.hpp>
#include <borg/wrap/wrapper.hpp>

#define TK_FWD_NCLASSES 4
#define TK_FWD_CLASSES \
  (dc, widget, frame, bitmap)

#define BOOST_PP_ITERATION_LIMITS (0, 3)
#define BOOST_PP_FILENAME_1 <borg/tk/traits_fwd.hpp>

#include BOOST_PP_ITERATE()

#undef TK_FWD_NCLASSES
#undef TK_FWD_CLASSES

#endif //ndef TK_TRAITS_FWD_HPP

#else

#define TK_NAME(y) BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(TK_FWD_NCLASSES, BOOST_PP_ITERATION(), TK_FWD_CLASSES), y)

#define TK_TYPE TK_NAME(_type)
#define TK_TRAITS TK_NAME(_traits)

namespace borg {
namespace tk {

template<class toolkit/*,
         class type = typename toolkit::TK_TYPE,
         class wrapper = borg::wrapper<type>*/ >
struct TK_TRAITS;

} // namespace tk
} // namespace borg

#undef TK_TYPE
#undef TK_TRAITS

#endif // !defined(BOOST_PP_IS_ITERATING)
