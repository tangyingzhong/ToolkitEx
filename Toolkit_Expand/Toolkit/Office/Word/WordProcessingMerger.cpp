#include "WordProcessingMerger.h"
#include "dfw.h"
#include <stdexcept>

using namespace DocxFactory;

WordProcessingMerger& WordProcessingMerger::GetInstance()
{
	static WordProcessingMerger s_instance;

	return s_instance;
} 

WordProcessingMerger::WordProcessingMerger()
{

}

WordProcessingMerger::~WordProcessingMerger()
{

}

bool WordProcessingMerger::Load( const std::string& p_fileName )
{
	dfw_load( p_fileName.c_str() );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::Save( const std::string& p_fileName )
{
	dfw_save( p_fileName.c_str() );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::Print(const std::string& p_printerName, unsigned short p_copyCnt)
{
	dfw_print( p_printerName.c_str(), p_copyCnt );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::Close()
{
	dfw_close();

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::Merge(const std::string& p_data)
{
	dfw_merge( p_data.c_str() );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::SetChartValue(const std::string& p_itemName,
	const std::string& p_fieldName,
	const std::string&	p_series,
	const std::string&	p_category,
	double p_value)
{
	dfw_setChartValueByStrStr( p_itemName.c_str(), 
		p_fieldName.c_str(), 
		p_series.c_str(), 
		p_category.c_str(), 
		p_value );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::SetChartValue(const std::string& p_itemName,
	const std::string& p_fieldName,
	const std::string&	p_series,
	double p_category,
	double p_value)
{
	dfw_setChartValueByStrDouble( p_itemName.c_str(), 
		p_fieldName.c_str(),
		p_series.c_str(), 
		p_category, 
		p_value );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::SetChartValue(const std::string& p_itemName,
	const std::string& p_fieldName,
	double p_series,
	double p_category,
	double p_value)
{
	dfw_setChartValueByDoubleDouble( p_itemName.c_str(), 
		p_fieldName.c_str(),
		p_series,
		p_category,
		p_value );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::SetClipboardValue(const std::string& p_itemName,
	const std::string& p_fieldName,
	const std::string& p_value)
{
	dfw_setClipboardValueByStr( p_itemName.c_str(), p_fieldName.c_str(), p_value.c_str() );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::SetClipboardValue(const std::string& p_itemName,
	const std::string& p_fieldName,
	double p_value)
{
	dfw_setClipboardValueByDouble( p_itemName.c_str(), p_fieldName.c_str(), p_value );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::Paste(const std::string& p_itemName)
{
	dfw_paste( p_itemName.c_str() );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::SetUpdateTocMethod(unsigned char p_method)
{
	dfw_setUpdateTocMethod( p_method );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

unsigned char WordProcessingMerger::GetUpdateTocMethod() const
{
	return dfw_getUpdateTocMethod();
}

std::string WordProcessingMerger::GetFields() const
{
	return dfw_getFields();
}

std::string WordProcessingMerger::GetItems() const
{
	return dfw_getItems();
}

std::string WordProcessingMerger::GetItemParent( const std::string& p_itemName ) const
{
	return dfw_getItemParent( p_itemName.c_str() );
}

std::string WordProcessingMerger::GetItemFields( const std::string& p_itemName ) const
{
	return dfw_getItemFields( p_itemName.c_str() );
}

bool WordProcessingMerger::SetCodePage()
{
	dfw_setCodePage( "" );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::SetCodePage( const std::string& p_codePage )
{
	dfw_setCodePage( p_codePage.c_str() );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::SetNumFracSep( char p_frac )
{
	dfw_setNumFracSep( p_frac );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::SetNumThSep(char p_th)
{
	dfw_setNumThSep( p_th );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::SetDateFormat( const std::string& p_format )
{
	dfw_setDateFormat( p_format.c_str() );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::SetYearOffset(unsigned short p_year)
{
	dfw_setYearOffset( p_year );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::SetFirstWeekDay()
{
	dfw_setFirstWeekDay(0);

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::SetFirstWeekDay(unsigned short p_weekday)
{
	dfw_setFirstWeekDay(p_weekday);

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::SetWeekDayNames()
{
	dfw_setWeekDayNames0();

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::SetWeekDayNames(
	const std::string& p_weekDay1,
	const std::string& p_weekDay2,
	const std::string& p_weekDay3,
	const std::string& p_weekDay4,
	const std::string& p_weekDay5,
	const std::string& p_weekDay6,
	const std::string& p_weekDay7 )
{
	dfw_setWeekDayNames7(
		p_weekDay1.c_str(),
		p_weekDay2.c_str(),
		p_weekDay3.c_str(),
		p_weekDay4.c_str(),
		p_weekDay5.c_str(),
		p_weekDay6.c_str(),
		p_weekDay7.c_str() );
		
	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::SetWeekDayNames(
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
	const std::string& p_shortName7 )
{
	dfw_setWeekDayNames14(
		p_fullName1.c_str(),
		p_fullName2.c_str(),
		p_fullName3.c_str(),
		p_fullName4.c_str(),
		p_fullName5.c_str(),
		p_fullName6.c_str(),
		p_fullName7.c_str(),
		p_shortName1.c_str(),
		p_shortName2.c_str(),
		p_shortName3.c_str(),
		p_shortName4.c_str(),
		p_shortName5.c_str(),
		p_shortName6.c_str(),
		p_shortName7.c_str() );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::SetMonthNames()
{
	dfw_setMonthNames0();

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::SetMonthNames(
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
	const std::string& p_month12 )
{
	dfw_setMonthNames12(
		p_month1.c_str(),
		p_month2.c_str(),
		p_month3.c_str(),
		p_month4.c_str(),
		p_month5.c_str(),
		p_month6.c_str(),
		p_month7.c_str(),
		p_month8.c_str(),
		p_month9.c_str(),
		p_month10.c_str(),
		p_month11.c_str(),
		p_month12.c_str() );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::SetMonthNames(
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
	const std::string& p_shortName12 )
{
	dfw_setMonthNames24(
		p_fullName1.c_str(),
		p_fullName2.c_str(),
		p_fullName3.c_str(),
		p_fullName4.c_str(),
		p_fullName5.c_str(),
		p_fullName6.c_str(),
		p_fullName7.c_str(),
		p_fullName8.c_str(),
		p_fullName9.c_str(),
		p_fullName10.c_str(),
		p_fullName11.c_str(),
		p_fullName12.c_str(),
		p_shortName1.c_str(),
		p_shortName2.c_str(),
		p_shortName3.c_str(),
		p_shortName4.c_str(),
		p_shortName5.c_str(),
		p_shortName6.c_str(),
		p_shortName7.c_str(),
		p_shortName8.c_str(),
		p_shortName9.c_str(),
		p_shortName10.c_str(),
		p_shortName11.c_str(),
		p_shortName12.c_str() );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

std::string WordProcessingMerger::GetCodePage()
{
	return dfw_getCodePage();
}

char WordProcessingMerger::GetNumFracSep()
{
	return dfw_getNumFracSep();
}

char WordProcessingMerger::GetNumThSep()
{
	return dfw_getNumThSep();
}

std::string WordProcessingMerger::GetDateFormat()
{
	return dfw_getDateFormat();
}

unsigned short WordProcessingMerger::GetYearOffset()
{
	return dfw_getYearOffset();
}

unsigned short WordProcessingMerger::GetFirstWeekDay()
{
	return dfw_getFirstWeekDay();
}

std::string WordProcessingMerger::GetWeekDayFullNames()
{
	return dfw_getWeekDayFullNames();
}

std::string WordProcessingMerger::GetWeekDayShortNames()
{
	return dfw_getWeekDayShortNames();
}

std::string WordProcessingMerger::GetMonthFullNames()
{
	return dfw_getMonthFullNames();
}

std::string WordProcessingMerger::GetMonthShortNames()
{
	return dfw_getMonthShortNames();
}

bool WordProcessingMerger::SetTempDir()
{
	dfw_setTempDir( "" );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

bool WordProcessingMerger::SetTempDir( const std::string& p_dir )
{
	dfw_setTempDir( p_dir.c_str() );

	if (dfw_getErrorFlag())
	{
		std::string strError = dfw_getErrorWhat();

		SetErrorMsg(strError);

		return false;
	}

	return true;
}

std::string WordProcessingMerger::GetWorkDir() const
{
	return dfw_getWorkDir();
}

std::string WordProcessingMerger::GetTempDir() const
{
	return dfw_getTempDir();
}

std::string WordProcessingMerger::GetErrorMessage()
{
	return GetErrorMsg();
}