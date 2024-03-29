/*	StringUtils.h

MIT License

Copyright (c) 2018-2023 Fabian Herb

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef MOLECULAR_UTIL_STRINGUTILS_H
#define MOLECULAR_UTIL_STRINGUTILS_H

#include <string>
#include <vector>
#include <cstring>

namespace molecular
{
namespace util
{

/// Utility functions for string processing
namespace StringUtils
{
/// Wrapper for sscanf that ignores the current locale
int ScanF(const char* string, const char* format, ...);

/// Returns true if haystack ends with needle
bool EndsWith(const char* haystack, const char* needle);

/// Returns true if haystack ends with needle
bool EndsWith(const std::string& haystack, const std::string& needle);

bool Contains(const char* haystack, const char* needle);

/// Returns true if strings are equal
inline bool Equals(const char* a, const char* b) {return std::strcmp(a, b) == 0;}

/// Wrapper around strerror_s or strerror
std::string StrError(int errnum);

/// Reads entire storage (e.g. a file) and returns it as string
template<class TStorage>
std::string FromStorage(TStorage& storage)
{
	size_t size = storage.GetSize();
	std::vector<char> out;
	out.resize(size);
	storage.Read(out.data(), size);
	return std::string(out.begin(), out.end());
}

/// Wrapper around strncpy with automatic destination size determination
template<size_t size>
void Copy(const char* source, char (&dest)[size])
{
	strncpy(dest, source, size);
}

/// Wrapper around strncpy with automatic destination size determination
template<size_t size>
void Copy(const std::string& source, char (&dest)[size])
{
	strncpy(dest, source.c_str(), size);
}

/// Splits a string at the given delimiter and returns list of delimited elements
std::vector<std::string> Explode(const std::string& str, char delimiter);

/// Splits a string at the given delimiters and returns list of delimited elements
std::vector<std::string> Explode(const std::string& str, const char* delimiters);

/// File name without directory
std::string FileName(const std::string& path);

/// File name without directory and without extension
std::string FileNameWithoutExtension(const std::string& path);
}

}
} // namespace molecular

#endif // MOLECULAR_STRINGUTILS_H
