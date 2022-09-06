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
3. 추가적인 보드 메니저에 다음을 입력해줍니다. ```https://dl.espressif.com/dl/package_esp32_index.json```  

![환경설정 이미지](https://github.com/uichan8/esp32_MicroProcesser2022_2/blob/main/images/%ED%99%98%EA%B2%BD%EC%84%A4%EC%A0%95.png)  
  
4. 다시 아두이노 IDE로 돌아와서 맨 위에 탭에서 툴 -> 보드 : "~" -> 보드 매니저 를 들어가줍니다.  
5. ESP32 를 검색 한 후 다운받아 줍니다.(오래 걸립니다)
![보드 매니저 이미지](https://github.com/uichan8/esp32_MicroProcesser2022_2/blob/main/images/%EB%B3%B4%EB%93%9C%20%EB%A7%A4%EB%8B%88%EC%A0%80.png)  
  
6. 툴 -> 보드 -> ESP32 Arduino -> "KITS ESP32 EDU" 를 선택해줍니다.
![환경 선택 이미지](https://github.com/uichan8/esp32_MicroProcesser2022_2/blob/main/images/%ED%99%98%EA%B2%BD%20%EC%84%A0%ED%83%9D.png)  
  
7. CP2102 드라이버를 다운받고, 압축을 풀고, 설치합니다. [CP 드라이버 다운로드 링크](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads)
![설치 이미지](https://github.com/uichan8/esp32_MicroProcesser2022_2/blob/main/images/CP2102%EC%84%A4%EC%B9%98.png)  

### 마이크로 파이썬
출처 : https://blog.naver.com/indifrog21/222328851497
1. VScode를 받아줍니다. [vscode download](https://code.visualstudio.com/)
2. 확장 모듈에서 platformIO IDE 를 검색하고 받아줍니다.
3. ![모듈 검색 이미지]()
