#ifndef __DOCXFACTORY_WORD_PROCESSING_MERGER_H__
#define __DOCXFACTORY_WORD_PROCESSING_MERGER_H__

#include <map>
#include <set>
#include <string>

namespace DocxFactory
{
	class WordProcessingMerger
	{
	public:
		static WordProcessingMerger& GetInstance();

		virtual ~WordProcessingMerger();

		bool	Load(const std::string& p_fileName);

		bool	Save(const std::string& p_fileName = "");

		bool	Print(const std::string& p_printerName, unsigned short p_copyCnt = 1);

		bool	Close();

		bool	Merge(const std::string& p_data);

		bool	SetChartValue(const std::string& p_itemName,
			const std::string& p_fieldName, 
			const std::string&	p_series, 
			const std::string&	p_category,
			double p_value);

		bool	SetChartValue(const std::string& p_itemName,
			const std::string& p_fieldName, 
			const std::string&	p_series, 
			double p_category,
			double p_value);

		bool	SetChartValue(const std::string& p_itemName, 
			const std::string& p_fieldName, 
			double p_series, 
			double p_category, 
			double p_value);

		bool	SetClipboardValue(const std::string& p_itemName, 
			const std::string& p_fieldName, 
			const std::string& p_value);

		bool	SetClipboardValue(const std::string& p_itemName, 
			const std::string& p_fieldName, 
			double p_value);

		bool	Paste(const std::string& p_itemName = "");

		bool	SetUpdateTocMethod(unsigned char p_method);

		unsigned char GetUpdateTocMethod() const;

		std::string	GetFields() const;

		std::string	GetItems() const;

		std::string	GetItemParent(const std::string& p_itemName) const;

		std::string	GetItemFields(const std::string& p_itemName) const;

		bool SetCodePage();

		bool SetCodePage(const std::string& p_codePage);

		bool SetNumFracSep(char p_frac = 0);

		bool SetNumThSep(char p_th = 0);

		bool SetDateFormat(const std::string& p_format = "");

		bool SetYearOffset(unsigned short p_year = 0);

		bool SetFirstWeekDay();

		bool SetFirstWeekDay(unsigned short p_weekday);

		bool SetWeekDayNames();

		bool SetWeekDayNames(
			const std::string& p_weekDay1,
			const std::string& p_weekDay2,
			const std::string& p_weekDay3,
			const std::string& p_weekDay4,
			const std::string& p_weekDay5,
			const std::string& p_weekDay6,
			const std::string& p_weekDay7);

		bool SetWeekDayNames(
			const std::string& p_fullName1,
			const std::string& p_fullName2,
			const std::string& p_fullName3,
			const std::string& p_fullName4,
			const std::string& p_fullName5,
			const std::string& p_fullName6,
			const std::string& p_fullName7,
			const std::string& p_shortName1,
			const std::string& p_shortName2,
			const std::string& p_shortName3,
			const std::string& p_shortName4,
			const std::string& p_shortName5,
			const std::string& p_shortName6,
			const std::string& p_shortName7);

		bool SetMonthNames();

		bool SetMonthNames(
			const std::string& p_month1,
			const std::string& p_month2,
			const std::string& p_month3,
			const std::string& p_month4,
			const std::string& p_month5,
			const std::string& p_month6,
			const std::string& p_month7,
			const std::string& p_month8,
			const std::string& p_month9,
			const std::string& p_month10,
			const std::string& p_month11,
			const std::string& p_month12);

		bool SetMonthNames(
			const std::string& p_fullName1,
			const std::string& p_fullName2,
			const std::string& p_fullName3,
			const std::string& p_fullName4,
			const std::string& p_fullName5,
			const std::string& p_fullName6,
			const std::string& p_fullName7,
			const std::string& p_fullName8,
			const std::string& p_fullName9,
			const std::string& p_fullName10,
			const std::string& p_fullName11,
			const std::string& p_fullName12,
			const std::string& p_shortName1,
			const std::string& p_shortName2,
			const std::string& p_shortName3,
			const std::string& p_shortName4,
			const std::string& p_shortName5,
			const std::string& p_shortName6,
			const std::string& p_shortName7,
			const std::string& p_shortName8,
			const std::string& p_shortName9,
			const std::string& p_shortName10,
			const std::string& p_shortName11,
			const std::string& p_shortName12);

		std::string 	GetCodePage();

		char 	GetNumFracSep();

		char GetNumThSep();

		std::string 	GetDateFormat();

		unsigned short 	GetYearOffset();

		unsigned short 	GetFirstWeekDay();

		std::string 	GetWeekDayFullNames();

		std::string	GetWeekDayShortNames();

		std::string	GetMonthFullNames();

		std::string	GetMonthShortNames();

		bool	SetTempDir();

		bool	SetTempDir(const std::string& p_dir);

		std::string	GetWorkDir() const;

		std::string	GetTempDir() const;

		std::string GetErrorMessage();

	private:
		WordProcessingMerger();

		WordProcessingMerger(const WordProcessingMerger& p_other);

		WordProcessingMerger& operator = (const WordProcessingMerger& p_other);

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

		private:
			std::string m_strErrorMsg;
	};
};

#endif
