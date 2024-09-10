#pragma once

class CBloodMemento;
class CBloodCareTaker
{
public:
	CBloodCareTaker();
	~CBloodCareTaker();

public:
	void Add_Memento(CBloodMemento* _pMemento)
	{
		m_vecMementos.push_back(_pMemento);
	}

	void Add_Memento_Front(CBloodMemento* _pMemento)
	{
		m_vecMementos.push_front(_pMemento);
	}

	CBloodMemento* Roll_Back()
	{
		CBloodMemento* pLastMemento = m_vecMementos.back();
		m_vecMementos.pop_back();
		return pLastMemento;
	}

	CBloodMemento* Roll_Front()
	{
		CBloodMemento* pFirstMemento = m_vecMementos.front();
		m_vecMementos.pop_front();
		return pFirstMemento;
	}


	CBloodMemento* Front()
	{
		return m_vecMementos.front();
	}

	size_t Get_Memento_Size()
	{
		return m_vecMementos.size();
	}

	CBloodMemento* Back()
	{
		return m_vecMementos.back();
	}

	void Release()
	{
		for_each(m_vecMementos.begin(), m_vecMementos.end(), Safe_Delete<CBloodMemento*>);
		m_vecMementos.clear();
	}

public:
	static CBloodCareTaker* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CBloodCareTaker;
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
	static CBloodCareTaker* m_pInstance;
	deque<CBloodMemento*> m_vecMementos;
};

