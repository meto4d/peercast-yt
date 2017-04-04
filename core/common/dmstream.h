#ifndef _DMSTREAM_H
#define _DMSTREAM_H

#include <vector>
#include "stream.h"
#include <string>

class DynamicMemoryStream : public Stream
{
public:
    DynamicMemoryStream();

    int  read(void *, int) override;
    void write(const void *, int) override;
    bool eof() override;
    void rewind() override;
    void seekTo(int) override;
    int  getPosition() override;
    int  getLength();

    std::string str();

    void checkSize(int);

    int m_pos;
    std::vector<uint8_t> m_buffer;
};

#endif