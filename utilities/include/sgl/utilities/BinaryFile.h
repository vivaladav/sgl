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

    bool IsOpen() const;

    void ReadCstring(char str[]);
    void ReadString(std::string & str);
    bool ReadBool();
    int ReadInt();
    unsigned int ReadUint();
    float ReadFloat();
    double ReadDouble();

    void WriteCstring(const char * str, unsigned int size);
    void WriteString(const std::string & str);
    void WriteBool(bool val);
    void WriteInt(int val);
    void WriteUint(unsigned int val);
    void WriteFloat(float val);
    void WriteDouble(double val);

    void Close();

private:
    std::fstream mStream;
};

inline bool BinaryFile::IsOpen() const { return mStream.is_open(); }

inline void BinaryFile::ReadCstring(char str[])
{
    const unsigned int size = ReadUint();

    if(size > 0)
        mStream.read(str, size);
}

inline void BinaryFile::ReadString(std::string & str)
{
    const unsigned int size = ReadUint();

    if(size > 0)
    {
        str.resize(size);
        mStream.read(str.data(), size);
    }
}

inline bool BinaryFile::ReadBool()
{
    bool val = false;
    mStream.read(reinterpret_cast<char *>(&val), sizeof(bool));
    return val;
}

inline int BinaryFile::ReadInt()
{
    int val = 0;
    mStream.read(reinterpret_cast<char *>(&val), sizeof(int));
    return val;
}

inline unsigned int BinaryFile::ReadUint()
{
    unsigned int val = 0;
    mStream.read(reinterpret_cast<char *>(&val), sizeof(unsigned int));
    return val;
}

inline float BinaryFile::ReadFloat()
{
    float val = 0.f;
    mStream.read(reinterpret_cast<char *>(&val), sizeof(float));
    return val;
}

inline double BinaryFile::ReadDouble()
{
    double val = 0.0;
    mStream.read(reinterpret_cast<char *>(&val), sizeof(double));
    return val;
}

inline void BinaryFile::WriteCstring(const char * str, unsigned int size)
{
    WriteUint(size);

    if(size > 0)
        mStream.write(str, size);
}

inline void BinaryFile::WriteString(const std::string & str)
{
    const unsigned int size = str.size();
    WriteUint(size);

    if(size > 0)
        mStream.write(str.c_str(), size);
}

inline void BinaryFile::WriteBool(bool val)
{
    mStream.write(reinterpret_cast<char *>(&val), sizeof(bool));
}

inline void BinaryFile::WriteInt(int val)
{
    mStream.write(reinterpret_cast<char *>(&val), sizeof(int));
}

inline void BinaryFile::WriteUint(unsigned int val)
{
    mStream.write(reinterpret_cast<char *>(&val), sizeof(unsigned int));
}

inline void BinaryFile::WriteFloat(float val)
{
    mStream.write(reinterpret_cast<char *>(&val), sizeof(float));
}

inline void BinaryFile::WriteDouble(double val)
{
    mStream.write(reinterpret_cast<char *>(&val), sizeof(double));
}

inline void BinaryFile::Close()
{
    mStream.close();
}

} // namespace utilities
} // namespace sgl