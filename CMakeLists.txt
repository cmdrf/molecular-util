cmake_minimum_required(VERSION 3.3)
project(molecular-util)

option(BUILD_TESTING "Build unit test runner executables" OFF)

find_package(Threads REQUIRED)

find_package(Eigen3)
if(NOT Eigen3_FOUND)
	include(ExternalProject)
	set(EIGEN_PREFIX ${CMAKE_BINARY_DIR}/eigen)
	ExternalProject_Add(external_eigen
		PREFIX ${EIGEN_PREFIX}
		URL https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.bz2
		URL_MD5 132dde48fe2b563211675626d29f1707
		CONFIGURE_COMMAND ""
		BUILD_COMMAND ""
		INSTALL_COMMAND ""
	)
	set_target_properties(external_eigen PROPERTIES EXCLUDE_FROM_ALL TRUE)
	add_library(eigen INTERFACE)
	target_include_directories(eigen INTERFACE SYSTEM ${EIGEN_PREFIX}/src/external_eigen/)
	add_dependencies(eigen external_eigen)
	add_library(Eigen3::Eigen ALIAS eigen)
endif()

add_library(molecular-util
	molecular/util/AtomicCounter.h
	molecular/util/AxisAlignedBox.cpp
	molecular/util/AxisAlignedBox.h
	molecular/util/Blob.h
	molecular/util/BufferInfo.h
	molecular/util/CharacterAnimation.cpp
	molecular/util/CharacterAnimation.h
	molecular/util/CommandLineParser.cpp
	molecular/util/CommandLineParser.h
	molecular/util/DdsFile.cpp
	molecular/util/DdsFile.h
	molecular/util/FileStreamStorage.cpp
	molecular/util/FileStreamStorage.h
	molecular/util/FloatToHalf.cpp
	molecular/util/FloatToHalf.h
	molecular/util/GlConstants.h
	molecular/util/Hash.h
	molecular/util/HostStream.h
	molecular/util/KtxFile.cpp
	molecular/util/KtxFile.h
	molecular/util/LittleEndianStream.h
	molecular/util/Math.cpp
	molecular/util/Math.h
	molecular/util/Matrix4.h
	molecular/util/Matrix.h
	molecular/util/MemoryStreamStorage.cpp
	molecular/util/MemoryStreamStorage.h
	molecular/util/Mesh.h
	molecular/util/MeshUtils.cpp
	molecular/util/MeshUtils.h
	molecular/util/NonCopyable.h
	molecular/util/ObjFile.cpp
	molecular/util/ObjFile.h
	molecular/util/ObjFileUtils.cpp
	molecular/util/ObjFileUtils.h
	molecular/util/Parser.h
	molecular/util/PixelFormat.cpp
	molecular/util/PixelFormat.h
	molecular/util/Quaternion.cpp
	molecular/util/Quaternion.h
	molecular/util/Range.h
	molecular/util/ReadStream.cpp
	molecular/util/ReadStream.h
	molecular/util/SphericalHarmonics.cpp
	molecular/util/SphericalHarmonics.h
	molecular/util/StdTaskQueue.cpp
	molecular/util/StdTaskQueue.h
	molecular/util/StdThread.h
	molecular/util/StreamStorage.cpp
	molecular/util/StreamStorage.h
	molecular/util/StringUtils.cpp
	molecular/util/StringUtils.h
	molecular/util/Task.h
	molecular/util/TaskDispatcher.h
	molecular/util/TextStream.h
	molecular/util/Vector.h
	molecular/util/Vector3.h
	molecular/util/Vector4.h
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
	target_sources(molecular-util PRIVATE
		molecular/util/GcdTaskDispatcher.cpp
		molecular/util/GcdTaskDispatcher.h
	)
endif()

add_library(molecular::util ALIAS molecular-util)
target_include_directories(molecular-util PUBLIC .)
target_link_libraries(molecular-util PUBLIC Eigen3::Eigen Threads::Threads)

if(BUILD_TESTING)
	include(CTest)

	add_library(molecular-testbed
		molecular/testbed/Matchers.cpp
		molecular/testbed/Matchers.h
		3rdparty/catch_amalgamated.cpp
	)
    add_library(molecular::testbed ALIAS molecular-testbed)
	target_include_directories(molecular-testbed PUBLIC
		3rdparty
		.
		molecular/testbed/include
	)
	target_link_libraries(molecular-testbed PUBLIC molecular::util)

	add_subdirectory(tests)
endif()
