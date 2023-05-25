#include "library.h"

void* mRMdir(void* temp_name)
{
  char* fname=(char*)temp_name;
  if(rmdir(fname)==-1)//파일삭제 실패
    fprintf(stderr, "%s directory remove error: %s\n", fname, strerror(errno));
}

void RMDIR(int argc,char* argv[])
{
      int num = argc - 1;
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