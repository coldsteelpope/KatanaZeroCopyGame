#include "pch.h"
#include "BmpMgr.h"
#include "BossStage01.h"
#include "Camera.h"
#include "UIMgr.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Gangster.h"
#include "Grunt.h"
#include "Player.h"
#include "MouseMgr.h"
#include "BigExplosion.h"
#include "Boss.h"
#include "Explosion.h"
#include "SceneMgr.h"
#include "CameraCareTaker.h"
#include "CameraMemento.h"
#include "PlayerCareTaker.h"
#include "Memento.h"
#include "ItemCareTaker.h"
#include "ItemMemento.h"
#include "BloodCareTaker.h"
#include "BloodMemento.h"
#include "EnemyCareTaker.h"
#include "EnemyMemento.h"
#include "BossCareTaker.h"
#include "BossMemento.h"
#include "TimeRewindMgr.h"
#include "TimeSlowMgr.h"
#include "Pomp.h"
#include "ThunderBreathingMgr.h"
#include "SoundMgr.h"
#include "HighlightMgr.h"


#define BOSS_STAGE_01_WIDTH     800
#define BOSS_STAGE_01_HEIGHT    847



#define FIRST_GATE_FX   132
#define FIRST_GATE_FY   350

#define SECOND_GATE_FX  304
#define SECOND_GATE_FY  350

#define THIRD_GATE_FX   520
#define THIRD_GATE_FY   350

#define FOURTH_GATE_FX  660
#define FOURTH_GATE_FY  350


CBossStage01::CBossStage01()
{

}

CBossStage01::~CBossStage01()
{
}

void CBossStage01::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/BS1.bmp", L"BS1");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/BS1_2.bmp", L"BS1_2");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/BS1_slow.bmp", L"BS1_Slow");

    CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_PLAYER, CAbstractFactory<CPlayer>::Create(FIRST_GATE_FX, FIRST_GATE_FY, PLAYER_IDLE_FCX, PLAYER_IDLE_FCY));
    m_pPlayer = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_PLAYER).front();
    CMouseMgr::Get_Instance()->Set_Target(m_pPlayer);


    CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_BOSS, CAbstractFactory<CBoss>::Create(FOURTH_GATE_FX, FOURTH_GATE_FY + 25));
    CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_BOSS).front()->Set_Target(m_pPlayer);

    CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_EXPLOSION, CAbstractFactory<CExplosion>::Create(300, 300));

    CCamera::Get_Instance()->Set_LookAt(WINCX / 2.0f, WINCY / 2.0f);
    CCamera::Get_Instance()->Set_Limit_X(BOSS_STAGE_01_WIDTH);
    CCamera::Get_Instance()->Set_Limit_Y(BOSS_STAGE_01_HEIGHT);

    CUIMgr::Get_Instance()->Initialize();
    CUIMgr::Get_Instance()->Set_Player(m_pPlayer);
    CLineMgr::Get_Instance()->Initialize();

    CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
    CSoundMgr::Get_Instance()->PlaySound(L"bossbgm.wav", SOUND_BGM, 1.f);

    backgroundMusic = L"bossbgm.wav";
}

int CBossStage01::Update()
{

    if (CTimeRewindMgr::Get_Instance()->Get_RewindTime() == false)
    {
        if (m_iBossHP > 0)
        {
            CCamera::Get_Instance()->Update();
            CLineMgr::Get_Instance()->Update();
            CObjMgr::Get_Instance()->Update();
        }
        else
        {
            if (m_bInitBombSituation == false)
            {
                for (int iPosX = FIRST_GATE_FX; iPosX <= FOURTH_GATE_FX; iPosX += 20)
                {
                    CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_BIG_EXPLOSION, CAbstractFactory<CBigExplosion>::Create(iPosX, FIRST_GATE_FY + 200));
                }
                m_eBossStageOneType = BOSS_STAGE_ONE_BOMB;
                CLineMgr::Get_Instance()->Initialize();


                m_bInitBombSituation = true;
            }

            CCamera::Get_Instance()->Update();
            CLineMgr::Get_Instance()->Update();
            CObjMgr::Get_Instance()->Update();
        }

        // 시간을 되돌릴 때 반드시 보스 체력 3으로 만들기

        CBossStage01::Spawn_Enemies();
    }
    
    return 0;
}

void CBossStage01::Late_Update()
{
    if (CTimeRewindMgr::Get_Instance()->Get_RewindTime() == false)
    {
        if (m_iBossHP > 0)
        {
            CCamera::Get_Instance()->Late_Update();
            CLineMgr::Get_Instance()->Late_Update();
            CObjMgr::Get_Instance()->Late_Update();
        }
        else
        {
            CCamera::Get_Instance()->Late_Update();
            CLineMgr::Get_Instance()->Late_Update();
            CObjMgr::Get_Instance()->Late_Update();

            //list<CObj*> enemyList = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_ENEMY);
            //for (auto& enemy : enemyList)
            //{
            //    Safe_Delete<CObj*>(enemy);
            //}
            CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_ENEMY).clear();
        }
        Store_Mementos();
        ++m_llFrameCount;
    }
}

void CBossStage01::Render(HDC _hDC)
{
    if (CTimeRewindMgr::Get_Instance()->Get_RewindTime() == false)
    {
        if (m_iBossHP > 0)
        {
            Vec2 vLookAt = CCamera::Get_Instance()->Get_LookAt();
            HDC hMapDC = CBmpMgr::Get_Instance()->Find_Img(L"BS1");
            HDC hSlowMapDC = CBmpMgr::Get_Instance()->Find_Img(L"BS1_Slow");

            if (CTimeSlowMgr::Get_Instance()->Get_Slow_Time())
            {
                BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY - 150, BOSS_STAGE_01_WIDTH, BOSS_STAGE_01_HEIGHT, hSlowMapDC, 0, 0, SRCCOPY);
            }
            else
            {
                BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY - 150, BOSS_STAGE_01_WIDTH, BOSS_STAGE_01_HEIGHT, hMapDC, 0, 0, SRCCOPY);
            }

            CUIMgr::Get_Instance()->Render(_hDC);
            CObjMgr::Get_Instance()->Render(_hDC);

            if (CThunderBreathingMgr::Get_Instance()->Get_ThunderBreathing_Mode())
            {
                CHighlightMgr::Get_Instance()->Print_Highlight_For_ThunderBreathing(
                    _hDC,
                    m_pPlayer->Get_Info().fX,
                    m_pPlayer->Get_Info().fY,
                    CThunderBreathingMgr::Get_Instance()->Get_Player_Thunder_Breathing_Motion()
                );
            }
            else if (m_bHighlightEvent)
            {
                //CHighlightMgr::Get_Instance()->Print_Highlight(_hDC, m_Highlight_Target_fX, m_Highlight_Target_fY);
                CHighlightMgr::Get_Instance()->Print_Highlight(_hDC, m_Highlight_Target_fX, m_Highlight_Target_fY, 500.f, true);
            }
        }
        else
        {
            Vec2 vLookAt = CCamera::Get_Instance()->Get_LookAt();
            HDC hMapDC = CBmpMgr::Get_Instance()->Find_Img(L"BS1_2");
            BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY - 150, BOSS_STAGE_01_WIDTH, BOSS_STAGE_01_HEIGHT, hMapDC, 0, 0, SRCCOPY);

            CUIMgr::Get_Instance()->Render(_hDC);
            CObjMgr::Get_Instance()->Render(_hDC);

            if (m_pPlayer->Get_Info().fY > 900)
            {
                CSceneMgr::Get_Instance()->Change_Scene(SC_BOSS_02);
            }


        }
    }
    else
    {
        Print_Store_Mementos(_hDC);
        --m_llFrameCount;
        if (m_llFrameCount == 0)
        {
            CSceneMgr::Get_Instance()->Renew_Scene(SCENE_ID::SC_BOSS_01);
        }
    }
}

void CBossStage01::Release()
{
    CCamera::Destroy_Instance();
    CLineMgr::Destroy_Instance();
    CObjMgr::Destroy_Instance();
    CPlayerCareTaker::Destroy_Instance();
    CItemCareTaker::Destroy_Instance();
    CBossCareTaker::Destroy_Instance();
    CEffectCareTaker::Destroy_Instance();
    CBloodCareTaker::Destroy_Instance();
    
}

void CBossStage01::Spawn_Enemies()
{
    for (int iGateIdx = 0; iGateIdx < 4; ++iGateIdx)
    {
        if (dwGateExSpawnTimes[iGateIdx] + dwGateSpawanTime[iGateIdx] < GetTickCount())
        {
            BOSS_STAGE_ENEMY eEnemy = (BOSS_STAGE_ENEMY)(rand() % 2);

            switch (iGateIdx)
            {
            case 0:
            {
                switch (eEnemy)
                {
                case BOSS_STAGE_ENEMY::GRUNT:
                {
                    CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(FIRST_GATE_FX, FIRST_GATE_FY, GRUNT_IDLE_FCX, GRUNT_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 80, 700));
                    break;
                }
                case BOSS_STAGE_ENEMY::POMP:
                {
                    CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CPomp>::Create(FIRST_GATE_FX, FIRST_GATE_FY, GANGSTER_IDLE_FCX, GANGSTER_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 80, 700));
                    break;
                }
                }
                break;
            }
            case 1:
            {
                switch (eEnemy)
                {
                case BOSS_STAGE_ENEMY::GRUNT:
                {
                    CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(SECOND_GATE_FX, SECOND_GATE_FY, GRUNT_IDLE_FCX, GRUNT_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 80, 700));
                    break;
                }
                case BOSS_STAGE_ENEMY::POMP:
                {
                    CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CPomp>::Create(SECOND_GATE_FX, SECOND_GATE_FY, GANGSTER_IDLE_FCX, GANGSTER_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 80, 700));
                    break;
                }
                }
                break;
            }
            case 2:
            {
                switch (eEnemy)
                {
                case BOSS_STAGE_ENEMY::GRUNT:
                {
                    CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(THIRD_GATE_FX, THIRD_GATE_FY, GRUNT_IDLE_FCX, GRUNT_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 80, 700));
                    break;
                }
                case BOSS_STAGE_ENEMY::POMP:
                {
                    CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CPomp>::Create(THIRD_GATE_FX, THIRD_GATE_FY, GANGSTER_IDLE_FCX, GANGSTER_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 80, 700));
                    break;
                }
                }
                break;
            }
            case 3:
            {
                switch (eEnemy)
                {
                case BOSS_STAGE_ENEMY::GRUNT:
                {
                    CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(FOURTH_GATE_FX, FOURTH_GATE_FY, GRUNT_IDLE_FCX, GRUNT_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 80, 700));
                    break;
                }
                case BOSS_STAGE_ENEMY::POMP:
                {
                    CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CPomp>::Create(FOURTH_GATE_FX, FOURTH_GATE_FY, GANGSTER_IDLE_FCX, GANGSTER_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 80, 700));
                    break;
                }
                }
                break;
            }
            }
            dwGateExSpawnTimes[iGateIdx] = GetTickCount();
        }
    }
}

void CBossStage01::Print_Store_Mementos(HDC _hDC)
{
    

    // Camera Memento 꺼내기
    if (CCameraCareTaker::Get_Instance()->Get_Memento_Size() != 0)
    {
        CCameraMemento* pCameraMemento = CCameraCareTaker::Get_Instance()->Get_Back();
        while (pCameraMemento->Get_Frame_Count() == m_llFrameCount)
        {
            pCameraMemento = CCameraCareTaker::Get_Instance()->Roll_Back();
            CCamera::Get_Instance()->Set_LookAt(pCameraMemento->Get_Look_At());
            CCamera::Get_Instance()->Set_PrevLookAt(pCameraMemento->Get_Prev_Look_At());
            CCamera::Get_Instance()->Set_m_vDiff(pCameraMemento->Get_Diff());
            Safe_Delete<CCameraMemento*>(pCameraMemento);

            if (CCameraCareTaker::Get_Instance()->Get_Memento_Size() != 0)
            {
                pCameraMemento = CCameraCareTaker::Get_Instance()->Get_Back();
            }
            else
            {
                break;
            }
        }
    }





    Vec2 vLookAt = CCamera::Get_Instance()->Get_LookAt();
    HDC hMapDC = CBmpMgr::Get_Instance()->Find_Img(L"BS1");

    BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY - 150, BOSS_STAGE_01_WIDTH, BOSS_STAGE_01_HEIGHT, hMapDC, 0, 0, SRCCOPY);


    // Player Care Taker 가져오기
    if (CPlayerCareTaker::Get_Instance()->Get_Memento_Size() != 0)
    {
        CMemento* pLastMemento = CPlayerCareTaker::Get_Instance()->Back();
        while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
        {
            pLastMemento = CPlayerCareTaker::Get_Instance()->Roll_Back();
            pLastMemento->Print_Memento(_hDC);
            Safe_Delete<CMemento*>(pLastMemento);

            if (CPlayerCareTaker::Get_Instance()->Get_Memento_Size() != 0)
            {
                pLastMemento = CPlayerCareTaker::Get_Instance()->Back();
            }
            else
            {
                break;
            }
        }
    }

    if (CEffectCareTaker::Get_Instance()->Get_Memento_Size() != 0)
    {
        CMemento* pLastMemento = CEffectCareTaker::Get_Instance()->Back();
        while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
        {
            pLastMemento = CEffectCareTaker::Get_Instance()->Roll_Back();
            pLastMemento->Print_Memento(_hDC);
            Safe_Delete<CMemento*>(pLastMemento);

            if (CEffectCareTaker::Get_Instance()->Get_Memento_Size() != 0)
            {
                pLastMemento = CPlayerCareTaker::Get_Instance()->Back();
            }
            else
            {
                break;
            }
        }
    }


    // Enemy Care Taker 가져오기
    if (CEnemyCareTaker::Get_Instance()->Get_Memento_Size() != 0)
    {
        CEnemyMemento* pLastMemento = CEnemyCareTaker::Get_Instance()->Back();
        while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
        {
            pLastMemento = CEnemyCareTaker::Get_Instance()->Roll_Back();
            pLastMemento->Print_Memento(_hDC);
            Safe_Delete<CEnemyMemento*>(pLastMemento);

            if (CEnemyCareTaker::Get_Instance()->Get_Memento_Size() != 0)
            {
                pLastMemento = CEnemyCareTaker::Get_Instance()->Back();
            }
            else
            {
                break;
            }
        }
    }

    // Item 가져오기
    if (CItemCareTaker::Get_Instance()->Get_Memento_Size() != 0)
    {
        CItemMemento* pLastMemento = CItemCareTaker::Get_Instance()->Back();
        while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
        {
            pLastMemento = CItemCareTaker::Get_Instance()->Roll_Back();
            pLastMemento->Print_Memento(_hDC);
            Safe_Delete<CItemMemento*>(pLastMemento);

            if (CItemCareTaker::Get_Instance()->Get_Memento_Size() != 0)
            {
                pLastMemento = CItemCareTaker::Get_Instance()->Back();
            }
            else
            {
                break;
            }
        }
    }

    // Blood 가져오기
    if (CBloodCareTaker::Get_Instance()->Get_Memento_Size() != 0)
    {
        CBloodMemento* pLastMemento = CBloodCareTaker::Get_Instance()->Back();
        while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
        {
            pLastMemento = CBloodCareTaker::Get_Instance()->Roll_Back();
            pLastMemento->Print_Memento(_hDC);
            Safe_Delete<CBloodMemento*>(pLastMemento);
            if (CBloodCareTaker::Get_Instance()->Get_Memento_Size() != 0)
            {
                pLastMemento = CBloodCareTaker::Get_Instance()->Back();
            }
            else
            {
                break;
            }
        }
    }

    // Boss 가져오기
    if (CBossCareTaker::Get_Instance()->Get_Memento_Size() != 0)
    {
        CBossMemento* pLastMemento = CBossCareTaker::Get_Instance()->Back();
        while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
        {
            pLastMemento = CBossCareTaker::Get_Instance()->Roll_Back();
            pLastMemento->Print_Memento(_hDC);
            Safe_Delete<CBossMemento*>(pLastMemento);
            if (CBossCareTaker::Get_Instance()->Get_Memento_Size() != 0)
            {
                pLastMemento = CBossCareTaker::Get_Instance()->Back();
            }
            else
            {
                break;
            }
        }
    }
}

void CBossStage01::Store_Mementos()
{
    CMemento* pCurrentMemento = new CMemento(
        m_pPlayer->Get_Frame(),
        m_pPlayer->Get_Frame_Key(),
        m_pPlayer->Get_Render_Rect(),
        m_pPlayer->Get_Info(),
        m_pPlayer->Get_Obj_Cur_Dir(),
        m_llFrameCount
    );

    CPlayerCareTaker::Get_Instance()->Add_Memento(pCurrentMemento);

    CCameraMemento* pCurrentCameraMemento = new CCameraMemento(
        CCamera::Get_Instance()->Get_LookAt(),
        CCamera::Get_Instance()->Get_PrevLookAt(),
        CCamera::Get_Instance()->Get_Diff(),
        m_llFrameCount
    );
    CCameraCareTaker::Get_Instance()->Add_Memento(pCurrentCameraMemento);


    // Effect 저장
    list<CObj*> m_pObjEffectList = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_EFFECT);
    for (auto iter = m_pObjEffectList.begin(); iter != m_pObjEffectList.end(); ++iter)
    {
        CObj* pEffectObj = (*iter);
        CMemento* pCurentEffectMemento = new CMemento(
            pEffectObj->Get_Frame(),
            pEffectObj->Get_Frame_Key(),
            pEffectObj->Get_Render_Rect(),
            pEffectObj->Get_Info(),
            pEffectObj->Get_Obj_Cur_Dir(),
            m_llFrameCount
        );
        CEffectCareTaker::Get_Instance()->Add_Memento(pCurentEffectMemento);
    }


    // Enemy 저장
    list<CObj*> m_pObjEnemyList = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_ENEMY);
    for (auto iter = m_pObjEnemyList.begin(); iter != m_pObjEnemyList.end(); ++iter)
    {
        CObj* pEnemyObj = (*iter);
        CEnemyMemento* pCurrentEnemyMemento = new CEnemyMemento(
            pEnemyObj->Get_Frame(),
            pEnemyObj->Get_Frame_Key(),
            pEnemyObj->Get_Render_Rect(),
            pEnemyObj->Get_Info(),
            pEnemyObj->Get_Obj_Cur_Dir(),
            m_llFrameCount
        );
        CEnemyCareTaker::Get_Instance()->Add_Memento(pCurrentEnemyMemento);
    }


    // Item 저장
    list<CObj*> m_pObjExplosiveList = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_EXPLOSIVE);
    list<CObj*> m_pObjOilDrumList = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_OIL_DRUM);
    list<CObj*> m_pExplosionList = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_EXPLOSION);

    for (auto iter = m_pObjExplosiveList.begin(); iter != m_pObjExplosiveList.end(); ++iter)
    {
        CObj* pObj = (*iter);
        CItemMemento* pCurrentMemento = new CItemMemento(
            pObj->Get_Frame(),
            pObj->Get_Frame_Key(),
            pObj->Get_Render_Rect(),
            pObj->Get_Info(),
            pObj->Get_Obj_Cur_Dir(),
            m_llFrameCount
        );
        CItemCareTaker::Get_Instance()->Add_Memento(pCurrentMemento);
    }

    for (auto iter = m_pObjOilDrumList.begin(); iter != m_pObjOilDrumList.end(); ++iter)
    {
        CObj* pObj = (*iter);
        CItemMemento* pCurrentMemento = new CItemMemento(
            pObj->Get_Frame(),
            pObj->Get_Frame_Key(),
            pObj->Get_Render_Rect(),
            pObj->Get_Info(),
            pObj->Get_Obj_Cur_Dir(),
            m_llFrameCount
        );
        CItemCareTaker::Get_Instance()->Add_Memento(pCurrentMemento);
    }

    for (auto iter = m_pExplosionList.begin(); iter != m_pExplosionList.end(); ++iter)
    {
        CObj* pObj = (*iter);
        CItemMemento* pCurrentMemento = new CItemMemento(
            pObj->Get_Frame(),
            pObj->Get_Frame_Key(),
            pObj->Get_Render_Rect(),
            pObj->Get_Info(),
            pObj->Get_Obj_Cur_Dir(),
            m_llFrameCount
        );
        CItemCareTaker::Get_Instance()->Add_Memento(pCurrentMemento);
    }

    // 피 저장
    list<CObj*> m_pObjBloodList = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_BLOOD);
    for (auto iter = m_pObjBloodList.begin(); iter != m_pObjBloodList.end(); ++iter)
    {
        CObj* pObj = (*iter);

        CBloodMemento* pCurrentMemento = new CBloodMemento(
            pObj->Get_Frame(),
            pObj->Get_Frame_Key(),
            pObj->Get_Render_Rect(),
            pObj->Get_Info(),
            pObj->Get_Obj_Cur_Dir(),
            m_llFrameCount
        );
        CBloodCareTaker::Get_Instance()->Add_Memento(pCurrentMemento);
    }

    // 보스 저장
    list<CObj*> m_pObjBossList = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_BOSS);
    for (auto iter = m_pObjBossList.begin(); iter != m_pObjBossList.end(); ++iter)
    {
        CObj* pObj = (*iter);
        CBossMemento* pCurrentMemento = new CBossMemento(
            pObj->Get_Frame(),
            pObj->Get_Frame_Key(),
            pObj->Get_Render_Rect(),
            pObj->Get_Info(),
            pObj->Get_Obj_Cur_Dir(),
            m_llFrameCount
        );
        CBossCareTaker::Get_Instance()->Add_Memento(pCurrentMemento);
    }
}
