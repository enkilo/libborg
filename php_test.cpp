#define ZTS
#define PTHREADS

#include <fstream>
#include <iterator>
extern "C" {
  #include <php5/Zend/zend.h>
}

#include <php5/TSRM/TSRM.h>
#include <php5/Zend/FlexLexer.h>
#include <php5/Zend/zend_API.h>
#include <php5/Zend/zend_globals.h>
#include <php5/Zend/zend_globals_macros.h>
#include <php5/main/php.h>
#include <php5/main/php_globals.h>

#include <borg/zend.hpp>

using namespace std;
using namespace borg;

int main()
{
  ifstream input("p_eitsch_p.php");

  copy(istream_iterator<string>(input), istream_iterator<string>(), 
       ostream_iterator<string>(cout));

  zend_utility_functions zuf;
  zend_utility_values zuv;
 
  zend_compiler_globals *compiler_globals;
  zend_executor_globals *executor_globals;
  php_core_globals *core_globals;
  void ***tsrm_ls;
  
#ifdef ZTS
  tsrm_startup(1, 1, 0, NULL);

  compiler_globals = (zend_compiler_globals *)ts_resource((ts_rsrc_id)compiler_globals_id);
  executor_globals = (zend_executor_globals *)ts_resource((ts_rsrc_id)executor_globals_id);
  core_globals = (php_core_globals *)ts_resource((ts_rsrc_id)core_globals_id);
  tsrm_ls = (void ***)ts_resource(0);
//  *ptsrm_ls = tsrm_ls;
  
#endif

//  zend_startup(&zuf, NULL, 1);
  
  zval zv1;
  script::value_t<zend::traits> v(zv1);
  
  v.print_r(2);
  
  zval zv2 = v;
  
  return 0;
}
