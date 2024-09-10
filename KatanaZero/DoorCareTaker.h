#pragma once

class CDoorMemento;
class CDoorCareTaker
{
public:
	CDoorCareTaker();
	~CDoorCareTaker();

public:
	void Add_Memento(CDoorMemento* _pMemento)
	{
		m_vecMementos.push_back(_pMemento);
	}

	void Add_Memento_Front(CDoorMemento* _pMemento)
	{
		m_vecMementos.push_front(_pMemento);
	}

	CDoorMemento* Roll_Back()
	{
		CDoorMemento* pLastMemento = m_vecMementos.back();
		m_vecMementos.pop_back();
		return pLastMemento;
	}

	CDoorMemento* Roll_Front()
	{
		CDoorMemento* pFirstMemento = m_vecMementos.front();
		m_vecMementos.pop_front();
		return pFirstMemento;
	}

	CDoorMemento* Front()
	{
		return m_vecMementos.front();
	}

	size_t Get_Memento_Size()
	{
		return m_vecMementos.size();
	}

	CDoorMemento* Back()
	{
		return m_vecMementos.back();
	}

	void Release()
	{
		for_each(m_vecMementos.begin(), m_vecMementos.end(), Safe_Delete<CDoorMemento*>);
		m_vecMementos.clear();
	}

public:
	static CDoorCareTaker* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CDoorCareTaker;
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
	static CDoorCareTaker* m_pInstance;
	deque<CDoorMemento*> m_vecMementos;
};

