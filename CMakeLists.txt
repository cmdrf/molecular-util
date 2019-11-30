cmake_minimum_required(VERSION 3.3)
project(molecular-util)

option(BUILD_TESTING "Build unit test runner executables" OFF)

add_library(molecular-util
	molecular/util/AxisAlignedBox.cpp
	molecular/util/AxisAlignedBox.h
	molecular/util/BufferInfo.h
	molecular/util/CharacterAnimation.cpp
	molecular/util/CharacterAnimation.h
	molecular/util/CommandLineParser.cpp
	molecular/util/CommandLineParser.h
	molecular/util/FileStreamStorage.cpp
	molecular/util/FileStreamStorage.h
	molecular/util/FloatToHalf.cpp
	molecular/util/FloatToHalf.h
	molecular/util/Hash.h
	molecular/util/Math.cpp
	molecular/util/Math.h
	molecular/util/Matrix4.h
	molecular/util/Matrix.h
	molecular/util/Mesh.h
	molecular/util/MeshUtils.cpp
	molecular/util/MeshUtils.h
	molecular/util/Quaternion.cpp
	molecular/util/Quaternion.h
	molecular/util/Parser.h
	molecular/util/Range.h
	molecular/util/SphericalHarmonics.cpp
	molecular/util/SphericalHarmonics.h
	molecular/util/StreamStorage.cpp
	molecular/util/StreamStorage.h
	molecular/util/StringUtils.cpp
	molecular/util/StringUtils.h
	molecular/util/TextStream.h
	molecular/util/Vector.h
	molecular/util/Vector3.h
	molecular/util/Vector4.h
)
add_library(molecular::util ALIAS molecular-util)
target_include_directories(molecular-util PUBLIC .)
target_link_libraries(molecular-util PUBLIC Eigen3::Eigen)

if(BUILD_TESTING)
	add_library(molecular-testbed
		molecular/testbed/TestsMain.cpp
		molecular/testbed/Matchers.cpp
		molecular/testbed/Matchers.h
	)
    add_library(molecular::testbed ALIAS molecular-testbed)
	target_include_directories(molecular-testbed PUBLIC 3rdparty .)
	target_link_libraries(molecular-testbed PUBLIC molecular::util)

	add_subdirectory(tests)
endif()
