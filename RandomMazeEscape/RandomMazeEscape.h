
// RandomMazeEscape.h : RandomMazeEscape ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CRandomMazeEscapeApp:
// �� Ŭ������ ������ ���ؼ��� RandomMazeEscape.cpp�� �����Ͻʽÿ�.
//

class CRandomMazeEscapeApp : public CWinAppEx
{
public:
	CRandomMazeEscapeApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRandomMazeEscapeApp theApp;
