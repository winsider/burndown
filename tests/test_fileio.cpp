#include <burndown/fileio.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <cstdio>
#include <array>

using namespace ltc::bd;

class Test_Filestat : public ::testing::Test
{
public:
    void SetUp()
    {
        create_file();       
    }

    void TearDown()
    {
        std::remove(test_filename);
    }

    const char * test_filename = "testfile.tst";
    const char * test_filename_invalid = "testfile_not_exists.tst";

private:
    void create_file()
    {
        auto f = std::fopen(test_filename, "w");      
        int8_t data[1000];
        for (auto i=0; i<1000; i++)
            data[i] = i % 256;
        std::fwrite(&data, 1, 1000, f);   
        std::fclose(f);
    }
};

TEST_F(Test_Filestat, construct_default)
{
    Filestat s;
    EXPECT_FALSE(s.valid());
}

TEST_F(Test_Filestat, construct_init)
{
    Filestat s(test_filename);
    EXPECT_TRUE(s.valid());
}

TEST_F(Test_Filestat, constuct_init_invalid)
{
    EXPECT_THROW({
        Filestat s(test_filename_invalid);
    }, std::runtime_error);
}

TEST_F(Test_Filestat, init_invalid)
{
    Filestat s;
    EXPECT_FALSE(s.init(test_filename_invalid));
    EXPECT_FALSE(s.valid());
}

TEST_F(Test_Filestat, init_default)
{
    Filestat s;
    EXPECT_FALSE(s.valid());
}

TEST_F(Test_Filestat, filesize)
{
    Filestat s(test_filename);
    EXPECT_TRUE(s.valid());
    EXPECT_EQ(s.filesize(), 1000);
}

