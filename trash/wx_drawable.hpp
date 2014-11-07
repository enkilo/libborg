#warning "obsolete"
// Copyright (C) 2007  Roman Senn <r.senn@nexbyte.com>

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the wrapied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
// USA.

// As a special exception, you may use this file as part of a free software
// library without restriction.  Specifically, if other files instantiate
// templates or use macros or inline functions from this file, or you compile
// this file and link it with other files to produce an executable, this
// file does not by itself cause the resulting executable to be covered by
// the GNU General Public License.  This exception does not however
// invalidate any other reasons why the executable file might be covered by
// the GNU General Public License.

#ifndef _cxx_wx_drawable_
#define _cxx_wx_drawable_

#include <wx/dc.h>
#include <wrap/drawable.hpp>

namespace wx
{
  struct font
  {
    wxFontFamily family;
    int size;
  };

  const font fonts[] =
  {
    { wxFONTFAMILY_MODERN, 10 },
    { wxFONTFAMILY_SWISS, 24 },
    { wxFONTFAMILY_SWISS, 16 },
    { wxFONTFAMILY_SWISS, 12 },
    { wxFONTFAMILY_SWISS, 9 },
    { wxFONTFAMILY_SWISS, 7 }  
  };
}


namespace wrap {
  
  template<>
    struct drawable_traits<tk::wx>
  {
    typedef wxDC *wrap_type;
    typedef int vector_type;
    typedef unsigned char color_type;
    typedef abstract::font_type font_type;
    typedef abstract::dc<int, unsigned char> drawable_type;
  };
  
  //! Wraps wxDC class into an implementation of abstract::dc.
  template<>
    class drawable<tk::wx> :
      public wrapper<wxDC *>/*,
      public drawable_traits<wxDC *>::drawable_type*/
  {
  private:
    wxPoint m_penloc;
    wxFont m_font;
    borg::rect<int> m_clip;

  public:
    typedef drawable_traits<tk::wx> traits_type;
    typedef wrapper<wxDC *> wrapper_type;
    typedef traits_type::drawable_type drawable_type;
    typedef traits_type::font_type font_type;

    dc_TYPEDEF(traits_type::vector_type, 
                     traits_type::color_type)
    
    drawable(wxDC *__wxdc) : wrapper<wxDC *>(__wxdc)
    {}

/*    virtual ~drawable() 
    {}*/
    PROTOTYPE(drawable)      
  };

  // move_to(x, y)
  INLINE(drawable, move_to, drawable<tk::wx>::)
  {
    m_penloc.x = x;
    m_penloc.y = y;
  }

  // line_to(x, y)
  INLINE(drawable, line_to, drawable<tk::wx>::)
  { 
    wrapper_type::get().DrawLine(m_penloc.x, m_penloc.y, x, y);
    m_penloc.x = x;
    m_penloc.y = y;
  }
  
  // draw_point(x, y)
  INLINE(drawable, draw_point, drawable<tk::wx>::)
  { 
    wrapper_type::get().DrawPoint(x, y);
  }
  
  // draw_line(s, e)
  INLINE(drawable, draw_line, drawable<tk::wx>::)
  {
    wrapper_type::get().DrawLine(s.x(), s.y(), e.x(), e.y());
  }

  // draw_rect(r)
  INLINE(drawable, draw_rect, drawable<tk::wx>::)
  {
    wrapper_type::get().DrawRectangle(r.x(), r.y(), r.w(), r.h());
  }

  // draw_ellipse(r)
  INLINE(drawable, draw_ellipse, drawable<tk::wx>::)
  {
    wrapper_type::get().DrawEllipse(r.x(), r.y(), r.w(), r.h());
  }

  //! Draw an arc within \a rect, spanning from \a start to \a end.
  inline void 
  drawable<tk::wx>::draw_arc
    (const borg::rect<int> &r, float __s, float __e)
  {
    std::point<int> center = r.center();
    int x1 = static_cast<int>(center.x() + cos(__s) * (r.w() / 2));
    int y1 = static_cast<int>(center.y() + sin(__s) * (r.h() / 2));
    int x2 = static_cast<int>(center.x() + cos(__e) * (r.w() / 2));
    int y2 = static_cast<int>(center.y() + sin(__e) * (r.h() / 2));
    wrapper_type::get().DrawArc(x2, y2, x1, y1, center.x(), center.y());
  }
    
  //! Draw a polygon through the specified points.
  inline void 
  drawable<tk::wx>::draw_polygon(const std::point<int> __pts[], size_t n)
  {
    wxPoint points[n];
    for(size_t i = 0; i < n; i++)
    {
      points[i].x = __pts[i].x();
      points[i].y = __pts[i].y();
    }
    wrapper_type::get().DrawPolygon(n, points);
  }
    
  //! Set clipping region.
  inline void 
  drawable<tk::wx>::set_clip(const borg::rect<int> &r)
  {
    m_clip = r;
    wrapper_type::get().SetClippingRegion
      (r.x(), r.y(), r.w(), r.h());
  }
  
  //! Get clipping region.
  inline borg::rect<int> 
  drawable<tk::wx>::get_clip() const
  {
    return m_clip;
  }
  
  //! Reset clipping region.
  inline void
  drawable<tk::wx>::reset_clip()
  {
    int w, h;
    wrapper_type::get().DestroyClippingRegion();
    wrapper_type::get().GetSize(&w, &h);
    m_clip(0, 0, w, h);
  }
  
  //! Set the draw style.
  inline void 
  drawable<tk::wx>::set_draw_style(int __st)
  {
    wxBrush brush = wrapper_type::get().GetBrush();
    brush.SetStyle((__st & abstract::draw_filled) ? wxSOLID : wxTRANSPARENT);
    wrapper_type::get().SetBrush(brush);

    wxPen pen = wrapper_type::get().GetPen();
    pen.SetStyle((__st & abstract::draw_stroked) ? wxSOLID : wxTRANSPARENT);
    wrapper_type::get().SetPen(pen);
  }
    
  //! Get the draw style.
  inline int
  drawable<tk::wx>::get_draw_style() const
  {
    int style = 0;
    wxBrush brush = wrapper_type::get().GetBrush();
    if(brush.GetStyle() == wxSOLID) style |= abstract::draw_filled;
    wxPen pen = wrapper_type::get().GetPen();
    if(pen.GetStyle() == wxSOLID) style |= abstract::draw_stroked;
    return style;
  }
      
  //! Set the stroke (outline) color.
  inline void 
  drawable<tk::wx>::set_stroke_color(const rgba_type &__c)
  {
    wxPen pen = wrapper_type::get().GetPen();
    pen.SetColour(__c.r, __c.g, __c.b);
    wrapper_type::get().SetPen(pen);
  }

  //! Set the stroke (outline) width.
  inline void 
  drawable<tk::wx>::set_stroke_width(const int &__w)
  {
    wxPen pen = wrapper_type::get().GetPen();
    pen.SetWidth(__w);
    wrapper_type::get().SetPen(pen);    
  }
  
  //! Get the stroke (outline) width.
  inline int
  drawable<tk::wx>::get_stroke_width() const
  {
    wxPen pen = wrapper_type::get().GetPen();
    return pen.GetWidth();
  }
  
  //! Get the stroke (outline) color.
  inline drawable<tk::wx>::rgba_type 
  drawable<tk::wx>::get_stroke_color() const
  {
    wxPen pen = wrapper_type::get().GetPen();
    wxColour colour = pen.GetColour();

    return rgba_type
      (colour.Red(), colour.Green(), colour.Blue(), colour.Alpha());
  }

  //! Set the fill color.
  inline void
  drawable<tk::wx>::set_fill_color(const rgba_type &__c)
  {
    wxBrush brush = wrapper_type::get().GetBrush();
    brush.SetColour(__c.r, __c.g, __c.b);
    wrapper_type::get().SetBrush(brush);
  }

  //! Get the fill color.
  inline drawable<tk::wx>::rgba_type 
  drawable<tk::wx>::get_fill_color() const
  {
    wxBrush brush = wrapper_type::get().GetBrush();
    wxColour colour = brush.GetColour();

    return rgba_type
      (colour.Red(), colour.Green(), colour.Blue(), colour.Alpha());
  }  

  //! Set the text color.
  inline void 
  drawable<tk::wx>::set_font_color(const rgba_type &__c)
  {
    wxColour colour(__c.r, __c.g, __c.b, __c.a);
    wrapper_type::get().SetTextForeground(colour);
  }

  //! Get the text color.
  inline drawable<tk::wx>::rgba_type
  drawable<tk::wx>::get_font_color() const
  {
    wxColour colour = wrapper_type::get().GetTextForeground();

    return rgba_type
      (colour.Red(), colour.Green(), colour.Blue(), colour.Alpha());
  }
  
  //! Set the font type.
  inline void
  drawable<tk::wx>::set_font_type(const font_type &__t)
  {
    wxFont font = wrapper_type::get().GetFont();
    font.SetFamily(wx::fonts[__t].family);
    wrapper_type::get().SetFont(font);
  }

  //! Get the font type.
  inline drawable<tk::wx>::font_type
  drawable<tk::wx>::get_font_type() const
  {
    wxFont font = wrapper_type::get().GetFont();
    for(unsigned i = 0; i < sizeof(wx::fonts) / sizeof(wx::fonts[0]); i++)
    {
      if(wx::fonts[i].family == font.GetFamily())
        return font_type(i);
    }
    return font_type();
  }

  //! Set the font style.
  inline void
  drawable<tk::wx>::set_font_style(int style)
  {
    wxFont font = wrapper_type::get().GetFont();
    font.SetWeight((style & abstract::font_bold) ? wxFONTWEIGHT_BOLD : wxFONTWEIGHT_NORMAL);
    font.SetStyle((style & abstract::font_italic) ? wxFONTSTYLE_ITALIC : wxFONTSTYLE_NORMAL);
    wrapper_type::get().SetFont(font);
  }
  
  //! Get the font style
  inline int
  drawable<tk::wx>::get_font_style() const
  {
    wxFont font = wrapper_type::get().GetFont();
    return (font.GetWeight() == wxFONTWEIGHT_BOLD ? abstract::font_bold : 0) |
           (font.GetStyle() == wxFONTSTYLE_ITALIC ? abstract::font_italic : 0);
  }
  
  //! Set the font size.
  inline void
  drawable<tk::wx>::set_font_size(int sz)
  {
    wxFont font = wrapper_type::get().GetFont();
    font.SetPointSize(sz);
    wrapper_type::get().SetFont(font);
  }
  
  //! Get the font size.
  inline int
  drawable<tk::wx>::get_font_size() const
  {
    wxFont font = wrapper_type::get().GetFont();
    return font.GetPointSize();
  }
  
  inline void
  drawable<tk::wx>::draw_text
    (const std::string &s, const borg::rect<int> &rect, abstract::text_align align)
  {
    int x, y;
    int w, h;

    wrapper_type::get().GetTextExtent(s.c_str(), &w, &h);
    
    switch(align)
    {
    case abstract::align_center:
      x = rect.x() + (rect.w() - w) / 2;
      y = rect.y();
      break;
      
    case abstract::align_right:
      x = rect.x() + (w - rect.w());
      y = rect.y();
      break;
      
    default:
      x = rect.x();
      y = rect.y();
      break;
    }

    wrapper_type::get().DrawText(s, x, y);
  }

  inline int
  drawable<tk::wx>::set_antialias(bool __aa)
  {
    return -1;
  }
  
  inline bool
  drawable<tk::wx>::get_antialias() const
  {
    return false;
  }  
      
} // end of namespace wrap

/*namespace wx {
  
  typedef wrap::drawable<tk::wx> dc;
  typedef abstract::dc<dc::vector_type, dc::color_type> drawable;
  
} */
// end of namespace wx

#endif // _cxx_wx_drawable_
