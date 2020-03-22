#ifndef STREAMUTILS_STREAMUTILS_OPT_H
#define STREAMUTILS_STREAMUTILS_OPT_H

#include "comm.h"

class streamUtils_opt {
public:
    static Exception parse_options(int argc, char *argv[], OptionParseCtx *parseCtx);

    static void printusage();

protected:

private:
};


#endif //STREAMUTILS_STREAMUTILS_OPT_H
