#if !defined(BOOST_PP_IS_ITERATING)

#ifndef BORG_TK_IMPL_HPP
#define BORG_TK_IMPL_HPP

#include <boost/preprocessor.hpp>

#include <borg/tk/traits_fwd.hpp>
#include <borg/tk/widget.hpp>
#include <borg/tk/frame.hpp>
#include <borg/tk/bitmap.hpp>
#include <borg/tk/dc.hpp>

#define TK_IMPL_NCLASSES 5
#define TK_IMPL_CLASSES \
  (paint_dc, client_dc, widget, frame, bitmap)

#define TK_FWD_NCLASSES 5
#define TK_FWD_CLASSES \
  (dc, dc, widget, frame, bitmap)

#define BOOST_PP_ITERATION_LIMITS (0, 4)
#define BOOST_PP_FILENAME_1 <borg/tk/impl.hpp>

#include BOOST_PP_ITERATE()

#undef TK_FWD_NCLASSES
#undef TK_FWD_CLASSES

#undef TK_IMPL_NCLASSES
#undef TK_IMPL_CLASSES

#endif //ndef BORG_TK_IMPL_HPP

#else

#define TK_CLASS() BOOST_PP_TUPLE_ELEM(TK_IMPL_NCLASSES, BOOST_PP_ITERATION(), TK_IMPL_CLASSES)
#define TK_TYPENAME(y) BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(TK_FWD_NCLASSES, BOOST_PP_ITERATION(), TK_FWD_CLASSES), y)

#define TK_TYPE TK_TYPENAME(_type)
#define TK_TRAITS TK_TYPENAME(_traits)
#define TK_IMPL TK_CLASS()

namespace borg {
namespace tk {

template<
    class toolkit/*,
    class type = typename toolkit::TK_TYPE,
    class traits = TK_TRAITS<toolkit, type>*/
>
class TK_IMPL;

} // namespace tk
} // namespace borg

#undef TK_TYPE
#undef TK_TRAITS
#undef TK_IMPL

#endif // !defined(BOOST_PP_IS_ITERATING)
