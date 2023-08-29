/*	ObjFileUtils.h

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

#ifndef MOLECULAR_UTIL_OBJFILEUTILS_H
#define MOLECULAR_UTIL_OBJFILEUTILS_H

#include <molecular/util/Range.h>
#include <molecular/util/Vector3.h>
#include <molecular/util/ObjFile.h>

namespace molecular
{
namespace util
{
namespace ObjFileUtils
{

using QuadRange = Range<std::vector<ObjFile::Quad>::const_iterator>;
using TriangleRange = Range<std::vector<ObjFile::Triangle>::const_iterator>;

/// Convert OBJ mesh data to data for three vertex buffers and one index buffer
/** Index and vertex data is appended to the output vectors. */
void ObjVertexGroupBuffers(
		const ObjFile& objFile,
		const ObjFile::VertexGroup& vg,
		std::vector<uint32_t>& unifiedIndices,
		std::vector<Vector3>& unifiedPositions,
		std::vector<Vector3>& unifiedNormals,
		std::vector<Vector2>& unifiedUvs);

}
}
}

#endif // MOLECULAR_UTIL_OBJFILEUTILS_H
