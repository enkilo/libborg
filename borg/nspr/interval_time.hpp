#ifndef BORG_NSPR_INTERVAL_TIME_HPP
#define BORG_NSPR_INTERVAL_TIME_HPP

#include <borg/net/interval_time.hpp>
#include <borg/nspr/traits.hpp>

#include <nspr/prnetdb.h>

namespace borg {
namespace net { 
  
//----------------------------------------------------------------------------
template<>
struct interval_time_impl< nspr::traits >
{
  BORG_NET_INTERVAL_TIME_TYPES( nspr::traits )
 
  BOOST_STATIC_CONSTANT(unsigned long, min = PR_INTERVAL_MIN);
  BOOST_STATIC_CONSTANT(unsigned long, max = PR_INTERVAL_MAX);

  BOOST_STATIC_CONSTANT(unsigned long, no_wait = PR_INTERVAL_NO_WAIT);
  BOOST_STATIC_CONSTANT(unsigned long, no_timeout = PR_INTERVAL_NO_TIMEOUT);
  
  static interval_type
  now()
  {
    return ::PR_IntervalNow();
  }
  
  static interval_type
  ticks_per_second()
  {
    return ::PR_TicksPerSecond();
  }
  
  static interval_type
  seconds_to_interval(size_type seconds)
  {
    return ::PR_SecondsToInterval(seconds);
  }

  static interval_type
  milliseconds_to_interval(size_type milli)
  {
    return ::PR_MillisecondsToInterval(milli);
  }
  
  static interval_type
  microseconds_to_interval(size_type micro)
  {
    return ::PR_MicrosecondsToInterval(micro);
  }
  
  static size_type
  interval_to_seconds(interval_type ticks)
  {
    return ::PR_IntervalToSeconds(ticks);
  }
  
  static size_type
  interval_to_milliseconds(interval_type ticks)
  {
    return ::PR_IntervalToMilliseconds(ticks);
  }
  
  static size_type
  interval_to_microseconds(interval_type ticks)
  {
    return ::PR_IntervalToMicroseconds(ticks);
  }
};
  
//----------------------------------------------------------------------------

} // namespace net
namespace nspr {

typedef net::interval_time_t<traits> interval_time_t;
typedef net::interval_time<traits> interval_time;

} // namespace nspr
} // namespace borg

//----------------------------------------------------------------------------
#endif //ndef BORG_NSPR_INTERVAL_TIME_HPP
