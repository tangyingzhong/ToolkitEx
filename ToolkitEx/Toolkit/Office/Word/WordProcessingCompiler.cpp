#include "WordProcessingCompiler.h"
#include "dfwc.h"
#include <stdexcept>

using namespace DocxFactory;

WordProcessingCompiler& WordProcessingCompiler::GetInstance()
{
	static WordProcessingCompiler s_instance;

	return s_instance;
}

WordProcessingCompiler::WordProcessingCompiler()
{

}

WordProcessingCompiler::~WordProcessingCompiler()
{

} 

std::string WordProcessingCompiler::GetErrorMessage()
{
	return GetErrorMsg();
}

bool WordProcessingCompiler::Compile(const std::string& p_srcFileName, const std::string& p_dstFileName)
{
	dfwc_compile( p_srcFileName.c_str(), p_dstFileName.c_str() );

	if (dfwc_getErrorFlag())
	{
		std::string strError = dfwc_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}	

	return true;
}

bool WordProcessingCompiler::SetTempDir()
{
	dfwc_setTempDir("");

	if (dfwc_getErrorFlag())
	{
		std::string strError = dfwc_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingCompiler::SetTempDir(const std::string& p_dir)
{
	dfwc_setTempDir( p_dir.c_str() );

	if (dfwc_getErrorFlag())
	{
		std::string strError = dfwc_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

std::string WordProcessingCompiler::GetWorkDir() const
{
	return dfwc_getWorkDir();
}

std::string WordProcessingCompiler::GetTempDir() const
{
	return dfwc_getTempDir();
}