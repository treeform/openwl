#ifndef OPENWL_UNICODESTUFF_H
#define OPENWL_UNICODESTUFF_H

#include <boost/locale/encoding_utf.hpp>
#include <string>

using boost::locale::conv::utf_to_utf;

static std::wstring utf8_to_wstring(const std::string& str)
{
    return utf_to_utf<wchar_t>(str.c_str(), str.c_str() + str.size());
}

static std::string wstring_to_utf8(const std::wstring& str)
{
    return utf_to_utf<char>(str.c_str(), str.c_str() + str.size());
}

#endif //OPENWL_UNICODESTUFF_H
