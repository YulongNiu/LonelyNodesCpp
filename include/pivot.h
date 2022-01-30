#ifndef _PIVOT_H_
#define _PIVOT_H_

#include "init.h"
#include "util.h"

ln::vecu IntersectionIdc_(const ln::vecu& fv, const ln::vecu& tv);

ln::iterv NextPnode_(ln::vecu& eachNodes, const ln::vecu& eachIndicators);

ln::vecu NextIdc_(const ln::vecu&  eachNodes,
                  const ln::vecu&  eachXnodes,
                  const ln::gumap& g);

#endif // _PIVOT_H_
