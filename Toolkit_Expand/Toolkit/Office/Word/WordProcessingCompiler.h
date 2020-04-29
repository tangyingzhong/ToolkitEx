#ifndef __DOCXFACTORY_WORD_PROCESSING_COMPILER_H__
#define __DOCXFACTORY_WORD_PROCESSING_COMPILER_H__

#include <string>

namespace DocxFactory
{
	class WordProcessingCompiler
	{
	public:
		static WordProcessingCompiler& GetInstance();

		virtual ~WordProcessingCompiler();

		bool Compile(const std::string& p_srcFileName, const std::string& p_dstFileName);

		bool SetTempDir();

		bool SetTempDir(const std::string& p_dir);

		std::string GetWorkDir() const;

		std::string GetTempDir() const;

		std::string GetErrorMessage();

	private:
		WordProcessingCompiler();

		WordProcessingCompiler( const WordProcessingCompiler& p_other );

		WordProcessingCompiler& operator = ( const WordProcessingCompiler& p_other );

		// Get the ErrorMsg
		inline std::string GetErrorMsg() const
		{
			return m_strErrorMsg;
		}

		// Set the ErrorMsg
		inline void SetErrorMsg(std::string strErrorMsg)
		{
			m_strErrorMsg = strErrorMsg;
		}

	private:
		std::string m_strErrorMsg;
	};
};

#endif
