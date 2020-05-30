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

class LibCurl :public ILibCurl
{
public:
	typedef struct curl_slist* HeadList;
	typedef CURLcode RetCode;
	typedef CURL* UrlHandle;
	struct CurlRun
	{
		CurlRun()
		{
			LibCurl::InitCurl();
		}

		~CurlRun()
		{
			LibCurl::DestoryCurl();
		}
	};

public:
	// Construct the LibCurl
	LibCurl();

	// Detructe the LibCurl
	~LibCurl();

private:
	// Forbid the copy LibCurl
	LibCurl(const LibCurl& other) {	}

	// Forbid the assigment of LibCurl
	LibCurl& operator=(const LibCurl& other) { return *this; }

public:
	// Init the curl
	static None InitCurl();

	// Destory the curl
	static None DestoryCurl();

public:
	// Get the current libcurl version
	virtual std::string GetCurVersion();

	// Set time out
	virtual None SetTimeout(UInt32 iSeconds);

	// Set head for url
	virtual None SetRequestHead(std::string strHeadType = "Content-Type",
		std::string strProtocol = "application/json",
		std::string strEncodeType = "charset=UTF-8");

	// Post the request by http
	virtual Boolean Post(std::string strRequestUrl,
		std::string strRequestData,
		std::string& strResponseData,
		Object pUserData = NULL,
		UploadProgress pUploadFunc = NULL,
		DownLoadProgress pDownloadFunc = NULL);

	// Get the respoend by http
	virtual Boolean Get(std::string strRequestUrl,
		std::string strRequestData,
		std::string& strResponseData,
		Object pUserData = NULL,
		UploadProgress pUploadFunc = NULL,
		DownLoadProgress pDownloadFunc = NULL);

	// Post the request by https (pCaPath==NULL : do not verify the certification on server)
	virtual Boolean Posts(std::string strRequestUrl,
		std::string strRequestData,
		std::string& strResponseData,
		Object pUserData = NULL,
		UploadProgress pUploadFunc = NULL,
		DownLoadProgress pDownloadFunc = NULL,
		const SByteArray pCaPath = NULL);

	// Get the respoend by https (pCaPath==NULL : do not verify the certification on server)
	virtual Boolean Gets(std::string strRequestUrl,
		std::string strRequestData,
		std::string& strResponseData,
		Object pUserData = NULL,
		UploadProgress pUploadFunc = NULL,
		DownLoadProgress pDownloadFunc = NULL,
		const SByteArray pCaPath = NULL);

	// Ftp upload (strRemoteFilePath: ftp://127.0.0.1/aa.txt)
	virtual Boolean FtpUpload(const std::string strRemoteFilePath,
		const std::string strLocalFilePath,
		const std::string strUserName,
		const std::string strPassword,
		const std::string strPortNo = "21",	
		UploadProgress pUploadFunc = NULL,
		DownLoadProgress pDownloadFunc = NULL,
		long TimeoutS = 60,
		Int32 iTryCount = 3,
		Object pUserData = NULL);

	// Ftp download (strRemoteFilePath: ftp://127.0.0.1/aa.txt)
	virtual Boolean FtpDownload(const std::string strRemoteFilePath,
		const std::string strLocalFilePath,
		const std::string strUserName,
		const std::string strPassword,
		const std::string strPortNo = "21",	
		UploadProgress pUploadFunc = NULL,
		DownLoadProgress pDownloadFunc = NULL,
		long TimeoutS = 60,
		Int32 iTryCount = 3,
		Object pUserData = NULL);

	// Get the error std::string
	virtual None GetErrorInfo(Int32& iErrorCode, std::string& strErrorMsg);

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
	std::string GetCurlErrorInfo(RetCode eRetCode);

	// Set error info
	None SetErrorInfo(RetCode eRetCode, std::string strErrorMsg);

	// Is can do the operation
	Boolean IsCanOperate();

private:
	// Get content length
	static size_t GetContentLength(Object pHeader,
		size_t iHeadSize,
		size_t iMem,
		Object pStream);

	// Read data (Called by url inner)
	static size_t OnReadData(void* buffer,
		size_t size,
		size_t nmemb,
		void* lpVoid);

	// Write data (Called by url inner)
	static size_t OnWriteFileData(void* buffer,
		size_t size,
		size_t nmemb,
		void* lpVoid);

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
	inline std::string GetErrorMsg() const
	{
		return m_strErrorMsg;
	}

	// Set the ErrorMsg
	inline void SetErrorMsg(std::string strErrorMsg)
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
	
	// Get the UploadTotalSize
	inline Real GetUploadTotalSize() const
	{
		return m_dUploadTotalSize;
	}

	// Set the UploadTotalSize
	inline void SetUploadTotalSize(Real dUploadTotalSize)
	{
		m_dUploadTotalSize = dUploadTotalSize;
	}

	// Get the IsFtpUpload
	inline Boolean GetIsFtpUpload() const
	{
		return m_bIsFtpUpload;
	}

	// Set the IsFtpUpload
	inline void SetIsFtpUpload(Boolean bIsFtpUpload)
	{
		m_bIsFtpUpload = bIsFtpUpload;
	}

private:
	// Is curl initialized
	static Boolean m_bIsInit;

	// Run the curl
	static CurlRun* m_pCurlRun;

	// Transfer paramenter
	TransPara m_TransPara;

	// Is Ftp upload
	Boolean m_bIsFtpUpload;

	// Total size of uploading
	Real m_dUploadTotalSize;
	
	// Head list
	HeadList m_pHeadList;

	// Timeout 
	UInt32 m_iTimeoutS;

	// Error code
	Int32 m_iErrorCode;

	// Error message
	std::string m_strErrorMsg;

	// Disposed status
	Boolean m_bDisposed;
};

#endif // LIBCURL_H