///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Offering word's functions 
///</describe>
/// <date>2019/11/21</date>
///***********************************************************************
#ifndef IWORD_H
#define IWORD_H

#include "Tool/Common/SystemType.h"
#include "Tool/BaseType/String.h"

using namespace System;
using namespace System::BasicType;

namespace System
{
	namespace Office
	{
		class IWord
		{
		public:
			// Detructe the word
			virtual ~IWord(){	}

		public:
			// Load the doc
			virtual Boolean Load(String strDocFilePath) = 0;

			// Get the doc content(Doc size must <2G)
			virtual Boolean GetDoc(String& strContent) = 0;

			// Write the doc
			virtual Boolean WriteDoc(String strValue,
				String strTitleName = String(_T("")), 
				String strFiledName = String(_T(""))) = 0;

			// Write the doc
			virtual Boolean WriteDoc(Real dValue, 
				String strTitleName = String(_T("")),
				String strFiledName = String(_T(""))) = 0;

			// Save the doc
			virtual Boolean Save(String strDocFilePath) = 0;

			// Get the error message
			virtual String GetErrorMsg() = 0;
		};
	}
}

#endif // IWORD_H