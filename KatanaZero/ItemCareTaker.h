#pragma once

class CItemMemento;
class CItemCareTaker
{
public:
	CItemCareTaker();
	~CItemCareTaker();
public:
	void Add_Memento(CItemMemento* _pMemento)
	{
		m_vecMementos.push_back(_pMemento);
	}

	void Add_Memento_Front(CItemMemento* _pMemento)
	{
		m_vecMementos.push_front(_pMemento);
	}

	CItemMemento* Roll_Back()
	{
		CItemMemento* pLastMemento = m_vecMementos.back();
		m_vecMementos.pop_back();
		return pLastMemento;
	}

	CItemMemento* Roll_Front()
	{
		CItemMemento* pFirstMemento = m_vecMementos.front();
		m_vecMementos.pop_front();
		return pFirstMemento;
	}

	CItemMemento* Front()
	{
		return m_vecMementos.front();
	}

	size_t Get_Memento_Size()
	{
		return m_vecMementos.size();
	}

	CItemMemento* Back()
	{
		return m_vecMementos.back();
	}

	void Release()
	{
		for_each(m_vecMementos.begin(), m_vecMementos.end(), Safe_Delete<CItemMemento*>);
		m_vecMementos.clear();
	}


public:
	static CItemCareTaker* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CItemCareTaker;
		}
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CItemCareTaker* m_pInstance;
	deque<CItemMemento*> m_vecMementos;
};

