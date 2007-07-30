#ifndef FRAME_API
#define FRAME_API(ret_type) ret_type
#endif // FRAME_API

#ifndef FRAME_CALL
#define FRAME_CALL(call_fn) call_fn
#endif // FRAME_CALL

#ifndef FRAME_CONST
#define FRAME_CONST(c) c
#endif // FRAME_CONST

#ifndef FRAME_DEFAULT
#define FRAME_DEFAULT(def_value) = def_value
#endif // FRAME_DEFAULT

//----------------------------------------------------------------------------
//! \name Implementation of the abstract::dc interface ontop wxWidgets.
//----------------------------------------------------------------------------
//@{

//----------------------------------------------------------------------------
//! Get client area origin.
//----------------------------------------------------------------------------
FRAME_API( point_type )
client_origin() FRAME_CONST(const)
{
  wxPoint org = FRAME_CALL( GetClientAreaOrigin() );
  return point_type(org.x, org.y);
}
  
//----------------------------------------------------------------------------
//! Set status text.
//----------------------------------------------------------------------------
FRAME_API( void )
set_status_text(const std::string &text, int number = 0) FRAME_CONST()
{
  FRAME_CALL( SetStatusText(text, number) );
}
  
//@}
//----------------------------------------------------------------------------

#undef FRAME_API
#undef FRAME_DEFAULT
