#include "WordProcessingCompiler.h"
#include "WordProcessingMerger.h"
#include "Tool/Encoding/ANSI.h"
#include "Tool/Encoding/Unicode.h"
#include "Tool/Encoding/UTF8.h"
#include "Tool/Directory/Directory.h"
#include "Tool/File/File.h"
#include "Tool/Thread/Process.h"
#include "Word.h"

#pragma comment(lib, "DocxFactory.lib")

using namespace System::Thread;
using namespace System::Encoding;
using namespace System::IO;
using namespace System::Office;
using namespace DocxFactory;

// Construct the Word
Word::Word() :m_strDocFilePath(String("")),
m_strErrorMessage(String("")),
m_bDisposed(false)
{
	Initialize();
}

// Detructe the Word
Word::~Word()
{
	Destory();
}

// Initialize the Word
None Word::Initialize()
{

}

// Destory the Word
None Word::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		Clear();

		Close();
	}
}

// Delete imediate file
None Word::Clear()
{
	String strSrcDocPath = GetDocFilePath();

	Int32 iPos = strSrcDocPath.FindLast(String("."));
	if (iPos == -1)
	{
		return;
	}

	strSrcDocPath = strSrcDocPath.Left(iPos);

	String strDfwFilePath = strSrcDocPath + String(".dfw");

	File::Delete(strDfwFilePath);
}

// Get new doc file path 
String Word::GetNewDocPath(String strDocFilePath)
{
	if (strDocFilePath.IsEmpty())
	{
		return String("");
	}

	Int32 iPos = strDocFilePath.FindLast(String("\\"));
	if (iPos == -1)
	{
		SetErrorMessage(String(_T("Invalid file path!")));

		return String("");
	}

	String strLeftPath = strDocFilePath.Left(iPos + 1);

	String strDocName = strDocFilePath.Right(strDocFilePath.GetLength() - iPos - 1);

	Int32 iPos1 = strDocName.FindLast(String("."));
	if (iPos1 == -1)
	{
		SetErrorMessage(String(_T("Invalid short file name!")));

		return String("");
	}

	String strLeftName = strDocName.Left(iPos1 + 1);

	String strNewDocPath = Directory::AddEnding(strLeftPath) + strLeftName + String("dfw");

	return strNewDocPath;
}

// Compile the doc file
Boolean Word::Compile(String strDocFilePath, String strDfwFilePath)
{
	if (strDocFilePath.IsEmpty())
	{
		SetErrorMessage(String("Doc file path is None!"));

		return false;
	}

	if (strDfwFilePath.IsEmpty())
	{
		SetErrorMessage(String(_T("DFW file path is empty!")));

		return false;
	}

	WordProcessingCompiler& Compiler = WordProcessingCompiler::GetInstance();

	if (!Compiler.Compile(strDocFilePath.ToANSIData(),strDfwFilePath.ToANSIData()))
	{
		String strErrorMsg = Compiler.GetErrorMessage();

		SetErrorMessage(strErrorMsg);

		return false;
	}

	return true;
}

// Load the doc
Boolean Word::Load(String strDocFilePath)
{
	if (strDocFilePath.IsEmpty())
	{
		SetErrorMessage(String(_T("Doc file path is None!")));

		return false;
	}

	SetDocFilePath(strDocFilePath);

	// Get new dfw file path
	String strDfwFilePath = GetNewDocPath(strDocFilePath);
	if (strDfwFilePath.IsEmpty())
	{
		SetErrorMessage(String(_T("Failed to compile the doc file!")));

		return false;
	}

	// Compile the doc file
	if (!Compile(strDocFilePath,strDfwFilePath))
	{
		return false;
	}

	WordProcessingMerger& WordMerger = WordProcessingMerger::GetInstance();

	if (!WordMerger.Load(strDfwFilePath.ToANSIData()))
	{
		String strErrorMsg = WordMerger.GetErrorMessage();

		SetErrorMessage(strErrorMsg);

		return false;
	}

	return true;
}

// Get the doc content
Boolean Word::GetDoc(String& strContent)
{
	if (GetDocFilePath().IsEmpty())
	{
		SetErrorMessage(String(_T("Doc file path is empty!")));

		return false;
	}

	// Save this doc to be a txt file
	String strCurExePath = Directory::AddEnding(Directory::GetExcutableDirectory());

	strCurExePath = strCurExePath + String(_T("temp.txt"));

	Save(strCurExePath);

	// Read the txt file
	File FileHelper;

	if (!FileHelper.Open(strCurExePath,File::FileMode::OPEN,File::FileAccess::READ))
	{
		SetErrorMessage(String(_T("Failed to open the doc!")));

		File::Delete(strCurExePath);

		return false;
	}

	FixedUInt32 iFileSize = (FixedUInt32)FileHelper.GetSize();

	Array<SByte> FileData(iFileSize+1);

	File::ArraySize iContentSize = FileHelper.Read(FileData.Data(), 0, FileData.Size());
	if (iContentSize <= 0)
	{
		SetErrorMessage(String(_T("Failed to read the doc!")));

		File::Delete(strCurExePath);

		return false;
	}

	FileHelper.Close();

	File::Delete(strCurExePath);

	strContent = String(FileData.Data());

	return true;
}

// Write the doc
Boolean Word::WriteDoc(String strValue,
	String strTitleName,
	String strFiledName)
{
	if (strValue.IsEmpty())
	{
		SetErrorMessage(String(_T("Data to be written is empty!")));

		return false;
	}

	WordProcessingMerger& WordMerger = WordProcessingMerger::GetInstance();

	if (!WordMerger.SetClipboardValue(strTitleName.ToANSIData(),
		strFiledName.ToANSIData(),
		strValue.ToANSIData()))
	{
		String strErrorMsg = WordMerger.GetErrorMessage();

		SetErrorMessage(strErrorMsg);

		return false;
	}

	if (!WordMerger.Paste(strTitleName.ToANSIData()))
	{
		String strErrorMsg = WordMerger.GetErrorMessage();

		SetErrorMessage(strErrorMsg);

		return false;
	}

	return true;
}

// Write the doc
Boolean Word::WriteDoc(Real dValue,
	String strTitleName,
	String strFiledName)
{
	WordProcessingMerger& WordMerger = WordProcessingMerger::GetInstance();

	if (!WordMerger.SetClipboardValue(strTitleName.ToANSIData(),
		strFiledName.ToANSIData(),
		dValue))
	{
		String strErrorMsg = WordMerger.GetErrorMessage();

		SetErrorMessage(strErrorMsg);

		return false;
	}

	return true;
}

// Save the doc
Boolean Word::Save(String strDocFilePath)
{
	if (strDocFilePath.IsEmpty())
	{
		SetErrorMessage(String("Doc file path is None!"));

		return false;
	}

	WordProcessingMerger& WordMerger = WordProcessingMerger::GetInstance();

	if (!WordMerger.Save(strDocFilePath.ToANSIData()))
	{
		String strErrorMsg = WordMerger.GetErrorMessage();

		SetErrorMessage(strErrorMsg);

		return false;
	}

	return true;
}

// Close the doc
None Word::Close()
{
	WordProcessingMerger::GetInstance().Close();
}

// Get the error message
String Word::GetErrorMsg()
{
	return GetErrorMessage();
}