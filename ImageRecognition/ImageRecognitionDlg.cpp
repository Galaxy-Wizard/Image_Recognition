
// ImageRecognitionDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ImageRecognition.h"
#include "ImageRecognitionDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


const int ConstantImageSizeOnDialog = 330;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CImageRecognitionDlg dialog



CImageRecognitionDlg::CImageRecognitionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGERECOGNITION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageRecognitionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_1, EtalonImage);
	DDX_Control(pDX, IDC_STATIC_2, LoadedImage);
}

BEGIN_MESSAGE_MAP(CImageRecognitionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CImageRecognitionDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CImageRecognitionDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CImageRecognitionDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CImageRecognitionDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CImageRecognitionDlg message handlers

BOOL CImageRecognitionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CImageRecognitionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImageRecognitionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImageRecognitionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CImageRecognitionDlg::OnBnClickedButton1()
{
	OpenFile(Study);
}


void CImageRecognitionDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
}


void CImageRecognitionDlg::OnBnClickedButton2()
{
	OpenFile(Compare);
}


void CImageRecognitionDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
}

void CImageRecognitionDlg::OpenFile(function_type function)
{
	CFileDialog OpenDialog(TRUE);

	if (OpenDialog.DoModal() == IDOK)
	{
		auto FolderPath = OpenDialog.GetFolderPath();
		auto FileName = OpenDialog.GetFileName();

		if (FolderPath.GetLength() > 0)
		{
			if (FolderPath.GetAt(FolderPath.GetLength() - 1) != L'\\')
			{
				FolderPath += L'\\';
			}
		}

		auto FilePath = FolderPath + FileName;

		function(this, FilePath);
	}
}

void Study(CImageRecognitionDlg* ImageRecognitionDlg, CString file_name)
{
	if (ImageRecognitionDlg != nullptr)
	{
		CImage Image;
		auto Result = Image.Load(file_name);

		if (SUCCEEDED(Result))
		{
			ResizeAndSetToDialogImage(&ImageRecognitionDlg->EtalonImage, Image);
			//ImageRecognitionDlg->EtalonImage.SetBitmap(Image);
			//ImageRecognitionDlg->EtalonImage.RedrawWindow();
		}
	}
}

void Compare(CImageRecognitionDlg* ImageRecognitionDlg, CString file_name)
{
	if (ImageRecognitionDlg != nullptr)
	{
		CImage Image;
		auto Result = Image.Load(file_name);

		if (SUCCEEDED(Result))
		{
			ResizeAndSetToDialogImage(&ImageRecognitionDlg->LoadedImage, Image);		
			//ImageRecognitionDlg->LoadedImage.SetBitmap(Image);
			//ImageRecognitionDlg->LoadedImage.RedrawWindow();
		}
	}
}

void ResizeAndSetToDialogImage(CStatic* ImageArea, CImage Image)
{
	CImage new_image;

	int w = Image.GetWidth();
	int h = Image.GetHeight();

	double k = double(w) / double(h);

	int x2 = 0;
	int y2 = 0;

	if (k > 1)
	{
		x2 = int(ConstantImageSizeOnDialog / k);
		y2 = int(ConstantImageSizeOnDialog);
	}
	else
	{
		x2 = int(ConstantImageSizeOnDialog);
		y2 = int(ConstantImageSizeOnDialog * k);
	}

	if (ImageArea != nullptr)
	{
		CDC* ScreenDC = ImageArea->GetDC();
		if (ScreenDC != nullptr)
		{
			CDC* pMDC = new CDC;
			if (pMDC != nullptr)
			{
				pMDC->CreateCompatibleDC(ScreenDC);

				CBitmap* pb = new CBitmap;
				if (pb != nullptr)
				{
					pb->CreateCompatibleBitmap(ScreenDC, x2, y2);
					CBitmap* pob = pMDC->SelectObject(pb);
					if (pob != nullptr)
					{
						SetStretchBltMode(pMDC->m_hDC, COLORONCOLOR);
						Image.StretchBlt(pMDC->m_hDC, 0, 0, x2, y2, 0, 0, w, h, SRCCOPY);
						pMDC->SelectObject(pob);

						new_image.Attach(*pb);

						ImageArea->SetBitmap(new_image);
						ImageArea->RedrawWindow();
					}
					delete pb;
				}
				delete pMDC;
			}
			ScreenDC->ReleaseOutputDC();
		}
	}
}