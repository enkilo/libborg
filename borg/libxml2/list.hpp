#ifndef BORG_LIBXML2_LIST_HPP
#define BORG_LIBXML2_LIST_HPP

#include <borg/libxml2/traits.hpp>
#include <borg/abstract/list.hpp>

namespace borg {

//----------------------------------------------------------------------------
template<class T>
class list_impl< libxml2::traits, T >
{
public:
  BORG_ABSTRACT_LIST_TYPES( libxml2::traits )

  static list_type
  create()
  {
    return xmlListCreate(0, 0);
  }

  //-------------------------------------------------------------------
  // Create a new list.
  //-------------------------------------------------------------------
  static list_type
  create(deallocator_type const dealloc, comparator_type const comp)
  {
    return xmlListCreate(dealloc, comp);
  }
  
  //-------------------------------------------------------------------
  // Destroy a list.
  //-------------------------------------------------------------------
  static void
  destroy(list_type const list)
  {
    return xmlListDelete(list);
  }
  
  //-------------------------------------------------------------------
  // Search for an item within a list.
  //-------------------------------------------------------------------
  static T
  search(list_type const list, T item)
  {
    return xmlListSearch(list, item);
  }
  
  //-------------------------------------------------------------------
  // Search for an item within a list, starting at the tail.
  //-------------------------------------------------------------------
  static T
  reverse_search(list_type const list, T item)
  {
    return xmlListReverseSearch(list, item);
  }

  //-------------------------------------------------------------------
  // Insert an item to the beginning of a list.
  //-------------------------------------------------------------------
  static int
  insert(list_type const list, T item)
  {
    return xmlListInsert(list, item);
  }

  //-------------------------------------------------------------------
  // Append an item to the end of a list.
  //-------------------------------------------------------------------
  static int
  append(list_type const list, T item)
  {
    return xmlListAppend(list, item);
  }

};

//---------------------------------------------------------------------------

namespace libxml2 {

template<class T>
class list_t : public borg::list_t<traits, T> {};
  
template<class T>
class list : public borg::list<traits, T> {};
  
    
}// namespace libxml2
}// namespace borg
//---------------------------------------------------------------------------

#endif //ndef BORG_LIBXML2_LIST_HPP
