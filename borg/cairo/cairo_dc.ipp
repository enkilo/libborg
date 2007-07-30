#ifndef DC_API
#define DC_API(ret_type) ret_type
#endif // DC_API

#ifndef DC_CALL
#define DC_CALL(fn_call) fn_call;
#endif // DC_CALL

#ifndef DC_DEFAULT
#define DC_DEFAULT(def_value) = def_value
#endif // DC_DEFAULT

//----------------------------------------------------------------------------
//! \name Implementation of the abstract::dc interface ontop wxWidgets.
//----------------------------------------------------------------------------
//@{

//----------------------------------------------------------------------------
//! Move the pen to the coordinate pair \a x, \a y.
//----------------------------------------------------------------------------
DC_API( void )
move_to(const vector_type &x, const vector_type &y)
{
  m_penloc.x() = x;
  m_penloc.y() = y;
}

//----------------------------------------------------------------------------
//! Move the to the coordinate pair \a x, \a y while drawing a line.
//----------------------------------------------------------------------------
DC_API( void )
line_to(const vector_type &x, const vector_type &y)
{ 
  cairo_new_path(DC_OBJ);
  cairo_move_to(DC_OBJ, m_penloc.x(), m_penloc.y() );
  cairo_line_to(DC_OBJ, x, y);
  cairo_set_source_rgba(DC_OBJ, m_stroke.r, m_stroke.g, m_stroke.b, m_stroke.a);
  cairo_stroke(DC_OBJ);
  m_penloc.x() = x;
  m_penloc.y() = y;
}

//----------------------------------------------------------------------------
//! Draw a point at the coordinate pair \a x, \a y.
//----------------------------------------------------------------------------
DC_API( void )
draw_point(const vector_type &x, const vector_type &y)
{ 
  cairo_new_path(DC_OBJ);
  cairo_set_source_rgba(DC_OBJ, m_stroke.r, m_stroke.g, m_stroke.b, m_stroke.a);
  cairo_move_to(DC_OBJ, x, y);
  cairo_stroke(DC_OBJ);
}

//----------------------------------------------------------------------------
//! Draw a line from point \a s to point \a e.
//----------------------------------------------------------------------------
DC_API( void )
draw_line(const point_type &s, const point_type &e)
{
  cairo_new_path(DC_OBJ);
  cairo_move_to(DC_OBJ, s.x(), e.y());
  cairo_line_to(DC_OBJ, e.x(), e.y());
  cairo_stroke(DC_OBJ);
}

//----------------------------------------------------------------------------
//! Draw a rectangle with the position and dimensions of \a r.
//----------------------------------------------------------------------------
DC_API( void )
draw_rect(const rect_type &r)
{
  cairo_new_path(DC_OBJ);
  cairo_rectangle(DC_OBJ, r.x(), r.y(), r.w(), r.h());
  stroke_or_fill();
}

DC_API( void )
draw_rect(const vector_type &x, const vector_type &y, 
          const vector_type &w, const vector_type &h)
{
  cairo_new_path(DC_OBJ);
  cairo_rectangle(DC_OBJ, x, y, w, h);
  stroke_or_fill();
}

//----------------------------------------------------------------------------
//! Draw an ellipse with the position and dimensions of \a r.
//----------------------------------------------------------------------------
DC_API( void )
draw_ellipse(const rect_type &r)
{
  borg::point<double> center = r.center();  
  cairo_new_path(DC_OBJ);
  double rx = r.w() / 2;
  double ry = r.h() / 2;
  int extent = int(rx * ry * M_PI * 2);
  for(int i = 0; i < extent; i++)
  {
    double a = i * M_PI * 2 / extent;
    cairo_line_to(DC_OBJ, center.x() + cos(a) * rx, center.y() + cos(a) * ry);
  }
  cairo_close_path(DC_OBJ);
  stroke_or_fill();
}

//----------------------------------------------------------------------------
//! Draw an arc within the rectangle \a r, spanning from angle \a s to angle \a e.
//----------------------------------------------------------------------------
DC_API( void )
draw_arc(const rect_type &r, float s, float e)
{
  borg::point<double> center = r.center();  
  cairo_new_path(DC_OBJ);
  double rx = r.w() / 2;
  double ry = r.h() / 2;
  int extent = int(rx * ry * (e - s));  
  for(int i = 0; i < extent; i++)
  {
    double a = s + (i * (e - s) / extent);
    cairo_line_to(DC_OBJ, center.x() + cos(a) * rx, center.y() + sin(a) * ry);
  }
  if(m_drawstyle & draw_filled)
  {
    cairo_line_to(DC_OBJ, center.x(), center.y());
    cairo_close_path(DC_OBJ);
  }
  stroke_or_fill();    
}

//----------------------------------------------------------------------------
//! Draw a polygon through the specified points \a pts.
//----------------------------------------------------------------------------
DC_API( void )
draw_polygon(const point_type pts[], index_type n)
{
  if(n < 2) return;
  cairo_move_to(DC_OBJ, pts[0].x(), pts[0].y());  
  for(index_type i = 1; i < n; i++)
    cairo_line_to(DC_OBJ, pts[i].x(), pts[i].y());  
  cairo_close_path(DC_OBJ);
  stroke_or_fill();
}

//----------------------------------------------------------------------------
//! Set the clipping region to \a r.
//----------------------------------------------------------------------------
DC_API( void )
set_clip(const rect_type &r)
{
  if(r.x() < m_clip.x() || r.x2() > m_clip.x2() ||
     r.y() < m_clip.y() || r.y2() > m_clip.y2())
    cairo_reset_clip(DC_OBJ);  
  cairo_new_path(DC_OBJ);
  cairo_rectangle(DC_OBJ, r.x(), r.y(), r.w(), r.h());
  cairo_clip(DC_OBJ);
  m_clip = r;
}

//----------------------------------------------------------------------------
//! Get the current clipping region.
//----------------------------------------------------------------------------
DC_API( rect_type )
get_clip() const
{
  return m_clip;
}

//----------------------------------------------------------------------------
//! Reset the current clipping region (usually to the size of the associated widget).
//----------------------------------------------------------------------------
/*DC_API( void )
reset_clip()
{
  cairo_reset_clip(DC_OBJ);
#warning "set resetted clip rect here"
}*/

//----------------------------------------------------------------------------
//! Set the draw style to \a st.
//----------------------------------------------------------------------------
DC_API( void )
set_draw_style(draw_style st)
{
  m_drawstyle = st;
}

//----------------------------------------------------------------------------
//! Get the draw style.
//----------------------------------------------------------------------------
/*DC_API( draw_style )
get_draw_style() const
{
  return draw_style(m_drawstyle);
}*/

//----------------------------------------------------------------------------
//! Set the stroke (outline) color to \a c.
//----------------------------------------------------------------------------
DC_API( void )
set_stroke_color(const rgba_type &c)
{  
  m_stroke = c;
}

//----------------------------------------------------------------------------
//! Set the stroke (outline) color to the rgba color represented 
//! by \a r, \a g, \a b and \a a.
//----------------------------------------------------------------------------
DC_API( void )
set_stroke_color(color_type r, color_type g, color_type b, color_type a
                 DC_DEFAULT( 1.0 ))
{
  m_stroke(r, g, b, a);
}
  
//----------------------------------------------------------------------------
//! Get the stroke (outline) color.
//----------------------------------------------------------------------------
DC_API( rgba_type )
get_stroke_color() const
{
  return m_stroke;
}
  
//----------------------------------------------------------------------------
//! Set the stroke (outline) width to \a w.
//----------------------------------------------------------------------------
DC_API( void )
set_stroke_width(vector_type w)
{
  m_strokewidth = w;
  cairo_set_line_width(DC_OBJ, m_strokewidth);
}

//----------------------------------------------------------------------------
//! Get the stroke (outline) width.
//----------------------------------------------------------------------------
DC_API( vector_type )
get_stroke_width() const
{
  return m_strokewidth;
}

//----------------------------------------------------------------------------
//! Set the fill color to \a c.
//----------------------------------------------------------------------------
DC_API( void )
set_fill_color(const rgba_type &c)
{
  m_fill = c;
}
  
//----------------------------------------------------------------------------
//! Set the fill color to the rgba color represented by \a r, \a g, \a b and \a a.
//----------------------------------------------------------------------------
DC_API( void )
set_fill_color(color_type r, color_type g, color_type b, color_type a
               DC_DEFAULT( 1.0 ))
{
  m_fill(r, g, b, a);
}
  
//----------------------------------------------------------------------------
//! Get the fill color.
//----------------------------------------------------------------------------
DC_API( rgba_type )
get_fill_color() const
{
  return m_fill;
}  
  
//----------------------------------------------------------------------------
//! Set the text color to \a c.
//----------------------------------------------------------------------------
DC_API( void )
set_font_color(const rgba_type &c)
{
  m_text = c;
}
  
//----------------------------------------------------------------------------
//! Set the font color to the rgba color represented by \a r, \a g, \a b and \a a.
//----------------------------------------------------------------------------
DC_API( void )
set_font_color(color_type r, color_type g, color_type b, color_type a
               DC_DEFAULT( 1.0 ))
{
  m_text(r, g, b, a);
}
  
//----------------------------------------------------------------------------
//! Get the font color.
//----------------------------------------------------------------------------
DC_API( rgba_type )
get_font_color() const
{
  return m_text;
}

//----------------------------------------------------------------------------
//! Set the font type to \a t.
//----------------------------------------------------------------------------
/*DC_API( void )
set_font_type(const font_type &t)
{
  m_fonttype = t;
  cairo_select_font_face(DC_OBJ, ::cairo::fonts[(int)t].family,
                         (m_fontstyle & font_italic) ? CAIRO_FONT_SLANT_ITALIC : CAIRO_FONT_SLANT_NORMAL,
                         (m_fontstyle & font_bold) ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL);
}*/
  
//----------------------------------------------------------------------------
//! Get the font type.
//----------------------------------------------------------------------------
/*DC_API( font_type )
get_font_type() const
{
  return m_fonttype;
}*/
  
//----------------------------------------------------------------------------
//! Set the font style to \a st.
//----------------------------------------------------------------------------
/*DC_API( void )
set_font_style(font_style st)
{
  m_fontstyle = st;
  cairo_select_font_face(DC_OBJ, ::cairo::fonts[(int)m_fonttype].family,
                         (m_fontstyle & font_italic) ? CAIRO_FONT_SLANT_ITALIC : CAIRO_FONT_SLANT_NORMAL,
                         (m_fontstyle & font_bold) ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL);
}*/

//----------------------------------------------------------------------------
//! Get the font style
//----------------------------------------------------------------------------
/*DC_API( font_style )
get_font_style() const
{
  return m_fontstyle;
}*/

//----------------------------------------------------------------------------
//! Set the font size to \a sz.
//----------------------------------------------------------------------------
DC_API( void )
set_font_size(vector_type sz)
{
  m_fontsize = sz;
  cairo_set_font_size(DC_OBJ, m_fontsize);
}

//----------------------------------------------------------------------------
//! Get the font size.
//----------------------------------------------------------------------------
DC_API( vector_type )
get_font_size() const
{
  return m_fontsize;
}

//----------------------------------------------------------------------------
//! Draw the text \a s, aligned according to \a a to the destination 
//! rectangle \a r.
//----------------------------------------------------------------------------
DC_API( void )
draw_text(const std::string &s, const rect_type &r, int a DC_DEFAULT(align_center))
{
  cairo_text_extents_t extents;
  cairo_text_extents(DC_OBJ, s.c_str(), &extents);  
  double x, y;
  switch(a)
  {
  case align_center:
    x = r.x() + (r.w() - extents.width) / 2;
    y = r.y() + extents.height - (extents.y_bearing + extents.height);
    break;    
  case align_right:
    x = r.x() + (extents.width - r.w());
    y = r.y() + extents.height - (extents.y_bearing + extents.height);
    break;    
  default:
    x = r.x();
    y = r.y() + extents.height - (extents.y_bearing + extents.height);
    break;
  }
  cairo_move_to(DC_OBJ, x, y);
  cairo_set_source_rgba(DC_OBJ, m_text.r, m_text.g, m_text.b, m_text.a);
  cairo_show_text(DC_OBJ, borg::iconv::utf8_encode()(s).c_str());
}
  
//----------------------------------------------------------------------------
//! Set antialiasing mode. Returns -1 if not supported.
//----------------------------------------------------------------------------
DC_API( int )
set_antialias(bool aa DC_DEFAULT(true))
{
  cairo_set_antialias(DC_OBJ, (aa ? CAIRO_ANTIALIAS_DEFAULT : CAIRO_ANTIALIAS_NONE));
  return aa;
}

//----------------------------------------------------------------------------
//! Get antialiasing mode.
//----------------------------------------------------------------------------
DC_API( bool )
get_antialias() const
{
  return cairo_get_antialias
    (const_cast< ::_cairo * >(DC_OBJ)) != CAIRO_ANTIALIAS_NONE;
}

//@}

DC_PROT( private: )

//! Private helper function:
DC_API( void )
stroke_or_fill()
{
  // fill
  if(m_drawstyle & draw_filled)
  {
    cairo_set_source_rgba(DC_OBJ, m_fill.r, m_fill.g, m_fill.b, m_fill.a);
    if(m_drawstyle & draw_stroked)
      cairo_fill_preserve(DC_OBJ);
    else
      cairo_fill(DC_OBJ);
  }
  
  // stroke
  if(m_drawstyle & draw_stroked)
  {
    cairo_set_source_rgba(DC_OBJ, m_stroke.r, m_stroke.g, m_stroke.b, m_stroke.a);
    cairo_stroke(DC_OBJ);
  }    
}

//----------------------------------------------------------------------------
