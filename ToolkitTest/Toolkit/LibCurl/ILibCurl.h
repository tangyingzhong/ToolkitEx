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

#include "Tool/Common/SystemType.h"
#include "Tool/BaseType/String.h"
#include "curl.h"
#include "easy.h"

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

		class ILibCurl
		{
		public:
			typedef struct curl_slist* HeadList;

			// Destruct the curl
			virtual ~ILibCurl(){		}

		public:
			// Get the current libcurl version
			virtual String GetCurVersion() = 0;

			// Set time out
			virtual None SetTimeout(UInt32 iSeconds) = 0;

			// Set head for url
			virtual HeadList SetRequestHead(String strHeadType = String(_T("Content-Type")),
				String strProtocol = String(_T("application/json")),
				String strEncodeType = String(_T("charset=UTF-8"))) = 0;

			// Post the request by http
			virtual Boolean Post(std::string strRequestUrl,
				std::string strRequestData,
				std::string strResponseData,
				Object pUserData =NULL,
				UploadProgressProc pUploadFunc = NULL,
				DownLoadProgressProc pDownloadFunc = NULL) = 0;

			// Get the respoend by http
			virtual Boolean Get(std::string strRequestUrl,
				std::string strRequestData,
				std::string strResponseData,
				Object pUserData = NULL,
				UploadProgressProc pUploadFunc = NULL,
				DownLoadProgressProc pDownloadFunc = NULL) = 0;

			// Post the request by https (pCaPath==NULL : do not verify the certification on server)
			virtual Boolean Posts(std::string strRequestUrl,
				std::string strRequestData,
				std::string strResponseData,
				Object pUserData = NULL,
				UploadProgressProc pUploadFunc = NULL,
				DownLoadProgressProc pDownloadFunc = NULL,
				const SByteArray pCaPath = NULL) = 0;

			// Get the respoend by https (pCaPath==NULL : do not verify the certification on server)
			virtual Boolean Gets(std::string strRequestUrl,
				std::string strRequestData,
				std::string strResponseData,
				Object pUserData = NULL,
				UploadProgressProc pUploadFunc = NULL,
				DownLoadProgressProc pDownloadFunc = NULL,
				const SByteArray pCaPath = NULL) = 0;

			// Get the error string
			virtual None GetErrorInfo(Int32& iErrorCode, String& strErrorMsg) = 0;
		};
	}
}

#endif // ILIBCURL_H