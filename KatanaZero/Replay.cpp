#include "pch.h"
#include "Replay.h"
#include "BmpMgr.h"
#include "ReplayMgr.h"
#include "PlayerCareTaker.h"
#include "CameraCareTaker.h"
#include "EffectCareTaker.h"
#include "EnemyCareTaker.h"
#include "ItemCareTaker.h"
#include "CameraMemento.h"
#include "ItemCareTaker.h"
#include "Memento.h"
#include "Camera.h"
#include "ReplayMgr.h"
#include "EnemyMemento.h"
#include "ItemMemento.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "BloodCareTaker.h"
#include "DoorCareTaker.h"
#include "BloodMemento.h"
#include "DoorMemento.h"
#include "SoundMgr.h"
#include "BulletCareTaker.h"
#include "BulletMemento.h"
#include "Bullet.h"

CReplay::CReplay()
{
}

CReplay::~CReplay()
{
    Release();
}

void CReplay::Initialize()
{
    //CBmpMgr::Get_Instance()->Insert_Bmp();
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/videoUI/replayTV.bmp", L"replayTV");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/videoUI/title1.bmp", L"Title1");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/videoUI/title2.bmp", L"Title2");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/videoUI/title3.bmp", L"Title3");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/videoUI/title4.bmp", L"Title4");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/videoUI/youcandothis.bmp", L"YOUCANDOTHIS");


    dwYouCanDoThisTime = GetTickCount();

    eReplaySceneID = CSceneMgr::Get_Instance()->Get_Prev_Scene_ID();
}

int CReplay::Update()
{
    if (m_bShowVideo == true)
    {
        Key_Input();
    }
    
    return 0;
}

void CReplay::Late_Update()
{
    if (dwYouCanDoThisTime + 3000 < GetTickCount())
    {
        m_bShowVideo = true;
    }

    
    if (m_llFrameCount == CReplayMgr::Get_Instance()->Get_Full_Frame() - 1)
    {
        m_eReplayStatus = STOP;
    }
}

void CReplay::Render(HDC _hDC)
{
    if (m_bShowVideo == false)
    {
        HDC youCanDoThisDC = CBmpMgr::Get_Instance()->Find_Img(L"YOUCANDOTHIS");
        BitBlt(_hDC, 0, 0, WINCX, WINCY, youCanDoThisDC, 150, 0, SRCCOPY);
    }
    else
    {
        if (m_eReplayStatus == PLAY)
        {
            // 재생
            if (CCameraCareTaker::Get_Instance()->Get_Memento_Size() != 0)
            {
                CCameraMemento* pCameraMemento = CCameraCareTaker::Get_Instance()->Front();
                while (pCameraMemento->Get_Frame_Count() == m_llFrameCount)
                {
                    pCameraMemento = CCameraCareTaker::Get_Instance()->Roll_Front();
                    CCamera::Get_Instance()->Set_LookAt(pCameraMemento->Get_Look_At());
                    CCamera::Get_Instance()->Set_PrevLookAt(pCameraMemento->Get_Prev_Look_At());
                    CCamera::Get_Instance()->Set_m_vDiff(pCameraMemento->Get_Diff());
                    m_vCameraStack.push_back(pCameraMemento);

                    if (CCameraCareTaker::Get_Instance()->Get_Memento_Size() != 0)
                    {
                        pCameraMemento = CCameraCareTaker::Get_Instance()->Front();
                    }
                    else
                    {
                        break;
                    }
                }
            }

            Vec2 vLookAt = CCamera::Get_Instance()->Get_LookAt();

            
            switch (eReplaySceneID)
            {
            case SCENE_ID::SC_STAGE_01:
            {
                HDC hMapDC = CBmpMgr::Get_Instance()->Find_Img(L"Stage01");
                BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY, CReplayMgr::Get_Instance()->Get_Scene_Width(), CReplayMgr::Get_Instance()->Get_Scene_Height(), hMapDC, 0, 0, SRCCOPY);
                break;
            }
            case SCENE_ID::SC_STAGE_02:
            {
                HDC hMapDC = CBmpMgr::Get_Instance()->Find_Img(L"Stage02");
                BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY, CReplayMgr::Get_Instance()->Get_Scene_Width(), CReplayMgr::Get_Instance()->Get_Scene_Height(), hMapDC, 0, 0, SRCCOPY);
                break;
            }
            case SCENE_ID::SC_STAGE_03:
            {
                HDC hMapDC = CBmpMgr::Get_Instance()->Find_Img(L"Stage03");
                BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY, CReplayMgr::Get_Instance()->Get_Scene_Width(), CReplayMgr::Get_Instance()->Get_Scene_Height(), hMapDC, 0, 0, SRCCOPY);
                break;
            }
            }
            
            
            if (CBloodCareTaker::Get_Instance()->Get_Memento_Size() != 0)
            {
                CBloodMemento* pLastMemento = CBloodCareTaker::Get_Instance()->Front();
                while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
                {
                    pLastMemento = CBloodCareTaker::Get_Instance()->Roll_Front();
                    pLastMemento->Print_Memento(_hDC);
                    m_vBloodStack.push_back(pLastMemento);

                    if (CBloodCareTaker::Get_Instance()->Get_Memento_Size() != 0)
                    {
                        pLastMemento = CBloodCareTaker::Get_Instance()->Front();
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
                CItemMemento* pLastMemento = CItemCareTaker::Get_Instance()->Front();
                while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
                {
                    pLastMemento = CItemCareTaker::Get_Instance()->Roll_Front();
                    pLastMemento->Print_Memento(_hDC);
                    m_vItemStack.push_back(pLastMemento);

                    if (CItemCareTaker::Get_Instance()->Get_Memento_Size() != 0)
                    {
                        pLastMemento = CItemCareTaker::Get_Instance()->Front();
                    }
                    else
                    {
                        break;
                    }
                }
            }

            if (CDoorCareTaker::Get_Instance()->Get_Memento_Size() != 0)
            {
                CDoorMemento* pLastMemento = CDoorCareTaker::Get_Instance()->Front();
                while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
                {
                    pLastMemento = CDoorCareTaker::Get_Instance()->Roll_Front();
                    pLastMemento->Print_Memento(_hDC);
                    m_vDoorStack.push_back(pLastMemento);

                    if (CDoorCareTaker::Get_Instance()->Get_Memento_Size() != 0)
                    {
                        pLastMemento = CDoorCareTaker::Get_Instance()->Front();
                    }
                    else
                    {
                        break;
                    }
                }
            }

            if (CPlayerCareTaker::Get_Instance()->Get_Memento_Size() != 0)
            {
                CMemento* pLastMemento = CPlayerCareTaker::Get_Instance()->Front();
                while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
                {
                    pLastMemento = CPlayerCareTaker::Get_Instance()->Roll_Front();
                    pLastMemento->Print_Memento(_hDC);
                    m_vPlayerStack.push_back(pLastMemento);

                    if (CPlayerCareTaker::Get_Instance()->Get_Memento_Size() != 0)
                    {
                        pLastMemento = CPlayerCareTaker::Get_Instance()->Front();
                    }
                    else
                    {
                        break;
                    }
                }
            }

            if (CBulletCareTaker::Get_Instance()->Get_Memento_Size() != 0)
            {
                CBulletMemento* pLastMemento = CBulletCareTaker::Get_Instance()->Front();
                while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
                {
                    pLastMemento = CBulletCareTaker::Get_Instance()->Roll_Front();
                    pLastMemento->Print_Memento(_hDC);
                    m_vBulletStack.push_back(pLastMemento);

                    if (CBulletCareTaker::Get_Instance()->Get_Memento_Size() != 0)
                    {
                        pLastMemento = CBulletCareTaker::Get_Instance()->Front();
                    }
                    else
                    {
                        break;
                    }
                }
            }

            // Effect Care Taker 가져오기
            if (CEffectCareTaker::Get_Instance()->Get_Memento_Size() != 0)
            {
                CMemento* pLastMemento = CEffectCareTaker::Get_Instance()->Front();
                while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
                {
                    pLastMemento = CEffectCareTaker::Get_Instance()->Roll_Front();
                    pLastMemento->Print_Memento(_hDC);
                    m_vEffectStack.push_back(pLastMemento);

                    if (CEffectCareTaker::Get_Instance()->Get_Memento_Size() != 0)
                    {
                        pLastMemento = CEffectCareTaker::Get_Instance()->Front();
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
                CEnemyMemento* pLastMemento = CEnemyCareTaker::Get_Instance()->Front();
                while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
                {
                    pLastMemento = CEnemyCareTaker::Get_Instance()->Roll_Front();
                    pLastMemento->Print_Memento(_hDC);
                    m_vEnemyStack.push_back(pLastMemento);

                    if (CEnemyCareTaker::Get_Instance()->Get_Memento_Size() != 0)
                    {
                        pLastMemento = CEnemyCareTaker::Get_Instance()->Front();
                    }
                    else
                    {
                        break;
                    }
                }
            }




            


            ++m_llFrameCount;


            HDC titleTwoDC = CBmpMgr::Get_Instance()->Find_Img(L"Title2");
            GdiTransparentBlt(
                _hDC,
                50, 50,
                97, 63,
                titleTwoDC,
                0, 0,
                97, 63,
                RGB(255, 0, 255)
            );
        }
        else if (m_eReplayStatus == REWIND)
        {
            // 역재생
            if (m_vCameraStack.size() != 0)
            {
                CCameraMemento* pCameraMemento = m_vCameraStack.back();

                if (pCameraMemento->Get_Frame_Count() == m_llFrameCount)
                {
                    pCameraMemento = m_vCameraStack.back();
                    m_vCameraStack.pop_back();
                    CCamera::Get_Instance()->Set_LookAt(pCameraMemento->Get_Look_At());
                    CCamera::Get_Instance()->Set_PrevLookAt(pCameraMemento->Get_Prev_Look_At());
                    CCamera::Get_Instance()->Set_m_vDiff(pCameraMemento->Get_Diff());
                    CCameraCareTaker::Get_Instance()->Add_Memento_Front(pCameraMemento);
                }
            }

            Vec2 vLookAt = CCamera::Get_Instance()->Get_LookAt();
            switch (eReplaySceneID)
            {
            case SCENE_ID::SC_STAGE_01:
            {
                HDC hMapDC = CBmpMgr::Get_Instance()->Find_Img(L"Stage01");
                BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY, CReplayMgr::Get_Instance()->Get_Scene_Width(), CReplayMgr::Get_Instance()->Get_Scene_Height(), hMapDC, 0, 0, SRCCOPY);
                break;
            }
            case SCENE_ID::SC_STAGE_02:
            {
                HDC hMapDC = CBmpMgr::Get_Instance()->Find_Img(L"Stage02");
                BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY, CReplayMgr::Get_Instance()->Get_Scene_Width(), CReplayMgr::Get_Instance()->Get_Scene_Height(), hMapDC, 0, 0, SRCCOPY);
                break;
            }
            case SCENE_ID::SC_STAGE_03:
            {
                HDC hMapDC = CBmpMgr::Get_Instance()->Find_Img(L"Stage03");
                BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY, CReplayMgr::Get_Instance()->Get_Scene_Width(), CReplayMgr::Get_Instance()->Get_Scene_Height(), hMapDC, 0, 0, SRCCOPY);
                break;
            }
            }

            if (m_vPlayerStack.size() != 0)
            {
                CMemento* pLastMemento = m_vPlayerStack.back();
                if (pLastMemento->Get_Frame_Count() == m_llFrameCount)
                {
                    pLastMemento = m_vPlayerStack.back();
                    m_vPlayerStack.pop_back();
                    pLastMemento->Print_Memento(_hDC);
                    CPlayerCareTaker::Get_Instance()->Add_Memento_Front(pLastMemento);
                }
            }

            if (m_vEffectStack.size() != 0)
            {
                CMemento* pLastMemento = m_vEffectStack.back();
                if (pLastMemento->Get_Frame_Count() == m_llFrameCount)
                {
                    pLastMemento = m_vEffectStack.back();
                    m_vEffectStack.pop_back();
                    pLastMemento->Print_Memento(_hDC);
                    CEffectCareTaker::Get_Instance()->Add_Memento_Front(pLastMemento);
                }
            }


            if (m_vEnemyStack.size() != 0)
            {
                CEnemyMemento* pLastMemento = m_vEnemyStack.back();
                while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
                {
                    pLastMemento = m_vEnemyStack.back();
                    m_vEnemyStack.pop_back();
                    pLastMemento->Print_Memento(_hDC);
                    CEnemyCareTaker::Get_Instance()->Add_Memento_Front(pLastMemento);

                    if (m_vEnemyStack.size() != 0)
                    {
                        pLastMemento = m_vEnemyStack.back();
                    }
                    else
                    {
                        break;
                    }
                }
            }

            if (m_vBulletStack.size() != 0)
            {
                CBulletMemento* pLastMemento = m_vBulletStack.back();
                while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
                {
                    pLastMemento = m_vBulletStack.back();
                    m_vBulletStack.pop_back();
                    pLastMemento->Print_Memento(_hDC);
                    CBulletCareTaker::Get_Instance()->Add_Memento_Front(pLastMemento);

                    if (m_vBulletStack.size() != 0)
                    {
                        pLastMemento = m_vBulletStack.back();
                    }
                    else
                    {
                        break;
                    }
                }
            }

            if (m_vItemStack.size() != 0)
            {
                CItemMemento* pLastMemento = m_vItemStack.back();
                while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
                {
                    pLastMemento = m_vItemStack.back();
                    m_vItemStack.pop_back();
                    pLastMemento->Print_Memento(_hDC);

                    CItemCareTaker::Get_Instance()->Add_Memento_Front(pLastMemento);

                    if (m_vItemStack.size() != 0)
                    {
                        pLastMemento = m_vItemStack.back();
                    }
                    else
                    {
                        break;
                    }

                }
            }

            if (m_vBloodStack.size() != 0)
            {
                CBloodMemento* pLastMemento = m_vBloodStack.back();
                while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
                {
                    pLastMemento = m_vBloodStack.back();
                    m_vBloodStack.pop_back();
                    pLastMemento->Print_Memento(_hDC);
                    
                    CBloodCareTaker::Get_Instance()->Add_Memento_Front(pLastMemento);
                    if (m_vBloodStack.size() != 0)
                    {
                        pLastMemento = m_vBloodStack.back();
                    }
                    else
                    {
                        break;
                    }
                }
            }
            
            if (m_vDoorStack.size() != 0)
            {
                CDoorMemento* pLastMemento = m_vDoorStack.back();
                while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
                {
                    pLastMemento = m_vDoorStack.back();
                    m_vDoorStack.pop_back();
                    pLastMemento->Print_Memento(_hDC);
                    CDoorCareTaker::Get_Instance()->Add_Memento_Front(pLastMemento);
            
                    if (m_vDoorStack.size() != 0)
                    {
                        pLastMemento = m_vDoorStack.back();
                    }
                    else
                    {
                        break;
                    }
                }
            }

            --m_llFrameCount;

            HDC titleThreeDC = CBmpMgr::Get_Instance()->Find_Img(L"Title3");
            GdiTransparentBlt(
                _hDC,
                50, 50,
                147, 67,
                titleThreeDC,
                0, 0,
                147, 67,
                RGB(255, 0, 255)
            );
        }
        else if (m_eReplayStatus == REPLAY_STATUS::STOP)
        {
            HDC titleFourDC = CBmpMgr::Get_Instance()->Find_Img(L"Title4");
            GdiTransparentBlt(
                _hDC,
                WINCX - 250, 50,
                187, 70,
                titleFourDC,
                0, 0,
                187, 70,
                RGB(255, 0, 255)
            );
        }

        HDC titleOneDC = CBmpMgr::Get_Instance()->Find_Img(L"Title1");
        GdiTransparentBlt(
            _hDC,
            WINCX - 250, WINCY - 100,
            206, 77,
            titleOneDC,
            0, 0,
            206, 77,
            RGB(255, 0, 255)
        );
    }
}

void CReplay::Release()
{
    for_each(m_vPlayerStack.begin(), m_vPlayerStack.end(), Safe_Delete<CMemento*>);
    m_vPlayerStack.clear();

    for_each(m_vEffectStack.begin(), m_vEffectStack.end(), Safe_Delete<CMemento*>);
    m_vEffectStack.clear();

    for_each(m_vEnemyStack.begin(), m_vEnemyStack.end(), Safe_Delete<CEnemyMemento*>);
    m_vEnemyStack.clear();

    for_each(m_vItemStack.begin(), m_vItemStack.end(), Safe_Delete<CItemMemento*>);
    m_vItemStack.clear();

    for_each(m_vCameraStack.begin(), m_vCameraStack.end(), Safe_Delete<CCameraMemento*>);
    m_vCameraStack.clear();

    for_each(m_vBloodStack.begin(), m_vBloodStack.end(), Safe_Delete<CBloodMemento*>);
    m_vBloodStack.clear();

    for_each(m_vDoorStack.begin(), m_vDoorStack.end(), Safe_Delete<CDoorMemento*>);
    m_vDoorStack.clear();

    CReplayMgr::Destroy_Instance();
    CCamera::Destroy_Instance();
    CPlayerCareTaker::Destroy_Instance();
    CCameraCareTaker::Destroy_Instance();
    CEffectCareTaker::Destroy_Instance();
    CEnemyCareTaker::Destroy_Instance();
    CItemCareTaker::Destroy_Instance();
    CBloodCareTaker::Destroy_Instance();
    CDoorCareTaker::Destroy_Instance();
}

void CReplay::Key_Input()
{
    if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
    {
        switch (eReplaySceneID)
        {
        case SCENE_ID::SC_STAGE_01:
        {
            CSceneMgr::Get_Instance()->Change_Scene(SCENE_ID::SC_STAGE_02);
            break;
        }
        case SCENE_ID::SC_STAGE_02:
        {
            CSceneMgr::Get_Instance()->Change_Scene(SCENE_ID::SC_STAGE_03);
            break;
        }
        case SCENE_ID::SC_STAGE_03:
        {
            CSceneMgr::Get_Instance()->Change_Scene(SCENE_ID::SC_BOSS_01);
            break;
        }
        case SCENE_ID::SC_BOSS_02:
        {
            break;
        }
        }
    }

    if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT))
    {
        CSoundMgr::Get_Instance()->StopSound(REPLAY_EFFECT);
        CSoundMgr::Get_Instance()->PlaySound(L"pause.wav", REPLAY_EFFECT, 1.f);
        m_eReplayStatus = REPLAY_STATUS::PLAY;
        if (m_llFrameCount == 0)
        {
            m_llFrameCount += 1;
        }
    }
    
    if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT))
    {
        CSoundMgr::Get_Instance()->StopSound(REPLAY_EFFECT);
        CSoundMgr::Get_Instance()->PlaySound(L"pause.wav", REPLAY_EFFECT, 1.f);
        m_eReplayStatus = REPLAY_STATUS::REWIND;
        if (m_llFrameCount == CReplayMgr::Get_Instance()->Get_Full_Frame() - 1)
        {
            m_llFrameCount -= 1;
        }
    }

    if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
    {
        CSoundMgr::Get_Instance()->StopSound(REPLAY_EFFECT);
        CSoundMgr::Get_Instance()->PlaySound(L"pause.wav", REPLAY_EFFECT, 1.f);
        m_eReplayStatus = REPLAY_STATUS::STOP;
    }

    if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))
    {
        CSoundMgr::Get_Instance()->StopSound(REPLAY_EFFECT);
        CSoundMgr::Get_Instance()->PlaySound(L"pause.wav", REPLAY_EFFECT, 1.f);
        m_eReplayStatus = REPLAY_STATUS::PLAY;
    }
}
