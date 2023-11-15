
// imageProc_20190834View.cpp: CimageProc20190834View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "imageProc_20190834.h"
#endif

#include "imageProc_20190834Doc.h"
#include "imageProc_20190834View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CimageProc20190834View

IMPLEMENT_DYNCREATE(CimageProc20190834View, CScrollView)

BEGIN_MESSAGE_MAP(CimageProc20190834View, CScrollView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_MENUTEXT, &CimageProc20190834View::OnMenutext)
	ON_COMMAND(ID_PIXEL_ADD, &CimageProc20190834View::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_SUB, &CimageProc20190834View::OnPixelSub)
	ON_COMMAND(ID_PIXEL_MUL, &CimageProc20190834View::OnPixelMul)
	ON_COMMAND(ID_PIXEL_DIV, &CimageProc20190834View::OnPixelDiv)
	ON_COMMAND(ID_PIXEL_HISTOEQ, &CimageProc20190834View::OnPixelHistoeq)
	ON_COMMAND(ID_PIXEL_CONSTRETCH, &CimageProc20190834View::OnPixelConstretch)
	ON_COMMAND(ID_PIXEL_BINARY, &CimageProc20190834View::OnPixelBinary)
	ON_COMMAND(ID_PIXEL_TWOIMAGEADD, &CimageProc20190834View::OnPixelTwoimageadd)
	ON_COMMAND(ID_PIXEL_TWOIMAGESUB, &CimageProc20190834View::OnPixelTwoimagesub)
	ON_COMMAND(ID_REGION_SHARPENING, &CimageProc20190834View::OnRegionSharpening)
	ON_COMMAND(ID_REGION_SMOOTHING, &CimageProc20190834View::OnRegionSmoothing)
	ON_COMMAND(ID_REGION_EMBOSSING, &CimageProc20190834View::OnRegionEmbossing)
	ON_COMMAND(ID_REGION_PREWITT, &CimageProc20190834View::OnRegionPrewitt)
	ON_COMMAND(ID_REGION_ROBERTS, &CimageProc20190834View::OnRegionRoberts)
	ON_COMMAND(ID_REGION_SOBEL, &CimageProc20190834View::OnRegionSobel)
	ON_COMMAND(ID_REGION_AVERAGE_FILLTERING, &CimageProc20190834View::OnRegionAverageFilltering)
	ON_COMMAND(ID_REGION_MEDIAN_FILTERING, &CimageProc20190834View::OnRegionMedianFiltering)
	ON_COMMAND(ID_MOPOLGY_COLORTOGREY, &CimageProc20190834View::OnMopolgyColortogrey)
	ON_COMMAND(ID_MOPOLOGY_BINERY, &CimageProc20190834View::OnMopologyBinery)
	ON_COMMAND(ID_MOPOLOGY_EROSION, &CimageProc20190834View::OnMopologyErosion)
	ON_COMMAND(ID_MOPOLOGY_DILATION, &CimageProc20190834View::OnMopologyDilation)
	ON_COMMAND(ID_MOPOLOGY_OPENING, &CimageProc20190834View::OnMopologyOpening)
	ON_COMMAND(ID_MOPOLOGY_CLOSING, &CimageProc20190834View::OnMopologyClosing)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CimageProc20190834View::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_INTERPOLATION, &CimageProc20190834View::OnGeometryZoominInterpolation)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUBSAMPLING, &CimageProc20190834View::OnGeometryZoomoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_MINSUB, &CimageProc20190834View::OnGeometryZoomoutMinsub)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_AVGSAM, &CimageProc20190834View::OnGeometryZoomoutAvgsam)
	ON_COMMAND(ID_GEOMETRY_ROTATION, &CimageProc20190834View::OnGeometryRotation)
END_MESSAGE_MAP()

// CimageProc20190834View 생성/소멸

CimageProc20190834View::CimageProc20190834View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CimageProc20190834View::~CimageProc20190834View()
{
}

BOOL CimageProc20190834View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CimageProc20190834View 그리기

void CimageProc20190834View::OnDraw(CDC* pDC)
{
	CimageProc20190834Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	if (pDoc->inputImg == NULL)
		return;
	
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int x, y;
	if (pDoc->inputImg != NULL)
	{
		if (pDoc->depth == 1)//흑백일 때
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][x], pDoc->inputImg[y][x], pDoc->inputImg[y][x]));
		}
		else { //컬러일 때
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][3*x+0], pDoc->inputImg[y][3*x+1], pDoc->inputImg[y][3*x+2]));
		}
	}
	if (pDoc->ResultImg != NULL)
	{
		if (pDoc->depth == 1)// 흑백일 때
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel( pDoc->ImageWidth + 20 + x, y, RGB(pDoc->ResultImg[y][x], pDoc->ResultImg[y][x], pDoc->ResultImg[y][x]));
		}
		else {
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(pDoc->ImageWidth  + 20 + x, y, RGB(pDoc->ResultImg[y][3 * x + 0], pDoc->ResultImg[y][3 * x + 1], pDoc->ResultImg[y][3 * x + 2]));
		}
	}
	if (pDoc->inputImg2 != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(pDoc->ImageWidth + 20 + x, y, RGB(pDoc->inputImg2[y][x], pDoc->inputImg2[y][x], pDoc->inputImg2[y][x]));
		}
		else {
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(pDoc->ImageWidth + 20 + x, y, RGB(pDoc->inputImg2[y][3 * x + 0], pDoc->inputImg2[y][3 * x + 1], pDoc->inputImg2[y][3 * x + 2]));
		}
	}

	if (pDoc->gResultImage != NULL)
	{
		if (pDoc->depth == 1)// 흑백일 때
		{
			for (y = 0; y < pDoc->gImageHeight; y++)
				for (x = 0; x < pDoc->gImageWidth; x++)
					pDC->SetPixel(x, pDoc->ImageHeight + 20 + y, RGB(pDoc->gResultImage[y][x], pDoc->gResultImage[y][x], pDoc->gResultImage[y][x]));
		}
		else {
			for (y = 0; y < pDoc->gImageHeight; y++)
				for (x = 0; x < pDoc->gImageWidth; x++)
					pDC->SetPixel(x, pDoc->ImageHeight + 20 + y, RGB(pDoc->gResultImage[y][3 * x + 0], pDoc->gResultImage[y][3 * x + 1], pDoc->gResultImage[y][3 * x + 2]));
		}
	}
}

void CimageProc20190834View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = 2048;
	sizeTotal.cy = 1024;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CimageProc20190834View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CimageProc20190834View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CimageProc20190834View 진단

#ifdef _DEBUG
void CimageProc20190834View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CimageProc20190834View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CimageProc20190834Doc* CimageProc20190834View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CimageProc20190834Doc)));
	return (CimageProc20190834Doc*)m_pDocument;
}
#endif //_DEBUG


// CimageProc20190834View 메시지 처리기


void CimageProc20190834View::OnMenutext()
{
	AfxMessageBox("안녕하세요 메뉴출력입니다");
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CimageProc20190834View::OnPixelAdd()
{
	CimageProc20190834Doc* pDoc = GetDocument();
	if (pDoc->inputImg == NULL) return;
	
	int x, y, value;
	for(y=0; y<pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1)
			{
				value = pDoc->inputImg[y][x] + 100;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][x] = value;
			}
			else
			{
				value = pDoc->inputImg[y][3*x+0] + 100;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3*x+0] = value;

				value = pDoc->inputImg[y][3 * x + 1] + 100;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 1] = value;

				value = pDoc->inputImg[y][3 * x + 2] + 100;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 2] = value;
			}
		}
	Invalidate();
}


void CimageProc20190834View::OnPixelSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CimageProc20190834View::OnPixelMul()
{
	CimageProc20190834Doc* pDoc = GetDocument();

	int x, y, value;
	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++) {

			value = pDoc->inputImg[y][x] *15;
			if (value > 250) value = 255;
			else if (value < 0) value = 0;
			pDoc->ResultImg[y][x] = value;
		}
	Invalidate();
}


void CimageProc20190834View::OnPixelDiv()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CimageProc20190834View::OnPixelHistoeq()
{
	CimageProc20190834Doc* pDoc = GetDocument();
	int x, y, k, i;
	int acc_hist;
	int N = 256 * 256;
	int hist[256], sum[256];


	for (i = 0; i < 256; i++) hist[i] = 0;

	//히스토그램 구하기

	for(y=0; y< pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			k = pDoc->inputImg[y][x];
			hist[k]++;
		}

	//누적분포 구하기
	acc_hist = 0;
	for (i = 0; i < 256; i++)
	{
		acc_hist += hist[i];
		sum[i] = acc_hist;
	}

	//픽셀 밝기 변환
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			k = pDoc->inputImg[y][x];
			pDoc->ResultImg[y][x] = (float)sum[k] / N * 255;
		}

	Invalidate();
}


void CimageProc20190834View::OnPixelConstretch()
{
	CimageProc20190834Doc* pDoc = GetDocument();
	int x, y;
	int min = 0;
	int	max = 255;

	



}


void CimageProc20190834View::OnPixelBinary()
{
	CimageProc20190834Doc* pDoc = GetDocument();
	int x, y;
	int threshold = 150;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->inputImg[y][x] > threshold) pDoc->ResultImg[y][x] = 255;
			else pDoc->ResultImg[y][x] = 0;
		}

	Invalidate();
}


void CimageProc20190834View::OnPixelTwoimageadd()
{
	CimageProc20190834Doc* pDoc = GetDocument();
	
	loadtwoimage();

	int x, y, value;

	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = pDoc->inputImg[y][x] + pDoc->inputImg2[y][x];
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				if (value > 64) value = 255;
				else value = 0;
				pDoc->ResultImg[y][x] = value;
			}

			}
			
		}
	
	Invalidate();
}


void CimageProc20190834View::loadtwoimage()
{
	CimageProc20190834Doc* pDoc = GetDocument();
	CFileDialog dlg(true);

	CFile file;

	if (dlg.DoModal() == IDOK)
	{
		
		file.Open(dlg.GetPathName(), CFile::modeRead); //파일 열기
		CArchive ar(&file, CArchive::load);
		pDoc->LoadSecondImageFile(ar);

		file.Close();
	}
}


void CimageProc20190834View::OnPixelTwoimagesub()
{
	CimageProc20190834Doc* pDoc = GetDocument();

	loadtwoimage();

	int x, y;
	int value;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{

				value = pDoc->inputImg[y][x] - pDoc->inputImg2[y][x];
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				if (value > 64) value = 255;
				else value = 0;
				pDoc->ResultImg[y][x] = value;
			}

		}
	Invalidate();
}


void CimageProc20190834View::OnRegionSharpening()
{
	CimageProc20190834Doc* pDoc = GetDocument();

	float kernel[3][3] = { {0,-1,0},{-1,5,-1},{0,-1,0} };

	convolve(pDoc->inputImg, pDoc->ResultImg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CimageProc20190834View::convolve(unsigned char** inimg, unsigned char** outimg, int cols, int rows, float mask[][3], int bias, int depth)
{
	int x, y;
	int i, j;
	int sum, rsum, bsum, gsum;

	for (y = 1; y < rows-1; y++)
		for (x = 1; x < cols-1; x++)
		{
			if (depth == 1)
			{
				sum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
					{
						sum += (inimg[y + j - 1][x + i - 1] * mask[j][i]);
					}
				sum += bias;
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;

				outimg[y][x] = sum;
			}
			else
			{
				rsum = 0; gsum = 0; bsum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
					{
						rsum += (inimg[y + j - 1][3 * (x + i - 1) + 0] * mask[j][i]);
						gsum += (inimg[y + j - 1][3 * (x + i - 1) + 1] * mask[j][i]);
						bsum += (inimg[y + j - 1][3 * (x + i - 1) + 2] * mask[j][i]);

					}
				rsum += bias;
				bsum += bias;
				gsum += bias;

				if (rsum > 255) rsum = 255;
				else if (rsum < 0) rsum = 0;
				if (gsum > 255) gsum = 255;
				else if (gsum < 0) gsum = 0;
				if (bsum > 255) bsum = 255;
				else if (bsum < 0) bsum = 0;

				outimg[y][3 * x + 0] = rsum;
				outimg[y][3 * x + 1] = gsum;
				outimg[y][3 * x + 2] = bsum;
			}
		}
}


void CimageProc20190834View::OnRegionSmoothing()
{
	CimageProc20190834Doc* pDoc = GetDocument();

	float kernel[3][3] = {
		{1 / 9.0f, 1 / 9.0f, 1 / 9.0f, },
		{1 / 9.0f, 1 / 9.0f, 1 / 9.0f, },
		{1 / 9.0f, 1 / 9.0f, 1 / 9.0f, }
	};

	convolve(pDoc->inputImg, pDoc->ResultImg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CimageProc20190834View::OnRegionEmbossing()
{
	CimageProc20190834Doc* pDoc = GetDocument();

	float kernel[3][3] = {
		{-1, 0, 0},
		{0, 0, 0},
		{0, 0, 1}
	};

	convolve(pDoc->inputImg, pDoc->ResultImg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 128, pDoc->depth);

	Invalidate();
}


void CimageProc20190834View::OnRegionPrewitt()
{
	CimageProc20190834Doc* pDoc = GetDocument();

	int x, y, i;
    int value, rvalue, gvalue, bvalue;

	float kernel_h[3][3] = {
		{-1, -1, -1},
		{0, 0, 0},
		{1, 1, 1}
	};
	float kernel_v[3][3] = {
		{-1, 0, 1},
		{-1, 0, 1},
		{-1, 0, 1}
	};

	unsigned char** Er, ** Ec;
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->ImageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}


	convolve(pDoc->inputImg, Er, pDoc->ImageWidth, pDoc->ImageHeight, kernel_h, 128, pDoc->depth);
	convolve(pDoc->inputImg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, kernel_v, 128, pDoc->depth);

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][x] = value;
			}
			else {
				rvalue = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				gvalue = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				bvalue = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));

				value = sqrt(rvalue * rvalue + gvalue * gvalue + bvalue * bvalue);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultImg[y][3 * x + 0] = value;
				pDoc->ResultImg[y][3 * x + 1] = value;
				pDoc->ResultImg[y][3 * x + 2] = value;
			}
		}

	//메모리 삭제(용량 문제)
	for (i = 0; i < pDoc->ImageHeight; i++) {
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CimageProc20190834View::OnRegionRoberts()
{
	CimageProc20190834Doc* pDoc = GetDocument();

	int x, y, i;
	int value, rvalue, gvalue, bvalue;

	float kernel_h[3][3] = {
		{-1, 0, 0},
		{0, 1, 0},
		{0, 0, 0}
	};
	float kernel_v[3][3] = {
		{0, 0, -1},
		{0, 1, 0},
		{0, 0, 0}
	};
	unsigned char** Er, ** Ec;
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->ImageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}


	convolve(pDoc->inputImg, Er, pDoc->ImageWidth, pDoc->ImageHeight, kernel_h, 128, pDoc->depth);
	convolve(pDoc->inputImg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, kernel_v, 128, pDoc->depth);

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][x] = value;
			}
			else {
				rvalue = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				gvalue = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				bvalue = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));

				value = sqrt(rvalue * rvalue + gvalue * gvalue + bvalue * bvalue);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultImg[y][3 * x + 0] = value;
				pDoc->ResultImg[y][3 * x + 1] = value;
				pDoc->ResultImg[y][3 * x + 2] = value;
			}
		}

	//메모리 삭제(용량 문제)
	for (i = 0; i < pDoc->ImageHeight; i++) {
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CimageProc20190834View::OnRegionSobel()
{
	CimageProc20190834Doc* pDoc = GetDocument();

	int x, y, i;
	int value, rvalue, gvalue, bvalue;

	float kernel_h[3][3] = {
		{-1, -2, -1},
		{0, 0, 0},
		{1, 2, 1}
	};
	float kernel_v[3][3] = {
		{-1, 0, 1},
		{-2, 0, 2},
		{-1, 0, 1}
	};
	unsigned char** Er, ** Ec;
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->ImageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}


	convolve(pDoc->inputImg, Er, pDoc->ImageWidth, pDoc->ImageHeight, kernel_h, 128, pDoc->depth);
	convolve(pDoc->inputImg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, kernel_v, 128, pDoc->depth);

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][x] = value;
			}
			else {
				rvalue = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				gvalue = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				bvalue = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));

				value = sqrt(rvalue * rvalue + gvalue * gvalue + bvalue * bvalue);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultImg[y][3 * x + 0] = value;
				pDoc->ResultImg[y][3 * x + 1] = value;
				pDoc->ResultImg[y][3 * x + 2] = value;
			}
		}

	//메모리 삭제(용량 문제)
	for (i = 0; i < pDoc->ImageHeight; i++) {
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CimageProc20190834View::OnRegionAverageFilltering()
{
	CimageProc20190834Doc* pDoc = GetDocument();

	int x, y, i, j;
	int xpos, ypos;
	int sum, rsum, gsum, bsum;
	int pixelcount;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			sum = 0;  pixelcount = 0; rsum = gsum = bsum = 0;
			for(j=-2; j<=2; j++)
				for (i = -2; i <= 2; i++) //5x5 
				{
					xpos = x + i;
					ypos = y + j;
					if (xpos >= 0 && xpos < pDoc->ImageWidth - 1 && ypos >= 0 && ypos < pDoc->ImageHeight - 1)
					{
						if (pDoc->depth == 1)
							sum += pDoc->inputImg[y + j][x + i];
						else {
							rsum += pDoc->inputImg[y + j][3 * (x + i) + 0];
							gsum += pDoc->inputImg[y + j][3 * (x + i) + 1];
							bsum += pDoc->inputImg[y + j][3 * (x + i) + 2];
						}
						pixelcount++;
					}
				}
			if (pDoc->depth == 1)
				pDoc->ResultImg[y][x] = sum / pixelcount;
			else {
				pDoc->ResultImg[y][3 * x + 0] = rsum / pixelcount;
				pDoc->ResultImg[y][3 * x + 1] = gsum / pixelcount;
				pDoc->ResultImg[y][3 * x + 2] = bsum / pixelcount;
			}
		}
	Invalidate();
}


void CimageProc20190834View::OnRegionMedianFiltering()
{
	CimageProc20190834Doc* pDoc = GetDocument();

	int x, y, i, j;
	int n[9], temp;

	for (y = 1; y < pDoc->ImageHeight-1; y++)
		for (x = 1; x < pDoc->ImageWidth-1; x++)
		{
			n[0] = pDoc->inputImg[y - 1][x - 1];
			n[1] = pDoc->inputImg[y - 1][x - 0];
			n[2] = pDoc->inputImg[y - 1][x + 2];
			n[3] = pDoc->inputImg[y - 1][x - 1];
			n[4] = pDoc->inputImg[y - 0][x - 0];
			n[5] = pDoc->inputImg[y - 0][x + 1];
			n[6] = pDoc->inputImg[y + 1][x - 1];
			n[7] = pDoc->inputImg[y + 1][x - 0];
			n[8] = pDoc->inputImg[y + 1][x + 1];

			//버블쇼팅(오름차순)
			for(i=8; i>0; i--)
				for (j = 0; j < i; j++)
				{
					if(n[j] > n[j+1])
					{
						temp = n[j + 1];
						n[j + 1] = n[j];
						n[j] = temp;
					}
				}

			pDoc->ResultImg[y][x] = n[4];
		}
	Invalidate();
}


void CimageProc20190834View::OnMopolgyColortogrey()
{
	CimageProc20190834Doc* pDoc = GetDocument();
	if (pDoc->depth == 1) return;

	int x, y;
	int grey;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			grey = (pDoc->inputImg[y][3 * x + 0] + pDoc->inputImg[y][3 * x + 0] + pDoc->inputImg[y][3 * x + 0]) / 3;
			pDoc->inputImg[y][3 * x + 0] = grey;
			pDoc->inputImg[y][3 * x + 1] = grey;
			pDoc->inputImg[y][3 * x + 2] = grey;
		}
	Invalidate();

}


void CimageProc20190834View::OnMopologyBinery()
{
	CimageProc20190834Doc* pDoc = GetDocument();

	int x, y;
	int grey, threshold = 100;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				if (pDoc->inputImg[y][x] > threshold)
					pDoc->inputImg[y][x] = 255;
				else
					pDoc->inputImg[y][x] = 0;
			}
			else
			{
				if ((pDoc->inputImg[y][3 * x + 0] + pDoc->inputImg[y][3 * x + 1] + pDoc->inputImg[y][3 * x + 2] / 3) > threshold)
				{
					pDoc->inputImg[y][3 * x + 0] = 255;
					pDoc->inputImg[y][3 * x + 1] = 255;
					pDoc->inputImg[y][3 * x + 2] = 255;
				}
				else
				{
					pDoc->inputImg[y][3 * x + 0] = 0;
					pDoc->inputImg[y][3 * x + 1] = 0;
					pDoc->inputImg[y][3 * x + 2] = 0;
				}
			}
		}
	Invalidate();
}


void CimageProc20190834View::OnMopologyErosion()
{
	CimageProc20190834Doc* pDoc = GetDocument();

	int x, y, i, j;
	int min = 255, rmin, gmin, bmin;

	for (y = 1; y < pDoc->ImageHeight-1; y++)
		for (x = 1; x < pDoc->ImageWidth-1; x++)
		{
			min = 255; rmin = 255; gmin = 255;bmin = 255;
			for(j=-1; j<=1; j++)
				for (i = -1; i <= 1; i++)
				{
					if (pDoc->depth == 1)
					{
						if (pDoc->inputImg[y + j][x + i] < min)
							min = pDoc->inputImg[y + j][x + i];
					}
					else
					{
						if (pDoc->inputImg[y + j][3*(x + i)+0] < rmin)
							rmin = pDoc->inputImg[y + j][3*(x + i)+0];
						if (pDoc->inputImg[y + j][3 * (x + i) + 1] < gmin)
							gmin = pDoc->inputImg[y + j][3 * (x + i) + 1];
						if (pDoc->inputImg[y + j][3 * (x + i) + 2] < bmin)
							bmin = pDoc->inputImg[y + j][3 * (x + i) + 2];
					}
				}
			if (pDoc->depth == 1)
			{
				pDoc->ResultImg[y][x] = min;
			}
			else
			{
				pDoc->ResultImg[y][3 * x + 0] = rmin;
				pDoc->ResultImg[y][3 * x + 1] = gmin;
				pDoc->ResultImg[y][3 * x + 2] = bmin;
			}
		}
	Invalidate();
}


void CimageProc20190834View::OnMopologyDilation()
{
	 CimageProc20190834Doc * pDoc = GetDocument();

	 int x, y, i, j;
	 int max, rmax, gmax, bmax;

	 for (y = 1; y < pDoc->ImageHeight - 1; y++)
		 for (x = 1; x < pDoc->ImageWidth - 1; x++)
		 {
			 max = 0; rmax = 0; gmax = 0; bmax = 0;
			 for (j = -1; j <= 1; j++)
				 for (i = -1; i <= 1; i++)
				 {
					 if (pDoc->depth == 1)
					 {
						 if (pDoc->inputImg[y + j][x + i] > max)
							 max = pDoc->inputImg[y + j][x + i];
					 }
					 else
					 {
						 if (pDoc->inputImg[y + j][3 * (x + i) + 0] > rmax) rmax = pDoc->inputImg[y + j][3 * (x + i) + 0];
						 if (pDoc->inputImg[y + j][3 * (x + i) + 1] > gmax) gmax = pDoc->inputImg[y + j][3 * (x + i) + 1];
						 if (pDoc->inputImg[y + j][3 * (x + i) + 2] > bmax) bmax = pDoc->inputImg[y + j][3 * (x + i) + 2];
					 }
				 }
			 if (pDoc->depth == 1)
			 {
				 pDoc->ResultImg[y][x] = max;
			 }
			 else
			 {
				 pDoc->ResultImg[y][3 * x + 0] = rmax;
				 pDoc->ResultImg[y][3 * x + 1] = gmax;
				 pDoc->ResultImg[y][3 * x + 2] = bmax;
			 }
		 }
	 Invalidate();
}


void CimageProc20190834View::OnMopologyOpening()
{
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();

	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
}


void CimageProc20190834View::CopyResultToInput()
{
	CimageProc20190834Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
		{
			pDoc->inputImg[y][x] = pDoc->ResultImg[y][x];
		}
}


void CimageProc20190834View::OnMopologyClosing()
{
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();

	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();

	
}


void CimageProc20190834View::OnGeometryZoominPixelCopy()
{
	CimageProc20190834Doc* pDoc = GetDocument();

	int x, y, i;

	int xscale = 3; 
	int yscale = 2;

	if (pDoc->gResultImage != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImage[i]);
		free(pDoc->gResultImage);
	}

	pDoc->gImageWidth = pDoc->ImageWidth * xscale;
	pDoc->gImageHeight = pDoc->ImageHeight * yscale;

	//메모리 할당
	pDoc->gResultImage = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	/*
	//전방향 사상
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
				pDoc->gResultImage[y*yscale][x*xscale] = pDoc->inputImg[y][x];
		}
		*/
	
	//역방향 사상
	for(y=0; y<pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if(pDoc->depth==1)
			    pDoc->gResultImage[y][x] = pDoc->inputImg[y / yscale][x / xscale];
			else
			{
				pDoc->gResultImage[y][3 * x + 0] = pDoc->inputImg[y / yscale][3 * (x / xscale) + 0];
				pDoc->gResultImage[y][3 * x + 1] = pDoc->inputImg[y / yscale][3 * (x / xscale) + 1];
				pDoc->gResultImage[y][3 * x + 2] = pDoc->inputImg[y / yscale][3 * (x / xscale) + 2];
			}
		} 
	Invalidate();
}


void CimageProc20190834View::OnGeometryZoominInterpolation()
{
	CimageProc20190834Doc* pDoc = GetDocument();

	int x, y, i;

	float xscale = 2.1;
	float yscale = 1.5;
	float src_x, src_y;
	float alpha, beta;
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
	int E, F;

	if (pDoc->gResultImage != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImage[i]);
		free(pDoc->gResultImage);
	}

	pDoc->gImageWidth = (pDoc->ImageWidth) * xscale;
	pDoc->gImageHeight = (pDoc->ImageHeight) * yscale;

	//메모리 할당
	pDoc->gResultImage = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	/*
	//전방향 사상
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
				pDoc->gResultImage[y*yscale][x*xscale] = pDoc->inputImg[y][x];
		}
		*/

		//역방향 사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			src_x = x / xscale;
			src_y = y / yscale;
			alpha = src_x - (int)src_x;
		    beta = src_y - (int)src_y;

			Ax = (int)src_x;
			Ay = (int)src_y;
			Bx = Ax + 1;
			By = Ay;
			Cx = Ax;
			Cy = Ay + 1;
			Dx = Ax + 1;
			Dy = Ay + 1;

			if (Bx > pDoc->ImageWidth - 1) Bx = pDoc->ImageWidth - 1;
			if (Cy > pDoc->ImageHeight - 1) Cy = pDoc->ImageHeight - 1;
			if (Dx > pDoc->ImageWidth - 1) Dx = pDoc->ImageWidth - 1;
			if (Dy > pDoc->ImageHeight - 1) Dy = pDoc->ImageHeight - 1;

			if (pDoc->depth == 1)
			{
				E = (1 - alpha) * pDoc->inputImg[Ay][Ax] + alpha * pDoc->inputImg[By][Bx];
				F = (1 - alpha) * pDoc->inputImg[Cy][Cx] + alpha * pDoc->inputImg[Dy][Dx];

				pDoc->gResultImage[y][x] = (1 - beta) * E + beta * F;
			}
			else
			{
				E = (1 - alpha) * pDoc->inputImg[Ay][3*Ax+0] + alpha * pDoc->inputImg[By][3*Bx+0];
				F = (1 - alpha) * pDoc->inputImg[Cy][3*Cx+0] + alpha * pDoc->inputImg[Dy][3*Dx+0];
				pDoc->gResultImage[y][3*x+0] = (1 - beta) * E + beta * F;


				E = (1 - alpha) * pDoc->inputImg[Ay][3 * Ax + 1] + alpha * pDoc->inputImg[By][3 * Bx + 1];
				F = (1 - alpha) * pDoc->inputImg[Cy][3 * Cx + 1] + alpha * pDoc->inputImg[Dy][3 * Dx + 1];
				pDoc->gResultImage[y][3 * x + 1] = (1 - beta) * E + beta * F;


				E = (1 - alpha) * pDoc->inputImg[Ay][3 * Ax + 2] + alpha * pDoc->inputImg[By][3 * Bx + 2];
				F = (1 - alpha) * pDoc->inputImg[Cy][3 * Cx + 2] + alpha * pDoc->inputImg[Dy][3 * Dx + 2];
				pDoc->gResultImage[y][3 * x + 2] = (1 - beta) * E + beta * F;
			}
		}
	Invalidate();
}


void CimageProc20190834View::OnGeometryZoomoutSubsampling()
{
	CimageProc20190834Doc* pDoc = GetDocument();

	int x, y, i;
	

	int xscale = 3;  //  1/3
 	int yscale = 2;  //  1/2

	if (pDoc->gResultImage != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImage[i]);
		free(pDoc->gResultImage);
	}

	pDoc->gImageWidth = (pDoc->ImageWidth)  / xscale;
	pDoc->gImageHeight = (pDoc->ImageHeight) / yscale;

	//메모리 할당
	pDoc->gResultImage = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}


	//역방향 사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				pDoc->gResultImage[y][x] = pDoc->inputImg[y * yscale][x * xscale];
			}
			else
			{
				pDoc->gResultImage[y][3 * x + 0] = pDoc->inputImg[y * yscale][3 * (x * xscale) + 0];
				pDoc->gResultImage[y][3 * x + 1] = pDoc->inputImg[y * yscale][3 * (x * xscale) + 1];
				pDoc->gResultImage[y][3 * x + 2] = pDoc->inputImg[y * yscale][3 * (x * xscale) + 2];
			}
		}

	Invalidate();

}


void CimageProc20190834View::OnGeometryZoomoutMinsub()
{
	OnRegionSmoothing();
	CopyResultToInput();
	OnGeometryZoomoutSubsampling();
}


void CimageProc20190834View::OnGeometryZoomoutAvgsam()
{
	CimageProc20190834Doc* pDoc = GetDocument();

	int x, y, i, j;
	int sum, rsum, gsum, bsum;
	int src_x, src_y;

	int xscale = 3;  //  1/3
	int yscale = 2;  //  1/2

	if (pDoc->gResultImage != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImage[i]);
		free(pDoc->gResultImage);
	}

	pDoc->gImageWidth = (pDoc->ImageWidth) / xscale;
	pDoc->gImageHeight = (pDoc->ImageHeight) / yscale;

	//메모리 할당
	pDoc->gResultImage = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//전방향 사상
	for (y = 0; y < pDoc->ImageHeight; y+=yscale)
		for (x = 0; x < pDoc->ImageWidth; x+=xscale)
		{
			sum = 0; rsum = 0; gsum = 0; bsum = 0;
			for(j=0;j<yscale;j++)
				for (i = 0; i < xscale; i++)
				{
					src_x = x + i;
					src_y = y + j;
					if (src_x > pDoc->ImageWidth - 1) src_x = pDoc->ImageWidth - 1;
					if (src_y > pDoc->ImageHeight - 1) src_y = pDoc->ImageHeight - 1;
					
					if (pDoc->depth == 1)
					{
						sum += pDoc->inputImg[src_y][src_x];
					}
					else
					{
						rsum += pDoc->inputImg[src_y][3*src_x+0];
						gsum += pDoc->inputImg[src_y][3*src_x+1];
						bsum += pDoc->inputImg[src_y][3*src_x+2];
					}
					
				}
			if (pDoc->depth == 1)
			{
				pDoc->gResultImage[y / yscale][x / xscale] = sum / (xscale * yscale);
			}
			else
			{
				pDoc->gResultImage[y / yscale][3*(x / xscale)+0] = rsum / (xscale * yscale);
				pDoc->gResultImage[y / yscale][3*(x / xscale)+1] = gsum / (xscale * yscale);
				pDoc->gResultImage[y / yscale][3*(x / xscale)+2] = bsum / (xscale * yscale);
			}
		}
	Invalidate();
}

#define PI 3.1415926535

void CimageProc20190834View::OnGeometryRotation()
{
	CimageProc20190834Doc* pDoc = GetDocument();

	int x, y, i, j;
	int angle = 30;  //단위 : degree
	float radian;
	int Cx, Cy, Oy;
	int xdiff, ydiff;
	int x_sourse, y_sourse;

	

	if (pDoc->gResultImage != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImage[i]);
		free(pDoc->gResultImage);
	}

	radian = 2 * PI / 360 * angle;
	pDoc->gImageWidth = (int)((pDoc->ImageHeight) * fabs(cos(PI / 2 - radian)) + (pDoc->ImageWidth)*fabs(cos(radian)));
	pDoc->gImageHeight = (int)((pDoc->ImageHeight) * fabs(cos(radian)) + (pDoc->ImageWidth) * fabs(cos(PI / 2 - radian)));

	//메모리 할당
	pDoc->gResultImage = (unsigned char**)malloc((pDoc->gImageHeight) * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//중심점 
	Cx = pDoc->ImageWidth / 2; 
	Cy = pDoc->ImageHeight / 2;
	//y의 마지막 좌표값
	Oy = pDoc->ImageHeight - 1;

	xdiff = (pDoc->gImageWidth - pDoc->ImageWidth) / 2;
	ydiff = (pDoc->gImageHeight - pDoc->ImageHeight) / 2;

	for(y = -ydiff; y<pDoc->gImageHeight-ydiff; y++)
		for (x = -xdiff; x < pDoc->gImageWidth - xdiff; x++)
		{
			x_sourse = (int)(((Oy - y) - Cy) * sin(radian) + (x - Cx) * cos(radian) + Cx);
			y_sourse = (int)(Oy - (((Oy - y) - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy));

			if (pDoc->depth == 1) {
				if (x_sourse <0 || x_sourse > pDoc->ImageWidth - 1 || y_sourse < 0 || y_sourse > pDoc->ImageHeight - 1) 
				{
					pDoc->gResultImage[y + ydiff][x + xdiff] = 255;
				}
				else
				{
					pDoc->gResultImage[y + ydiff][x + xdiff] = pDoc->inputImg[y_sourse][x_sourse];
				}
			}
			else
			{
				if (x_sourse <0 || x_sourse > pDoc->ImageWidth - 1 || y_sourse < 0 || y_sourse > pDoc->ImageHeight - 1)
				{
					pDoc->gResultImage[y + ydiff][(x + xdiff) * 3 + 0] = 255;
					pDoc->gResultImage[y + ydiff][(x + xdiff) * 3 + 1] = 255;
					pDoc->gResultImage[y + ydiff][(x + xdiff) * 3 + 2] = 255;
				}
				else
				{
					pDoc->gResultImage[y + ydiff][(x + xdiff) * 3 + 0] = pDoc->inputImg[y_sourse][3 * (x_sourse) + 0];
					pDoc->gResultImage[y + ydiff][(x + xdiff) * 3 + 1] = pDoc->inputImg[y_sourse][3 * (x_sourse) + 1];
					pDoc->gResultImage[y + ydiff][(x + xdiff) * 3 + 2] = pDoc->inputImg[y_sourse][3 * (x_sourse) + 2];
				}
			}
		}
	Invalidate();
}
