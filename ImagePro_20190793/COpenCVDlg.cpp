// COpenCVDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImagePro_20190793.h"
#include "afxdialogex.h"
#include "COpenCVDlg.h"

#include <opencv2/opencv.hpp>


// COpenCVDlg 대화 상자

IMPLEMENT_DYNAMIC(COpenCVDlg, CDialogEx)

COpenCVDlg::COpenCVDlg(CWnd* pParent /*=nullptr*/) : CDialogEx(IDD_DIALOG_OPENCV, pParent) {

}

COpenCVDlg::~COpenCVDlg() {}

void COpenCVDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COpenCVDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FILE_SELECT, &COpenCVDlg::OnBnClickedButtonFileSelect)
	ON_BN_CLICKED(IDC_BUTTON_MOVIE, &COpenCVDlg::OnBnClickedButtonMovie)
	ON_BN_CLICKED(IDC_BUTTON_CAMERA, &COpenCVDlg::OnBnClickedButtonCamera)
END_MESSAGE_MAP()


// COpenCVDlg 메시지 처리기


void COpenCVDlg::OnBnClickedButtonFileSelect() {
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CFileDialog dlg(true, "", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "JPG 파일(*.jpg)|*.jpg|모든 파일|(*.*)|*.*");
	CFileDialog dlg(true, "", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "AVI 파일(*.avi)|*.avi|모든 파일|(*.*)|*.*");

	if (dlg.DoModal() == IDOK) {
		cv::VideoCapture cap; //((LPSTR) (LPCTSTR) dlg.GetPathName());

		cap.open((LPSTR) (LPCTSTR) dlg.GetPathName());

		cv::Mat frame;

		while (1) {
			//frame = cv::imread((LPSTR) (LPCTSTR) dlg.GetPathName(), 1);
			cap.read(frame);

			if (frame.empty()) {//재생종료 or 재생 불가
				break;
			}

			cv::imshow("video", frame);
			if (cv::waitKey(30) == 'q') {
				break;
			}

			cv::destroyWindow("video");
		}
	}
}


void COpenCVDlg::OnBnClickedButtonMovie() {
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void COpenCVDlg::OnBnClickedButtonCamera() {
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	cv::VideoCapture cap(0);

	cv::Mat frame;

	while (1) {
		//frame = cv::imread((LPSTR) (LPCTSTR) dlg.GetPathName(), 1);
		cap.read(frame);

		if (frame.empty()) {//재생종료 or 재생 불가
			break;
		}

		cv::imshow("camera", frame);
		if (cv::waitKey(30) == 'q') {
			break;
		}

		cv::destroyWindow("camera");
	}
}
