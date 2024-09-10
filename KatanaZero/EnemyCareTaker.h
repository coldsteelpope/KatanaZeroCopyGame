#pragma once

class CEnemyMemento;
class CEnemyCareTaker
{
public:
	CEnemyCareTaker();
	~CEnemyCareTaker();

public:
	void Add_Memento(CEnemyMemento* _pMemento)
	{
		m_vecMementos.push_back(_pMemento);
	}

	void Add_Memento_Front(CEnemyMemento* _pMemento)
	{
		m_vecMementos.push_front(_pMemento);
	}

	CEnemyMemento* Roll_Back()
	{
		CEnemyMemento* pLastMemento = m_vecMementos.back();
		m_vecMementos.pop_back();
		return pLastMemento;
	}

	CEnemyMemento* Roll_Front()
	{
		CEnemyMemento* pFirstMemento = m_vecMementos.front();
		m_vecMementos.pop_front();
		return pFirstMemento;
	}

	size_t Get_Memento_Size()
	{
		return m_vecMementos.size();
	}

	CEnemyMemento* Back()
	{
		return m_vecMementos.back();
	}

	CEnemyMemento* Front()
	{
		return m_vecMementos.front();
	}

	void Release()
	{
		for_each(m_vecMementos.begin(), m_vecMementos.end(), Safe_Delete<CEnemyMemento*>);
		m_vecMementos.clear();
	}



public:
	static CEnemyCareTaker* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CEnemyCareTaker;
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
	static CEnemyCareTaker* m_pInstance;
	deque<CEnemyMemento*> m_vecMementos;
};

