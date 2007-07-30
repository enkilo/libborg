#ifndef BORG_WX_LISTBOX_HPP
#define BORG_WX_LISTBOX_HPP

#include <wx/listbox.h>

#include <borg/wx.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/tk/listbox.hpp>

namespace borg { 
namespace tk {

//----------------------------------------------------------------------------
template<>
struct listbox_impl<wx::traits>
{
  BORG_TK_LISTBOX_TYPES(wx::traits)

  enum style
  {
    single    = wxLB_SINGLE,    //!< Single-selection list.
    multiple  = wxLB_MULTIPLE,  //!< Multiple-selection list: the user can 
                                //!< toggle multiple items on and off.
    extended  = wxLB_EXTENDED,  //!< Extended-selection list: the user can select
                                //!< multiple items using the SHIFT key and the
                                //!< mouse or special key combinations.
    hscroll   = wxLB_HSCROLL,   //!< Create horizontal scrollbar if contents are
                                //!< too wide (Windows only).
    always_sb = wxLB_ALWAYS_SB, //!< Always show a vertical scrollbar.
    needed_sb = wxLB_NEEDED_SB, //!< Only create a vertical scrollbar if needed.
    sort      = wxLB_SORT,      //!< The listbox contents are sorted in alphabetical order.
  };
  
/*  static point_type     default_pos = wxDefaultPosition;
  static size_type      default_size = wxDefaultSize;
  static validator_type default_validator = wxDefaultValidator;*/
    
  //-------------------------------------------------------------------
  static void
  deselect(listbox_type &listbox, index_type n)
  {
    listbox.Deselect(n);
  }

  //-------------------------------------------------------------------
  static index_type
  get_selections(const listbox_type &listbox, int_array_type &selections)
  {
    return listbox.GetSelections(selections);
  }
  
  //-------------------------------------------------------------------
  static void
  insert_items(listbox_type &listbox, index_type n_items, 
               const string_type items[], index_type pos)
  {
    listbox.InsertItems(n_items, items, pos);
  }

  //-------------------------------------------------------------------
  static void
  insert_items(listbox_type &listbox, const string_array_type &items, 
               index_type pos)
  {
    listbox.InsertItems(items, pos);
  }
  
  //-------------------------------------------------------------------
  static index_type
  hit_test(const listbox_type &listbox, const point_type &point)
  {
    return listbox.HitTest(point);
  }
  
  //-------------------------------------------------------------------
  static bool
  is_selected(const listbox_type &listbox, index_type n)
  {
    return listbox.IsSelected(n);
  }
  
  //-------------------------------------------------------------------
  static void
  set(listbox_type &listbox, index_type n, const string_type choices[],
      void *client_data[] = 0)
  {
    listbox.Set(n, choices, client_data);
  }

  //-------------------------------------------------------------------
  static void
  set(listbox_type &listbox, const string_array_type &choices, 
      void **client_data = 0)
  {
    listbox.Set(choices, client_data);
  }
  
  //-------------------------------------------------------------------
  static void
  set_first_item(listbox_type &listbox, index_type n)
  {
    listbox.SetFirstItem(n);
  }
  
  //-------------------------------------------------------------------
  static void
  set_first_item(listbox_type &listbox, const string_type &str)
  {
    listbox.SetFirstItem(str);
  }
                 
  // wxControlWithItems::GetCount
  //-------------------------------------------------------------------
  static index_type
  count(const listbox_type &listbox)
  {
    listbox.GetCount();
  }
                 
  // wxControlWithItems::Append
  //-------------------------------------------------------------------
  static index_type
  append(listbox_type &listbox, const string_type &item)
  {
    return listbox.Append(item);
  }
};

//----------------------------------------------------------------------------
template<class Derived>
struct listbox_facade<wx::traits, Derived>
{
  BORG_TK_LISTBOX_TYPES(wx::traits)
};
  
//----------------------------------------------------------------------------
template<>
class listbox<wx::traits>
    : public listbox_interface< wx::traits, listbox<wx::traits> >
    , public listbox_facade< wx::traits, listbox<wx::traits> >
{
public:
  BORG_TK_LISTBOX_TYPES(wx::traits)

  typedef wrapper<wx::traits::listbox_type> base_type;
  typedef listbox<wx::traits> this_type;
  
  //! Wrapper constructor.
  listbox(widget_type &parent, id_type id = wx::default_id, 
          const point_type &pos = wx::default_position,
          const size_type &size = wx::default_size, index_type n = 0, 
          const string_type choices[] = 0, style_type style = 0,
          const validator_type &val = wx::default_validator, 
          const string_type &name = "listbox")
    : m_listbox(&parent, id, pos, size, n, choices, style, val, name)
  {}

  listbox(widget_type &parent, id_type id = wx::default_id, 
          const point_type &pos = wx::default_position,
          const size_type &size = wx::default_size, 
          const string_array_type &choices = string_array_type(), style_type style = 0,
          const validator_type &val = wx::default_validator, 
          const string_type &name = "listbox")
    : m_listbox(&parent, id, pos, size, choices, style, val, name)
  {}

  ~listbox()
  {
  }
  
  operator const listbox_type &() const { return m_listbox; }
  operator listbox_type &() { return m_listbox; }
  
  const listbox_type *
  operator->() const { return &m_listbox; }
  listbox_type *
  operator->() { return &m_listbox; }
    
  
private:
  wxListBox m_listbox;
  
  this_type &
  operator=(const this_type &);

  listbox(const this_type &);
};
  
}// namespace tk

//---------------------------------------------------------------------------
namespace wx {

typedef tk::listbox_t<traits> listbox_t;
typedef tk::listbox<traits> listbox;

} // namespace wx
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_WX_LISTBOX_HPP
