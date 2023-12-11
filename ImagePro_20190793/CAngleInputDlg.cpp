// CAngleInputDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImagePro_20190793.h"
#include "afxdialogex.h"
#include "CAngleInputDlg.h"


// CAngleInputDlg 대화 상자

IMPLEMENT_DYNAMIC(CAngleInputDlg, CDialogEx)

CAngleInputDlg::CAngleInputDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent), m_iAngle(0)
{

}

CAngleInputDlg::~CAngleInputDlg()
{
}

void CAngleInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iAngle);
}


BEGIN_MESSAGE_MAP(CAngleInputDlg, CDialogEx)
END_MESSAGE_MAP()


// CAngleInputDlg 메시지 처리기
