#ifndef BORG_WX_ARRAY_HPP
#define BORG_WX_ARRAY_HPP

#include <borg/array.hpp>
#include <borg/wx/traits.hpp>

namespace borg {

//----------------------------------------------------------------------------
template<class ConstIterator, class Iterator>
class sequence_impl<wxArrayShort, ConstIterator, Iterator, wx::traits >
{
public:
//  typedef Sequence array_type;

  //----------------------------------------------------------------------------
  static Iterator      begin(wxArrayShort &arr)       { return arr.begin(); }
  static ConstIterator begin(wxArrayShort const &arr) { return arr.end(); }
  
  //----------------------------------------------------------------------------
  static Iterator      end(wxArrayShort &arr)       { return arr.begin(); }
  static ConstIterator end(wxArrayShort const &arr) { return arr.end(); }
};

//----------------------------------------------------------------------------
template<class T>
class array_impl< T, wx::traits >
{
public:
  typedef typename wx::traits::array<T>::type array_type;
  BORG_PP_USE_TYPE(wx::traits, index_type)

  //-------------------------------------------------------------------
  //! Return the number of items in the array.
  //-------------------------------------------------------------------
  template<class Array>
  static index_type
  size(const Array &arr)
  {
    return arr->GetCount();
  }
  
  //-------------------------------------------------------------------
  template<class Array>
  static void
  push_back(Array &arr, const T &val)
  {
    arr->Add(val);
  }
  
};

//----------------------------------------------------------------------------
namespace wx {

template<class T> 
struct array_t : borg::array_t<T, traits> 
{
  typedef borg::array_t<T, traits> base_type;
  array_t() : base_type() {}
  template<class U> array_t(U arg) : base_type(arg) {}  
};
  
template<class T>
struct array : borg::array<T, traits> 
{
  typedef borg::array<T, traits> base_type;
  array() : base_type() {}
  template<class U> array(U arg) : base_type(arg) {}  
};
  
} // namespace wx
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_WX_ARRAY_HPP
