
// ExamClientDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "ExamClient.h"
#include "ExamClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString strIPAddr;

int MyClient::ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char *ap_recv_data, BS a_body_size)
{
	if (a_msg_id == NM_CHAT_DATA) {
		mp_parent->AddEventString((wchar_t *)ap_recv_data);

	}

	return 1;
}

// CExamClientDlg 대화 상자
CExamClientDlg::CExamClientDlg(CWnd* pParent /*=nullptr*/) : CDialogEx(IDD_EXAMCLIENT_DIALOG, pParent), m_client(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExamClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);						//list 1번 창
	DDX_Control(pDX, IDC_EVENT_LIST, m_event_list);
	DDX_Control(pDX, IDC_EVENT_LIST2, m_event_list2);
	DDX_Control(pDX, IDC_STATIC_DISP, m_staticDisp);
	DDX_Control(pDX, IDC_IPADDR_CTRL, m_IPControl);
}


BEGIN_MESSAGE_MAP(CExamClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND_BTN, &CExamClientDlg::OnBnClickedSendBtn)
	ON_MESSAGE(26001, &CExamClientDlg::OnConnected)
	ON_MESSAGE(26002, &CExamClientDlg::OnReadAndClose)
	ON_LBN_SELCHANGE(IDC_EVENT_LIST, &CExamClientDlg::OnLbnSelchangeEventList)
	ON_LBN_SELCHANGE(IDC_EVENT_LIST2, &CExamClientDlg::OnLbnSelchangeEventList2)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDR_CTRL, &CExamClientDlg::OnIpnFieldchangedIpaddrCtrl)
	ON_BN_CLICKED(IDC_BUTTON1, &CExamClientDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CExamClientDlg 메시지 처리기

BOOL CExamClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	m_bk_brush.CreateSolidBrush(RGB(40, 40, 43)); // 배경색
	mh_edit_bk_brush = CreateSolidBrush(RGB(233, 237, 241));  // 메시지 창 색상

	CString ip;
	//m_client.ConnectToServer(L"219.241.72.182", 27100, m_hWnd);  //서버 접속 아이피 설정 L"219.241.72.182"
	AddEventState(L"        <클라이언트 상태창>    ");
	AddEventState(L"_________________________________________________________________________________________");
	AddEventState(L""); AddEventState(L"");	AddEventState(L""); 
	AddEventState(L"_________________________________________________________________________________________");
	AddEventString(L"<사용방법>");
	AddEventString(L"");
	AddEventString(L"서버에 접속하시려면 아이피를 입력해주세요!");
	AddEventString(L"     ㄴ !** 아이피를 입력하지 않으시면 기본 서버로 접속됩니다  **!");
	AddEventString(L"");
	AddEventString(L"____________________________________________________________________________________________________");
	AddEventString(L"");


	m_iCount = 0;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CExamClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CRect r;
		GetClientRect(r);
		dc.FillRect(r, &m_bk_brush);  // 배경 색상
		
		//dc.FillSolidRect(r, RGB(0, 200, 255));
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CExamClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CExamClientDlg::OnBnClickedSendBtn()
{
	CString str;
	GetDlgItemText(IDC_CHAT_EDIT, str);
	SetDlgItemText(IDC_CHAT_EDIT, L"");

	if (m_client.IsConnected()) {
		m_client.SendFrameData(NM_CHAT_DATA, (char *)(const wchar_t *)str, (str.GetLength() + 1) * 2);
	}
	
}

void CExamClientDlg::AddEventString(const wchar_t *ap_string)
{
	int index = m_event_list.InsertString(-1, ap_string);  //IDC_EVENT_LIST2  m_event_list  // 	m_event_list.SetCurSel(index);
}

void CExamClientDlg::AddEventState(const wchar_t* ap_string)
{
	int index = m_event_list2.InsertString(-1, ap_string);  //IDC_EVENT_LIST2  m_event_list  // 	m_event_list.SetCurSel(index);
	m_event_list2.SetCurSel(index);
}

afx_msg LRESULT CExamClientDlg::OnConnected(WPARAM wParam, LPARAM lParam)
{
	if (m_client.ResultOfConnection(lParam) == 1) {
		SetTimer(1, 1000, NULL);
		AddEventState(L"서버에 접속했습니다!!");
	} else {
		AddEventState(L"서버에 접속할 수 없습니다!");
		OnBnClickedButton1();
	}

	return 0;
}


afx_msg LRESULT CExamClientDlg::OnReadAndClose(WPARAM wParam, LPARAM lParam)
{
	// 접속한 서버에서 데이터를 전송하거나 접속을 해제할 때 발생하는 메시지를 처리한다.
	m_client.ProcessServerEvent(wParam, lParam); // FD_READ, FD_CLOSE	

	return 0;
}


void CExamClientDlg::OnLbnSelchangeEventList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CExamClientDlg::OnLbnSelchangeEventList2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CExamClientDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	m_bk_brush.DeleteObject();
	DeleteObject(mh_edit_bk_brush);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}




HBRUSH CExamClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	int control_id = pWnd->GetDlgCtrlID();
	if (control_id == IDC_EVENT_LIST || control_id == IDC_EVENT_LIST2){
		return mh_edit_bk_brush;
	}

	switch (nCtlColor)
	{
		case CTLCOLOR_STATIC:
				if (pWnd->GetDlgCtrlID() == IDC_STATIC_DISP)
				{
					pDC->SetTextColor(RGB(255, 0, 0));
					pDC->SetBkMode(RGB(233, 237, 241));
					return mh_edit_bk_brush;
				}
	}

	return hbr;
}


void CExamClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString sTxt;
	switch (nIDEvent) {
		case 1:
			sTxt.Format(_T("접속시간 :: %d 초\n접속서버 :: %s"), m_iCount++, strIPAddr);
			m_staticDisp.SetWindowTextW(sTxt);
			break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CExamClientDlg::OnIpnFieldchangedIpaddrCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CExamClientDlg::OnBnClickedButton1()  //"219.241.72.182";
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// IP Address Contro -> Edit Control 

	BYTE ipFirst, ipSecond, ipThird, ipForth;

	// BYTE 변수에 IP Address Control 값 Save 
	m_IPControl.GetAddress(ipFirst, ipSecond, ipThird, ipForth);
	if (ipFirst && ipSecond) {
		strIPAddr.Format(_T("%d.%d.%d.%d"), ipFirst, ipSecond, ipThird, ipForth);
	}
	else {
		strIPAddr.Format(_T("%d.%d.%d.%d"), 219,241,72,182);
	}
	MessageBox(strIPAddr);
	m_client.ConnectToServer(strIPAddr, 27100, m_hWnd);
}
