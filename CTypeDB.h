#pragma once

#include "afxdialogex.h"
#include <locale.h>
#include "pch.h"
#include "framework.h"
#include "Termp.h"
#include "TermpDlg.h"


using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

struct SCharInfo
{
	CString m_char;
	int m_type, m_sheet, m_sx, m_sy, m_line, m_order, m_width, m_height;
};

class CTypeDB
{
public:
	int m_nSheet; 
	int m_nChar = m_Chars.GetSize();
	CArray<SCharInfo*, SCharInfo*> m_Chars;
	inline BOOL ReadCSVFile(CString filename);
};



BOOL CTypeDB::ReadCSVFile(CString filename)
{

	if (filename == _T("C:\\Users\\����\\Desktop\\����õ������ �ǻ�\\typeDB.csv"))
	{
		_tsetlocale(LC_ALL, "Korean");

		CString strFilePath = _T("");
		strFilePath.Format(filename);

		//"D:\\programing\\����õ������ �ǻ�\\typeDB.csv"
		FILE* fp = NULL;
		fopen_s(&fp, strFilePath, "r");
		if (fp)
		{
			char szContent[2048] = { 0, };
			memset(szContent, NULL, 2048);

			while (fgets(szContent, 2048, fp))
			{
				CString strContent;
				strContent.Format("%s", szContent);
				memset(szContent, NULL, 2048);

				if (strContent.Find("#") >= 0) //���� csv ���� ���� ������ �� #�� ������ �ǳ� �پ��
					continue;
				if (strContent.Find("char") >= 0)
					continue;

				strContent.Remove('\r');
				strContent.Remove('\n');

				strContent = _T(strContent); //�����ڵ� ��ȯ�Ͽ� ����
				SCharInfo* pSCharInfo = new SCharInfo;
				CString rString;
				int nSubString = 0;

				while (AfxExtractSubString(rString, strContent, nSubString++, ','))
				{
					switch (nSubString)
					{
					case 1: pSCharInfo->m_char = _T(rString); break;

					case 2: pSCharInfo->m_type = _ttoi(rString); break;

					case 3: pSCharInfo->m_sheet = _ttoi(rString); break;

					case 4: pSCharInfo->m_sx = _ttoi(rString); break;

					case 5: pSCharInfo->m_sy = _ttoi(rString); break;

					case 6: pSCharInfo->m_line = _ttoi(rString); break;

					case 7: pSCharInfo->m_order = _ttoi(rString); break;

					case 8: pSCharInfo->m_width = _ttoi(rString); break;

					case 9: pSCharInfo->m_height = _ttoi(rString); break;
					}
				}
				m_Chars.Add(pSCharInfo);
			}
			fclose(fp);
		}

		return TRUE;
	}
	else
		return FALSE;
}