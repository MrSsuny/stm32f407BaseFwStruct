`.cproject`, `.project` 파일이 누락되었거나 Git에서 일부러 제외한 상태에서 STM32CubeIDE에서 **자동 재생성하는 절차**

이 절차는 주로 다음과 같은 상황에서 사용됩니다:

- `.ioc`만 GitHub로 공유한 경우
    
- 팀원이 처음 프로젝트를 클론한 후 `.project`, `.cproject` 없이 시작할 때
    
- 기존 워크스페이스를 새로 만든 경우
    

---

## ✅ `.cproject`, `.project` 자동 재생성 절차 (STM32CubeIDE 기준)

### 📌 전제 조건

- `.ioc` 파일은 존재해야 함
    
- CubeIDE는 설치되어 있고, 새 워크스페이스가 준비됨
   
---

### 🪜 STEP 1. STM32CubeIDE 실행 후 새 워크스페이스 선택

```plaintext
예: D:\workspace_new\myproject1
```

> 워크스페이스는 Git으로 관리되지 않음 → 각자 PC에 맞게 자유롭게 선택

---

### 🪜 STEP 2. `.ioc` 파일 열기

- [File] → [Open Projects from File System] 선택  
    또는 [File] → [Open File...] 사용해서 직접 `.ioc` 열기
    

```plaintext
예: D:\projectCode\myproject1_code\myproject1.ioc
```

> `.ioc` 파일을 열면 CubeMX GUI가 실행되며, 프로젝트 설정을 읽어옴

---

### 🪜 STEP 3. [Project] → [Generate Code] 클릭

- CubeMX 설정 화면에서 우측 상단에 있는 **[GENERATE CODE]** 버튼 클릭
    
- 그러면 다음 항목이 자동 생성됨:
    
    - `.cproject`
        
    - `.project`
        
    - `.settings/` 폴더
        
    - `.launch` (디버그 설정, 선택적)
        

---

### 🪜 STEP 4. 프로젝트 자동 등록 및 인식 확인

- STM32CubeIDE의 프로젝트 탐색기(Project Explorer)에 해당 프로젝트가 등록됨
    
- 기본 빌드 환경, 디버깅 설정까지 구성된 상태
    

---

### ✅ 참고 이미지 (절차 요약)

```
[STM32CubeIDE 실행] → [Open .ioc] → [GENERATE CODE]
                          ↓
   자동으로 .project / .cproject / .settings 생성
                          ↓
           [Project Explorer에 자동 등록됨]
```

---

## ⚠️ 주의사항

|주의 항목|설명|
|---|---|
|기존에 같은 이름의 프로젝트가 등록되어 있으면|덮어쓰지 않음. 이름 변경하거나 기존 삭제 후 진행|
|CubeMX 설정이 유효하지 않으면|코드 생성 실패할 수 있음 (`.ioc` 손상된 경우)|
|빌드 설정이 초기 상태일 수 있음|예: Debug/Release 세부 설정은 수동 재구성 필요 가능|

---

## ✅ 요약

|항목|내용|
|---|---|
|**재생성 대상**|`.cproject`, `.project`, `.settings/`|
|**필요 조건**|`.ioc` 파일만 있으면 됨|
|**IDE 메뉴**|[File] → [Open File] → `.ioc` 열기 → [GENERATE CODE]|
|**자동 등록 여부**|CubeIDE가 자동으로 프로젝트 등록함|

---

원하시면 이 절차를 문서나 이미지 포함된 문서형 PDF로 정리해서 드릴 수도 있습니다.  
또는 `.cproject`와 `.project`가 깨졌을 때의 **복구 전략**도 안내해드릴 수 있어요.