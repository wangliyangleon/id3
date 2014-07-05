/**
 * @Author: WangLiyang
 * @Date:   2014/06/25 16:46:49
 * @Brief:  test utils
 */

#include <stdlib.h>
#include <float.h>
#include <gtest/gtest.h>

#include <id3_util.h>

class UtilTest : public ::testing::Test {
protected:
    UtilTest() {}
    virtual ~UtilTest() {}

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

TEST_F(UtilTest, test_create_sign) {
    id3::Sign test_sign;
    id3::Sign check_sign;

    /// good cases
    // length <= 4
    ASSERT_EQ(0, id3::create_sign_64("wang", 4, test_sign));
    check_sign.s = 1735287159lu;
    EXPECT_EQ(test_sign.s, check_sign.s);
    // 4 < length <= 8
    ASSERT_EQ(0, id3::create_sign_64("wangli", 6, test_sign));
    check_sign.s = 115914312671607lu;
    EXPECT_EQ(test_sign.s, check_sign.s);
    // length > 8
    ASSERT_EQ(0, id3::create_sign_64("wangliyang", 10, test_sign));
    check_sign.s = 15784074399946037909lu;
    EXPECT_EQ(test_sign.s, check_sign.s);

    /// bad cases
    ASSERT_EQ(-1, id3::create_sign_64(nullptr, 0, test_sign));
    ASSERT_EQ(-1, id3::create_sign_64("test", 0, test_sign));
}

TEST_F(UtilTest, test_lg2) {
    /// good cases
    ASSERT_DOUBLE_EQ(id3::lg2(0.5), log(0.5) / log(2));
    ASSERT_DOUBLE_EQ(id3::lg2(1), 0.0);
    ASSERT_DOUBLE_EQ(id3::lg2(2), 1.0);
    ASSERT_DOUBLE_EQ(id3::lg2(100), log(100) / log(2));

    /// bad cases
    ASSERT_TRUE(isinf(id3::lg2(0)));
    ASSERT_TRUE(isnan(id3::lg2(-1)));
}
