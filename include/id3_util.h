/**
 * @Author: WangLiyang
 * @Date:   2014/06/23 15:26:27
 * @Brief:  util definition
 */
#ifndef _ID3_UTIL_H_
#define _ID3_UTIL_H_

#include <id3_def.h>

namespace id3 {

// string sign definition
union Sign {
    struct {
        uint32_t s1;
        uint32_t s2;
    };
    uint64_t s;
};

/**
 *      get string sign (64 byte)
 *      @param      str     [in]    input string
 *      @param      len     [in]    input string length
 *      @param      sign    [out]   sign result
 *      @return     0       succ
 *                  -1      failed
 */
int create_sign_64(const char *str, size_t len, Sign& sign);

/**
 *      calc lg
 *      @param      d       [in]    param
 *      @return     double  lg2(d)
 */
double lg2(double n);


}

#endif
