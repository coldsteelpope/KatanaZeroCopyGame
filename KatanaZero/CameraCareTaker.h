#pragma once
class CCameraMemento;
class CCameraCareTaker
{
public:
	CCameraCareTaker();
	~CCameraCareTaker();

public:
	void Add_Memento(CCameraMemento* _pMemento)
	{
		m_vecMementos.push_back(_pMemento);
	}

	void Add_Memento_Front(CCameraMemento* _pMemento)
	{
		m_vecMementos.push_front(_pMemento);
	}

	CCameraMemento* Roll_Back()
	{
		CCameraMemento* pLastMemento = m_vecMementos.back();
		m_vecMementos.pop_back();
		return pLastMemento;
	}

	CCameraMemento* Roll_Front()
	{
		CCameraMemento* pFirstMemento = m_vecMementos.front();
		m_vecMementos.pop_front();
		return pFirstMemento;
	}

	size_t Get_Memento_Size()
	{
		return m_vecMementos.size();
	}

	CCameraMemento* Get_Back()
	{
		return m_vecMementos.back();
	}

	CCameraMemento* Front()
	{
		return m_vecMementos.front();
	}

	void Release()
	{
		for_each(m_vecMementos.begin(), m_vecMementos.end(), Safe_Delete<CCameraMemento*>);
		m_vecMementos.clear();
	}

public:
	static CCameraCareTaker* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CCameraCareTaker;
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
	static CCameraCareTaker* m_pInstance;
	deque<CCameraMemento*> m_vecMementos;

};

