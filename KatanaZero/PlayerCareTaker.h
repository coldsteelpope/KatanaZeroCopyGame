#pragma once

class CMemento;
class CPlayerCareTaker
{
public:
	CPlayerCareTaker();
	~CPlayerCareTaker();

public:
	void Add_Memento(CMemento* _pMemento)
	{
		m_vecMementos.push_back(_pMemento);
	}

	void Add_Memento_Front(CMemento* _pMemento)
	{
		m_vecMementos.push_front(_pMemento);
	}

	CMemento* Roll_Back()
	{
		CMemento* pLastMemento = m_vecMementos.back();
		m_vecMementos.pop_back();
		return pLastMemento;
	}

	CMemento* Roll_Front()
	{
		CMemento* pFirstMemento = m_vecMementos.front();
		m_vecMementos.pop_front();
		return pFirstMemento;
	}

	size_t Get_Memento_Size()
	{
		return m_vecMementos.size();
	}

	CMemento* Front()
	{
		return m_vecMementos.front();
	}

	CMemento* Back()
	{
		return m_vecMementos.back();
	}

	void Release()
	{
		for_each(m_vecMementos.begin(), m_vecMementos.end(), Safe_Delete<CMemento*>);
		m_vecMementos.clear();
	}

public:
	static CPlayerCareTaker* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CPlayerCareTaker;
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
	static CPlayerCareTaker* m_pInstance;
	deque<CMemento*> m_vecMementos;
};

