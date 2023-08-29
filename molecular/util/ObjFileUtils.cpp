/*	ObjFileUtils.cpp

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

#include "ObjFileUtils.h"

#include <molecular/util/MeshUtils.h>

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
		std::vector<Vector2>& unifiedUvs)
{
	unsigned int endQuad = vg.firstQuad + vg.numQuads;
	unsigned int endTriangle = vg.firstTriangle + vg.numTriangles;
	assert(endQuad <= objFile.GetQuads().size());
	assert(endTriangle <= objFile.GetTriangles().size());
	auto quadsBegin = objFile.GetQuads().begin();
	auto trianglesBegin = objFile.GetTriangles().begin();
	QuadRange quads(quadsBegin + vg.firstQuad, quadsBegin + endQuad);
	TriangleRange triangles(trianglesBegin + vg.firstTriangle, trianglesBegin + endTriangle);

	std::vector<uint32_t> positionIndices, normalIndices, uvIndices;

	{
		std::vector<uint32_t> quadPositionIndices;
		for(auto& quad: quads)
			quadPositionIndices.insert(quadPositionIndices.end(), quad.vertexIndices.begin(), quad.vertexIndices.end());
		positionIndices.resize(quadPositionIndices.size() / 2 * 3);
		MeshUtils::QuadToTriangleIndices(vg.numQuads, quadPositionIndices.data(), positionIndices.data());
	}

	if(vg.hasNormals)
	{
		std::vector<uint32_t> quadNormalIndices;
		for(auto& quad: quads)
			quadNormalIndices.insert(quadNormalIndices.end(), quad.normalIndices.begin(), quad.normalIndices.end());
		normalIndices.resize(quadNormalIndices.size() / 2 * 3);
		MeshUtils::QuadToTriangleIndices(vg.numQuads, quadNormalIndices.data(), normalIndices.data());
	}

	if(vg.hasTexCoords)
	{
		std::vector<uint32_t> quadUvIndices;
		for(auto& quad: quads)
			quadUvIndices.insert(quadUvIndices.end(), quad.texCoordIndices.begin(), quad.texCoordIndices.end());
		uvIndices.resize(quadUvIndices.size() / 2 * 3);
		MeshUtils::QuadToTriangleIndices(vg.numQuads, quadUvIndices.data(), uvIndices.data());
	}

	for(auto& tri: triangles)
	{
		positionIndices.insert(positionIndices.end(), tri.vertexIndices.begin(), tri.vertexIndices.end());
		if(vg.hasNormals)
			normalIndices.insert(normalIndices.end(), tri.normalIndices.begin(), tri.normalIndices.end());
		if(vg.hasTexCoords)
			uvIndices.insert(uvIndices.end(), tri.texCoordIndices.begin(), tri.texCoordIndices.end());
	}

	const uint32_t* normalIndexData = nullptr;
	const Vector3* normalVertexData = nullptr;
	if(vg.hasNormals)
	{
		assert(positionIndices.size() == normalIndices.size());
		normalIndexData = normalIndices.data();
		normalVertexData = objFile.GetNormals().data();
	}

	const uint32_t* uvIndexData = nullptr;
	const Vector2* uvVertexData = nullptr;
	if(vg.hasTexCoords)
	{
		assert(positionIndices.size() == uvIndices.size());
		uvIndexData = uvIndices.data();
		uvVertexData = objFile.GetTexCoords().data();
	}

	MeshUtils::SeparateToUnifiedIndices(
				positionIndices.size(),
				positionIndices.data(),
				normalIndexData,
				uvIndexData,
				objFile.GetVertices().size(), objFile.GetVertices().data(),
				objFile.GetNormals().size(), normalVertexData,
				objFile.GetTexCoords().size(), uvVertexData,
				unifiedIndices,
				unifiedPositions,
				unifiedNormals,
				unifiedUvs);
}

}
} // namespace util
} // namespace molecular
