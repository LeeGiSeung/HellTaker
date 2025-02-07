#include "pch.h"
#include "CObj.h"

#include "define.h"
#include "CEngine.h"
#include "CComponent.h"
#include "CCamera.h"
#include "CTimeMgr.h"

CObj::CObj()
	: m_Pos{}
	, m_Scale{}
	, m_LayerType(LAYER_TYPE::END)
	, m_Dead(false)
{	
}

CObj::~CObj()
{
	Delete_Vector(m_Component);
}

void CObj::Begin()
{

}

void CObj::FinalTick()
{
	for (size_t i = 0; i < m_Component.size(); ++i)
	{
		m_Component[i]->FinalTick();
	}
}

void CObj::Render()
{
	HDC dc = CEngine::GetInst()->GetSecondDC();

	Vec2 vPos = GetRenderPos();

	Rectangle(dc
		, vPos.x - m_Scale.x / 2
		, vPos.y - m_Scale.y / 2
		, vPos.x + m_Scale.x / 2
		, vPos.y + m_Scale.y / 2);

	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
    ReleaseDC(hwnd, dc);
}

CComponent* CObj::AddComponent(CComponent* _Component)
{
	m_Component.push_back(_Component);

	_Component->m_Owner = this;

	return _Component;
}

CComponent* CObj::GetComponent(const wstring& _Name)
{
	for (size_t i = 0; i < m_Component.size(); ++i)
	{
		if (m_Component[i]->GetName() == _Name)
			return m_Component[i];
	}

	return nullptr;
}

CComponent* CObj::GetComponent(COMPONENT_TYPE _Type)
{
	for (size_t i = 0; i < m_Component.size(); ++i)
	{
		if (m_Component[i]->GetType() == _Type)
			return m_Component[i];
	}

	return nullptr;
}

//SetPos할때 한번에 이동하지 않고 이동하는 모습이 보이게
void CObj::Tick_Move(Vec2 _CurPos, Vec2 _MovePos)
{

}

Vec2 CObj::GetRenderPos()
{
	return CCamera::GetInst()->GetRenderPos(m_Pos);
}