#include<iostream>
#include<time.h>
#include<conio.h>//_kbhit(),_getch()
#include<Windows.h>//gotoxy 함수
#include <stdlib.h> //srand, rand
#pragma warning(disable: 4996)

using namespace std;


class game{

protected:
	int m_time;  //제한시간
	int m_combo; //콤보 수
	int m_best_combo; //최대 콤보 수
	int speed_t;   //깜빡이는 시간
	int m_score; //점수


public:
	void Calc_score();//점수계산
	void Print_gameover();//게임종료화면 출력
	void Print_score();  //점수창 출력
	
	friend void gotoxy(int x,int y); //커서 위치 옮기기
	friend void bling(char *str,int x,int y); //한번 깜빡이며 

	friend int get_key();   //입력 키 인식
	friend void clean_screen();//화면 지우기*/

};

void game::Calc_score(){
	
	if(0<=m_combo&&m_combo<5)
		m_score+=10;
	else if(5<=m_combo&&m_combo<10)
		m_score+=15;
	else if(10<=m_combo&&m_combo<15)
		m_score+=20;
	else if(15<=m_combo&&m_combo<20)
		m_score+=25;
	else 
		m_score+=30;
}

void game:: Print_gameover(){//게임종료화면 출력

	clean_screen();//화면 지우기
	cout<<"\n";
	

	cout<<"===========================================================================\n";
	cout<<"==     =====  =====   =====   =     =======     ==  ======= =     ==    ===\n";
	cout<<"=  ===  === == ====  = === =  =  =========  ===  == ====== ==  ===== === ==\n";
	cout<<"=  =======      ===  == = ==  =     ======  ===  === ==== ===     ==    ===\n";
	cout<<"=  ==   =  ====  ==  === ===  =  =========  ===  ==== == ====  ===== ==  ==\n";
	cout<<"===   = = ====== ==  =======  =     =======    =======  =====     ==  ==  =\n";
	cout<<"===========================================================================\n";
	
	//□

	gotoxy(35,10);
	cout<<"점수 : " 
		<<m_score;
	gotoxy(31,11);
	cout<<"최대 콤보 수 : "
		<<m_best_combo;
	gotoxy(28,14);
	cout<<"- 게임을 종료합니다. -";
	
	int key=0;

	bling("Enter",35,15);
}


void game::Print_score(){//점수창 출력

	gotoxy(47,5);  cout<<"=====================";
	for(int i=6;i<16;i++){
		gotoxy(47,i); 
		cout<<			 "|                   |";
	}
	gotoxy(47,16); cout<<"=====================";

	gotoxy(56,7);   cout<<"시간";
	gotoxy(56,10);	cout<<"점수";
	gotoxy(56,13);	cout<<"콤보";

}



//-------------------------------------------------game 부모 클래스---------------------------------------------------------




class game_easy:public game{
protected:
	char m_key[4];//두더지 장소

public:
	void e_Initialize();
	void e_Print_screen(); //게임화면 출력
	void e_Game();   //게임 구현
	void e_cursor_change(int num); //네모 칸 속 커서 위치 옮기기	
};

void game_easy::e_Initialize(){//초기화
	m_time=60;
	m_combo=0;
	m_best_combo=0;
	speed_t=2000;   
	m_score=0;
	for(int i=0;i<4;i++)
		m_key[i]=0;
}



void game_easy::e_Print_screen(){
	gotoxy(0,0);
	cout<<"\n";
	

	cout<<"==========================================================================\n";
	cout<<"==========================================================================\n";
	gotoxy(0,22);
	cout<<"==========================================================================\n";
	cout<<"==========================================================================\n";
	
	gotoxy(0,6);
			
	cout<<"	  □□□□□□□□□\n";
	cout<<"	  □      □      □\n";
	cout<<"	  □      □      □\n";
	cout<<"	  □      □      □\n";
	cout<<"	  □□□□□□□□□\n";
	cout<<"	  □      □      □\n";
	cout<<"	  □      □      □\n";
	cout<<"	  □      □      □\n";
	cout<<"	  □□□□□□□□□\n";

	
	
	Print_score();//점수창 출력
		
	gotoxy(56,8);
	cout<<"1:00";
	gotoxy(57,11);
	cout<<m_score;
	gotoxy(57,14);
	cout<<m_combo;
	

}

void game_easy:: e_Game(){//게임화면 출력
	
	gotoxy(36,10); cout<<"3";
	Sleep(1000);
	gotoxy(36,10); cout<<"2";
	Sleep(1000);
	gotoxy(36,10); cout<<"1";
	Sleep(1000);
	gotoxy(34,10); cout<<"Start!!";
	Sleep(1000);
	
	e_Print_screen();

	srand((unsigned)time(NULL));
	int random=0;		  //위치 랜덤으로 생성 (0~3)
	char random_alpha=' ';//알파벳 랜덤으로 생성(65~90)

	int back_t=clock();//제한시간
	int now_t=clock();
	char key;
	int i,j;//반복 변수 선언

	while(m_time!=0){
		if((clock()-now_t==0)||(clock()-now_t>=speed_t)){//지정된 시간만큼 지나면
			e_cursor_change(random);//랜덤 위치로 이동
			cout<<"  ";//그 자리를 비우고
			m_key[random]=' '; //key값도 비운다.
		

			random=rand()%4; //위치를 랜덤으로 만든다.
			random_alpha=65+rand()%26; //알파벳 대문자를 랜덤으로 만든다.
			
			e_cursor_change(random); //랜덤인 위치로 이동한다.

			m_key[random]=random_alpha;//key값에 랜덤으로 만든 알파벳을 넣는다.			
			cout<<m_key[random];//만든 랜덤 알파벳을 출력한다.

			now_t=clock(); //현재시간은 now_t에 저장한다.
		}
	
		gotoxy(56,8); 
		
		if(clock()-back_t>=1000){//1초 경과하면
			m_time--; //제한시간-1
			cout<<"0:";
			if(m_time<10) //시간의 한자리 남았을때
				cout<<"0" //앞에 0을 출력한다.
					<<m_time;
			else
				cout<<m_time;
			back_t=clock(); //제한시간을 위한 시간에 현재시간을 넣는다.
		}
		
		if(_kbhit()){		//입력
			key=_getch();	//key를 읽는다.


			if(key>='a')//소문자이면
				key=key-('a'-'A');		//대문자로 바꾼다.

			j=-1;
				

			for(i=0;i<4;i++){	//0~4까지 i를 1씩 더해가며
				if(m_key[i]==key) //맞는 문자가 있는지 확인
					j=i;		//있으면 j에 넣는다.
			}
				
			if(j!=-1){	//맞는 문자가 있으면
				e_cursor_change(j);
				cout<<"  ";
				m_key[j]=' ';
				m_combo=m_combo+1;
				Calc_score();//콤보수에 대한 점수를 더해준다.
				if(m_best_combo<m_combo)//최대 콤보보다 현재 콤보수가 크면
					m_best_combo=m_combo;//최대 콤보에 현재 콤보수를 넣는다.
					
				gotoxy(57,11);
				cout<<m_score;//점수 출력
				gotoxy(57,14);
				cout<<m_combo;//콤보 출력
		
				if(speed_t>800)//스피드가 800이상인경우 뒤로 갈수록
					speed_t-=22;//스피드가 빨라진다.->어려워진다.
				
			}
			
			else{ //맞는 문자가 없으면
				m_combo=0;//콤보 0으로 초기화
				gotoxy(57,14);
				cout<<"0    ";
			}
		}//입력 끝
		
				

		
	}
	gotoxy(34,10); cout<<"여기까지!!";
	Sleep(2000);

}





void game_easy ::e_cursor_change(int num){
	if(num==0)
		gotoxy(15,8);
	else if(num==1)
		gotoxy(22,8);
	else if(num==2)
		gotoxy(15,12);
	else if(num==3)
		gotoxy(22,12);
}



//----------------------------------------------game easy 클래스-------------------------------------------------------------------------



class game_normal:public game{
protected:
	char m_key[9];//두더지 장소


public:
	void n_Initialize();//초기화
	void n_Print_screen(); //게임화면 출력
	void n_Game();   //게임 구현
	void n_cursor_change(int num); //네모 칸 속 커서 위치 옮기기	

};

void game_normal::n_Initialize(){//초기화
	m_time=60;
	m_combo=0;
	m_best_combo=0;
	speed_t=2000;   
	m_score=0;
	for(int i=0;i<9;i++)
		m_key[i]=0;
}


void game_normal::n_Print_screen(){
	gotoxy(0,0);
	cout<<"\n";
	

	cout<<"==========================================================================\n";
	cout<<"==========================================================================\n";
	gotoxy(0,22);
	cout<<"==========================================================================\n";
	cout<<"==========================================================================\n";
	
	gotoxy(0,5);
			
	cout<<"  □□□□□□□□□□□□□\n";
	cout<<"  □      □      □      □\n";
	cout<<"  □      □      □      □\n";
	cout<<"  □      □      □      □\n";
	cout<<"  □□□□□□□□□□□□□\n";
	cout<<"  □      □      □      □\n";
	cout<<"  □      □      □      □\n";
	cout<<"  □      □      □      □\n";
	cout<<"  □□□□□□□□□□□□□\n";
	cout<<"  □      □      □      □\n";
	cout<<"  □      □      □      □\n";
	cout<<"  □      □      □      □\n";
	cout<<"  □□□□□□□□□□□□□";
	
	
	Print_score();//점수창 출력
		
	gotoxy(56,8);
	cout<<"1:00";
	gotoxy(57,11);
	cout<<m_score;
	gotoxy(57,14);
	cout<<m_combo;
	

}

void game_normal:: n_Game(){//게임화면 출력
	
	
	gotoxy(36,10); cout<<"3";
	Sleep(1000);
	gotoxy(36,10); cout<<"2";
	Sleep(1000);
	gotoxy(36,10); cout<<"1";
	Sleep(1000);
	gotoxy(34,10); cout<<"Start!!";
	Sleep(1000);
	
	n_Print_screen();

	srand((unsigned)time(NULL));
	int random=0;		  //위치 랜덤으로 생성 (0~8)
	char random_alpha=' ';//알파벳 랜덤으로 생성(65~90)

	int back_t=clock();//제한시간
	int now_t=clock();
	char key;
	int i,j;//반복 변수 선언

	while(m_time!=0){
		if((clock()-now_t==0)||(clock()-now_t>=speed_t)){//지정된 시간만큼 지나면
			n_cursor_change(random);//랜덤 위치로 이동
			cout<<"  ";//그 자리를 비우고
			m_key[random]=' '; //key값도 비운다.
		

			random=rand()%9; //위치를 랜덤으로 만든다.
			random_alpha=65+rand()%26; //알파벳 대문자를 랜덤으로 만든다.
			
			n_cursor_change(random); //랜덤인 위치로 이동한다.

			m_key[random]=random_alpha;//key값에 랜덤으로 만든 알파벳을 넣는다.
			cout<<m_key[random];//만든 랜덤 알파벳을 출력한다.

			now_t=clock(); //현재시간은 now_t에 저장한다.
		}
	
		gotoxy(56,8); 
		
		if(clock()-back_t>=1000){//1초 경과하면
			m_time--; //제한시간-1
			cout<<"0:";
			if(m_time<10) //시간의 한자리 남았을때
				cout<<"0" //앞에 0을 출력한다.
					<<m_time;
			else
				cout<<m_time;
			back_t=clock(); //제한시간을 위한 시간에 현재시간을 넣는다.
		}
		
		if(_kbhit()){		//입력
			key=_getch();	//key를 읽는다.


			if(key>='a')//소문자이면
				key=key-('a'-'A');		//대문자로 바꾼다.

			j=-1;
				

			for(i=0;i<9;i++){	//0~8까지 i를 1씩 더해가며
				if(m_key[i]==key)
					j=i;
			}
				
			if(j!=-1){	//맞는 문자가 있으면
				n_cursor_change(j);
				cout<<"  ";
				m_key[j]=' ';
				m_combo=m_combo+1;
				Calc_score();//콤보수에 대한 점수를 더해준다.
				if(m_best_combo<m_combo)//최대 콤보보다 현재 콤보수가 크면
					m_best_combo=m_combo;//최대 콤보에 현재 콤보수를 넣는다.
					
				gotoxy(57,11);
				cout<<m_score;//점수 출력
				gotoxy(57,14);
				cout<<m_combo;//콤보 출력
				if(speed_t>700)
					speed_t-=20;
				
			}
			else{ //맞는 문자가 없으면
				m_combo=0;//콤보 0으로 초기화
				gotoxy(57,14);
				cout<<"0    ";
			}
		}//입력 끝
		
				

		
	}
	gotoxy(34,10); cout<<"여기까지!!";
	Sleep(2000);
	//cout<<m_key[rand()%9]; 
}


void game_normal :: n_cursor_change(int num){
	if(num==0)
		gotoxy(7,7);
	else if(num==1)
		gotoxy(15,7);
	else if(num==2)
		gotoxy(23,7);
	else if(num==3)
		gotoxy(7,11);
	else if(num==4)
		gotoxy(15,11);
	else if(num==5)
		gotoxy(23,11);
	else if(num==6)
		gotoxy(7,15);
	else if(num==7)
		gotoxy(15,15);
	else if(num==8)
		gotoxy(23,15);
			

}

//--------------------------------------------game normal 클래스---------------------------------------------------




class game_hard:public game{

protected:
	char m_key[16];//두더지 장소

public:
	void h_Initialize();//초기화
	void h_Print_screen(); //게임화면 출력
	void h_Game();   //게임 구현
	void h_cursor_change(int num); //네모 칸 속 커서 위치 옮기기	

};

void game_hard::h_Initialize(){//초기화
	m_time=60;
	m_combo=0;
	m_best_combo=0;
	speed_t=1500;   
	m_score=0;
	for(int i=0;i<16;i++)
		m_key[i]=0;
}


void game_hard::h_Print_screen(){
	gotoxy(0,0);
	cout<<"\n";
	

	cout<<"==========================================================================\n";
	cout<<"==========================================================================\n";
	gotoxy(0,22);
	cout<<"==========================================================================\n";
	cout<<"==========================================================================\n";
	
	gotoxy(0,4);
			
	cout<<" □□□□□□□□□□□□□□□□□\n";
	cout<<" □      □      □      □      □\n";
	cout<<" □      □      □      □      □\n";
	cout<<" □      □      □      □      □\n";
	cout<<" □□□□□□□□□□□□□□□□□\n";
	cout<<" □      □      □      □      □\n";
	cout<<" □      □      □      □      □\n";
	cout<<" □      □      □      □      □\n";
	cout<<" □□□□□□□□□□□□□□□□□\n";
	cout<<" □      □      □      □      □\n";
	cout<<" □      □      □      □      □\n";
	cout<<" □      □      □      □      □\n";
	cout<<" □□□□□□□□□□□□□□□□□\n";
	cout<<" □      □      □      □      □\n";
	cout<<" □      □      □      □      □\n";
	cout<<" □      □      □      □      □\n";
	cout<<" □□□□□□□□□□□□□□□□□\n";
	
	
	Print_score();//점수창 출력
		
	gotoxy(56,8);
	cout<<"1:00";
	gotoxy(57,11);
	cout<<m_score;
	gotoxy(57,14);
	cout<<m_combo;
	

}

void game_hard:: h_Game(){//게임화면 출력
	
	
	gotoxy(39,10); cout<<"3";
	Sleep(1000);
	gotoxy(39,10); cout<<"2";
	Sleep(1000);
	gotoxy(39,10); cout<<"1";
	Sleep(1000);
	gotoxy(37,10); cout<<"Start!!";
	Sleep(1000);
	
	h_Print_screen();

	srand((unsigned)time(NULL));

	int random=0;		  //위치 랜덤으로 생성 (0~8)
	char random_alpha=' ';//알파벳 랜덤으로 생성(65~90)

	int back_t=clock();//제한시간
	int now_t=clock();
	char key;
	int i,j;//반복 변수 선언

	while(m_time!=0){
		if((clock()-now_t==0)||(clock()-now_t>=speed_t)){//지정된 시간만큼 지나면
			h_cursor_change(random);//랜덤 위치로 이동
			cout<<"  ";//그 자리를 비우고
			m_key[random]=' '; //key값도 비운다.
		

			random=rand()%16; //위치를 랜덤으로 만든다.
			random_alpha=65+rand()%26; //알파벳 대문자를 랜덤으로 만든다.
			
			h_cursor_change(random); //랜덤인 위치로 이동한다.

			m_key[random]=random_alpha;//key값에 랜덤으로 만든 알파벳을 넣는다.
			cout<<m_key[random];//만든 랜덤 알파벳을 출력한다.

			now_t=clock(); //현재시간은 now_t에 저장한다.
		}
	
		gotoxy(56,8); 
		
		if(clock()-back_t>=1000){//1초 경과하면
			m_time--; //제한시간-1
			cout<<"0:";
			if(m_time<10) //시간의 한자리 남았을때
				cout<<"0" //앞에 0을 출력한다.
					<<m_time;
			else
				cout<<m_time;
			back_t=clock(); //제한시간을 위한 시간에 현재시간을 넣는다.
		}
		
		if(_kbhit()){		//입력
			key=_getch();	//key를 읽는다.


			if(key>='a')//소문자이면
				key=key-('a'-'A');		//대문자로 바꾼다.

			j=-1;
				

			for(i=0;i<16;i++){	//0~8까지 i를 1씩 더해가며
				if(m_key[i]==key)
					j=i;
			}
				
			if(j!=-1){	//맞는 문자가 있으면
				h_cursor_change(j);
				cout<<"  ";
				m_key[j]=' ';
				m_combo=m_combo+1;
				Calc_score();//콤보수에 대한 점수를 더해준다.
				if(m_best_combo<m_combo)//최대 콤보보다 현재 콤보수가 크면
					m_best_combo=m_combo;//최대 콤보에 현재 콤보수를 넣는다.
					
				gotoxy(57,11);
				cout<<m_score;//점수 출력
				gotoxy(57,14);
				cout<<m_combo;//콤보 출력
				if(speed_t>600)
					speed_t-=20;
				
			}
			else{ //맞는 문자가 없으면
				m_combo=0;//콤보 0으로 초기화
				gotoxy(57,14);
				cout<<"0    ";
			}
		}//입력 끝
		
				

		
	}
	gotoxy(36,10); cout<<"여기까지!!";
	Sleep(2000);
	//cout<<m_key[rand()%9]; 
}


void game_hard :: h_cursor_change(int num){
	if(num==0)
		gotoxy(5,6);
	else if(num==1)
		gotoxy(14,6);
	else if(num==2)
		gotoxy(22,6);
	else if(num==3)
		gotoxy(30,6);
	else if(num==4)
		gotoxy(6,10);
	else if(num==5)
		gotoxy(14,10);
	else if(num==6)
		gotoxy(22,10);
	else if(num==7)
		gotoxy(30,10);
	else if(num==8)
		gotoxy(6,14);
	else if(num==9)
		gotoxy(14,14);
	else if(num==10)
		gotoxy(22,14);
	else if(num==11)
		gotoxy(30,14);
	else if(num==12)
		gotoxy(6,18);
	else if(num==13)
		gotoxy(14,18);
	else if(num==14)
		gotoxy(22,18);
	else if(num==15)
		gotoxy(30,18);		

}

//--------------------------------------------game hard 클래스---------------------------------------------------

void printstart();  //프로그램 시작화면 출력 함수.
int printlevel();   //난이도 출력화면 함수


void printstart(){   

	

	cout<<"==========================================================================\n";
	cout<<"============          ======          ===  =====             ====  =======\n";
	cout<<"============  ==============   ==========  ==========   =========  =======\n";
	cout<<"============  ==============   ==========  ==========   =========  =======\n";
	cout<<"============          ======   =====       =========  ==  =======  =======\n";
	cout<<"============================   ==========  ========  ====  ======  =======\n";
	cout<<"===========            =====   ==========  =======  ======  =====  =======\n";
	cout<<"================  ==========          ===  ======  ========  ====  =======\n";
	cout<<"================  =======================  =====  ==========  ===  =======\n";
	cout<<"================  =======================  ====   ==========   ==  =======\n";
	cout<<"==========================================================================\n";
	cout<<"===========              ==  =============================================\n";
	cout<<"===============  ==  ======  ==========           ====  ==================\n";
	cout<<"=============  =====  =====     ===============   ====  ==================\n";
	cout<<"===========   =======    ==  =================   =====  ==================\n";
	cout<<"===========================  =================  ======  ==================\n";
	cout<<"===========================  ===============   =======  ==================\n";
	cout<<"=============  =========  =  ==============   ========  ==================\n";
	cout<<"=============             ================   =========  ==================\n";
	cout<<"=============  =========  =============   ============  ==================\n";
	cout<<"=============             ============================  ==================\n";
	cout<<"====================== - 게임을 시작합니다 - =============================\n";
	cout<<"==============================       =====================================\n";
	cout<<"==========================================================================\n";

	int key=0;
  
	bling("ENTER",31,22);
	clean_screen();//화면 지우기
} //프로그램 시작화면 출력 함수.

int printlevel(){   
	cout<<"\n";
	

	cout<<"==========================================================================\n";
    cout<<"==========================================================================\n";
	gotoxy(27,9); cout<<"난이도를 선택하세요.";
	gotoxy(31,12); cout<<"1. Easy"; 
	gotoxy(31,13); cout<<"2. Normal";
	gotoxy(31,14); cout<<"3. Hard";
    gotoxy(36,17); cout<<"<-";
	gotoxy(0,22);
	

	cout<<"==========================================================================\n";
	cout<<"==========================================================================\n";


	int num;
	gotoxy(34,17);
	cin>>num;

	clean_screen();

	return num; //난이도 반환
}//난이도 출력화면 함수.

int get_key(){ 
	int key=0;   //키를 누르지 않았다고 가정
	if(_kbhit())  //사용자가 키를 눌렀을 때
		key=_getch(); //키를 읽고
	return key;   //리턴
}//입력 키 인식

void bling(char *str,int x,int y){
	int time=clock();
	char key=0;

  
	gotoxy(x,y);
	cout<< str;
		

	key=0;
	while(key!=13){//무한반복
		if(clock()-time==1300){
			gotoxy(x,y);
			cout<< str;
		}
		if(clock()-time>=2000){
			gotoxy(x,y);
			for(int i=0;i<strlen(str); i++)
				cout<<" ";
			time=clock();
		}

		key=get_key();
	
	}
}//문자 깜빡임
void gotoxy(int x,int y){
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}//커서 위치옮기기

void clean_screen(){
	int y,x;
	for(y=0;y<30;y++)
		for(x=0;x<80;x++){
			gotoxy(x,y);
			putch(' ');
		}
	gotoxy(0,0);
}//화면 지우기




int main(){
	system("title 두 더 지 게 임 합 시 다");
	system("mode con: lines=25 cols=76");

	printstart();  //시작화면 출력
	int level=printlevel(); //난이도 선택
	

	if(level==1){ //easy 선택시
		game_easy easy;
		easy.e_Initialize();
		easy.e_Game();
		easy.Print_gameover();
	}
	
	else if(level==2){ //normal 선택시
		game_normal normal;
		normal.n_Initialize();
		normal.n_Game();
		normal.Print_gameover();
	}

	else if(level==3){ //hard 선택시
		game_hard hard;
		hard.h_Initialize();
		hard.h_Game();
		hard.Print_gameover();
	}

	return 0;
}