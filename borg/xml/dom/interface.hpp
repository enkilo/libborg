#ifndef BORG_XML_DOM_INTERFACE_HPP
#define BORG_XML_DOM_INTERFACE_HPP

#include <borg/util/dereference_cast.hpp>

#include <borg/xml/lib/adapter.hpp>
#include <borg/xml/dom/types.hpp>
#include <borg/xml/dom/forward.hpp>

#include <borg/xml/dom/document.hpp>
#include <borg/xml/dom/attribute.hpp>
#include <borg/xml/dom/element.hpp>
#include <borg/xml/dom/nodelist.hpp>

namespace borg {
namespace xml {
namespace dom {

//---------------------------------------------------------------------------
#define XML_DOM_INTERFACE(name) \
  template<class Traits, class Derived> \
  struct name ## _interface

//---------------------------------------------------------------------------
XML_DOM_INTERFACE(exception)
{
  XML_DOM_TYPES(typename Traits)

  string_t<Traits, char_type>
  message() const
  {
    return exception_impl<Traits>::message(dereference_cast<Derived const>(this));
  }
};

} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_DOM_INTERFACE_HPP
