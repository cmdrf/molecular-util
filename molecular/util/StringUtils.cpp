/*	StringUtils.cpp

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

#include "StringUtils.h"

#include <cstdarg>
#include <cstdio>
#include <cstring>

#ifndef _MSC_VER
#include <libgen.h>
#endif

#if __APPLE__
#include <xlocale.h>
#endif

namespace molecular
{
namespace util
{

namespace StringUtils
{

int ScanF(const char* string, const char* format, ...)
{
	va_list args;
	va_start(args, format);
#if __APPLE__
	int result = vsscanf_l(string, 0, format, args);
#else
	int result = vsscanf(string, format, args);
#endif
	va_end(args);
	return result;
}

bool EndsWith(const char* haystack, const char* needle)
{
	size_t haystackLength = strlen(haystack);
	size_t needleLength = strlen(needle);
	if(needleLength > haystackLength)
		return false;

	return strncmp(haystack + (haystackLength - needleLength), needle, needleLength) == 0;
}

bool EndsWith(const std::string& haystack, const std::string& needle)
{
	size_t haystackLength = haystack.length();
	size_t needleLength = needle.length();
	if(needleLength > haystackLength)
		return false;
	return !haystack.compare(haystackLength - needleLength, needleLength, needle);
}

bool Contains(const char* haystack, const char* needle)
{
	return strstr(haystack, needle);
}

std::string StrError(int errnum)
{
#ifdef __STDC_LIB_EXT1__
	char buffer[256] = {0};
	strerror_s(buffer, errnum);
	return buffer;
#else
	return strerror(errnum);
#endif
}

template<class T>
std::vector<std::string> ExplodeImpl(const std::string& str, T delimiter)
{
	std::vector<std::string> output;
	size_t currentBegin = 0;
	while(true)
	{
		size_t currentEnd = str.find_first_of(delimiter, currentBegin);
		if(currentEnd == std::string::npos)
		{
			output.push_back(str.substr(currentBegin));
			break;
		}
		else
			output.push_back(str.substr(currentBegin, currentEnd - currentBegin));
		currentBegin = currentEnd + 1;
	}
	return output;
}

std::vector<std::string> Explode(const std::string& str, char delimiter)
{
	return ExplodeImpl(str, delimiter);
}

std::vector<std::string> Explode(const std::string& str, const char* delimiters)
{
	return ExplodeImpl(str, delimiters);
}

std::string FileName(const std::string& path)
{
	auto lastSlash = path.find_last_of("/\\");
	if(lastSlash == std::string::npos)
		return path;
	else
		return path.substr(lastSlash + 1);
}

std::string FileNameWithoutExtension(const std::string& path)
{
	auto filename = FileName(path);
	auto firstDot = filename.find_first_of('.');
	if(firstDot == std::string::npos)
		return filename;
	else
		return filename.substr(0, firstDot);
}

}
}
} // namespace molecular
