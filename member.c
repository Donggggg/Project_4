#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Info{
	char id[30]; //ID
	char password[30]; //비밀번호
	char name[20]; //이름
	char email[30]; //이메일
	char phone[15]; //번호
	char nickname[20]; //닉네임
	int member_number; //고유 회원번호
	int win; // 승리 횟수 저장
	int lose; // 패배 횟수 저장 [위 둘을 통해 승률 계산]
	int manage; // 관리자 유무

} Info;


void inputInfo(){
	FILE *fp = fopen("info.txt","ab+");
	Info input, person_list[100];
	int N = 0, read_check; //갖고 올 회원 수

	rewind(fp); //회원 리스트에다가 기존 회원의 정보들 삽입
	while(fread(&person_list[N], sizeof(Info),1,fp)){ 
		N+=1;
	}

	while(1){
		int isExist = 0;
		printf("사용하실 ID를 입력하세요 : ");
		scanf("%s", input.id);

		for(int i = 0; i <= N; i++){
			if(strcmp(input.id, person_list[i].id) == 0){ //만약 닉네임이 겹치면
				printf("겹치는 ID가 존재합니다. 다시 입력해주세요\n");
				isExist = 1;
				break;
			}
		}
		if(isExist == 0)
			break;
	}
	printf("패스워드를 입력하세요(4-12자) : ");
	scanf("%s", input.password);
	printf("이름을 입력하세요 : ");
	scanf("%s", input.name);
	printf("이메일을 입력하세요 : ");
	scanf("%s", input.email);
	printf("전화번호를 (-)을 생략하고 입력하세요 : ");
	scanf("%s", input.phone);
	while(1){
		int isExist = 0;
		printf("사용하실 닉네임을 입력하세요 : ");
		scanf("%s", input.nickname);
		for(int i = 0; i <= N; i++){
			if(strcmp(input.id, person_list[i].id) == 0){ //만약 닉네임이 겹치면
				printf("겹치는 ID가 존재합니다. 다시 입력해주세요\n");
				isExist = 1;
				break;
			}
		}
		if(isExist == 0)
			break;
	}

	printf("관리자 계정으로 생성하시겠습니까? (1/0) : ");
	scanf("%d",&input.manage);
	
	input.member_number = N+1;

	fseek(fp,0,SEEK_END); //맨 끝으로 이동
	fwrite(&input,sizeof(Info),1,fp); //이진 파일로 저장
	printf("\n회원가입이 완료되었습니다!\n");
	fclose(fp);

}



Info login(){	
	FILE *fp = fopen("info.txt","ab+");
	Info person_list[100];
	char check_id[30], check_password[30];
	int isExist = 0, N = 0, me; //로그인 닉네임 체크, 갖고 올 회원 수, 몇 번째 회원

	rewind(fp); //회원 리스트에다가 기존 회원의 정보들 삽입
	while(fread(&person_list[N], sizeof(Info), 1, fp)){ 
		N+=1;
		//	fread(&person_list[N],sizeof(Info),1,fp);
	}
	while(1){
		int isokay = 0;
		printf("ID : "); //ID 로그인 과정
		scanf("%s",check_id);
		for(int i = 0; i <= N; i++){
			if(strcmp(check_id, person_list[i].id) == 0){ //만약 닉네임이 겹치면
				isExist = 1;
				me = i; // 해당 번째 인물 위치 저장
				isokay = 1; //while 탈출!
				break;
			}
		}
		if(isExist == 0){
			printf("존재하지 않는 ID입니다. 다시 입력하세요\n");
			continue;
		}
		if(isokay==1) //닉네임 완료 
			break;
	}
	while(1){ //패스워드 로그인 과정

		printf("Password : ");
		scanf("%s", check_password);
		if(strcmp(check_password, person_list[me].password)==0){
			printf("\n로그인이 성공했습니다.\n");
			break;
		}
		else{
			printf("패스워드가 틀립니다. 다시 입력하세요\n");
			continue;
		}
	}

	fclose(fp);
	return person_list[me];
}

void searchIdPass(int check){
	FILE *fp = fopen("info.txt","ab+");
	Info person_list[100];
	int N = 0, idExist = 0, M = 0;
	char input_info[5][30]; // 0:ID 1:이름 2:닉네임 3:이메일 4:번호
	rewind(fp);

	while(fread(&person_list[N], sizeof(Info),1,fp)){ 
		N+=1;
	}

	if(check==1){ //ID 찾기
		printf("ID를 찾기 위한 정보를 입력하세요\n");
		printf("이름 : ");
		scanf("%s",input_info[1]);
		printf("E-mail : ");
		scanf("%s",input_info[3]);
		printf("번호(휴대폰 - 없이) : ");
		scanf("%s",input_info[4]);

		for(int i = 0; i <= N; i++){
			if(strcmp(person_list[i].name, input_info[1]) == 0 && strcmp(person_list[i].email, input_info[3]) == 0 && strcmp(person_list[i].phone, input_info[4]) == 0){
				idExist = 1;
				printf("\n입력하신 정보와 일치하는 ID를 찾았습니다.\n");
				printf("ID : %s\n",person_list[i].id);
				break;
			}
		}
		if(idExist == 0)
			printf("\n입력하신 정보와 일치하는 ID가 존재하지 않습니다.\n");
	}

	else if(check == 2){ //비밀번호 찾기

		printf("ID를 입력하세요 : ");
		scanf("%s",input_info[0]);
		for(int i = 0; i <= N; i++){
			if(strcmp(person_list[i].id, input_info[0]) == 0){
				idExist = 1;
				M = i;
				break;
			}
		}
		if(idExist == 0)
			printf("입력하신 ID가 존재하지 않습니다.\n");
		else{
			printf("비밀번호를 찾기 위한 정보를 입력하세요\n");
			printf("이름 : ");
			scanf("%s",input_info[1]);
			printf("E-mail : ");
			scanf("%s",input_info[3]);
			printf("번호(휴대폰 - 없이) : ");
			scanf("%s",input_info[4]);

			if(strcmp(person_list[M].name, input_info[1]) == 0 && strcmp(person_list[M].email, input_info[3]) == 0 && strcmp(person_list[M].phone, input_info[4]) == 0){
				printf("\n입력하신 정보와 일치하는 비밀번호를 찾았습니다.\n");
				printf("비밀번호 : %s",person_list[M].password);
			}
			else
				printf("\n입력하신 정보와 일치하는 비밀번호가 존재하지 않습니다.\n");
		}
	}

	fclose(fp);
}

void manageMember(){	
	FILE *fp = fopen("info.txt","ab+");
	Info person_list[100];
	int N = 0, go, input_memnum;
	rewind(fp);
	while(fread(&person_list[N], sizeof(Info),1,fp)){ 
		N+=1;
	}
	while(1){
		printf("\n===============================================\n");
		printf("1. 회원 명부 출력 / 2. 회원 삭제 / 3. 관리자 모드 종료\n입력: ");
		scanf("%d",&go);

		if(go == 1){
			printf("\n===============================================\n");
			for(int i = 0; i < N; i++)
				printf("%02d| 회원번호: %d / 이름: %s / 닉네임: %s / ID: %s / PW: %s\n", i+1,person_list[i].member_number, person_list[i].name, person_list[i].nickname, person_list[i].id, person_list[i].password);
		}
		else if(go == 2){ // 
			printf("삭제하실 회원의 회원번호를 입력하세요 : ");
			scanf("%d",&input_memnum);
			for(int i = 0; i <= N; i++){
				if(person_list[i].member_number == input_memnum)
					break;
			}
		}
		else
			break;
	}
}

int printMenu(Info member){
	int go; 
	if(member.manage == 1){ //관리자
		printf("\n===============================================\n");
		printf("1. 로그인 / 2. 회원가입 / 3. 로그인 정보 출력 / ");
		printf("4. ID 찾기 / 5. 비밀번호 찾기 / 6. 로그아웃 / 7. 종료\n");
		printf("관리자 메뉴 [ 8. 회원 관리 / 9. 승률 패치 ]\n");
		printf("입력 : ");
		scanf("%d",&go);

	}
	else{
		printf("\n===============================================\n");
		printf("1. 로그인 / 2. 회원가입 / 3. 로그인 정보 출력 / ");
		printf("4. ID 찾기 / 5. 비밀번호 찾기 / 6. 로그아웃 / 7. 종료\n");
		printf("입력 : ");
		scanf("%d",&go);

	}
	return go;
}


int main(){
	int go, login_check = 0; //메뉴 이동(일반, 관리자 버전), 로그인 체크
	Info member; //로그인한 멤버의 정보를 저장
	go = printMenu(member);
	while(1){
		if(go == 1){
			member = login();
			login_check = 1;
		}	
		else if(go == 2){
			inputInfo();
		}
		else if(go == 3){
			if(login_check == 0)
				printf("로그인이 필요합니다.\n");
			else{
				printf("\nID: %s\n", member.id);
				printf("Password: %s\n", member.password);
				printf("Name: %s\n", member.name);
				printf("E-mail: %s\n", member.email);
				printf("Phone-number: %s\n", member.phone);
				printf("NickName: %s\n", member.nickname);
				printf("Member_number: %d\n", member.member_number);
			}
		}	
		else if(go == 4){
			searchIdPass(1);
		}
		else if(go == 5){
			searchIdPass(2);
		}
		else if(go == 6){
			member.manage = 0;
			login_check = 0;
			printf("로그아웃이 완료되었습니다.\n");
		}
		else if(go == 8 && member.manage == 1){
			manageMember();
		}
		else if(go == 9 && member.manage == 1){
			break; //아직 구현X
		}
		else 
			break;
		go = printMenu(member);

	}



}
