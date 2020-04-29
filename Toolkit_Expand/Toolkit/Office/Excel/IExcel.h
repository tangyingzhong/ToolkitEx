///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Offering excel's functions 
///</describe>
/// <date>2019/11/21</date>
///***********************************************************************
#ifndef IEXCEL_H
#define IEXCEL_H

#include <comdef.h>
#include "Tool/Common/SystemType.h"
#include "Tool/BaseType/String.h"
#include "libxl.h"

using namespace System;
using namespace System::BasicType;
using namespace libxl;

namespace System
{
	namespace Office
	{
		class IExcel
		{
		public:
			typedef vector<String> HeadTable;
			typedef _variant_t AlterType;
			typedef vector<AlterType> ColumnTable;
			typedef ColumnTable RowTable;
			typedef AlignH AlignHEnum;
			typedef AlignV AlignVEnum;
			typedef Color FontColorEnum;

		public:
			// Detructe the IExcel
			virtual ~IExcel(){	}

		public:
			// Load the excel
			virtual Boolean Load(String strExcelFilePath) = 0;

			// Set the current active sheet
			virtual Boolean SetWorkSheet(Int32 iIndex) = 0;

			// Get the cell value
			virtual Boolean GetCell(Int32 iRowIndex,Int32 iColumnIndex,AlterType& AlterValue) = 0;

			// Get a column data
			virtual Boolean GetColumn(Int32 iColIndex, ColumnTable& CTable) = 0;

			// Get a row data
			virtual Boolean GetRow(Int32 iRowIndex,RowTable& RTable) = 0;

			// Set cell's format
			virtual None SetCellAlign(AlignHEnum eAlignH,AlignVEnum eAlignV) = 0;

			// Set cell's font
			virtual None SetCellFont(FontColorEnum eColor, Boolean bIsFontBold) = 0;

			// Get the column with
			virtual Boolean GetColumnWidth(Int32 iColumnIndex,Real& dWidth)=0;

			// Set column's width
			virtual Boolean SetColumnWidth(Int32 iColumnIndex, Int32 iWidth) = 0;

			// Get the row height
			virtual Boolean GetRowHeight(Int32 iRowIndex, Real& dHeight) = 0;

			// Set row's height
			virtual Boolean SetRowHeight(Int32 iRowIndex,Int32 iHeight) = 0;

			// Write a cell
			virtual Boolean WriteCell(Int32 iRowIndex,
				Int32 iColumnIndex,
				String strValue,
				Boolean bIsUseCellFormat) = 0;

			// Write a cell
			virtual Boolean WriteCell(Int32 iRowIndex,
				Int32 iColumnIndex,
				Int32 iValue,
				Boolean bIsUseCellFormat) = 0;

			// Write a cell
			virtual Boolean WriteCell(Int32 iRowIndex,
				Int32 iColumnIndex,
				Real dValue,
				Boolean bIsUseCellFormat) = 0;

			// Write a cell
			virtual Boolean WriteCell(Int32 iRowIndex,
				Int32 iColumnIndex,
				Boolean bValue,
				Boolean bIsUseCellFormat) = 0;

			// Write a cell. Such as "SUM(B5:B6)"
			virtual Boolean WriteCellByFormula(Int32 iRowIndex,
				Int32 iColumnIndex, 
				String strFormula,
				Boolean bIsUseCellFormat) = 0;

			// Save the excel
			virtual Boolean Save(String strExcelFileName) = 0;

			// Get the error message
			virtual String GetErrorMsg() = 0;
		};
	}
}

#endif // IEXCEL_H-