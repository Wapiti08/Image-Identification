
// ChildView.h : CChildView ��Ľӿ�
//


#pragma once

#include "FaceAlign_Haar.h"
// CChildView ����

class CChildView : public CScrollView
{
// ����
public:
	CChildView();
	DECLARE_DYNCREATE(CChildView)

// ����
public:

// ����
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy(){}

// ʵ��
public:
	virtual ~CChildView();

	// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileRecove();
	afx_msg void OnCmd32775();

private:
	LPBITMAPINFO m_lpBmi;
	IplImage *mWorkImage;
	IplImage *mSrcImage;

	CFaceAlign mFace;
};

