#include <id3.h>

void trans_node(id3::attr_node_t* pnode, std::string pre) {
    if (NULL == pnode) {
        return;
    }
    if (pnode->attr_id < 0) {
        std::cout << pre.c_str() << "leaf node, pos rate: " << pnode->rate << std::endl;
    } else {
        std::cout << pre.c_str() << "cur attr id: " << pnode->attr_id << std::endl;
    }

    for (std::vector<id3::attr_node_t*>::const_iterator iter = pnode->children_nodes.begin();
            iter != pnode->children_nodes.end(); ++iter) {
        trans_node(*iter, pre + "\t");
    }
}

int main() {
    id3::Id3 id3_test;
    id3::GlobalData* gdata = id3::GlobalData::get_instance();
    if (NULL == gdata) {
        std::cerr << "get gdata failed" << std::endl;
        return -1;
    }

    if (0 != gdata->init("./data/test.dat")) {
        std::cerr << "init gdata failed" << std::endl;
        return -1;
    }

    id3::attr_node_t* root = NULL;
    if (0 != id3_test.id3_solution(root,
            *(gdata->get_globle_corpus()),
            *(gdata->get_globle_attrs()),
            NULL)) {
        std::cerr << "build solution tree failed" << std::endl;
        return -1;
    }

    /// trans des tree
    trans_node(root, "");

    return 0;
}
