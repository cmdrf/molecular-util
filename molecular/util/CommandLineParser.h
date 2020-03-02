/*	CommandLineParser.h

MIT License

Copyright (c) 2018-2020 Fabian Herb

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

#ifndef MOLECULAR_UTIL_COMMANDLINEPARSER_H
#define MOLECULAR_UTIL_COMMANDLINEPARSER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

namespace molecular
{
namespace util
{

/// Easy processing of argc and argv
/** Example:
@code
int main(int argc, char** argv)
{
	CommandLineParser cmd;
	CommandLineParser::PositionalArg<std::string> inFileName(cmd, "input file", "Input mesh to compile");
	CommandLineParser::PositionalArg<std::string> outFileName(cmd, "output file", "Output compiled mesh file");
	CommandLineParser::Flag prt(cmd, "prt", "Enable radiance transfer precomputation");
	CommandLineParser::Option<float> scale(cmd, "scale", "Mesh scale factor", 1.0);
	CommandLineParser::HelpFlag help(cmd);

	try
	{
		cmd.Parse(argc, argv);
	}
	catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		cmd.PrintHelp();
		return EXIT_FAILURE;
	}

	// Get value by dereferencing:
	std::cerr << "Input file: " << *inFileName;
}
@endcode
*/
class CommandLineParser
{
public:
	/// Parse command line arguments
	/** Throws on failure. */
	void Parse(int argc, char** argv);

	/// Print usage information
	/** Alternatively, add a HelpFlag. */
	void PrintHelp();

	class Arg;
	class OptionBase;
	class PositionalArgBase;
	class Flag;
	class HelpFlag;

	template<class T>
	class Option;

	template<class T>
	class PositionalArg;

private:
	std::unordered_map<std::string, OptionBase*> mOptions;
	std::vector<PositionalArgBase*> mPositionalArgs;
	std::string mProgramName;
};

class CommandLineParser::Arg
{
	friend class CommandLineParser;
public:
	Arg(const std::string& help);
	virtual ~Arg() = default;

	virtual void PrintHelp() = 0;

	operator bool() {return mPresent;}

protected:
	std::string mHelp;
	bool mPresent = false;
};

class CommandLineParser::OptionBase : public CommandLineParser::Arg
{
public:
	OptionBase(CommandLineParser& parser, const std::string& longOpt, const std::string& help);
	virtual void Parse(int& i, int argc, char** argv) = 0;
	void PrintHelp() override;

protected:
	std::string mLongOpt;
};

class CommandLineParser::PositionalArgBase : public CommandLineParser::Arg
{
public:
	PositionalArgBase(CommandLineParser& parser, const std::string& name, const std::string& help);
	virtual void SetValue(const std::string& arg) = 0;
	void PrintHelp() override;
	const std::string& GetName() {return mName;}

private:
	std::string mName;
};

/// Option without parameter
/** Example: "--enable-thing" */
class CommandLineParser::Flag : public CommandLineParser::OptionBase
{
public:
	Flag(CommandLineParser& parser, const std::string& longOpt, const std::string& help);
	void Parse(int& i, int argc, char** argv) override;
	void PrintHelp() override;
};

/// Displays help
class CommandLineParser::HelpFlag : public CommandLineParser::Flag
{
public:
	HelpFlag(CommandLineParser& parser);
	void Parse(int& i, int argc, char** argv) override;

private:
	CommandLineParser& mParser;
};


/// Command line option with parameter
/** Something like "--input-file foo.txt" */
template<class T>
class CommandLineParser::Option : public CommandLineParser::OptionBase
{
public:
	Option(CommandLineParser& parser, const std::string& longOpt, const std::string& help, T value = T()) :
	    OptionBase(parser, longOpt, help),
	    mValue(value)
	{

	}

	void Parse(int& i, int argc, char** argv) override
	{
		i++;
		if(i >= argc)
			throw std::runtime_error("Expected value after option");
		std::istringstream(argv[i]) >> mValue;
	}

	const T* operator->() const
	{
		return &mValue;
	}

	const T& operator*() const
	{
		return mValue;
	}

private:
	T mValue;
};

template<class T>
class CommandLineParser::PositionalArg : public CommandLineParser::PositionalArgBase
{
public:
	PositionalArg(CommandLineParser& parser, const std::string& name, const std::string& help, T value = T()) :
	    PositionalArgBase(parser, name, help),
	    mValue(value)
	{

	}

	void SetValue(const std::string& arg) override
	{
		std::istringstream iss(arg);
		iss >> mValue;
	}

	const T* operator->() const
	{
		return &mValue;
	}

	const T& operator*() const
	{
		return mValue;
	}

private:
	T mValue;
};

} // namespace util
} // namespace molecular

#endif // MOLECULAR_UTIL_COMMANDLINEPARSER_H
