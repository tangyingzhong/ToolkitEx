///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Offer interfaces for http and ftp operation by curl
///</describe>
/// <date>2020/5/30</date>
///***********************************************************************
#ifndef ILIBCURL_H
#define ILIBCURL_H

#include "Tool/Toolkit.h"

typedef int(*UploadProgress)(Object pUserData,
	Real TotalToUpload,
	Real NowUpload);

typedef int(*DownLoadProgress)(Object pUserData,
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

	// User data
	Object pUserData;

	// Upload progress call back func
	UploadProgress UploadFunc;

	// Download progress call back func
	DownLoadProgress DownloadFunc;

	TransPara()
	{
		Clear();
	}

	None Set(std::string strReqUrl,
		std::string strReqData,
		std::string strResponseData,
		UploadProgress pUploadFunc,
		DownLoadProgress pDownloadFunc,
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

class ILibCurl
{
public:
	// Detructe the ILibCurl
	virtual ~ILibCurl() {	}

public:
	// Get the current libcurl version
	virtual std::string GetCurVersion() = 0;

	// Set time out
	virtual None SetTimeout(UInt32 iSeconds) = 0;

	// Set head for url
	virtual None SetRequestHead(std::string strHeadType = "Content-Type",
		std::string strProtocol = "application/json",
		std::string strEncodeType = "charset=UTF-8") = 0;

	// Post the request by http
	virtual Boolean Post(std::string strRequestUrl,
		std::string strRequestData,
		std::string& strResponseData,
		Object pUserData = NULL,
		UploadProgress pUploadFunc = NULL,
		DownLoadProgress pDownloadFunc = NULL) = 0;

	// Get the respoend by http
	virtual Boolean Get(std::string strRequestUrl,
		std::string strRequestData,
		std::string& strResponseData,
		Object pUserData = NULL,
		UploadProgress pUploadFunc = NULL,
		DownLoadProgress pDownloadFunc = NULL) = 0;

	// Post the request by https (pCaPath==NULL : do not verify the certification on server)
	virtual Boolean Posts(std::string strRequestUrl,
		std::string strRequestData,
		std::string& strResponseData,
		Object pUserData = NULL,
		UploadProgress pUploadFunc = NULL,
		DownLoadProgress pDownloadFunc = NULL,
		const SByteArray pCaPath = NULL) = 0;

	// Get the respoend by https (pCaPath==NULL : do not verify the certification on server)
	virtual Boolean Gets(std::string strRequestUrl,
		std::string strRequestData,
		std::string& strResponseData,
		Object pUserData = NULL,
		UploadProgress pUploadFunc = NULL,
		DownLoadProgress pDownloadFunc = NULL,
		const SByteArray pCaPath = NULL) = 0;

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
		Object pUserData = NULL) = 0;

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
		Object pUserData = NULL) = 0;

	// Get the error std::string
	virtual None GetErrorInfo(Int32& iErrorCode, std::string& strErrorMsg) = 0;
};

#endif // ILIBCURL_H
