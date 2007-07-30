#ifndef BORG_EVENT_SIGNAL_HPP
#define BORG_EVENT_SIGNAL_HPP

#include <boost/signal.hpp>
#include <borg/event/traits.hpp>
#include <borg/util/bind_method.hpp>

namespace borg {
namespace event {
  
template<typename idT, typename toolkit>
  class signal : public boost::signal<typename traits<idT, toolkit>::slot::type >
{
public:
  typedef boost::signal<typename traits<idT, toolkit>::slot::type > base_type;
  
  signal() {}
    
  template<typename methodT, typename thisT>
  void bind(methodT m, thisT t)
  {
    base_type::connect(borg::bind_method(m, t));
  }    
};

} // namespace event
} // namespace borg

#endif /* BORG_EVENT_SIGNAL_HPP */
