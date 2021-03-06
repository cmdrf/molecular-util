cmake_minimum_required(VERSION 3.3)
project(molecular-util)

option(BUILD_TESTING "Build unit test runner executables" OFF)

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

if(APPLE)
	target_sources(molecular-util PRIVATE
		molecular/util/GcdTaskDispatcher.cpp
		molecular/util/GcdTaskDispatcher.h
	)
endif()

add_library(molecular::util ALIAS molecular-util)
target_include_directories(molecular-util PUBLIC .)
target_link_libraries(molecular-util PUBLIC Eigen3::Eigen Threads::Threads)

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
