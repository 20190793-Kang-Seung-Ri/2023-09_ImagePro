// OnOpenCVView.cpp: 구현 파일
//

#include "pch.h"
#include "ImagePro_20190793.h"
#include "afxdialogex.h"
#include "OnOpenCVView.h"


// OnOpenCVView 대화 상자

IMPLEMENT_DYNAMIC(OnOpenCVView, CDialogEx)

OnOpenCVView::OnOpenCVView(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_OPENCV, pParent)
{

}

OnOpenCVView::~OnOpenCVView()
{
}

void OnOpenCVView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(OnOpenCVView, CDialogEx)
END_MESSAGE_MAP()


// OnOpenCVView 메시지 처리기
