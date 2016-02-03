#ifndef MSG_HPP
#define MSG_HPP

#include <stdio.h>

#define MSG_ERROR(x...) \
  do { \
    FILE *fp = stderr; \
    fprintf(fp, x); \
    fputc('\n',fp); \
    fflush(fp); \
  } while(0);

#ifdef WIN32
#include <windows.h>

#define MSG_BOX(x...) \
  do { \
    char b[1024]; \
    sprintf(b,x); \
    MessageBox(0, (b), "MSG", 0); \
  } while(0);
#else
#define MSG_BOX(x...)
#endif

#endif //ndef MSG_HPP
