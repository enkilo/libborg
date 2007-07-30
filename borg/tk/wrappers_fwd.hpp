#if !defined(BOOST_PP_IS_ITERATING)

#ifndef TK_WRAPPERS_FWD_HPP
#define TK_WRAPPERS_FWD_HPP

#include <boost/preprocessor.hpp>

#define TK_FWD_NCLASSES 4
#define TK_FWD_CLASSES \
  (dc, widget, frame, bitmap)

#define BOOST_PP_ITERATION_LIMITS (0, 3)
#define BOOST_PP_FILENAME_1 "tk/wrappers_fwd.hpp"

#include BOOST_PP_ITERATE()

#undef TK_FWD_NCLASSES
#undef TK_FWD_CLASSES

#endif //ndef TK_WRAPPERS_FWD_HPP

#else

#define TK_NAME(y) BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(TK_FWD_NCLASSES, BOOST_PP_ITERATION(), TK_FWD_CLASSES), y)

#define TK_TYPE TK_NAME(_type)
#define TK_TRAITS TK_NAME(_traits)
#define TK_WRAPPER TK_NAME(_wrapper)

namespace borg {
namespace tk {

#ifndef TK_TRAITS_FWD_HPP
template<class toolkit,
         class type = typename toolkit::TK_TYPE,
         class wrapper = borg::wrapper<type> >
struct TK_TRAITS;
#endif //ndef TK_TRAITS_FWD_HPP

template<class toolkit,
         class type = typename toolkit::TK_TYPE,
         class traits = TK_TRAITS<toolkit, type> >
struct TK_WRAPPER;
  
} // namespace tk
} // namespace borg

#undef TK_TYPE
#undef TK_TRAITS
#undef TK_WRAPPER

#endif // !defined(BOOST_PP_IS_ITERATING)
