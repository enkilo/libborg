#ifndef BORG_LIBXML2_TRAITS_HPP
#define BORG_LIBXML2_TRAITS_HPP

#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xmlwriter.h>

namespace borg {
namespace libxml2 {

//----------------------------------------------------------------------------
struct traits
{
  typedef short                     id_type;
  typedef xmlGenericErrorFunc       error_reporter_type;
  typedef xmlParserCtxtPtr          parser_type;
  typedef xmlNodePtr                node_type;
  typedef xmlDocPtr                 document_type;
  typedef xmlNodePtr                nodelist_type;
  typedef xmlNodeSetPtr             nodeset_type;
  typedef xmlAttributePtr           nodemap_type;
  typedef xmlAttrPtr                attribute_type;
  typedef xmlNodePtr                element_type;
  typedef xmlNodePtr                text_type;
  typedef xmlNodePtr                comment_type;
  typedef xmlNodePtr                cdata_type;
  typedef void                     *implementation_type;
  typedef xmlError                  exception_type;
  typedef char                      char_type;
  typedef xmlChar                   wchar_type;
  typedef xmlChar                  *string_type;
  typedef xmlChar const            *const_string_type;
  typedef unsigned char             byte_type;
  typedef unsigned long             length_type;
  typedef long                      index_type;
  typedef xmlTextWriterPtr          writer_type;

  typedef xmlXPathCompExprPtr       expression_type;
  typedef xmlXPathContextPtr        evaluator_type;
  typedef void                     *ns_resolver_type;
  typedef xmlXPathObjectPtr         result_type;
  typedef double                    number_type;
  typedef xmlXPathFunction          xpath_function_type;
  typedef xmlXPathParserContextPtr  xpath_parser_type;
  

  typedef void                     *http_client_type;
  typedef int                       return_type;
//  typedef const xmlChar *           url_type;
  typedef const char *           url_type;
  typedef const char *              path_type;
  typedef xmlOutputBufferPtr        output_buffer_type;
  typedef xmlBufferPtr              buffer_type;
  typedef xmlCharEncodingHandlerPtr encoder_type;
  typedef FILE                     *file_type;
  
  typedef int                       status_type;
  typedef void                     *any_type;
  typedef xmlOutputWriteCallback    write_callback;
  typedef xmlOutputCloseCallback    close_callback;
  typedef int                       options_type;
  
  template<typename CharT>
  struct string
  {
    typedef CharT *type;
    typedef CharT const *const_type;
  };
  
  // list types
  typedef xmlListPtr         list_type;
  typedef xmlListDeallocator deallocator_type;
  typedef xmlListDataCompare comparator_type;
  typedef xmlListWalker      walker_type;
};

}// namespace libxml2
}// namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_LIBXML2_TRAITS_HPP
