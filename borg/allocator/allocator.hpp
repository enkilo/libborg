#ifndef BORG_ALLOCATOR_HPP
#define BORG_ALLOCATOR_HPP

#include <borg/util/dereference_cast.hpp>
#include <borg/util/lazy_instance.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/wrap/preproc.hpp>
#include <boost/operators.hpp>
#include <borg/allocator/traits.hpp>
#include <borg/allocator/interface.hpp>

namespace borg {

//---------------------------------------------------------------------------
/*template<class T, class Traits>
struct allocator_t 
    : public allocator_interface< allocator_t<T, Traits>, T, Traits >
//    , public allocator_facade< Traits, allocator_t<Traits, T>, T >
{
  typedef allocator_impl<T, Traits> impl;

  BORG_ALLOCATOR_TYPES(typename impl, T)

  typedef allocator_interface< allocator_t<T, Traits>, T, Traits > base_type;

  //---------------------------------------------------------------------------
  //! Create unallocated allocator. Specifically a null-pointer.
  //---------------------------------------------------------------------------
  allocator_t() : base_type(0)
  {}

  //---------------------------------------------------------------------------
  //! Create from an existing allocator.
  //---------------------------------------------------------------------------
  allocator_t(const allocator_type &a)
    : base_type(a)
  {}  
};*/  
    
//---------------------------------------------------------------------------
template<class Derived, class T, class Traits>
struct allocator_facade
    : public boost::equality_comparable< allocator_facade<Derived, T, Traits> >
{
  typedef allocator_impl<T, Traits> impl;

  BORG_ALLOCATOR_TYPES(typename impl, T)

  bool
  operator==(Derived const &a) const
  {
    return dereference_cast<Derived const>(this) == a;
  }
  
  
};
  
//---------------------------------------------------------------------------
template<class T, class Traits>
struct allocator
    : public allocator_facade< allocator<T, Traits>, T, Traits >
    , public allocator_interface< allocator<T, Traits>, T, Traits >
{
  template<class U>
  struct rebind
  {
    typedef allocator<U, Traits> other;
  };

  typedef allocator_impl<T, Traits> impl;

  BORG_ALLOCATOR_TYPES(typename impl, T)

  static allocator<T, Traits>
  singleton()
  {
    return allocator<T, Traits>(impl::singleton(), 0);
  }

  allocator(allocator_type const &a) 
    : m_alloc(a) 
  {}

  //! Default constructor.
  allocator()
    : m_alloc(impl::singleton())
  {}
  
  //! Copy constructor.
  allocator(allocator<T, Traits> const &a)
    : m_alloc(a)
  {
  }
  
  //! Rebinding constructor.
  template<class U>
  allocator(allocator<U, Traits> const &a) 
    : m_alloc(a) 
  {}
  
  //! Destructor.
  ~allocator()
  {
/*    if(m_free)
      impl::destroy(dereference_cast<base_type>(this));*/
  }
  
  //! \name Conversion operators.
  //@{
  operator allocator_type       &()       { return m_alloc; }
  operator allocator_type const &() const { return m_alloc; }
  //@}

private:
  allocator(allocator_type const &a, const void *const dummy)
    : m_alloc(a)
  {}

  allocator_type m_alloc;  
};  
    
//---------------------------------------------------------------------------
/*template<class Traits, class Derived, class T, class Tag>
class allocator_decorator;
  

template<class Traits, class Derived, class T>
class allocator_decorator<Traits, Derived, T, 
{
public:
  BORG_ALLOCATOR_TYPES(typename Traits)
  
  typedef allocator_impl<Traits, T> impl;
  
};*/
  
//---------------------------------------------------------------------------
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_ALLOCATOR_HPP
