#ifndef STREAMUTILS_STREAMUTILS_OPT_H
#define STREAMUTILS_STREAMUTILS_OPT_H

#include "comm.h"

#define CHECK_ARGS_COUNT(n)\
  if (n >= argc) { printf("Incorrect number of parameters\n"); print_usage(argv[0]); return 1; }

#define READ_PAR_STRING(dest)\
{\
  i++;\
  CHECK_ARGS_COUNT(i);\
  dest = argv[i];\
}

#define READ_PAR_INT(num, format)\
{\
  i++;\
  CHECK_ARGS_COUNT(i);\
  sscanf(argv[i], format, &num);\
}

class streamUtils_opt {
public:
    static int parse_options(int argc, char *argv[], OptionParse *optionParse);

    static void print_usage(char *string);

    static int check_parse(OptionParse *optionParse, YuvUtilsCtx *yuvUtilsCtx);

protected:

private:

};


#endif //STREAMUTILS_STREAMUTILS_OPT_H
