#include <catch2/catch_test_macros.hpp>
#include <molecular/util/CommandLineParser.h>

using namespace molecular;
using namespace molecular::util;

TEST_CASE("Parsing basic command line arguments", "[CommandLineParser]")
{
	SECTION("Parsing valid arguments")
	{
		const char* argv[] = {
			"program_name",
			"input.txt",
			"output.txt",
			"--prt",
			"--scale",
			"2.5"
		};
		int argc = sizeof(argv) / sizeof(char*);

		CommandLineParser cmd;
		CommandLineParser::PositionalArg<std::string> inFileName(cmd, "input file", "Input mesh to compile");
		CommandLineParser::PositionalArg<std::string> outFileName(cmd, "output file", "Output compiled mesh file");
		CommandLineParser::Flag prt(cmd, "prt", "Enable radiance transfer precomputation");
		CommandLineParser::Option<float> scale(cmd, "scale", "Mesh scale factor", 1.0);
		CommandLineParser::HelpFlag help(cmd);

		REQUIRE_NOTHROW(cmd.Parse(argc, argv));

		REQUIRE(*inFileName == "input.txt");
		REQUIRE(*outFileName == "output.txt");
		REQUIRE(prt);
		REQUIRE(*scale == 2.5f);
	}

	SECTION("Parsing missing required arguments")
	{
		const char* argv[] = {
			"program_name",
			"--prt"
		};
		int argc = sizeof(argv) / sizeof(char*);

		CommandLineParser cmd;
		CommandLineParser::PositionalArg<std::string> inFileName(cmd, "input file", "Input mesh to compile");
		CommandLineParser::PositionalArg<std::string> outFileName(cmd, "output file", "Output compiled mesh file");
		CommandLineParser::Flag prt(cmd, "prt", "Enable radiance transfer precomputation");
		CommandLineParser::Option<float> scale(cmd, "scale", "Mesh scale factor", 1.0);
		CommandLineParser::HelpFlag help(cmd);

		REQUIRE_THROWS_AS(cmd.Parse(argc, argv), std::exception);
	}
}
