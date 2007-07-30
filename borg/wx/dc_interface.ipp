/*
#ifndef DC_API
#define DC_API(ret_type) ret_type
#endif // DC_API

#ifndef DC_CALL
#define DC_CALL(fn_call) fn_call;
#endif // DC_CALL

#ifndef DC_DEFAULT
#define DC_DEFAULT(def_value) = def_value
#endif // DC_DEFAULT

#ifndef DC_CONST
#define DC_CONST(c) c
#endif // DC_CONST
*/
//----------------------------------------------------------------------------
//! \name Implementation of the abstract::dc interface ontop wxWidgets.
//----------------------------------------------------------------------------
//@{

//----------------------------------------------------------------------------
//! Blit from this draw context to a destination context.
//----------------------------------------------------------------------------
DC_API( bool )
blit(dc_type &dc, rect_type const &r, point_type const &o) DC_CONST()
{
  return dc.Blit(r.GetX(), r.GetY(), r.GetWidth(), r.GetHeight(), DC_OBJ(), o.x, o.y);
}

//----------------------------------------------------------------------------
//! Adds the specified point to the bounding box.
//----------------------------------------------------------------------------
DC_API( void )
calc_bounding_box(vector_type const &x, vector_type const &y) DC_CONST()
{
  DC_CALL( CalcBoundingBox(x, y) );
}

//----------------------------------------------------------------------------
//! Clears the device context using the current background brush.
//----------------------------------------------------------------------------
DC_API( void )
clear() DC_CONST()
{
  DC_CALL( Clear() );
}

//----------------------------------------------------------------------------
//! Displays a cross hair using the current pen. This is a vertical and
//! horizontal line the height and width of the window, centred on the given
//! point.
//----------------------------------------------------------------------------
DC_API( void )
cross_hair(vector_type const &x, vector_type const &y) DC_CONST()
{
  DC_CALL( CrossHair(x, y) );
}

//----------------------------------------------------------------------------
//! Move the to the coordinate pair \a x, \a y while drawing a line.
//----------------------------------------------------------------------------
/*
DC_API( void )
line_to(vector_type const &x, vector_type const &y) DC_CONST()
{ 
  DC_CALL( DrawLine(m_penloc.x, m_penloc.y, x, y) )
  m_penloc.x = x;
  m_penloc.y = y;
}
*/

//----------------------------------------------------------------------------
//! Draws an arc of a circle, centred on (xc, yc), with starting point (x1, y1)
//! and ending at (x2, y2).   The current pen is used for the outline and the 
//! current brush for filling the shape.
//----------------------------------------------------------------------------
DC_API( void )
draw_arc(vector_type const &x1, vector_type const &y1, vector_type const &x2,
         vector_type const &y2, vector_type const &xc, vector_type const &yc) 
    DC_CONST()
{
  DC_CALL( DrawArc(x1, y1, x2, y2, xc, yc) );
}  

//----------------------------------------------------------------------------
//! Draw a bitmap on the device context at the specified point. If transparent
//! is true and the bitmap has a transparency mask, the bitmap will be drawn 
//! transparently.
//----------------------------------------------------------------------------
template<class bitmap>
DC_API( void )
draw_bitmap(bitmap const &bmp, vector_type const &x, vector_type const &y, 
            bool transparent DC_DEFAULT(false)) DC_CONST()
{
  DC_CALL( DrawBitmap(bmp, x, y, transparent) );
}
  
//----------------------------------------------------------------------------
//! Draw a circle with the given centre and radius.
//----------------------------------------------------------------------------
DC_API( void )
draw_circle(vector_type const &x, vector_type const &y, 
            vector_type const &r) DC_CONST()
{
  DC_CALL( DrawCircle(x, y, r) );
}
  
DC_API( void )
draw_circle(point_type const &pt, vector_type const &r) DC_CONST()
{
  DC_CALL( DrawCircle(wxPoint(pt.x(), pt.y()), r) );
}
  
//----------------------------------------------------------------------------
//! Draws an ellipse contained in the rectangle specified either with the
//! given top left corner and the given size or directly. The current pen
//! is used for the outline and the current brush for filling the shape.
//----------------------------------------------------------------------------
DC_API( void )
draw_ellipse(vector_type const &x, vector_type const &y,
             vector_type const &w, vector_type const &h) DC_CONST()
{
  DC_CALL( DrawEllipse(x, y, w, h) );
}

DC_API( void )
draw_ellipse(point_type const &pt, size_type const &sz) DC_CONST()
{
  DC_CALL( DrawEllipse(pt, sz) );
}

DC_API( void )
draw_ellipse(const rect_type &r) DC_CONST()
{
  DC_CALL( DrawEllipse(r) );
}
  
//----------------------------------------------------------------------------
//! Draws an arc of an ellipse. The current pen is used for drawing the arc 
//! and the current brush is used for drawing the pie.
//! x and y specify the x and y coordinates of the upper-left corner of the 
//! rectangle that contains the ellipse.
//! width and height specify the width and height of the rectangle that
//! contains the ellipse.
//!
//! start and end specify the start and end of the arc relative to the three-
//! o'clock position from the center of the rectangle. Angles are specified 
//! in degrees (360 is a complete circle). Positive values mean counter-
//! clockwise motion. If start is equal to end, a complete ellipse will be drawn.
//----------------------------------------------------------------------------
DC_API( void )
draw_elliptic_arc(vector_type const &x, vector_type const &y, 
         vector_type const &width, vector_type const &height,
         double start, double end) DC_CONST()
{
  DC_CALL( DrawEllipticArc(x, y, width, height, start, end) );
}

//----------------------------------------------------------------------------
//! Draw an icon on the display (does nothing if the device context is
//! PostScript). This can be the simplest way of drawing bitmaps on a window.
//----------------------------------------------------------------------------
template<class icon>
DC_API( void )
draw_icon(icon const &i, vector_type const &x, vector_type const &y)
{
  DC_CALL( DrawIcon(i, x, y) );
}

//----------------------------------------------------------------------------
//! Draw optional bitmap and the text into the given rectangle and aligns it 
//! as specified by alignment parameter; it also will emphasize the character
//! with the given index if it is != -1 and return the bounding rectangle if 
//! required.
//----------------------------------------------------------------------------
template<class bitmap>
DC_API( void )
draw_label(std::string const &text, bitmap const &image, rect_type const &rect,
           int a DC_DEFAULT( (int)(types::align_left|types::align_top) ))
  DC_CONST()
{
  DC_CALL( DrawLabel(text, image, rect, a) );
}

DC_API( void )
draw_label(std::string const &text, rect_type const &rect, int a
           DC_DEFAULT(types::align_left|types::align_top))
  DC_CONST()
{
  DC_CALL( DrawLabel(text, rect, a) );
}

//----------------------------------------------------------------------------
//! Draws a line from the first point to the second. The current pen is used
//! for drawing the line. Note that the point (x2, y2) is not part of the line
//! and is not drawn by this function (this is consistent with the behaviour
//! of many other toolkits).
//----------------------------------------------------------------------------
DC_API( void )
draw_line(vector_type const &x1, vector_type const &y1,
          vector_type const &x2, vector_type const &y2) DC_CONST()
{
  DC_CALL( DrawLine(x1, y1, x2, y2) );
}

DC_API( void )
draw_line(point_type const &s, point_type const &e) DC_CONST()
{
  DC_CALL( DrawLine(s.x(), s.y(), e.x(), e.y()) );
}

//----------------------------------------------------------------------------
//! Draws lines using an array of points of size n, or list of pointers to
//! points, adding the optional offset coordinate. The current pen is used for
//! drawing the lines.  The programmer is responsible for deleting the list of
//! points.
//----------------------------------------------------------------------------
DC_API( void )
draw_lines(unsigned n, point_type const pts[], vector_type const &xoffset = 0,
           vector_type const &yoffset = 0) DC_CONST()
{
  wxPoint points[n];
  for(index_type i = 0; i < n; i++)
  {
    points[i].x = pts[i].x();
    points[i].y = pts[i].y();
  }
  DC_CALL( DrawLines(n, pts, xoffset, yoffset) );
}

//----------------------------------------------------------------------------
//! Draw a polygon through the specified points \a pts.
//----------------------------------------------------------------------------
DC_API( void )
draw_polygon(unsigned n, point_type const pts[], 
             vector_type const &xoffset = 0,
             vector_type const &yoffset = 0) DC_CONST()
{
  wxPoint points[n];
  for(index_type i = 0; i < n; i++)
  {
    points[i].x = pts[i].x();
    points[i].y = pts[i].y();
  }
  DC_CALL( DrawPolygon(n, points, xoffset, yoffset) );
}
  
//----------------------------------------------------------------------------
//! Draw a point at the coordinate pair \a x, \a y.
//----------------------------------------------------------------------------
DC_API( void )
draw_point(vector_type const &x, vector_type const &y) DC_CONST()
{ 
  DC_CALL( DrawPoint(x, y) );
}

//----------------------------------------------------------------------------
//! Draws a rectangle with the given top left corner, and with the given size.
//! The current pen is used for the outline and the current brush for filling 
//! the shape.
//----------------------------------------------------------------------------
DC_API( void )
draw_rect(vector_type const &x1, vector_type const &y1, 
          vector_type const &x2, vector_type const &y2) DC_CONST()
{
  DC_CALL( DrawRectangle(x1, y1, x2, y2) );
}

DC_API( void )
draw_rect(const rect_type &r) DC_CONST()
{
  DC_CALL( DrawRectangle(r.GetX(), r.GetY(), r.GetWidth(), r.GetHeight()) );
}

//----------------------------------------------------------------------------
//! Draws the text rotated by angle degrees.
//----------------------------------------------------------------------------
DC_API( void )
draw_rotated_text(std::string const &text, 
                  vector_type const &x, vector_type const &y, double angle) 
  DC_CONST()
{
  DC_CALL( DrawRotatedText(text, x, y, angle) );
}

//----------------------------------------------------------------------------
//! Draws a rectangle with the given top left corner, and with the given size.
//! The corners are quarter-circles using the given radius. The current pen
//! is used for the outline and the current brush for filling the shape.
//! If radius is positive, the value is assumed to be the radius of the
//! rounded corner. If radius is negative, the absolute value is assumed to be
//! the proportion of the smallest dimension of the rectangle. This means that
//! the corner can be a sensible size relative to the size of the rectangle,
//! and also avoids the strange effects X produces when the corners are too 
//! big for the rectangle.
//----------------------------------------------------------------------------
DC_API( void )
draw_rounded_rectangle(vector_type const &x, vector_type const &y,
                       vector_type const &width, vector_type const &height,
                       double radius)
  DC_CONST()
{
  DC_CALL( DrawRoundedRectangle(x, y, width, height, radius) );
}

//----------------------------------------------------------------------------
//! Draws a spline between all given control points, using the current pen.
//----------------------------------------------------------------------------
DC_API( void )
draw_spline(unsigned n, point_type const pts[]) DC_CONST()
{
  wxPoint points[n];
  for(index_type i = 0; i < n; i++)
  {
    points[i].x = pts[i].x();
    points[i].y = pts[i].y();
  }
  DC_CALL( DrawSpline(n, points) );
}

//----------------------------------------------------------------------------
//! Draws a three-point spline using the current pen.
//----------------------------------------------------------------------------
DC_API( void )
draw_spline(vector_type const &x1, vector_type const &y1,
            vector_type const &x2, vector_type const &y2,
            vector_type const &x3, vector_type const &y3) DC_CONST()
{
  DC_CALL( DrawSpline(x1, y1, x2, y2, x3, y3) );
}

//----------------------------------------------------------------------------
//! Draws a text string at the specified point, using the current text font, 
//! and the current text foreground and background colours.
//! The coordinates refer to the top-left corner of the rectangle bounding the
//! string. See wxDC::GetTextExtent for how to get the dimensions of a text 
//! string, which can be used to position the text more precisely.
//----------------------------------------------------------------------------
DC_API( void )
draw_text(std::string const &s, vector_type const &x, vector_type const &y) 
  DC_CONST()
{
  DC_CALL( DrawText(s, x, y) );
}

//----------------------------------------------------------------------------
//! Draw the text \a s, aligned according to \a a to the destination 
//! rectangle \a r.
//----------------------------------------------------------------------------
DC_API( void )
draw_text(std::string const &s, rect_type const &r, int a DC_DEFAULT(types::align_center)) DC_CONST()
{
  int x, y;
  int w, h;
  
  DC_CALL( GetTextExtent(s.c_str(), &w, &h) );
  
  switch(a)
  {
  case types::align_center:
    x = r.GetX() + (r.GetWidth() - w) / 2;
    y = r.GetY();
    break;
    
  case types::align_right:
    x = r.GetX() + (w - r.GetWidth());
    y = r.GetY();
    break;
    
  default:
    x = r.GetX();
    y = r.GetY();
    break;
  }
  
  DC_CALL( DrawText(s, x, y) );
}

//----------------------------------------------------------------------------
//! Gets the character height of the currently set font.
//----------------------------------------------------------------------------
DC_API( vector_type )
get_char_height() DC_CONST(const)
{
  return DC_CALL( GetCharHeight() );
}

//----------------------------------------------------------------------------
//! Gets the average character width of the currently set font.
//----------------------------------------------------------------------------
DC_API( vector_type )
get_char_width() DC_CONST(const)
{
  return DC_CALL( GetCharWidth() );
}

//----------------------------------------------------------------------------
//! Gets the rectangle surrounding the current clipping region.
//----------------------------------------------------------------------------
DC_API( void )
get_clip(vector_type &x, vector_type &y,
         vector_type &width, vector_type &height) 
  DC_CONST(const)
{
  DC_CALL( GetClippingBox(&x, &y, &width, &height) );
}

DC_API( void )
get_clip(rect_type &r)
  DC_CONST(const)
{
  vector_type x, y, w, h;
  DC_CALL( GetClippingBox(&x, &y, &w, &h) );
  r.SetX(x);
  r.SetY(y);
  r.SetWidth(w);
  r.SetHeight(h);
}

DC_API( rect_type )
get_clip() DC_CONST(const)
{
  vector_type x, y, w, h;
  DC_CALL( GetClippingBox(&x, &y, &w, &h) );
  return rect_type(x, y, w, h);
}

//----------------------------------------------------------------------------
//! Set the clipping region to \a r.
//----------------------------------------------------------------------------
DC_API( void )
set_clip(rect_type const &r) DC_CONST()
{
//  m_clip = r;
  DC_CALL( SetClippingRegion(r.GetX(), r.GetY(), r.GetWidth(), r.GetHeight()) );
}

//----------------------------------------------------------------------------
//! Convert device coordinates to logical coordinates, using the current 
//! mapping mode.
//----------------------------------------------------------------------------
DC_API( point_type )
frame_to_local(point_type const &pt) DC_CONST(const)
{
  return point_type(DC_CALL( DeviceToLogicalX(pt.x()) ), 
                    DC_CALL( DeviceToLogicalY(pt.y()) ));
}

//----------------------------------------------------------------------------
//! Convert device dimensions to logical dimensions, using the current 
//! mapping mode.
//----------------------------------------------------------------------------
DC_API( size_type )
frame_to_local(size_type const &sz) DC_CONST(const)
{
  return size_type(DC_CALL( DeviceToLogicalXRel(sz.GetWidth()) ),
                   DC_CALL( DeviceToLogicalYRel(sz.GetHeight()) ));
}

//----------------------------------------------------------------------------
//! Reset the current clipping region (usually to the size of the associated widget).
//----------------------------------------------------------------------------
DC_API( void )
reset_clip() DC_CONST()
{
  int w, h;
  DC_CALL( DestroyClippingRegion() );
}

//----------------------------------------------------------------------------
//! Sets the user scaling factor, useful for applications which require 
//! 'zooming'.
//----------------------------------------------------------------------------
DC_API( void )
set_user_scale(double xscale, double yscale)
{
  DC_CALL( SetUserScale(xscale, yscale) );
}

//----------------------------------------------------------------------------
//! Set the draw style to \a st.
//----------------------------------------------------------------------------
DC_API( void )
set_draw_style(style_type st) DC_CONST()
{
// FIXME
  wxBrush brush = DC_CALL( GetBrush() );
//  brush.SetStyle((st & types::draw_filled) ? wxSOLID : wxTRANSPARENT);
  DC_CALL( SetBrush(brush) );

  wxPen pen = DC_CALL( GetPen() );
//  pen.SetStyle((st & types::draw_stroked) ? wxSOLID : wxTRANSPARENT);
  DC_CALL( SetPen(pen) );
}
  
//----------------------------------------------------------------------------
//! Get the draw style.
//----------------------------------------------------------------------------
DC_API( style_type )
get_draw_style() DC_CONST(const)
{
  int style = 0;
  wxBrush brush = DC_CALL( GetBrush() );
  if(brush.GetStyle() == wxSOLID) style |= types::draw_filled;
  wxPen pen = DC_CALL( GetPen() );
  if(pen.GetStyle() == wxSOLID) style |= types::draw_stroked;
  return style_type(style);
}
    
//----------------------------------------------------------------------------
//! Set the stroke (outline) color to \a c.
//----------------------------------------------------------------------------
DC_API( void )
set_stroke_color(rgba_type const &c) DC_CONST()
{
  wxPen pen = DC_CALL( GetPen() );
  pen.SetColour(c.r, c.g, c.b);
  DC_CALL( SetPen(pen) );
}
  
//----------------------------------------------------------------------------
//! Set the stroke (outline) color to the rgba color represented 
//! by \a r, \a g, \a b and \a a.
//----------------------------------------------------------------------------
DC_API( void )
set_stroke_color(color_type r, color_type g, color_type b, color_type a
                 DC_DEFAULT( boost::integer_traits<color_type>::const_max )) DC_CONST()
{
  wxPen pen = DC_CALL( GetPen() );
  pen.SetColour(wxColour(r, g, b
#if (wxABI_VERSION > 20800)
  , a
#endif
  ));
  DC_CALL( SetPen(pen) );
}
  
//----------------------------------------------------------------------------
//! Get the stroke (outline) color.
//----------------------------------------------------------------------------
DC_API( rgba_type )
get_stroke_color()  DC_CONST(const)
{
  wxPen pen = DC_CALL( GetPen() );
  wxColour colour = pen.GetColour();
  
  return rgba_type(colour.Red(), colour.Green(), colour.Blue(),
#if (wxABI_VERSION > 20800)
  colour.Alpha()
#else
  0
#endif
  );
}
  
//----------------------------------------------------------------------------
//! Set the stroke (outline) width to \a w.
//----------------------------------------------------------------------------
DC_API( void )
set_stroke_width(vector_type w) DC_CONST()
{
  wxPen pen = DC_CALL( GetPen() );
  pen.SetWidth(w);
  DC_CALL( SetPen(pen) );
}

//----------------------------------------------------------------------------
//! Get the stroke (outline) width.
//----------------------------------------------------------------------------
DC_API( vector_type )
get_stroke_width() DC_CONST(const)
{
  wxPen pen = DC_CALL( GetPen() );
  return pen.GetWidth();
}

//----------------------------------------------------------------------------
//! Set the fill color to \a c.
//----------------------------------------------------------------------------
DC_API( void )
set_fill_color(rgba_type const &c) DC_CONST()
{
  wxBrush brush = DC_CALL( GetBrush() );
  brush.SetColour(wxColour(c.r, c.g, c.b
#if (wxABI_VERSION > 20800)
  , c.a
#endif
  ));
  DC_CALL( SetBrush(brush) );
}
  
//----------------------------------------------------------------------------
//! Set the fill color to the rgba color represented by \a r, \a g, \a b and \a a.
//----------------------------------------------------------------------------
DC_API( void )
set_fill_color(color_type r, color_type g, color_type b, color_type a
               DC_DEFAULT( boost::integer_traits<color_type>::const_max )) DC_CONST()
{
  wxBrush brush = DC_CALL( GetBrush() );
  brush.SetColour(wxColour(r, g, b
#if (wxABI_VERSION > 20800)
  , a
#endif
  ));
  DC_CALL( SetBrush(brush) );
}
  
//----------------------------------------------------------------------------
//! Get the fill color.
//----------------------------------------------------------------------------
DC_API( rgba_type )
get_fill_color()  DC_CONST(const)
{
  wxBrush brush = DC_CALL( GetBrush() );
  wxColour colour = brush.GetColour();
  
  return rgba_type(colour.Red(), colour.Green(), colour.Blue(), 
#if (wxABI_VERSION > 20800)
  colour.Alpha()
#else
  0
#endif
  );
}  
  
//----------------------------------------------------------------------------
//! Set the text color to \a c.
//----------------------------------------------------------------------------
DC_API( void )
set_font_color(rgba_type const &c) DC_CONST()
{
  wxColour colour(c.r, c.g, c.b
#if (wxABI_VERSION > 20800)
  , c.a
#endif
  );
  DC_CALL( SetTextForeground(colour) );
}
  
//----------------------------------------------------------------------------
//! Set the font color to the rgba color represented by \a r, \a g, \a b and \a a.
//----------------------------------------------------------------------------
DC_API( void )
set_font_color(color_type r, color_type g, color_type b, color_type a
               DC_DEFAULT( boost::integer_traits<color_type>::const_max )) DC_CONST()
{
  wxColour colour(r, g, b
#if (wxABI_VERSION > 20800)
  , a
#endif
  );
  DC_CALL( SetTextForeground(colour) );
}
  
//----------------------------------------------------------------------------
//! Get the font color.
//----------------------------------------------------------------------------
DC_API( rgba_type )
get_font_color()  DC_CONST(const)
{
  wxColour colour = DC_CALL( GetTextForeground() );
  return rgba_type(colour.Red(), colour.Green(), colour.Blue(),
#if (wxABI_VERSION > 20800)
  colour.Alpha()
#else
  0
#endif
  );
}

//----------------------------------------------------------------------------
//! Set the font type to \a t.
//----------------------------------------------------------------------------
/*DC_API( void )
set_font_type(font_type const &t) DC_CONST()
{
  wxFont font = DC_CALL( GetFont() );
  font.SetFamily(::wx::fonts[t].family);
  DC_CALL( SetFont(font) );
}*/
  
//----------------------------------------------------------------------------
//! Get the font type.
//----------------------------------------------------------------------------
/*DC_API( font_type )
get_font_type()  DC_CONST(const)
{
  wxFont font = DC_CALL( GetFont() );
  for(unsigned i = 0; i < sizeof(::wx::fonts) / sizeof(::wx::fonts[0]); i++)
  {
    if(::wx::fonts[i].family == font.GetFamily())
      return font_type(i);
  }
  return font_type();
}*/
  
//----------------------------------------------------------------------------
//! Set the font style to \a st.
//----------------------------------------------------------------------------
DC_API( void )
set_font_style(style_type st) DC_CONST()
{
  wxFont font = DC_CALL( GetFont() );
  font.SetWeight((st & types::font_bold) ? wxFONTWEIGHT_BOLD : wxFONTWEIGHT_NORMAL);
  font.SetStyle((st & types::font_italic) ? wxFONTSTYLE_ITALIC : wxFONTSTYLE_NORMAL);
  DC_CALL( SetFont(font) );
}

//----------------------------------------------------------------------------
//! Get the font style
//----------------------------------------------------------------------------
DC_API( style_type )
get_font_style()  DC_CONST(const)
{
  wxFont font = DC_CALL( GetFont() );
  return style_type((font.GetWeight() == wxFONTWEIGHT_BOLD ? types::font_bold : 0) |
                    (font.GetStyle() == wxFONTSTYLE_ITALIC ? types::font_italic : 0));
}

//----------------------------------------------------------------------------
//! Set the font size to \a sz.
//----------------------------------------------------------------------------
DC_API( void )
set_font_size(vector_type sz) DC_CONST()
{
  wxFont font = DC_CALL( GetFont() );
  font.SetPointSize(sz);
  DC_CALL( SetFont(font) );
}

//----------------------------------------------------------------------------
//! Get the font size.
//----------------------------------------------------------------------------
DC_API( vector_type )
get_font_size()  DC_CONST(const)
{
  wxFont font = DC_CALL( GetFont() );
  return font.GetPointSize();
}
  
//----------------------------------------------------------------------------
//! Set antialiasing mode. Returns -1 if not supported.
//----------------------------------------------------------------------------
DC_API( int )
set_antialias(bool aa DC_DEFAULT(true)) DC_CONST()
{
  return -1;
}

//----------------------------------------------------------------------------
//! Get antialiasing mode.
//----------------------------------------------------------------------------
DC_API( bool )
get_antialias()  DC_CONST(const)
{
  return false;
}

//----------------------------------------------------------------------------
//! Get system specific pointer to draw-context.
//----------------------------------------------------------------------------
DC_API( void * )
get_pointer()  DC_CONST(const)
{
#ifdef __WXGTK20__
  return DC_CALL( GetGDKWindow() );
#else
  return DC_CALL( GetHDC() );
#endif
}
  
//@}
//----------------------------------------------------------------------------
/*
#undef DC_API
#undef DC_CALL
#undef DC_DEFAULT
*/
