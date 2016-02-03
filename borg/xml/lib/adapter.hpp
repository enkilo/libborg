#ifndef BORG_XML_ADAPTER_HPP
#define BORG_XML_ADAPTER_HPP

#include <borg/string.hpp>
#include <borg/xml/adapter_macros.hpp>
//#include <borg/xml/lib/string.hpp>
#include <borg/xml/lib/output_buffer.hpp>

namespace borg {
namespace xml {

//! Most adapters will want to use this wrapper.
//---------------------------------------------------------------------------
using borg::wrapper;

//---------------------------------------------------------------------------
XML_ADAPTER_CLASS_0(error_reporter);
//XML_ADAPTER_CLASS_1(string);
XML_ADAPTER_CLASS_1(output_buffer);

}// namespace xml
}// namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_ADAPTER_HPP
