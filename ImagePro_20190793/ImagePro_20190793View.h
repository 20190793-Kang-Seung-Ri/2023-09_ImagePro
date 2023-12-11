
// ImagePro_20190793View.h: CImagePro20190793View 클래스의 인터페이스
//

#pragma once


class CImagePro20190793View : public CScrollView {
protected: // serialization에서만 만들어집니다.
	CImagePro20190793View() noexcept;
	DECLARE_DYNCREATE(CImagePro20190793View)

	// 특성입니다.
public:
	CImagePro20190793Doc* GetDocument() const;

	// 작업입니다.
public:

	// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 구현입니다.
public:
	virtual ~CImagePro20190793View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	bool bAviMode;
	CString AVIFileName;
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelSub();
	afx_msg void OnPixelMul();
	afx_msg void OnPixelDiv();
	afx_msg void OnPixelHistoEq();
	afx_msg void OnPixelContrastStretching();
	afx_msg void OnPixelBinarization();
	afx_msg void OnPixelTwoImageAdd();
	afx_msg void OnPixelTwoImageSub();
	afx_msg void OnRegionMeaning();
	void convolve(unsigned char** inimg, unsigned char** outimg, int cols, int rows, float mask[3][3], int bias, int depth);
	afx_msg void OnRegionSharpening();
	afx_msg void OnRegionEmbossing();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionRoberts();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionAverageFiltering();
	afx_msg void OnRegionMedianFiltering();
	afx_msg void OnMopologyColorToGray();
	afx_msg void OnMopologyGrayToBinary();
	afx_msg void OnMopologyErosion();
	afx_msg void OnMopologyDilation();
	void CopyResultToInput();
	afx_msg void OnMopologyOpening();
	afx_msg void OnMopologyClosing();
	afx_msg void OnGeometryZoominPixelCopy();
	afx_msg void OnGeometryZoominBilinearInterpolation();
	afx_msg void OnGeometryZoomoutSubsampling();
	afx_msg void OnGeometryZoomoutMeanSub();
	afx_msg void OnGeometryAvgSampling();
	afx_msg void OnGeometryRotation();
	afx_msg void OnGeometryMirror();
	afx_msg void OnGeometryFlip();
	afx_msg void OnGeometryWarping();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnAviPrint();
	void LoadAviFile(CDC* pDC);
	afx_msg void OnGeometryMorping();
};

#ifndef _DEBUG  // ImagePro_20190793View.cpp의 디버그 버전
inline CImagePro20190793Doc* CImagePro20190793View::GetDocument() const
{
	return reinterpret_cast<CImagePro20190793Doc*>(m_pDocument);
}
#endif

