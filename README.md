# 마이크로 프로세서 공학
2022년 2학기 마이크로 프로세서 공학 수업 관련 코드입니다.
## 프로젝트 설명

## 하드웨어
- ESP32-PICO-V3  [제품 링크](https://www.indifrog.co.kr/product/ifzero-board-lite-%EC%95%84%EB%91%90%EC%9D%B4%EB%85%B8-%ED%98%B8%ED%99%98-%EB%B8%94%EB%A3%A8%ED%88%AC%EC%8A%A4-%EC%99%80%EC%9D%B4%ED%8C%8C%EC%9D%B4-%EB%AA%A8%EB%93%88-%EB%B3%B4%EB%93%9C-%EC%95%84%EB%91%90%EC%9D%B4%EB%85%B8cc%EB%A7%88%EC%9D%B4%ED%81%AC%EB%A1%9C%ED%8C%8C%EC%9D%B4%EC%8D%AC/107/category/49/display/1/)

## 설정
### 아두이노 IDE
출처 : https://blog.naver.com/indifrog21/222327584069
1. 아두이노 IDE를 다운받고 설치합니다. [아두이노 IDE 다운 링크](https://www.arduino.cc/en/software)
2. 아두이노 IDE를 열어주고 맨 위에 탭에서 파일 -> 환경설정을 열어줍니다.
3. 추가적인 보드 메니저에 다음을 입력해줍니다.  
```https://dl.espressif.com/dl/package_esp32_index.json```  
[환경설정 이미지]()
4. 다시 아두이노 IDE로 돌아와서 맨 위에 탭에서 툴 -> 보드 : "~" -> 보드 매니저 를 들어가줍니다.
5. ESP32 를 검색 한 후 다운받아 줍니다.(오래 걸립니다)
[보드 매니저 이미지]()
6. 툴 -> 보드 -> ESP32 Arduino -> "KITS ESP32 EDU" 를 선택해줍니다.
[환경 선택 이미지]()
7. CP2102 드라이버를 다운받고, 압축을 풀고, 설치합니다. [CP 드라이버 다운로드 링크](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads)
[설치 이미지]()

### 마이크로 파이썬
