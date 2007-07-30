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

#ifndef _wrap_gdmm_
#define _wrap_gdmm_

#include <gdmm.hpp>

#include <wrap/dc.hpp>

namespace wrap {

  using namespace abstract;
      
  struct gdmm : public traits::vector_types<int>, 
                public traits::color_types<unsigned char>
  {
    typedef gd::Image &dc_type;
    typedef int vector_type;
    typedef unsigned char color_type;
  };
  
  template<>
    struct dc_traits<gdmm>
  {
    typedef gdmm::dc_type wrap_type;
    typedef int vector_type;
    typedef unsigned char color_type;
//    typedef abstract::dc<int, unsigned char> interface;
  };
  
  //! Wraps gd::Image class into an implementation of abstract::dc.
  template<>
    class dc<gdmm> : public wrapper<gdmm::dc_type>/*,
                                  public dc_traits<gdmm>::interface*/
  {
  public:
    typedef dc_traits<gdmm> traits_type;
    typedef traits_type::wrap_type wrap_type;

    dc_TYPEDEF(traits_type::vector_type,
                     traits_type::color_type)
    
    dc(wrap_type __gdimage) : wrapper<wrap_type>(__gdimage)
    {}

    //! Move pen to \a point.
    inline void
    move_to
      (const int &__x, const int &__y)
    {
      wrapper_type::get().moveTo(__x, __y);
    }
  
    //! Draw while moving the pen to \a point.
    inline void
    line_to(const int &__x, const int &__y)
    { 
      wrapper_type::get().lineTo(__x, __y);
    }

    //! Draw a point to the specified position.
    inline void
    draw_point(const int &__x, const int &__y)
    {
      wrapper_type::get().drawPoint(__x, __y);
    }
    
    //! Draw a line from \a __s to \a __e.
    inline void
    draw_line(const std::point<int> &__s, const std::point<int> &__e)
    {
      wrapper_type::get().drawLine
        (__s.x(), __s.y(), __e.x(), __e.y());
    }

    //! Draw a rectangle.
    inline void
    draw_rect(const borg::rect<int> &__r)
    {
      wrapper_type::get().drawRect
        (__r.x(), __r.y(), __r.x2(), __r.y2());
    }

    //! Draw an ellipse.
    inline void
    draw_ellipse(const borg::rect<int> &__r)
    {
      wrapper_type::get().drawEllipse
        (__r.x(), __r.y(), __r.x2(), __r.y2());
    }
    
    //! Draw an arc within \a rect, spanning from \a start to \a end.
    inline void 
    draw_arc(const borg::rect<int> &__r, float __s, float __e)
    {
      wrapper_type::get().drawArc
        (__r.center().x(), __r.center().y(), __r.w(), __r.h(), 
         int(__s * 180 / M_PI), int(__e * 180 / M_PI));
    }

    //! Draw a polygon through the specified points.
    inline void 
    draw_polygon(const std::point<int> __pts[], size_t n)
    {
      gd::Point points[n];
      for(size_t i = 0; i < n; i++)
      {
        points[i].x = __pts[i].x();
        points[i].y = __pts[i].y();
      }
      wrapper_type::get().drawPolygon(points, n);
    }
    
    //! Set clipping region.
    inline void 
    set_clip(const borg::rect<int> &__r)
    {
      wrapper_type::get().setClip(__r.x(), __r.y(), __r.x2(), __r.y2());
    }

    //! Get clipping region.
    inline borg::rect<int> 
    get_clip() const
    {
      borg::rect<int> ret;
      int x1, y1, x2, y2;
      wrapper_type::get().getClip(x1, y1, x2, y2);
      return ret;
    }
  
    //! Reset clipping region.
    inline void
    reset_clip()
    {
      wrapper_type::get().resetClip();
    }

    //! Set the draw style.
    inline void
    set_draw_style(int __st)
    {
    }

    //! Get the draw style.
    inline int
    get_draw_style() const
    {
    }
    
    //! Set the stroke (outline) color.
    inline void
    set_stroke_color(const borg::rgba<unsigned char> &__c)
    {
      wrapper_type::get().setStrokeColor
        (gd::Color(__c.r, __c.g, __c.b, __c.a));
    }

    //! Set the stroke (outline) width.
    inline void 
    set_stroke_width(const int &__w)
    {
      wrapper_type::get().setStrokeWidth(__w);
    }
  
    //! Get the stroke (outline) width.
    inline int
    get_stroke_width() const
    {
      return wrapper_type::get().getStrokeWidth();
    }

    //! Get the stroke (outline) color.
    inline borg::rgba<unsigned char> 
    get_stroke_color() const
    {
      gd::Color ret = wrapper_type::get().getStrokeColor();
      return borg::rgba<unsigned char>(ret.r, ret.g, ret.b, ret.a);
    }

    //! Set the fill color.
    inline void
    set_fill_color
      (const borg::rgba<unsigned char> &__c)
    {
      wrapper_type::get().setStrokeColor
        (gd::Color(__c.r, __c.g, __c.b, __c.a));
    }
    
    //! Get the fill color.
    inline borg::rgba<unsigned char>
    get_fill_color() const
    {
      gd::Color ret = wrapper_type::get().getFillColor();
      return borg::rgba<unsigned char>(ret.r, ret.g, ret.b, ret.a);
    }

    //! Set the text color.
    inline void
    set_font_color(const borg::rgba<unsigned char> &__c)
    {
      wrapper_type::get().setFontColor
        (gd::Color(__c.r, __c.g, __c.b, __c.a));
    }

    //! Get the text color.
    inline borg::rgba<unsigned char> 
    get_font_color() const
    {
      gd::Color ret = wrapper_type::get().getFontColor();
      return borg::rgba<unsigned char>(ret.r, ret.g, ret.b, ret.a);
    }
    
    //! Set the font type.
    inline void
    set_font_type(const abstract::font_type &__t)
    {
      gd::Font font;
      switch(__t)
      {
        case abstract::font_fixed: font = gd::fontFixed; break;
        case abstract::font_very_big: font = gd::fontVeryBig; break;
        case abstract::font_big: font = gd::fontBig; break;
        case abstract::font_medium: font = gd::fontMedium; break;
        case abstract::font_small: font = gd::fontSmall; break;
        case abstract::font_very_small: font = gd::fontVerySmall; break;
      }
      wrapper_type::get().setFont(font);
    }
    
    //! Get the font type.
    inline abstract::font_type
    get_font_type() const
    {
      gd::Font font = wrapper_type::get().getFont();
      switch(font)
      {
        case gd::fontVeryBig: return abstract::font_very_big;
        case gd::fontBig: return abstract::font_big;
        case gd::fontMedium: return abstract::font_medium;
        case gd::fontSmall: return abstract::font_small;
        case gd::fontVerySmall: return abstract::font_very_small;
        default: return abstract::font_fixed;
      }
    }
    
    inline void
    draw_text(const std::string &s, const borg::rect<int> &rect, abstract::text_align align)
    {
        
    }

    inline int
    set_antialias(bool aa)
    {
    }

    inline bool
    get_antialias() const
    {
    }
  
    inline void
    set_font_style(int sz)
    {
    }

    inline int
    get_font_style() const
    {
    }
  
    inline void
    set_font_size(int sz)
    {
    }
    
    inline int
    get_font_size() const
    {
    }
  };
}

#endif // _wrap_gdmm_
