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

		Close();
	}
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
		SetErrorMessage(String("Invalid file path!"));

		return false;
	}

	String strLeftPath = strDocFilePath.Left(iPos + 1);

	String strDocName = strDocFilePath.Right(strDocFilePath.GetLength() - iPos - 1);

	Int32 iPos1 = strDocName.FindLast(String("."));
	if (iPos1 == -1)
	{
		SetErrorMessage(String("Invalid short file name!"));

		return false;
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
		SetErrorMessage(String("DFW file path is None!"));

		return false;
	}

	WordProcessingCompiler& Compiler = WordProcessingCompiler::GetInstance();

	if (!Compiler.Compile(strDocFilePath.ToANSIData(),strDfwFilePath.ToANSIData()))
	{
		SetErrorMessage(Compiler.GetErrorMessage());

		return false;
	}

	return true;
}

// Load the doc
Boolean Word::Load(String strDocFilePath)
{
	if (strDocFilePath.IsEmpty())
	{
		SetErrorMessage(String("Doc file path is None!"));

		return false;
	}

	SetDocFilePath(strDocFilePath);

	// Get new dfw file path
	String strDfwFilePath = GetNewDocPath(strDocFilePath);
	if (strDfwFilePath.IsEmpty())
	{
		SetErrorMessage(String("Failed to compile the doc file!"));

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
		SetErrorMessage(WordMerger.GetErrorMessage());

		return false;
	}

	return true;
}

// Get the doc content
Boolean Word::GetDoc(String& strContent)
{
	if (GetDocFilePath().IsEmpty())
	{
		SetErrorMessage(String("Doc file path is None!"));

		return false;
	}

	File FileHelper;

	if (!FileHelper.Open(GetDocFilePath(),File::FileMode::OPEN))
	{
		SetErrorMessage(String("Failed to open the doic!"));

		return false;
	}

	FixedUInt32 iFileSize = (FixedUInt32)FileHelper.GetSize();

	FileHelper.Read((SByteArray)strContent.ToANSIData().c_str(), 0, iFileSize);

	FileHelper.Close();

	return true;
}

// Write the doc
Boolean Word::WriteDoc(String strValue,
	String strTitleName,
	String strFiledName)
{
	if (strValue.IsEmpty())
	{
		SetErrorMessage(String("Data to be written is None!"));

		return false;
	}

	WordProcessingMerger& WordMerger = WordProcessingMerger::GetInstance();

	if (!WordMerger.SetClipboardValue(strTitleName.ToANSIData(),
		strFiledName.ToANSIData(),
		strValue.ToANSIData()))
	{
		SetErrorMessage(WordMerger.GetErrorMessage());

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
		SetErrorMessage(WordMerger.GetErrorMessage());

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
		SetErrorMessage(WordMerger.GetErrorMessage());

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