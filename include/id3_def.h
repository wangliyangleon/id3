/**
 * @Author: WangLiyang
 * @Date:   2014/06/23 14:56:29
 * @Brief:  common definitions
 */
#ifndef _ID3_DEF_H_
#define _ID3_DEF_H_

#include <stdint.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cmath>

namespace id3 {

/**
 * @Struct: attr_node_t
 * @Brief:  attr node definition
 */
typedef struct _attr_node_t {
    double rate;
    int attr_id;
    _attr_node_t* parent_node;
    std::vector<_attr_node_t*> children_nodes;
} attr_node_t;

/// const data definition
const size_t MAX_CORPUS_LINE_LEN = 2048;
const char CORPUS_SPLIT_CHAR = '\t';
const size_t MAX_CORPUS_ROW_COUNT = 1024 * 32;
const size_t MAX_ATTR_TYPE_COUNT = 1024;
const size_t MAX_VALUE_PER_ATTR = 128;
const char* const POS_SAMPLE_SIGN = "1";

}
#endif
