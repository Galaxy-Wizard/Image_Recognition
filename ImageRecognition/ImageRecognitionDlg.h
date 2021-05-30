
// ImageRecognitionDlg.h : header file
//

#pragma once

class CImageRecognitionDlg;

typedef void function_type(CImageRecognitionDlg*, CString);

// CImageRecognitionDlg dialog
class CImageRecognitionDlg : public CDialogEx
{
// Construction
public:
	CImageRecognitionDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGERECOGNITION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();

	void OpenFile(function_type function);

	CStatic EtalonImage;
	CStatic LoadedImage;
};

void Study(CImageRecognitionDlg*, CString);
void Compare(CImageRecognitionDlg*, CString);
void ResizeAndSetToDialogImage(CStatic* ImageArea, CImage Image);