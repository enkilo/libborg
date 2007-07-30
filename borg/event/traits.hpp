#ifndef BORG_EVENT_TRAITS_HPP
#define BORG_EVENT_TRAITS_HPP

#include <boost/function.hpp>
#include <borg/event/id.hpp>
#include <borg/event/slot.hpp>
#include <borg/tk/wrappers_fwd.hpp>
#include <borg/tk/dc.hpp>

namespace borg {
namespace event {

using namespace tk;
  
template<typename idT, typename toolkit>
struct traits {};
  
template<typename toolkit>
struct traits<event::move, toolkit>
{
  typedef move id;
  typedef toolkit tk_type;
  typedef typename tk_type::vector_type vector_type;
  typedef typename slot::move<tk_type> slot;
  typedef typename boost::function<slot> fn;
};

template<typename toolkit>
struct traits<event::resize, toolkit>
{
  typedef resize id;
  typedef toolkit tk_type;
  typedef typename tk_type::vector_type vector_type;
  typedef typename slot::resize<tk_type> slot;
  typedef typename boost::function<slot> fn;
};

template<typename toolkit>
struct traits<event::mouseup, toolkit>
{
  typedef mouseup id;
  typedef toolkit tk_type;
  typedef typename tk_type::vector_type vector_type;
  typedef typename slot::mousebutton<tk_type> slot;
  typedef typename boost::function<slot> fn;
};

template<typename toolkit>
struct traits<event::mousedown, toolkit>
{
  typedef mousedown id;
  typedef toolkit tk_type;
  typedef typename tk_type::vector_type vector_type;
  typedef typename slot::mousebutton<tk_type> slot;
  typedef typename boost::function<slot> fn;
};

template<typename toolkit>
struct traits<event::mousedclick, toolkit>
{
  typedef mousedclick id;
  typedef toolkit tk_type;
  typedef typename tk_type::vector_type vector_type;
  typedef typename slot::mousebutton<tk_type> slot;
  typedef typename boost::function<slot> fn;
};

template<typename toolkit>
struct traits<event::mousemove, toolkit>
{
  typedef mousemove id;
  typedef toolkit tk_type;
  typedef typename tk_type::vector_type vector_type;
  typedef typename slot::mousemove<tk_type> slot;
  typedef typename boost::function<slot> fn;
};

template<typename toolkit>
struct traits<event::mouseenter, toolkit>
{
  typedef mouseenter id;
  typedef toolkit tk_type;
  typedef typename tk_type::vector_type vector_type;
  typedef typename slot::mousemove<tk_type> slot;
  typedef typename boost::function<slot> fn;
};

template<typename toolkit>
struct traits<event::mouseleave, toolkit>
{
  typedef mouseleave id;
  typedef toolkit tk_type;
  typedef typename tk_type::vector_type vector_type;
  typedef typename slot::mousemove<tk_type> slot;
  typedef typename boost::function<slot> fn;
};

template<typename toolkit>
struct traits<event::redraw, toolkit>
{
  typedef redraw id;
  typedef toolkit tk_type;
//  typedef borg::tk::dc_wrapper<toolkit> dc_type;
  typedef slot::redraw<tk_type> slot;
  typedef typename boost::function<slot> fn;
};

template<typename toolkit>
struct traits<event::focusloose, toolkit>
{
  typedef focusloose id;
  typedef toolkit tk_type;
  typedef slot::focus slot;
  typedef typename boost::function<slot> fn;
};

template<typename toolkit>
struct traits<event::focusgain, toolkit>
{
  typedef focusgain id;
  typedef toolkit tk_type;
  typedef slot::focus slot;
  typedef typename boost::function<slot> fn;
};
  
} // namespace event
} // namespace borg

#endif /* BORG_EVENT_TRAITS_HPP */
