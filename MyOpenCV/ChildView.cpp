
// ChildView.cpp : CChildView ���ʵ��
//

#include "stdafx.h"
#include "MyOpenCV.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView
IMPLEMENT_DYNCREATE(CChildView, CScrollView)

BEGIN_MESSAGE_MAP(CChildView, CScrollView)	
	ON_COMMAND(ID_FILE_OPEN, &CChildView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CChildView::OnFileSave)
	ON_COMMAND(ID_FILE_RECOVER, &CChildView::OnFileRecove)
	ON_COMMAND(ID_32775, &CChildView::OnCmd32775)
END_MESSAGE_MAP()

CChildView::CChildView()
{
	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	mWorkImage = NULL;
	mSrcImage = NULL;
	m_lpBmi = NULL;

	mFace.Init();
}

CChildView::~CChildView()
{
}

// CChildView ��Ϣ�������
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnDraw(CDC* pDC) 
{
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	if (mWorkImage) {                          //  ˢ�´��ڻ���
		int w = mWorkImage->width;		
		int h = mWorkImage->height;

		if(m_lpBmi)
			free(m_lpBmi);
		m_lpBmi = CreateMapInfo(mWorkImage,1);	

		CSize  sizeTotal;
		sizeTotal = CSize(w,h);
		SetScrollSizes(MM_TEXT,sizeTotal);  //  ���ù�����

		SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE); 
		StretchDIBits(pDC->m_hDC,
			0,0,w,h,
			0,0,mWorkImage->width,mWorkImage->height,
			mWorkImage->imageData,m_lpBmi,DIB_RGB_COLORS,SRCCOPY);
	}
}

// CMyOpenCVView ��Ϣ�������
void CChildView::OnFileOpen()
{
	// TODO: �ڴ���������������	
	CFileDialog dlgFile(TRUE, 0, 0, OFN_NOCHANGEDIR | OFN_HIDEREADONLY,_T("����ͼ���ļ�|*.jpg;*.png;*.bmp||"));
	if (dlgFile.DoModal() == IDOK)
	{		
		string file_name = CStr_to_str(dlgFile.GetPathName());
		mSrcImage = cvLoadImage(file_name.c_str(),-1);		
		cvFlip(mSrcImage); 

		mWorkImage = cvCloneImage(mSrcImage);              //  ������λͼ
		Invalidate();
	}
}

void CChildView::OnFileSave()
{
	// TODO: �ڴ���������������
	CFileDialog dlgFile(FALSE, _T("*.bmp"), 0, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("bmp|*.bmp|jpg|*.jpg||"));
	if (dlgFile.DoModal() == IDOK)
	{			
		string file_name = CStr_to_str(dlgFile.GetPathName());
		try{
			if(mWorkImage)
			{
				cvFlip(mWorkImage);
				cvSaveImage(file_name.c_str(),mWorkImage,0);
				cvFlip(mWorkImage);
			}
		}
		catch(cv::Exception e)
		{

		}
	}
}

void CChildView::OnFileRecove()
{
	if(mWorkImage)
		cvReleaseImage( &mWorkImage );

	mWorkImage = cvCloneImage(mSrcImage);              //  ������λͼ
	Invalidate();
}

//�������ػ�
void CChildView::OnCmd32775()
{
	cvFlip(mWorkImage);
	const CvSeq *pFaces = mFace.GetFace(mWorkImage);
	if(pFaces->total == 0)
	{
		MessageBox(_T("δ�ҵ�����"));
		return;
	}
	else
	{
		CString msg;
		msg.Format(_T("�ҵ�%d������"),pFaces->total);		
		MessageBox(msg);

		for(int i = 0; i < pFaces->total; i++ )  
		{  
			/* extract the rectanlges only */  
			CvRect face_rect = *(CvRect*)cvGetSeqElem( pFaces, i);  
			cvRectangle(mWorkImage, cvPoint(face_rect.x,face_rect.y),  
						 cvPoint((face_rect.x+face_rect.width),  
								 (face_rect.y+face_rect.height)),  
						 CV_RGB(255,0,255), 3 );  			
		} 
	}

	cvFlip(mWorkImage);
	Invalidate();
}