
// imageProc_20190834View.h: CimageProc20190834View 클래스의 인터페이스
//

#pragma once


class CimageProc20190834View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CimageProc20190834View() noexcept;
	DECLARE_DYNCREATE(CimageProc20190834View)

// 특성입니다.
public:
	CimageProc20190834Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	


// 구현입니다.
public:
	virtual ~CimageProc20190834View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenutext();
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelSub();
	afx_msg void OnPixelMul();
	afx_msg void OnPixelDiv();
	afx_msg void OnPixelHistoeq();
	afx_msg void OnPixelConstretch();
	afx_msg void OnPixelBinary();
	afx_msg void OnPixelTwoimageadd();
	void loadtwoimage();
	afx_msg void OnPixelTwoimagesub();
	afx_msg void OnRegionSharpening();
	void convolve(unsigned char** inimg, unsigned char** outimg, int cols, int rows, float mask[][3], int bias, int depth);
	afx_msg void OnRegionSmoothing();
	afx_msg void OnRegionEmbossing();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionRoberts();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionAverageFilltering();
	afx_msg void OnRegionMedianFiltering();
	afx_msg void OnMopolgyColortogrey();
	afx_msg void OnMopologyBinery();
	afx_msg void OnMopologyErosion();
	afx_msg void OnMopologyDilation();
	afx_msg void OnMopologyOpening();
	void CopyResultToInput();
	afx_msg void OnMopologyClosing();
	afx_msg void OnGeometryZoominPixelCopy();
	afx_msg void OnGeometryZoominInterpolation();
	afx_msg void OnGeometryZoomoutSubsampling();
	afx_msg void OnGeometryZoomoutMinsub();
	afx_msg void OnGeometryZoomoutAvgsam();
	afx_msg void OnGeometryRotation();
	afx_msg void OnGeometryMirror();
	afx_msg void OnGeometryFlip();
	afx_msg void OnDeometryWarping();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnAviView();
	bool bAVIMode;
	CString AVIFileName;
	void LoadAVIFile(CDC* pDC);
	afx_msg void OnGoemetryMorping();
};

#ifndef _DEBUG  // imageProc_20190834View.cpp의 디버그 버전
inline CimageProc20190834Doc* CimageProc20190834View::GetDocument() const
   { return reinterpret_cast<CimageProc20190834Doc*>(m_pDocument); }
#endif

