
// ChildView.h : CChildView 类的接口
//


#pragma once

#include "FaceAlign_Haar.h"
// CChildView 窗口

class CChildView : public CScrollView
{
// 构造
public:
	CChildView();
	DECLARE_DYNCREATE(CChildView)

// 特性
public:

// 操作
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy(){}

// 实现
public:
	virtual ~CChildView();

	// 生成的消息映射函数
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

