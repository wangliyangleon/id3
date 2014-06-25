/**
 * @Author: WangLiyang
 * @Date:   2014/06/23 15:14:57
 * @Brief:  
 */
#ifndef _ID3_GDATA_H_
#define _ID3_GDATA_H_

#include <id3_def.h>
#include <id3_util.h>

namespace id3 {

/**
 * @Class:  GlobalData
 * @Brief:  global data, singleton
 */
class GlobalData {
public:
    static GlobalData* get_instance() {
        if (NULL == _instance) {
            _instance = new (std::nothrow) GlobalData();
            if (NULL == _instance) {
                std::cerr << "alloc global data failed" << std::endl;
            }
        }
        return _instance;
    }

    /**
     *      init gdata
     *      @param      file    [in]    corpus file path
     *      @return     0       succ
     *                  -1      failed
     */
    int init(const std::string& file);

    /**
     *      clear gdata
     */
    void clear();


    /**
     *      check if corpus pos
     *      @param      corpus_id   [in]    corpus id
     *      @return     1       pos
     *                  0       neg
     *                  -1      bad id
     */
    inline int is_pos_corpus(int corpus_id) {
        return ((corpus_id >= 0) && (corpus_id < _corpus_count)
                ? _corpus_value[corpus_id] : -1);
    }

    /**
     *      get attr value count by id
     *      @param      attr_id     [in]    attr id
     *      @return     >0      attr value count for attr id
     *                  0       bad attr id
     */
    inline int get_attr_value_count(int attr_id) {
        return ((attr_id >= 0) && (attr_id < _attr_count)
                ? _attr_value_count[attr_id] : 0);
    }

    /**
     *      get attr value by corpus id and attr id
     *      @param      corpus_id   [in]    corpus id
     *      @param      attr_id     [in]    attr id
     *      @return     >=0     attr value
     */
    inline int get_attr_value(int corpus_id, int attr_id) {
        return ((corpus_id < 0) || (attr_id < 0)
                || (corpus_id >= _corpus_count)
                || (attr_id >= _attr_count) ?
                -1 : _corpus_table[corpus_id][attr_id]);
    }

    /**
     *      get entropy by corpus
     *      @param      corpus  [in]    input corpus
     *      @return     double      entropy
     */
    double get_entropy(const std::set<int> &corpus);

    /**
     *      get globle corpus
     *      @return     std::set<int>*  globle corpus pointor
     */
    inline std::set<int>* get_globle_corpus() {
        return &_globle_corpus_set;
    }

    /**
     *      get globle attrs
     *      @return     std::set<int>*  globle attrs pointor
     */
    inline std::set<int>* get_globle_attrs() {
        return &_globle_attr_set;
    }

private:
    GlobalData() :
        _corpus_count(0),
        _attr_count(0) {}
    static GlobalData* _instance;

    /// counts
    int _corpus_count;
    int _attr_count;


    /// corpus table
    int _corpus_table[MAX_CORPUS_ROW_COUNT][MAX_ATTR_TYPE_COUNT];

    /// corpus value list
    int _corpus_value[MAX_CORPUS_ROW_COUNT];

    /// attr value cnt
    int _attr_value_count[MAX_ATTR_TYPE_COUNT];

    /// globle set
    std::set<int> _globle_corpus_set;
    std::set<int> _globle_attr_set;
};

}

#endif
