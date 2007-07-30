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
  DC_CALL( moveTo(CPoint(x, y)) )
}

//----------------------------------------------------------------------------
//! Move the to the coordinate pair \a x, \a y while drawing a line.
//----------------------------------------------------------------------------
DC_API( void )
line_to(const vector_type &x, const vector_type &y)
{ 
  DC_CALL( lineTo(CPoint(x, y)) )
}

//----------------------------------------------------------------------------
//! Draw a point at the coordinate pair \a x, \a y.
//----------------------------------------------------------------------------
DC_API( void )
draw_point(const vector_type &x, const vector_type &y)
{ 
  CColor c = DC_CALL( getFrameColor() )
  DC_CALL( drawPoint(CPoint(x, y), c) )
}

//----------------------------------------------------------------------------
//! Draw a line from point \a s to point \a e.
//----------------------------------------------------------------------------
DC_API( void )
draw_line(const point_type &s, const point_type &e)
{
  CPoint pt;
  DC_CALL( getLoc(pt) )
  DC_CALL( moveTo(s) )
  DC_CALL( lineTo(e) )
  DC_CALL( moveTo(pt) )
}

//----------------------------------------------------------------------------
//! Draw a rectangle with the position and dimensions of \a r.
//----------------------------------------------------------------------------
DC_API( void )
draw_rect(const rect_type &r) DC_CONST()
{
  DC_CALL( drawRect(CRect(r.x, r.y, r.x2, r.y2)) )
}

//----------------------------------------------------------------------------
//! Draw an ellipse with the position and dimensions of \a r.
//----------------------------------------------------------------------------
DC_API( void )
draw_ellipse(const rect_type &r)
{
  DC_CALL( drawEllipse(r) )
}

//----------------------------------------------------------------------------
//! Draw an arc within the rectangle \a r, spanning from angle \a s to angle \a e.
//----------------------------------------------------------------------------
DC_API( void )
draw_arc(const rect_type &r, float s, float e)
{
  DC_CALL( drawArc(r, (s * 3.141592653589793 / 180), (e * 3.141592653589793 / 180)) )
}

//----------------------------------------------------------------------------
//! Draw a polygon through the specified points \a pts.
//----------------------------------------------------------------------------
DC_API( void )
draw_polygon(const point_type pts[], index_type n, style_type st)
{
/*  CPoint *points = new CPoint[n];

  for(index_type i = 0; i < n; i++)
  {
    points[i].x = pts[i].x;
    points[i].y = pts[i].y;
  }*/

  DC_CALL( drawPolygon(pts, n, st) )
}

//----------------------------------------------------------------------------
//! Set the clipping region to \a r.
//----------------------------------------------------------------------------
DC_API( void )
set_clip(const rect_type &r)
{
  DC_CALL( setClipRect(CRect(r.x, r.y, r.x2, r.y2)) )
}

//----------------------------------------------------------------------------
//! Get the current clipping region.
//----------------------------------------------------------------------------
DC_API( rect_type )
get_clip() DC_CONST( const )
{
  CRect rect;
  DC_CALL( getClipRect(rect) )
  return rect_type(rect.x, rect.y, rect.width(), rect.height());
}

//----------------------------------------------------------------------------
//! Reset the current clipping region (usually to the size of the associated widget).
//----------------------------------------------------------------------------
DC_API( void )
reset_clip()
{
  DC_CALL( resetClipRect() )
}

//----------------------------------------------------------------------------
//! Set the draw style to \a st.
//----------------------------------------------------------------------------
/*DC_API( void )
set_draw_style(draw_style st) DC_CONST()
{
  if((st & draw_stroked) && (st & draw_filled))
    m_drawstyle = kDrawFilledAndStroked;
  else if((st & draw_filled))
    m_drawstyle = kDrawFilled;
  else
    m_drawstyle = kDrawStroked;
}*/

//----------------------------------------------------------------------------
//! Get the draw style.
//----------------------------------------------------------------------------
/*DC_API( draw_style )
get_draw_style() DC_CONST( const )
{
  switch(m_drawstyle)
  {
    case kDrawFilledAndStroked: return draw_stroked|draw_filled;
    case kDrawFilled: return draw_filled;
    case kDrawStroked: return draw_stroked;
  }
  return 0;
}*/

//----------------------------------------------------------------------------
//! Set the stroke (outline) color to \a c.
//----------------------------------------------------------------------------
DC_API( void )
set_stroke_color(const rgba_type &c)
{
  CColor color = { c.red, c.green, c.blue, c.alpha };
  DC_CALL( setFrameColor(color) )
}

//----------------------------------------------------------------------------
//! Set the stroke (outline) color to the rgba color represented 
//! by \a r, \a g, \a b and \a a.
//----------------------------------------------------------------------------
DC_API( void )
set_stroke_color(color_type r, color_type g, color_type b, color_type a
                 DC_DEFAULT( boost::integer_traits<color_type>::const_max ))
{
  CColor color = { r, g, b, a };
  DC_CALL( setFrameColor(color) )
}
  
//----------------------------------------------------------------------------
//! Get the stroke (outline) color.
//----------------------------------------------------------------------------
DC_API( rgba_type )
get_stroke_color() DC_CONST( const )
{
  return DC_CALL( getFrameColor() )
    
//  return rgba_type(frame.red, frame.green, frame.blue, frame.alpha);
}
  
//----------------------------------------------------------------------------
//! Set the stroke (outline) width to \a w.
//----------------------------------------------------------------------------
DC_API( void )
set_stroke_width(vector_type w)
{
  DC_CALL( setLineWidth(w) )
}

//----------------------------------------------------------------------------
//! Get the stroke (outline) width.
//----------------------------------------------------------------------------
DC_API( vector_type )
get_stroke_width() DC_CONST( const )
{
  return DC_CALL( getLineWidth() )
}

//----------------------------------------------------------------------------
//! Set the fill color to \a c.
//----------------------------------------------------------------------------
DC_API( void )
set_fill_color(const rgba_type &c) DC_CONST()
{
//  CColor color = { c.r, c.g, c.b, c.a };
  DC_CALL( setFillColor(c) )
}
  
//----------------------------------------------------------------------------
//! Set the fill color to the rgba color represented by \a r, \a g, \a b and \a a.
//----------------------------------------------------------------------------
DC_API( void )
set_fill_color(color_type r, color_type g, color_type b, color_type a
               DC_DEFAULT( boost::integer_traits<color_type>::const_max ))
{
  CColor color = { r, g, b, a };
  DC_CALL( setFillColor(color) )
}
  
//----------------------------------------------------------------------------
//! Get the fill color.
//----------------------------------------------------------------------------
DC_API( rgba_type )
get_fill_color() DC_CONST( const )
{
  return DC_CALL( getFillColor() )
//  return rgba_type(fill.red, fill.green, fill.blue, fill.alpha);
}  
  
//----------------------------------------------------------------------------
//! Set the text color to \a c.
//----------------------------------------------------------------------------
DC_API( void )
set_font_color(const rgba_type &c)
{
  CColor color = { c.red, c.green, c.blue, c.alpha };
  DC_CALL( setFontColor(color) )
}
  
//----------------------------------------------------------------------------
//! Set the font color to the rgba color represented by \a r, \a g, \a b and \a a.
//----------------------------------------------------------------------------
DC_API( void )
set_font_color(color_type r, color_type g, color_type b, color_type a
               DC_DEFAULT( boost::integer_traits<color_type>::const_max ))
{
  CColor color = { r, g, b, a };
  DC_CALL( setFontColor(color) )
}
  
//----------------------------------------------------------------------------
//! Get the font color.
//----------------------------------------------------------------------------
DC_API( rgba_type )
get_font_color() DC_CONST( const )
{
  return DC_CALL( getFontColor() )
//  return rgba_type(font.red, font.green, font.blue, font.alpha);
}

//----------------------------------------------------------------------------
//! Set the font type to \a t.
//----------------------------------------------------------------------------
DC_API( void )
set_font_type(const font_type &t)
{
}
  
//----------------------------------------------------------------------------
//! Get the font type.
//----------------------------------------------------------------------------
/*DC_API( font_type )
get_font_type() DC_CONST( const )
{
}*/
  
//----------------------------------------------------------------------------
//! Set the font style to \a st.
//----------------------------------------------------------------------------
/*DC_API( void )
set_font_style(font_style st)
{
}*/

//----------------------------------------------------------------------------
//! Get the font style
//----------------------------------------------------------------------------
/*DC_API( font_style )
get_font_style() DC_CONST( const )
{
}*/

//----------------------------------------------------------------------------
//! Set the font size to \a sz.
//----------------------------------------------------------------------------
/*DC_API( void )
set_font_size(vector_type sz)
{
}*/

//----------------------------------------------------------------------------
//! Get the font size.
//----------------------------------------------------------------------------
/*DC_API( vector_type )
get_font_size() DC_CONST( const )
{
}*/

//----------------------------------------------------------------------------
//! Draw the text \a s, aligned according to \a a to the destination 
//! rectangle \a r.
//----------------------------------------------------------------------------
DC_API( void )
draw_text(const std::string &s, const rect_type &r, align_type a /*DC_DEFAULT(align_center)*/)
{
}
  
//----------------------------------------------------------------------------
//! Set antialiasing mode. Returns -1 if not supported.
//----------------------------------------------------------------------------
DC_API( int )
set_antialias(bool aa DC_DEFAULT(true))
{
  DC_CALL( setDrawMode(aa ? kAntialias : kCopyMode) )
  return aa;
}

//----------------------------------------------------------------------------
//! Get antialiasing mode.
//----------------------------------------------------------------------------
DC_API( bool )
get_antialias() DC_CONST( const )
{
  CDrawMode m = DC_CALL( getDrawMode() )
  return (m == kAntialias ? true : false);
}

//----------------------------------------------------------------------------
//! Return system-specific pointer to drawcontext.
//----------------------------------------------------------------------------
DC_API( void * )
get_pointer() DC_CONST( const )
{
  return DC_CALL( getSystemContext() )
}

//@}
//----------------------------------------------------------------------------

#undef DC_API
#undef DC_CALL
#undef DC_DEFAULT
