#include <iostream>
#include "Toolkit/MiniZip/MiniZip.h"
//#include "Tool/Toolkit.h"
//#include "Toolkit/Office/Excel/Excel.h"
//#include "Toolkit/Office/Word/Word.h"
//#include "Toolkit/Sqlite/SqliteDB.h"
//#include "Toolkit/LibCurl/LibCurl.h"

//using namespace System::Office;

//int DownLoad(Object pUserData,
//	Real TotalToDown,
//	Real NowDownload)
//{
//	float fPercent = 100 * NowDownload / TotalToDown;
//
//	std::cout << "Downloading: "<< std::to_string(fPercent) <<"%"<< std::endl;
//
//	return 0;
//}
//
//int Upload(Object pUserData,
//	Real TotalToUpload,
//	Real NowUpload)
//{
//	float fPercent = 100 * NowUpload / TotalToUpload;
//
//	std::cout << "Uploading: " << std::to_string(fPercent) << "%" << std::endl;
//
//	return 0;
//}

int main()
{
	MiniZi MyZip;

	/*if (!MyZip.CompressFile(String("D:\\Pool1.txt"), String("D:\\Pool.zip"), String("tang1028")))
	{
		std::cout << MyZip.GetErrorMsg().ToANSIData() << std::endl;

		return false;
	}*/

	//if (!MyZip.CompressFile(String("D:\\林俊杰.-.[因你而在](2013)[WAV].zip"),
	//	String("D:\\aa.zip"),
	//	String("tang1028")))
	//{
	//	std::cout << MyZip.GetErrorMsg().ToANSIData() << std::endl;

	//	return false;
	//}

	//if (!MyZip.UnCompress(String("D:\\aa.zip"),
	//	String("D:\\yu"),
	//	String("tang1028")))
	//{
	//	std::cout << MyZip.GetErrorMsg().ToANSIData() << std::endl;

	//	return false;
	//}

	//// String("tang1028")
	//if (!MyZip.CompressFolder(String("D:\\Good"),
	//	String("D:\\Good.zip"),
	//	String("")))
	//{
	//	std::cout << MyZip.GetErrorMsg().ToANSIData() << std::endl;

	//	return false;
	//}

	/*if (!MyZip.UnCompress(String("D:\\OK.zip"), String("D:\\kill")))
	{
		std::cout << MyZip.GetErrorMsg().ToANSIData() << std::endl;

		return false;
	}*/

	/*std::vector<String> Table;

	Table.push_back(String("D:\\林俊杰.-.[因你而在](2013)[WAV].wav"));

	Table.push_back(String("D:\\Win10激活工具.zip"));

	Table.push_back(String("D:\\OK - Copy\\Pool2.txt"));

	Table.push_back(String("D:\\wav\\林俊杰.-.[因你而在](2013)[WAV].wav"));

	if (!MyZip.CompressFile(Table,
		String("D:\\Total.zip"),
		String("tang1028")))
	{
		std::cout << MyZip.GetErrorMsg().ToANSIData() << std::endl;

		return false;
	}*/

	/*if (!MyZip.UnCompress(String("D:\\wav.zip"),
		String("D:\\"),
		String("tang1028")))
	{
		std::cout << MyZip.GetErrorMsg().ToANSIData() << std::endl;

		return false;
	}*/

	/*if (!MyZip.UnCompress(String("D:\\Good.zip"),
		String("D:\\PP"),
		String("tang1028")))
	{
		std::cout << MyZip.GetErrorMsg().ToANSIData() << std::endl;

		return false;
	}*/

	/*std::vector<String> FileTable;

	if (!MyZip.GetFileListInZip(String("D:\\wav\\林俊杰.-.[因你而在](2013)[WAV].zip"),
		FileTable))
	{
		std::cout << MyZip.GetErrorMsg().ToANSIData() << std::endl;

		return false;
	}

	for (int index = 0; index < static_cast<int>(FileTable.size()); ++index)
	{
		std::cout << FileTable[index].ToANSIData() << std::endl;
	}*/

	if (MyZip.IsFileInZip(String("D:\\Good.zip"),
		String("Win10激活工具.zip"),
		true,
		String("tang1028")))
	{
		std::cout << "File is existed in zip" << std::endl;
	}

	if (MyZip.IsFileInChildZip(String("D:\\Good.zip"),
		String("Win10激活工具.zip"),
		String("Windows Loader.exe"),
		true,
		String("tang1028")))
	{
		std::cout << "File is existed in zip2" << std::endl;
	}

	/*LibCurl::InitCurl();

	LibCurl CurObject;

	bool bDownloadOk = CurObject.FtpDownload("ftp://127.0.0.1/test/林俊杰.-.[因你而在](2013)[WAV].wav", 
		"D:\\Jon.wav", 
		"abc", 
		"tang1028",
		"21",
		NULL,
		DownLoad);

	if (!bDownloadOk)
	{
		Int32 iErrorCode = 0;

		std::string strErrorMsg;

		CurObject.GetErrorInfo(iErrorCode, strErrorMsg);

		std::cout << strErrorMsg << std::endl;

		return -1;
	}

	bool bUploadOk = CurObject.FtpUpload("ftp://127.0.0.1/test/林俊杰.-.[因你而在](2013)[WAV].wav", 
		"D:\\林俊杰.-.[因你而在](2013)[WAV].wav", 
		"abc", 
		"tang1028",
		"21",
		Upload);

	if (!bUploadOk)
	{
		Int32 iErrorCode = 0;

		std::string strErrorMsg;

		CurObject.GetErrorInfo(iErrorCode, strErrorMsg);

		std::cout << strErrorMsg << std::endl;

		return -1;
	}

	std::cout << "Finish one" << std::endl;

	bool bUploadOk1 = CurObject.FtpUpload("ftp://127.0.0.1/test/软件参数对照表.xlsx",
		"D:\\软件参数对照表.xlsx",
		"abc",
		"tang1028",
		"21",
		Upload);

	if (!bUploadOk1)
	{
		Int32 iErrorCode = 0;

		std::string strErrorMsg;

		CurObject.GetErrorInfo(iErrorCode, strErrorMsg);

		std::cout << strErrorMsg << std::endl;

		return -1;
	}*/

	/*String strVersion = CurObject.GetCurVersion();

	std::cout << strVersion.ToANSIData() << std::endl;

	{
		CurObject.SetRequestHead("Accept:Agent-000");

		std::string strRespondData;

		if (!CurObject.Get("https://www.baidu.com","",strRespondData))
		{
			Int32 iErrorCode = 0;

			std::string strErrorMsg;

			CurObject.GetErrorInfo(iErrorCode, strErrorMsg);

			std::cout << strErrorMsg << std::endl;

			return -1;
		}

		{
			File FileHelper;

			FileHelper.Open(String("E:\\aa.html"), File::FileMode::OPENORCREATE, File::FileAccess::READWRITE);

			FileHelper.Write(strRespondData.c_str(), 0, strRespondData.length());

			FileHelper.Close();
		}
	}*/

	//LibCurl::DestoryCurl();


	/*SqliteDB db;

	db.Open(String("E:\\history.db"));

	if (!db.IsOpen())
	{
		std::cout << db.GetErrorMessage().ToANSIData() << std::endl;

		db.Close();

		return -1;
	}

	String strSql = String(_T("CREATE TABLE tyz( \
		id INT PRIMARY KEY NOT NULL,\
		name CHAR(50) NOT NULL,\
		age INT NOT NULL,\
		comment TEXT NULL);"));

	Int32 iAffectedRow = 0;

	if (!db.ExecuteNonQuery(strSql, iAffectedRow))
	{
		std::cout << db.GetErrorMessage().ToANSIData() << std::endl;

		db.Close();

		return -1;
	}

	String strSql = String(_T("INSERT INTO tyz (id,name,age,comment) VALUES (8,'kelly',28,'no')"));

	Int32 iAffectedRow = 0;

	if (!db.ExecuteNonQuery(strSql, iAffectedRow))
	{
		std::cout << db.GetErrorMessage().ToANSIData() << std::endl;

		db.Close();

		return -1;
	}

	std::cout << "Affected rows are :" << iAffectedRow << std::endl;

	db.Close();*/


	/*Excel ExcelHelper;

	ExcelHelper.Load(String(_T("D:\\软件参数对照表.xlsx")));

	IExcel::AlterType Value0;

	ExcelHelper.GetCell(0, 0, Value0);

	IExcel::AlterType Value;

	ExcelHelper.GetCell(3, 0, Value);

	_bstr_t strValue = Value.bstrVal;

	String strFinalValue = std::string(strValue);

	ExcelHelper.GetCell(40, 0, Value);

	_bstr_t strValue2 = Value.bstrVal;

	String strFinalValue2 = std::string(strValue2);

	ExcelHelper.GetCell(1, 1, Value);

	Int32 iValue = (Int32)Value.dblVal;

	ExcelHelper.GetCell(-1, 1, Value);

	ExcelHelper.GetCell(0, 1999999, Value);

	_bstr_t strValue3 = Value.bstrVal;

	String strFinalValue3 = std::string(strValue3);*/

	/*Excel MyExcel;

	if (!MyExcel.Load(String(_T("D:\\78.csv"))))
	{
		std::cout << MyExcel.GetErrorMsg().ToANSIData() << std::endl;

		return -1;
	}

	if (!MyExcel.SetWorkSheet(0))
	{
		std::cout << MyExcel.GetErrorMsg().ToANSIData() << std::endl;

		return -1;
	}

	for (int iRowIndex = 0; iRowIndex < 4; iRowIndex++)
	{
		for (int iColIndex = 0; iColIndex < 4; iColIndex++)
		{
			Excel::AlterType CellData;

			if (!MyExcel.GetCell(iRowIndex, iColIndex, CellData))
			{
				std::cout << MyExcel.GetErrorMsg().ToANSIData() << std::endl;

				return -1;
			}

			String strData;

			if ((iRowIndex == 1 && iColIndex == 1)
				|| (iRowIndex == 1 && iColIndex == 3))
			{
				Double dValue = CellData.dblVal;

				strData = dValue.ToString();
			}
			else if (iRowIndex == 3 && iColIndex == 2)
			{
				Bool bValue = CellData.boolVal;

				strData = bValue.ToString();
			}
			else
			{
				strData = CellData.bstrVal;
			}

			std::cout << strData.ToANSIData() << std::endl;
		}
	}

	if (!MyExcel.WriteCell(0, 2, String(_T("testYou")), false))
	{
		std::cout << MyExcel.GetErrorMsg().ToANSIData() << std::endl;

		return -1;
	}

	if (!MyExcel.WriteCell(1, 2, true, false))
	{
		std::cout << MyExcel.GetErrorMsg().ToANSIData() << std::endl;

		return -1;
	}

	MyExcel.Save(String(_T("E:\\78.csv")));*/

	/*String strDocContent;

	{
		Word MyWord;

		if (!MyWord.Load(String(_T("E:\\88.docx"))))
		{
			std::cout << MyWord.GetErrorMsg().ToANSIData() << std::endl;

			return -1;
		}

		SByte Data[1024] = { 0 };

		if (!MyWord.GetDoc(strDocContent))
		{
			std::cout << MyWord.GetErrorMsg().ToANSIData() << std::endl;

			return -1;
		}

		std::cout << strDocContent.ToANSIData() << std::endl;
	}

	Word MyWord2;
	
	if (!MyWord2.Load(String(_T("E:\\77-3.时间轴黑红色块商务风.docx"))))
	{
		std::cout << MyWord2.GetErrorMsg().ToANSIData() << std::endl;

		return -1;
	}

	if (!MyWord2.WriteDoc(String("Account"),String("Customer"),strDocContent))
	{
		std::cout << MyWord2.GetErrorMsg().ToANSIData() << std::endl;

		return -1;
	}

	MyWord2.Save(String(_T("E:\\991.docx")));*/

	/*DateTime Time1;

	File::GetCreatedTime(String(_T("E:\\others")), Time1);

	String strTime1 = Time1.ToString();

	std::cout << strTime1.ToANSIData() << std::endl;*/

	//LOG_DEBUG(_T("Hello you"), _T(""));

	//String strData = String(std::string("我在吃饭啊"));

	//std::cout << strData.ToANSIData() << std::endl;

	//Bool bRet = true;

	//std::cout << bRet.ToString().ToANSIData() << std::endl;

	//Array<Int> CArr(2);

	//CArr[0] = 190;

	//CArr[1] = 12;

	//for (Int index = 0; index < 2; ++index)
	//{
	//	std::cout << CArr[index].ToString().ToANSIData() << std::endl;
	//}

	//DateTime CurTime = DateTime::Now();
	//
	//Int iCurTime = static_cast<Int32>(CurTime.ToTime_t());

	//DateTime Time = DateTime::FromString(String(_T("2020-04-25 12:12:43")));

	//DateTime Time2 = DateTime::FromTime_t(iCurTime);

	//std::cout << Time2.ToString().ToANSIData() << std::endl;

	//std::cout << Time.ToString().ToANSIData() << std::endl;

	//std::cout << CurTime.ToString().ToANSIData() << std::endl;

	//std::cout << iCurTime.ToString().ToANSIData() << std::endl;

	//String strCurExePath = Directory::GetExcutableDirectory();

	//std::cout << strCurExePath.ToANSIData() << std::endl;

	//String strCurExePath1 = Directory::TrimEnding(Directory::GetExcutableDirectory());

	//std::cout << strCurExePath1.ToANSIData() << std::endl;

	//String strCurExePath2 = Directory::AddEnding(strCurExePath1);

	//std::cout << strCurExePath2.ToANSIData() << std::endl;
	//
	//Directory::DirectoryTable Table;

	//Directory::GetAllSubDir(String(_T("D:\\TangYingZhong\\TANG_CODE_COLLECTION\\ShareLib")),Table);

	//for (Int index = 0; index < static_cast<int>(Table.size()); index++)
	//{
	//	std::cout << Table[index].ToANSIData() << std::endl;
	//}

	//Directory::FileTable FileTable1;

	//Directory::GetAllFiles(String(_T("D:\\TangYingZhong\\TANG_CODE_COLLECTION\\ShareLib")), FileTable1);

	//for (Int index = 0; index < static_cast<int>(FileTable1.size()); index++)
	//{
	//	std::cout << FileTable1[index].ToANSIData() << std::endl;
	//}

	///*{
	//	std::string strUtf8Data = "我始终托人";
	//	
	//	File FileHelper;

	//	if (!FileHelper.Open(String(_T("D:\\A.txt")), File::FileMode::OPENORCREATE, File::FileAccess::READWRITE))
	//	{
	//		std::cout << "Failed to open file" << std::endl;

	//		return -1;
	//	}

	//	Int32 iRet = FileHelper.Write(strUtf8Data.c_str(), 0, strUtf8Data.length());
	//	if (iRet != strUtf8Data.length())
	//	{
	//		std::cout << "Failed to write file" << std::endl;

	//		return -2;
	//	}

	//	FileHelper.Close();
	//}*/

	///*{
	//	File FileHelper;

	//	if (!FileHelper.Open(String(_T("D:\\B.txt")), File::FileMode::OPEN, File::FileAccess::READ))
	//	{
	//		std::cout << "Failed to open file" << std::endl;

	//		return -1;
	//	}

	//	char Respond[1024] = { 0 };

	//	Int32 iRet = FileHelper.Read(Respond, 0, 1024);

	//	FileHelper.Close();

	//	std::string strUtf8Data = Respond;

	//	String strFinalData = String(strUtf8Data,ENCODE_UTF8);

	//	std::cout << strFinalData.ToANSIData() << std::endl;
	//}*/

	//JsonDocument JsonDoc;

	//JsonDoc.SetKeyValue(String(_T("A")), String(_T("老夫大人")));

	//JsonDoc.SetKeyValue(String(_T("B")), true);

	//JsonDoc.SetKeyValue(String(_T("C")), 78.90);

	//JsonDoc.SetKeyValue(String(_T("D")), 78);

	//JsonDocument JsonDoc1;

	//JsonDoc1.SetKeyValue(String(_T("SD")), 78);

	//JsonDocument JsonDoc2;

	//JsonDoc2.Append(90);

	//JsonDoc2.Append(78);

	//JsonDoc2.Append(9.7);

	//JsonDoc1.SetKeyValue(String(_T("Array")), JsonDoc2);

	//JsonDoc.SetKeyValue(String(_T("Inner Configure")),JsonDoc1);

	//String strJson = JsonDoc.ToJson();

	//JsonDoc.Flush(String(_T("D:\\Json.txt")));

	//{
	//	JsonDocument JsonDoc = JsonDocument::FromJsonFile(String(_T("D:\\Json.txt")));

	//	String strJsonData = JsonDoc.GetKeyValue(String(_T("A"))).ToString();

	//	std::cout << strJsonData.ToANSIData() << std::endl;

	//	Int iSd = JsonDoc.GetKeyValue(String(_T("Inner Configure"))).GetKeyValue(String(_T("SD"))).ToInt();

	//	std::cout << iSd.ToString().ToANSIData() << std::endl;

	//	Bool bRet = JsonDoc.IsContain(String(_T("C")));

	//	std::cout << bRet.ToString().ToANSIData() << std::endl;
	//}

	/*{
		GeneralPlayer Player;

		Player.Load(String(_T("D:\\aa.wav")));
	
		while (Player.Play())
		{
			FixedInt32 iEventCode = 0;

			if (Player.WaitForCompletion(0,&iEventCode))
			{
				std::cout << "I am finishing playing" << std::endl;

				break;
			}

			std::cout << "I am playing" << std::endl;
		}

		Player.Stop();

		std::cout << "I have stopped playing" << std::endl;
	}*/

	/*{
		AudioPlayer Player;

		Player.Play(String(_T("D:\\aa.wav")));

		Player.Stop();
	}*/

	/*SocketClient Client(String(_T("192.168.1.2")),8080);

	Client.Start();

	String strData2 = String(_T("we are the world"));

	Client.Send((char*)strData2.ToANSIData().c_str(), 0, strData2.GetLength());

	char RecvData[1024] = {0};

	Client.Receive(RecvData, 0, 1024);

	std::cout << RecvData << std::endl;

	Client.Stop();*/

	/*SocketServer Server(8080,19);

	Server.Start();

	Socket client;

	if (Server.Accept(client))
	{
		String strData2 = String(_T("we are the world"));

		Server.Send(&client, (char*)strData2.ToANSIData().c_str(), 0, strData2.GetLength());

		char RecvData[1024] = { 0 };

		Server.Receive(&client, RecvData, 0, 1024);

		std::cout << RecvData << std::endl;
	}

	Server.Stop();*/

	return 0;
}
