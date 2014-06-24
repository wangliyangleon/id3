/**
 * @Author: WangLiyang
 * @Date:   2014/06/23 16:41:36
 * @Brief:  
 */
#ifndef _ID3_H_
#define _ID3_H_

#include <id3_def.h>
#include <id3_gdata.h>

namespace id3 {

/**
 * @Class:  Id3
 * @Brief:  Id3 definition
 */
class Id3 {
public:
    /**
     *      build tree
     *      @param      root    [out]       tree root
     *      @param      corpus  [in]        corpus
     *      @param      attr    [in|out]    attrs
     *      @param      parent  [in]        parent node
     *      @return     0       succ
     *                  -1      failed
     */
    int id3_solution(attr_node_t*& root,
            const std::set<int>& corpus,
            std::set<int>& attrs,
            attr_node_t* parent);

    /**
     *      find test attr
     *      @param      corpus  [in]        corpus
     *      @param      attr    [in]        attrs
     *      @return     int     best attr
     */
    int find_best_attr(const std::set<int>& corpus,
            const std::set<int>& attrs);

    /**
     *      get gain by attr id      
     *      @param      corpus  [in]        corpus
     *      @param      attr_id [in]        attr id
     *      @return     double      gain
     */
    double get_gain(const std::set<int>& corpus, int attr_id);

    
private:
};

}

#endif
