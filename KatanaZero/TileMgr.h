#pragma once

class CObj;
class CTileMgr
{

private:
	CTileMgr();
	~CTileMgr();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC _hDC);
	void Release();

public:
	void Picking_Tile(POINT _tPt, TILE_TYPE _iDrawID, TILE_TYPE _iOption);
	void Save_Tile();
	void Load_Tile();
	void Set_Width(int _iWidth) { m_iWidth = _iWidth; }
	void Set_Height(int _iHeight) { m_iHeight = _iHeight; }

	vector<CObj*> Get_Cur_Tiles() { return m_vecTile; }
private:
	void Key_Input();

public:
	static CTileMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CTileMgr;
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
	static CTileMgr* m_pInstance;
	vector<CObj*> m_vecTile;

	int m_iWidth;
	int m_iHeight;
	int m_iTheNumberOfWidthTiles;
	int m_iTheNumberOfHeightTiles;
	
	bool m_bEditMode = false;

	TILE_TYPE m_iDrawID = TILE_TYPE::SOLID_WALL_TILE;
	TILE_TYPE m_iOptionID = TILE_TYPE::SOLID_WALL_TILE;
};

