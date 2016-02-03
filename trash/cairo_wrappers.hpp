#warning "obsolete"
#error "fuck"
//#ifndef _wrap_cairo_
//#define _wrap_cairo_

//#include <cairo.h>
//#include <iconv.hpp>

//#include <tk/dc_wrapper.hpp>

namespace cairo
{
  struct font
  {
    const char *family;
    double size;
  };
  
  extern const font fonts[];
}

extern "C" {
  struct _cairo;
  struct _cairo_surface;
}
  
namespace wrap {

  using namespace abstract;
  using namespace std;
  
  struct cairo : public traits::vector_types<int>, 
                 public traits::color_types<unsigned char>
  {
    typedef ::_cairo *dc_type;
    typedef ::_cairo *paint_dc_type;
    typedef ::_cairo *client_dc_type;
  };
  
  template<>
    struct dc_traits<cairo> : public wrap_traits<cairo::dc_type>
  {
    typedef double vector_type;
    typedef double color_type;
    typedef wrapper<cairo::dc_type> wrapper_type;
//    typedef abstract::dc<double, double> interface_type;
  };
  
  //! Wraps cairo_t class into an implementation of abstract::dc.
  template<>
    class dc<cairo> : public wrapper<cairo::dc_type>/*,
      public dc_traits<cairo>::interface_type*/
  {
  private:
//    ::_cairo *m_cairo;
    ::_cairo_surface *m_surface;
    std::point<double> m_penloc;
    borg::rect<double> m_clip;
    borg::rgba<double> m_stroke;
    borg::rgba<double> m_fill;
    borg::rgba<double> m_text;
    font_type m_fonttype;
    font_style m_fontstyle;
    double m_fontsize;
    double m_strokewidth;
    draw_style m_drawstyle;

  public:
    typedef dc_traits<cairo> traits_type;
    typedef traits_type::wrap_type wrap_type;
    typedef traits_type::wrapper_type wrapper_type;
    
    dc_TYPEDEF(traits_type::vector_type,
               traits_type::color_type)
    
    inline dc(wrap_type __wdc) : wrapper_type(__wdc),
     m_stroke(unsigned(0), unsigned(0), unsigned(0))
    {
      /*  if(m_cairo == 0)
       m_cairo = cairo_create(m_surface);*/
  
      m_drawstyle = draw_stroked;
  
      cairo_set_line_width(wrapper_type::get(), 1.0);
      cairo_set_line_cap(wrapper_type::get(), CAIRO_LINE_CAP_ROUND);
    }
    
    #define DC_API(unwrap_type) inline unwrap_type
    #define DC_OBJ wrapper_type::get()
    #define DC_CALL(fn, args...) fn( DC_OBJ, args );
    
    #include <cairo/dc.ipp>
    
/*    inline void
    move_to(const double &__x, const double &__y)
    {
      m_penloc.x() = __x;
      m_penloc.y() = __y;
    }
    
    inline void
    line_to(const double &__x, const double &__y)
    {
      cairo_new_path(&wrapper_type::get());
      cairo_move_to(&wrapper_type::get(), m_penloc.x(), m_penloc.y());
      cairo_line_to(&wrapper_type::get(), __x, __y);
      cairo_set_source_rgba(&wrapper_type::get(), m_stroke.r, m_stroke.g, m_stroke.b, m_stroke.a);
      cairo_stroke(&wrapper_type::get());
    }

    inline void
    draw_point(const double &__x, const double &__y)
    {
      cairo_new_path(&wrapper_type::get());
      cairo_set_source_rgba(&wrapper_type::get(), m_stroke.r, m_stroke.g, m_stroke.b, m_stroke.a);
      cairo_move_to(&wrapper_type::get(), __x, __y);
      cairo_stroke(&wrapper_type::get());
    }
    
    inline void
    draw_line(const std::point<double> &__s, const std::point<double> &__e)
    {
      cairo_new_path(&wrapper_type::get());
      cairo_move_to(&wrapper_type::get(), __s.x(), __e.y());
      cairo_line_to(&wrapper_type::get(), __e.x(), __e.y());
      cairo_stroke(&wrapper_type::get());
    }
    
    inline void 
    draw_rect(const borg::rect<double> &__r)
    {
      cairo_new_path(&wrapper_type::get());
      cairo_rectangle(&wrapper_type::get(), __r.x(), __r.y(), __r.w(), __r.h());
      
      stroke_or_fill();
    }

    inline void
    draw_ellipse(const borg::rect<double> &__r)
    {
      std::point<double> center = __r.center();
      
      cairo_new_path(&wrapper_type::get());
      
      double rx = __r.w() / 2;
      double ry = __r.h() / 2;
      int extent = int(rx * ry * M_PI * 2);
      
      for(int i = 0; i < extent; i++)
      {
        double a = i * M_PI * 2 / extent;
        cairo_line_to(&wrapper_type::get(), center.x() + cos(a) * rx, center.y() + cos(a) * ry);
      }
      
      cairo_close_path(&wrapper_type::get());
      stroke_or_fill();
    }
    
    inline void
    draw_arc
      (const borg::rect<double> &__r, float __s, float __e)
    {
      std::point<double> center = __r.center();
      
      cairo_new_path(&wrapper_type::get());
  
      double rx = __r.w() / 2;
      double ry = __r.h() / 2;
      int extent = int(rx * ry * (__e - __s));
      
      for(int i = 0; i < extent; i++)
      {
        double a = __s + (i * (__e - __s) / extent);
        cairo_line_to(&wrapper_type::get(), center.x() + cos(a) * rx, center.y() + sin(a) * ry);
      }
      
      if(m_font_style & draw_filled)
      {
        cairo_line_to(&wrapper_type::get(), center.x(), center.y());
        cairo_close_path(&wrapper_type::get());
      }
      
      stroke_or_fill();    
    }

    inline void 
    draw_polygon(const std::point<double> __pts[], size_t n)
    {
      if(n < 2) return;
      cairo_move_to(&wrapper_type::get(), __pts[0].x(), __pts[0].y());
      
      for(size_t i = 1; i < n; i++)
        cairo_line_to(&wrapper_type::get(), __pts[i].x(), __pts[i].y());
      
      cairo_close_path(&wrapper_type::get());
      stroke_or_fill();
    }

    inline void 
    set_clip(const borg::rect<double> &__r)
    {
      if(__r.x() < m_clip.x() || __r.x2() > m_clip.x2() ||
         __r.y() < m_clip.y() || __r.y2() > m_clip.y2())
        cairo_reset_clip(&wrapper_type::get());
      
      cairo_new_path(&wrapper_type::get());
      cairo_rectangle(&wrapper_type::get(), __r.x(), __r.y(), __r.w(), __r.h());
      cairo_clip(&wrapper_type::get());
      
      m_clip = __r;
    }
  
    borg::rect<double>
    get_clip() const
    {
      return m_clip;
    }

    inline void
    reset_clip()
    {
      cairo_reset_clip(&wrapper_type::get());
    }

    inline void
    set_draw_style(int __st)
    {
      m_font_style = __st;
    }

    inline int
    get_draw_style() const
    {
      return m_font_style;
    }

    inline void 
    set_stroke_color
      (const borg::rgba<double> &__c)
    {
      m_stroke = __c;
    }
    
    inline void 
    set_stroke_width(const double &__w)
    {
      m_stroke_width = __w;
      cairo_set_line_width(&wrapper_type::get(), m_stroke_width);
    }
  
    inline double
    get_stroke_width() const
    {
      return m_stroke_width;
    }
    
    inline borg::rgba<double>
    get_stroke_color() const
    {
      return m_stroke;
    }

    inline void
    set_fill_color(const borg::rgba<double> &__c)
    {
      m_fill = __c;
    }

    inline borg::rgba<double> 
    get_fill_color() const
    {
      return m_fill;
    }  
    
    inline void
    set_font_color(const borg::rgba<double> &__c)
    {
      m_text = __c;
    }
    
    inline borg::rgba<double> 
    get_font_color() const
    {
      return m_text;
    }
  
    inline void
    set_font_type
      (const font_type &__t)
    {
      m_font_type = __t;
      
      cairo_select_font_face(&wrapper_type::get(), ::cairo::fonts[__t].family,
                             (m_font_style & font_italic) ? CAIRO_FONT_SLANT_ITALIC : CAIRO_FONT_SLANT_NORMAL,
                             (m_font_style & font_bold) ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL);
    }
    
    inline font_type
    get_font_type() const
    {
      return m_font_type;
    }
    
    inline void
    set_font_style(int style)
    {
      m_font_style = style;
      
      cairo_select_font_face(&wrapper_type::get(), ::cairo::fonts[m_font_type].family,
                             (m_font_style & font_italic) ? CAIRO_FONT_SLANT_ITALIC : CAIRO_FONT_SLANT_NORMAL,
                             (m_font_style & font_bold) ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL);
      
      //  cairo_set_font_size(&wrapper_type::get(), ::cairo::fonts[__t].size);
    }

    inline int
    get_font_style() const
    {
      return m_font_style;
    }
    
    inline void
    set_font_size(double sz)
    {
      m_font_size = sz;
      cairo_set_font_size(&wrapper_type::get(), m_font_size);
    }

    inline double
    get_font_size() const
    {
      return m_font_size;
    }

    inline void
    draw_text(const string &s, const rect_type &rect, text_align align = align_center)
    {
      cairo_text_extents_t extents;
      cairo_text_extents(&wrapper_type::get(), s.c_str(), &extents);
      
      double x, y;
  
      switch(align)
      {
      case align_center:
        x = rect.x() + (rect.w() - extents.width) / 2;
        y = rect.y() + extents.height - (extents.y_bearing + extents.height);
        break;
        
      case align_right:
        x = rect.x() + (extents.width - rect.w());
        y = rect.y() + extents.height - (extents.y_bearing + extents.height);
        break;
        
      default:
        x = rect.x();
        y = rect.y() + extents.height - (extents.y_bearing + extents.height);
        break;
      }
      
      cairo_move_to(&wrapper_type::get(), x, y);
      cairo_set_source_rgba(&wrapper_type::get(), m_text.r, m_text.g, m_text.b, m_text.a);
      cairo_show_text(&wrapper_type::get(), iconv::utf8_encode()(s).c_str());
    }
  
    inline int
    set_antialias(bool c)
    {
      cairo_set_antialias(&wrapper_type::get(), (c ? 
                                                    CAIRO_ANTIALIAS_DEFAULT : 
                                                    CAIRO_ANTIALIAS_NONE));
      return c;
    }
    
    inline bool 
    get_antialias() const
    {
      return cairo_get_antialias
        (const_cast< ::_cairo * >(&wrapper_type::get())) != CAIRO_ANTIALIAS_NONE;
    }*/
  };
  
  
} // end of namespace wrap
//#endif // _wrap_cairo_
