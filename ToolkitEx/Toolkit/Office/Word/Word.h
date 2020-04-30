///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// You can use it to operate word without installing word on your computer
///</describe>
/// <date>2019/11/21</date>
///***********************************************************************
#ifndef WORD_H
#define WORD_H

#include "IWord.h"

namespace System
{
	namespace Office
	{
		class Word:public IWord
		{
		public:
			// Construct the Word
			Word();

			// Detructe the Word
			virtual ~Word();

		private:
			// Forbid the copy Word
			Word(const Word& other){	}

			// Forbid the assigment of Word
			Word& operator=(const Word& other){ return *this; }

		public:
			// Load the doc
			virtual Boolean Load(String strDocFilePath);

			// Get the doc content
			virtual Boolean GetDoc(String& strContent);

			// Write the doc
			virtual Boolean WriteDoc(String strValue,
				String strTitleName = String(_T("")),
				String strFiledName = String(_T("")));

			// Write the doc
			virtual Boolean WriteDoc(Real dValue,
				String strTitleName = String(_T("")),
				String strFiledName = String(_T("")));

			// Save the doc
			virtual Boolean Save(String strDocFilePath);

			// Get the error message
			virtual String GetErrorMsg();

		private:
			// Initialize the Word
			None Initialize();

			// Destory the Word
			None Destory();

			// Get new doc file path 
			String GetNewDocPath(String strDocFilePath);

			// Compile the doc file
			Boolean Compile(String strDocFilePath,String strDfwFilePath);

			// Close the doc
			None Close();

			// Delete imediate file
			None Clear();

		private:
			// Get the DocFilePath
			inline String GetDocFilePath() const
			{
				return m_strDocFilePath;
			}

			// Set the DocFilePath
			inline None SetDocFilePath(String strDocFilePath)
			{
				m_strDocFilePath = strDocFilePath;
			}

			// Get the ErrorMessage
			inline String GetErrorMessage() const
			{
				return m_strErrorMessage;
			}

			// Set the ErrorMessage
			inline None SetErrorMessage(String strErrorMessage)
			{
				m_strErrorMessage = strErrorMessage;
			}

			// Get the disposed status
			inline Boolean GetDisposed() const
			{
				return m_bDisposed;
			}

			// Set the disposed status
			inline None SetDisposed(Boolean bDisposed)
			{
				m_bDisposed = bDisposed;
			}

		private:
			// Doc file path
			String m_strDocFilePath;

			// Error message
			String m_strErrorMessage;

			// Disposed status
			Boolean m_bDisposed;
		};
	}
}

#endif // WORD_H