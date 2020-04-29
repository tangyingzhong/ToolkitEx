///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// You can use it to operate excel without installing excel on your computer
///</describe>
/// <date>2019/11/21</date>
///***********************************************************************
#ifndef EXCEL_H
#define EXCEL_H

#include "IExcel.h"

namespace System
{
	namespace Office
	{
		class Excel :public IExcel
		{
		public:
			typedef Book* ExcelBook;
			typedef Sheet* ExcelSheet;
			typedef Format* ExcelFormat;
			typedef libxl::Font* ExcelFont;
	
		public:
			// Construct the Excel
			Excel();

			// Detructe the Excel
			~Excel();

		private:
			// Forbid the copy Excel
			Excel(const Excel& other){	}

			// Forbid the assigment of Excel
			Excel& operator=(const Excel& other){	}

		public:
			// Load the excel
			virtual Boolean Load(String strExcelFilePath);

			// Set the current active sheet
			virtual Boolean SetWorkSheet(Int32 iIndex);

			// Get the cell value
			virtual Boolean GetCell(Int32 iRowIndex, Int32 iColumnIndex, AlterType& AlterValue);

			// Get a column data
			virtual Boolean GetColumn(Int32 iColIndex, ColumnTable& CTable);

			// Get a row data
			virtual Boolean GetRow(Int32 iRowIndex, RowTable& RTable);

			// Set cell's format
			virtual None SetCellAlign(AlignHEnum eAlignH, AlignVEnum eAlignV);

			// Set cell's font
			virtual None SetCellFont(FontColorEnum eColor, Boolean bIsFontBold);

			// Get the column with
			virtual Boolean GetColumnWidth(Int32 iColumnIndex, Real& dWidth);

			// Set column's width
			virtual Boolean SetColumnWidth(Int32 iColumnIndex, Int32 iWidth);

			// Get the row height
			virtual Boolean GetRowHeight(Int32 iRowIndex, Real& dHeight);

			// Set row's height
			virtual Boolean SetRowHeight(Int32 iRowIndex, Int32 iHeight);

			// Write a cell
			virtual Boolean WriteCell(Int32 iRowIndex,
				Int32 iColumnIndex,
				String strValue,
				Boolean bIsUseCellFormat);

			// Write a cell
			virtual Boolean WriteCell(Int32 iRowIndex,
				Int32 iColumnIndex,
				Int32 iValue,
				Boolean bIsUseCellFormat);

			// Write a cell
			virtual Boolean WriteCell(Int32 iRowIndex,
				Int32 iColumnIndex,
				Real dValue,
				Boolean bIsUseCellFormat);

			// Write a cell
			virtual Boolean WriteCell(Int32 iRowIndex,
				Int32 iColumnIndex,
				Boolean bValue,
				Boolean bIsUseCellFormat);

			// Write a cell
			virtual Boolean WriteCellByFormula(Int32 iRowIndex,
				Int32 iColumnIndex,
				String strFormula,
				Boolean bIsUseCellFormat);

			// Save the excel
			virtual Boolean Save(String strExcelFileName);

			// Get the error message
			virtual String GetErrorMsg();

		private:
			// Initialize the Excel
			None Initialize();

			// Destory the Excel
			None Destory();

			// Create a book
			None CreateBook();

			// Destory the book
			None DestoryBook();

			// Release the excel
			None Release();

		private:
			// Get the Format
			inline ExcelFormat GetFormat() const
			{
				return m_pFormat;
			}

			// Set the Format
			inline None SetFormat(ExcelFormat pFormat)
			{
				m_pFormat = pFormat;
			}

			// Get the Font
			inline ExcelFont GetFont() const
			{
				return m_pFont;
			}

			// Set the Font
			inline None SetFont(ExcelFont pFont)
			{
				m_pFont = pFont;
			}

			// Get the Book
			inline ExcelBook GetBook() const
			{
				return m_pBook;
			}

			// Set the Book
			inline None SetBook(ExcelBook pBook)
			{
				m_pBook = pBook;
			}

			// Get the Sheet
			inline ExcelSheet GetSheet() const
			{
				return m_pSheet;
			}

			// Set the Sheet
			inline None SetSheet(ExcelSheet pSheet)
			{
				m_pSheet = pSheet;
			}

			// Get the IsClosed
			inline Boolean GetIsClosed() const
			{
				return m_bIsClosed;
			}

			// Set the IsClosed
			inline None SetIsClosed(Boolean bIsClosed)
			{
				m_bIsClosed = bIsClosed;
			}

			// Get the ErrorMessage
			inline String GetErrorMessage() const
			{
				return m_strErrorMessage;
			}

			// Set the ErrorMessage
			inline None SetErrorMessage(String strErrorMessage)
			{
				m_strErrorMessage = strErrorMessage;
			}

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

		private:
			// Excel book
			ExcelBook m_pBook;

			// Excel sheet
			ExcelSheet m_pSheet;

			// Current excel's font
			ExcelFont m_pFont;

			// Current excel format
			ExcelFormat m_pFormat;

			// Error message
			String m_strErrorMessage;

			// Is book closed
			Boolean m_bIsClosed;

			// Disposed status
			Boolean m_bDisposed;
		};
	}
}

#endif // EXCEL_H