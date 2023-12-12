
// imageProc_20190834Doc.cpp: CimageProc20190834Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "imageProc_20190834.h"
#endif

#include "imageProc_20190834Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CimageProc20190834Doc

IMPLEMENT_DYNCREATE(CimageProc20190834Doc, CDocument)

BEGIN_MESSAGE_MAP(CimageProc20190834Doc, CDocument)
END_MESSAGE_MAP()


// CimageProc20190834Doc 생성/소멸

CimageProc20190834Doc::CimageProc20190834Doc() noexcept
{
	inputImg = NULL;
	inputImg2 = NULL;
	ResultImg = NULL;

	gResultImage = NULL;
	

}

CimageProc20190834Doc::~CimageProc20190834Doc()
{
	int i;

	if (inputImg != NULL)
	{
		for (i = 0; i < ImageHeight; i++)
			free(inputImg[i]);
		free(inputImg);
	}
	if (inputImg2 != NULL)
	{
		for (i = 0; i < ImageHeight; i++)
			free(inputImg2[i]);
		free(inputImg2);
	}
	if (ResultImg != NULL)
	{
		for (i = 0; i < ImageHeight; i++)
			free(ResultImg[i]);
		free(ResultImg);
	}

	if (gResultImage != NULL)
	{
		for (i = 0; i < gImageHeight; i++)
			free(gResultImage[i]);
		free(gResultImage);
	}
}

BOOL CimageProc20190834Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CimageProc20190834Doc serialization

void CimageProc20190834Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		LoadImageFile(ar);
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CimageProc20190834Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
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
void CimageProc20190834Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CimageProc20190834Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CimageProc20190834Doc 진단

#ifdef _DEBUG
void CimageProc20190834Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CimageProc20190834Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CimageProc20190834Doc 명령


int CimageProc20190834Doc::LoadImageFile(CArchive& ar)
{
	int maxValue, i;
	char type[16], buf[256];
	CFile *fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	bool isbmp = false;

	if(strcmp(strchr(fname,'.'), ".ppm")==0 ||
		strcmp(strchr(fname, '.'), ".PPM") == 0 || 
		strcmp(strchr(fname, '.'), ".pgm") == 0 || 
		strcmp(strchr(fname, '.'), ".PGM") == 0)
	{
		ar.ReadString(type, 15); //P5
		do{
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &ImageWidth, &ImageHeight);

		//P5
		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d ", &maxValue);

		if (strcmp(type, "P5") == 0) depth = 1;
		else depth = 3;

	}
	else if (strcmp(strchr(fname, '.'), ".bmp") == 0 || strcmp(strchr(fname, '.'), ".BMP") == 0)
	{
		//bitmap file header 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));

		//bmp 파일임을 나타내는 "BM"마커가 있는지 확인
		if(bmfh.bfType != (WORD)(('M' << 8) | 'B'))  return 0;

		//bitmap info header 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));

		ImageWidth = bih.biWidth;
		ImageHeight = bih.biHeight;
		depth = bih.biBitCount / 8;

		//palette 처리
		if (depth == 1)
		{  //palette 존재
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}
		isbmp = true;
	}
	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256)
		{
			AfxMessageBox("256*256크기의 파일만 읽을 수 있습니다.");
			return 0;
		}
		ImageWidth = 256;
		ImageHeight = 256;
		depth = 1;
	}

	//메모리 할당
	inputImg = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));
	ResultImg = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));

	for (i=0; i < ImageHeight; i++) 
	{
		inputImg[i] = (unsigned char*)malloc(ImageWidth * depth);
		ResultImg[i] = (unsigned char*)malloc(ImageWidth * depth);
	}

	//영상데이터 읽기
	for (i = 0; i < ImageHeight; i++)
	{
		ar.Read(inputImg[i], ImageWidth * depth);
	}

	if (!isbmp)
	{
		// 파일에서 읽어서 저장
		for (i = 0; i < ImageHeight; i++)
			ar.Read(inputImg[i], ImageWidth * depth);
	}
	else
	{
		// 파일에서 읽어서 저장
		BYTE nu[4];
		int widthfile;
		widthfile = (ImageWidth * 8 + 31) / 32 * 4;
		for (i = 0; i < ImageHeight; i++)
		{
			if (depth == 1)
				ar.Read(inputImg[ImageHeight - 1 - i], ImageWidth * depth);
			else
			{
				for (int j = 0; j < ImageWidth; j++)
				{
					BYTE r, g, b;
					ar.Read(&b, 1);     ar.Read(&g, 1);     ar.Read(&r, 1);
					inputImg[ImageHeight - 1 - i][3 * j + 0] = r;
					inputImg[ImageHeight - 1 - i][3 * j + 1] = g;
					inputImg[ImageHeight - 1 - i][3 * j + 2] = b;
				}
			}

			if ((widthfile - ImageWidth) != 0)
				ar.Read(nu, (widthfile - ImageWidth) * depth);
		}


	}



	return 0;
}

void CimageProc20190834Doc::LoadSecondImageFile(CArchive& ar)
{
	int w, h, d;
	int maxValue, i;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	bool isbmp = false;

	if (strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strchr(fname, '.'), ".pgm") == 0 || strcmp(strchr(fname, '.'), ".PGM") == 0)
	{
		ar.ReadString(type, 15);

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf(buf, "%d %d", &w, &h);

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0) d = 1;
		else d = 3;
	}
	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), "RAW") == 0)
	{
		w = 256;
		h = 256;
		d = 1;
	}
	else if (strcmp(strchr(fname, '.'), ".bmp") == 0 || strcmp(strchr(fname, '.'), ".BMP") == 0)
	{
		//bitmap file header 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));
		//bmp 파일임을 나타내는 "BM"마커가 있는지 확인
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B'))  return;

		//bitmap info header 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));
		w = bih.biWidth;
		h = bih.biHeight;
		d = bih.biBitCount / 8;

		//palette 처리
		if (d == 1)
		{  //palette 존재
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}
		isbmp = true;
	}
	if (ImageWidth != w || ImageHeight != h || depth != d)
	{
		AfxMessageBox("두번째 파일의 width, height, depth가 다르면 읽을 수 없습니다.");
		return;
	}
	//메모리 할당
	inputImg2 = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));

	for (i = 0; i < ImageHeight; i++)
	{
		inputImg2[i] = (unsigned char*)malloc(ImageWidth * depth);
	}
	//영상데이터 읽기
	for (i = 0; i < ImageHeight; i++)
	{
		ar.Read(inputImg2[i], ImageWidth * depth);
	}

	if (!isbmp)
	{
		//파일에서 읽어서 저장
		for (i = 0; i < ImageHeight; i++)
			ar.Read(inputImg2[i], ImageWidth * depth);
	}
	else {
		//파일에서 읽어서 저장
		BYTE nu[4];
		int widthfile;

		widthfile = (ImageWidth * 8 + 31) / 32 * 4;

		for (i = 0; i < ImageHeight; i++)
		{
			if (depth == 1)
				ar.Read(inputImg2[ImageHeight - 1 - i], ImageWidth * depth);
			else
			{
				for (int j = 0; j < ImageWidth; j++)
				{
					// BGE->RGB
					BYTE r, g, b;
					ar.Read(&b, 1); ar.Read(&g, 1); ar.Read(&r, 1);
					inputImg2[ImageHeight - 1 - i][3 * j + 0] = r;
					inputImg2[ImageHeight - 1 - i][3 * j + 1] = g;
					inputImg2[ImageHeight - 1 - i][3 * j + 2] = b;
				}
			}

			if ((widthfile - ImageWidth) != 0) {
				ar.Read(nu, (widthfile - ImageWidth) * depth);
			}
		}
	}
	return;
	
}

