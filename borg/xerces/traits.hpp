#ifndef BORG_XERCES_TRAITS_HPP
#define BORG_XERCES_TRAITS_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/framework/XMLErrorReporter.hpp>
#include <xercesc/framework/MemBufFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/internal/MemoryManagerImpl.hpp>

#include <xercesc/util/XMLURL.hpp>

#ifdef WIN32
#include <xercesc/util/NetAccessors/WinSock/BinHTTPURLInputStream.hpp>
#else
#include <xercesc/util/NetAccessors/Socket/UnixHTTPURLInputStream.hpp>
#endif

//#include <boost/bind.hpp>
//#include <boost/mem_fn.hpp>

//#include <borg/xml/xml_wrappers.hpp>

namespace borg {
namespace xerces {

//----------------------------------------------------------------------------
struct traits
{
  //! \name Plain old data types.
  //@{
  typedef short          id_type;
  typedef char           char_type;
  typedef ::XMLCh        wchar_type;
  typedef int            index_type;
  typedef ::XMLSize_t    length_type; //!< deprecated
  typedef ::XMLSize_t    size_type;
  typedef ::XMLCh       *string_type;
  typedef ::XMLCh const *const_string_type;
  typedef ::XMLByte      byte_type;
  typedef void          *number_type;
  //@}

  template<typename CharT>
  struct string
  {
    typedef CharT *type;
    typedef CharT const *const_type;
  };
  
  //! \name Pointer to object types.
  //@{
  typedef ::XERCES_CPP_NAMESPACE::XMLErrorReporter         *error_reporter_type;
  typedef ::XERCES_CPP_NAMESPACE::XercesDOMParser          *parser_type;
  typedef ::XERCES_CPP_NAMESPACE::DOMException             *exception_type;
  typedef ::XERCES_CPP_NAMESPACE::DOMNode                  *node_type;
  typedef ::XERCES_CPP_NAMESPACE::DOMNodeList              *nodelist_type;
  typedef ::XERCES_CPP_NAMESPACE::DOMNamedNodeMap          *nodemap_type;
  typedef void                                             *nodeset_type;
  typedef ::XERCES_CPP_NAMESPACE::DOMAttr                  *attribute_type;
  typedef ::XERCES_CPP_NAMESPACE::DOMText                  *text_type;
  typedef ::XERCES_CPP_NAMESPACE::DOMCDATASection          *cdata_type;
  typedef ::XERCES_CPP_NAMESPACE::DOMElement               *element_type;
  typedef ::XERCES_CPP_NAMESPACE::DOMDocument              *document_type;
  typedef ::XERCES_CPP_NAMESPACE::DOMImplementation        *implementation_type;
  typedef ::XERCES_CPP_NAMESPACE::DOMComment               *comment_type;
  typedef ::XERCES_CPP_NAMESPACE::DOMXPathEvaluator        *evaluator_type;
  typedef ::XERCES_CPP_NAMESPACE::DOMXPathExpression const *expression_type;
  typedef ::XERCES_CPP_NAMESPACE::DOMXPathNSResolver const *ns_resolver_type;
  typedef ::XERCES_CPP_NAMESPACE::DOMXPathResult           *result_type;
  typedef void                                             *context_type;
  typedef ::XERCES_CPP_NAMESPACE::DOMWriter                *writer_type;
  
  
  typedef ::XERCES_CPP_NAMESPACE::XMLFormatter             *formatter_type;
  typedef ::XERCES_CPP_NAMESPACE::XMLFormatTarget          *output_buffer_type;
  typedef ::XERCES_CPP_NAMESPACE::MemBufFormatTarget       *membuf_output_buffer_type;
  typedef ::XERCES_CPP_NAMESPACE::LocalFileFormatTarget    *localfile_output_buffer_type;
  typedef ::XERCES_CPP_NAMESPACE::StdOutFormatTarget       *stdout_output_buffer_type;
  
#ifdef WIN32
  typedef ::XERCES_CPP_NAMESPACE::BinHTTPURLInputStream    *http_client_type;
#else
  typedef ::XERCES_CPP_NAMESPACE::UnixHTTPURLInputStream   *http_client_type;
#endif
  typedef unsigned int                                      return_type;
  typedef ::XERCES_CPP_NAMESPACE::XMLURL                    url_type;
  typedef ::XERCES_CPP_NAMESPACE::XMemory                   buffer_type;
  typedef ::XERCES_CPP_NAMESPACE::XMLTranscoder             encoder_type;
  typedef ::XERCES_CPP_NAMESPACE::MemoryManagerImpl        *allocator_type;
//  typedef ::XERCES_CPP_NAMESPACE::MemoryManager            *allocator_type;
  
  typedef void *file_type;
  typedef int status_type;
  typedef int options_type;
  typedef const char *path_type;
  
  
  typedef void *xpath_function_type;
  typedef void *xpath_parser_type;
  //@}
};

//---------------------------------------------------------------------------
} // namespace xerces
} // namespace borg
  
#endif //ndef BORG_XERCES_TRAITS_HPP
