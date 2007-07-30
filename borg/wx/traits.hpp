//----------------------------------------------------------------------------
//! \file   wx_traits.hpp
//! \brief  Implements tk::wx_traits, a metafunction resolving the basic 
//!         wxWidgets types.
//!
//! \svn $Id: pointer_adapter.hpp 35 2007-03-21 22:09:24Z nexbyte $
//----------------------------------------------------------------------------
#ifndef WX_TRAITS_HPP
#define WX_TRAITS_HPP

#include <wx/wx.h>
#include <wx/xml/xml.h>
#include <wx/encconv.h>
#include <wx/file.h>
#include <wx/dynarray.h>
#include <borg/string/char_traits.hpp>
#include <borg/traits/color_types.hpp>
#include <borg/traits/vector_types.hpp>

namespace tk {

//---------------------------------------------------------------------------
//! Key class for wxWidgets wrappers.
//! Inherits the types needed for the interface and defines the pointer types
//! which are wrapped.
//---------------------------------------------------------------------------
struct wx_traits 
    : traits::vector_types<int>
    , traits::color_types<unsigned char>
{
  typedef wxDC     dc_type;
  typedef wxWindow widget_type;
  typedef wxBitmap bitmap_type;
  typedef wxFrame  frame_type;
};

}// namespace tk
//---------------------------------------------------------------------------

namespace borg {
namespace xml {
  
//---------------------------------------------------------------------------
struct wx_traits
{
  typedef wxXmlNodeType  id_type;
  typedef wxXmlDocument *parser_type;
  typedef wxXmlDocument *document_type;
  typedef wxXmlProperty *attribute_type;
  typedef wxXmlProperty *nodemap_type;
  typedef wxXmlNode     *node_type;
  typedef wxXmlNode     *nodelist_type;
  typedef wxXmlNode     *element_type;
  typedef wxXmlNode     *text_type;
  typedef wxXmlNode     *cdata_type;
  typedef wxXmlNode     *comment_type;
  typedef void          *writer_type;
  typedef void          *exception_type;
  typedef void          *implementation_type;
  typedef void          *error_reporter_type;
//  typedef char           char_type;
  typedef wxChar         wchar_type;
  typedef wxByte         byte_type;
//  typedef unsigned int   size_type; // damn, conflicts with the one from vector_types, should the one from vector_types to dimension_type or similar
  typedef int            index_type;
};

}// namespace borg
}// namespace xml
  
//---------------------------------------------------------------------------
  
namespace borg {
namespace wx {

struct traits 
    : ::tk::wx_traits, xml::wx_traits, borg::char_traits<wxChar, traits>
{
  typedef wxWindowID     id_type;
  typedef wxPoint        point_type;
  typedef wxSize         size_type;
  typedef wxRect         rect_type;
  typedef int            index_type;
  typedef ::size_t       length_type;
  typedef wxString       string_type;
  typedef wxString const const_string_type;
  typedef long           style_type;
  typedef wxValidator    validator_type;
  typedef wxListBox      listbox_type;
  typedef wxArrayInt     int_array_type;
  typedef wxArrayString  string_array_type;
  typedef wxWindow       widget_type;
  typedef wxApp          application_type;
  typedef wxFrame        frame_type;
  typedef wxCoord        vector_type;
  typedef wxFont         font_type;
  typedef void   *       align_type;

  typedef wxOutputStream      output_buffer_type;
  typedef wxStreamBuffer      buffer_type;
  typedef wxEncodingConverter encoder_type;
  typedef wxFile              file_type;
  typedef int                 status_type;
  typedef int options_type;
  typedef const wxChar *path_type;
  typedef const wxChar *url_type;
  typedef int return_type;
  
  template<class T> struct array;
};

template<> struct traits::array<short>    { typedef wxArrayShort type; };
template<> struct traits::array<int>      { typedef wxArrayInt type; };
template<> struct traits::array<double>   { typedef wxArrayDouble type; };
template<> struct traits::array<void *>   { typedef wxArrayPtrVoid type; };
template<> struct traits::array<wxString> { typedef wxArrayString type; };

} // namespace wx
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef WX_TRAITS_HPP
