#include "Tool/Encoding/ANSI.h"
#include "Tool/Encoding/UTF8.h"
#include "Tool/Encoding/Unicode.h"
#include "LibCurl.h"

using namespace System::Encoding;
using namespace System::Network;

// Construct the LibCurl
LibCurl::LibCurl() :m_bDisposed(false)
{
	Initialize();
}

// Detructe the LibCurl
LibCurl::~LibCurl()
{
	Destory();
}

// Initialize the LibCurl
None LibCurl::Initialize()
{

}

// Destory the LibCurl
None LibCurl::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);
	}
}

// Init the curl
void LibCurl::InitCurl()
{
	curl_global_init(CURL_GLOBAL_ALL);
}

// Destory the curl
void LibCurl::DestoryCurl()
{
	curl_global_cleanup();
}

// Create Curl
Boolean LibCurl::CreateUrL(UrlHandle& pHandle)
{
	pHandle = curl_easy_init();
	if (pHandle == NULL)
	{
		return false;
	}

	return true;
}

// Destory Curl
None LibCurl::DestoryUrL(UrlHandle pHandle)
{
	if (pHandle)
	{
		curl_easy_cleanup(pHandle);

		pHandle = NULL;
	}
}

// Write data (Called by url inner)
size_t LibCurl::OnWriteData(void* buffer,
	size_t size,
	size_t nmemb,
	void* lpVoid)
{
	LibCurl* pThis = (LibCurl*)lpVoid;

	size_t iTotalSize = size * nmemb;

	Array<SByte> RespondData(iTotalSize);

	Array<SByte>::Copy((SByteArray)buffer, iTotalSize, RespondData.Data(), RespondData.Size());

	std::string strData = RespondData.Data();

	pThis->m_TransPara.strResponse.append(strData);

	return nmemb;
}

// Progerss call back for download and upload
int LibCurl::ProgressCallback(void* pUserData,
	double TotalToDownload,
	double NowDownloaded,
	double TotalToUpload,
	double NowUpload)
{
	LibCurl* pThis = (LibCurl*)pUserData;

	if (pThis == NULL)
	{
		return -1;
	}

	if (pThis->m_TransPara.UploadFunc)
	{
		return pThis->m_TransPara.UploadFunc(pThis->m_TransPara.pUserData, TotalToUpload, NowUpload);
	}

	if (pThis->m_TransPara.DownloadFunc)
	{
		return pThis->m_TransPara.DownloadFunc(pThis->m_TransPara.pUserData, TotalToDownload, NowDownloaded);
	}

	return 0;
}

// Get error info
String LibCurl::GetErrorInfo(RetCode eRetCode)
{
	std::string strErrorMsg=curl_easy_strerror(eRetCode);

	String strMsg = String(strErrorMsg, ENCODE_UTF8);

	return strMsg;
}

// Clear the head list
None LibCurl::ClearRequeHeadHead(HeadList& hList)
{
	if (hList)
	{
		curl_slist_free_all(hList);

		hList = NULL;
	}
}

// Set head for url
LibCurl::HeadList LibCurl::SetRequestHead(String strHeadType,
	String strProtocol,
	String strEncodeType)
{
	if (strHeadType.IsEmpty())
	{
		return NULL;
	}

	if (strProtocol.IsEmpty())
	{
		return NULL;
	}

	if (strEncodeType.IsEmpty())
	{
		return NULL;
	}

	String strHeadInfo = strHeadType + String(_T(":")) + strProtocol + String(_T(";")) + strEncodeType;

	HeadList pHeadList = NULL;

	pHeadList = curl_slist_append(pHeadList, strHeadInfo.ToUTF8Data().c_str());

	return pHeadList;
}

// Post the request by http
Boolean LibCurl::Post(TransPara& Para, Int32& iErrorCode, String& strErrorMessage)
{
	if (Para.strRequestUrl.empty())
	{
		return false;
	}

	m_TransPara = Para;

	// Create an url
	UrlHandle pHandle;
	if (!CreateUrL(pHandle))
	{
		strErrorMessage = GetErrorInfo(CURLE_FAILED_INIT);

		return false;
	}

	// Build the head info
	HeadList pList = SetRequestHead();
	if (pList == NULL)
	{
		return false;
	}

	curl_easy_setopt(pHandle, CURLOPT_HTTPHEADER, pList);

	curl_easy_setopt(pHandle, CURLOPT_URL, (char*)Para.strRequestUrl.c_str());

	curl_easy_setopt(pHandle, CURLOPT_POST, 1);

	curl_easy_setopt(pHandle, CURLOPT_POSTFIELDS, (char*)Para.strPostPara.c_str());

	curl_easy_setopt(pHandle, CURLOPT_POSTFIELDSIZE, Para.strPostPara.size());

	curl_easy_setopt(pHandle, CURLOPT_READFUNCTION, NULL);

	curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, OnWriteData);

	curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, (void *)this);

	curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYPEER, false);

	curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYHOST, false);

	{
		curl_easy_setopt(pHandle, CURLOPT_NOPROGRESS, false);

		curl_easy_setopt(pHandle, CURLOPT_PROGRESSFUNCTION, ProgressCallback);

		curl_easy_setopt(pHandle, CURLOPT_PROGRESSDATA, this);
	}

	m_TransPara.strResponse.clear();

	curl_easy_setopt(pHandle, CURLOPT_NOSIGNAL, 1);

	curl_easy_setopt(pHandle, CURLOPT_CONNECTTIMEOUT, 3);

	curl_easy_setopt(pHandle, CURLOPT_TIMEOUT, Para.iSecondTimeout);

	CURLcode eRetCode = curl_easy_perform(pHandle);
	if (eRetCode != CURLE_OK)
	{
		curl_easy_getinfo(pHandle, CURLINFO_RESPONSE_CODE, &iErrorCode);

		strErrorMessage = GetErrorInfo(eRetCode);

		// Clear the head list
		ClearRequeHeadHead(pList);

		// Destory the url
		DestoryUrL(pHandle);

		return false;
	}

	// Change the respond data encode
	Para.strResponse = m_TransPara.strResponse;

	// Clear the head list
	ClearRequeHeadHead(pList);

	// Destory the url
	DestoryUrL(pHandle);

	return true;
}

// Get the respoend by http
Boolean LibCurl::Get(TransPara& Para, Int32& iErrorCode, String& strErrorMessage)
{
	if (Para.strRequestUrl.empty())
	{
		return false;
	}

	m_TransPara = Para;

	// Create an url
	UrlHandle pHandle;
	if (!CreateUrL(pHandle))
	{
		strErrorMessage = GetErrorInfo(CURLE_FAILED_INIT);

		return false;
	}

	curl_easy_setopt(pHandle, CURLOPT_HTTPGET, 1);

	curl_easy_setopt(pHandle, CURLOPT_URL, (char*)Para.strRequestUrl.c_str());

	curl_easy_setopt(pHandle, CURLOPT_FOLLOWLOCATION, 1);

	curl_easy_setopt(pHandle, CURLOPT_READFUNCTION, NULL);

	curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, OnWriteData);

	curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, (void *)this);

	curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYPEER, false);

	curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYHOST, false);

	curl_easy_setopt(pHandle, CURLOPT_PROGRESSFUNCTION, ProgressCallback);

	curl_easy_setopt(pHandle, CURLOPT_PROGRESSDATA, (void*)this);

	curl_easy_setopt(pHandle, CURLOPT_NOPROGRESS, FALSE);

	m_TransPara.strResponse.clear();

	curl_easy_setopt(pHandle, CURLOPT_NOSIGNAL, 1);

	curl_easy_setopt(pHandle, CURLOPT_CONNECTTIMEOUT, 3);

	curl_easy_setopt(pHandle, CURLOPT_TIMEOUT, Para.iSecondTimeout);

	CURLcode eRetCode = curl_easy_perform(pHandle);
	if (eRetCode != CURLE_OK)
	{
		curl_easy_getinfo(pHandle, CURLINFO_RESPONSE_CODE, &iErrorCode);

		strErrorMessage = GetErrorInfo(eRetCode);

		// Destory the url
		DestoryUrL(pHandle);

		return false;
	}

	// Change the respond data encode
	Para.strResponse = m_TransPara.strResponse;

	// Destory the url
	DestoryUrL(pHandle);

	return true;
}

// Post the request by https (pCaPath==NULL : do not verify the certification on server)
Boolean LibCurl::Posts(TransPara& Para, String& strErrorMessage, const SByteArray pCaPath)
{
	if (Para.strRequestUrl.empty())
	{
		return false;
	}

	m_TransPara = Para;

	// Create an url
	UrlHandle pHandle;
	if (!CreateUrL(pHandle))
	{
		strErrorMessage = GetErrorInfo(CURLE_FAILED_INIT);

		return false;
	}

	// Build the head info
	HeadList pList = SetRequestHead();
	if (pList == NULL)
	{
		return false;
	}

	curl_easy_setopt(pHandle, CURLOPT_HTTPHEADER, pList);

	curl_easy_setopt(pHandle, CURLOPT_URL, (char*)Para.strRequestUrl.c_str());

	curl_easy_setopt(pHandle, CURLOPT_POST, 1);

	curl_easy_setopt(pHandle, CURLOPT_POSTFIELDS, Para.strPostPara.c_str());

	curl_easy_setopt(pHandle, CURLOPT_POSTFIELDSIZE, Para.strPostPara.size());

	curl_easy_setopt(pHandle, CURLOPT_READFUNCTION, NULL);

	curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, OnWriteData);

	curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, (void *)this);

	curl_easy_setopt(pHandle, CURLOPT_NOSIGNAL, 1);

	{
		curl_easy_setopt(pHandle, CURLOPT_NOPROGRESS, false);

		curl_easy_setopt(pHandle, CURLOPT_PROGRESSFUNCTION, ProgressCallback);

		curl_easy_setopt(pHandle, CURLOPT_PROGRESSDATA, this);
	}

	m_TransPara.strResponse.clear();

	if (pCaPath == NULL)
	{
		curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYPEER, false);

		curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYHOST, false);
	}
	else
	{
		curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYPEER, true);

		curl_easy_setopt(pHandle, CURLOPT_CAINFO, pCaPath);
	}

	curl_easy_setopt(pHandle, CURLOPT_CONNECTTIMEOUT, 3);

	curl_easy_setopt(pHandle, CURLOPT_TIMEOUT, Para.iSecondTimeout);

	CURLcode eRetCode = curl_easy_perform(pHandle);
	if (eRetCode != CURLE_OK)
	{
		strErrorMessage = GetErrorInfo(eRetCode);

		// Clear the head list
		ClearRequeHeadHead(pList);

		// Destory the url
		DestoryUrL(pHandle);

		return false;
	}

	// Change the respond data encode
	Para.strResponse = m_TransPara.strResponse;

	// Clear the head list
	ClearRequeHeadHead(pList);

	// Destory the url
	DestoryUrL(pHandle);

	return true;
}

// Get the respoend by https (pCaPath==NULL : do not verify the certification on server)
Boolean LibCurl::Gets(TransPara& Para, String& strErrorMessage, const SByteArray pCaPath)
{
	if (Para.strRequestUrl.empty())
	{
		return false;
	}

	m_TransPara = Para;

	// Create an url
	UrlHandle pHandle;
	if (!CreateUrL(pHandle))
	{
		strErrorMessage = GetErrorInfo(CURLE_FAILED_INIT);

		return false;
	}

	curl_easy_setopt(pHandle, CURLOPT_URL, (char*)Para.strRequestUrl.c_str());

	curl_easy_setopt(pHandle, CURLOPT_READFUNCTION, NULL);

	curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, OnWriteData);

	curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, (void *)this);

	curl_easy_setopt(pHandle, CURLOPT_NOSIGNAL, 1);

	{
		curl_easy_setopt(pHandle, CURLOPT_NOPROGRESS, false);

		curl_easy_setopt(pHandle, CURLOPT_PROGRESSFUNCTION, ProgressCallback);

		curl_easy_setopt(pHandle, CURLOPT_PROGRESSDATA, this);
	}

	m_TransPara.strResponse.clear();

	if (pCaPath == NULL)
	{
		curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYPEER, false);

		curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYHOST, false);
	}
	else
	{
		curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYPEER, true);

		curl_easy_setopt(pHandle, CURLOPT_CAINFO, pCaPath);
	}

	curl_easy_setopt(pHandle, CURLOPT_CONNECTTIMEOUT,3);

	curl_easy_setopt(pHandle, CURLOPT_TIMEOUT, Para.iSecondTimeout);

	CURLcode eRetCode = curl_easy_perform(pHandle);
	if (eRetCode != CURLE_OK)
	{
		strErrorMessage = GetErrorInfo(eRetCode);

		// Destory the url
		DestoryUrL(pHandle);

		return false;
	}

	// Change the respond data encode
	Para.strResponse = m_TransPara.strResponse;

	// Destory the url
	DestoryUrL(pHandle);

	return true;
}
