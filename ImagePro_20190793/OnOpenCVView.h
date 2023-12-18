#pragma once
#include "afxdialogex.h"


// OnOpenCVView 대화 상자

class OnOpenCVView : public CDialogEx
{
	DECLARE_DYNAMIC(OnOpenCVView)

public:
	OnOpenCVView(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~OnOpenCVView();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OPENCV };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
