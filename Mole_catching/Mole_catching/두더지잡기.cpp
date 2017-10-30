#include<iostream>
#include<time.h>
#include<conio.h>//_kbhit(),_getch()
#include<Windows.h>//gotoxy �Լ�
#include <stdlib.h> //srand, rand
#pragma warning(disable: 4996)

using namespace std;


class game{

protected:
	int m_time;  //���ѽð�
	int m_combo; //�޺� ��
	int m_best_combo; //�ִ� �޺� ��
	int speed_t;   //�����̴� �ð�
	int m_score; //����


public:
	void Calc_score();//�������
	void Print_gameover();//��������ȭ�� ���
	void Print_score();  //����â ���
	
	friend void gotoxy(int x,int y); //Ŀ�� ��ġ �ű��
	friend void bling(char *str,int x,int y); //�ѹ� �����̸� 

	friend int get_key();   //�Է� Ű �ν�
	friend void clean_screen();//ȭ�� �����*/

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

void game:: Print_gameover(){//��������ȭ�� ���

	clean_screen();//ȭ�� �����
	cout<<"\n";
	

	cout<<"===========================================================================\n";
	cout<<"==     =====  =====   =====   =     =======     ==  ======= =     ==    ===\n";
	cout<<"=  ===  === == ====  = === =  =  =========  ===  == ====== ==  ===== === ==\n";
	cout<<"=  =======      ===  == = ==  =     ======  ===  === ==== ===     ==    ===\n";
	cout<<"=  ==   =  ====  ==  === ===  =  =========  ===  ==== == ====  ===== ==  ==\n";
	cout<<"===   = = ====== ==  =======  =     =======    =======  =====     ==  ==  =\n";
	cout<<"===========================================================================\n";
	
	//��

	gotoxy(35,10);
	cout<<"���� : " 
		<<m_score;
	gotoxy(31,11);
	cout<<"�ִ� �޺� �� : "
		<<m_best_combo;
	gotoxy(28,14);
	cout<<"- ������ �����մϴ�. -";
	
	int key=0;

	bling("Enter",35,15);
}


void game::Print_score(){//����â ���

	gotoxy(47,5);  cout<<"=====================";
	for(int i=6;i<16;i++){
		gotoxy(47,i); 
		cout<<			 "|                   |";
	}
	gotoxy(47,16); cout<<"=====================";

	gotoxy(56,7);   cout<<"�ð�";
	gotoxy(56,10);	cout<<"����";
	gotoxy(56,13);	cout<<"�޺�";

}



//-------------------------------------------------game �θ� Ŭ����---------------------------------------------------------




class game_easy:public game{
protected:
	char m_key[4];//�δ��� ���

public:
	void e_Initialize();
	void e_Print_screen(); //����ȭ�� ���
	void e_Game();   //���� ����
	void e_cursor_change(int num); //�׸� ĭ �� Ŀ�� ��ġ �ű��	
};

void game_easy::e_Initialize(){//�ʱ�ȭ
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
			
	cout<<"	  ����������\n";
	cout<<"	  ��      ��      ��\n";
	cout<<"	  ��      ��      ��\n";
	cout<<"	  ��      ��      ��\n";
	cout<<"	  ����������\n";
	cout<<"	  ��      ��      ��\n";
	cout<<"	  ��      ��      ��\n";
	cout<<"	  ��      ��      ��\n";
	cout<<"	  ����������\n";

	
	
	Print_score();//����â ���
		
	gotoxy(56,8);
	cout<<"1:00";
	gotoxy(57,11);
	cout<<m_score;
	gotoxy(57,14);
	cout<<m_combo;
	

}

void game_easy:: e_Game(){//����ȭ�� ���
	
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
	int random=0;		  //��ġ �������� ���� (0~3)
	char random_alpha=' ';//���ĺ� �������� ����(65~90)

	int back_t=clock();//���ѽð�
	int now_t=clock();
	char key;
	int i,j;//�ݺ� ���� ����

	while(m_time!=0){
		if((clock()-now_t==0)||(clock()-now_t>=speed_t)){//������ �ð���ŭ ������
			e_cursor_change(random);//���� ��ġ�� �̵�
			cout<<"  ";//�� �ڸ��� ����
			m_key[random]=' '; //key���� ����.
		

			random=rand()%4; //��ġ�� �������� �����.
			random_alpha=65+rand()%26; //���ĺ� �빮�ڸ� �������� �����.
			
			e_cursor_change(random); //������ ��ġ�� �̵��Ѵ�.

			m_key[random]=random_alpha;//key���� �������� ���� ���ĺ��� �ִ´�.			
			cout<<m_key[random];//���� ���� ���ĺ��� ����Ѵ�.

			now_t=clock(); //����ð��� now_t�� �����Ѵ�.
		}
	
		gotoxy(56,8); 
		
		if(clock()-back_t>=1000){//1�� ����ϸ�
			m_time--; //���ѽð�-1
			cout<<"0:";
			if(m_time<10) //�ð��� ���ڸ� ��������
				cout<<"0" //�տ� 0�� ����Ѵ�.
					<<m_time;
			else
				cout<<m_time;
			back_t=clock(); //���ѽð��� ���� �ð��� ����ð��� �ִ´�.
		}
		
		if(_kbhit()){		//�Է�
			key=_getch();	//key�� �д´�.


			if(key>='a')//�ҹ����̸�
				key=key-('a'-'A');		//�빮�ڷ� �ٲ۴�.

			j=-1;
				

			for(i=0;i<4;i++){	//0~4���� i�� 1�� ���ذ���
				if(m_key[i]==key) //�´� ���ڰ� �ִ��� Ȯ��
					j=i;		//������ j�� �ִ´�.
			}
				
			if(j!=-1){	//�´� ���ڰ� ������
				e_cursor_change(j);
				cout<<"  ";
				m_key[j]=' ';
				m_combo=m_combo+1;
				Calc_score();//�޺����� ���� ������ �����ش�.
				if(m_best_combo<m_combo)//�ִ� �޺����� ���� �޺����� ũ��
					m_best_combo=m_combo;//�ִ� �޺��� ���� �޺����� �ִ´�.
					
				gotoxy(57,11);
				cout<<m_score;//���� ���
				gotoxy(57,14);
				cout<<m_combo;//�޺� ���
		
				if(speed_t>800)//���ǵ尡 800�̻��ΰ�� �ڷ� ������
					speed_t-=22;//���ǵ尡 ��������.->���������.
				
			}
			
			else{ //�´� ���ڰ� ������
				m_combo=0;//�޺� 0���� �ʱ�ȭ
				gotoxy(57,14);
				cout<<"0    ";
			}
		}//�Է� ��
		
				

		
	}
	gotoxy(34,10); cout<<"�������!!";
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



//----------------------------------------------game easy Ŭ����-------------------------------------------------------------------------



class game_normal:public game{
protected:
	char m_key[9];//�δ��� ���


public:
	void n_Initialize();//�ʱ�ȭ
	void n_Print_screen(); //����ȭ�� ���
	void n_Game();   //���� ����
	void n_cursor_change(int num); //�׸� ĭ �� Ŀ�� ��ġ �ű��	

};

void game_normal::n_Initialize(){//�ʱ�ȭ
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
			
	cout<<"  ��������������\n";
	cout<<"  ��      ��      ��      ��\n";
	cout<<"  ��      ��      ��      ��\n";
	cout<<"  ��      ��      ��      ��\n";
	cout<<"  ��������������\n";
	cout<<"  ��      ��      ��      ��\n";
	cout<<"  ��      ��      ��      ��\n";
	cout<<"  ��      ��      ��      ��\n";
	cout<<"  ��������������\n";
	cout<<"  ��      ��      ��      ��\n";
	cout<<"  ��      ��      ��      ��\n";
	cout<<"  ��      ��      ��      ��\n";
	cout<<"  ��������������";
	
	
	Print_score();//����â ���
		
	gotoxy(56,8);
	cout<<"1:00";
	gotoxy(57,11);
	cout<<m_score;
	gotoxy(57,14);
	cout<<m_combo;
	

}

void game_normal:: n_Game(){//����ȭ�� ���
	
	
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
	int random=0;		  //��ġ �������� ���� (0~8)
	char random_alpha=' ';//���ĺ� �������� ����(65~90)

	int back_t=clock();//���ѽð�
	int now_t=clock();
	char key;
	int i,j;//�ݺ� ���� ����

	while(m_time!=0){
		if((clock()-now_t==0)||(clock()-now_t>=speed_t)){//������ �ð���ŭ ������
			n_cursor_change(random);//���� ��ġ�� �̵�
			cout<<"  ";//�� �ڸ��� ����
			m_key[random]=' '; //key���� ����.
		

			random=rand()%9; //��ġ�� �������� �����.
			random_alpha=65+rand()%26; //���ĺ� �빮�ڸ� �������� �����.
			
			n_cursor_change(random); //������ ��ġ�� �̵��Ѵ�.

			m_key[random]=random_alpha;//key���� �������� ���� ���ĺ��� �ִ´�.
			cout<<m_key[random];//���� ���� ���ĺ��� ����Ѵ�.

			now_t=clock(); //����ð��� now_t�� �����Ѵ�.
		}
	
		gotoxy(56,8); 
		
		if(clock()-back_t>=1000){//1�� ����ϸ�
			m_time--; //���ѽð�-1
			cout<<"0:";
			if(m_time<10) //�ð��� ���ڸ� ��������
				cout<<"0" //�տ� 0�� ����Ѵ�.
					<<m_time;
			else
				cout<<m_time;
			back_t=clock(); //���ѽð��� ���� �ð��� ����ð��� �ִ´�.
		}
		
		if(_kbhit()){		//�Է�
			key=_getch();	//key�� �д´�.


			if(key>='a')//�ҹ����̸�
				key=key-('a'-'A');		//�빮�ڷ� �ٲ۴�.

			j=-1;
				

			for(i=0;i<9;i++){	//0~8���� i�� 1�� ���ذ���
				if(m_key[i]==key)
					j=i;
			}
				
			if(j!=-1){	//�´� ���ڰ� ������
				n_cursor_change(j);
				cout<<"  ";
				m_key[j]=' ';
				m_combo=m_combo+1;
				Calc_score();//�޺����� ���� ������ �����ش�.
				if(m_best_combo<m_combo)//�ִ� �޺����� ���� �޺����� ũ��
					m_best_combo=m_combo;//�ִ� �޺��� ���� �޺����� �ִ´�.
					
				gotoxy(57,11);
				cout<<m_score;//���� ���
				gotoxy(57,14);
				cout<<m_combo;//�޺� ���
				if(speed_t>700)
					speed_t-=20;
				
			}
			else{ //�´� ���ڰ� ������
				m_combo=0;//�޺� 0���� �ʱ�ȭ
				gotoxy(57,14);
				cout<<"0    ";
			}
		}//�Է� ��
		
				

		
	}
	gotoxy(34,10); cout<<"�������!!";
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

//--------------------------------------------game normal Ŭ����---------------------------------------------------




class game_hard:public game{

protected:
	char m_key[16];//�δ��� ���

public:
	void h_Initialize();//�ʱ�ȭ
	void h_Print_screen(); //����ȭ�� ���
	void h_Game();   //���� ����
	void h_cursor_change(int num); //�׸� ĭ �� Ŀ�� ��ġ �ű��	

};

void game_hard::h_Initialize(){//�ʱ�ȭ
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
			
	cout<<" ������������������\n";
	cout<<" ��      ��      ��      ��      ��\n";
	cout<<" ��      ��      ��      ��      ��\n";
	cout<<" ��      ��      ��      ��      ��\n";
	cout<<" ������������������\n";
	cout<<" ��      ��      ��      ��      ��\n";
	cout<<" ��      ��      ��      ��      ��\n";
	cout<<" ��      ��      ��      ��      ��\n";
	cout<<" ������������������\n";
	cout<<" ��      ��      ��      ��      ��\n";
	cout<<" ��      ��      ��      ��      ��\n";
	cout<<" ��      ��      ��      ��      ��\n";
	cout<<" ������������������\n";
	cout<<" ��      ��      ��      ��      ��\n";
	cout<<" ��      ��      ��      ��      ��\n";
	cout<<" ��      ��      ��      ��      ��\n";
	cout<<" ������������������\n";
	
	
	Print_score();//����â ���
		
	gotoxy(56,8);
	cout<<"1:00";
	gotoxy(57,11);
	cout<<m_score;
	gotoxy(57,14);
	cout<<m_combo;
	

}

void game_hard:: h_Game(){//����ȭ�� ���
	
	
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

	int random=0;		  //��ġ �������� ���� (0~8)
	char random_alpha=' ';//���ĺ� �������� ����(65~90)

	int back_t=clock();//���ѽð�
	int now_t=clock();
	char key;
	int i,j;//�ݺ� ���� ����

	while(m_time!=0){
		if((clock()-now_t==0)||(clock()-now_t>=speed_t)){//������ �ð���ŭ ������
			h_cursor_change(random);//���� ��ġ�� �̵�
			cout<<"  ";//�� �ڸ��� ����
			m_key[random]=' '; //key���� ����.
		

			random=rand()%16; //��ġ�� �������� �����.
			random_alpha=65+rand()%26; //���ĺ� �빮�ڸ� �������� �����.
			
			h_cursor_change(random); //������ ��ġ�� �̵��Ѵ�.

			m_key[random]=random_alpha;//key���� �������� ���� ���ĺ��� �ִ´�.
			cout<<m_key[random];//���� ���� ���ĺ��� ����Ѵ�.

			now_t=clock(); //����ð��� now_t�� �����Ѵ�.
		}
	
		gotoxy(56,8); 
		
		if(clock()-back_t>=1000){//1�� ����ϸ�
			m_time--; //���ѽð�-1
			cout<<"0:";
			if(m_time<10) //�ð��� ���ڸ� ��������
				cout<<"0" //�տ� 0�� ����Ѵ�.
					<<m_time;
			else
				cout<<m_time;
			back_t=clock(); //���ѽð��� ���� �ð��� ����ð��� �ִ´�.
		}
		
		if(_kbhit()){		//�Է�
			key=_getch();	//key�� �д´�.


			if(key>='a')//�ҹ����̸�
				key=key-('a'-'A');		//�빮�ڷ� �ٲ۴�.

			j=-1;
				

			for(i=0;i<16;i++){	//0~8���� i�� 1�� ���ذ���
				if(m_key[i]==key)
					j=i;
			}
				
			if(j!=-1){	//�´� ���ڰ� ������
				h_cursor_change(j);
				cout<<"  ";
				m_key[j]=' ';
				m_combo=m_combo+1;
				Calc_score();//�޺����� ���� ������ �����ش�.
				if(m_best_combo<m_combo)//�ִ� �޺����� ���� �޺����� ũ��
					m_best_combo=m_combo;//�ִ� �޺��� ���� �޺����� �ִ´�.
					
				gotoxy(57,11);
				cout<<m_score;//���� ���
				gotoxy(57,14);
				cout<<m_combo;//�޺� ���
				if(speed_t>600)
					speed_t-=20;
				
			}
			else{ //�´� ���ڰ� ������
				m_combo=0;//�޺� 0���� �ʱ�ȭ
				gotoxy(57,14);
				cout<<"0    ";
			}
		}//�Է� ��
		
				

		
	}
	gotoxy(36,10); cout<<"�������!!";
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

//--------------------------------------------game hard Ŭ����---------------------------------------------------

void printstart();  //���α׷� ����ȭ�� ��� �Լ�.
int printlevel();   //���̵� ���ȭ�� �Լ�


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
	cout<<"====================== - ������ �����մϴ� - =============================\n";
	cout<<"==============================       =====================================\n";
	cout<<"==========================================================================\n";

	int key=0;
  
	bling("ENTER",31,22);
	clean_screen();//ȭ�� �����
} //���α׷� ����ȭ�� ��� �Լ�.

int printlevel(){   
	cout<<"\n";
	

	cout<<"==========================================================================\n";
    cout<<"==========================================================================\n";
	gotoxy(27,9); cout<<"���̵��� �����ϼ���.";
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

	return num; //���̵� ��ȯ
}//���̵� ���ȭ�� �Լ�.

int get_key(){ 
	int key=0;   //Ű�� ������ �ʾҴٰ� ����
	if(_kbhit())  //����ڰ� Ű�� ������ ��
		key=_getch(); //Ű�� �а�
	return key;   //����
}//�Է� Ű �ν�

void bling(char *str,int x,int y){
	int time=clock();
	char key=0;

  
	gotoxy(x,y);
	cout<< str;
		

	key=0;
	while(key!=13){//���ѹݺ�
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
}//���� ������
void gotoxy(int x,int y){
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}//Ŀ�� ��ġ�ű��

void clean_screen(){
	int y,x;
	for(y=0;y<30;y++)
		for(x=0;x<80;x++){
			gotoxy(x,y);
			putch(' ');
		}
	gotoxy(0,0);
}//ȭ�� �����




int main(){
	system("title �� �� �� �� �� �� �� ��");
	system("mode con: lines=25 cols=76");

	printstart();  //����ȭ�� ���
	int level=printlevel(); //���̵� ����
	

	if(level==1){ //easy ���ý�
		game_easy easy;
		easy.e_Initialize();
		easy.e_Game();
		easy.Print_gameover();
	}
	
	else if(level==2){ //normal ���ý�
		game_normal normal;
		normal.n_Initialize();
		normal.n_Game();
		normal.Print_gameover();
	}

	else if(level==3){ //hard ���ý�
		game_hard hard;
		hard.h_Initialize();
		hard.h_Game();
		hard.Print_gameover();
	}

	return 0;
}