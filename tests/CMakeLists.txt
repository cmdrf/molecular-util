add_executable(molecular-util-tests
	TestAxisAlignedBox.cpp
	TestCommandLineParser.cpp
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
	molecular::testbed
)

add_test(NAME molecular-util-tests COMMAND molecular-util-tests)
