#include "pch.h"
#include "CTimeMgr.h"

#include "CEngine.h"
#include "CPlayer.h"
#include "CLevel.h"
#include "CLevelMgr.h"

CTimeMgr::CTimeMgr()
	: m_Frequency{}
	, m_PrevCount{}
	, m_CurCount{}
	, m_FPS(0)
	, m_DT(0.f)
	, m_Time(0.f)
{
}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::Init()
{
	// 1�ʿ� 1000 ī���� -> �ʴ� ī���� ���� �ʹ� ����
	//GetTickCount();

	// �����Ӱ� ������ ������ �ð�
	QueryPerformanceFrequency(&m_Frequency); // �ʴ� ī���� �� (õ��)
	QueryPerformanceCounter(&m_PrevCount);
}

void CTimeMgr::Tick()
{	
	// ������� Count ��
	QueryPerformanceCounter(&m_CurCount);

	m_DT = (float)(m_CurCount.QuadPart - m_PrevCount.QuadPart) / (float)m_Frequency.QuadPart;

	m_PrevCount = m_CurCount;

	++m_FPS;
	m_Time += m_DT;

	if (1.f <= m_Time)
	{
		wchar_t buff[255] = {};
		swprintf_s(buff, 255, L"HellTaker FPS : %d", m_FPS);
		SetWindowText(CEngine::GetInst()->GetMainWndHwnd(), buff);

		m_FPS = 0;
		m_Time -= 1.f;
	}
}

float CTimeMgr::GetDeltaTime()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecChain = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
	CPlayer* cp = dynamic_cast<CPlayer*>(vecChain[0]);

	if (cp->PauseMenu) {
		return 0.f;
	}
	else {
		return m_DT;
	}
}
