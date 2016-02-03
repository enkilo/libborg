#ifndef WINDOW_API
#define WINDOW_API(ret_type) ret_type
#endif // WINDOW_API

#ifndef WINDOW_CALL
#define WINDOW_CALL(fn_call) fn_call;
#endif // WINDOW_CALL

#ifndef WINDOW_DEFAULT
#define WINDOW_DEFAULT(def_value) = def_value
#endif // WINDOW_DEFAULT

#ifndef WINDOW_CONST
#define WINDOW_CONST(c) c
#endif // WINDOW_CONST

//----------------------------------------------------------------------------
//! \name Implementation of the wxWindow interface.
//----------------------------------------------------------------------------
//@{

//----------------------------------------------------------------------------
//! 
//----------------------------------------------------------------------------
WINDOW_API( void ) 
add_child(const widget_type &child) WINDOW_CONST()
{
  WINDOW_CALL( AddChild(child) );
}

//----------------------------------------------------------------------------
//! Sets the cached best size value.
//----------------------------------------------------------------------------
WINDOW_API( void ) 
cache_best_size(const size_type &sz) WINDOW_CONST(const)
{
  WINDOW_CALL( CacheBestSize(sz) );
}

//----------------------------------------------------------------------------
//! Directs all mouse input to this window. Call wxWindow::ReleaseMouse to
//! release the capture.
//! Note that wxWidgets maintains the stack of windows having captured the
//! mouse and when the mouse is released the capture returns to the window
//! which had had captured it previously and it is only really released if
//! there were no previous window. In particular, this means that you must
//! release the mouse as many times as you capture it, unless the window 
//! receives the wxMouseCaptureLostEvent event.
//!
//! Any application which captures the mouse in the beginning of some operation
//! must handle wxMouseCaptureLostEventand cancel this operation when it 
//! receives the event. The event handler must not recapture mouse.
//----------------------------------------------------------------------------
WINDOW_API( void ) 
capture_mouse()
{
  WINDOW_CALL( CaptureMouse() );
}

//----------------------------------------------------------------------------
//! Center.
//----------------------------------------------------------------------------
WINDOW_API( void )
center(types::dimension dim) WINDOW_CONST()
{
  int d = 0;
  switch(dim)
  {
    case types::horizontal: d = wxHORIZONTAL; break;
    case types::vertical: d = wxVERTICAL; break;
    case types::both: d = wxBOTH; break;
  }

  WINDOW_CALL( Center(d) );
}

//----------------------------------------------------------------------------
//! Center on parent.
//----------------------------------------------------------------------------
WINDOW_API( void )
center_on_parent(types::dimension dim) WINDOW_CONST()
{
  int d = 0;
  switch(dim)
  {
    case types::horizontal: d = wxHORIZONTAL; break;
    case types::vertical: d = wxVERTICAL; break;
    case types::both: d = wxBOTH; break;
  }

  WINDOW_CALL( CenterOnParent(d) );
}

//----------------------------------------------------------------------------
//! Center on screen.
//----------------------------------------------------------------------------
WINDOW_API( void )
center_on_screen(types::dimension dim) WINDOW_CONST()
{
  int d = 0;
  switch(dim)
  {
    case types::horizontal: d = wxHORIZONTAL; break;
    case types::vertical: d = wxVERTICAL; break;
    case types::both: d = wxBOTH; break;
  }

  WINDOW_CALL( CenterOnScreen(d) );
}

//----------------------------------------------------------------------------
//! Clears the window by filling it with the current background colour. Does 
//! not cause an erase background event to be generated.
//----------------------------------------------------------------------------
WINDOW_API( void )
clear_background() WINDOW_CONST()
{
  WINDOW_CALL( ClearBackground() );
}

//----------------------------------------------------------------------------
//! Converts to screen coordinates from coordinates relative to this window.
//----------------------------------------------------------------------------
WINDOW_API( void )
client_to_screen(vector_type &x, vector_type &y) WINDOW_CONST(const)
{
  WINDOW_CALL( ClientToScreen(&x, &y) );
}

WINDOW_API( void )
client_to_screen(point_type &pt) WINDOW_CONST(const)
{
  WINDOW_CALL( ClientToScreen(&pt.x(), &pt.y()) );
}

WINDOW_API( point_type )
client_to_screen(const point_type &pt) WINDOW_CONST(const)
{
  point_type ret = pt;
  WINDOW_CALL( ClientToScreen(&ret.x(), &ret.y()) );
  return ret;
}

//----------------------------------------------------------------------------
//! This function simply generates a wxCloseEvent whose handler usually tries
//! to close the window. It doesn't close the window itself, however.
//----------------------------------------------------------------------------
WINDOW_API( bool )
close(bool force WINDOW_DEFAULT(false)) WINDOW_CONST()
{
  return WINDOW_CALL( Close(force) );
}

//----------------------------------------------------------------------------
//! Converts a point or size from dialog units to pixels.
//! For the x dimension, the dialog units are multiplied by the average
//! character width and then divided by 4.
//! For the y dimension, the dialog units are multiplied by the average 
//! character height and then divided by 8.
//----------------------------------------------------------------------------
WINDOW_API( point_type )
convert_dialog_to_pixels(const point_type &pt) WINDOW_CONST(const)
{
  wxPoint ret = WINDOW_CALL( ConvertPixelsToDialog(wxPoint(pt.x(), pt.y())) );
  return point_type(ret.x, ret.y);
}

WINDOW_API( size_type )
convert_dialog_to_pixels(const size_type &pt) WINDOW_CONST(const)
{
  wxSize ret = WINDOW_CALL( ConvertPixelsToDialog(wxSize(pt.x(), pt.y())) );
  return size_type(ret.x, ret.y);
}

//----------------------------------------------------------------------------
//! Destroys the window safely. Use this function instead of the delete
//! operator, since different window classes can be destroyed differently.
//! Frames and dialogs are not destroyed immediately when this function is
//! called -- they are added to a list of windows to be deleted on idle time,
//! when all the window's events have been processed. This prevents problems 
//! with events being sent to non-existent windows.
//----------------------------------------------------------------------------
WINDOW_API( bool )
destroy() WINDOW_CONST()
{
  return WINDOW_CALL( Destroy() );
}

//----------------------------------------------------------------------------
//! Destroys all children of a window.  Called automatically by the destructor.
//----------------------------------------------------------------------------
WINDOW_API( void )
destroy_children() WINDOW_CONST()
{
  WINDOW_CALL( DestroyChildren() );
}

//----------------------------------------------------------------------------
//! Disables the window, same as Enable(false).
//----------------------------------------------------------------------------
WINDOW_API( bool )
disable() WINDOW_CONST()
{
  return WINDOW_CALL( Disable() );
}

//----------------------------------------------------------------------------
//! Gets the size which best suits the window: for a control, it would be the
//! minimal size which doesn't truncate the control, for a panel - the same 
//! size as it would have after a call to Fit().
//----------------------------------------------------------------------------
#if WIN32
WINDOW_API( void )
drag_accept_files(bool accept WINDOW_DEFAULT(true)) WINDOW_CONST()
{
  WINDOW_CALL( DragAcceptFiles(accept) );
}
#endif // WIN32

//----------------------------------------------------------------------------
//! Enable or disable the window for user input. Note that when a parent
//! window is disabled, all of its children are disabled as well and they 
//! are reenabled again when the parent is.
//----------------------------------------------------------------------------
WINDOW_API( bool )
enable(bool e WINDOW_DEFAULT(true)) WINDOW_CONST()
{
  return WINDOW_CALL( Enable(e) );
}

//----------------------------------------------------------------------------
//! Finds the window or control which currently has the keyboard focus.
//----------------------------------------------------------------------------
static WINDOW_API( widget_type )
find_focus()
{
  return wxWindow::FindFocus();
}

//----------------------------------------------------------------------------
//! Find a child of this window, by identifier.
//----------------------------------------------------------------------------
WINDOW_API( widget_type )
find_window(long id) WINDOW_CONST(const)
{
  return WINDOW_CALL( FindWindow(id) );
}

//----------------------------------------------------------------------------
//! Find a child of this window, by name.
//----------------------------------------------------------------------------
WINDOW_API( widget_type )
find_window(const std::string &name) WINDOW_CONST(const)
{
  return WINDOW_CALL( FindWindow(name) );
}

//----------------------------------------------------------------------------
//! Find the first window with the given id.
//! If parent is NULL, the search will start from all top-level frames and
//! dialog boxes; if non-NULL, the search will be limited to the given window 
//! hierarchy. The search is recursive in both cases.
//----------------------------------------------------------------------------
static WINDOW_API( widget_type )
find_window_by_id(long id, const widget_type *parent = 0)
{
  return wxWindow::FindWindowById(id, parent);
}

//----------------------------------------------------------------------------
//! Find a window by its label. Depending on the type of window, the label may
//! be a window title or panel item label. If parent is NULL, the search will
//! start from all top-level frames and dialog boxes; if non-NULL, the search
//! will be limited to the given window hierarchy. The search is recursive in
//! both cases.
//----------------------------------------------------------------------------
static WINDOW_API( widget_type )
find_window_by_label(const std::string &label, const widget_type *parent = 0)
{
  return wxWindow::FindWindowByLabel(label, parent);
}

//----------------------------------------------------------------------------
//! Find a window by its name (as given in a window constructor or Create
//! function call). If parent is NULL, the search will start from all top-
//! level frames and dialog boxes; if non-NULL, the search will be limited to 
//! the given window hierarchy. The search is recursive in both cases.
//! If no window with such name is found,FindWindowByLabel is called.
//----------------------------------------------------------------------------
static WINDOW_API( widget_type )
find_window_by_name(const std::string &name, const widget_type *parent = 0)
{
  return wxWindow::FindWindowByName(name, parent);
}

//----------------------------------------------------------------------------
//! Sizes the window so that it fits around its subwindows.
//! This function won't do anything if there are no subwindows and will only 
//! really work correctly if the sizers are used for the subwindows layout.
//----------------------------------------------------------------------------
WINDOW_API( void )
fit() WINDOW_CONST()
{
  WINDOW_CALL( Fit() );
}

//----------------------------------------------------------------------------
//! Similar to Fit, but sizes the interior (virtual) size of a window.  Mainly
//! useful with scrolled windows to reset scrollbars after sizing changes that
//! do not trigger a size event, and/or scrolled windows without an interior 
//! sizer.  
//! This function similarly won't do anything if there are no subwindows.
//----------------------------------------------------------------------------
WINDOW_API( void )
fit_inside() WINDOW_CONST()
{
  WINDOW_CALL( FitInside() );
}

//----------------------------------------------------------------------------
//! Freezes the window or, in other words, prevents any updates from taking
//! place on screen, the window is not redrawn at all. Thaw must be called to
//! reenable window redrawing. Calls to these two functions may be nested.
//! This method is useful for visual appearance optimization (for example,
//! it is a good idea to use it before doing many large text insertions in a
//! row into a wxTextCtrl under wxGTK) but is not implemented on all platforms
//! nor for all controls so it is mostly just a hint to wxWidgets and not a 
//! mandatory directive.
//----------------------------------------------------------------------------
WINDOW_API( void )
freeze() WINDOW_CONST()
{
  WINDOW_CALL( Freeze() );
}

//----------------------------------------------------------------------------
//! Returns the background colour of the window.
//----------------------------------------------------------------------------
WINDOW_API( rgba_type )
get_background_color() WINDOW_CONST(const)
{
  wxColour ret = WINDOW_CALL( GetBackgroundColor() );
  return rgba_type(ret.Red(), ret.Green(), ret.Blue(),
#if (wxABI_VERSION > 20800)
    ret.Alpha()
#else
    0
#endif
  );
}

//----------------------------------------------------------------------------
//! Merges the window's best size into the min size and returns the result.
//! This is the value used by sizers to determine the appropriate ammount of 
//! sapce to allocate for the widget.
//----------------------------------------------------------------------------
WINDOW_API( size_type )
get_effective_min_size() WINDOW_CONST(const)
{
  wxSize ret = WINDOW_CALL( GetEffectiveMinSize() );
  return size_type(ret.x, ret.y);
}

//----------------------------------------------------------------------------
//! This functions returns the best acceptable minimal size for the window.
//! For example, for a static control, it will be the minimal size such that
//! the control label is not truncated. For windows containing subwindows
//! (typicallywxPanel), the size returned by this function will be the same 
//! as the size the window would have had after callingFit.
//----------------------------------------------------------------------------
WINDOW_API( size_type )
get_best_size() WINDOW_CONST(const)
{
  return WINDOW_CALL( GetBestSize() );
}

//----------------------------------------------------------------------------
//! Returns the currently captured window.
//----------------------------------------------------------------------------
static WINDOW_API( widget_type )
get_capture()
{
  return wxWindow::GetCapture();
}

//----------------------------------------------------------------------------
//! Gets the character height of the currently set font.
//----------------------------------------------------------------------------
WINDOW_API( vector_type )
get_char_height() WINDOW_CONST(const)
{
  return WINDOW_CALL( GetCharHeight() );
}

//----------------------------------------------------------------------------
//! Gets the average character width of the currently set font.
//----------------------------------------------------------------------------
WINDOW_API( vector_type )
get_char_width() WINDOW_CONST(const)
{
  return WINDOW_CALL( GetCharWidth() );
}

//----------------------------------------------------------------------------
//! This gets the size of the window 'client area' in pixels. The client area
//! is the area which may be drawn on by the programmer, excluding title bar,
//! border, scrollbars, etc.
//----------------------------------------------------------------------------
WINDOW_API( void )
get_client_size(size_type &sz) WINDOW_CONST(const)
{
  WINDOW_CALL( GetClientSize(sz) );
}

WINDOW_API( size_type )
get_client_size() WINDOW_CONST(const)
{
  wxSize sz = WINDOW_CALL( GetClientSize() );
  return size_type(sz.x, sz.y);
}

//----------------------------------------------------------------------------
#warning "missing GetChildren here..."

//----------------------------------------------------------------------------
//! Returns the foreground colour of the window.
//----------------------------------------------------------------------------
WINDOW_API( rgba_type )
get_foreground_color() WINDOW_CONST(const)
{
  wxColour ret = WINDOW_CALL( GetForegroundColor() );
  return rgba_type(ret.Red(), ret.Green(), ret.Blue(),
#if (wxABI_VERSION > 20800)
    ret.Alpha()
#else
    0
#endif
  );
}

//----------------------------------------------------------------------------
//! Returns the platform-specific handle of the physical window.
//! Cast it to an appropriate handle, such as HWND for Windows, Widget for 
//! Motif, GtkWidget for GTK or WinHandle for PalmOS.
//----------------------------------------------------------------------------
WINDOW_API( void * )
get_handle() WINDOW_CONST(const)
{
  return WINDOW_CALL( GetHandle() );
}

//----------------------------------------------------------------------------
//! Gets the parent widget.
//----------------------------------------------------------------------------
WINDOW_API( widget_type )
get_parent()
{
  return WINDOW_CALL( GetParent() )
}

//----------------------------------------------------------------------------
//! Stores the position of the widget into \a pt.
//----------------------------------------------------------------------------
WINDOW_API( void )
get_position(point_type &pt) const
{
  vector_type x, y;
  WINDOW_CALL( GetPosition(&x, &y) )
  pt.x = x;
  pt.y = y;
}

WINDOW_API( point_type )
get_position() const
{
  vector_type x, y;
  WINDOW_CALL( GetPosition(&x, &y) )
  return point_type(x, y);
}

//----------------------------------------------------------------------------
//! Stores position and size into \a rt.
//----------------------------------------------------------------------------
WINDOW_API( rect_type )
get_rect(rect_type &rt) const
{
  wxRect rect = WINDOW_CALL( GetRect() )
  return rect_type(rect.x, rect.y, rect.width, rect.height);
}

//----------------------------------------------------------------------------
//! Returns the window position in screen coordinates, whether the window is a
//! child window or a top level one.
//----------------------------------------------------------------------------
WINDOW_API( void )
get_screen_position(point_type &pt) const
{
  return WINDOW_CALL( GetScreenPosition(&pt.x(), &pt.y()) )
}

WINDOW_API( point_type )
get_screen_position() const
{
  point_type pt;
  WINDOW_CALL( GetScreenPosition(&pt.x(), &pt.y()) )
  return pt;
}

//----------------------------------------------------------------------------
//! Returns the window position in screen coordinates, whether the window is a
//! child window or a top level one.
//----------------------------------------------------------------------------
WINDOW_API( rect_type )
get_screen_rect() WINDOW_CONST(const)
{
  wxRect sr = WINDOW_CALL( GetScreenRect() );
  return rect_type(sr.x, sr.y, sr.width, sr.height);
}

#warning "missing GetScrollPos() here..."
#warning "missing GetScrollRange() here..."
#warning "missing GetScrollThumb() here..."

//----------------------------------------------------------------------------
//! Stores the size of the widget into \a sz.
//----------------------------------------------------------------------------
WINDOW_API( void )
get_size(vector_type &w, vector_type &h) WINDOW_CONST(const)
{
  WINDOW_CALL( GetSize(&w, &h) )
}

WINDOW_API( void )
get_size(size_type &sz) WINDOW_CONST(const)
{
  WINDOW_CALL( GetSize(sz) )
}

WINDOW_API( size_type )
get_size() WINDOW_CONST( const )
{
  size_type sz;
  WINDOW_CALL( GetSize(sz) );
  return sz;
}

#warning "missing GetTextExtent() here..."
#warning "missing GetUpdateRegion() here..."

//----------------------------------------------------------------------------
//! This gets the virtual size of the window in pixels. By default it returns
//! the client size of the window, but after a call toSetVirtualSize it will 
//! return that size.
//----------------------------------------------------------------------------
WINDOW_API( void )
get_virtual_size(vector_type &w, vector_type &h) WINDOW_CONST(const)
{
  WINDOW_CALL( GetVirtualSize(&w, &h) )
}

WINDOW_API( size_type )
get_virtual_size() WINDOW_CONST( const )
{
  vector_type w, h;
  WINDOW_CALL( GetVirtualSize(&w, &h) );
  return size_type(w, h);
}

//----------------------------------------------------------------------------
//! Returns the size of the left/right and top/bottom borders of this window 
//! in x and y components of the result respectively.
//----------------------------------------------------------------------------
WINDOW_API( size_type )
get_window_border_size() WINDOW_CONST(const)
{
  size_type sz = WINDOW_CALL( GetWindowBorderSize() );
  return size_type(sz.x, sz.y);
}

//----------------------------------------------------------------------------
//! Returns true if this window has the current mouse capture.
//----------------------------------------------------------------------------
WINDOW_API( bool )
has_capture() WINDOW_CONST(const)
{
  return WINDOW_CALL( HasCapture() );
}

//----------------------------------------------------------------------------
//! This method should be overridden to return true if this window has
//! multiple pages. All standard class with multiple pages such as wxNotebook,
//! wxListbook and wxTreebook already override it to return trueand user-
//! defined classes with similar behaviour should do it as well to allow the 
//! library to handle such windows appropriately.
//----------------------------------------------------------------------------
WINDOW_API( bool )
has_multiple_pages() WINDOW_CONST(const)
{
  return WINDOW_CALL( HasMultiplePages() );
}

//----------------------------------------------------------------------------
//! Returns true if this window has a scroll bar for this orientation.
//----------------------------------------------------------------------------
WINDOW_API( bool )
has_scrollbar(int orient) WINDOW_CONST(const)
{
  return WINDOW_CALL( HasScrollbar(orient == horizontal_orientation ? wxHORIZONTAL : wxVERTICAL) );
}

//----------------------------------------------------------------------------
//! Returns true if this window background is transparent (as, for example,
//! for wxStaticText) and should show the parent window background.
//! This method is mostly used internally by the library itself and you
//! normally shouldn't have to call it. You may, however, have to override it
//! in your wxWindow-derived class to ensure that background is painted 
//! correctly.
//----------------------------------------------------------------------------
WINDOW_API( bool )
has_transparent_background() WINDOW_CONST(const)
{
  return WINDOW_CALL( HasTransparentBackground() );
}

//----------------------------------------------------------------------------
//! Equivalent to calling Show(false).
//----------------------------------------------------------------------------
WINDOW_API( bool )
hide() WINDOW_CONST()
{
  return WINDOW_CALL( Hide() );
}

//----------------------------------------------------------------------------
//! This function is (or should be, in case of custom controls) called during
//! window creation to intelligently set up the window visual attributes, that
//! is the font and the foreground and background colours.
//! By "intelligently'' the following is meant: by default, all windows use
//! their own default attributes. However if some of the parents attributes
//! are explicitly (that is, usingSetFont and notSetOwnFont) changed and if
//! the corresponding attribute hadn't been explicitly set for this window
//! itself, then this window takes the same value as used by the parent.
//! In addition, if the window overrides ShouldInheritColoursto return false, 
//! the colours will not be changed no matter what and only the font might.
//!
//! This rather complicated logic is necessary in order to accommodate the
//! different usage scenarios. The most common one is when all default
//! attributes are used and in this case, nothing should be inherited as in
//! modern GUIs different controls use different fonts (and colours) than
//! their siblings so they can't inherit the same value from the parent.
//! However it was also deemed desirable to allow to simply change the
//! attributes of all children at once by just changing the font or colour of
//! their common parent, hence in this case we do inherit the parents 
//! attributes.
//----------------------------------------------------------------------------
WINDOW_API( void )
inherit_attributes() WINDOW_CONST()
{
  return WINDOW_CALL( InheritAttributes() );
}

//----------------------------------------------------------------------------
//! Sends an wxEVT_INIT_DIALOG event, whose handler usually transfers data to 
//! the dialog via validators.
//----------------------------------------------------------------------------
WINDOW_API( void )
init_dialog() WINDOW_CONST()
{
  return WINDOW_CALL( InitDialog() );
}

//----------------------------------------------------------------------------
//! Resets the cached best size value so it will be recalculated the next time
//! it is needed.
//----------------------------------------------------------------------------
WINDOW_API( void )
invalidate_best_size() WINDOW_CONST()
{
  return WINDOW_CALL( InvalidateBestSize() );
}

//----------------------------------------------------------------------------
//! Returns true if the window contents is double-buffered by the system, i.e.
//! if any drawing done on the window is really done on a temporary backing 
//! surface and transferred to the screen all at once later.
//----------------------------------------------------------------------------
WINDOW_API( bool )
is_double_buffered() WINDOW_CONST(const)
{
  return WINDOW_CALL( IsDoubleBuffered() );
}

//----------------------------------------------------------------------------
//! Returns true if the window is enabled for input, false otherwise.
//----------------------------------------------------------------------------
WINDOW_API( bool )
is_enabled() WINDOW_CONST(const)
{
  return WINDOW_CALL( IsEnabled() );
}

//----------------------------------------------------------------------------
//! Returns true if the given point or rectangle area has been exposed since
//! the last repaint. Call this in an paint event handler to optimize 
//! redrawing by only redrawing those areas, which have been exposed.
//----------------------------------------------------------------------------
WINDOW_API( bool )
is_exposed(const vector_type &x, const vector_type &y) WINDOW_CONST(const)
{
  return WINDOW_CALL( IsExposed(x, y) );
}

WINDOW_API( bool )
is_exposed(const point_type &pt) WINDOW_CONST(const)
{
  return WINDOW_CALL( IsExposed(wxPoint(pt.x(), pt.y())) );
}

WINDOW_API( bool )
is_exposed(const vector_type &x, const vector_type &y,
           const vector_type &w, const vector_type &h) WINDOW_CONST(const)
{
  return WINDOW_CALL( IsExposed(x, y, w, h) );
}

WINDOW_API( bool )
is_exposed(const rect_type &r) WINDOW_CONST(const)
{
  return WINDOW_CALL( IsExposed(wxRect(r.GetX(), r.GetY(), r.GetWidth(), r.GetHeight())) );
}

//----------------------------------------------------------------------------
//! Returns true if the window is currently frozen by a call to Freeze().
//----------------------------------------------------------------------------
WINDOW_API( bool )
is_frozen() WINDOW_CONST(const)
{
  return WINDOW_CALL( IsFrozen() );
}

//----------------------------------------------------------------------------
//! Returns true if the window is retained, false otherwise.
//----------------------------------------------------------------------------
WINDOW_API( bool )
is_retained() WINDOW_CONST(const)
{
  return WINDOW_CALL( IsRetained() );
}

//----------------------------------------------------------------------------
//! Returns true if the window is shown, false if it has been hidden.
//----------------------------------------------------------------------------
WINDOW_API( bool )
is_shown() WINDOW_CONST(const)
{
  return WINDOW_CALL( IsShown() );
}

//----------------------------------------------------------------------------
//! Returns true if the window is physically visible on the screen, i.e. it is
//! shown and all its parents up to the toplevel window are shown as well.
//----------------------------------------------------------------------------
WINDOW_API( bool )
is_shown_on_screen() WINDOW_CONST(const)
{
  return WINDOW_CALL( IsShownOnScreen() );
}

//----------------------------------------------------------------------------
//! Returns true if the given window is a top-level one. Currently all frames
//! and dialogs are considered to be top-level windows (even if they have a 
//! parent window).
//----------------------------------------------------------------------------
WINDOW_API( bool )
is_top_level() WINDOW_CONST(const)
{
  return WINDOW_CALL( IsTopLevel() );
}

//----------------------------------------------------------------------------
//! Invokes the constraint-based layout algorithm or the sizer-based algorithm
//! for this window.
//----------------------------------------------------------------------------
WINDOW_API( void )
layout() WINDOW_CONST()
{
  WINDOW_CALL( Layout() );
}

//----------------------------------------------------------------------------
//! Lowers the window to the bottom of the window hierarchy (z-order).
//----------------------------------------------------------------------------
WINDOW_API( void )
lower() WINDOW_CONST()
{
  WINDOW_CALL( Lower() );
}

//----------------------------------------------------------------------------
//! Disables all other windows in the application so that the user can only 
//! interact with this window.
//----------------------------------------------------------------------------
WINDOW_API( void )
make_modal(bool on WINDOW_DEFAULT(true)) WINDOW_CONST()
{
  WINDOW_CALL( MakeModal(on) );
}

//----------------------------------------------------------------------------
//! Moves the widget to the position \a pt.
//----------------------------------------------------------------------------
WINDOW_API( void )
move(const vector_type &x, const vector_type &y)
{
  return WINDOW_CALL( Move(x, y) );
}

WINDOW_API( void )
move(const point_type &pt)
{
  return WINDOW_CALL( Move(pt) );
}

//----------------------------------------------------------------------------
//! Moves this window in the tab navigation order after the specified win.
//! This means that when the user presses TAB key on that other window, the 
//! focus switches to this window.
//! Default tab order is the same as creation order, this function and
//! MoveBeforeInTabOrder() allow to change it after creating all the windows.
//----------------------------------------------------------------------------
WINDOW_API( void )
move_after_in_tab_order(widget_type const &w)
{
  return WINDOW_CALL( MoveAfterInTabOrder(w) );
}

//----------------------------------------------------------------------------
//! Same as MoveAfterInTabOrder except that it inserts this window just before
//! win instead of putting it right after it.
//----------------------------------------------------------------------------
WINDOW_API( void )
move_before_in_tab_order(widget_type const &w)
{
  return WINDOW_CALL( MoveBeforeInTabOrder(w) );
}

//----------------------------------------------------------------------------
//! Raises the window to the top of the window hierarchy (z-order).
//! In current version of wxWidgets this works both for managed and child 
//! windows.
//----------------------------------------------------------------------------
WINDOW_API( void )
raise() WINDOW_CONST()
{
  WINDOW_CALL( Raise() );
}

//----------------------------------------------------------------------------
//! Causes this window, and all of its children recursively (except under
//! wxGTK1 where this is not implemented), to be repainted. Note that
//! repainting doesn't happen immediately but only during the next event loop
//! iteration, if you need to update the window immediately you should use 
//! Updateinstead.
//----------------------------------------------------------------------------
WINDOW_API( void )
refresh(bool erase_bgnd = true, const rect_type *rect = 0) WINDOW_CONST()
{
  wxRect r;
  if(rect)
  {
    r.x = rect->GetX();
    r.y = rect->GetY();
    r.width = rect->GetWidth();
    r.height = rect->GetHeight();
  }
  WINDOW_CALL( Refresh(erase_bgnd, (rect ? &r : 0)) );
}

WINDOW_API( void )
refresh_rect(const rect_type &rect, bool erase_bgnd = true) WINDOW_CONST()
{
  WINDOW_CALL( RefreshRect(wxRect(rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight()), erase_bgnd) );
}

//----------------------------------------------------------------------------
//! Releases mouse input captured with wxWindow::CaptureMouse.
//----------------------------------------------------------------------------
WINDOW_API( void )
release_mouse()
{
  WINDOW_CALL( ReleaseMouse() );
}

//----------------------------------------------------------------------------
//! Removes a child window.  This is called automatically by window deletion 
//! functions so should not be required by the application programmer.
//! Notice that this function is mostly internal to wxWidgets and shouldn't be 
//! called by the user code.
//----------------------------------------------------------------------------
WINDOW_API( void )
remove_child(const widget_type &w)
{
  WINDOW_CALL( RemoveChild(w) );
}

//----------------------------------------------------------------------------
//! Reparents the window, i.e the window will be removed from its current
//! parent window (e.g. a non-standard toolbar in a wxFrame) and then re-
//! inserted into another.
//----------------------------------------------------------------------------
WINDOW_API( void )
reparent(const widget_type &p)
{
  WINDOW_CALL( Reparent(p) );
}

//----------------------------------------------------------------------------
//! Converts from screen to client window coordinates.
//----------------------------------------------------------------------------
WINDOW_API( void )
screen_to_client(vector_type &x, vector_type &y) WINDOW_CONST(const)
{
  WINDOW_CALL( ScreenToClient(&x, &y) );
}

WINDOW_API( void )
screen_to_client(point_type &pt) WINDOW_CONST(const)
{
  WINDOW_CALL( ScreenToClient(&pt.x(), &pt.y()) );
}

WINDOW_API( point_type )
screen_to_client(const point_type &pt) WINDOW_CONST(const)
{
  point_type ret = pt;
  WINDOW_CALL( ScreenToClient(&ret.x(), &ret.y()) );
  return ret;
}

//----------------------------------------------------------------------------
//! Scrolls the window by the given number of lines down (if lines is 
//! positive) or up.
//! Returns true if the window was scrolled, false if it was already on 
//! top/bottom and nothing was done.
//----------------------------------------------------------------------------
WINDOW_API( bool )
scroll_lines(int lines) WINDOW_CONST()
{
  return WINDOW_CALL( ScrollLines(lines) );
}  

//----------------------------------------------------------------------------
//! Scrolls the window by the given number of pages down (if pages is
//! positive) or up.
//! Returns true if the window was scrolled, false if it was already on 
//! top/bottom and nothing was done.
//----------------------------------------------------------------------------
WINDOW_API( bool )
scroll_pages(int pages) WINDOW_CONST()
{
  return WINDOW_CALL( ScrollPages(pages) );
}  

//----------------------------------------------------------------------------
//! Physically scrolls the pixels in the window and move child windows 
//! accordingly.
//----------------------------------------------------------------------------
WINDOW_API( bool )
scroll_window(const vector_type &dx, const vector_type &dy, 
              const rect_type *rect = 0) WINDOW_CONST()
{
  wxRect r;
  if(rect)
  {
    r.x = rect->GetX();
    r.y = rect->GetY();
    r.width = rect->GetWidth();
    r.height = rect->GetHeight();
  }
  return WINDOW_CALL( ScrollWindow(dx, dy, (rect ? &r : 0)) );
}  

//----------------------------------------------------------------------------
//! Determines whether the wxWindow::Layout function will be called
//! automatically when the window is resized. Please note that this only
//! happens for the windows usually used to contain children, namely wxPanel
//! and wxTopLevelWindow  (and the classes deriving from them).
//! This method is called implicitly by wxWindow::SetSizer but if you use
//! wxWindow::SetConstraints you should call it manually or otherwise the 
//! window layout won't be correctly updated when its size changes.
//----------------------------------------------------------------------------
WINDOW_API( bool )
set_auto_layout(bool auto_layout WINDOW_DEFAULT(true))
  WINDOW_CONST()
{
  return WINDOW_CALL( SetAutoLayout(auto_layout) );
}  

//----------------------------------------------------------------------------
//! Sets the background colour of the window.
//! Please see InheritAttributes for explanation of the difference between 
//! this method andSetOwnBackgroundColour.
//----------------------------------------------------------------------------
WINDOW_API( void )
set_background_color(const rgba_type &c)
  WINDOW_CONST()
{
  WINDOW_CALL( SetBackgroundColor(wxColour(c.r, c.g, c.b, c.a)) );
}

//----------------------------------------------------------------------------
//! This sets the size of the window client area in pixels. Using this
//! function to size a window tends to be more device-independent than
//! wxWindow::SetSize, since the application need not worry about what
//! dimensions the border or title bar have when trying to fit the window 
//! around panel items, for example.
//----------------------------------------------------------------------------
WINDOW_API( void )
set_client_size(const vector_type &w, const vector_type &h)
  WINDOW_CONST()
{
  WINDOW_CALL( SetClientSize(w, h) );
}

WINDOW_API( void )
set_client_size(const size_type &sz)
  WINDOW_CONST()
{
  WINDOW_CALL( SetClientSize(sz) );
}

//----------------------------------------------------------------------------
//! A smart SetSize that will fill in default size components with the
//! window's best size values.  Also sets the window's minsize to the value
//! passed in for use with sizers.  This means that if a full or partial size
//! is passed to this function then the sizers will use that size instead of
//! the results of GetBestSize to determine the minimum needs of the window 
//! for layout.
//! Most controls will use this to set their initial size, and their min size 
//! to the passed in value (if any.)
//----------------------------------------------------------------------------
WINDOW_API( void )
set_initial_size(const size_type &sz)
  WINDOW_CONST()
{
  WINDOW_CALL( SetInitialSize(sz) );
}

//----------------------------------------------------------------------------
//! Sets the initial window size if none is given (i.e. at least one of the 
//! components of the size passed to ctor/Create() is wxDefaultCoord).
//----------------------------------------------------------------------------
WINDOW_API( void )
set_initial_best_size(const size_type &sz)
  WINDOW_CONST()
{
  WINDOW_CALL( SetInitialBestSize(sz) );
}

//----------------------------------------------------------------------------
//! This sets the window to receive keyboard input.
//----------------------------------------------------------------------------
WINDOW_API( void )
set_focus() WINDOW_CONST()
{
  WINDOW_CALL( SetFocus() );
}

//----------------------------------------------------------------------------
//! This function is called by wxWidgets keyboard navigation code when the
//! user gives the focus to this window from keyboard (e.g. using TAB key).
//! By default this method simply calls SetFocus but can be overridden to do 
//! something in addition to this in the derived classes.
//----------------------------------------------------------------------------
WINDOW_API( void )
set_focus_from_kbd() WINDOW_CONST()
{
  WINDOW_CALL( SetFocusFromKbd() );
}

//----------------------------------------------------------------------------
//! Sets the foreground colour of the window.
//! Please see InheritAttributes for explanation of the difference between 
//! this method andSetOwnForegroundColour.
//----------------------------------------------------------------------------
WINDOW_API( void )
set_foreground_color(const rgba_type &c)
  WINDOW_CONST()
{
  WINDOW_CALL( SetForegroundColor(wxColour(c.r, c.g, c.b, c.a)) );
}

//----------------------------------------------------------------------------
//! Sets the help text to be used as context-sensitive help for this window.
//! Note that the text is actually stored by the current wxHelpProvider 
//! implementation, and not in the window object itself.
//----------------------------------------------------------------------------
WINDOW_API( void )
set_help_text(const std::string &text)
  WINDOW_CONST()
{
  WINDOW_CALL( SetHelpText(text) );
}

//----------------------------------------------------------------------------
//! Sets the identifier of the window.
//----------------------------------------------------------------------------
WINDOW_API( void )
set_id(int id)
  WINDOW_CONST()
{
  WINDOW_CALL( SetId(id) );
}

//----------------------------------------------------------------------------
//! Sets the identifier of the window.
//----------------------------------------------------------------------------
WINDOW_API( void )
set_label(const std::string &label)
  WINDOW_CONST()
{
  WINDOW_CALL( SetLabel(label) );
}

//----------------------------------------------------------------------------
//! Sets the maximum size of the window, to indicate to the sizer layout 
//! mechanism that this is the maximum possible size.
//----------------------------------------------------------------------------
WINDOW_API( void )
set_max_size(const size_type &sz)
{
  return WINDOW_CALL( SetMaxSize(sz) );
}

//----------------------------------------------------------------------------
//! Sets the minimum size of the window, to indicate to the sizer layout
//! mechanism that this is the minimum required size. You may need to call
//! this if you change the window size after construction and before adding to 
//! its parent sizer.
//----------------------------------------------------------------------------
WINDOW_API( void )
set_min_size(const size_type &sz)
{
  return WINDOW_CALL( SetMinSize(sz) );
}

//----------------------------------------------------------------------------
//! Sets the window's name.
//----------------------------------------------------------------------------
WINDOW_API( void )
set_name(const std::string &name)
  WINDOW_CONST()
{
  WINDOW_CALL( SetName(name) );
}

//----------------------------------------------------------------------------
//! Sets the background colour of the window but prevents it from being 
//! inherited by the children of this window.
//----------------------------------------------------------------------------
WINDOW_API( void )
set_own_background_color(const rgba_type &c)
  WINDOW_CONST()
{
  WINDOW_CALL( SetOwnBackgroundColor(wxColour(c.r, c.g, c.b, c.a)) );
}

//----------------------------------------------------------------------------
//! Sets the foreground colour of the window but prevents it from being 
//! inherited by the children of this window.
//----------------------------------------------------------------------------
WINDOW_API( void )
set_own_foreground_color(const rgba_type &c)
  WINDOW_CONST()
{
  WINDOW_CALL( SetOwnForegroundColor(wxColour(c.r, c.g, c.b, c.a)) );
}

//----------------------------------------------------------------------------
//! Sets the scrollbar properties of a built-in scrollbar.
//----------------------------------------------------------------------------
WINDOW_API( void )
set_scrollbar(int orient, int position, int thumbSize, int range, 
              bool refresh WINDOW_DEFAULT(true))
  WINDOW_CONST()
{
  WINDOW_CALL( SetScrollbar((orient == horizontal_orientation ? wxHORIZONTAL : wxVERTICAL), position, thumbSize, range, refresh) );
}

//----------------------------------------------------------------------------
//! Sets the position of one of the built-in scrollbars.
//----------------------------------------------------------------------------
WINDOW_API( void )
set_scroll_pos(int orient, int position, bool refresh WINDOW_DEFAULT(true))
  WINDOW_CONST()
{
  WINDOW_CALL( SetScrollPos((orient == horizontal_orientation ? wxHORIZONTAL : wxVERTICAL), position, refresh) );
}

//----------------------------------------------------------------------------
//! Sets the size and position of the window in pixels.
//----------------------------------------------------------------------------
WINDOW_API( void )
set_size(const vector_type &x, const vector_type &y,
         const vector_type &w, const vector_type &h)
  WINDOW_CONST()
{
  return WINDOW_CALL( SetSize(x, y, w, h) );
}

WINDOW_API( void )
set_size(const rect_type &rect)
  WINDOW_CONST()
{
  return WINDOW_CALL( SetSize(wxRect(rect.GetX(), rect.GetY(), 
                                     rect.GetWidth(), rect.GetHeight())) );
}

//----------------------------------------------------------------------------
//! Sets the size of the window in pixels.
//----------------------------------------------------------------------------
WINDOW_API( void )
set_size(const vector_type &w, const vector_type &h)
  WINDOW_CONST()
{
  return WINDOW_CALL( SetSize(w, h) );
}

WINDOW_API( void )
set_size(const size_type &sz)
  WINDOW_CONST()
{
  return WINDOW_CALL( SetSize(sz) );
}

//----------------------------------------------------------------------------
//! This function tells a window if it should use the system's "theme" code to
//! draw the windows' background instead if its own background drawing code.
//! This does not always have any effect since the underlying platform
//! obviously needs to support the notion of themes in user defined windows.
//! One such platform is GTK+ where windows can have (very colourful) 
//! backgrounds defined by a user's selected theme.
//! Dialogs, notebook pages and the status bar have this flag set to true by 
//! default so that the default look and feel is simulated best.
//----------------------------------------------------------------------------
WINDOW_API( void )
set_theme_enabled(bool e WINDOW_DEFAULT(true))
  WINDOW_CONST()
{
  WINDOW_CALL( SetThemeEnabled(e) );
}

//----------------------------------------------------------------------------
//! Attach a tooltip to the window.
//----------------------------------------------------------------------------
template<class tooltip>
WINDOW_API( void )
set_tool_tip(const tooltip &tip)
  WINDOW_CONST()
{
  WINDOW_CALL( SetToolTip(tip) );
}

/*WINDOW_API( void )
set_tool_tip<std::string>(const std::string &tip)
{
  WINDOW_CALL( SetToolTip(tip) );
}*/

//----------------------------------------------------------------------------
//! Sets the virtual size of the window in pixels.
//----------------------------------------------------------------------------
WINDOW_API( void )
set_virtual_size(const vector_type &w, const vector_type &h)
  WINDOW_CONST()
{
  return WINDOW_CALL( SetVirtualSize(w, h) );
}

WINDOW_API( void )
set_virtual_size(const size_type &sz)
  WINDOW_CONST()
{
  return WINDOW_CALL( SetVirtualSize(sz) );
}

//----------------------------------------------------------------------------
//! Allows specification of minimum and maximum virtual window sizes. If a 
//! pair of values is not set (or set to -1), the default values will be used.
//----------------------------------------------------------------------------
WINDOW_API( void )
set_virtual_size_hints(const vector_type &min_w, const vector_type &min_h,
                       const vector_type &max_w WINDOW_DEFAULT(-1), 
                       const vector_type &max_h WINDOW_DEFAULT(-1))
  WINDOW_CONST()
{
  WINDOW_CALL( SetVirtualSizeHints(min_w, min_h, max_w, max_h) );
}

WINDOW_API( void )
set_virtual_size_hints(const size_type &min, const size_type &max)
  WINDOW_CONST()
{
  WINDOW_CALL( SetVirtualSizeHints(min, max) );
}

//----------------------------------------------------------------------------
//! Return true from here to allow the colours of this window to be changed
//! by InheritAttributes, returning false forbids inheriting them from the
//! parent window.
//! The base class version returns false, but this method is overridden 
//! in wxControl where it returns true.
//----------------------------------------------------------------------------
WINDOW_API( bool )
should_inherit_colors() WINDOW_CONST(const)
{
  return WINDOW_CALL( ShouldInheritColors() );
}

//----------------------------------------------------------------------------
//! Shows or hides the window. You may need to call Raise for a top level
//! window if you want to bring it to top, although this is not needed if 
//! Show() is called immediately after the frame creation.
//----------------------------------------------------------------------------
WINDOW_API( void )
show(bool sw WINDOW_DEFAULT(true))
  WINDOW_CONST()
{
  WINDOW_CALL( Show(sw) );
}

//----------------------------------------------------------------------------
//! Reenables window updating after a previous call toFreeze. To really thaw 
//! the control, it must be called exactly the same number of times as Freeze.
//----------------------------------------------------------------------------
WINDOW_API( void )
thaw() WINDOW_CONST()
{
  WINDOW_CALL( Thaw() );
}

//----------------------------------------------------------------------------
//! Transfers values from child controls to data areas specified by their 
//! validators. Returnsfalse if a transfer failed.
//! If the window has wxWS_EX_VALIDATE_RECURSIVELY extra style flag set, the 
//! method will also call TransferDataFromWindow() of all child windows.
//----------------------------------------------------------------------------
WINDOW_API( bool )
transfer_data_from_window() WINDOW_CONST()
{
  return WINDOW_CALL( TransferDataFromWindow() );
}

//----------------------------------------------------------------------------
//! Transfers values to child controls from data areas specified by their
//! validators.
//! If the window has wxWS_EX_VALIDATE_RECURSIVELY extra style flag set, the 
//! method will also call TransferDataToWindow() of all child windows.
//----------------------------------------------------------------------------
WINDOW_API( bool )
transfer_data_to_window() WINDOW_CONST()
{
  return WINDOW_CALL( TransferDataToWindow() );
}

//----------------------------------------------------------------------------
//! Unregisters a system wide hotkey.
//----------------------------------------------------------------------------
WINDOW_API( bool )
unregister_hot_key(int hotkey_id) WINDOW_CONST()
{
  return WINDOW_CALL( UnregisterHotKey(hotkey_id) );
}

//----------------------------------------------------------------------------
//! Calling this method immediately repaints the invalidated area of the
//! window and all of its children recursively while this would usually only
//! happen when the flow of control returns to the event loop.  Notice that
//! this function doesn't invalidate any area of the window so nothing happens
//! if nothing has been invalidated (i.e. marked as requiring a redraw).
//! Use Refresh first if you want to immediately redraw the window 
//! unconditionally.
//----------------------------------------------------------------------------
WINDOW_API( void )
update() WINDOW_CONST()
{
  WINDOW_CALL( Update() );
}

//----------------------------------------------------------------------------
//! This function sends wxUpdateUIEvents to the window. The particular
//! implementation depends on the window; for example a wxToolBar will send an
//! update UI event for each toolbar button, and a wxFrame will send an update
//! UI event for each menubar menu item. You can call this function from your
//! application to ensure that your UI is up-to-date at this point (as far as
//! your wxUpdateUIEvent handlers are concerned). This may be necessary if you
//! have calledwxUpdateUIEvent::SetMode orwxUpdateUIEvent::SetUpdateInterval
//! to limit the overhead that wxWidgets incurs by sending update UI events 
//! in idle time.
//----------------------------------------------------------------------------
WINDOW_API( void )
update_window_ui(int flags = update_none) WINDOW_CONST()
{
  long f = wxUPDATE_UI_NONE;
  if(flags & update_recurse) f |= wxUPDATE_UI_RECURSE;
  if(flags & update_fromidle) f |= wxUPDATE_UI_FROMIDLE;
  WINDOW_CALL( UpdateWindowUI(f) );
}

//----------------------------------------------------------------------------
//! Validates the current values of the child controls using their validators.
//! If the window has wxWS_EX_VALIDATE_RECURSIVELY extra style flag set, the 
//! method will also call Validate() of all child windows.
//----------------------------------------------------------------------------
WINDOW_API( bool )
validate() WINDOW_CONST()
{
  return WINDOW_CALL( Validate() );
}

//----------------------------------------------------------------------------
//! Moves the pointer to the given position on the window.
//! NB:  This function is not supported under Mac because Apple Human 
//! Interface Guidelines forbid moving the mouse cursor programmatically.
//----------------------------------------------------------------------------
WINDOW_API( void )
warp_pointer(const vector_type &x, const vector_type &y) WINDOW_CONST()
{
  WINDOW_CALL( WarpPointer(x, y) );
}

//----------------------------------------------------------------------------
//! Gets the system specific window handle of the widget.
//----------------------------------------------------------------------------
#if WIN32
WINDOW_API( void * )
get_hwnd()
{
  return WINDOW_CALL( GetHWND() )
}
#endif // WIN32

//@}

private:

//----------------------------------------------------------------------------

bool m_dirty;

#undef WINDOW_API
#undef WINDOW_DEFAULT
