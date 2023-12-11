
// ImagePro_20190793Doc.cpp: CImagePro20190793Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImagePro_20190793.h"
#endif

#include "ImagePro_20190793Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImagePro20190793Doc

IMPLEMENT_DYNCREATE(CImagePro20190793Doc, CDocument)

BEGIN_MESSAGE_MAP(CImagePro20190793Doc, CDocument)
END_MESSAGE_MAP()


// CImagePro20190793Doc 생성/소멸

CImagePro20190793Doc::CImagePro20190793Doc() noexcept {
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	inputImg = NULL;
	inputImg2 = NULL;

	resultImg = NULL;

	gResultImg = NULL;
}

CImagePro20190793Doc::~CImagePro20190793Doc() {
	if (inputImg != NULL) {
		for (int i = 0; i < imageHeight; i++) {
			free(inputImg[i]);
		}

		free(inputImg);
	}

	if (inputImg2 != NULL) {
		for (int i = 0; i < imageHeight; i++) {
			free(inputImg2[i]);
		}

		free(inputImg2);
	}

	if (resultImg != NULL) {
		for (int i = 0; i < imageHeight; i++) {
			free(resultImg[i]);
		}

		free(resultImg);
	}

	if (gResultImg != NULL) {
		for (int i = 0; i < gImageHeight; i++) {
			free(gResultImg[i]);
		}

		free(gResultImg);
	}
}

BOOL CImagePro20190793Doc::OnNewDocument() {
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImagePro20190793Doc serialization

void CImagePro20190793Doc::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {
		// TODO: 여기에 저장 코드를 추가합니다.
	} else {
		// TODO: 여기에 로딩 코드를 추가합니다.
		LoadImageFile(ar);
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImagePro20190793Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds) {
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImagePro20190793Doc::InitializeSearchContent() {
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImagePro20190793Doc::SetSearchContent(const CString& value) {
	if (value.IsEmpty()) {
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	} else {
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr) {
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImagePro20190793Doc 진단

#ifdef _DEBUG
void CImagePro20190793Doc::AssertValid() const {
	CDocument::AssertValid();
}

void CImagePro20190793Doc::Dump(CDumpContext& dc) const {
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImagePro20190793Doc 명령


void CImagePro20190793Doc::LoadImageFile(CArchive& ar) {
	// TODO: 여기에 구현 코드 추가.
	int maxValue;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	bool isbmp = false;

	if (strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0
		|| strcmp(strchr(fname, '.'), ".pgm") == 0 || strcmp(strchr(fname, '.'), ".PGM") == 0) {
		ar.ReadString(type, 15);

		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &imageWidth, &imageHeight);

		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0) {
			depth = 1;
		}
		else {
			depth = 3;
		}
	}
	else if (strcmp(strchr(fname, '.'), ".bmp") == 0 || strcmp(strchr(fname, '.'), ".BMP") == 0) {
		//bitmap file header 읽기
		BITMAPFILEHEADER bmfh;

		ar.Read((LPSTR)&bmfh, sizeof(bmfh));

		//bmp 화일임을 나타내는 "BM" 마커가 있는지 확인
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B')) {
			return;
		}

		//bitmap info header 읽기
		BITMAPINFOHEADER bmih;

		ar.Read((LPSTR)&bmih, sizeof(bmih));

		imageWidth = bmih.biWidth;
		imageHeight = bmih.biHeight;
		depth = bmih.biBitCount / 8;

		//palette 처리
		if (depth == 1) {
			//팔레트 존재
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}

		isbmp = true;
	}
	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0) {
		imageWidth = 256;
		imageHeight = 256;
		depth = 1;
	}

	inputImg = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));
	resultImg = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));

	for (int i = 0; i < imageHeight; i++) {
		inputImg[i] = (unsigned char*)malloc(imageWidth * depth);
		resultImg[i] = (unsigned char*)malloc(imageWidth * depth);
	}

	if (!isbmp) {
		for (int i = 0; i < imageHeight; i++) {
			ar.Read(inputImg[i], imageWidth * depth);
		}
	}
	else {
		BYTE nu[4 * 3];
		int widthfile;

		widthfile = (imageWidth * 8 + 31) / 32 * 4;

		for (int i = 0; i < imageHeight; i++) {
			if (depth == 1) {
				ar.Read(inputImg[imageHeight - 1 - i], imageWidth * depth);
			}
			else {
				BYTE r, g, b;

				for (int j = 0; j < imageWidth; j++) {
					ar.Read(&b, 1);
					ar.Read(&g, 1);
					ar.Read(&r, 1);
					inputImg[imageHeight - 1 - i][3 * j + 0] = r;
					inputImg[imageHeight - 1 - i][3 * j + 1] = g;
					inputImg[imageHeight - 1 - i][3 * j + 2] = b;
				}
			}

			if ((widthfile - imageWidth) != 0) {
				ar.Read(nu, (widthfile - imageWidth) * depth);
			}
		}
	}
}


void CImagePro20190793Doc::LoadSecondImageFile(CArchive& ar) {
	// TODO: 여기에 구현 코드 추가.
	int maxValue;
	int temp_w, temp_h, temp_d;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	bool isbmp = false;

	if (strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0
		|| strcmp(strchr(fname, '.'), ".pgm") == 0 || strcmp(strchr(fname, '.'), ".PGM") == 0) {
		ar.ReadString(type, 15);

		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &temp_w, &temp_h);

		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0) {
			temp_d = 1;
		}
		else {
			temp_d = 3;
		}
	}
	else if (strcmp(strchr(fname, '.'), ".bmp") == 0 || strcmp(strchr(fname, '.'), ".BMP") == 0) {
		//bitmap file header 읽기
		BITMAPFILEHEADER bmfh;

		ar.Read((LPSTR)&bmfh, sizeof(bmfh));

		//bmp 화일임을 나타내는 "BM" 마커가 있는지 확인
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B')) {
			return;
		}

		//bitmap info header 읽기
		BITMAPINFOHEADER bmih;

		ar.Read((LPSTR)&bmih, sizeof(bmih));

		temp_w = bmih.biWidth;
		temp_h = bmih.biHeight;
		temp_d = bmih.biBitCount / 8;

		//palette 처리
		if (depth == 1) {
			//팔레트 존재
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}

		isbmp = true;
	}
	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0) {
		temp_w = 256;
		temp_h = 256;
		temp_d = 1;
	}

	if (imageWidth != temp_w || imageHeight != temp_h || depth != temp_d) {
		AfxMessageBox("두번째 파일의 크기가 같지 않습니다");
		return;
	}

	inputImg2 = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));

	for (int i = 0; i < imageHeight; i++) {
		inputImg2[i] = (unsigned char*)malloc(imageWidth * depth);
	}

	if (!isbmp) {
		for (int i = 0; i < imageHeight; i++) {
			ar.Read(inputImg2[i], imageWidth * depth);
		}
	}
	else {
		BYTE nu[4 * 3];
		int widthfile;

		widthfile = (imageWidth * 8 + 31) / 32 * 4;

		for (int i = 0; i < imageHeight; i++) {
			if (depth == 1) {
				ar.Read(inputImg2[imageHeight - 1 - i], imageWidth * depth);
			}
			else {
				BYTE r, g, b;

				for (int j = 0; j < imageWidth; j++) {
					ar.Read(&b, 1);
					ar.Read(&g, 1);
					ar.Read(&r, 1);
					inputImg2[imageHeight - 1 - i][3 * j + 0] = r;
					inputImg2[imageHeight - 1 - i][3 * j + 1] = g;
					inputImg2[imageHeight - 1 - i][3 * j + 2] = b;
				}
			}

			if ((widthfile - imageWidth) != 0) {
				ar.Read(nu, (widthfile - imageWidth) * depth);
			}
		}
	}
}
