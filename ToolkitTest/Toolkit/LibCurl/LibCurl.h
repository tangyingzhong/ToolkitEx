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
#include "curl.h"
#include "easy.h"

using namespace System;

namespace System
{
	namespace Network
	{
		struct TransPara
		{
			// Url
			std::string strRequestUrl;

			// Post para
			std::string strPostPara;

			// Respond data
			std::string strResponse;

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

			None Set(std::string strReqUrl,
				std::string strReqData,
				std::string strResponseData,
				UploadProgressProc pUploadFunc,
				DownLoadProgressProc pDownloadFunc,
				Object pUser)
			{
				strRequestUrl = strReqUrl;
				strPostPara = strReqData;
				strResponse = strResponseData;
				UploadFunc = pUploadFunc;
				DownloadFunc = pDownloadFunc;
				pUserData = pUser;
			}

			None Clear()
			{
				strRequestUrl = "";

				strPostPara = "";

				strResponse = "";

				pUserData = NULL;

				UploadFunc = NULL;

				DownloadFunc = NULL;
			}
		};

		class LibCurl:public ILibCurl
		{
		public:
			typedef struct curl_slist* HeadList;
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

			// Set time out
			virtual None SetTimeout(UInt32 iSeconds);

			// Set head for url
			virtual None SetRequestHead(String strHeadType = String(_T("Content-Type")),
				String strProtocol = String(_T("application/json")),
				String strEncodeType = String(_T("charset=UTF-8")));

			// Post the request by http
			virtual Boolean Post(std::string strRequestUrl,
				std::string strRequestData,
				std::string strResponseData,
				Object pUserData = NULL,
				UploadProgressProc pUploadFunc = NULL,
				DownLoadProgressProc pDownloadFunc = NULL);

			// Get the respoend by http
			virtual Boolean Get(std::string strRequestUrl,
				std::string strRequestData,
				std::string strResponseData,
				Object pUserData = NULL,
				UploadProgressProc pUploadFunc = NULL,
				DownLoadProgressProc pDownloadFunc = NULL);

			// Post the request by https (pCaPath==NULL : do not verify the certification on server)
			virtual Boolean Posts(std::string strRequestUrl,
				std::string strRequestData,
				std::string strResponseData,
				Object pUserData = NULL,
				UploadProgressProc pUploadFunc = NULL,
				DownLoadProgressProc pDownloadFunc = NULL,
				const SByteArray pCaPath = NULL);

			// Get the respoend by https (pCaPath==NULL : do not verify the certification on server)
			virtual Boolean Gets(std::string strRequestUrl,
				std::string strRequestData,
				std::string strResponseData,
				Object pUserData = NULL,
				UploadProgressProc pUploadFunc = NULL,
				DownLoadProgressProc pDownloadFunc = NULL,
				const SByteArray pCaPath = NULL);

			// Get the error string
			virtual None GetErrorInfo(Int32& iErrorCode, String& strErrorMsg);

		private:
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

			// Is can do the operation
			Boolean IsCanOperate();

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

			// Get the TimeoutS
			inline UInt32 GetTimeoutS() const
			{
				return m_iTimeoutS;
			}

			// Set the TimeoutS
			inline void SetTimeoutS(UInt32 iTimeoutS)
			{
				m_iTimeoutS = iTimeoutS;
			}

			// Get the HeadList
			inline HeadList GetHeadList() const
			{
				return m_pHeadList;
			}

			// Set the HeadList
			inline void SetHeadList(HeadList pHeadList)
			{
				m_pHeadList = pHeadList;
			}

		private:
			// Is curl initialized
			static Boolean m_bIsInit;

			// Transfer paramenter
			TransPara m_TransPara;

			// Head list
			HeadList m_pHeadList;
			
			// Timeout 
			UInt32 m_iTimeoutS;
		
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