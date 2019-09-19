cmake_minimum_required(VERSION 3.3)
project(molecular-util)

add_library(molecular-util
	molecular/util/AxisAlignedBox.h
	molecular/util/CommandLineParser.cpp
	molecular/util/CommandLineParser.h
	molecular/util/FileStreamStorage.cpp
	molecular/util/FileStreamStorage.h
	molecular/util/FloatToHalf.cpp
	molecular/util/FloatToHalf.h
	molecular/util/Hash.h
	molecular/util/Math.h
	molecular/util/Matrix4.h
	molecular/util/Matrix.h
	molecular/util/Mesh.h
	molecular/util/MeshUtils.cpp
	molecular/util/MeshUtils.h
	molecular/util/Range.h
	molecular/util/SphericalHarmonics.cpp
	molecular/util/SphericalHarmonics.h
	molecular/util/StreamStorage.cpp
	molecular/util/StreamStorage.h
	molecular/util/StringUtils.cpp
	molecular/util/StringUtils.h
	molecular/util/TextStream.h
	molecular/util/Vector3.h
	molecular/util/Vector4.h
	molecular/util/Vector.h
)
add_library(molecular::util ALIAS molecular-util)
target_include_directories(molecular-util PUBLIC .)
