#ifndef BORG_XML_DOM_IDREFLIST_HPP
#define BORG_XML_DOM_IDREFLIST_HPP

#include <borg/xml/dom/element.hpp>
#include <borg/xml/dom/document.hpp>
#include <borg/util/exception.hpp>
#include <boost/tokenizer.hpp>
#include <boost/iterator/iterator_facade.hpp>
  
namespace borg {
namespace xml {
namespace dom {

//---------------------------------------------------------------------------
template<class Traits, class ListT>
struct idreflist_impl
{
  BORG_PP_USE_TYPE(typename Traits, document_type)
  BORG_PP_USE_TYPE(typename Traits, wchar_type)
  
  typedef boost::char_separator<wchar_type> separator_type;
  
  typedef boost::tokenizer
  <
      separator_type
    , typename ListT::const_iterator
    , std::string
//    , typename boost::remove_const<ListT>::type
  > tokenizer_type;

  BORG_PP_USE_TYPE(typename tokenizer_type, iterator)
  BORG_PP_USE_TYPE(typename tokenizer_type, const_iterator)
  
  static const_iterator
  begin (tokenizer_type const &toks) { return toks.begin(); }
  
  static iterator
  begin (tokenizer_type       &toks) { return toks.begin(); }
  
  static const_iterator
  end   (tokenizer_type const &toks) { return toks.end(); }
  
  static iterator
  end   (tokenizer_type       &toks) { return toks.end(); }
};

//---------------------------------------------------------------------------
template<class Traits, class ListT>
struct idreflist_iterator
    : public boost::iterator_facade
      <
          idreflist_iterator<Traits, ListT>
        , element_t<Traits>
        , boost::forward_traversal_tag
      >
{
  typedef idreflist_impl<Traits, ListT> impl;
  typedef element_t<Traits> value_type;

  BORG_PP_USE_TYPE(typename impl, tokenizer_type);
  BORG_PP_USE_TYPE(typename impl, iterator);
  BORG_PP_USE_TYPE(typename impl, const_iterator);

  typedef string_t<typename Traits::wchar_type, Traits> string_type;
  
  idreflist_iterator(const_iterator const &it, document_t<Traits> const &doc)
    : m_iter(it)
    , m_doc(doc)
  {
  }

  template<class ListU>
  idreflist_iterator(idreflist_iterator<Traits, ListU> const &it)
    : m_iter(*reinterpret_cast< idreflist_iterator<Traits, ListT> const * >(&it))
    , m_doc(it.get_document())
  {
  }

  void
  increment()
  {
    ++m_iter;
  }
  
  bool
  equal(idreflist_iterator<Traits, ListT> const &it) const
  {
    return m_iter == it.m_iter;
  }

/*  template<class ListU>
  bool
  equal(idreflist_iterator<Traits, ListU> const &it) const
  {
    return m_iter == it;
  }*/

  element_t<Traits> &
  dereference() const
  {
    m_elm = m_doc.get_element_by_id((*m_iter).c_str());
    return m_elm;
  }
  
//  string_type
  std::string
  ref() const
  {
    return *m_iter;
  }
  
  operator const_iterator const &() const { return m_iter; }
  operator const_iterator       &()       { return m_iter; }
  
  document_t<Traits> const &get_document() const { return m_doc; }
  
private:
  const_iterator m_iter;
  document_t<Traits> m_doc;
  mutable element_t<Traits> m_elm;
};
  
//---------------------------------------------------------------------------
//! ID reference list interface.
//---------------------------------------------------------------------------
template<class Traits, class Derived, class ListT>
struct idreflist_interface
{
  typedef idreflist_impl<Traits, ListT> impl;
  
  typedef idreflist_iterator<Traits, ListT> iterator;
  typedef idreflist_iterator<Traits, ListT const> const_iterator;
  
  iterator
  begin() 
  { 
    return iterator
      (impl::begin(dereference_cast<Derived>(this).get_tokenizer()),
                   dereference_cast<Derived>(this).get_document());
  }
  
  const_iterator
  begin() const
  { 
    return const_iterator
      (impl::begin(dereference_cast<Derived const>(this).get_tokenizer()),
                   dereference_cast<Derived const>(this).get_document());
  }
  
  iterator
  end() 
  { 
    return iterator
      (impl::end(dereference_cast<Derived>(this).get_tokenizer()), 
                 dereference_cast<Derived>(this).get_document());
  }
  
  const_iterator
  end() const
  { 
    return const_iterator
      (impl::end(dereference_cast<Derived const>(this).get_tokenizer()), 
                 dereference_cast<Derived const>(this).get_document());
  }
  
};  
  
//---------------------------------------------------------------------------
template<class Traits, class Derived, class ListT>
struct idreflist_facade
{
  XML_DOM_TYPES(typename Traits)

  typedef idreflist_impl<Traits, ListT> impl;
  
};
  
//---------------------------------------------------------------------------
template<class Traits, class ListT = string<typename Traits::wchar_type, Traits> >
struct idreflist_t
    : public idreflist_interface <Traits, idreflist_t<Traits, ListT>, ListT>
    , public idreflist_facade    <Traits, idreflist_t<Traits, ListT>, ListT>
{
  XML_DOM_TYPES(typename Traits)
    
  typedef idreflist_impl<Traits, ListT> impl;
  typedef element_t<Traits> value_type;

  BORG_PP_USE_TYPE(typename impl, tokenizer_type);

  idreflist_t(ListT const &list, document_t<Traits> const &doc)
    : m_list(list)
    , m_sep((typename Traits::wchar_type const *)" \0\0\0\0\0\0\0",
            (typename Traits::wchar_type const *)"\0\0\0\0")
    , m_toks(m_list, m_sep)
    , m_doc(doc)
  {
  }
  
  template<class ListU>
  idreflist_t(idreflist_t<Traits, ListU> const &reflist)
    : m_list(reflist)
    , m_sep((typename Traits::wchar_type const *)" \0\0\0\0\0\0\0",
            (typename Traits::wchar_type const *)"\0\0\0\0")
    , m_toks(m_list, m_sep)
    , m_doc(reflist.get_document())
  {
  }
  
  idreflist_t(attribute_t<Traits> const &ref)
    : m_list(ref.value())
    , m_sep((typename Traits::wchar_type const *)" \0\0\0\0\0\0\0",
            (typename Traits::wchar_type const *)"\0\0\0\0")
    , m_toks(m_list, m_sep)
    , m_doc(ref.owner_document())
  {
  }
  
  operator ListT() const
  {
    return m_list;
  }
  
  //! \name Get document.
  //-------------------------------------------------------------------
  //@{
  document_t<Traits> const &
  get_document() const { return m_doc; }

  document_t<Traits> &
  get_document() { return m_doc; }
  //@}
  
  //! \name Get tokenizer.
  //-------------------------------------------------------------------
  //@{
  tokenizer_type const &
  get_tokenizer() const { return m_toks; }

  tokenizer_type &
  get_tokenizer() { return m_toks; }
  //@}

private:
  ListT m_list;
  boost::char_separator<typename Traits::wchar_type> m_sep;
  tokenizer_type     m_toks;
  document_t<Traits> m_doc;
};
  
//---------------------------------------------------------------------------

} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_DOM_IDREFLIST_HPP
