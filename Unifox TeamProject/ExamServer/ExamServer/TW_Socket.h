/*
#include "TW_Socket.h"

#pragma comment(lib, "WS2_32.lib")

#ifdef _DEBUG
	#pragma comment(lib, "D_TW_Socket.lib")
#else
	#pragma comment(lib, "R_TW_Socket.lib")
#endif
*/

#ifndef _TW_SOCKET_H_
#define _TW_SOCKET_H_

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>

#define LM_SEND_COMPLETED      29001
#define LM_RECV_COMPLETED      29002

typedef unsigned int BS;
#define HEAD_SIZE          2+sizeof(BS)


// ���۰� ���ſ��� ���������� �۾��� ������ ������ Ŭ����
class TW_ExchangeManager
{
protected:
	// ���� �Ǵ� ������ ���� �Ҵ�� �޸��� ��ü ũ��� ���� �۾����� ũ��
	int m_total_size, m_cur_size;
	// ���� �Ǵ� ������ ���ؼ� �Ҵ�� �޸��� ���� �ּ�
	char *mp_data;

public:
	TW_ExchangeManager();  // ��ü ������
	~TW_ExchangeManager(); // ��ü �ı���

	// ���� �Ǵ� ���ſ� ����� �޸𸮸� �Ҵ��Ѵ�.
	// a_data_size�� �Ҵ��� ũ�⸦ ����ϸ� �� �Լ��� ��ȯ ������
	// �Ҵ�� �޸��� �ּҸ� ��ȯ�Ѵ�.(��ȯ�� �ּҴ� �� Ŭ������ �����ϰ� �ִ�)
	char *MemoryAlloc(int a_data_size);
	// ���� �Ǵ� ���ſ� ���Ǵ� �޸𸮸� �����Ѵ�.
	void DeleteData();

	inline int GetTotalSize() { return m_total_size; } // �Ҵ�� �޸��� ũ�⸦ ��ȯ�Ѵ�.
	inline int GetCurSize() { return m_cur_size; }     // ���� �۾����� �޸��� ��ġ�� ��ȯ�Ѵ�.
};


class TW_SendManager : public TW_ExchangeManager
{
public:
	// ���� ������ ��ġ�� ũ�⸦ ����Ѵ�.
	int GetPosition(char **ap_data, int a_data_size = 2048);
	// ������ �Ϸ�Ǿ����� üũ�Ѵ�.
	inline char IsProcessing() { return m_total_size != m_cur_size; }
};

class TW_RecvManager : public TW_ExchangeManager
{
public:
	// ���ŵ� �����͸� ���� ���ŵ� �����Ϳ� �߰��Ѵ�.
	int AddData(char *ap_data, int a_size);
	// ���ŵ� �����͸� �ϳ��� ��ģ �޸��� ���� �ּҸ� ��´�.
	inline char *GetData() { return mp_data; }
};

class TW_Socket
{
protected:
	unsigned char m_valid_key;  // ���������� ��ȿ���� üũ�ϱ� ���� ���� ���� ������ ����
	char *mp_send_data, *mp_recv_data; // ���۰� ���ſ� ����� ����
	// �����Ͱ� ���ŵǰų� ������� ������ �������� �� �޽����� ������ ������ �ڵ� ��
	HWND mh_notify_wnd;         
	// �����Ͱ� ���ŵǰų� ������� ������ �������� �� ����� �޽��� ID
	int m_data_notify_id;

public:
	// ��ü �����ÿ� �������� ���� ���� ������ ���� �� ���� ������ ����� �޽��� ID�� �����ؾ� �Ѵ�.
	TW_Socket(unsigned char a_valid_key, int a_data_notify_id);
	virtual ~TW_Socket();

	// ����� ��󿡰� ��Ʈ��ũ�� �����͸� ������ �� ����� �Լ�
	// �� �Լ��� ���޵� ������ ������ �ϳ��� �޸𸮿� ��ӵ� Head ������ �����ؼ� �����մϴ�.
	int SendFrameData(SOCKET ah_socket, unsigned char a_message_id, const char * ap_body_data, BS a_body_size);
	// ��õ� ������ �����ϴ� �Լ�
	int ReceiveData(SOCKET ah_socket, BS a_body_size);
	// �����Ͱ� ���ŵǾ����� ���ŵ� �����͸� ó���ϴ� �Լ�
	void ProcessRecvEvent(SOCKET ah_socket);

	// ���ӵ� ����� ���� �� ����ϴ� �Լ� - �ڽ� Ŭ�������� �� �������ؼ� ����ؾ� ��
	virtual void DisconnectSocket(SOCKET ah_socket, int a_error_code);
	// ���ŵ� �����͸� ó���ϴ� �Լ� - �ڽ� Ŭ�������� �� �������ؼ� ����ؾ� ��
	virtual int ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char * ap_recv_data, BS a_body_size);

	// ASCII ������ ���ڿ��� �����ڵ�� ��ȯ�մϴ�.
	static void AsciiToUnicode(wchar_t *ap_dest_ip, char *ap_src_ip);
	// �����ڵ� ������ ���ڿ��� ASCII�� ��ȯ�մϴ�.
	static void UnicodeToAscii(char *ap_dest_ip, wchar_t *ap_src_ip);
};

class TW_UserData
{
protected:
	// Ŭ���̾�Ʈ�� ����ϱ� ���� ����� ���� �ڵ�
	SOCKET mh_socket;
	// Ŭ���̾�Ʈ���� ū �����͸� �����ϱ� ���� ����� ��ü
	TW_SendManager *mp_send_man;
	// Ŭ���̾�Ʈ���Լ� ū �����͸� �����ϱ� ���� ����� ��ü
	TW_RecvManager *mp_recv_man;
	// Ŭ���̾�Ʈ�� IP �ּ�
	wchar_t m_ip_address[16];

public:
	TW_UserData();
	virtual ~TW_UserData();

	inline SOCKET GetHandle() { return mh_socket; }  // ���� �ڵ� ���� ��´�.
	inline void SetHandle(SOCKET ah_socket) { mh_socket = ah_socket; } // ���� �ڵ� ���� �����Ѵ�.
	inline TW_SendManager *GetSendMan() { return mp_send_man; }  // ���ۿ� ��ü�� �ּҸ� ��´�.
	inline TW_RecvManager *GetRecvMan()	{ return mp_recv_man; }  // ���ſ� ��ü�� �ּҸ� ��´�.

	wchar_t *GetIP();                          // Ŭ���̾�Ʈ�� IP �ּҸ� ��´�.
	void SetIP(const wchar_t *ap_ip_address);  // Ŭ���̾�Ʈ�� IP �ּҸ� �����Ѵ�.
	// ���� ������ �Ҵ�Ǿ� �ִٸ� ������ �ݰ� �ʱ�ȭ�Ѵ�. 
	// a_linger_flag�� 1�� ����ϸ� ������ �����͸� �������̴��� ��� ������ �����Ѵ�.
	void CloseSocket(char a_linger_flag = 0);      

	// ������ ���� ��, ������ Ŭ������ Ȯ���Ҷ� �� �Լ��� ����Ѵ�.
	virtual TW_UserData *CreateObject() { return new TW_UserData; }
};

class TW_ServerSocket : public TW_Socket
{
protected:
	// listen �۾��� ����� ���� �ڵ�
	SOCKET mh_listen_socket;
	// ���ο� Ŭ���̾�Ʈ�� �������� �� �߻��� �޽��� ID ��
	int m_accept_notify_id;
	// ������ ������ �ִ� ����� ��
	unsigned short int m_max_user_count;
	// �ִ� ����ڸ� �����ϱ� ���ؼ� ����� ��ü��
	TW_UserData **mp_user_list;

public:
	TW_ServerSocket(unsigned char a_valid_key, unsigned short int a_max_user_count, TW_UserData *ap_user_data, 
						int a_accept_notify_id = 25001, int a_data_notify_id = 25002);
	virtual ~TW_ServerSocket();

	// ���� ���񽺸� �����Ѵ�. ��ȯ���� 1�̸� ����. -1�̸� ���� ���� ����, -2�̸� ������ ������ ���ε��ϴµ� ����
	int StartServer(const wchar_t *ap_ip_address, int a_port, HWND ah_notify_wnd);
	// Accept �ÿ� �߰������� �ؾ��� �۾��� �ִٸ� �� �Լ��� �������̵��ؼ� ó���ؾ���
	virtual void AddWorkForAccept(TW_UserData *ap_user) { }
	// �ִ� ����ڼ� �ʰ��ÿ� �߰������� �ؾ��� �۾��� �ִٸ� �� �Լ��� �������̵��ؼ� ó���ؾ���
	virtual void ShowLimitError(const wchar_t *ap_ip_address) { }
	// ���ο� Ŭ���̾�Ʈ�� �����Ҷ� ����� �Լ� - FD_ACCEPT�� ����� �޽����� �߻������� ����ϸ� �ȴ�.
	// ��ȯ���� 1�̸� ����. -1�̸� accept ����, -2�̸� ���� ������ �ִ� ����ڼ� �ʰ�
	int ProcessToAccept(WPARAM wParam, LPARAM lParam);

	// Ŭ���̾�Ʈ�� ���������ÿ� �߰������� �ؾ��� �۾��� �ִٸ� �� �Լ��� �������̵��ؼ� ó���ؾ���
	// a_error_code : 0�̸� ��������, -1�̸� Ű���� ��ȿ���� �ʾƼ� ����, -2�̸� �ٵ����� �����߿� ���� �߻�
	virtual void AddWorkForCloseUser(TW_UserData  *ap_user, int a_error_code);

	// ���ο� �����Ͱ� ����(FD_READ)�ǰų� Ŭ���̾�Ʈ�� ������ ����(FD_CLOSE)�ɶ� �߻��ϴ� 
	// �޽������� ���� ���ϰ� ���õ� �۾��� ó�����ִ� �Լ�
	void ProcessClientEvent(WPARAM wParam, LPARAM lParam);

	// ���� �ڵ��� ����Ͽ� � ��������� ã�´�. ã���� ������� ��ġ�� ��ȯ�Ѵ�.
	inline int FindUserIndex(SOCKET ah_socket)
	{
		for (int i = 0; i < m_max_user_count; i++) if (mp_user_list[i]->GetHandle() == ah_socket) return i;
		return -1;
	}

	// ���� �ڵ��� ����Ͽ� � ��������� ã�´�. ã���� ����� ������ �����ϴ� ��ü�� �ּҸ� ��ȯ�Ѵ�.
	inline TW_UserData *FindUserData(SOCKET ah_socket)
	{
		for (int i = 0; i < m_max_user_count; i++) if (mp_user_list[i]->GetHandle() == ah_socket) return mp_user_list[i];
		return NULL;
	}

	// ��ü ����ڿ� ���� ������ ��� ���
	inline TW_UserData **GetUserList() { return mp_user_list; }
	// �ִ� ����� ���� ��� ���
	unsigned short int GetMaxUserCount() { return m_max_user_count; }

	// ah_socket �ڵ� ���� ����ϴ� ���� ����ڸ� ������ ���� ��Ų��.
	virtual void DisconnectSocket(int ah_socket, int a_error_code);
	// FD_READ �̺�Ʈ�� �߻������� ���� �����͸� ó���ϴ� �Լ� 
	// (���� ������ ��� ���� Ŭ�������� �ݵ�� �������Ͽ� �ڽ��� ������ �޽����� ó���ؾ� �Ѵ�.)
	virtual int ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char *ap_recv_data, BS a_body_size);
};

class TW_ClientSocket : public TW_Socket
{
protected:
	// ������ ����ϱ� ���� ����� ���� �ڵ�
	SOCKET mh_socket;
	// 0 : ���� �ȵ�, 1 : ���� �õ���, 2 : ���� ��
	char m_connect_flag;
	// ������ ������ �õ��� ����� �˷��� ������ �޽����� �����Ѵ�.
	int m_connect_notify_id;
	// ������ ū �����͸� �����ϱ� ���� ����� ��ü
	TW_SendManager m_send_man;
	// ������ ū �����͸� �����ϱ� ���� ����� ��ü
	TW_RecvManager m_recv_man;

public:
	TW_ClientSocket(unsigned char a_valid_key, int a_connect_notify_id = 26001, int a_data_notify_id = 26002);
	virtual ~TW_ClientSocket();

	inline TW_SendManager *GetSendMan() { return &m_send_man; }  // ���ۿ� ��ü�� �ּҸ� ��´�.
	inline TW_RecvManager *GetRecvMan() { return &m_recv_man; }  // ���ſ� ��ü�� �ּҸ� ��´�.

	// ������ ������ �õ��Ѵ�.
	int ConnectToServer(const wchar_t *ap_ip_address, int a_port_num, HWND ah_notify_wnd);
	// ���� ���ӿ� ���� ����� �޽����� ���޵Ǿ����� �� �Լ��� ����ϸ� �ȴ�.
	// ��ȯ���� 1�̸� ������ ������ ������, 0�̸� ������ ������ ������
	int ResultOfConnection(LPARAM lParam);
	// ������ �����͸� �����ϰų� ������ ���������� �߻��ϴ� ������ �޽������� �� �Լ��� ����ϸ� �˴ϴ�.
	// ��ȯ���� 0 �̸� ������ ������ ����, 1�̸� �������� �����͸� ����
	int ProcessServerEvent(WPARAM wParam, LPARAM lParam);
	// ������ ������ ������ ������ �� ����մϴ�.
	virtual void DisconnectSocket(int ah_socket, int a_error_code);
	// FD_READ �̺�Ʈ�� �߻������� ���� �����͸� ó���ϴ� �Լ� 
	// (���� ������ ��� ���� Ŭ�������� �ݵ�� �������Ͽ� �ڽ��� ������ �޽����� ó���ؾ� �Ѵ�.)
	virtual int ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char *ap_recv_data, BS a_body_size);
	// ������ �����͸� ������ �� ����մϴ�. �޽��� ID�� ������ �������� �ּ�, �������� ũ�⸦ �Ѱ��ָ�
	// ��ӵ� �������� �������� �����ؼ� �����մϴ�.
	int SendFrameData(unsigned char a_message_id, const char * ap_body_data, BS a_body_size);

	// �������� ���ӻ��¸� �˰� ������ ����Ѵ�. 0 : ��������, 1 : ���ӻ���
	// ���������δ� ���¸� �������� ���������� �ܺο� �˷��ٶ��� �ΰ��� ���·� �˷��ش�.
	// '���� �õ���' ���´� ������ �����Ѵ�.
	inline int IsConnected() { return m_connect_flag == 2; }
	// ������ ����ϱ� ���� ������ ������ �ڵ� ���� �˰� ���� �� ����Ѵ�.
	inline SOCKET GetHandle() { return mh_socket; }
};

#endif