#ifndef BORG_XML_OUTPUT_BUFFER_HPP
#define BORG_XML_OUTPUT_BUFFER_HPP

#include <boost/noncopyable.hpp>
#include <borg/string.hpp>
#include <borg/xml/lib/types.hpp>
#include <borg/xml/lib/forward.hpp>
#include <borg/util/dereference_cast.hpp>

namespace borg { 
namespace xml {

//---------------------------------------------------------------------------
template<class Traits, class Derived, class Target>
struct output_buffer_interface
{
  XML_LIB_TYPES(typename Traits)

  typedef output_buffer_impl<Traits, Target> impl;

  //-----------------------------------------------------------------------
  status_type
  write(const byte_type *b, length_type n)
  {
    return impl::write(dereference_cast<Derived>(this), b, n);
  }

};

//---------------------------------------------------------------------------
template<class Traits, class Derived, class Target>
struct output_buffer_facade
{
//  XML_LIB_TYPES(typename Traits)

//  typedef output_buffer_impl<Traits, Target> impl;
};

//---------------------------------------------------------------------------
template<class Traits, class Target>
class output_buffer
    : private boost::noncopyable
    , public output_buffer_interface< Traits, output_buffer<Traits, Target>, Target >
    , public output_buffer_facade< Traits, output_buffer<Traits, Target>, Target >
{
  typedef output_buffer_impl<Traits, Target> impl;

public:
  XML_LIB_TYPES(typename Traits)

  template<typename A1>
  output_buffer(const A1 &a1, typename boost::enable_if_c<
                    !boost::is_same<A1, Target>::value, void
                >::type const *dummy = 0)
      : m_buffer(impl::create(a1))
  {}
  
  ~output_buffer()
  {
//    impl::destroy(m_buffer);
  }
  
  operator Target() const
  {
    return get();
  }
  
private:
  Target m_buffer;
  Target get() const { return m_buffer; }
}; 

//---------------------------------------------------------------------------
/*template<class Traits, class Target>
struct output_buffer : output_buffer_t<Traits, Target>
{
  XML_LIB_TYPES(typename Traits)
  
  typedef output_buffer_t<traits, Target> base_type;
  typedef output_buffer_impl<Traits> impl;

  output_buffer(const typename Traits::Target &t)
    : base_type(t)
  {}

protected:
  output_buffer(const Target &t)
    : base_type(t)
  {}
};*/
  
//---------------------------------------------------------------------------
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_OUTPUT_BUFFER_HPP
