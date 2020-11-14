#include<unisd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h> //문자열

int main(int argc, char* argv[]) //argc와 argv배열 포인터를 인자로하는 main함수
{
	if (argc < 4) {
		printf("Usage: ./DumbFuzz [Target] [InputFile] [OutPutDir]\n");
		exit(0); //정상종료
	}
	int num = 0;
	int error = 0;
	printf("[+] Start Dumb Fuzzing....\n");

	while (num < 100) //num이 100미만일 동안 반복
	{
		unsigned char cmd[2024]; //2024바이트 cmd배열
		sprintf(cmd, "echo %s | radamsa", argv[2]); //cmd 문자열에 'echo argv[2] | radamsa'저장
		FILE* stream = popen(cmd, "r"); //파일포인터 stream ; 파이프오픈? cmd(를) 파이프로 표준 풀력 내용을 읽기 위해 사용
		
		unsigned char buf[1024]; //1024바이트 buf배열
		if (stream != NULL) {
			fgets(buf, 1024, stream); // fgets():파일에 문자열을 쓰는 함수 -> stream의 문자열을 최대 1024까지 읽어 buf에 담는다.
			printf("[+] input : %s\n", buf);
		}

	}
}
