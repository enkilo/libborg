#ifndef BORG_ARRAY_HPP
#define BORG_ARRAY_HPP

#include <borg/util/dereference_cast.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/preproc.hpp>
#include <borg/sequence.hpp>

namespace borg {

//---------------------------------------------------------------------------
//! Forward declare array classes.
//---------------------------------------------------------------------------
template<class T, class Traits>
struct array_impl;
  
template<class T, class Traits>
struct array_t;
  
template<class T, class Traits>
struct array;
  
//---------------------------------------------------------------------------
#define BORG_ARRAY_TYPES(ValueType, Traits) \
  typedef Traits::template array<ValueType>::type array_type; \
  typedef ValueType                               value_type; \
  typedef Traits::index_type                      index_type;
  
//---------------------------------------------------------------------------
//! Defines a generic interface for arrays.
//!
//! Calls to any method are forwarded to static methods within the array
//! impl class. Arguments are passed using the implementation dependant
//! types defined by the Traits class.
//!
//! The Derived class which inherits from array_interface should be 
//! convertible to some type which is accepted as first argument of the 
//! static impl methods.
//---------------------------------------------------------------------------
template<class Derived, class T, class Traits>
struct array_interface : 
  sequence_interface<Derived, typename Traits::template array<T>::type,
    typename Traits::template array<T>::type::const_iterator, 
    typename Traits::template array<T>::type::iterator, Traits>
{
  BORG_ARRAY_TYPES(T, typename Traits)
  BORG_PP_USE_TYPE(typename array_type, const_iterator)
  BORG_PP_USE_TYPE(typename array_type, iterator)    

  //-----------------------------------------------------------------------
  //! Impl class which provides the implementation.
  //-----------------------------------------------------------------------
  typedef array_impl<T, Traits> impl;

  //-----------------------------------------------------------------------
  index_type
  size() const
  {
    return impl::size
      (dereference_cast<Derived const>(this));
  }
  
  //-----------------------------------------------------------------------
  void
  push_back(const T &val)
  {
    impl::push_back
      (dereference_cast<Derived>(this), val);
  }
  
  
};

//---------------------------------------------------------------------------
//! The array facade implements the standard array operators and other
//! syntactic sugar ontop of the generic array interface.
//---------------------------------------------------------------------------
template<class Derived, class T, class Traits>
struct array_facade
//    : public boost::equality_comparable< array_facade<Derived, T, Traits> >
{
  BORG_ARRAY_TYPES(T, typename Traits)

  typedef array_impl<T, Traits> impl;

};

//---------------------------------------------------------------------------
//! String adapter class. Models a wrapper of the underlaying character 
//! pointer which mixes in the generic array interface and facade.
//!
//! Used to instantiate temporary objects which hold a pointer to the 
//! underlaying array while emulating this pointers behaviour through
//! overloaded operators (not unlike an iterator).
//!
//! Thus it can be transparently used in the calls to the underlaying API. 
//---------------------------------------------------------------------------
template<class T, class Traits>
struct array_t 
    : public wrapper<typename Traits::template array<T>::type *>
    , public array_interface< array_t<T, Traits>, T, Traits >
    , public array_facade< array_t<T, Traits>, T, Traits >
{
  BORG_ARRAY_TYPES(T, typename Traits)

  typedef wrapper<array_type *> base_type;
  typedef array_impl<T, Traits> impl;

  //---------------------------------------------------------------------------
  //! Create unallocated (unlike empty) array. Specifically a null-pointer.
  //---------------------------------------------------------------------------
  array_t() : base_type(0)
  {}

  array_t(array_type *a) : base_type(a)
  {}
};  
    
//---------------------------------------------------------------------------
template<class T, class Traits>
class array
    : public array_interface< array<T, Traits>, T, Traits >
    , public array_facade< array<T, Traits>, T, Traits >
{
public:
  BORG_ARRAY_TYPES(T, typename Traits)
  
  typedef array_type sequence_type;
  
  BORG_PP_USE_TYPE(typename array_type, const_iterator)
  BORG_PP_USE_TYPE(typename array_type, iterator)
    
  friend class wrapper_core_access;
  friend class array_interface< array<T, Traits>, T, Traits >;
  friend class array_facade< array<T, Traits>, T, Traits >;
  
  typedef array_t<T, Traits> base_type;
  typedef array_impl<T, Traits> impl;
  
  array() : m_array()
  {}
  
  array(const array_type &arr) : m_array(arr)
  {}
  
  operator array_type &() { return m_array; }
  operator const array_type &() const { return m_array; }
  array_type *operator->() { return &m_array; }
  const array_type *operator->() const { return &m_array; }

private:
  array_type m_array;
};
  
//---------------------------------------------------------------------------

} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_ARRAY_HPP
