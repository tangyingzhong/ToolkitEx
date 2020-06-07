///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
///  Offer compress and uncompress file or folder interfaces
///</describe>
/// <date>2019/7/25</date>
///***********************************************************************
#ifndef MINIZIP_H
#define MINIZIP_H

#include "Tool/BaseType/String.h"
#include "zip.h"

using namespace System::BasicType;

class MiniZi
{
public:
	// Construct the MiniZi
	MiniZi();

	// Destory the MiniZi
	virtual ~MiniZi();

private:
	// Forbid the MiniZi's copy
	MiniZi(const MiniZi& other){	}

	// Forbid the MiniZi's assignment
	MiniZi& operator=(const MiniZi& other){ return *this; }

public:
	// Compress the file
	virtual Boolean CompressFile(String strSrcFilePath, 
		String strZipFilePath, 
		String strPassword = String(""));

	// Compress the file
	virtual Boolean CompressFile(std::vector<String>& SrcFilePathTable, 
		String strZipFilePath, 
		String strPassword = String(""));

	// Compress the folder (If you have another zip file to the current zip file ,you should not use password)
	virtual Boolean CompressFolder(String strSrcFolderPath, 
		String strZipFilePath,
		String strPassword = String(""));

	// Uncompress zip file
	virtual Boolean UnCompress(String strZipFilePath, 
		String strDestDirPath, 
		String strPassword = String(""));

	// Get file path in zip
	virtual Boolean GetFilePathInZip(String strZipFilePath,
		String strFileName,
		String& strFilePathInZip,
		String strPassword = String(""));

	// Get file list in zip
	virtual Boolean GetFileListInZip(String strZipFilePath,
		std::vector<String>& FileList,
		String strPassword = String(""));

	// Is the file in this zip file
	virtual Boolean IsFileInZip(String strZipFilePath,
		String strFileName,
		bool bInsensitiveCase,
		String strPassword = String(""));

	// Is file in the zip by recursively(Child zip file must be in parent zip file)
	virtual Boolean IsFileInChildZip(String strParentZipFilePath,
		String strChildZipFileName,
		String strFileName,
		bool bInsensitiveCase,
		String strPassword = String(""));

	// Get the error message
	virtual String GetErrorMsg();

private:
	// Init the MiniZi
	None Initialize();

	// Destory the MiniZi
	None Destory();

	// Get error message
	String GetZipErrorMsg(DWORD dErrorCode);

	// Get error message
	String GetUnZipErrorMsg(DWORD dErrorCode);

	// Compress folder
	Boolean CompressFolder(HZIP hZip,
		String strLastFolderName,
		String strCurFolderPath, 
		String strPassword);

private:
	// Get the Disposed
	inline Boolean GetDisposed() const
	{
		return m_bDisposed;
	}

	// Set the Disposed
	inline None SetDisposed(Boolean bDisposed)
	{
		m_bDisposed = bDisposed;
	}

	// Get the ErrorText
	inline String GetErrorText() const
	{
		return m_strErrorText;
	}

	// Set the ErrorText
	inline void SetErrorText(String strErrorText)
	{
		m_strErrorText = strErrorText;
	}

private:
	// Error message
	String m_strErrorText;

	// Disposed status
	Boolean m_bDisposed;
};

#endif // MINIZIP_H
