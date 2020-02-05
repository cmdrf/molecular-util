/*	CommandLineParser.cpp

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

#include "CommandLineParser.h"
#include <iostream>

namespace molecular
{
namespace util
{

void CommandLineParser::Parse(int argc, char** argv)
{
	for(int i = 1; i < argc; ++i)
	{
		std::string arg(argv[i]);
		if(argv[i][0] == '-')
		{
			auto it = mOptions.find(arg);
			if(it == mOptions.end())
				throw std::runtime_error("Unknown option '" + arg + "'");
			it->second->Parse(i, argc, argv);
			it->second->mPresent = true;
		}
		else if(mCurrentPositionalArg < mPositionalArgs.size())
		{
			auto& posArg = mPositionalArgs.at(mCurrentPositionalArg);
			posArg->SetValue(arg);
			posArg->mPresent = true;
			mCurrentPositionalArg++;
		}
		else
		{
			throw std::runtime_error("Too many positional arguments");
		}
	}

}

void CommandLineParser::PrintHelp(const char* programName)
{
	std::cerr << "Usage: " << programName;
	if(!mOptions.empty())
		std::cerr << " <options>";
	for(auto& arg: mPositionalArgs)
	{
		std::cerr << " <" << arg->GetName() << '>';
	}
	std::cerr << '\n';
	if(!mPositionalArgs.empty())
	{
		std::cerr << "\nPositional arguments:\n";
		for(auto& arg: mPositionalArgs)
		{
			std::cerr << '\t';
			arg->PrintHelp();
		}
	}
	if(!mOptions.empty())
	{
		std::cerr << "\nOptions:\n";
		for(auto& arg: mOptions)
		{
			std::cerr << '\t';
			arg.second->PrintHelp();
		}
	}
	std::cerr << '\n';
}

CommandLineParser::Arg::Arg(const std::string& help) :
    mHelp(help)
{

}

CommandLineParser::OptionBase::OptionBase(CommandLineParser& parser, const std::string& longOpt, const std::string& help) :
    Arg(help),
    mLongOpt("--" + longOpt)
{
	parser.mOptions[mLongOpt] = this;
}

void CommandLineParser::OptionBase::PrintHelp()
{
	std::cerr << mLongOpt << " <value>\t" << mHelp << std::endl;
}

CommandLineParser::PositionalArgBase::PositionalArgBase(CommandLineParser& parser, const std::string& name, const std::string& help) :
    Arg(help),
    mName(name)
{
	parser.mPositionalArgs.push_back(this);
}

void CommandLineParser::PositionalArgBase::PrintHelp()
{
	std::cerr << "<" << mName << ">\t" << mHelp << std::endl;
}

CommandLineParser::Flag::Flag(CommandLineParser& parser, const std::string& longOpt, const std::string& help) :
    OptionBase(parser, longOpt, help)
{
}

void CommandLineParser::Flag::Parse(int& /*i*/, int /*argc*/, char** /*argv*/)
{
	// Flags don't have additional parameters to parse
}

void CommandLineParser::Flag::PrintHelp()
{
	std::cerr << mLongOpt << '\t' << mHelp << std::endl;
}

}
} // namespace molecular
