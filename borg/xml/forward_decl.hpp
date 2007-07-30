#ifndef BORG_XML_FORWARD_DECL_HPP
#define BORG_XML_FORWARD_DECL_HPP

namespace borg {
namespace xml {

//---------------------------------------------------------------------------
//! Forward declarations for the impl, interface, adapter and concrete
//! classes of each DOM object.
//---------------------------------------------------------------------------
#define XML_FORWARD_DECL_0(name) \
  template<class Traits> \
  struct name ## _impl; \
  \
  template<class Traits, class Derived> \
  class name ## _interface; \
  \
  template<class Traits, class Derived> \
  class name ## _facade; \
  \
  template<class Traits> \
  class name ## _t; \
  \
  template<class Traits> \
  class name;

//---------------------------------------------------------------------------
//! Forward declarations for the impl, interface, adapter and concrete
//! classes of each DOM object with an additional template argument.
//---------------------------------------------------------------------------
#define XML_FORWARD_DECL_1(name) \
  template<class Traits, class T> \
  struct name ## _impl; \
  \
  template<class Traits, class Derived, class T> \
  class name ## _interface; \
  \
  template<class Traits, class Derived, class T> \
  class name ## _facade; \
  \
  template<class Traits, typename T> \
  class name ## _t; \
  \
  template<class Traits, typename T> \
  class name;

//---------------------------------------------------------------------------
#define XML_FORWARD_DECL_T(name, tmpl) \
  template<class Traits> \
  struct name ## _impl; \
  \
  template<class Traits, class Derived, tmpl> \
  class name ## _interface; \
  \
  template<class Traits, class Derived, tmpl> \
  class name ## _facade; \
  \
  template<class Traits, tmpl> \
  class name ## _t; \
  \
  template<class Traits, tmpl> \
  class name;

} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_FORWARD_DECL_HPP
