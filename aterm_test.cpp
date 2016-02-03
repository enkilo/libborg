#include <aterm2.h>

int main(int argc, char *argv[])
{
  
  ATinitialize(argc, argv);

  ATerm term = ATreadFromNamedFile("http_client.aterm");
  
  ATwriteToTextFile(term, stdout);
  
  return 0;
}
