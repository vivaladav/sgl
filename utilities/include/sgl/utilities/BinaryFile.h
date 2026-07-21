#pragma once

#include <fstream>

namespace sgl
{
namespace utilities
{

class BinaryFile
{
public:
    enum OpenMode : unsigned int
    {
        OPEN_OUTPUT,
        OPEN_INPUT,
    };

public:
    BinaryFile(const std::string & path, OpenMode mode, bool truncate);
    ~BinaryFile();

    bool OpenToWri();
    bool OpenToWrite(const std::string & path, bool truncate);

    bool IsOpen() const;

    void WriteCString(const char * str, unsigned int size);
    void WriteString(const std::string & str);
    void WriteInt(int val);
    void WriteUint(unsigned int val);
    void WriteFloat(float val);
    void WriteDouble(double val);

    void Close();

private:
    std::fstream mStream;
};

inline bool BinaryFile::IsOpen() const { return mStream.is_open(); }

inline void BinaryFile::WriteCString(const char * str, unsigned int size)
{
    mStream.write(str, size);
}

inline void BinaryFile::WriteString(const std::string & str)
{
    mStream.write(str.c_str(), str.size());
}

inline void BinaryFile::WriteInt(int val)
{
    mStream.write(reinterpret_cast<const char *>(&val), sizeof(int));
}

inline void BinaryFile::WriteUint(unsigned int val)
{
    mStream.write(reinterpret_cast<const char *>(&val), sizeof(unsigned int));
}

inline void BinaryFile::WriteFloat(float val)
{
    mStream.write(reinterpret_cast<const char *>(&val), sizeof(float));
}

inline void BinaryFile::WriteDouble(double val)
{
    mStream.write(reinterpret_cast<const char *>(&val), sizeof(double));
}

inline void BinaryFile::Close()
{
    mStream.close();
}

} // namespace utilities
} // namespace sgl