#ifndef BORG_LIBXML2_DOM_WRITER_HPP
#define BORG_LIBXML2_DOM_WRITER_HPP

#include <borg/libxml2/traits.hpp>
#include <borg/xml/dom/node.hpp>

struct _xmlTextWriter
{
  xmlOutputBufferPtr out;     /* output buffer */
  xmlListPtr nodes;           /* element name stack */
  xmlListPtr nsstack;         /* name spaces stack */
  int level;
  int indent;                 /* enable indent */
  int doindent;               /* internal indent flag */
  xmlChar *ichar;             /* indent character */
  char qchar;                 /* character used for quoting attribute values */
  xmlParserCtxtPtr ctxt;
  int no_doc_free;
  xmlDocPtr doc;
};

struct _xmlLink
{
  struct _xmlLink *next;
  struct _xmlLink *prev;
  void *data;
};

namespace borg { 
namespace xml { 
namespace dom {

//---------------------------------------------------------------------------
template<>
struct writer_impl<libxml2::traits>
{
  XML_DOM_TYPES(libxml2::traits)

  //! Create writer.
  //-----------------------------------------------------------------------
  static writer_type
  create(output_buffer_type out)
  {
    writer_type ret = xmlNewTextWriter(out);
    
//    std::cout << "initial size: " << xmlListSize(ret->nodes) << std::endl;
    
    return ret;
  }

  //-----------------------------------------------------------------------
  static writer_type
  create(document_type *out, int compression = 0)
  {
    return xmlNewTextWriterDoc(out, compression);
  }

  //-----------------------------------------------------------------------
  static writer_type
  create(const char *uri, int compression = 0)
  {
    return xmlNewTextWriterFilename(uri, compression);
  }

  static writer_type
  create(buffer_type buf, int compression = 0)
  {
    return xmlNewTextWriterMemory(buf, compression);
  }

  //-----------------------------------------------------------------------
  static writer_type
  create(parser_type push, int compression = 0)
  {
    return xmlNewTextWriterPushParser(push, compression);
  }

  //-----------------------------------------------------------------------
  static writer_type
  create(document_type doc, node_type node, int compression = 0)
  {
    return xmlNewTextWriterTree(doc, node, compression);
  }
  
  //-----------------------------------------------------------------------
  static int
  flush(writer_type writer)
  {
    return xmlTextWriterFlush(writer);
  }
  
  //-----------------------------------------------------------------------
  static void
  destroy(writer_type writer)
  {
    xmlFreeTextWriter(writer);
  }
  
  //-----------------------------------------------------------------------
  static int
  set_indent(writer_type writer, int indent = true)
  {
    return xmlTextWriterSetIndent(writer, indent);
  }
  
  static int
  set_indent(writer_type writer, const wchar_type *indent)
  {
    if(!indent)
      return xmlTextWriterSetIndent(writer, 0);
    
    if(writer->indent == 0)
      xmlTextWriterSetIndent(writer, 1);
    
    return xmlTextWriterSetIndentString(writer, indent);
  }
  
  //-----------------------------------------------------------------------
  static int
  get_indent(writer_type writer)
  {
    if(!writer->indent)
      return 0;

    int n = xmlListSize(writer->nodes);
    
    return (n ? n : 1);
  }
  
  //-----------------------------------------------------------------------
  static int
  indent(writer_type writer)
  {
    int lksize = xmlListSize(writer->nodes);
    
    if(lksize < 1)
      return -1;
    
    for(int i = 0; i < (lksize - 1); ++i)
    {
      int ret = xmlOutputBufferWriteString(writer->out, (const char *)writer->ichar);
      
      if(ret < 0)
        return -1;
    }
    
    return (lksize - 1);
  }
  
  //-----------------------------------------------------------------------
  static const output_buffer_type &
  output(writer_type writer)
  {
    return writer->out;
  }
    
  //-----------------------------------------------------------------------
  //! Start writing an attribute node.
  //-----------------------------------------------------------------------
  static int
  start(writer_type writer, attribute_type attr)
  {
//    if(output(writer)->written == 0)
//      indent(writer);
    
    return xmlTextWriterStartAttribute(writer, attr->name);
  }
      
  //-----------------------------------------------------------------------
  //! Start writing a document node.
  //-----------------------------------------------------------------------
  static int
  start(writer_type writer, document_type doc)
  {
//    if(output(writer)->written == 0)
//      indent(writer);
    
    return xmlTextWriterStartDocument
      (writer, (char_type *)doc->version, (char_type *)doc->encoding, "1");
  }
      
  //-----------------------------------------------------------------------
  //! Start writing a node.
  //-----------------------------------------------------------------------
  static int
  start(writer_type writer, node_type node)
  {
    int ret = -1;
    
    
//    if(output(writer)->written == 0)
//      indent(writer);
//  
//    std::cout << "size before start_node: " << xmlListSize(writer->nodes) << std::endl;
    
    switch(node->type)
    {
      case XML_DOCUMENT_NODE:
      {
        ret = start(writer, (document_type)node);
        break;
      }

      case XML_ELEMENT_NODE:
      {
        ret = xmlTextWriterStartElement(writer, node->name);
        break;
      }

      case XML_ATTRIBUTE_NODE:
      {
        ret = start(writer, (attribute_type)node);
        break;
      }

      default:
      {
        break;
      }
    }

//    dump(writer);
//    std::cout << "size after start_node: " << xmlListSize(writer->nodes) << std::endl;
    return ret;
  }
      
  //-----------------------------------------------------------------------
  //! End writing an attribute node.
  //-----------------------------------------------------------------------
  static int
  end(writer_type writer, attribute_type attr)
  {
    return xmlTextWriterEndAttribute(writer);
  }
      
  //-----------------------------------------------------------------------
  //! Start writing a document node.
  //-----------------------------------------------------------------------
  static int
  end(writer_type writer, document_type doc)
  {
    return xmlTextWriterEndDocument(writer);
//      (writer, (char_type *)doc->version, (char_type *)doc->encoding, "1");
  }
      
  //-----------------------------------------------------------------------
  //! End writing a node.
  //-----------------------------------------------------------------------
  static int
  end(writer_type writer, node_type node)
  {
    switch(node->type)
    {
      case XML_DOCUMENT_NODE:
        return end(writer, (document_type)node);

      case XML_ELEMENT_NODE:
        return xmlTextWriterEndElement(writer);

      case XML_ATTRIBUTE_NODE:
        return end(writer, (attribute_type)node);

      default:
        return 1;
    }
  }
      
  //-----------------------------------------------------------------------
  //! Write an attribute node (name and value).
  //-----------------------------------------------------------------------
  static int
  write(writer_type writer, attribute_type attr)
  {
    int ret;
    
//    if(output(writer)->written == 0)
//      indent(writer);
    
    if((ret = xmlTextWriterWriteAttribute
        (writer, attr->name, xmlNodeGetContent((node_type)attr))) != -1)
      return ret;
    
    // Alternative code, when not within element.
    int sum = 0;
    
//    if((ret = xmlTextWriterWriteRaw(writer, attr->name)) < 0) return -1;
//    sum += ret;
    
//    if((ret = xmlTextWriterWriteRawLen(writer, (const xmlChar *)"=\"", 2)) < 0) return -1;
//    sum += ret;
    
    if((ret = xmlTextWriterWriteString(writer, xmlNodeGetContent((node_type)attr))) < 0) return -1;
    sum += ret;
    
//    if((ret = xmlTextWriterWriteRawLen(writer, (const xmlChar *)"\"", 1)) < 0) return -1;
//    sum += ret;
    
    return sum;
    
  }
  
  //-----------------------------------------------------------------------
  //! Write a node.
  //-----------------------------------------------------------------------
  static int
  write(writer_type writer, node_type node)
  {
    int ret = -1;
    int sum = 0;

//    std::cout << "size before write_node: " << xmlListSize(writer->nodes) << std::endl;

    switch(node->type)
    {
      case XML_ATTRIBUTE_NODE:
      {
        if((ret = write(writer, (attribute_type)node)) < 0) return -1;
        sum += ret;
        break;
      }
      
      case XML_TEXT_NODE:
      {
        if((ret = write(writer, node->content)) < 0) return -1;
        sum += ret;
        break;
      }
      
      case XML_CDATA_SECTION_NODE:
      {
        if((ret = xmlTextWriterWriteCDATA(writer, node->content)) < 0) return -1;
        sum += ret;
        break;
      }
      
      case XML_COMMENT_NODE:
      {
        if((ret = xmlTextWriterWriteComment(writer, node->content)) < 0) return -1;        
        sum += ret;
        break;
      }

      case XML_ELEMENT_NODE:
      {
/*        xmlListPushBack(writer->nodes, 0);
        xmlListPushBack(writer->nodes, 0);
        indent(writer);
        xmlListPopBack(writer->nodes);
        xmlListPopBack(writer->nodes);*/
        
        
//        if((ret = xmlTextWriterStartElement(writer, node->name)) < 0)
        if((ret = start(writer, node)) < 0) return -1;

//        std::cout << "list size after start(): " << xmlListSize(writer->nodes) << std::endl;
        
    //if(output(writer)->written == 0)
    
        for(attribute_type attr = node->properties; attr; attr = attr->next)
        {
          if((ret = write(writer, attr)) < 0) return -1;
          sum += ret;
        }

//        void *p = xmlListEnd(writer->nodes);
//        xmlListPopBack(writer->nodes);        
        
        for(node_type child = node->children; child; child = child->next)
        {
          // We'll certainly want to skip blanks in auto-indentation mode.
          if(get_indent(writer) && xmlIsBlankNode(child))
            continue;
          
          if((ret = write(writer, child)) < 0) return -1;
          sum += ret;
        }

//        xmlListPushBack(writer->nodes, p);
        
        if((ret = end(writer, node)) < 0) return -1;
        sum += ret;
        break;
     }

     default:
     {
       break;
     }

    }
    
//        std::cout << "size after write_node: " << xmlListSize(writer->nodes) << std::endl;
//        dump(writer);
  
    return ret;
  }
  
  //-----------------------------------------------------------------------
  //! Write a raw string.
  //-----------------------------------------------------------------------
  static int
  write(writer_type writer, const wchar_type *str)
  {
//    if(output(writer)->written == 0)
//      indent(writer);
    
    return xmlTextWriterWriteRaw(writer, str);
  }
      
  static int
  write(writer_type writer, const wchar_type *str, length_type n)
  {
//    if(output(writer)->written == 0)
//      indent(writer);
    
    return xmlTextWriterWriteRawLen(writer, str, n);
  }
      
  static int
  write(writer_type writer, const char *format, va_list args)
  {
//    if(output(writer)->written == 0)
//      indent(writer);
    
    return xmlTextWriterWriteVFormatString(writer, format, args);
  }
      
  static void
  dump(writer_type writer)
  {
    using namespace std;
    
//    cout << "out: " << writer->out << endl;
    cout << "nodes: "; // << writer->nodes << endl;
    cout.flush();
    
    xmlLinkPtr link = xmlListFront(writer->nodes);
    int n = xmlListSize(writer->nodes);
    
    while(n--)
    {
      cout << *static_cast<char **>(xmlLinkGetData(link));
      
      if((link = link->next))
        cout << ", ";
    }
    
    cout << "(" << xmlListSize(writer->nodes) << ")" << endl;
    cout << "indent: " << writer->indent << endl;
    
/*    cout << "nsstack: " << writer->nsstack << endl;
    cout << "level: " << writer->level << endl;
    cout << "doindent: " << writer->doindent << endl;
    cout << "ichar: " << *writer->ichar << endl;
    cout << "qchar: " << writer->qchar << endl;
    cout << "ctxt: " << writer->ctxt << endl;
    cout << "no_doc_free: " << writer->no_doc_free << endl;
    cout << "doc: " << writer->doc << endl;*/
    
  }
  
  //-----------------------------------------------------------------------
};
  
//---------------------------------------------------------------------------

} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_LIBXML2_DOM_WRITER_HPP
