option(BUILD_TESTING "Build unit test runner executable" OFF)

if(NOT BUILD_TESTING)
	return()
endif()

add_executable(molecular-util-tests
	TestsMain.cpp
	Matchers.cpp
	Matchers.h

	TestAxisAlignedBox.cpp
	TestFloatToHalf.cpp
	TestHash.cpp
	TestMath.cpp
	TestMatrix3.cpp
	TestMatrix.cpp
	TestParser.cpp
	TestQuaternion.cpp
	TestSphericalHarmonics.cpp
	TestStringUtils.cpp
	TestVector.cpp
)

target_link_libraries(molecular-util-tests
	molecular::util
)
target_include_directories(molecular-util-tests PRIVATE ../3rdparty)
