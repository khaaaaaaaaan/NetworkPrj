Network Programing


유의사항
1. server와 client는 같은 폴더에 있으면 정상작동하지 않습니다.

사용법
1. server [포트번호]

2. client [서버ip 주소] [포트번호]
    - 입력 명령어
        1. pull [파일 이름] : 서버내 파일 다운로드
        2. push [파일 이름] : 서버내 파일 업로드
        3. vim [파일 이름] : 서버내 파일을 받아 vi 작동, 종료시 자동으로 push 실행
        4. rm [파일 이름] : 서버내 존재하는 파일을 삭제합니다.
        5. exit : 프로그램을 종료합니다
