#ifndef BORG_XERCES_DOM_NODEMAP_HPP
#define BORG_XERCES_DOM_NODEMAP_HPP

#include <borg/xerces/traits.hpp>
#include <borg/xml/dom/nodemap.hpp>

namespace borg {
namespace xml {
namespace dom {

//----------------------------------------------------------------------------
template<>
struct nodemap_impl<xerces::traits>
{
  XML_DOM_TYPES(xerces::traits)
  
  //------------------------------------------------------------------------
  //! Returns the nth item in the node map.
  //------------------------------------------------------------------------
  template<typename NodeMapT>
  static node_type
  item(NodeMapT const &list, index_type n)
  {
    return list->item(n);
  }

  //------------------------------------------------------------------------
  //! Returns the size of the node map.
  //------------------------------------------------------------------------
  template<typename NodeMapT>
  static length_type
  size(NodeMapT const &list)
  {
    return list->getLength();
  }
};

//---------------------------------------------------------------------------

} // namespace dom
} // namespace xml
} // namespace borg

#endif //ndef BORG_XERCES_DOM_NODEMAP_HPP
