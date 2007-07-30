#ifndef DC_API
#define DC_API(ret_type) ret_type
#endif // DC_API

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
move_to(const vector_type &x, const vector_type &y);

//----------------------------------------------------------------------------
//! Move the to the coordinate pair \a x, \a y while drawing a line.
//----------------------------------------------------------------------------
DC_API( void )
line_to(const vector_type &x, const vector_type &y);

//----------------------------------------------------------------------------
//! Draw a point at the coordinate pair \a x, \a y.
//----------------------------------------------------------------------------
DC_API( void )
draw_point(const vector_type &x, const vector_type &y);

//----------------------------------------------------------------------------
//! Draw a line from point \a s to point \a e.
//----------------------------------------------------------------------------
DC_API( void )
draw_line(const point_type &s, const point_type &e);
  
//----------------------------------------------------------------------------
//! Draw a rectangle with the position and dimensions of \a r.
//----------------------------------------------------------------------------
DC_API( void )
draw_rect(const rect_type &r);
  
//----------------------------------------------------------------------------
//! Draw an ellipse with the position and dimensions of \a r.
//----------------------------------------------------------------------------
DC_API( void )
draw_ellipse(const rect_type &r);

//----------------------------------------------------------------------------
//! Draw an arc within the rectangle \a r, spanning from angle \a s to angle \a e.
//----------------------------------------------------------------------------
DC_API( void )
draw_arc(const rect_type &r, float s, float e);

//----------------------------------------------------------------------------
//! Draw a polygon through the specified points \a pts.
//----------------------------------------------------------------------------
DC_API( void )
draw_polygon(const point_type pts[], size_t n);

//----------------------------------------------------------------------------
//! Set the clipping region to \a r.
//----------------------------------------------------------------------------
DC_API( void )
set_clip(const rect_type &r);

//----------------------------------------------------------------------------
//! Get the current clipping region.
//----------------------------------------------------------------------------
DC_API( rect_type )
get_clip() const;

//----------------------------------------------------------------------------
//! Reset the current clipping region (usually to the size of the associated 
//! widget).
//----------------------------------------------------------------------------
DC_API( void )
reset_clip();

//----------------------------------------------------------------------------
//! Set the draw style to \a st.
//----------------------------------------------------------------------------
DC_API( void )
set_draw_style(draw_style st);

//----------------------------------------------------------------------------
//! Get the draw style.
//----------------------------------------------------------------------------
DC_API( draw_style )
get_draw_style() const;
    
//----------------------------------------------------------------------------
//! Set the stroke (outline) color to \a c.
//----------------------------------------------------------------------------
DC_API( void )
set_stroke_color(const rgba_type &c);
  
//----------------------------------------------------------------------------
//! Set the stroke (outline) color to the rgba color represented 
//! by \a r, \a g, \a b and \a a.
//----------------------------------------------------------------------------
DC_API( void )
set_stroke_color(color_type r, color_type g, color_type b, color_type a
                 DC_DEFAULT( boost::integer_traits<color_type>::const_max ));
  
//----------------------------------------------------------------------------
//! Get the stroke (outline) color.
//----------------------------------------------------------------------------
DC_API( typename traits::rgba_type )
get_stroke_color() const;

//----------------------------------------------------------------------------
//! Set the stroke (outline) width to \a w.
//----------------------------------------------------------------------------
DC_API( void )
set_stroke_width(vector_type w);

//----------------------------------------------------------------------------
//! Get the stroke (outline) width.
//----------------------------------------------------------------------------
DC_API( vector_type )
get_stroke_width() const;

//----------------------------------------------------------------------------
//! Set the fill color to \a c.
//----------------------------------------------------------------------------
DC_API( void )
set_fill_color(const rgba_type &c);

//----------------------------------------------------------------------------
//! Set the fill color to the rgba color represented
//! by \a r, \a g, \a b and \a a.
//----------------------------------------------------------------------------
DC_API( void )
set_fill_color(color_type r, color_type g, color_type b, color_type a
               DC_DEFAULT( boost::integer_traits<color_type>::const_max ));

//----------------------------------------------------------------------------
//! Get the fill color.
//----------------------------------------------------------------------------
DC_API( typename traits::rgba_type )
get_fill_color() const;

//----------------------------------------------------------------------------
//! Set the text color to \a c.
//----------------------------------------------------------------------------
DC_API( void )
set_font_color(const rgba_type &c);

//----------------------------------------------------------------------------
//! Set the font color to the rgba color represented 
//! by \a r, \a g, \a b and \a a.
//----------------------------------------------------------------------------
DC_API( void )
set_font_color(color_type r, color_type g, color_type b, color_type a
               DC_DEFAULT( boost::integer_traits<color_type>::const_max ));

//----------------------------------------------------------------------------
//! Get the font color.
//----------------------------------------------------------------------------
DC_API( typename traits::rgba_type )
get_font_color() const;

//----------------------------------------------------------------------------
//! Set the font type to \a t.
//----------------------------------------------------------------------------
DC_API( void )
set_font_type(const font_type &t);
  
//----------------------------------------------------------------------------
//! Get the font type.
//----------------------------------------------------------------------------
DC_API( font_type )
get_font_type() const;

//----------------------------------------------------------------------------
//! Set the font style to \a st.
//----------------------------------------------------------------------------
DC_API( void )
set_font_style(font_style st);

//----------------------------------------------------------------------------
//! Get the font style
//----------------------------------------------------------------------------
DC_API( font_style )
get_font_style() const;

//----------------------------------------------------------------------------
//! Set the font size to \a sz.
//----------------------------------------------------------------------------
DC_API( void )
set_font_size(vector_type sz);

//----------------------------------------------------------------------------
//! Get the font size.
//----------------------------------------------------------------------------
DC_API( vector_type )
get_font_size() const;

//----------------------------------------------------------------------------
//! Draw the text \a s, aligned according to \a a to the destination 
//! rectangle \a r.
//----------------------------------------------------------------------------
DC_API( void )
draw_text(const std::string &s, const rect_type &r, text_align a 
          DC_DEFAULT(align_center));

//----------------------------------------------------------------------------
//! Set antialiasing mode. Returns -1 if not supported.
//----------------------------------------------------------------------------
DC_API( int )
set_antialias(bool aa DC_DEFAULT(true));

//----------------------------------------------------------------------------
//! Get antialiasing mode.
//----------------------------------------------------------------------------
DC_API( bool )
get_antialias() const;

//----------------------------------------------------------------------------
//! Return system-specific pointer to drawcontext.
//----------------------------------------------------------------------------
DC_API( void * )
get_pointer() const;

//@}
//----------------------------------------------------------------------------

#undef DC_API
#undef DC_DEFAULT
