#pragma once

class CBossMemento;
class CBossCareTaker
{
public:
	CBossCareTaker();
	~CBossCareTaker();

public:
	void Add_Memento(CBossMemento* _pMemento)
	{
		m_vecMementos.push_back(_pMemento);
	}

	void Add_Memento_Front(CBossMemento* _pMemento)
	{
		m_vecMementos.push_front(_pMemento);
	}

	CBossMemento* Roll_Back()
	{
		CBossMemento* pLastMemento = m_vecMementos.back();
		m_vecMementos.pop_back();
		return pLastMemento;
	}

	CBossMemento* Roll_Front()
	{
		CBossMemento* pFirstMemento = m_vecMementos.front();
		m_vecMementos.pop_front();
		return pFirstMemento;
	}


	CBossMemento* Front()
	{
		return m_vecMementos.front();
	}

	size_t Get_Memento_Size()
	{
		return m_vecMementos.size();
	}

	CBossMemento* Back()
	{
		return m_vecMementos.back();
	}

	void Release()
	{
		for_each(m_vecMementos.begin(), m_vecMementos.end(), Safe_Delete<CBossMemento*>);
		m_vecMementos.clear();
	}

public:
	static CBossCareTaker* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CBossCareTaker;
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
	static CBossCareTaker* m_pInstance;
	deque<CBossMemento*> m_vecMementos;
};

