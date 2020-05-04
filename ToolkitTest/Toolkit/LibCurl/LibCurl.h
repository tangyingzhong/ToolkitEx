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
			LibCurl& operator=(const LibCurl& other){ return *this; }

		public:
			// Init the curl
			static None InitCurl();

			// Destory the curl
			static None DestoryCurl();

		public:
			// Get the current libcurl version
			virtual String GetCurVersion();

			// Set head for url
			virtual HeadList SetRequestHead(String strHeadType = String(_T("Content-Type")),
				String strProtocol = String(_T("application/json")),
				String strEncodeType = String(_T("charset=UTF-8")));

			// Post the request by http
			virtual Boolean Post(TransPara& Para, Int32& iErrorCode, String& strErrorMessage);

			// Get the respoend by http
			virtual Boolean Get(TransPara& Para, Int32& iErrorCode,String& strErrorMessage);

			// Post the request by https (pCaPath==NULL : do not verify the certification on server)
			virtual Boolean Posts(TransPara& Para, String& strErrorMessage, const SByteArray pCaPath = NULL);

			// Get the respoend by https (pCaPath==NULL : do not verify the certification on server)
			virtual Boolean Gets(TransPara& Para, String& strErrorMessage, const SByteArray pCaPath = NULL);

			// Get the error string
			virtual None GetErrorInfo(Int32& iErrorCode, String& strErrorMsg);

		private:
			// Initialize the LibCurl
			None Initialize();

			// Destory the LibCurl
			None Destory();

			// Create Curl
			Boolean CreateUrL(UrlHandle& pHandle);

			// Destory Curl
			None DestoryUrL(UrlHandle pHandle);

			// Clear the head list
			None ClearRequeHeadHead(HeadList& hList);

			// Get error info
			String GetCurlErrorInfo(RetCode eRetCode);

			// Set error info
			None SetErrorInfo(RetCode eRetCode,String strErrorMsg);

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
			inline None SetDisposed(Boolean bDisposed)
			{
				m_bDisposed = bDisposed;
			}

			// Get the IsInit
			inline static Boolean GetIsInit()
			{
				return m_bIsInit;
			}

			// Set the IsInit
			inline static void SetIsInit(Boolean bIsInit)
			{
				m_bIsInit = bIsInit;
			}

			// Get the ErrorCode
			inline Int32 GetErrorCode() const
			{
				return m_iErrorCode;
			}

			// Set the ErrorCode
			inline void SetErrorCode(Int32 iErrorCode)
			{
				m_iErrorCode = iErrorCode;
			}

			// Get the ErrorMsg
			inline String GetErrorMsg() const
			{
				return m_strErrorMsg;
			}

			// Set the ErrorMsg
			inline void SetErrorMsg(String strErrorMsg)
			{
				m_strErrorMsg = strErrorMsg;
			}

		private:
			// Is curl initialized
			static Boolean m_bIsInit;

			// Transfer paramenter
			TransPara m_TransPara;

			// Error code
			Int32 m_iErrorCode;
			
			// Error message
			String m_strErrorMsg;
			
			// Disposed status
			Boolean m_bDisposed;
		};
	}
}

#endif // LIBCURL_H