#include "library.h"

void* makedir(void* temp_name)
{
    int flag;
    char* fname = (char*)temp_name;
    flag = mkdir(fname, 0755);
    if (flag < 0)
    {
        perror("디렉토리 생성 오류! \n");
    }

}

void Mmkdir(int argc, char* argv[])//여러개의 디렉토리를 생성하는 함수.
{
    int num = argc - 2; //입력받은 함수&명령어의 개수 조작
    pthread_t p_thread[num];    //멀티스레드 생성
    int thr_check;
    if (!strcmp(argv[1], "mkdir")) {
        for (int i = 0; i < num; i++)
        {
            thr_check = pthread_create(&p_thread[i], NULL, makedir, (void*)argv[i + 2]);//스레드를 생성하여 makedir함수를 실행
            if (thr_check < 0)
            {
                perror("thread create error : \n");
            }
        }
    }
    for (int i = 0; i < num; i++)
    {
        pthread_join(p_thread[i], NULL);//스레드가 종료될떄까지 기다려줌
    }
}

void Omkdir(char* op, char* fname, char* filemode)//하나의 디렉토리를 생성하는 옵션
{
    int result = 0;
    int mode = (filemode[0] - 48) * 64 + (filemode[1] - 48) * 8 + (filemode[2] - 48);
    if (strcmp(op, "-p") == 0)
    {
        int t = strlen(fname);
        char* path;
        for (int i = 0; i <= t; i++)
        {
            path[i] = fname[i];
            if (path[i] == '/' || path[i] == '\0') {//파일과 디렉토리를 / 기준으로 나눠줌
                path[i] = '\0';//디렉토리 이름이 완료됐음을 표시해줌
                result = mkdir(path, mode);
                path[i] = '/';
                if(result<0)
                  printf("파일 생성에 실패했습니다\n");
            }
        }
    }

    else {
        result = mkdir(fname, mode);
        if(result<0)
          printf("파일 생성에 실패했습니다\n");
    }
}

void* mRMdir(void* temp_name)
{
  char* fname=(char*)temp_name;
  if(rmdir(fname)==-1)//파일삭제 실패
    fprintf(stderr, "%s directory remove error: %s\n", fname, strerror(errno));
}

void RMDIR(int argc,char* argv[])
{
      int num = argc - 2;
      pthread_t p_thread[num];
      int thr_id;
      char path[1024];
      if (!strcmp(argv[2], "-p")) {//상위 디렉토리도 함께 삭제.
          strcpy(path, argv[3]);
          int t = strlen(path);
          for (int i = t; i > -1; i--)
          {
              if (path[i] == '/')//디렉토리들을 /기준으로  나눠준다.
                  path[i] = '\0';// 끊어진 디렉토리를 저장해준다.
              if (path[i] == '\0') {
                  if (rmdir(path) == -1) {
                      fprintf(stderr, "%s directory remove error: %s\n", path, strerror(errno));
                  }
              }
          }
      }
      
      else{
        for (int i = 0; i < num; i++)
        {
          thr_id = pthread_create(&p_thread[i], NULL, mRMdir, (void*)argv[i + 2]);
        }
        for (int i = 0; i < num; i++)
        {
          pthread_join(p_thread[i],NULL);
        }
    }
}


void Cat(int argc, char* op, char* filename) {//cat함수
    int fdin;
    int cnt = 1;
    char buf[BUFSIZ];
    if (argc == 3) {//파일의 정보를 읽오 오는 함수. //cat file1
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
    
    if (argc == 4) {//파일을 생성하는 옵션
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

