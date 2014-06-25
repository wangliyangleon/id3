#include <id3.h>

namespace id3 {

int Id3::id3_solution(const std::set<int>& corpus,
        attr_node_t* parent,
        std::set<int>& attrs,
        attr_node_t** root) {
    GlobalData* gdata = GlobalData::get_instance();
    if (NULL == gdata) {
        std::cerr << "get gdata failed" << std::endl;
        return -1;
    }

    *root = new (std::nothrow) attr_node_t;
    if (NULL == *root) {
        std::cerr << "alloc new node failed" << std::endl;
        return -1;
    }

    attr_node_t* cur_node = *root;
    cur_node->parent_node = parent;
    // no attr, finish
    if (attrs.empty()) {
        return 0;
    }

    // check if is leaf node
    int pos_cnt = 0, neg_cnt = 0, sum = corpus.size();
    for (std::set<int>::const_iterator iter = corpus.begin();
            iter != corpus.end(); ++iter) {
        int pos_ret = gdata->is_pos_corpus(*iter);
        if (1 == pos_ret) {
            ++pos_cnt;
        } else if (0 == pos_ret) {
            ++neg_cnt;
        } else {
            --sum;
        }
    }
    if (0 == pos_cnt || sum == pos_cnt) {
        cur_node->rate = pos_cnt / sum;
        cur_node->attr_id = -1;
        return 0;
    }

    /// find best attribute, then erase it in the attrs
    int cur_attr_id = find_best_attr(corpus, attrs);
    cur_node->attr_id = cur_attr_id;

    std::set<int>::iterator iter = attrs.find(cur_attr_id);
    if (attrs.end() == iter) {
        std::cerr << "cannot find the iter for erase: " << cur_attr_id << std::endl;
        return -1;
    }
    attrs.erase(attrs.find(cur_attr_id));

    /// split corpus into parts, and biuld sub tree recursively
    int attr_value_cnt = gdata->get_attr_value_count(cur_attr_id);
    std::vector<std::set<int> > sub_corpus(attr_value_cnt);
    for (std::set<int>::const_iterator iter = corpus.begin();
            iter != corpus.end(); ++iter) {
        int attr_value = gdata->get_attr_value(*iter, cur_attr_id);
        if (attr_value < 0 || attr_value >= attr_value_cnt) {
            std::cerr << "bad attr value " << attr_value << " for " << cur_attr_id << std::endl;
            continue;
        }
        sub_corpus.at(attr_value).insert(*iter);
    }
    for (std::vector<std::set<int> >::iterator iter = sub_corpus.begin();
            iter != sub_corpus.end(); ++iter) {
        attr_node_t* subtree = NULL;
        if (0 == iter->size()) {
            std::cerr << "empty sub corpus, parant attr: " << cur_attr_id << std::endl;
            continue;
        }
        if (0 != id3_solution(*iter, cur_node, attrs, &subtree)) {
            std::cerr << "build sub tree failed" << std::endl;
            continue;
        }
        cur_node->children_nodes.push_back(subtree);
    }
    return 0;
}

int Id3::find_best_attr(const std::set<int>& corpus,
        const std::set<int>& attrs) {
    double max = 0.0;  
    int best_attr = -1;  
    for (std::set<int>::const_iterator iter = attrs.begin();
            iter != attrs.end(); ++iter) {
        double ret = get_gain(corpus, *iter);
        if (ret > max) {
            max = ret;
            best_attr = *iter;
        }
    }
    return best_attr;
}

double Id3::get_gain(const std::set<int>& corpus, int attr_id) {
    GlobalData* gdata = GlobalData::get_instance();
    if (NULL == gdata) {
        std::cerr << "get gdata failed" << std::endl;
        return 0.0;
    }
    if (0 == corpus.size()) {
        std::cerr << "empty corpus" << std::endl;
        return 0.0;
    }
    int attr_count = gdata->get_attr_value_count(attr_id);
    double ans = gdata->get_entropy(corpus);
    double sum = corpus.size();
    std::vector<std::set<int> > attr_ans_vec(attr_count);
    for (std::set<int>::const_iterator iter = corpus.begin();
            iter != corpus.end(); ++iter) {
        int attr_value = gdata->get_attr_value(*iter, attr_id);
        if (attr_value < 0 || attr_value >= attr_count) {
            std::cerr << "bad attr value " << attr_value << " for attr " << attr_id << std::endl;
            continue;
        }
        attr_ans_vec.at(attr_value).insert(*iter);
    }
    for (std::vector<std::set<int> >::const_iterator iter = attr_ans_vec.begin();
            iter != attr_ans_vec.end(); ++iter) {
        ans -= iter->size() / sum * gdata->get_entropy(*iter);
    }
    return ans;
}

void Id3::destroy(attr_node_t** root) {
    if (NULL == *root) {
        return;
    }
    for (size_t i = 0; i < (*root)->children_nodes.size(); ++i) {
        destroy(&((*root)->children_nodes.at(i)));
    }
    delete *root;
    *root = NULL;
}

}
