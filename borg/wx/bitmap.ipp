#ifndef BITMAP_API
#define BITMAP_API(ret_type) ret_type
#endif // BITMAP_API

#ifndef BITMAP_CALL
#define BITMAP_CALL(call_fn) call_fn
#endif // BITMAP_CALL

#ifndef BITMAP_CONST
#define BITMAP_CONST(c) c
#endif // BITMAP_CONST

#ifndef BITMAP_DEFAULT
#define BITMAP_DEFAULT(def_value) = def_value
#endif // BITMAP_DEFAULT

//----------------------------------------------------------------------------
//! \name Implementation of the abstract::dc interface ontop wxWidgets.
//----------------------------------------------------------------------------
//@{

//----------------------------------------------------------------------------
//! Get the bitmap size.
//----------------------------------------------------------------------------
BITMAP_API( size_type )
size() BITMAP_CONST(const)
{
  return size_type(BITMAP_CALL( GetWidth() ), BITMAP_CALL( GetHeight() ));
}

//----------------------------------------------------------------------------
//! Get the bitmap width.
//----------------------------------------------------------------------------
BITMAP_API( vector_type )
width() BITMAP_CONST(const)
{
  return BITMAP_CALL( GetWidth() );
}

//----------------------------------------------------------------------------
//! Get the bitmap height.
//----------------------------------------------------------------------------
BITMAP_API( vector_type )
height() BITMAP_CONST(const)
{
  return BITMAP_CALL( GetHeight() );
}

//----------------------------------------------------------------------------
//! Load bitmap from disk.
//----------------------------------------------------------------------------
BITMAP_API( void )
draw(const dc_type &dc, const rect_type &r, const point_type &o
     BITMAP_DEFAULT(point_type(0, 0)))
{
  dc.Blit(r.x, r.y, r.GetWidth(), r.GetHeight(), &dc, o.x, o.y);
}

//----------------------------------------------------------------------------
//! Return system-specific pointer to bitmap.
//----------------------------------------------------------------------------
BITMAP_API( void * )
get_pointer() const
{
#if WIN32
  return BITMAP_CALL( GetHBITMAP() );
#else
#warning "No wx_bitmap_wrapper::get_pointer() implementation on this platform..."
#endif
}

//----------------------------------------------------------------------------
BITMAP_API( int )
get_depth() const
{
  return BITMAP_CALL( GetDepth() );
}

//----------------------------------------------------------------------------
BITMAP_API( void )
set_depth(int depth) const
{
  BITMAP_CALL( SetDepth(depth) );
}

//----------------------------------------------------------------------------
BITMAP_API( bitmap_type )
get_sub_bitmap(const rect_type &r) const
{
  return BITMAP_CALL( GetSubBitmap(r) );
}

//----------------------------------------------------------------------------
BITMAP_API( bool )
load_file(const std::string &name) const
{
  unsigned extpos = name.rfind('.');
  wxBitmapType type;
  std::string ext = (extpos < name.length()) ? name.substr(extpos + 1) : "";

//  cout << "load_file(" << ext << ")" << endl;

  if(ext == "bmp") type = wxBITMAP_TYPE_BMP;
  else if(ext == "gif") type = wxBITMAP_TYPE_GIF;
  else if(ext == "xbm") type = wxBITMAP_TYPE_XBM;
  else if(ext == "xpm") type = wxBITMAP_TYPE_XPM;
  else if(ext == "jpg") type = wxBITMAP_TYPE_JPEG;
  else if(ext == "jpeg") type = wxBITMAP_TYPE_JPEG;
  else if(ext == "png") type = wxBITMAP_TYPE_PNG;
  else if(ext == "pcx") type = wxBITMAP_TYPE_PCX;
  else if(ext == "pnm") type = wxBITMAP_TYPE_PNM;
#if WIN32
  else type = wxBITMAP_TYPE_BMP_RESOURCE;
#else
  else type = wxBITMAP_TYPE_PICT_RESOURCE;
#endif  

  return BITMAP_CALL( LoadFile(name, type) );
}

//----------------------------------------------------------------------------
BITMAP_API( bool )
is_ok() const
{
  return BITMAP_CALL( IsOk() );
}
  
//@}
//----------------------------------------------------------------------------

#undef BITMAP_API
#undef BITMAP_DEFAULT
