#if !defined(BOOST_PP_IS_ITERATING)

#ifndef TK_WRAPPERS_HPP
#define TK_WRAPPERS_HPP

#include <boost/preprocessor.hpp>
#include <borg/wrap/wrapper.hpp>

#define TK_WRAPPER_NCLASSES 4
#define TK_WRAPPER_CLASSES \
  (dc, widget, frame, bitmap)

#define BOOST_PP_ITERATION_LIMITS (0, 3)
#define BOOST_PP_FILENAME_1 <borg/tk/wrappers.hpp>

#include BOOST_PP_ITERATE()

#undef TK_WRAPPER_NCLASSES
#undef TK_WRAPPER_CLASSES

#ifndef TK_TRAITS_FWD_HPP
#define TK_TRAITS_FWD_HPP
#endif //ndef TK_TRAITS_FWD_HPP

#ifndef TK_ADAPTERS_FWD_HPP
#define TK_ADAPTERS_FWD_HPP
#endif //ndef TK_ADAPTERS_FWD_HPP

#endif //ndef TK_WRAPPERS_HPP

#else

#define TK_NAME(y) BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(TK_WRAPPER_NCLASSES, BOOST_PP_ITERATION(), TK_WRAPPER_CLASSES), y)

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
class TK_TRAITS;
#endif //ndef TK_TRAITS_FWD_HPP

#ifndef TK_ADAPTERS_FWD_HPP
template<
    class toolkit,
    class derived/*,
    class Traits = TK_TRAITS<toolkit>*/
>
class TK_ADAPTER;
#endif //ndef TK_ADAPTERS_FWD_HPP

template<class toolkit>
struct TK_WRAPPER 
    : public wrapper<typename toolkit::TK_TYPE *>
    , public TK_ADAPTER< toolkit, TK_WRAPPER<toolkit> >
{
  typedef wrapper<typename toolkit::TK_TYPE *> base_type;
  typedef typename toolkit::TK_TYPE *init_type;
//  DC_TRAITS(Traits)
//  BORG_WRAP_TRAITS(base_type)

  TK_WRAPPER(init_type x) : base_type(x) {}
};

} // namespace tk
} // namespace borg

#undef TK_TYPE
#undef TK_TRAITS
#undef TK_WRAPPER
#undef TK_ADAPTER

#endif // !defined(BOOST_PP_IS_ITERATING)
