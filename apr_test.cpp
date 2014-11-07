#define APR_DECLARE_STATIC 1
#define APU_DECLARE_STATIC 1

#include <iostream>

#include <apr.h>
#include <apr_file_io.h>
#include <apr_file_info.h>
#include <apr_pools.h>

#include <borg/apr/buckets.hpp>
#include <borg/apr/file_io.hpp>
#include <borg/apr/tables.hpp>

namespace borg {
namespace apr {

//static apr::allocator_t allocator;

}
}

int test_file_io()
{
  using namespace borg;
  
//  apr::pool pool(apr::allocator);
  
  apr::file testfile("test.txt", APR_WRITE|APR_CREATE|APR_TRUNCATE
#if APR_MAJOR_VERSION == 0
                    , APR_UREAD|APR_UWRITE
#else
                    , APR_FPROT_UREAD|APR_FPROT_UWRITE
#endif
                    );
  
  apr_file_printf(testfile, "hello world!\n");
  testfile.close();
  
 // pool.destroy();

  return 0;
}

int main()
{
  using namespace std;
  using namespace borg;
    
  try
  {
    using namespace apr;
    
    test_file_io();
    
    pool_t pool;
    bucket_alloc_t bucket_alloc;
    
    eos_bucket eosbpp(bucket_alloc);
    cout << "is_eos() = " << eosbpp.is_eos() << endl;

    flush_bucket flushbpp(bucket_alloc);
    cout << "is_flush() = " << flushbpp.is_flush() << endl;
   
    table tpp(pool, 0);
    
    tpp.set("test", "blah");
    tpp.set("lala", "0x29a");

    cout << "get(\"test\") = " << tpp.get("test") << endl;
    
    return 0;
  }
  catch(apr::exception &e)
  {
    cerr << "apr::exception - " << e.what() << endl;
    return 1;
  }
  catch(std::exception &e)
  {
    cerr << "std::exception - " << e.what() << endl;
    return 127;
  }
  return 0;
}
