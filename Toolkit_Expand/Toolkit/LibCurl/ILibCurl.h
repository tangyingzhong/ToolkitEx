///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Lib curl's interfaces
///</describe>
/// <date>2019/11/19</date>
///***********************************************************************
#ifndef ILIBCURL_H
#define ILIBCURL_H

#include "Common/SystemType.h"
#include "BaseType/String.h"
#include "../../ShareLib/LibCurl/include/curl.h"
#include "../../ShareLib/LibCurl/include/easy.h"

using namespace System;
using namespace System::BasicType;

namespace System
{
	namespace Network
	{
		typedef int(*UploadProgressProc)(Object pUserData,
			Real TotalToUpload,
			Real NowUpload);

		typedef int(*DownLoadProgressProc)(Object pUserData,
			Real TotalToDown,
			Real NowDownload);

		struct TransPara
		{
			// Url
			std::string strRequestUrl;

			// Post para
			std::string strPostPara;

			// Respond data
			std::string strResponse;

			// Timeout
			UInt32 iSecondTimeout;

			// User data
			Object pUserData;

			// Upload progress call back func
			UploadProgressProc UploadFunc;

			// Download progress call back func
			DownLoadProgressProc DownloadFunc;

			TransPara()
			{
				Clear();
			}

			Empty Clear()
			{
				strRequestUrl = "";

				strPostPara = "";

				strResponse = "";

				iSecondTimeout = 0;

				pUserData = NULL;

				UploadFunc = NULL;

				DownloadFunc = NULL;
			}
		};

		class ILibCurl
		{
		public:
			typedef struct curl_slist* HeadList;

			// Destruct the curl
			virtual ~ILibCurl(){		}

		public:
			// Set head for url
			virtual HeadList SetRequestHead(String strHeadType = _T("Content-Type"),
				String strProtocol = _T("application/json"),
				String strEncodeType = _T("charset=UTF-8")) = 0;

			// Post the request by http
			virtual Boolean Post(TransPara& Para, Int32& iErrorCode, String& strErrorMessage) = 0;

			// Get the respoend by http
			virtual Boolean Get(TransPara& Para, Int32& iErrorCode, String& strErrorMessage) = 0;

			// Post the request by https (pCaPath==NULL : do not verify the certification on server)
			virtual Boolean Posts(TransPara& Para, String& strErrorMessage, const SByteArray pCaPath = NULL) = 0;

			// Get the respoend by https (pCaPath==NULL : do not verify the certification on server)
			virtual Boolean Gets(TransPara& Para, String& strErrorMessage, const SByteArray pCaPath = NULL) = 0;
		};
	}
}

#endif // ILIBCURL_H