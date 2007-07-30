#ifndef BORG_GCCXML_ITERATOR_HPP
#define BORG_GCCXML_ITERATOR_HPP

#include <borg/gccxml/traits.hpp>
#include <borg/ast/iterator.hpp>
#include <borg/util/exception.hpp>
#include <borg/xml/dom/node.hpp>

namespace borg {
namespace ast  {

//! Iterator implementation for nodelists.
template<class XmlTraits>
struct iterator_impl
< 
    gccxml::traits<XmlTraits>
  , typename gccxml::traits<XmlTraits>::node_type
  , typename gccxml::traits<XmlTraits>::sequence_type
>
{
  typedef gccxml::traits<XmlTraits>  traits;
  typedef typename traits::node_type value_type;

  BORG_PP_USE_TYPE(typename traits, sequence_type)
  BORG_PP_USE_TYPE(typename sequence_type, iterator)
  BORG_PP_USE_TYPE(typename sequence_type, const_iterator)
  
  static value_type const &
  dereference(const_iterator const &it)
  {
    return *reinterpret_cast<value_type const *>(&(*it));
  }
  
  static value_type &
  dereference(iterator const &it)
  {
    return *reinterpret_cast<value_type *>(&(*it));
  }
  
  static bool
  equal(const iterator &it1, const iterator &it2)
  {
    return (it1 == it2) || (*it1 == 0 && *it2 == 0);
  }
  
  static void
  increment(iterator &it)
  {
    do
    {
      ++it;
    } while(*it && (*it).type() != xml::dom::element_node);
  }
  
  static void
  decrement(iterator &it)
  {
    --it;
  }
  
};

//! Iterator implementation for an attribute whose value contains a list of id tokens.
template<class XmlTraits, class T>
struct iterator_impl< gccxml::traits<XmlTraits>, T, typename gccxml::traits<XmlTraits>::members_type >
{
  typedef gccxml::traits<XmlTraits> traits;
//  typedef T value_type;

//  BORG_PP_USE_TYPE(typename traits, tokenizer_type)
  BORG_PP_USE_TYPE(typename traits, members_type)
  BORG_PP_USE_TYPE(typename members_type, iterator)
  BORG_PP_USE_TYPE(typename members_type, const_iterator)
  BORG_PP_USE_TYPE(typename members_type, value_type)

  static void
  increment(iterator &it)
  {
//    std::cout << "token: " << *it << std::endl;
    ++it;
  }
  
  static value_type
  dereference(iterator const &it)
  {
    return *it;
//    return T();
  }
  
  static bool
  equal(iterator const &it1, iterator const &it2)
  {
    return it1 == it2;
  }
  
  
};

//----------------------------------------------------------------------------
}// namespace ast
}// namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_GCCXML_NODE_HPP
