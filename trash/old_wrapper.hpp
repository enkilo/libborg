#warning "obsolete"
//----------------------------------------------------------------------------
//! \file wrapper.hpp
//! \svn  $Id: wrapper.hpp 10 2007-03-19 06:16:14Z nexbyte $
//!
//! Implements \ref wrap::wrapper, a class wrapping data as private member
//! while avoiding invocation of copy-constructors and assignment operators.
//----------------------------------------------------------------------------
#ifndef WRAPPER_HPP
#define WRAPPER_HPP

#include <boost/static_assert.hpp>
#include <wrap/wrap_traits.hpp>
#include <wrap/is_mutable.hpp>

namespace wrap 
{  
  using namespace boost;
  
  #define wrapper_TYPEDEF(wrapT) \
    typedef wrapT wrap_type; \
    typedef wrapper<wrapT> wrapper_type;
  
  //! Encapsulates objects of class T.
  //! is_mutable_ will indicate if the wrapee can be changed after
  //! instantiation of the encapsulator.
  template<typename T, class traits = wrap_traits<T>, bool is_mutable_ = traits::is_mutable>
    class wrapper
  {
    //! Reject function types. We are wrapping a DATA member.
    BOOST_STATIC_ASSERT(!::boost::is_function<T>::value);
    
    //! Accept types with trivial constructors only, because
    //! we don't want to call any (non-trivial) constructor code.
    BOOST_STATIC_ASSERT(::boost::is_reference<T>::value ||
                        ::boost::has_trivial_constructor<T>::value);

  public:
    //! Can the wrapee be changed after instantiation?
    BOOST_STATIC_CONSTANT(bool, is_mutable = is_mutable_);

    //!< The type we're wrapping.
    typedef typename traits::wrap_type wrap_type;
    
    //!< Parameter type.
    typedef typename traits::param_type param_type;
    
    //!< Parameter type.
    typedef typename traits::unwrap_type unwrap_type;
    
    //! Initialize with another object of the wrapped type.
    wrapper(param_type __w) : m_wrapped(__w)
    {}

  protected:
    // Declare the wrapper interface.
    
    #define FN(F) F
    #define CONST(C) C
    #define PROT(P) public

    #include <wrap/const_wrapper.ipp>

  private:
    //! The wrapped object.
    wrap_type m_wrapped;    
  };
  
  //! Returns a const-reference to the wrapped data.
  template<typename T, class traits, bool is_mutable_>
    inline typename traits::unwrap_type
    wrapper<T, traits, is_mutable_>::get() const
  {
    return m_wrapped;
  }
  
} // end of namespace wrap

//----------------------------------------------------------------------------
#endif // WRAPPER_HPP
