#ifndef BORG_LIBXML2_XPATH_RESULT_HPP
#define BORG_LIBXML2_XPATH_RESULT_HPP

#include <borg/libxml2/traits.hpp>

namespace borg { 
namespace xml { 
namespace xpath {

//----------------------------------------------------------------------------
template<>
class result_impl<libxml2::traits>
{
public:
  XML_XPATH_TYPES(libxml2::traits)
  
  //-----------------------------------------------------------------------
  template<class ResultT>
  static int
  type(const ResultT &res)
  {
    return res->type;
  }

  //-----------------------------------------------------------------------
  template<class ResultT>
  static nodeset_type
  nodeset(const ResultT &res)
  {
    if(res->type == XPATH_NODESET)
      return res->nodesetval;
    
    return 0;
  }
  
  //-----------------------------------------------------------------------
  static number_type
  number(result_type res)
  {
    if(res->type == XPATH_NUMBER)
      return res->floatval;
    
    return xmlXPathCastToNumber(res);
  }
  
  //-----------------------------------------------------------------------
  static wchar_type *
  string(result_type res)
  {
    if(res->type == XPATH_STRING)
      return res->stringval;
    
    return xmlXPathCastToString(res);
  }
  
  //-----------------------------------------------------------------------
  static bool
  boolean(result_type res)
  {
    if(res->type == XPATH_BOOLEAN)
      return res->boolval;
    
    return xmlXPathCastToBoolean(res);
  }
  
};

} // namespace xpath
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_LIBXML2_XPATH_RESULT_HPP
