#ifndef BORG_WX_DC_HPP
#define BORG_WX_DC_HPP

#include <wx/wx.h>

#include <borg/wrap/wrapper_facade.hpp>
#include <borg/tk/impl.hpp>
#include <borg/tk/wrappers.hpp>
#include <borg/wx.hpp>
#include <borg/wx/dc_adapter.hpp>

class wxPaintDC;
class wxClientDC;
  
// declare instantiable stuff in namespace "tk" as specialization of the templates..
namespace borg {
namespace wx {
  
/*enum drawstyle
{
  draw_stroke,
  draw_fill,
  draw_stroke_and_fill = dra
};*/
  
  
} // namespace wx   
namespace tk {

  
//---------------------------------------------------------------------------
template<>
class paint_dc<wx::traits> :
  public wxPaintDC,
  public tk::dc_adapter< wx::traits, paint_dc<wx::traits> >,
  public borg::wrapper_facade< paint_dc<wx::traits>, borg::wrap_traits<wxPaintDC *> >
{
public:
  typedef wxPaintDC *value_type;

  paint_dc(borg::wx::traits::widget_type &w)
    : wxPaintDC(&w)
  {}

  value_type 
  get() const 
  {
    return const_cast<wxPaintDC *const>(static_cast<wxPaintDC const *const>(this));
  }
};

//---------------------------------------------------------------------------
template<>
  class client_dc<wx::traits> : 
  public wxClientDC,
  public tk::dc_adapter<
      wx::traits,
      client_dc<wx::traits> 
  >,
  public borg::wrapper_facade< 
    client_dc<wx::traits>, 
    borg::wrap_traits<wxClientDC *> 
  >
{
public:
  typedef wxClientDC *value_type;
  
  client_dc(borg::wx::traits::widget_type &w) : wxClientDC(&w) {}

  value_type
  get() const 
  {
    return const_cast<wxClientDC *const>(static_cast<wxClientDC const *const>(this));
  }
};

} // namespace tk

namespace wx {
  
  typedef tk::paint_dc<traits> paint_dc;
  typedef tk::client_dc<traits> client_dc;

} // namespace wx
} // namespace borg

//---------------------------------------------------------------------------
#endif // BORG_WX_DC_HPP
