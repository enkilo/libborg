#ifndef BORG_XML_DOM_IDREF_HPP
#define BORG_XML_DOM_IDREF_HPP

/*#include <boost/iterator/iterator_facade.hpp>
#include <borg/wrap/preproc.hpp>
#include <borg/util/dereference_cast.hpp>
#include <borg/xml/lib/adapter.hpp>
#include <borg/xml/dom/forward.hpp>*/
#include <borg/xml/dom/element.hpp>
#include <borg/xml/dom/document.hpp>
#include <borg/util/exception.hpp>
  
namespace borg {
namespace xml {
namespace dom {

//WRAP_PATTERN_FORWARD(idref, (class RefT))
  
//---------------------------------------------------------------------------
template<class Traits, class RefT = string<typename Traits::wchar_type, Traits> >
struct idref_t;

//---------------------------------------------------------------------------
template<class Traits>
struct idref_impl
{
  BORG_PP_USE_TYPE(typename Traits, document_type)
  BORG_PP_USE_TYPE(typename Traits, wchar_type)
  
  static element_t<Traits>
  dereference(document_type doc, string<wchar_type, Traits> const &idref)
  {
    return document_impl<Traits>::get_element_by_id(doc, idref);
  }
  
};

//---------------------------------------------------------------------------
//! ID reference interface.
//---------------------------------------------------------------------------
template<class Traits, class Derived, class RefT>
struct idref_interface
{
//  XML_DOM_TYPES(typename Traits)

  typedef idref_impl<Traits> impl;
  
  idref_interface() : m_elm(0)
  {
  }
  
  element_t<Traits> &
  dereference()
  {
    if(!m_elm)
    {
      m_elm = impl::dereference(
          dereference_cast<Derived const>(this).get_document()
        , dereference_cast<Derived const>(this)
      );
    }
    
    if(!m_elm)
      throw borg::exception<Traits>("invalid reference");
    
    return *reinterpret_cast<element_t<Traits> *>(&m_elm);
  }
  
protected:
  node_t<Traits> m_elm;
};  
  
//---------------------------------------------------------------------------
template<class Traits, class Derived, class RefT>
struct idref_facade
{
  XML_DOM_TYPES(typename Traits)

  typedef idref_impl<Traits> impl;
  
  element_t<Traits>
  operator*() const
  {
    return const_cast<Derived *>(static_cast<Derived const *>(this))->dereference();
  }  
  
  element_t<Traits> *
  operator->() const
  {
    return boost::addressof(const_cast<Derived *>(static_cast<Derived const *>(this))->dereference());
  }

};
  
//---------------------------------------------------------------------------
//template<class Traits, class RefT = string<typename Traits::wchar_type, Traits> >
template<class Traits, class RefT>
struct idref_t
    : public wrapper<RefT>
    , public idref_interface<Traits, idref_t<Traits, RefT>, RefT>
    , public idref_facade<Traits, idref_t<Traits, RefT>, RefT>
{
  XML_DOM_TYPES(typename Traits)

  typedef wrapper<RefT> base;
  typedef idref_impl<Traits> impl;
  typedef element_t<Traits> value_type;
  
  idref_t(RefT const &ref, document_type const &doc) 
    : base(ref)
    , m_doc(doc)
  {}
  
  idref_t(attribute_t<Traits> const &ref)
    : base(ref.value())
    , m_doc(ref.owner_document())
  {}
  
  template<class T>
  idref_t(const idref_t<Traits, T> &idref)
    : base(idref)
  {}
  
  document_type const &
  get_document() const { return m_doc; }

  document_type &
  get_document() { return m_doc; }

  RefT
  get_ref() const { return *this; }
  
private:
  document_type m_doc;
};
  
//---------------------------------------------------------------------------

} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_DOM_NODELIST_HPP
