#ifndef BORG_TK_LISTBOX_HPP
#define BORG_TK_LISTBOX_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>

#define BORG_TK_LISTBOX_TYPES(Traits) \
    BORG_PP_USE_TYPE(Traits, listbox_type) \
    BORG_PP_USE_TYPE(Traits, widget_type) \
    BORG_PP_USE_TYPE(Traits, point_type) \
    BORG_PP_USE_TYPE(Traits, index_type) \
    BORG_PP_USE_TYPE(Traits, size_type) \
    BORG_PP_USE_TYPE(Traits, id_type) \
    BORG_PP_USE_TYPE(Traits, style_type) \
    BORG_PP_USE_TYPE(Traits, string_type) \
    BORG_PP_USE_TYPE(Traits, int_array_type) \
    BORG_PP_USE_TYPE(Traits, string_array_type) \
    BORG_PP_USE_TYPE(Traits, validator_type)

//---------------------------------------------------------------------------
namespace borg {
namespace tk {

WRAP_PATTERN_FORWARD(listbox)
    
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct listbox_interface : listbox_impl<Traits>
{
  BORG_TK_LISTBOX_TYPES(typename Traits)
  
  typedef listbox_impl<Traits> impl;

  //-------------------------------------------------------------------
  //! Constructs a listbox widget.
  //-------------------------------------------------------------------

  /*listbox_type
  create(const widget_type &parent, id_type id, const point_type &pos = default_position,
         index_type n, const string_type choices[] = 0, style_type style,
         const validator_type &validator = default_validator, 
         const string_type &name = "listbox")
  {
  }*/
  
  
  //-------------------------------------------------------------------
  //! Determines whether an item is selected.
  //-------------------------------------------------------------------
  bool
  is_selected(const index_type &n) const
  { 
    return impl::is_selected
      (dereference_cast<Derived const>(this), n); 
  }
  
  //-------------------------------------------------------------------
  //! Deselects an item in the list box.
  //-------------------------------------------------------------------
  void
  deselect(const index_type &n)
  {
    return impl::deselect
      (dereference_cast<Derived>(this), n);
  }
  
  //-------------------------------------------------------------------
  //! Fill an array of ints with the positions of the currently
  //! selected items.
  //-------------------------------------------------------------------
  int
  get_selections(int_array_type &selections) const
  {
    return impl::get_selections
      (dereference_cast<Derived const>(this));
  }
  
  //-------------------------------------------------------------------
  //! Insert the given number of strings before the specified position.
  //-------------------------------------------------------------------
  void
  insert_items(const index_type &n, const string_type &items, 
               const size_type &pos)
  {
    return impl::insert_items
      (dereference_cast<Derived>(this), n, items, pos);
  }

  //-------------------------------------------------------------------
  //! Returns the item located at point, or listbox::not_found if there
  //! is no item located at point.
  //-------------------------------------------------------------------
  index_type
  hit_test(const point_type &point) const
  {
    return impl::hit_test
      (dereference_cast<Derived const>(this), point);
  }

  //-------------------------------------------------------------------
  //! Clears the list box and adds the given strings to it.
  //-------------------------------------------------------------------
  void
  set(const index_type &n, const string_type &choices, 
      void **client_data = 0)
  {
  }

  //-------------------------------------------------------------------
  void
  set(const string_array_type &choices, void **client_data = 0)
  {
    impl::set
      (dereference_cast<Derived>(this), choices, client_data);
  }
  
  //-------------------------------------------------------------------
  void
  set_first_item(const string_type &str)
  {
    impl::set_first_item
      (dereference_cast<Derived>(this), str);
  }
  
  //-------------------------------------------------------------------
  index_type
  count() const
  {
    return impl::count
      (dereference_cast<Derived const>(this));
  }
  
  //-------------------------------------------------------------------
  index_type
  append(const string_type &str)
  {
    return impl::append
      (dereference_cast<Derived>(this), str);
  }
  
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct listbox_facade
{
};
  
//---------------------------------------------------------------------------
template<class Traits>
class listbox_t
    : public wrapper< typename Traits::listbox_type >
    , public listbox_interface< Traits, listbox_t<Traits> >
    , public listbox_facade< Traits, listbox_t<Traits> >
{
public:
  BORG_TK_LISTBOX_TYPES(typename Traits)

  typedef wrapper<listbox_type> base_type;

  listbox_t(listbox_type const &v) 
    : base_type(v) 
  {}

  template<template<class> class Adapter>
  listbox_t(Adapter<Traits> const &a)
    : base_type(a)
  {}
};

} // namespace tk
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_TK_LISTBOX_HPP
