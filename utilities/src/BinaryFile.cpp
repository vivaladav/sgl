#include "sgl/utilities/BinaryFile.h"

namespace sgl
{
namespace utilities
{

BinaryFile::BinaryFile(const std::string & path, OpenMode mode, bool truncate)
{
    using namespace std;

    auto flags = ios::binary;

    if(mode == OPEN_INPUT)
        flags |= ios::in;
    else
        flags |= ios::out;

    if(truncate)
        flags |= ios::trunc;

    mStream.open(path, flags);
}

BinaryFile::~BinaryFile()
{
    Close();
}

} // namespace utilities
} // namespace sgl