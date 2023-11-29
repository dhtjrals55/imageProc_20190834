﻿// CAngleInputDialog.cpp: 구현 파일
//

#include "pch.h"
#include "imageProc_20190834.h"
#include "afxdialogex.h"
#include "CAngleInputDialog.h"


// CAngleInputDialog 대화 상자

IMPLEMENT_DYNAMIC(CAngleInputDialog, CDialogEx)

CAngleInputDialog::CAngleInputDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_iangle(0)
{

}

CAngleInputDialog::~CAngleInputDialog()
{
}

void CAngleInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ANGLE, m_iangle);
}


BEGIN_MESSAGE_MAP(CAngleInputDialog, CDialogEx)
END_MESSAGE_MAP()


// CAngleInputDialog 메시지 처리기
