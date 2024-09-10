#pragma once

class CBulletMemento;
class CBulletCareTaker
{
public:
	CBulletCareTaker();
	~CBulletCareTaker();

public:
	void Add_Memento(CBulletMemento* _pMemento)
	{
		m_vecMementos.push_back(_pMemento);
	}

	void Add_Memento_Front(CBulletMemento* _pMemento)
	{
		m_vecMementos.push_front(_pMemento);
	}

	CBulletMemento* Roll_Back()
	{
		CBulletMemento* pLastMemento = m_vecMementos.back();
		m_vecMementos.pop_back();
		return pLastMemento;
	}

	CBulletMemento* Roll_Front()
	{
		CBulletMemento* pFirstMemento = m_vecMementos.front();
		m_vecMementos.pop_front();
		return pFirstMemento;
	}


	CBulletMemento* Front()
	{
		return m_vecMementos.front();
	}

	size_t Get_Memento_Size()
	{
		return m_vecMementos.size();
	}

	CBulletMemento* Back()
	{
		return m_vecMementos.back();
	}

	void Release()
	{
		for_each(m_vecMementos.begin(), m_vecMementos.end(), Safe_Delete<CBulletMemento*>);
		m_vecMementos.clear();
	}

public:
	static CBulletCareTaker* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CBulletCareTaker;
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
	static CBulletCareTaker* m_pInstance;
	deque<CBulletMemento*> m_vecMementos;
};

