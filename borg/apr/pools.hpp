#ifndef APR_POOLS_HPP
#define APR_POOLS_HPP

#include <apr_pools.h>
#include <borg/apr/allocator.hpp>
#include <borg/apr/exception.hpp>
#include <borg/wrap/pointer.hpp>
#include <boost/thread/detail/singleton.hpp>
#include <borg/util/lazy_instance.hpp>

namespace borg {
namespace apr {

typedef apr_size_t size_t;
typedef apr_off_t off_t;
typedef void *data_type;
  
//---------------------------------------------------------------------------
typedef int abortfunc_t(int);
  
//---------------------------------------------------------------------------
typedef pool const pool_t;
  
//---------------------------------------------------------------------------
class pool : public borg::pointer<apr_pool_t>
{
public:
  typedef borg::pointer<apr_pool_t> base_type;
  typedef pool this_type;
  typedef allocator<char> allocator_type;
  typedef pool_t &pool_type;

  typedef lazy_instance< this_type > lazy_type;
  typedef boost::detail::thread::singleton< lazy_type > singleton_type;

  static this_type &
  shared()
  {
    return static_cast< this_type & >
      (static_cast< lazy_type & >(singleton_type::instance()));
  }
  
  /// create new root pool.
  pool(allocator_type const &a = allocator_type::singleton())
  {
    ::apr_pool_t *p;
    ::apr_status_t st = ::apr_pool_create_ex(&p, 0, &this_type::abort, a);

    if(st != success)
      throw exception(st);
    
    (*this) = p;
  }
  
  /// implicitly wraps up existing pool.
  pool(init_type p) throw(exception)
    : base_type(p)
  {
    if(!p)
      throw exception("trying to wrap null-pointer to apr_pool_t");
  }

  /// static constructor
  static pool
  create(pool_type parent) throw(exception)
  {
    ::apr_pool_t *ret;
    
    if(!parent)
      throw exception("trying to create pool without allocator and null-pointer parent");
    
    ::apr_pool_create(&ret, parent);
    return ret;
  }

  /// clear all memory in the pool and run all the cleanups.
  /// this also destroys all subpools.
  void
  clear() const
  { 
    ::apr_pool_clear(get());
  }

  /// debug version of clear().
  void
  clear_debug(const char *file_line) const
  { 
    ::apr_pool_clear_debug(get(), file_line); 
  }
  
  /// destroy the pool
  void
  destroy()
  {
    ::apr_pool_destroy(get());
    set(static_cast< ::apr_pool_t * >(0));
  }
  
protected:
  static int 
  abort(int retcode) throw(exception)
  {
    throw exception(enomem);
    return retcode;
  }
  
private:
//  pool() : base_type(0) {}    
};

//---------------------------------------------------------------------------

} // namespace apr
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef APR_POOLS_HPP
