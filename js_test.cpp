#include <string>
#include <iostream>

#include <js/jsapi.h>
#include <js/jsscan.h>
#include <js/jsparse.h>

#include <borg/parse.hpp>
#include <borg/js.hpp>
#include <borg/js/token_iterator.hpp>

#include <boost/range.hpp>

template<class CharT>
static inline 
std::size_t
strlen(const CharT *const s)
{
  const CharT *ptr = s;

  while(*ptr)
    ++ptr;

  return ptr - s;
}

int main()
{
/*
  JSObject *global = JS_GetGlobalObject(cx);
  
  std::cout << "global obj: " << global << std::endl;
  
  global = JS_NewObject(cx, NULL, NULL, NULL);
  
  JS_InitStandardClasses(cx, global);
  
  std::string script_str = "blah = 3 * Math.PI";
  
  JSScript *scr = JS_CompileScript
    (cx, global, script_str.c_str(), script_str.length(), "script_str", 0);
  
  jsval rval;
  
  JS_ExecuteScript(cx, global, scr, &rval);
 
   if(JSVAL_IS_DOUBLE(rval))
    std::cout << "result: " << *JSVAL_TO_DOUBLE(rval) << std::endl;
  

 */
  using namespace std;

  FILE *fp = fopen("test.js", "r");

  const jschar test_script[] = { '/','*',' ','w','e','l','l',',',' ','f','i','r','s','t',' ','w','e',' ','h','a','v','e',' ','a',' ','c','o','m','m','e','n','t','.','.','.','.',' ','*','/',' ','f','u','n','c','t','i','o','n',' ','l','a','m','e','(',')',' ','{',' ','v','a','r',' ','x',' ','=',' ','f','u','n','c','t','i','o','n','(',')',' ','{','}',';',' ','r','e','t','u','r','n',' ','x',';',' ','}' };
  const jschar *test_ptr = test_script;
  const jschar *test_limit = test_ptr + strlen(test_script);

  cout << "strlen(test_script) = " << strlen(test_script) << endl;
  cout << "sizeof(test_script) = " << sizeof(test_script) << endl;

  using namespace borg;

 // js::runtime rt(4 * 1024 * 1024);
  js::context cx; // (rt, 8192);

  js::init_scanner(cx);
  js::token_stream ts(cx, test_ptr, test_limit);
  js::token_type tok;
  js::token_iterator tokit(cx, boost::begin(test_script), boost::end(test_script));
  js::token_iterator endit;

  while(tokit != endit)
  {
    js::token tok = *tokit;
    
    ++tokit;
  }
  
  JSStringBuffer buf;

  js::string_buffer_t out_buf = &buf;
  js_InitStringBuffer(out_buf);

  cout << "size of out_buf: " << sizeof(out_buf) << endl;

  out_buf.write("test string");

  cout << "out_buf.length() = " << out_buf.size() << endl;

  for(int i = 0; i < 7; i++)
  {
    //tok = (js::token_type)js::token_stream_a::get(ts, cx);

    tok = ts.get(cx);

    js::string_buffer_t sb = ts.tokenbuf();

//    ts.linebuf();
    ts.current().print(cout);

    cout << endl;
//    cout << "token type=" << tok << ",value=" << ts.current().get_value() << endl;
  }

  return 0;
}
