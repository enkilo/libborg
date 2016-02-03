#ifndef BORG_LIBXML2_OUTPUT_BUFFER_HPP
#define BORG_LIBXML2_OUTPUT_BUFFER_HPP

#include <borg/libxml2/traits.hpp>
#include <borg/xml/lib/output_buffer.hpp>

namespace borg { 
namespace xml {

//---------------------------------------------------------------------------
template<class T>
struct output_buffer_impl<libxml2::traits, T>
{
  XML_LIB_TYPES(libxml2::traits)
  XML_LIB_CALLBACKS(libxml2::traits)

  //! Create output_buffer.
  //-----------------------------------------------------------------------
  static output_buffer_type
  create(write_callback w, close_callback c, any_type ioctx, encoder_type encoder)
  {
    return xmlOutputBufferCreateIO(w, c, ioctx, encoder);
  }

  static output_buffer_type
  create(file_type file, encoder_type encoder = 0)
  {
    return xmlOutputBufferCreateFile(file, encoder);
  }

  static void
  destroy(output_buffer_type ob)
  {
    std::cout << "close output buffer" << std::endl;
    
    xmlOutputBufferClose(ob);
  }
  
  static int
  flush(output_buffer_type ob)
  {
    std::cout << "flush output buffer" << std::endl;

    return xmlOutputBufferFlush(ob);
  }
  
  static int
  write(output_buffer_type ob, const char *out, length_type len)
  {
    return xmlOutputBufferWrite(ob, len, out);
  }
  
  static int
  write(output_buffer_type ob, const char *str)
  {
    return xmlOutputBufferWriteString(ob, str);
  }
};
  
//---------------------------------------------------------------------------

} // namespace xml


namespace libxml2 {

typedef xml::output_buffer<traits, traits::output_buffer_type> output_buffer;
  
} // namespace libxml2
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_LIBXML2_OUTPUT_BUFFER_HPP
