#include "library.h"

void Cat(int argc, char* op, char* filename) {//cat함수
    int fdin;
    int cnt = 1;
    char buf[BUFSIZ];
    if (argc == 2) {//파일의 정보를 읽오 오는 함수. //cat file1
        char* pLine;
        FILE* fp = fopen(filename, "r");
        pLine = fgets(buf, BUFSIZ, fp);
        while (!feof(fp)) {//파일이 끝날떄까지 라인을 불러와서 저장하기
            pLine = fgets(buf, BUFSIZ, fp);
            if (pLine != NULL) {
                printf("%s", pLine);//라인을 불러올때마다 출력
            }
        }
        fclose(fp);
    }
    
    if (argc == 3) {//파일을 생성하는 옵션
        if (!strcmp(op, ">")) //cat > newfile
        {
            FILE* fp = fopen(filename, "w");
            char c;
            while ((c = getchar()) != EOF) {//ctrl+D로 저장하고 종료
                fputc(c, fp);
            }
            fclose(fp);
        }
        if (!strcmp(op, "-n"))//파일에 줄을 붙혀서 출력해주는 옵션
        {
            char* pLine;
            FILE* fp = fopen(filename, "r");
            pLine = fgets(buf, BUFSIZ, fp);
            while (!feof(fp)) {
                pLine = fgets(buf, BUFSIZ, fp);
                if (pLine != NULL) {
                    printf("%d", cnt++);
                    printf("%s", pLine);
                }
            }
            fclose(fp);
        }
    }
}