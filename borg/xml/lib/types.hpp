#ifndef XML_LIB_TYPES_HPP
#define XML_LIB_TYPES_HPP

#include <borg/preproc.hpp>

namespace xml {
namespace lib {

//---------------------------------------------------------------------------
//! Macro to slurp in the typedefs from the traits.
//---------------------------------------------------------------------------
#define XML_LIB_TYPES(Traits) \
  BORG_PP_USE_TYPE(Traits, length_type) \
  typedef Traits::index_type index_type; \
  typedef Traits::char_type char_type; \
  typedef Traits::wchar_type wchar_type; \
  typedef Traits::byte_type byte_type; \
  typedef Traits::error_reporter_type error_reporter_type; \
  typedef Traits::output_buffer_type output_buffer_type; \
  typedef Traits::buffer_type buffer_type; \
  typedef Traits::encoder_type encoder_type; \
  typedef Traits::file_type file_type; \
  typedef Traits::status_type status_type; \
  typedef Traits::path_type path_type;

#define XML_LIB_CALLBACKS(Traits) \
  BORG_PP_USE_TYPE(Traits, any_type) \
  BORG_PP_USE_TYPE(Traits, write_callback) \
  BORG_PP_USE_TYPE(Traits, close_callback)

}// namespace lib
}// namespace xml

//---------------------------------------------------------------------------
#endif //ndef XML_LIB_TYPES_HPP
