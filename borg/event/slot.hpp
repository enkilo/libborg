#ifndef BORG_EVENT_SLOT_HPP
#define BORG_EVENT_SLOT_HPP

#include <boost/type_traits/function_traits.hpp>
#include <list>
#include <borg/tk/traits_fwd.hpp>
#include <borg/event/mouse.hpp>

// Callback function types for all possible event types.

namespace borg { 
namespace event { 
namespace slot {

  using boost::function_traits;
  using tk::dc_traits;
  
  //! Type of function called when event source is moved.
  template<class toolkit>
    struct move
  {
    typedef toolkit tk_type;
    typedef typename toolkit::vector_type vector_type;
    typedef bool type(vector_type x, vector_type y);
    static const int arity = function_traits<type>::arity;
  };

  //! Type of function called when event source is resized.
  template<class toolkit>
    struct resize
  {
    typedef toolkit tk_type;
    typedef typename toolkit::vector_type vector_type;
    typedef bool type(vector_type w, vector_type h);
    static const int arity = function_traits<type>::arity;
  };
    
  //! Type of function called when mouse buttons change state.
  template<class toolkit>
    struct mousebutton
  {
    typedef toolkit tk_type;
    typedef typename toolkit::vector_type vector_type;
    typedef bool type(vector_type x, vector_type y, mouse::button b);
    static const int arity = function_traits<type>::arity;
  };
  
  //! Type of function called when mouse moves.
  template<class toolkit>
    struct mousemove
  {
    typedef toolkit tk_type;
    typedef typename toolkit::vector_type vector_type;
    typedef bool type(vector_type x, vector_type y, mouse::buttons b);
    static const int arity = function_traits<type>::arity;
  };

  //! Type of function called when focus changes.
  struct focus
  {
    typedef bool type(bool f);
    static const int arity = function_traits<type>::arity;
  };

  //! Type of function called when redrawing is needed.
  template<class toolkit, class dc = typename toolkit::dc_type>
    struct redraw
  {
    typedef toolkit tk_type;
    typedef dc dc_type;
    typedef typename toolkit::rect_type rect_type;
    typedef bool type(dc_type &paintdc, const std::list<rect_type> &rects);
    static const int arity = function_traits<type>::arity;
  };

} // namespace slot
} // namespace event
} // namespace borg

#endif //ndef BORG_EVENT_SLOT_HPP
