# [WINAPI] Katana Zero 모작
2주동안 WINAPI로 만든 Katana Zero 모작 게임입니다.

# 게임 주요 사진
## 스테이지 구성
스테이지는 총 5개의 Stage로 구성되어 있습니다.

### Normal Stage 
일반 스테이지는 총 3개로 구성되어 있습니다.

![stage1gif](https://github.com/user-attachments/assets/24af90bf-78e5-4a5f-a10e-561a5405509d) 
![stage2gif](https://github.com/user-attachments/assets/f6f5b33d-0be3-4f34-bc00-f34f12da8a61) 
![stage3gif](https://github.com/user-attachments/assets/6feb7e01-1df0-41d2-b284-c42c58779067)

### Boss Stage
보스 스테이지는 총 2개로 구성되며, 각 스테이지마다 보스의 체력은 3입니다.

#### Boss Stage1
Boss Stage 1에서는 적들이 랜덤으로 4개의 문 중 하나에서 일정한 시간 간격으로 생성됩니다.

![stage4gif](https://github.com/user-attachments/assets/3beae129-3f16-479b-9200-9cb043f64743)

보스가 총 3번 맞으면 바닥이 폭발하며, 다음 스테이지로 이동합니다.
![Stage1ToStage2](https://github.com/user-attachments/assets/cd563b8f-ed5d-4cd6-8eea-1a2eca769851)

#### Boss Stage1 보스 패턴
보스가 좌측 또는 우측에 랜덤하게 등장하여 캐릭터를 조준한 후 레이저를 발사합니다. 

레이저 발사 후 보스는 다시 좌측 또는 우측으로 랜덤하게 이동하여 다음 공격을 준비합니다.
![BossStage1Pattern1](https://github.com/user-attachments/assets/95857d29-a977-4191-b4ad-c00eeada3b43)

#### Boss Stage2
![stage5gif](https://github.com/user-attachments/assets/4a6227ef-26c2-497d-88ee-4c9c8566e0af)

### Boss Stage2 보스 패턴
#### 1. 폭탄 발사
총 3개의 폭탄을 발사하며, 이 폭탄들은 벽, 천장, 바닥에 충돌할 때 입사각 반사각 공식을 이용해 반사되도록 설계되었습니다.

![BossStage2Pattern1](https://github.com/user-attachments/assets/40626d41-f381-4a42-b83e-83969c87f04e)

#### 2. 레이저 발사
![BossStage2Pattern2](https://github.com/user-attachments/assets/2bfd4488-4bce-406c-9698-81cfbbada552)

#### 3. 기관총 발사
![BossStage2Pattern3](https://github.com/user-attachments/assets/b80a2dd4-152f-45f3-a9ba-a874f5e766b2)

플레이어가 기관총 총알을 공격할 때, 총알을 반사하는 패링이 발동됩니다.
![pairingGif](https://github.com/user-attachments/assets/d5789589-bc7d-4f8f-9bb8-a31fcbd7de0e)

## 구현 컨텐츠 및 기능 설명
### 1. 시간 되돌리기
객체를 이전 상태로 되돌리는 메멘토 패턴을 이용해 시간 되돌리기 컨텐츠를 구현했습니다.

![timesleep1-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/571fe536-851d-44ad-a502-11e5b81ecef9)
![timesleep2-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/7d0f720e-561b-4d74-88b7-17714f354eaf)

### 2. 간단한 동영상 플레이어
Deque 자료구조를 이용해 프레임을 제어하고, 재생, 일시정지, 되감기 기능을 갖춘 간단한 동영상 플레이어를 구현했습니다.

![replayPlay-ezgif com-video-to-gif-converter (online-video-cutter com)](https://github.com/user-attachments/assets/7debf1cc-ae56-4947-86ba-5b0a1deaade3)
![backPlay-ezgif com-video-to-gif-converter (online-video-cutter com)](https://github.com/user-attachments/assets/40532201-315e-454f-93e0-b55649e65e0c)

### 3. 카메라 줌인 줌아웃
카메라 줌인/줌아웃 기능을 StretchBlt 함수를 활용해 구현했습니다. 
이 기능을 Highlight Manager와 결합하여 "하이라이트" 효과를 추가함으로써, 더욱 극적인 분위기를 연출하고자 했습니다.

하이라이트는 특정 인원을 처치하거나, 패링된 총알이 적에게 맞거나, 적의 특정 공격을 피했을 때 발생합니다.

![highlight1](https://github.com/user-attachments/assets/cd98c1ce-9fb7-4461-a1aa-0e510120b30b)
![highlight2](https://github.com/user-attachments/assets/fe0af3c5-311d-4d36-a91e-e8ba92e121f8)
![highlight3](https://github.com/user-attachments/assets/0d730a09-1cb9-40d9-8a02-6f1b047cafdb)

### 4. 벽력일섬!
플레이어의 필살기는 플레이어가 선을 따라 이동하며, 해당 선에 닿아있는 적들을 모두 제거합니다.

![buk1](https://github.com/user-attachments/assets/b90c604f-12d5-4a93-886d-4c47e8f70ff5)
![buk2](https://github.com/user-attachments/assets/a91741b1-4446-48f3-b4d0-a4611333a310)
