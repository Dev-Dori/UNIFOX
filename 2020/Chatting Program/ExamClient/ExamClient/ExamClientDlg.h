
// ExamClientDlg.h: 헤더 파일
//

#pragma once

#define NM_CHAT_DATA     1


class CExamClientDlg;

class MyClient : public TW_ClientSocket
{
private:
	CExamClientDlg *mp_parent;

public:
	MyClient(CExamClientDlg *ap_parent) : TW_ClientSocket(0x27)
	{
		mp_parent = ap_parent;
	}

	virtual int ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char *ap_recv_data, BS a_body_size);
};

// CExamClientDlg 대화 상자
class CExamClientDlg : public CDialogEx
{
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_staticDisp;
	int m_iCount;

private:
	HBRUSH mh_edit_bk_brush;//색상
private: 
	MyClient m_client;

private:
	CBrush m_bk_brush;
	CBrush m_bk_list_box_brush;

// 생성입니다.
public:
	CExamClientDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	void AddEventString(const wchar_t *ap_string);
	void AddEventState(const wchar_t* ap_string);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXAMCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_event_list;
	afx_msg void OnBnClickedSendBtn();

protected:
	afx_msg LRESULT OnConnected(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReadAndClose(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnLbnSelchangeEventList();
	afx_msg void OnLbnSelchangeEventList2();

	CListBox m_event_list2;
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CIPAddressCtrl m_IPControl;
	afx_msg void OnIpnFieldchangedIpaddrCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton1();
};



