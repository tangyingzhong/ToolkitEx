///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// You can use it to do http or https post and get 
///</describe>
/// <date>2019/11/15</date>
///***********************************************************************
#ifndef LIBCURL_H
#define LIBCURL_H

#include "ILibCurl.h"

using namespace System;

namespace System
{
	namespace Network
	{
		class LibCurl:public ILibCurl
		{
		public:
			typedef CURLcode RetCode;
			typedef CURL* UrlHandle;

		public:
			// Construct the LibCurl
			LibCurl();

			// Detructe the LibCurl
			~LibCurl();

		private:
			// Forbid the copy LibCurl
			LibCurl(const LibCurl& other){	}

			// Forbid the assigment of LibCurl
			LibCurl& operator=(const LibCurl& other){	}

		public:
			// Init the curl
			static void InitCurl();

			// Destory the curl
			static void DestoryCurl();

			// Set head for url
			virtual HeadList SetRequestHead(String strHeadType = _T("Content-Type"),
				String strProtocol = _T("application/json"),
				String strEncodeType = _T("charset=UTF-8"));

			// Post the request by http
			virtual Boolean Post(TransPara& Para, Int32& iErrorCode, String& strErrorMessage);

			// Get the respoend by http
			virtual Boolean Get(TransPara& Para, Int32& iErrorCode,String& strErrorMessage);

			// Post the request by https (pCaPath==NULL : do not verify the certification on server)
			virtual Boolean Posts(TransPara& Para, String& strErrorMessage, const SByteArray pCaPath = NULL);

			// Get the respoend by https (pCaPath==NULL : do not verify the certification on server)
			virtual Boolean Gets(TransPara& Para, String& strErrorMessage, const SByteArray pCaPath = NULL);

		private:
			// Initialize the LibCurl
			Empty Initialize();

			// Destory the LibCurl
			Empty Destory();

			// Create Curl
			Boolean CreateUrL(UrlHandle& pHandle);

			// Destory Curl
			Empty DestoryUrL(UrlHandle pHandle);

			// Clear the head list
			Empty ClearRequeHeadHead(HeadList& hList);

			// Get error info
			String GetErrorInfo(RetCode eRetCode);

			// Change the string encode type
			String ChangeEncodeType(String strData);

			// Write data (Called by url inner)
			static size_t OnWriteData(void* buffer,
				size_t size,
				size_t nmemb,
				void* lpVoid);

			// Progerss call back for download and upload
			static int ProgressCallback(void* pUserData,
				double TotalToDownload,
				double NowDownloaded,
				double TotalToUpload,
				double NowUpload);

		private:
			// Get the disposed status
			inline Boolean GetDisposed() const
			{
				return m_bDisposed;
			}

			// Set the disposed status
			inline Empty SetDisposed(Boolean bDisposed)
			{
				m_bDisposed = bDisposed;
			}

		private:
			// Transfer paramenter
			TransPara m_TransPara;

			// Disposed status
			Boolean m_bDisposed;
		};
	}
}

#endif // LIBCURL_H