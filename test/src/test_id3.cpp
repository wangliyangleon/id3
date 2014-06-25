/**
 * @Author: WangLiyang
 * @Date:   2014/06/25 19:18:04
 * @Brief:  test id3 logic
 */
#include <stdlib.h>
#include <gtest/gtest.h>

#include <id3.h>

class Id3Test : public ::testing::Test {
protected:
    Id3Test() {}
    virtual ~Id3Test() {}

    virtual void SetUp()
    {
        // SetUp
    }
    
    virtual void TearDown()
    {
        // TearDown
    }
};

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(Id3Test, test_find_best_attr) {
    id3::Id3 id3_test;                                
    id3::GlobalData* gdata = id3::GlobalData::get_instance();
    ASSERT_NE((id3::GlobalData*)NULL, gdata);
    gdata->clear();
    ASSERT_EQ(0, gdata->init("./test_data/test.dat"));

    /// good cases, regression test cases
    std::set<int> test_attr;
    test_attr = *(gdata->get_globle_attrs());
    ASSERT_EQ(0, id3_test.find_best_attr(
                *(gdata->get_globle_corpus()),
                test_attr));
    test_attr.erase(0);
    ASSERT_EQ(2, id3_test.find_best_attr(
                *(gdata->get_globle_corpus()),
                test_attr));
    test_attr.erase(2);
    ASSERT_EQ(3, id3_test.find_best_attr(
                *(gdata->get_globle_corpus()),
                test_attr));
    test_attr.erase(3);
    ASSERT_EQ(1, id3_test.find_best_attr(
                *(gdata->get_globle_corpus()),
                test_attr));
}

TEST_F(Id3Test, test_build_and_destroy) {
    id3::Id3 id3_test;                                
    id3::attr_node_t* root = NULL;
    id3::attr_node_t* node = NULL;
    id3::GlobalData* gdata = id3::GlobalData::get_instance();
    ASSERT_NE((id3::GlobalData*)NULL, gdata);
    gdata->clear();
    ASSERT_EQ(0, gdata->init("./test_data/test.dat"));

    /// good cases, regression test cases
    ASSERT_EQ(0, id3_test.id3_solution(
                *(gdata->get_globle_corpus()),
                NULL,
                *(gdata->get_globle_attrs()),
                &root));

    /// lv1
    ASSERT_NE((id3::attr_node_t*)NULL, root);
    ASSERT_EQ(0, root->attr_id);
    ASSERT_EQ(3u, root->children_nodes.size());

    /// lv2
    node = root->children_nodes.at(0);
    ASSERT_NE((id3::attr_node_t*)NULL, node);
    ASSERT_EQ(2, node->attr_id);
    ASSERT_EQ(2u, node->children_nodes.size());
    node = root->children_nodes.at(1);
    ASSERT_NE((id3::attr_node_t*)NULL, node);
    ASSERT_EQ(-1, node->attr_id);
    ASSERT_EQ(0u, node->children_nodes.size());
    ASSERT_DOUBLE_EQ(1.0, node->rate);
    node = root->children_nodes.at(2);
    ASSERT_NE((id3::attr_node_t*)NULL, node);
    ASSERT_EQ(3, node->attr_id);
    ASSERT_EQ(2u, node->children_nodes.size());

    /// lv3
    node = root->children_nodes.at(0)->children_nodes.at(0);
    ASSERT_NE((id3::attr_node_t*)NULL, node);
    ASSERT_EQ(-1, node->attr_id);
    ASSERT_EQ(0u, node->children_nodes.size());
    ASSERT_DOUBLE_EQ(0.0, node->rate); 
    node = root->children_nodes.at(0)->children_nodes.at(1);
    ASSERT_NE((id3::attr_node_t*)NULL, node);
    ASSERT_EQ(-1, node->attr_id);
    ASSERT_EQ(0u, node->children_nodes.size());
    ASSERT_DOUBLE_EQ(1.0, node->rate); 
    node = root->children_nodes.at(2)->children_nodes.at(0);
    ASSERT_NE((id3::attr_node_t*)NULL, node);
    ASSERT_EQ(-1, node->attr_id);
    ASSERT_EQ(0u, node->children_nodes.size());
    ASSERT_DOUBLE_EQ(1.0, node->rate); 
    node = root->children_nodes.at(2)->children_nodes.at(1);
    ASSERT_NE((id3::attr_node_t*)NULL, node);
    ASSERT_EQ(-1, node->attr_id);
    ASSERT_EQ(0u, node->children_nodes.size());
    ASSERT_DOUBLE_EQ(0.0, node->rate); 

    id3_test.destroy(&root);
    ASSERT_EQ((id3::attr_node_t*)NULL, root);

}


