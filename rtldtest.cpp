#include <sys/rtld.hpp>
#include <vst/vst_proxy.hpp>
#include <borg/types/rect_type.hpp>
#include <iostream>

using namespace std;
//using namespace vst;

int main()
{
  sys::rtld rtld("vsttest.dll");
  
  cout << rtld.sym<void *>("VSTPluginMain") << endl;
  cout << rtld.sym<void *>("main") << endl;
  
  rtld.close();
  
  vst::proxy proxy("vsttest.dll");
  
  cout << (void *)proxy.get_main() << endl;
  
  float in[2][10];
  float out[2][10];
  float *pin[2] = { in[0], in[1] };
  float *pout[2] = { out[0], out[1] };
  
  proxy.process_replacing(pin, pout, 10);
  
  ERect *erect;
  proxy.get_editor_rect(&erect);
  
  borg::rect<int> r(erect->left, erect->top,
                    erect->right - erect->left, 
                    erect->bottom - erect->top);
  
  cout << "rect: " << r << endl;
  
  proxy.close();
}
