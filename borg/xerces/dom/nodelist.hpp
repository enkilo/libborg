#ifndef BORG_XERCES_DOM_NODELIST_HPP
#define BORG_XERCES_DOM_NODELIST_HPP

#include <borg/xerces/traits.hpp>
#include <borg/xml/dom/nodelist.hpp>

namespace borg {
namespace xml {
namespace dom {

//----------------------------------------------------------------------------
template<>
struct nodelist_impl<xerces::traits>
{
  XML_DOM_TYPES(xerces::traits)
  
  //------------------------------------------------------------------------
  //! Returns the nth item in the node list.
  //------------------------------------------------------------------------
  template<typename NodeListT>
  static node_type
  item(NodeListT const &list, index_type n)
  {
    return list->item(n);
  }
  
  //------------------------------------------------------------------------
  //! Returns the size of the node list.
  //------------------------------------------------------------------------
  template<typename NodeListT>
  static length_type
  size(NodeListT const &list)
  {
    return list->getLength();
  }
};

//---------------------------------------------------------------------------

} // namespace dom
} // namespace xml
} // namespace borg

#endif //ndef BORG_XERCES_DOM_NODELIST_HPP
