#include <borg/wrap/preproc.hpp>
#include <borg/util/lexical_function.hpp>

//WRAP_PATTERN_ARRAY

WRAP_PATTERN_FORWARD(document)

WRAP_CLASS_TEMPLATE(iterator, _facade, );
WRAP_CLASS_TEMPLATE(container, _facade, (typename T));
  
BORG_UTIL_LEXICAL_ARGS(void, 1)
BORG_UTIL_LEXICAL_ARGS(int, 0)

int main()
  
{
}
