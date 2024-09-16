# [WINAPI] Katana Zero 모작
2주동안 WINAPI로 만든 Katana Zero 모작 게임입니다.

# 게임 주요 사진
## 스테이지 구성
스테이지는 총 5개의 Stage로 구성되어 있습니다.

### Normal Stage 
![stage1gif](https://github.com/user-attachments/assets/24af90bf-78e5-4a5f-a10e-561a5405509d) 
![stage2gif](https://github.com/user-attachments/assets/f6f5b33d-0be3-4f34-bc00-f34f12da8a61) 
![stage3gif](https://github.com/user-attachments/assets/6feb7e01-1df0-41d2-b284-c42c58779067)

### Boss Stage
#### Boss Stage1
![stage4gif](https://github.com/user-attachments/assets/3beae129-3f16-479b-9200-9cb043f64743)
#### Boss Stage2
![stage5gif](https://github.com/user-attachments/assets/4a6227ef-26c2-497d-88ee-4c9c8566e0af)

## 구현 컨텐츠 및 기능 설명
### 1. 시간 되돌리기
객체를 이전 상태로 되돌리는 메멘토 패턴을 이용해 시간 되돌리기 컨텐츠를 구현했습니다.

![timesleep1-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/571fe536-851d-44ad-a502-11e5b81ecef9)
![timesleep2-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/7d0f720e-561b-4d74-88b7-17714f354eaf)

### 2. 간단한 동영상 플레이어
Deque 자료구조를 이용해 재생, 일시정지, 되감기 기능이 담겨있는 간단한 동영상 플레이어를 구현했습니다.

![replayPlay-ezgif com-video-to-gif-converter (online-video-cutter com)](https://github.com/user-attachments/assets/7debf1cc-ae56-4947-86ba-5b0a1deaade3)
![backPlay-ezgif com-video-to-gif-converter (online-video-cutter com)](https://github.com/user-attachments/assets/40532201-315e-454f-93e0-b55649e65e0c)

### 3. 카메라 줌인 줌아웃
카메라 줌인/줌아웃 기능을 StretchBlt 함수를 활용해 구현했습니다. 
이 기능을 Highlight Manager와 결합하여 "하이라이트" 효과를 추가함으로써, 더욱 극적인 분위기를 연출하고자 했습니다.

![highlight1](https://github.com/user-attachments/assets/cd98c1ce-9fb7-4461-a1aa-0e510120b30b)
![highlight2](https://github.com/user-attachments/assets/fe0af3c5-311d-4d36-a91e-e8ba92e121f8)
![highlight3](https://github.com/user-attachments/assets/0d730a09-1cb9-40d9-8a02-6f1b047cafdb)

### 4. 벽력일섬!
![buk1](https://github.com/user-attachments/assets/b90c604f-12d5-4a93-886d-4c47e8f70ff5)
![buk2](https://github.com/user-attachments/assets/a91741b1-4446-48f3-b4d0-a4611333a310)
