#include<unistd.h>
#include<stdio.h>
#include<stdlib.h> //system()함수가 들어있는 헤더
#include<string.h> //문자열

int main(int argc, char* argv[]) //argc와 argv배열 포인터를 인자로하는 main함수
{
	if (argc < 4) {
		printf("Usage: ./DumbFuzz [Target] [InputFile] [OutPutDir]\n"); // 사용자는 퍼저에 필요한 것(타겟 입력파일 저장위치)이 4개보다 적다면 printf문 출력 
		exit(0); //정상종료
	} 
	
	int num = 0; // 변수 num 선언&초기화
	int error = 0; // 변수 error 선언&초기화
	
	printf("[+] Start Dumb Fuzzing....\n"); // 덤퍼저 시작을 알리는 출력문

	while (num < 100) //num이 100미만일 동안 반복
	{
		unsigned char cmd[2024]; // 양수 2024바이트 문자형 cmd 배열 생성
		sprintf(cmd, "echo %s | radamsa", argv[2]); //cmd 문자열에 'echo argv[2]=inputfile | radamsa'을 출력 (radamsa왜사용..?)
		FILE* stream = popen(cmd, "r"); //파일포인터 stream ; 파이프오픈? cmd(를) 파이프로 표준 풀력 내용을 읽기 위해 사용
		
		unsigned char buf[1024]; //양수 1024바이트 문자형 buf 배열 생성
		if (stream != NULL) { //stream이 null이 아니라면
			fgets(buf, 1024, stream); // stream의 문자열을 최대 1024까지 읽어 buf에 담는다.
			printf("[+] input : %s\n", buf);//[+]input : buf문자열 출력
		}
		pclose(stream); //닫기
		
		printf("len : %d\n",strlen(buf)); //buf의 문자열 길이 출력
		for(int i=0; i<strlen;(buf);i++); //
		{
			printf("%2x",buf[i]);//buf[i]를 두자리 hexcode로 출력
			if(buf[i] == '\x0a') //buf[i]가 줄바꿈되면
				buf[i]='\x00'; // buf[i]에 null대입
		}

		printf("\n");
		sprintf(cmd, "python -c \'print \"%s\"\' | %s", buf, argv[1]); // cmd문자열에 python -c'print"buf"' | argv[1]
		printf("[+] cmd : %s", cmd);// [+] cmd : cmd 문자열 출력
		int result = system(cmd); //cmd을 result에 대입
		printf("[+] Program Terminated\n");
		printf("[+] result : %d\n", result); // [+] result : result값 출력
		if (result != 0)
		{
			printf("error!\n");
			error++;
			FILE* fp = fopen(argv[3], "a+");//파일포인터 fp; argv[3]=ouputdir을 파일 읽기 및 덧붙이기 형식으로 연다
			fwrite(buf, sizeof(buf), 1, fp);// buf에 있는 정수 1개를 fp에 저장
			fclose(fp); //파일 닫기
		}
		else
		{
			printf("good\n");
			num++;
		}
	}
	printf("[+] Fuzzing Done!\n");
	printf("[+] error : %d\n", error);
}
