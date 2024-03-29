/*	FloatToHalf.h

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

#ifndef MOLECULAR_FLOATTOHALF_H
#define MOLECULAR_FLOATTOHALF_H

#include <cstdint>
#include <cstring>

namespace molecular
{
namespace util
{

#ifdef __ARM_FP16_FORMAT_IEEE
// TODO: Might also be available on x86 through AVX512 or emulation

class FloatToHalf
{
public:
	uint16_t Convert(float input) const
	{
		__fp16 f = input;
		uint16_t out;
		std::memcpy(&out, &f, 2);
		return out;
	}
};

#else

/// Converts 32 bit to 16 bit floating point numbers
/** Fast Half Float Conversions, Jeroen van der Zijp, November 2008
	ftp://ftp.fox-toolkit.org/pub/fasthalffloatconversion.pdf */
class FloatToHalf
{
public:
	FloatToHalf();

	uint16_t Convert(float input) const
	{
		uint32_t f = 0;
		std::memcpy(&f, &input, 4);

		return mBaseTable[(f >> 23) & 0x1ff] + ((f & 0x007fffff) >> mShiftTable[(f >> 23) & 0x1ff]);
	}

private:
	uint16_t mBaseTable[512];
	int8_t mShiftTable[512];
};

#endif // __ARM_FP16_FORMAT_IEEE

}
}

#endif // MOLECULAR_FLOATTOHALF_H
