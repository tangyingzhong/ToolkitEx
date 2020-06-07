#include "MiniZip.h"
#include "unzip.h"
#include "Tool/Directory/Directory.h"
#include "Tool/File/File.h"
#include "Tool/Encoding/UTF8.h"
#include "Tool/Encoding/Unicode.h"
#include "Tool/Encoding/ANSI.h"

using namespace System::IO;
using namespace System::Encoding;

// Construct the MiniZi
MiniZi::MiniZi() :
	m_strErrorText(""),
	m_bDisposed(false)
{
	Initialize();
}

// Destory the MiniZi
MiniZi::~MiniZi()
{
	Destory();
}

// Init the MiniZi
None MiniZi::Initialize()
{

}

// Destory the MiniZi
None MiniZi::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);
	}
}

// Compress the file
Boolean MiniZi::CompressFile(String strSrcFilePath, 
	String strZipFilePath, 
	String strPassword)
{
	if (strSrcFilePath.IsEmpty())
	{
		SetErrorText(String("Source file path is empty !"));

		return false;
	}

	if (strZipFilePath.IsEmpty())
	{
		SetErrorText(String("Zip file path is empty !"));

		return false;
	}

	HZIP hZip = CreateZip(strZipFilePath.CStr(), strPassword.ToANSIData().c_str());
	if (hZip == NULL)
	{
		String strErrorMsg = String("Failed to create zip file:") + strZipFilePath;

		SetErrorText(strErrorMsg);

		return false;
	}

	Int32 iPos = strSrcFilePath.FindLast(String("\\"));
	if (iPos == -1)
	{
		SetErrorText(String("Source file path is not correct !"));

		return false;
	}

	String strFileName = strSrcFilePath.Right(strSrcFilePath.GetLength() - iPos -1);

	ZRESULT dErrorCode = ZipAdd(hZip, strFileName.CStr(), strSrcFilePath.CStr());
	if (dErrorCode != ZR_OK)
	{
		SetErrorText(GetZipErrorMsg(dErrorCode));

		CloseZip(hZip);

		return false;
	}

	CloseZip(hZip);

	return true;
}

// Compress the file
Boolean MiniZi::CompressFile(std::vector<String>& SrcFilePathTable,
	String strZipFilePath,
	String strPassword)
{
	if (SrcFilePathTable.empty())
	{
		SetErrorText(String("Source file table is empty!"));

		return false;
	}

	if (strZipFilePath.IsEmpty())
	{
		SetErrorText(String("Zip file path is empty !"));

		return false;
	}

	HZIP hZip = CreateZip(strZipFilePath.CStr(), strPassword.ToANSIData().c_str());
	if (hZip == NULL)
	{
		String strErrorMsg = String("Failed to create zip file:") + strZipFilePath;

		SetErrorText(strErrorMsg);

		return false;
	}

	for (int index = 0; index < static_cast<int>(SrcFilePathTable.size()); ++index)
	{
		String strSrcFilePath = SrcFilePathTable[index];

		String strFilePath = strSrcFilePath;

		Int32 iPos = strSrcFilePath.FindLast(String("\\"));
		if (iPos == -1)
		{
			SetErrorText(String("Source file path is not correct !"));

			return false;
		}

		String strFileName = strSrcFilePath.Right(strSrcFilePath.GetLength() - iPos - 1);

		Int32 iPos1 = strFilePath.Find(String(":"), 0);
		if (iPos1 == -1)
		{
			SetErrorText(String("Source file path is not correct !"));

			return false;
		}

		String strMidFileName = strFilePath.Right(strFilePath.GetLength() - iPos1 - 1);

		String strFilePathInZip = strMidFileName;

		ZRESULT dErrorCode = ZipAdd(hZip, strFilePathInZip.CStr(), strSrcFilePath.CStr());
		if (dErrorCode != ZR_OK)
		{
			SetErrorText(GetZipErrorMsg(dErrorCode));

			CloseZip(hZip);

			return false;
		}
	}

	CloseZip(hZip);

	return true;
}

// Compress the folder
Boolean MiniZi::CompressFolder(String strSrcFolderPath, 
	String strZipFilePath,
	String strPassword)
{
	if (strSrcFolderPath.IsEmpty())
	{
		SetErrorText(String("Source folder path is empty !"));

		return false;
	}

	if (strZipFilePath.IsEmpty())
	{
		SetErrorText(String("Zip file path is empty !"));

		return false;
	}

	// Create zip file
	HZIP hZip = CreateZip(strZipFilePath.CStr(), strPassword.ToANSIData().c_str());
	if (hZip == NULL)
	{
		String strErrorMsg = String("Failed to create zip file:") + strZipFilePath;

		SetErrorText(strErrorMsg);

		return false;
	}

	// Compress folder
	if (!CompressFolder(hZip, String(""),strSrcFolderPath,strPassword))
	{
		CloseZip(hZip);

		return false;
	}

	CloseZip(hZip);

	return true;
}

// Compress folder
Boolean MiniZi::CompressFolder(HZIP hZip,
	String strLastFolderName,
	String strCurFolderPath,
	String strPassword)
{
	if (hZip == NULL)
	{
		return false;
	}

	if (strCurFolderPath.IsEmpty())
	{
		return false;
	}

	// Get folder name
	String strSrcFolderPath = Directory::TrimEnding(strCurFolderPath);

	Int32 iPos1 = strSrcFolderPath.FindLast(String("\\"));
	if (iPos1 == -1)
	{
		String strErrorMsg = String("Invalid folder path:") + strSrcFolderPath;

		SetErrorText(strErrorMsg);

		return false;
	}

	String strFolderName = strSrcFolderPath.Right(strSrcFolderPath.GetLength() - iPos1 - 1);

	String strTempFolderName = strFolderName;

	// Add folder to zip
	if (!strLastFolderName.IsEmpty())
	{
		strFolderName = strLastFolderName + String("\\") + strFolderName;
	}

	ZRESULT dErrorCode = ZipAddFolder(hZip, strFolderName.CStr());
	if (dErrorCode != ZR_OK)
	{
		SetErrorText(GetZipErrorMsg(dErrorCode));

		return false;
	}

	// Backup folder path
	String strTempFolderPath = strCurFolderPath;

	String strDirPath = strTempFolderPath;

	int iFindPos = strCurFolderPath.FindLast(String("\\"));
	if (iFindPos == -1)
	{
		return false;
	}
	else if (iFindPos == strCurFolderPath.GetLength() - 1)
	{
		strDirPath = strDirPath + String("*");
	}
	else
	{
		strDirPath = strDirPath + String("\\*");
	}

	// Find the file with its attributes
	WIN32_FIND_DATA data;

	HANDLE hDirectory = ::FindFirstFile(strDirPath.CStr(), &data);
	if (hDirectory == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	while (1)
	{
		// Find the next file or directory
		if (!FindNextFile(hDirectory, &data))
		{
			break;
		}

		// Judge the found one is directory or not
		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (String(data.cFileName) == String("..")
				|| String(data.cFileName) == String("."))
			{
				continue;
			}

			// Wipe out the last character '*'
			String strRoot = strDirPath.SubString(0, strDirPath.GetLength() - 1);

			// Rebuild the directory path
			String strNextDir = strRoot + data.cFileName;

			// Add folder to zip
			String strDirName = data.cFileName;

			String strRootDirName = strTempFolderPath;

			String strSubFolderPath= Directory::AddEnding(strRootDirName) + strDirName;

			if (!CompressFolder(hZip, strFolderName,strSubFolderPath, strPassword))
			{
				return false;
			}
		}
		else
		{
			String strFileName = data.cFileName;

			String strRootDirName = strFolderName;

			String strFileNameInZip = strRootDirName + String("\\") + strFileName;

			String strFullPath = Directory::AddEnding(strSrcFolderPath) + strFileName;

			ZRESULT dErrorCode = ZipAdd(hZip, strFileNameInZip.CStr(), strFullPath.CStr());
			if (dErrorCode != ZR_OK)
			{
				SetErrorText(GetZipErrorMsg(dErrorCode));

				return false;
			}
		}
	}

	// Close the finding
	::FindClose(hDirectory);

	return true;
}

// Uncompress zip file
Boolean MiniZi::UnCompress(String strZipFilePath, 
	String strDestDirPath, 
	String strPassword)
{
	if (strZipFilePath.IsEmpty())
	{
		SetErrorText(String("Zip file path is empty !"));

		return false;
	}

	if (strDestDirPath.IsEmpty())
	{
		SetErrorText(String("Dest file path is empty !"));

		return false;
	}

	String strRootDirPath = Directory::AddEnding(strDestDirPath);

	if (!Directory::IsExisted(strRootDirPath))
	{
		if (!Directory::Create(strRootDirPath))
		{
			SetErrorText(String("Failed to set unzip environment !"));

			return false;
		}
	}

	String strCurDirPath = Directory::GetCurDirectory();

	::SetCurrentDirectory(strRootDirPath.CStr());

	HZIP hZip = OpenZip(strZipFilePath.CStr(), strPassword.ToANSIData().c_str());
	if (hZip == NULL)
	{
		String strErrorMsg = String("Failed to open zip file:") + strZipFilePath;

		SetErrorText(strErrorMsg);

		return false;
	}

	ZIPENTRY ZipEntry;

	ZRESULT dErrorCode = GetZipItem(hZip, -1, &ZipEntry);
	if (dErrorCode != ZR_OK)
	{
		SetErrorText(GetUnZipErrorMsg(dErrorCode));

		CloseZip(hZip);

		return false;
	}

	Int32 iItemCount = ZipEntry.index;

	for (Int32 index = 0; index < iItemCount; ++index)
	{
		dErrorCode = GetZipItem(hZip, index, &ZipEntry);
		if (dErrorCode != ZR_OK)
		{
			SetErrorText(GetUnZipErrorMsg(dErrorCode));

			CloseZip(hZip);

			return false;
		}

		dErrorCode = UnzipItem(hZip, index, ZipEntry.name);
		if (dErrorCode != ZR_OK)
		{
			SetErrorText(GetUnZipErrorMsg(dErrorCode));

			CloseZip(hZip);

			return false;
		}
	}

	::SetCurrentDirectory(strCurDirPath.CStr());

	CloseZip(hZip);

	return true;
}

// Get file path in zip
Boolean MiniZi::GetFilePathInZip(String strZipFilePath,
	String strFileName,
	String& strFilePathInZip,
	String strPassword)
{
	if (strZipFilePath.IsEmpty())
	{
		SetErrorText(String("Zip file path is empty !"));

		return false;
	}

	if (strFileName.IsEmpty())
	{
		SetErrorText(String("File name you searching is empty !"));

		return false;
	}

	HZIP hZip = OpenZip(strZipFilePath.CStr(), strPassword.ToANSIData().c_str());
	if (hZip == NULL)
	{
		String strErrorMsg = String("Failed to open zip file:") + strZipFilePath;

		SetErrorText(strErrorMsg);

		return false;
	}

	ZIPENTRY ZipEntry;

	ZRESULT dErrorCode = GetZipItem(hZip, -1, &ZipEntry);
	if (dErrorCode != ZR_OK)
	{
		SetErrorText(GetUnZipErrorMsg(dErrorCode));

		CloseZip(hZip);

		return false;
	}

	Int32 iItemCount = ZipEntry.index;

	for (Int32 index = 0; index < iItemCount; ++index)
	{
		dErrorCode = GetZipItem(hZip, index, &ZipEntry);
		if (dErrorCode != ZR_OK)
		{
			SetErrorText(GetUnZipErrorMsg(dErrorCode));

			CloseZip(hZip);

			return false;
		}

		String strFileNameInZip = ZipEntry.name;

		Int32 iPos = strFileNameInZip.FindLast(String("/"));
		if (iPos == -1)
		{
			String strTempFileName = strFileNameInZip;

			if (strTempFileName == strFileName)
			{
				strFilePathInZip = ZipEntry.name;

				return true;
			}
		}
		else
		{
			String strTempFileName = strFileNameInZip.Right(strFileNameInZip.GetLength() - iPos - 1);

			if (strTempFileName == strFileName)
			{
				strFilePathInZip = ZipEntry.name;

				return true;
			}
		}
	}

	CloseZip(hZip);

	return true;
}

// Get file list in zip
Boolean MiniZi::GetFileListInZip(String strZipFilePath,
	std::vector<String>& FileList,
	String strPassword)
{
	if (strZipFilePath.IsEmpty())
	{
		SetErrorText(String("Zip file path is empty !"));

		return false;
	}

	HZIP hZip = OpenZip(strZipFilePath.CStr(), strPassword.ToANSIData().c_str());
	if (hZip == NULL)
	{
		String strErrorMsg = String("Failed to open zip file:") + strZipFilePath;

		SetErrorText(strErrorMsg);

		return false;
	}

	ZIPENTRY ZipEntry;

	ZRESULT dErrorCode = GetZipItem(hZip, -1, &ZipEntry);
	if (dErrorCode != ZR_OK)
	{
		SetErrorText(GetUnZipErrorMsg(dErrorCode));

		CloseZip(hZip);

		return false;
	}

	Int32 iItemCount = ZipEntry.index;

	for (Int32 index = 0; index < iItemCount; ++index)
	{
		dErrorCode = GetZipItem(hZip, index, &ZipEntry);
		if (dErrorCode != ZR_OK)
		{
			SetErrorText(GetUnZipErrorMsg(dErrorCode));

			CloseZip(hZip);
			
			return false;
		}

		FileList.push_back(ZipEntry.name);
	}

	CloseZip(hZip);

	return true;
}

// Is file in the zip
Boolean MiniZi::IsFileInZip(String strZipFilePath,
	String strFileName,
	bool bInsensitiveCase,
	String strPassword)
{
	if (strZipFilePath.IsEmpty())
	{
		SetErrorText(String("Zip file path is empty !"));

		return false;
	}

	if (strFileName.IsEmpty())
	{
		SetErrorText(String("File name you searching is empty !"));

		return false;
	}

	HZIP hZip = OpenZip(strZipFilePath.CStr(), strPassword.ToANSIData().c_str());
	if (hZip == NULL)
	{
		String strErrorMsg = String("Failed to open zip file:") + strZipFilePath;

		SetErrorText(strErrorMsg);

		return false;
	}

	ZIPENTRY ZipEntry;

	ZRESULT dErrorCode = GetZipItem(hZip, -1, &ZipEntry);
	if (dErrorCode != ZR_OK)
	{
		SetErrorText(GetUnZipErrorMsg(dErrorCode));

		CloseZip(hZip);

		return false;
	}

	Int32 iItemCount = ZipEntry.index;

	for (Int32 index = 0; index < iItemCount; ++index)
	{
		dErrorCode = GetZipItem(hZip, index, &ZipEntry);
		if (dErrorCode != ZR_OK)
		{
			SetErrorText(GetUnZipErrorMsg(dErrorCode));

			CloseZip(hZip);

			return false;
		}

		String strFileNameInZip = ZipEntry.name;

		Int32 iPos = strFileNameInZip.FindLast(String("/"));
		if (iPos == -1)
		{
			String strTempFileName = strFileNameInZip;

			if (!bInsensitiveCase)
			{
				if (strTempFileName.MakeUpper() == strFileName.MakeUpper())
				{
					CloseZip(hZip);

					return true;
				}
			}
			else
			{
				if (strTempFileName == strFileName)
				{
					CloseZip(hZip);

					return true;
				}
			}
		}
		else
		{
			String strTempFileName = strFileNameInZip.Right(strFileNameInZip.GetLength() - iPos - 1);

			if (!bInsensitiveCase)
			{
				if (strTempFileName.MakeUpper() == strFileName.MakeUpper())
				{
					CloseZip(hZip);

					return true;
				}
			}
			else
			{
				if (strTempFileName == strFileName)
				{
					CloseZip(hZip);

					return true;
				}
			}
		}
	}

	SetErrorText(String("There is no such file in zip !"));

	CloseZip(hZip);

	return false;
}

// Is file in the zip by recursively
Boolean MiniZi::IsFileInChildZip(String strParentZipFilePath,
	String strChildZipFileName,
	String strFileName,
	bool bInsensitiveCase,
	String strPassword)
{
	if (strParentZipFilePath.IsEmpty())
	{
		SetErrorText(String("Zip file path is empty !"));

		return false;
	}

	if (strChildZipFileName.IsEmpty())
	{
		SetErrorText(String("Child zip file name is empty !"));

		return false;
	}

	if (strFileName.IsEmpty())
	{
		SetErrorText(String("File name you searching is empty !"));

		return false;
	}

	// Recursively mode
	String strTempZipDirPath = String("C:\\TempZip\\");

	if (!UnCompress(strParentZipFilePath, strTempZipDirPath,strPassword))
	{
		return false;
	}

	// Hide the directory
	Directory::SetDirAttribute(strTempZipDirPath, Directory::FileAttrEnum::HIDDEN);

	/*Int32 iPos = strFileName.FindLast(String("/"));
	if (iPos == -1)
	{
		iPos = strFileName.FindLast(String("\\"));
		if (iPos == -1)
		{
			SetErrorText(String("In recursively mode,you should input file name as Test/aa.json [Test is a zip file in your parent zip file] !"));

			return false;
		}
	}*/

	String strSecondZipFilePath = strChildZipFileName;

	// Get file path in zip
	String strFilePathInZip = String("");

	if (!GetFilePathInZip(strParentZipFilePath, strSecondZipFilePath, strFilePathInZip,strPassword))
	{
		return false;
	}

	strSecondZipFilePath = strTempZipDirPath + strFilePathInZip;

	String strFileNameInZip = strFileName;

	if (!IsFileInZip(strSecondZipFilePath, strFileNameInZip,bInsensitiveCase,strPassword))
	{
		return false;
	}

	Directory::SetDirAttribute(String("C:\\TempZip\\"), Directory::FileAttrEnum::NORMAL);

	Directory::Delete(String("C:\\TempZip\\"), true);

	return true;
}

// Get error message
String MiniZi::GetZipErrorMsg(DWORD dErrorCode)
{
	char Buffer[1024] = { 0 };

	FormatZipMessageZ(dErrorCode, Buffer, 1024);

	std::string strErrorText = Buffer;

	return strErrorText;
}

// Get error message
String MiniZi::GetUnZipErrorMsg(DWORD dErrorCode)
{
	TCHAR Buffer[1024] = { 0 };

	FormatZipMessageU(dErrorCode, Buffer, 1024);

	return Buffer;
}

// Get the error message
String MiniZi::GetErrorMsg()
{
	return GetErrorText();
}
