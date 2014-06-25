/**
 * @Author: WangLiyang
 * @Date:   2014/06/25 17:16:15
 * @Brief:  test global data
 */

#include <stdlib.h>
#include <gtest/gtest.h>

#include <id3_gdata.h>

class GdataTest : public ::testing::Test {
protected:
    GdataTest() {}
    virtual ~GdataTest() {}

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

TEST_F(GdataTest, test_load_and_clear) {
    std::set<int>* pset = NULL;
    id3::GlobalData* gdata = id3::GlobalData::get_instance();
    ASSERT_NE((id3::GlobalData*)NULL, gdata);

    /// good cases
    // init and check size (normal)
    ASSERT_EQ(0, gdata->init("./test_data/test.dat"));
    pset = gdata->get_globle_corpus();
    ASSERT_NE((std::set<int>*)NULL, pset);
    ASSERT_EQ(14u, pset->size());
    pset = gdata->get_globle_attrs();
    ASSERT_NE((std::set<int>*)NULL, pset);
    ASSERT_EQ(4u, pset->size());
    // clear and check size
    gdata->clear();
    pset = gdata->get_globle_corpus();
    ASSERT_NE((std::set<int>*)NULL, pset);
    ASSERT_EQ(0u, pset->size());
    pset = gdata->get_globle_attrs();
    ASSERT_NE((std::set<int>*)NULL, pset);
    ASSERT_EQ(0u, pset->size());
    // init and check size (has 2 bad lines)
    ASSERT_EQ(0, gdata->init("./test_data/test_2_bad_lines.dat"));
    pset = gdata->get_globle_corpus();
    ASSERT_NE((std::set<int>*)NULL, pset);
    ASSERT_EQ(12u, pset->size());
    pset = gdata->get_globle_attrs();
    ASSERT_NE((std::set<int>*)NULL, pset);
    ASSERT_EQ(4u, pset->size());


    /// bad cases
    // not exist
    ASSERT_EQ(-1, gdata->init("./test_data/test_not_exist.dat"));
    ASSERT_NE((std::set<int>*)NULL, pset);
    ASSERT_EQ(0u, pset->size());
    pset = gdata->get_globle_attrs();
    ASSERT_NE((std::set<int>*)NULL, pset);
    ASSERT_EQ(0u, pset->size());
    // bad format
    ASSERT_EQ(-1, gdata->init("./test_data/test_bad_format.dat"));
    ASSERT_NE((std::set<int>*)NULL, pset);
    ASSERT_EQ(0u, pset->size());
    pset = gdata->get_globle_attrs();
    ASSERT_NE((std::set<int>*)NULL, pset);
    ASSERT_EQ(0u, pset->size());
    // empty
    ASSERT_EQ(-1, gdata->init("./test_data/test_empty.dat"));
    ASSERT_NE((std::set<int>*)NULL, pset);
    ASSERT_EQ(0u, pset->size());
    pset = gdata->get_globle_attrs();
    ASSERT_NE((std::set<int>*)NULL, pset);
    ASSERT_EQ(0u, pset->size());
}
 
TEST_F(GdataTest, test_check_corpus) {
    id3::GlobalData* gdata = id3::GlobalData::get_instance();
    ASSERT_NE((id3::GlobalData*)NULL, gdata);
    gdata->clear();
    ASSERT_EQ(0, gdata->init("./test_data/test.dat"));

    /// good cases
    // check is pos corpus
    ASSERT_EQ(0, gdata->is_pos_corpus(0));
    ASSERT_EQ(1, gdata->is_pos_corpus(2));
    // check attr value count
    ASSERT_EQ(3, gdata->get_attr_value_count(0));
    ASSERT_EQ(3, gdata->get_attr_value_count(1));
    ASSERT_EQ(2, gdata->get_attr_value_count(2));
    ASSERT_EQ(2, gdata->get_attr_value_count(3));
    // check attr value
    ASSERT_EQ(0, gdata->get_attr_value(0, 0));
    ASSERT_EQ(2, gdata->get_attr_value(8, 1));
    ASSERT_EQ(1, gdata->get_attr_value(4, 2));
    ASSERT_EQ(1, gdata->get_attr_value(5, 3));

    /// bad cases
    // bad corpus id
    ASSERT_EQ(-1, gdata->is_pos_corpus(-1));
    ASSERT_EQ(-1, gdata->is_pos_corpus(14));
    // bad attr id
    ASSERT_EQ(0, gdata->get_attr_value_count(-1));
    ASSERT_EQ(0, gdata->get_attr_value_count(4));
    // bad corpus id or bad attr id
    ASSERT_EQ(-1, gdata->get_attr_value(-1, 0));
    ASSERT_EQ(-1, gdata->get_attr_value(14, 0));
    ASSERT_EQ(-1, gdata->get_attr_value(0, -1));
    ASSERT_EQ(-1, gdata->get_attr_value(0, 4));
    ASSERT_EQ(-1, gdata->get_attr_value(-1, -1));
    ASSERT_EQ(-1, gdata->get_attr_value(14, 4));
}

TEST_F(GdataTest, test_check_entropy) {
    std::set<int> test_corpus;
    id3::GlobalData* gdata = id3::GlobalData::get_instance();
    ASSERT_NE((id3::GlobalData*)NULL, gdata);
    gdata->clear();
    ASSERT_EQ(0, gdata->init("./test_data/test.dat"));
    
    /// good cases
    // empty corpus
    ASSERT_DOUBLE_EQ(0.0, gdata->get_entropy(test_corpus));
    // not empty corpus
    test_corpus.insert(0);
    test_corpus.insert(1);
    test_corpus.insert(2);
    double result = -1.0 / 3 * id3::lg2(1.0 / 3) - 2.0 / 3 * id3::lg2(2.0 / 3);
    ASSERT_DOUBLE_EQ(result, gdata->get_entropy(test_corpus));

    /// bad cases
    test_corpus.clear();
    test_corpus.insert(-1);
    test_corpus.insert(14);
    ASSERT_DOUBLE_EQ(0.0, gdata->get_entropy(test_corpus));
}
