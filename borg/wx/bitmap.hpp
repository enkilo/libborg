#ifndef BORG_WX_BITMAP_HPP
#define BORG_WX_BITMAP_HPP

#include <borg/tk/impl.hpp>
#include <borg/tk/wrappers.hpp>
#include <borg/wx/bitmap_adapter.hpp>

namespace borg {
namespace tk {

//---------------------------------------------------------------------------
template<>
class bitmap<wx::traits> : 
  public wxBitmap,
  public tk::bitmap_adapter< wx::traits, bitmap<wx::traits> >
{
public:
  typedef wx::traits tk_type;
  typedef wxBitmap *value_type;
  typedef bitmap_wrapper<tk_type> bitmap_type;

  bitmap(const vector_type &w, const vector_type &h) : wxBitmap(w, h) {}

  const wxBitmap *get() const { return this; }
  wxBitmap *get() { return this; }
};
  
//---------------------------------------------------------------------------
} // namespace tk
namespace wx { 
  typedef tk::bitmap<traits> bitmap; 
} // namespace wx
} // namespace borg

//---------------------------------------------------------------------------
#endif // BORG_WX_BITMAP_HPP

