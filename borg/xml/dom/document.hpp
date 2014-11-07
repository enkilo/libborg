#ifndef BORG_XML_DOM_DOCUMENT_HPP
#define BORG_XML_DOM_DOCUMENT_HPP

#include <borg/xml/dom/types.hpp>
#include <borg/xml/dom/forward.hpp>
#include <borg/string.hpp>
#include <borg/xml/xpath/evaluator.hpp>
#include <borg/util/dereference_cast.hpp>

namespace borg {
namespace xml {
namespace dom {

//---------------------------------------------------------------------------
//! Document interface.
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct document_interface 
    : node_interface<Traits, Derived>
//    , xpath::evaluator_interface<Traits, Derived>
{
  XML_DOM_TYPES(typename Traits)

  typedef document_impl<Traits> impl;
    
  nodelist_t< Traits, element_t<Traits> >
  get_elements_by_tag_name(string<wchar_type, Traits> const &name) const
  {
    return impl::get_elements_by_tag_name
      (dereference_cast<Derived const>(this), name);
  }

  nodelist_t< Traits, element_t<Traits> >
  get_elements_by_tag_name(const wchar_type *name) const
  {
    return impl::get_elements_by_tag_name
      (dereference_cast<Derived const>(this), name);
  }

//  template< template<class, class> class StringT >
  node_t<Traits>
  get_element_by_id(const string<wchar_type, Traits> &name) const
  {
    return impl::get_element_by_id
      (dereference_cast<Derived const>(this), name);
  }

/*  node_t<Traits>
  get_element_by_id(const wchar_type *name) const
  {
    return impl::get_element_by_id
      (dereference_cast<Derived const>(this), name);
  }*/

  //! Create a new element.
  //-----------------------------------------------------------------------
  element_t<Traits>
  create_element(const string<wchar_type, Traits> &name) const
  {
    return impl::create_element
      (dereference_cast<Derived const>(this), name);
  }
  
  //! Create a new text node.
  //-----------------------------------------------------------------------
  text_t<Traits>
  create_text_node(const string<wchar_type, Traits> &data) const
  {
    return impl::create_text_node
      (dereference_cast<Derived const>(this), data);
  }
  
  //! Create a new comment node.
  //-----------------------------------------------------------------------
  comment_t<Traits>
  create_comment(const string<wchar_type, Traits> &data) const
  {
    return impl::create_comment
      (dereference_cast<Derived const>(this), data);
  }
  
  //! Create a new attribute node.
  //-----------------------------------------------------------------------
  attribute_t<Traits>
  create_attribute(const string<wchar_type, Traits> &name) const
  {
    return impl::create_attribute
      (dereference_cast<Derived const>(this), name);
  }
  
  //! Gets the character encoding.
  //-----------------------------------------------------------------------
  string_t<wchar_type, Traits>
  get_encoding() const
  {
    return impl::get_encoding
      (dereference_cast<Derived const>(this));
  }
  
  string_t<wchar_type, Traits>
  get_actual_encoding() const
  {
    return impl::get_actual_encoding
      (dereference_cast<Derived const>(this));
  }
  
  //! Sets the character encoding.
  //-----------------------------------------------------------------------
  void
  set_encoding(const string<wchar_type, Traits> &str) const
  {
    return impl::set_encoding
      (dereference_cast<Derived const>(this), str);
  }
  
  void
  set_actual_encoding(const string<wchar_type, Traits> &str) const
  {
    return impl::set_actual_encoding
      (dereference_cast<Derived const>(this), str);
  }
  
  //! Get root element.
  //-----------------------------------------------------------------------
  element_t<Traits>
  root() const
  {
    return impl::root
      (dereference_cast<Derived const>(this));
  }
};

//---------------------------------------------------------------------------
//! Document facade.
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct document_facade
{
};

//---------------------------------------------------------------------------
template<class Traits>
class document_t 
    : public wrapper<typename Traits::document_type>
    , public document_interface< Traits, document_t<Traits> >
    , public document_facade< Traits, document_t<Traits> >
{
public:
  XML_DOM_TYPES(typename Traits)

  typedef document_impl<Traits> impl;
  typedef wrapper<document_type> base_type;

  document_t()
    : base_type(0)
  {}
  
  document_t(document_type const &doc)
    : base_type(doc)
  {}
};


} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_DOM_DOCUMENT_HPP
