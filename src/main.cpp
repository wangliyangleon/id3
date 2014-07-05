#include <id3.h>

void trans_node(id3::attr_node_t* pnode, std::string pre) {
    if (nullptr == pnode) {
        return;
    }
    if (pnode->attr_id < 0) {
        std::cout << pre.c_str() << "leaf node, pos rate: " << pnode->rate << std::endl;
    } else {
        std::cout << pre.c_str() << "cur attr id: " << pnode->attr_id << std::endl;
    }

    for (auto node : pnode->children_nodes) {
        trans_node(node, pre + "\t");
    }
}

int main() {
    id3::Id3 id3_test;
    id3::GlobalData* gdata = id3::GlobalData::get_instance();
    if (nullptr == gdata) {
        std::cerr << "get gdata failed" << std::endl;
        return -1;
    }

    if (0 != gdata->init("./data/test.dat")) {
        std::cerr << "init gdata failed" << std::endl;
        return -1;
    }

    id3::attr_node_t* root = nullptr;
    if (0 != id3_test.id3_solution(
                *(gdata->get_globle_corpus()),
                nullptr,
                *(gdata->get_globle_attrs()),
                &root)) {
        std::cerr << "build solution tree failed" << std::endl;
        return -1;
    }

    /// trans des tree
    trans_node(root, "");
    id3_test.destroy(&root);

    return 0;
}
