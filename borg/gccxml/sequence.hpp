#ifndef BORG_GCCXML_SEQUENCE_HPP
#define BORG_GCCXML_SEQUENCE_HPP

#include <borg/gccxml/traits.hpp>
#include <borg/ast/sequence.hpp>
#include <borg/util/exception.hpp>
#include <boost/tokenizer.hpp>

namespace borg {
namespace ast  {

//----------------------------------------------------------------------------
template<class T, class Sequence, class XmlTraits>
struct sequence_impl< T, Sequence, gccxml::traits<XmlTraits> >
{
  typedef gccxml::traits<XmlTraits> traits;
  typedef xml::dom::element_t<XmlTraits> value_type;
  typedef xml::dom::nodelist_iterator< XmlTraits, value_type > iterator;
  typedef xml::dom::nodelist_iterator< XmlTraits, value_type > const_iterator;
  
  static iterator
  begin(Sequence &seq) { return seq.begin(); }

  static const_iterator
  begin(Sequence const &seq) { return seq.begin(); }

  static iterator
  end(Sequence &seq) { return seq.end(); }
  
  static const_iterator
  end(Sequence const &seq) { return seq.end(); }
  
    
};

//----------------------------------------------------------------------------
//! Sequence represented by an attribute value which contains XML ids.
//----------------------------------------------------------------------------
template<class T, class XmlTraits>
struct sequence_impl
<
    T, 
    typename gccxml::traits<XmlTraits>::members_type, 
    gccxml::traits<XmlTraits> 
>
{
  typedef gccxml::traits<XmlTraits> traits;
  
//  BORG_PP_USE_TYPE(typename traits, tokenizer_type)
  BORG_PP_USE_TYPE(typename traits, members_type)
  BORG_PP_USE_TYPE(typename members_type, const_iterator)
    
  static const_iterator
  begin(members_type const &seq)
  {
    return seq.begin();
  }

  static const_iterator
  end(members_type const &seq)
  {
    return seq.end();
  }
  
    
};

//----------------------------------------------------------------------------

}// namespace ast
}// namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_GCCXML_SEQUENCE_HPP
