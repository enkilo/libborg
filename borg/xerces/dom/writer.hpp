#ifndef BORG_XERCES_DOM_WRITER_HPP
#define BORG_XERCES_DOM_WRITER_HPP

#include <borg/xerces/traits.hpp>
#include <borg/xml/dom/node.hpp>

namespace borg { 
namespace xml { 
namespace dom {

//---------------------------------------------------------------------------
template<>
struct writer_impl<xerces::traits>
{
  XML_DOM_TYPES(xerces::traits)

  //! Get/set the character encoding.
  //-----------------------------------------------------------------------
  template<class WriterT>
  static const wchar_type *
  get_encoding(WriterT const &writer)
  {
    return writer->getEncoding();
  }
  
  template<class WriterT, class StringT>
  static void
  set_encoding(const WriterT &writer, const StringT &str)
  {
    return writer->setEncoding(str);
  }  
  
  //! Get/set features.
  //-----------------------------------------------------------------------
  template<class WriterT, class StringT>
  static bool
  get_feature(WriterT const &writer, const StringT &str)
  {
    return writer->getFeature(str);
  }
  
  template<class WriterT, class StringT>
  static void
  set_feature(WriterT const &writer, const StringT &str, bool state)
  {
    return writer->setFeature(str, state);
  }
  
  //! Write a node to the specified format target.
  //-----------------------------------------------------------------------
  template<class WriterT, class FormatTarget, class Node>
  static status_type
  write(const WriterT &writer, const FormatTarget &t, const Node &n)
  {
    writer->writeNode(t, *(node_type)n);
    return status_type();
  }
  
  //! Write a node to the specified format target.
  //-----------------------------------------------------------------------
  template<class WriterT, class StringT>
  static void
  set_newline(const WriterT &writer, const StringT &nl)
  {
    writer->setNewLine(nl);
  }

  template<class WriterT>
  static const wchar_type *
  get_newline(const WriterT &writer)
  {
    return writer->getNewLine();
  }
};
  
//---------------------------------------------------------------------------

} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XERCES_DOM_WRITER_HPP
