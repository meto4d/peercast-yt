#include <gtest/gtest.h>

#include "flv.h"
#include "sstream.h"

class FLVTagFixture : public ::testing::Test {
public:
    FLVTagFixture()
        :data{ // a Script tag
        0x12,0x00,0x01,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x0A,0x6F,0x6E,0x4D,0x65,0x74,0x61,0x44,0x61,0x74,0x61,
        0x08,0x00,0x00,0x00,0x0C,0x00,0x08,0x64,0x75,0x72,0x61,0x74,0x69,0x6F,0x6E,0x00,0x40,0xB8,0x28,0xC0,0x00,0x00,0x00,0x00,
        0x00,0x05,0x77,0x69,0x64,0x74,0x68,0x00,0x40,0x94,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x68,0x65,0x69,0x67,0x68,0x74,
        0x00,0x40,0x86,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x0D,0x76,0x69,0x64,0x65,0x6F,0x64,0x61,0x74,0x61,0x72,0x61,0x74,0x65,
        0x00,0x40,0x72,0x0D,0xEC,0x00,0x00,0x00,0x00,0x00,0x0C,0x76,0x69,0x64,0x65,0x6F,0x63,0x6F,0x64,0x65,0x63,0x69,0x64,0x00,
        0x40,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0D,0x61,0x75,0x64,0x69,0x6F,0x64,0x61,0x74,0x61,0x72,0x61,0x74,0x65,0x00,
        0x40,0x59,0x46,0xE0,0x00,0x00,0x00,0x00,0x00,0x0F,0x61,0x75,0x64,0x69,0x6F,0x73,0x61,0x6D,0x70,0x6C,0x65,0x72,0x61,0x74,
        0x65,0x00,0x40,0xE7,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x61,0x75,0x64,0x69,0x6F,0x73,0x61,0x6D,0x70,0x6C,0x65,0x73,
        0x69,0x7A,0x65,0x00,0x40,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x73,0x74,0x65,0x72,0x65,0x6F,0x01,0x01,0x00,0x0C,
        0x61,0x75,0x64,0x69,0x6F,0x63,0x6F,0x64,0x65,0x63,0x69,0x64,0x00,0x40,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x65,
        0x6E,0x63,0x6F,0x64,0x65,0x72,0x02,0x00,0x0D,0x4C,0x61,0x76,0x66,0x35,0x37,0x2E,0x36,0x36,0x2E,0x31,0x30,0x32,0x00,0x08,
        0x66,0x69,0x6C,0x65,0x73,0x69,0x7A,0x65,0x00,0x41,0xB2,0xD7,0x9D,0x35,0x00,0x00,0x00,0x00,0x00
            }
    {
    }

    void SetUp()
    {
    }

    void TearDown()
    {
    }

    ~FLVTagFixture()
    {
    }

    FLVTag tag;
    unsigned char data[283];
};

TEST_F(FLVTagFixture, initialState)
{
    ASSERT_EQ(0, tag.size);
    ASSERT_EQ(0, tag.packetSize);
    ASSERT_EQ(FLVTag::T_UNKNOWN, tag.type);
    ASSERT_EQ(nullptr, tag.data);
    ASSERT_EQ(nullptr, tag.packet);
}

TEST_F(FLVTagFixture, timestamp)
{
    StringStream mem( std::string((char*)data, (char*)data+283) );

    ASSERT_EQ(283, mem.getLength());

    tag.read(mem);

    ASSERT_EQ(283, mem.getPosition());

    ASSERT_EQ(273, tag.size);
    ASSERT_EQ(288, tag.packetSize);

    ASSERT_EQ(0, tag.getTimestamp());

    tag.setTimestamp(0x12345678);

    ASSERT_EQ(0x12345678, tag.getTimestamp());

    ASSERT_FALSE(tag.isKeyFrame());
    ASSERT_EQ(FLVTag::T_SCRIPT, tag.type);
}
