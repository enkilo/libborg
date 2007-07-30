#ifndef BORG_JS_CONTEXT_HPP
#define BORG_JS_CONTEXT_HPP

#include <boost/thread/detail/singleton.hpp>
#include <borg/js/traits.hpp>
#include <borg/script/runtime.hpp>
#include <borg/script/context.hpp>
#include <borg/util/lazy_instance.hpp>
#include <js/jscntxt.h>

namespace borg {
  
using boost::detail::thread::singleton;
  
namespace script {
  
template<>
class runtime<js::traits>;

//----------------------------------------------------------------------------
template<>
struct runtime_impl<js::traits>
{
  BORG_SCRIPT_RUNTIME_TYPES(js::traits)

  typedef runtime< js::traits > this_type;
  typedef lazy_instance< this_type > lazy_type;
  typedef singleton< lazy_type > singleton_type;
    
  static this_type &
  shared()
  {
    return static_cast< this_type & >
      (static_cast< lazy_type & >(singleton_type::instance()));
  }

  static runtime_type
  create(length_type sz = js::default_runtime_size)
  {
    return ::JS_NewRuntime(sz);
  }

/*  static runtime_type
  create()
  {
    return ::JS_NewRuntime(4 * 1024 * 1024);
  }*/

  static void
  destroy(runtime_type rt)
  {
    return ::JS_DestroyRuntime(rt);
  }
  
};

//----------------------------------------------------------------------------
template<>
class runtime<js::traits>
    : public runtime_interface< js::traits, runtime<js::traits> >
//    , public runtime_facade< js::traits, runtime<js::traits> >
{
public:
  typedef runtime_impl<js::traits> impl;
  
  runtime(length_type vsz = js::default_runtime_size)
    : m_runtime(impl::create(vsz))
  {}
  
  operator runtime_type() const
  {
    return m_runtime;
  }
  
/*  operator const runtime_type &() const
  {
    return m_runtime;
  }*/
  
private:
  runtime_type m_runtime;
  runtime_type &get()
  {
    return m_runtime;
  }
  
};

//----------------------------------------------------------------------------
template<>
struct context_impl<js::traits>
{
  BORG_SCRIPT_CONTEXT_TYPES(js::traits)

  typedef lazy_instance< context<js::traits> > lazy_type;
  typedef singleton< lazy_type > singleton_type;
    
  static context_type &
  shared()
  {
    return static_cast< context<js::traits> & >
      (static_cast< lazy_type & >(singleton_type::instance()));
  }

  static context_type
  create(length_type st = js::default_stack_size)
  {
    return ::JS_NewContext(runtime_impl<js::traits>::shared(), st);
  }

  static context_type
  create(runtime_type rt, length_type st = js::default_stack_size)
  {
    return ::JS_NewContext(rt, st);
  }

  static void
  destroy(context_type cx)
  {
    return ::JS_DestroyContext(cx);
  }
};

//----------------------------------------------------------------------------

} // namespace script

namespace js {

typedef borg::script::runtime_t<traits> runtime_t;
typedef borg::script::runtime<traits> runtime;

typedef borg::script::context_t<traits> context_t;
typedef borg::script::context<traits> context;

} // namespace js
} // namespace borg

//----------------------------------------------------------------------------
#endif //ndef BORG_JS_SCAN_HPP
