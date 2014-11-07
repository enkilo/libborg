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

#ifndef WIDGET_API
#define WIDGET_API(ret_type) ret_type
#endif // WIDGET_API

#ifndef WIDGET_CALL
#define WIDGET_CALL(fn_call) fn_call;
#endif // WIDGET_CALL

#ifndef WIDGET_DEFAULT
#define WIDGET_DEFAULT(def_value) = def_value
#endif // WIDGET_DEFAULT

//----------------------------------------------------------------------------
//! \name Implementation of the abstract::dc interface ontop VSTGUI.
//----------------------------------------------------------------------------
//@{

//----------------------------------------------------------------------------
//! Stores the position of the widget into \a pt.
//----------------------------------------------------------------------------
WIDGET_API( void )
pos(point_type &pt) const
{
  CRect rect = WIDGET_CALL( getViewSize() )
  pt.x = rect.x;
  pt.y = rect.y;
}

//----------------------------------------------------------------------------
//! Moves the widget to the position \a pt.
//----------------------------------------------------------------------------
WIDGET_API( void )
move(const point_type &pt)
{
  CRect rect = WIDGET_CALL( getViewSize() )
  rect.x = pt.x;
  rect.y = pt.y;
  WIDGET_CALL( setViewSize(rect) )
}

//----------------------------------------------------------------------------
//! Stores the size of the widget into \a sz.
//----------------------------------------------------------------------------
WIDGET_API( void )
size(size_type &sz) const
{
  CRect rect = WIDGET_CALL( getViewSize() )
  sz.x = rect.getWidth();
  sz.y = rect.getHeight();
}

//----------------------------------------------------------------------------
//! Resizes the widget to the size \a sz.
//----------------------------------------------------------------------------
WIDGET_API( void )
resize(const size_type &sz)
{
  CRect rect = WIDGET_CALL( getViewSize() )
  rect.setWidth(sz.x);
  rect.setHeight(sz.y);
  WIDGET_CALL( setViewSize(rect) )
}

//----------------------------------------------------------------------------
//! Stores position and size into \a rt.
//----------------------------------------------------------------------------
WIDGET_API( void )
rect(rect_type &rt) const
{
  rt = WIDGET_CALL( getViewSize() )
/*  rt.x() = rect.x;
  rt.y() = rect.y;
  rt.w() = rect.width();
  rt.h() = rect.height();*/
}

//----------------------------------------------------------------------------
//! Marks the widget as dirty so it gets redrawn next time in event loop.
//----------------------------------------------------------------------------
WIDGET_API( void )
set_dirty(bool d WIDGET_DEFAULT(true))
{
  WIDGET_CALL( setDirty(d) )
}

//----------------------------------------------------------------------------
//! Is the widget marked as dirty?
//----------------------------------------------------------------------------
WIDGET_API( bool )
is_dirty()
{
  return WIDGET_CALL( isDirty() )
}

//----------------------------------------------------------------------------
//! Shows or hides the widget according to \a sw.
//----------------------------------------------------------------------------
/*WIDGET_API( void )
show(bool sw WIDGET_DEFAULT(true))
{
}*/

//----------------------------------------------------------------------------
//! Gets the system specific window handle of the widget.
//----------------------------------------------------------------------------
/*WIDGET_API( void * )
get_pointer()
{
}*/

//----------------------------------------------------------------------------
//! Gets the parent widget.
//----------------------------------------------------------------------------
WIDGET_API( widget_type )
get_parent()
{
  WIDGET_CALL( getParentView() )
}

//@}
//----------------------------------------------------------------------------

#undef WIDGET_API
#undef WIDGET_CALL
#undef WIDGET_DEFAULT
