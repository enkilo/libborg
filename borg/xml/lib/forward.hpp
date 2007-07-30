#ifndef BORG_XML_FORWARD_HPP
#define BORG_XML_FORWARD_HPP

#include <borg/xml/forward_decl.hpp>
#include <borg/wrap/preproc.hpp>

namespace borg {
namespace xml {

//---------------------------------------------------------------------------
XML_FORWARD_DECL_0(error_reporter)
XML_FORWARD_DECL_1(output_buffer)
//XML_FORWARD_DECL_1(string)
        
//WRAP_PATTERN_FORWARD(string, (class CharT = typename Traits::wchar_type))
        
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_FORWARD_HPP
