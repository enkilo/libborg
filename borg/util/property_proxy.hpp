#ifndef BORG_UTIL_PROPERTY_PROXY_HPP
#define BORG_UTIL_PROPERTY_PROXY_HPP

//#include <boost/function.hpp>
#include <borg/util/detail/property_impl.hpp>

#define TEMPLATE_CCC_PROPERTY_PROXY(Namespace, ObjectT, TemplateT, Id, ValueT) \
  property_proxy< ObjectT, TEMPLATE_CCC_PROPERTY_TYPE(Namespace, TemplateT, Id, ValueT) >

#define TEMPLATE_CCCB_PROPERTY_PROXY(Namespace, ObjectT, TemplateT, Id, ValueT) \
  property_proxy< ObjectT, TEMPLATE_CCCB_PROPERTY_TYPE(Namespace, TemplateT, Id, ValueT) >

namespace borg {

template<typename Pointee>
Pointee *
ptr_sub(Pointee *ptr, int i)
{
  return reinterpret_cast<Pointee *>(((char *)ptr) - i);
}  
  
//----------------------------------------------------------------------------
template<class ObjectT, class Implementation>
class /*__attribute__((packed))*/ property_proxy
{
public:
  typedef property_proxy<ObjectT, Implementation> this_type;
  typedef ObjectT object_type;
  typedef Implementation implementation_type;
  typedef typename Implementation::value_type value_type;

  explicit
  property_proxy(ObjectT *obj) 
    : m_offset((size_t)this - (size_t)obj)
  {}
  
  operator value_type() const
  {
    return implementation_type::get(object());
  }
  
  const this_type &
  operator=(const value_type &v) const
  {
    implementation_type::set(object(), v);
    return *this;
  }

private:
  ObjectT *object() const
  {
    return ptr_sub((ObjectT *)this, m_offset);
  }
  
  unsigned char/* const*/ m_offset;
};

//----------------------------------------------------------------------------
/*template<class obj, class value>
class property_proxy<obj, value const>
{
public:
  typedef property_proxy<obj, value> this_type;
  typedef boost::function<value(obj)> getter_type;

  explicit
  property_proxy(obj &o, getter_type g)
    : m_obj(o)
    , m_getter(g)
  {}

  operator value() const
  {
    return m_getter(m_obj);
  }
  
private:
  obj &m_obj;
  getter_type m_getter;
};*/

}// namespace borg
  
//---------------------------------------------------------------------------
#endif //ndef BORG_UTIL_PROPERTY_PROXY_HPP
