/*
Copyright 2013-2016 Yuer

This file is part of Story.

    Story is free software: you can redistribute it and/or 
	modify it under the terms of the GNU General Public 
	License as published by the Free Software Foundation, 
	either version 3 of the License, or (at your option) 
	any later version.

    Story is distributed in the hope that it will be useful, 
	but WITHOUT ANY WARRANTY; without even the implied 
	warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
	PURPOSE.  See the GNU General Public License for more 
	details.

    You should have received a copy of the GNU General 
	Public License along with Story.  If not, see 
	<http://www.gnu.org/licenses/>.
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<conio.h>
#include<direct.h>

#define size 2552                // 20+20+20+8*12+28*17+80*24
#define grade 40
#define ver "1.4.1"

#define storyfolder "D:\\story\\"
#define savefolder "D:\\story\\save\\"
#define accountfile "D:\\story\\account.ys"
#define onlinefile "D:\\story\\onlineact.ys"
#define namefile "D:\\story\\name.ys"
#define troopfile "D:\\story\\troops.ys"
#define tfile "D:\\story\\t.ys"
#define logfile "log.txt"

struct USERINFO
{
 char username[20];
 char userpwd[20];
};

struct GOODS
{
	char name[20];               // ��Ʒ����
	char nam;                    // ����
	int q;                       // ����
};

struct EQUIPMENT
{
	char name[20];               // װ������
	char kind[20];               // װ������
	int grd;                     // װ������
	char rank;                   // װ������
	double axHP;                 // ����������
	double axMP;                 // ����ħ����
	double aatc;                 // ���ӹ�����
	double adef;                 // ���ӷ�����
};

struct MONSTER
{
	char name[20];               // ����
	int grd;				 	 // �ȼ�
	double HP;                   // ����
	double atc;		 	         // ������
	double def;		  	         // ������
	double exp;			         // �õ�����
	double mny;	 	             // �������
	struct GOODS out[10];		 // ������Ʒ
	struct EQUIPMENT oequ[10];   // ����װ��
};

struct CHARACTER
{
	char name[20];               // ����
	int grd;				   	 // �ȼ�
	char prof[20];               // ְҵ
	double xHP;	      	         // ��������
	double HP;                   // ����ֵ
	double xMP;                  // ħ������
	double MP;                   // ħ��ֵ
	double atc;				     // ������
	double def;			         // ������
	double mny;			         // ���
	struct EQUIPMENT equ[24];	 // װ��
	double xexp;			     // ��������
	double exp;		  	         // ����ֵ
	struct GOODS goods[17];		 // ��Ʒ
	char v[20];                  // ���ڵط�
	int t;						 // ��Ʒ����
	int e;                       // װ������
	int n,m,q;                   // ��ʱ����
	double h,k;                  // ��ʱ����
	char filename[100];          // �ļ�
	int p;                       // ��ɫ��
	int trp;                     // �����
	char trpname[37];            // ����
	char buddy1[20];             // ��Ա
	char buddy2[20];             // ��Ա
	char buddy3[20];             // ��Ա
	char b1;                     // ׼��
	char b2;                     // ׼��
	char b3;                     // ׼��
};

struct MONSTER Out(struct MONSTER mon,int b);
void Printf(struct CHARACTER cha);
struct CHARACTER SeeGoods(struct CHARACTER cha);
void Choice(struct CHARACTER cha);
struct CHARACTER Uptrp(struct CHARACTER cha);

char act[20];
struct USERINFO USER[100];
int CurCounts;
char jiami[20] = "hbxfbmphbxfbmphbxfb";

void cqlog(int t,int e)
{
	FILE *f;
	f=fopen(logfile,"w");
	fprintf(f,"��Ʒ����%d\n",t);
	fprintf(f,"װ������%d\n",e);
	fprintf(f,"\n");
	fclose(f);
}

struct CHARACTER Equname(struct CHARACTER cha)
{
 int t=cha.n;
 if(cha.equ[t].rank=='D')
  {
  if(strcmp(cha.equ[t].kind,"ͷ��")==0)
  {
   strcpy(cha.equ[t].name,"��ͨͷ��");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"��ͨ����");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"��ͨ����");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"��ͨ����");
  }
  if(strcmp(cha.equ[t].kind,"Ь��")==0)
  {
   strcpy(cha.equ[t].name,"��ͨЬ��");
  }
  }
 if(cha.equ[t].grd>=5&&cha.equ[t].grd<=10)
 {
  if(cha.equ[t].rank=='C'||cha.equ[t].rank=='B')
  {
  if(strcmp(cha.equ[t].kind,"ͷ��")==0)
  {
   strcpy(cha.equ[t].name,"  �ֲ�ñ");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"  �ֲ���");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"  �ֲ���");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"  ��ľ��");
  }
  if(strcmp(cha.equ[t].kind,"Ь��")==0)
  {
   strcpy(cha.equ[t].name,"  �ֲ�Ь");
  }
  if(strcmp(cha.equ[t].kind,"��ָ")==0)
  {
   strcpy(cha.equ[t].name,"��ͨ��ָ");
  }
  }
  if(cha.equ[t].rank=='A'&&cha.equ[t].grd==10)
  {
  if(strcmp(cha.equ[t].kind,"ͷ��")==0)
  {
   strcpy(cha.equ[t].name,"����ͷ��");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"�������");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"  �����");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"    ذ��");
  }
  if(strcmp(cha.equ[t].kind,"Ь��")==0)
  {
   strcpy(cha.equ[t].name,"  ����Ь");
  }
  if(strcmp(cha.equ[t].kind,"��ָ")==0)
  {
   strcpy(cha.equ[t].name,"��Խ�ָ");
  }
  }
 }
 if(cha.equ[t].grd>10&&cha.equ[t].grd<=15)
 {
  if(cha.equ[t].rank=='C'||cha.equ[t].rank=='B')
  {
  if(strcmp(cha.equ[t].kind,"ͷ��")==0)
  {
   strcpy(cha.equ[t].name,"����ͷ��");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"���Ϳ���");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"  ���Ϳ�");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"    ����");
  }
  if(strcmp(cha.equ[t].kind,"Ь��")==0)
  {
   strcpy(cha.equ[t].name,"  ����Ь");
  }
  if(strcmp(cha.equ[t].kind,"��ָ")==0)
  {
   strcpy(cha.equ[t].name,"    ս��");
  }
  }
  if(cha.equ[t].rank=='A'&&cha.equ[t].grd==15)
  {
  if(strcmp(cha.equ[t].kind,"ͷ��")==0)
  {
   strcpy(cha.equ[t].name,"��ͭͷ��");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"��ͭ����");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"  ��ͭ��");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"  ��ͭ��");
  }
  if(strcmp(cha.equ[t].kind,"Ь��")==0)
  {
   strcpy(cha.equ[t].name,"  ��ͭЬ");
  }
  if(strcmp(cha.equ[t].kind,"��ָ")==0)
  {
   strcpy(cha.equ[t].name,"��ͭ��ָ");
  }
  }
 }
 if(cha.equ[t].grd>15&&cha.equ[t].grd<=25)
 {
  if(cha.equ[t].rank=='C'||cha.equ[t].rank=='B')
  {
  if(strcmp(cha.equ[t].kind,"ͷ��")==0)
  {
   strcpy(cha.equ[t].name,"����ͷ��");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"���Ϳ���");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"  ���Ϳ�");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"  ն��");
  }
  if(strcmp(cha.equ[t].kind,"Ь��")==0)
  {
   strcpy(cha.equ[t].name,"  ����Ь");
  }
  if(strcmp(cha.equ[t].kind,"��ָ")==0)
  {
   strcpy(cha.equ[t].name,"������ָ");
  }
  }
  if(cha.equ[t].rank=='A'&&cha.equ[t].grd==20)
  {
  if(strcmp(cha.equ[t].kind,"ͷ��")==0)
  {
   strcpy(cha.equ[t].name,"��ͷ��");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"������");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"  ����");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"��֮��");
  }
  if(strcmp(cha.equ[t].kind,"Ь��")==0)
  {
   strcpy(cha.equ[t].name,"  ��Ь");
  }
  if(strcmp(cha.equ[t].kind,"��ָ")==0)
  {
   strcpy(cha.equ[t].name,"ţ�ǽ�ָ");
  }
  }
  if(cha.equ[t].rank=='A'&&cha.equ[t].grd==25)
  {
  if(strcmp(cha.equ[t].kind,"ͷ��")==0)
  {
   strcpy(cha.equ[t].name,"����ͷ��");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"�������");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"  �����");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"�����䵶");
  }
  if(strcmp(cha.equ[t].kind,"Ь��")==0)
  {
   strcpy(cha.equ[t].name,"  ����Ь");
  }
  if(strcmp(cha.equ[t].kind,"��ָ")==0)
  {
   strcpy(cha.equ[t].name,"ˮ����ָ");
  }
  }
 }
 if(cha.equ[t].grd>25&&cha.equ[t].grd<=40)
 {
  if(cha.equ[t].rank=='C'||cha.equ[t].rank=='B')
  {
  if(strcmp(cha.equ[t].kind,"ͷ��")==0)
  {
   strcpy(cha.equ[t].name,"����ͷ��");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"���Ϳ���");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"  ���Ϳ�");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   if(strcmp(cha.prof,"սʿ")==0)
   {
    strcpy(cha.equ[t].name,"  �ƿս�");
   }
   if(strcmp(cha.prof,"��ʦ")==0)
   {
    strcpy(cha.equ[t].name,"   ħ��");
   }
   if(strcmp(cha.prof,"��ʿ")==0)
   {
    strcpy(cha.equ[t].name,"  ������");
   }
  }
  if(strcmp(cha.equ[t].kind,"Ь��")==0)
  {
   strcpy(cha.equ[t].name,"  ����Ь");
  }
  if(strcmp(cha.equ[t].kind,"��ָ")==0)
  {
   strcpy(cha.equ[t].name,"������ָ");
  }
  }
  if(cha.equ[t].rank=='A'&&cha.equ[t].grd==32)
  {
  if(strcmp(cha.equ[t].kind,"ͷ��")==0)
  {
   strcpy(cha.equ[t].name,"����ͷ��");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"�������");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"  �����");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   if(strcmp(cha.prof,"սʿ")==0)
   {
    strcpy(cha.equ[t].name,"  ���佣");
   }
   if(strcmp(cha.prof,"��ʦ")==0)
   {
    strcpy(cha.equ[t].name,"�þ�֮��");
   }
   if(strcmp(cha.prof,"��ʿ")==0)
   {
    strcpy(cha.equ[t].name,"  ���ƽ�");
   }
  }
  if(strcmp(cha.equ[t].kind,"Ь��")==0)
  {
   strcpy(cha.equ[t].name,"  ����Ь");
  }
  if(strcmp(cha.equ[t].kind,"��ָ")==0)
  {
   strcpy(cha.equ[t].name,"�����ָ");
  }
  }
  if(cha.equ[t].rank=='A'&&cha.equ[t].grd==40)
  {
  if(strcmp(cha.equ[t].kind,"ͷ��")==0)
  {
   strcpy(cha.equ[t].name,"��ħͷ��");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"��ħ����");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   strcpy(cha.equ[t].name,"  ��ħ��");
  }
  if(strcmp(cha.equ[t].kind,"����")==0)
  {
   if(strcmp(cha.prof,"սʿ")==0)
   {
    strcpy(cha.equ[t].name,"    Ѫ��");
   }
   if(strcmp(cha.prof,"��ʦ")==0)
   {
    strcpy(cha.equ[t].name,"�ɻ귨��");
   }
   if(strcmp(cha.prof,"��ʿ")==0)
   {
    strcpy(cha.equ[t].name,"  �޼���");
   }
  }
  if(strcmp(cha.equ[t].kind,"Ь��")==0)
  {
   strcpy(cha.equ[t].name,"  ��ħЬ");
  }
  if(strcmp(cha.equ[t].kind,"��ָ")==0)
  {
   strcpy(cha.equ[t].name,"ħѪ��ָ");
  }
  }
 }//45���ٳ���ȸһ�ף�54������һ�ײ���Ū
 return cha;
}

struct MONSTER Out(struct MONSTER mon,int b)
{
 int a,k=0;
 while(mon.out[k].nam!='*')
 {
  k++;
 }
 k = k + b;
 a = 1 + rand()%7;
 if(a==1)
 {
    strcpy(mon.oequ[k].kind,"����");
 }
 if(a==2||a==3)
 {
	strcpy(mon.oequ[k].kind,"��ָ");
 }
 if(a==4)
 {
	strcpy(mon.oequ[k].kind,"����");
 }
 if(a==5)
 {
    strcpy(mon.oequ[k].kind,"ͷ��");
 }
 if(a==6)
 {
	strcpy(mon.oequ[k].kind,"����");
 }
 if(a==7)
 {
	strcpy(mon.oequ[k].kind,"Ь��");
 }
 return mon;
}

struct MONSTER Monster(struct CHARACTER cha)
{
	struct MONSTER mon;
	int a;
	int grd;
	for(int i=0;i<=9;i++)
	{
	  mon.out[i].nam = '\0';
	  strcpy(mon.out[i].name,"\0");
	  mon.out[i].q = 0;
	  strcpy(mon.oequ[i].name,"\0");
	  strcpy(mon.oequ[i].kind,"\0");
	  mon.oequ[i].grd=0;
	  mon.oequ[i].rank=' ';
	  mon.oequ[i].aatc=0;
	  mon.oequ[i].adef=0;
	  mon.oequ[i].axHP=0;
	  mon.oequ[i].axMP=0;
	}
	if(strcmp(cha.v,"�����ܱ�")==0)
	{
	 a = 1 + rand()%10;
	 if (a<=10-cha.grd*3)
	 {
		strcpy(mon.name,"��");
		mon.grd = 1;
		mon.HP = 5;
		mon.atc = 4;
		mon.def = 2;
		mon.exp = 5;
		mon.mny = 1;
		return mon;
	 }
	 if (a>=6)
	 {
		strcpy(mon.name,"������");
		mon.grd = 2;
		mon.HP = 20;
		mon.atc = 10;
		mon.def = 5;
		mon.exp = 8;
		mon.mny = 5;
		return mon;
	 }
	 if (a<=5)
	 {
		strcpy(mon.name,"¹");
		mon.grd = 3;
		mon.HP = 50;
		mon.atc = 16;
		mon.def = 8;
		mon.exp = 15;
		mon.mny = 3;
		return mon;
	 }
	}
	if (strcmp(cha.v,"ɭ��")==0)
	{
		a = 1 + rand()%100;
		grd = cha.grd;
		if(cha.grd>=11)
		{
		 grd = 11;
		}
		if(a>3&&a<=75-grd*5)
		{
		 mon.grd=5;
		 strcpy(mon.name,"�๳è");
		}
		if(a>75-grd*5&&a<=100-grd*5)
		{
		 mon.grd=6;
		 strcpy(mon.name,"ʳ�˻�");
		}
		if(a>100-grd*5&&a<=125-grd*5)
		{
		 mon.grd=8;
		 strcpy(mon.name,"֩�뾫");
		}
		if(a>125-grd*5&&a<=100)
		{
		 mon.grd=9;
		 strcpy(mon.name,"����");
		}
		if(a<=3)
		{
		 strcpy(mon.name,"������ʿ");
		 mon.grd = 10;
		 mon.HP = 500;
		 mon.atc = 120;
		 mon.def = 40;
         mon.exp = 50;
		 mon.mny = 20;
		 mon.out[0].nam = '*';
		 mon.oequ[0].rank = 'A';
         mon = Out(mon,0);
		 if(grd<=10)
		 {
		  mon.exp = 250;
		  mon.mny = 100;
		  mon.out[1].nam = '@';
		  strcpy(mon.out[1].name,"�м��ָ�ҩˮ");
		  mon.out[1].q = 3;
		 }
		 return mon;
		}
		mon.HP = mon.grd * 15;
		mon.atc = mon.grd * 4.5;
		mon.def = mon.grd * 3;
		mon.exp = mon.grd * 4;
		mon.mny = mon.grd;
		a = 1 + rand()%10;
		if(a>=9&&mon.grd<=6)
		{
		 mon.out[0].nam = '*';
		 mon.oequ[0].rank = 'C';
         mon = Out(mon,0);
		}
		if(a<=2&&mon.grd<=8)
		{
		 mon.out[0].nam = '*';
		 mon.oequ[0].rank = 'B';
         mon = Out(mon,0);
		}
		return mon;
	}
	if (strcmp(cha.v,"��ʬ��")==0)
	{
		a = 1 + rand()%100;
		if(a<=40)
		{
		 strcpy(mon.name,"��ʬ");
		 if(a<20)
		 {
		  mon.grd = 10;
		 }
		 if(a>=20)
		 {
		  mon.grd = 15;
		 }
		 mon.HP = mon.grd * 15;
		 mon.atc = mon.grd * 4.7;
		 mon.def = mon.grd * 3;
		 mon.exp = mon.grd * 4;
		 mon.mny = mon.grd-5;
		 a = 21 + rand()%18;
	     if(a==25)
		 {
		  mon.out[0].nam = 'a';
		  strcpy(mon.out[0].name,"��ͭ");
		  mon.out[0].q = 1;
		 }
		 return mon;
		}
        if(a>40&&a<=75)
		{
		 strcpy(mon.name,"�׵罩ʬ");
		 if(a<55)
		 {
		  mon.grd = 13;
		 }
		 if(a>=55)
		 {
		  mon.grd = 15;
		 }
		 mon.HP = mon.grd * 18;
		 mon.atc = mon.grd * 4.9;
		 mon.def = mon.grd * 3;
		 mon.exp = mon.grd * 4;
		 mon.mny = mon.grd-5;
		 a = 21 + rand()%10;
	     if(a==26)
		 {
		  mon.out[0].nam = 'a';
		  strcpy(mon.out[0].name,"��ͭ");
		  mon.out[0].q = 1;
		 }
		 return mon;
		}
		if (a>95)
		{
			strcpy(mon.name,"��ʬ��");
			mon.grd = 15;
			mon.HP = mon.grd * 50 + 50;    //800
			mon.atc = mon.grd * 5 * 1.6;   //120
			mon.def = mon.grd * 3 * 1.5;   //68
			mon.exp = (4 * mon.grd) * 4;
			mon.mny = mon.grd * 2;
			mon.out[0].nam = '*';
			mon.oequ[0].rank = 'B';
			mon = Out(mon,0);
			mon.out[1].nam = '%';
			strcpy(mon.out[1].name,"�м��ָ�ҩˮ");
		    mon.out[1].q = 1;
			mon.out[2].nam = 'a';
			strcpy(mon.out[2].name,"��ͭ");
		    mon.out[2].q = 1;
			return mon;
		}
		if (a>75&&a<=95)
		{
			strcpy(mon.name,"��ʬ");
			mon.grd = 13;
			mon.HP = mon.grd * 30;
			mon.atc = mon.grd * 4.7 * 1.5;
			mon.def = mon.grd * 3 * 1.4;
			mon.exp = (4 * mon.grd) * 2;
			mon.mny = mon.grd;
			mon.out[0].nam = '*';
			mon.oequ[0].rank = 'C';
			mon = Out(mon,0);
			if(a>80)
			{
			  mon.out[1].nam = '#';
			  strcpy(mon.out[1].name,"�ͼ��ָ�ҩˮ");
		      mon.out[1].q = 1;
			  a = 21 + rand()%5;
			  if(a==23)
			  {
			   mon.out[2].nam = 'a';
			   strcpy(mon.out[2].name,"��ͭ");
		       mon.out[2].q = 1;
			  }
			}
			else
			{
			  a = 21 + rand()%5;
			  if(a==23)
			  {
			   mon.out[1].nam = 'a';
			   strcpy(mon.out[1].name,"��ͭ");
		       mon.out[1].q = 1;
			  }
			}
			return mon;
		}
	}
	if(strcmp(cha.v,"��򼶴")==0)
	{
	 a = 1 + rand()%100;
	 if(a<=50)
		{
		 strcpy(mon.name,"��򼾫");
		 mon.grd = 17;
		 mon.HP = mon.grd * 15;
		 mon.atc = mon.grd * 5.3;
		 mon.def = mon.grd * 3.4;
		 mon.exp = mon.grd * 4;
		 mon.mny = mon.grd-5;
		 return mon;
		}
        if(a>50&&a<=90)
		{
		 strcpy(mon.name,"����");
		 mon.grd = 19;
		 mon.HP = mon.grd * 18;
		 mon.atc = mon.grd * 5.4;
		 mon.def = mon.grd * 3.5;
		 mon.exp = mon.grd * 4;
		 mon.mny = mon.grd-5;
		 a = 21 + rand()%5;
	     if(a==24)
		 {
		  mon.out[0].nam = '*';
	      mon.oequ[0].rank = 'C';
		  mon = Out(mon,0);
		 }
		 return mon;
		}
		if (a>90)
		{
			strcpy(mon.name,"Ы��");
			mon.grd = 19;
			mon.HP = mon.grd * 30;
			mon.atc = mon.grd * 4.7 * 1.4;
			mon.def = mon.grd * 3 * 1.3;
			mon.exp = (4 * mon.grd) * 2;
			mon.mny = mon.grd * 2;
			mon.out[0].nam = '*';
			mon.oequ[0].rank = 'B';
			mon = Out(mon,0);
			mon.out[1].nam = '#';
			strcpy(mon.out[1].name,"�ͼ��ָ�ҩˮ");
		    mon.out[1].q = 1;
			a = 21 + rand()%5;
			if(a==23)
			{
			  mon.out[2].nam = 'b';
			  strcpy(mon.out[2].name,"���걦ʯ");
		      mon.out[2].q = 1;
			}
			return mon;
		}
	}
	if(strcmp(cha.v,"ʯ��")==0)
	{
	 a = 1 + rand()%100;
	 if(a<=45)
		{
		 strcpy(mon.name,"ɽ������");
		 mon.grd = 21;
		 mon.HP = mon.grd * 15;
		 mon.atc = mon.grd * 5.3;
		 mon.def = mon.grd * 3.4;
		 mon.exp = mon.grd * 4;
		 mon.mny = mon.grd-10;
		 a = 21 + rand()%20;
		 if(a==34)
		 {
		  mon.out[0].nam = 'b';
		  strcpy(mon.out[0].name,"���걦ʯ");
		  mon.out[0].q = 1;
		 }
		 if(a==28)
		 {
		  mon.grd = 20;
		  mon.out[0].nam = '*';
		  mon.oequ[0].rank = 'A';
		  mon = Out(mon,0);
		 }
		 return mon;
		}
        if(a>45&&a<=85)
		{
		 strcpy(mon.name,"����");
		 mon.grd = 23;
		 mon.HP = mon.grd * 18;
		 mon.atc = mon.grd * 5.5;
		 mon.def = mon.grd * 3.5;
		 mon.exp = mon.grd * 4;
		 mon.mny = mon.grd-5;
		 a = 21 + rand()%15;
	     if(a==26)
		 {
		  mon.out[0].nam = 'b';
		  strcpy(mon.out[0].name,"���걦ʯ");
		  mon.out[0].q = 1;
		 }
		 if(a==28)
		 {
		  mon.grd = 20;
		  mon.out[0].nam = '*';
		  mon.oequ[0].rank = 'A';
		  mon = Out(mon,0);
		 }
		 return mon;
		}
		if (a>85&&a<=95)
		{
			strcpy(mon.name,"����ս��");
			mon.grd = 21;
			mon.HP = mon.grd * 30;
			mon.atc = mon.grd * 4.7 * 1.3;
			mon.def = mon.grd * 3 * 1.3;
			mon.exp = (4 * mon.grd) * 2;
			mon.mny = mon.grd * 2;
			mon.out[0].nam = '*';
			mon.oequ[0].rank = 'C';
			mon = Out(mon,0);
			mon.out[1].nam = '#';
			strcpy(mon.out[1].name,"�ͼ��ָ�ҩˮ");
		    mon.out[1].q = 1;
			a = 21 + rand()%10;
			if(a==23||a==27)
			{
			  mon.out[2].nam = 'b';
			  strcpy(mon.out[2].name,"���걦ʯ");
		      mon.out[2].q = 1;
			}
			return mon;
		}
		if (a>95)
		{
		   a = 1 + rand()%10;
		   if(a<=8)
		   {
		    strcpy(mon.name,"���þ���");
			mon.grd = 24;
			mon.HP = mon.grd * 40;
			mon.atc = mon.grd * 4.7 * 1.5;
			mon.def = mon.grd * 3 * 1.4;
			mon.exp = (4 * mon.grd) * 3;
			mon.mny = mon.grd * 2;
			mon.out[0].nam = '*';
			mon.oequ[0].rank = 'B';
			mon = Out(mon,0);
			mon.out[1].nam = '#';
			strcpy(mon.out[1].name,"�ͼ��ָ�ҩˮ");
		    mon.out[1].q = 1;
			a = 21 + rand()%4;
			if(a==23)
			{
			  mon.out[2].nam = 'b';
			  strcpy(mon.out[2].name,"���걦ʯ");
		      mon.out[2].q = 1;
			}
			return mon;
		   }
		   else
		   {
		    strcpy(mon.name,"�������");
			mon.grd = 25;
			mon.HP = mon.grd * 50 + 50;
			mon.atc = mon.grd * 5 * 1.6;
			mon.def = mon.grd * 3 * 1.5;
			mon.exp = (4 * mon.grd) * 4;
			mon.mny = mon.grd * 3;
			mon.out[0].nam = 'b';
			strcpy(mon.out[0].name,"���걦ʯ");
		    mon.out[0].q = 1;
			mon.out[1].nam = '%';
			strcpy(mon.out[1].name,"�м��ָ�ҩˮ");
		    mon.out[1].q = 1;
			a = 21 + rand()%3;
			if(a==23)
			{
			mon.out[2].nam = '*';
			mon.oequ[2].rank = 'A';
			mon = Out(mon,0);
			}
			return mon;
		   }
		}
	}
	if(strcmp(cha.v,"Ұ��")==0)
	{
	 a = 1 + rand()%100;
	 if(a<=45)
		{
		 strcpy(mon.name,"Ы��");
		 mon.grd = 28;
		 mon.HP = mon.grd * 15;
		 mon.atc = mon.grd * 5.3;
		 mon.def = mon.grd * 3.4;
		 mon.exp = mon.grd * 4;
		 mon.mny = mon.grd-10;
		 a = 21 + rand()%5;
		 if(a==23)
		 {
		  mon.out[0].nam = '*';
		  mon.oequ[0].rank = 'C';
		  mon = Out(mon,0);
		 }
		 return mon;
		}
        if(a>45&&a<=85)
		{
		 strcpy(mon.name,"��Ұ��");
		 mon.grd = 30;
		 mon.HP = mon.grd * 18;
		 mon.atc = mon.grd * 5.5;
		 mon.def = mon.grd * 3.5;
		 mon.exp = mon.grd * 4;
		 mon.mny = mon.grd-5;
		 a = 21 + rand()%5;
		 if(a==23)
		 {
		  mon.out[0].nam = '*';
		  mon.oequ[0].rank = 'B';
		  mon = Out(mon,0);
		 }
		 return mon;
		}
		if(a>85)
		{
			strcpy(mon.name,"��Ұ��");
			mon.grd = 32;
			mon.HP = mon.grd * 40;
			mon.atc = mon.grd * 4.7 * 1.5;
			mon.def = mon.grd * 3 * 1.4;
			mon.exp = (4 * mon.grd) * 2;
			mon.mny = mon.grd * 2;
			mon.out[0].nam = '#';
			strcpy(mon.out[0].name,"�ͼ��ָ�ҩˮ");
		    mon.out[0].q = 1;
			a = 21 + rand()%5;
			if(a==22)
			{
			 mon.out[1].nam = '*';
			 mon.oequ[1].rank = 'A';
			 mon = Out(mon,0);
			}
			return mon;
		}
	}
	if(strcmp(cha.v,"��ħ��")==0)
	{
	 a = 1 + rand()%100;
	 if(a<=45)
		{
		 strcpy(mon.name,"����սʿ");
		 if(a<=30)
		 {
		  mon.grd = 34;
		 }
		 else
		 {
		  mon.grd = 36;
		 }
		 mon.HP = mon.grd * 15;
		 mon.atc = mon.grd * 5.3;
		 mon.def = mon.grd * 3.4;
		 mon.exp = mon.grd * 4;
		 mon.mny = mon.grd-10;
		 a = 21 + rand()%5;
		 if(a==23)
		 {
		  mon.out[0].nam = '*';
		  mon.oequ[0].rank = 'C';
		  mon = Out(mon,0);
		 }
		 return mon;
		}
        if(a>45&&a<=85)
		{
		 strcpy(mon.name,"�Ļ�");
		 if(a<=73)
		 {
		  mon.grd = 36;
		 }
		 else
		 {
		  mon.grd = 38;
		 }
		 mon.HP = mon.grd * 18;
		 mon.atc = mon.grd * 5.5;
		 mon.def = mon.grd * 3.5;
		 mon.exp = mon.grd * 4;
		 mon.mny = mon.grd-5;
		 a = 21 + rand()%5;
		 if(a==23)
		 {
		  mon.out[0].nam = '*';
		  mon.oequ[0].rank = 'B';
		  mon = Out(mon,0);
		 }
		 return mon;
		}
		if(a>85&&a<=95)
		{
			strcpy(mon.name,"������");
			mon.grd = 38;
			mon.HP = mon.grd * 40;
			mon.atc = mon.grd * 4.7 * 1.5;
			mon.def = mon.grd * 3 * 1.4;
			mon.exp = (4 * mon.grd) * 2;
			mon.mny = mon.grd * 2;
			mon.out[0].nam = '#';
			strcpy(mon.out[0].name,"�ͼ��ָ�ҩˮ");
		    mon.out[0].q = 1;
			a = 21 + rand()%5;
			if(a==22)
			{
			 mon.out[1].nam = 'c';
			 strcpy(mon.out[1].name,"��ħ��Ϣ");
		     mon.out[1].q = 1;
			}
			return mon;
		}
		if(a>95)
		{
			strcpy(mon.name,"���¶�ħ");
			mon.grd = 40;
			mon.HP = mon.grd * 50 + 50;
			mon.atc = mon.grd * 5 * 1.6;
			mon.def = mon.grd * 3 * 1.5;
			mon.exp = (4 * mon.grd) * 4;
			mon.mny = mon.grd * 3;
			mon.out[0].nam = '%';
			strcpy(mon.out[0].name,"�м��ָ�ҩˮ");
		    mon.out[0].q = 2;
			a = 21 + rand()%3;
			if(a==22)
			{
			 mon.out[1].nam = 'c';
			 strcpy(mon.out[1].name,"��ħ��Ϣ");
		     mon.out[1].q = 1;
			}
			return mon;
		}
	}
	return mon;
}

struct MONSTER Monbackup(struct CHARACTER cha)
{
	struct MONSTER mon;
	for(int i=0;i<=9;i++)
	{
	  mon.out[i].nam = '\0';
	  strcpy(mon.out[i].name,"\0");
	  mon.out[i].q = 0;
	}
	if(cha.grd>=25)
	{
		strcpy(mon.name,"�������");
		mon.grd = 25;
		mon.HP = 3500;
		mon.atc = mon.grd * 5 * 1.6+15.0;
		mon.def = mon.grd * 3 * 1.5;
		mon.mny = mon.grd * 3;
		mon.exp = 0;
		if(cha.trp==0)
		{
		 mon.out[0].nam = '%';
		 strcpy(mon.out[0].name,"�м��ָ�ҩˮ");
		 mon.out[0].q = 1;
		}
		if(cha.trp!=0)
		{
		 mon.out[0].nam = '%';
		 strcpy(mon.out[0].name,"�м��ָ�ҩˮ");
		 mon.out[0].q = 3;
		 mon.out[1].nam = '$';
		 strcpy(mon.out[1].name,"25��װ��ǿ������");
		 mon.out[1].q = 1;
		}
		return mon;
	}
	return mon;
}

void SeeAbi(struct CHARACTER cha)
{
	printf("����       %s\n",cha.name);
	printf("�ȼ�       %d\n", cha.grd);
	printf("ְҵ       %s\n", cha.prof);
	printf("HP         %.0lf/%.0lf\n", cha.HP, cha.xHP);
	printf("MP         %.0lf/%.0lf\n", cha.MP, cha.xMP);
	printf("������     %.0lf\n", cha.atc);
	printf("������     %.0lf\n", cha.def);
	printf("����       %.0lf/%.0lf\n", cha.exp, cha.xexp);
	printf("ȷ��");
	getchar();
	printf("\n");
}

struct CHARACTER SeeEqu(struct CHARACTER cha)
{
    int t = cha.n,s,n,m;
	if(t!=0)
	{
	 if(strcmp(cha.equ[t].kind,"ͷ��")==0)
	 {
	  s = 0;
	 }
	 if(strcmp(cha.equ[t].kind,"����")==0)
	 {
	  s = 1;
	 }
	 if(strcmp(cha.equ[t].kind,"����")==0)
	 {
	  s = 2;
	 }
	 if(strcmp(cha.equ[t].kind,"����")==0)
	 {
	  s = 3;
	 }
	 if(strcmp(cha.equ[t].kind,"Ь��")==0)
	 {
	  s = 4;
	 }
	 if(strcmp(cha.equ[t].kind,"��ָ")==0)
	 {
	  s = 5;
	 }
	 if(strcmp(cha.equ[s].name,"\0")==0)
	 {
	  printf("   ");
	  printf("%s\n",cha.equ[t].name);
	  printf("����:%s\n",cha.equ[t].kind);
	  printf("װ������   %d\n",cha.equ[t].grd);
	  printf("װ������   %c\n",cha.equ[t].rank);
	  printf("HP         +%.0lf\n", cha.equ[t].axHP);
	  printf("MP         +%.0lf\n", cha.equ[t].axMP);
	  printf("������     +%.0lf\n", cha.equ[t].aatc);
	  printf("������     +%.0lf\n", cha.equ[t].adef);
	 }
	 else
	 {
	  printf("   ");
	  printf("%s",cha.equ[t].name);
	  printf("           |   ");
	  printf("%s\n",cha.equ[s].name);
	  printf("����:%s             |����:%s\n", cha.equ[t].kind,cha.equ[s].kind);
	  printf("װ������   %d         |װ������   %d\n", cha.equ[t].grd, cha.equ[s].grd);
	  printf("װ������   %c          |װ������   %c\n", cha.equ[t].rank, cha.equ[s].rank);
	  printf("HP         +%-5.0lf     |HP         +%.0lf\n", cha.equ[t].axHP, cha.equ[s].axHP);
	  printf("MP         +%-5.0lf     |MP         +%.0lf\n", cha.equ[t].axMP, cha.equ[s].axMP);
	  printf("������     +%-5.0lf     |������     +%.0lf\n", cha.equ[t].aatc, cha.equ[s].aatc);
	  printf("������     +%-5.0lf     |������     +%.0lf\n", cha.equ[t].adef, cha.equ[s].adef);
	 }
	}
	if(t==0)
	{
	  int i=0;
      while(i==0)
	  {
		  printf("      1.%c\n\n",cha.equ[0].rank);
		  printf("2.%c          6.%c\n\n",cha.equ[1].rank,cha.equ[5].rank);
		  printf("3.%c          7.%c\n\n",cha.equ[2].rank,cha.equ[6].rank);
		  printf("4.%c   5.%c\n",cha.equ[3].rank,cha.equ[4].rank);
		  printf("��ѡ��");
		  scanf("%d",&s);
		  getchar();
		  if(s!=1&&s!=2&&s!=3&&s!=4&&s!=5&&s!=6&&s!=7)
		  {
			  return cha;
		  }
		  s--;
		  if(strcmp(cha.equ[s].name,"\0")==0)
		  {
			  printf("��װ��\n");
			  printf("ȷ��");
			  getchar();
			  printf("\n");
		  }
		  if(strcmp(cha.equ[s].name,"\0")!=0)
		  {
			  printf("   ");
			  printf("%s\n",cha.equ[s].name);
			  printf("����:%s\n", cha.equ[s].kind);
			  printf("װ������   %d\n", cha.equ[s].grd);
			  printf("װ������   %c\n", cha.equ[s].rank);
			  printf("HP         +%.0lf\n", cha.equ[s].axHP);
			  printf("MP         +%.0lf\n", cha.equ[s].axMP);
			  printf("������     +%.0lf\n", cha.equ[s].aatc);
			  printf("������     +%.0lf\n", cha.equ[s].adef);
			  printf("1.ȷ��  2.ж��װ��\n");
			  printf("��ѡ��");
			  scanf("%d",&t);
			  getchar();
			  if(t==2)
			  {
				  n = cha.e;
				  m = cha.t;
				  if(m==17)
				  {
					  printf("�����ռ䲻��\n");
					  printf("ȷ��");
					  getchar();
					  return cha;
				  }
				  cha.equ[n] = cha.equ[s];
				  strcpy(cha.equ[s].name,"\0");
				  strcpy(cha.equ[s].kind,"\0");
				  cha.equ[s].grd = 0;
				  cha.equ[s].rank = ' ';
				  cha.equ[s].axHP = 0;
				  cha.equ[s].axMP = 0;
				  cha.equ[s].aatc = 0;
				  cha.equ[s].adef = 0;
				  cha.goods[m].nam = '*';
				  if(cha.HP>cha.xHP-cha.equ[n].axHP)
				  {
					  cha.HP = cha.xHP-cha.equ[n].axHP;
				  }
				  cha.xHP = cha.xHP-cha.equ[n].axHP;
				  if(cha.MP>cha.xMP-cha.equ[n].axMP)
				  {
					  cha.MP = cha.xMP-cha.equ[n].axMP;
				  }
				  cha.xMP = cha.xMP-cha.equ[n].axMP;
				  cha.atc = cha.atc-cha.equ[n].aatc;
				  cha.def = cha.def-cha.equ[n].adef;
				  if(cha.equ[0].rank==' '&&cha.equ[1].rank==' '&&cha.equ[2].rank==' '&&cha.equ[3].rank==' '&&
					  cha.equ[4].rank==' '&&cha.equ[5].rank==' '&&cha.equ[6].rank==' ')
				  {
					  if(strcmp(cha.prof,"սʿ")==0)
					  {
						  cha.xHP=cha.grd*19;
						  cha.HP=cha.xHP;
						  cha.xMP=cha.grd*3;
						  cha.MP=cha.xMP;
						  cha.atc=cha.grd*5;
						  cha.def=cha.grd*3;
					  }
					  if(strcmp(cha.prof,"��ʦ")==0)
					  {
						  cha.xHP=cha.grd*5;
						  cha.HP=cha.xHP;
						  cha.xMP=cha.grd*20;
						  cha.MP=cha.xMP;
						  cha.atc=cha.grd*2;
						  cha.def=cha.grd*3;
					  }
					  if(strcmp(cha.prof,"��ʿ")==0)
					  {
						  cha.xHP=cha.grd*12;
						  cha.HP=cha.xHP;
						  cha.xMP=cha.grd*11;
						  cha.MP=cha.xMP;
						  cha.atc=cha.grd*3.5;
						  cha.def=cha.grd*3;
					  }
				  }
				  cha.e+=1;
				  cha.t+=1;
			  }
			  printf("\n");
		  }
      }
    }
	return cha;
}

void SeeGood(struct CHARACTER cha)
{
    int m;
    m = cha.m;
	if(m==-1)
	{
	 printf("Ч��   ����HP100%%\n");
	 printf("       ����MP100%%\n");
	}
    if(cha.goods[m].nam=='#')
	{
	  printf("    %s\n",cha.goods[m].name);
      printf("Ч��   ����HP30%%\n");
	  printf("       ����MP30%%\n");
    }
    if(cha.goods[m].nam=='%')
    {
	  printf("    %s\n",cha.goods[m].name);
      printf("Ч��   ����HP50%%\n");
	  printf("       ����MP50%%\n");
    }
    if(cha.goods[m].nam=='@')
    {
	  printf("    %s\n",cha.goods[m].name);
      printf("Ч��   ����HP100%%\n");
	  printf("       ����MP100%%\n");
    }
	if(cha.goods[m].nam=='a')
	{
	  printf("    %s\n",cha.goods[m].name);
	  printf("����������ͭ��װ�Ĳ��ϡ�\n");
	}
	if(cha.goods[m].nam=='b')
	{
	  printf("    %s\n",cha.goods[m].name);
	  printf("��������������װ�Ĳ��ϡ�\n");
	}
	if(cha.goods[m].nam=='$')
	{
	  printf("    %s\n",cha.goods[m].name);
	  printf("��ǿ��25�����µ�װ�����ɳ�ֵΪ50%%\n");
	  printf("ǿ������װ�������ٴ�ǿ����\n");
	}
	if(cha.goods[m].nam=='c')
	{
	  printf("    %s\n",cha.goods[m].name);
	  printf("����������ħ��װ�Ĳ��ϡ�\n");
	}
}

struct CHARACTER EquAtt(struct CHARACTER cha)
{
	int s;
	double t;
	s = cha.e-1;
	if (cha.equ[s].rank == 'A')
	{
        t = 0.5;
	}
	if (cha.equ[s].rank == 'B')
	{
	    t = 0.4;
	}
	if (cha.equ[s].rank == 'C')
	{
	    t = 0.3;
	}
	if (cha.equ[s].rank == 'D')
	{
	    t = 0.15;
	}
	if(strcmp(cha.prof,"սʿ")==0)
	{
	if(strcmp(cha.equ[s].kind,"����")==0)
	{
		cha.equ[s].axHP = 0;
		cha.equ[s].axMP = 0;
		cha.equ[s].aatc = cha.equ[s].grd*5*t*0.684;
		cha.equ[s].adef = cha.equ[s].grd*3*t*0.087;
	}
	if(strcmp(cha.equ[s].kind,"��ָ")==0)
	{
		cha.equ[s].axHP = cha.equ[s].grd*19*t*0.14;
		cha.equ[s].axMP = cha.equ[s].grd*3*t*0.14;
	    cha.equ[s].aatc = cha.equ[s].grd*5*t*0.158;
		cha.equ[s].adef = 0;
	}
	if(strcmp(cha.equ[s].kind,"����")==0)
	{
	    cha.equ[s].axHP = cha.equ[s].grd*19*t*0.3;
		cha.equ[s].axMP = cha.equ[s].grd*3*t*0.3;
		cha.equ[s].aatc = 0;
		cha.equ[s].adef = cha.equ[s].grd*3*t*0.391;
	}
	if(strcmp(cha.equ[s].kind,"ͷ��")==0||strcmp(cha.equ[s].kind,"����")==0||strcmp(cha.equ[s].kind,"Ь��")==0)
	{
	    cha.equ[s].axHP = cha.equ[s].grd*19*t*0.14;
		cha.equ[s].axMP = cha.equ[s].grd*3*t*0.14;
		cha.equ[s].aatc = 0;
		cha.equ[s].adef = cha.equ[s].grd*3*t*0.174;
	}
	}
	if(strcmp(cha.prof,"��ʦ")==0)
	{
	if(strcmp(cha.equ[s].kind,"����")==0)
	{
		cha.equ[s].axHP = 0;
		cha.equ[s].axMP = 0;
		cha.equ[s].aatc = cha.equ[s].grd*2*t*0.684;
		cha.equ[s].adef = cha.equ[s].grd*3*t*0.087;
	}
	if(strcmp(cha.equ[s].kind,"��ָ")==0)
	{
		cha.equ[s].axHP = cha.equ[s].grd*5*t*0.14;
		cha.equ[s].axMP = cha.equ[s].grd*20*t*0.14;
	    cha.equ[s].aatc = cha.equ[s].grd*2*t*0.158;
		cha.equ[s].adef = 0;
	}
	if(strcmp(cha.equ[s].kind,"����")==0)
	{
	    cha.equ[s].axHP = cha.equ[s].grd*5*t*0.3;
		cha.equ[s].axMP = cha.equ[s].grd*20*t*0.3;
		cha.equ[s].aatc = 0;
		cha.equ[s].adef = cha.equ[s].grd*3*t*0.391;
	}
	if(strcmp(cha.equ[s].kind,"ͷ��")==0||strcmp(cha.equ[s].kind,"����")==0||strcmp(cha.equ[s].kind,"Ь��")==0)
	{
	    cha.equ[s].axHP = cha.equ[s].grd*5*t*0.14;
		cha.equ[s].axMP = cha.equ[s].grd*20*t*0.14;
		cha.equ[s].aatc = 0;
		cha.equ[s].adef = cha.equ[s].grd*3*t*0.174;
	}
	}
	if(strcmp(cha.prof,"��ʿ")==0)
	{
	if(strcmp(cha.equ[s].kind,"����")==0)
	{
		cha.equ[s].axHP = 0;
		cha.equ[s].axMP = 0;
		cha.equ[s].aatc = cha.equ[s].grd*3.5*t*0.684;
		cha.equ[s].adef = cha.equ[s].grd*3*t*0.087;
	}
	if(strcmp(cha.equ[s].kind,"��ָ")==0)
	{
		cha.equ[s].axHP = cha.equ[s].grd*12*t*0.14;
		cha.equ[s].axMP = cha.equ[s].grd*11*t*0.14;
	    cha.equ[s].aatc = cha.equ[s].grd*3.5*t*0.158;
		cha.equ[s].adef = 0;
	}
	if(strcmp(cha.equ[s].kind,"����")==0)
	{
	    cha.equ[s].axHP = cha.equ[s].grd*12*t*0.3;
		cha.equ[s].axMP = cha.equ[s].grd*11*t*0.3;
		cha.equ[s].aatc = 0;
		cha.equ[s].adef = cha.equ[s].grd*3*t*0.391;
	}
	if(strcmp(cha.equ[s].kind,"ͷ��")==0||strcmp(cha.equ[s].kind,"����")==0||strcmp(cha.equ[s].kind,"Ь��")==0)
	{
	    cha.equ[s].axHP = cha.equ[s].grd*12*t*0.14;
		cha.equ[s].axMP = cha.equ[s].grd*11*t*0.14;
		cha.equ[s].aatc = 0;
		cha.equ[s].adef = cha.equ[s].grd*3*t*0.174;
	}
	}
	cha.n = s;
	cha = Equname(cha);
	return cha;
}

struct CHARACTER Equip(struct CHARACTER cha)
{
    int n=cha.n,m=cha.m,t;
    struct EQUIPMENT p;
	if(cha.grd<cha.equ[n].grd)
	{
	    printf("װ���ȼ�����\n");
		return cha;
	}
	if(strcmp(cha.equ[n].kind,"ͷ��")==0)
	{
	 t = 0;
	}
	if(strcmp(cha.equ[n].kind,"����")==0)
	{
	 t = 1;
	}
	if(strcmp(cha.equ[n].kind,"����")==0)
	{
	 t = 2;
	}
	if(strcmp(cha.equ[n].kind,"����")==0)
	{
	 t = 3;
	}
	if(strcmp(cha.equ[n].kind,"Ь��")==0)
	{
	 t = 4;
	}
	if(strcmp(cha.equ[n].kind,"��ָ")==0)
	{
	 t = 5;
	 if(cha.equ[t].rank!=' ')
	 {
	  t = 6;
	  if(cha.equ[t].rank!=' ')
	  {
	   t = 5;
	  }
	 }
	}
	if (cha.equ[t].rank != ' ')
	{
		if (cha.HP >= cha.xHP - cha.equ[t].axHP)
		{
			cha.HP = cha.xHP-cha.equ[t].axHP+cha.equ[n].axHP;
		}
		cha.xHP = cha.xHP-cha.equ[t].axHP+cha.equ[n].axHP;
		if (cha.MP >= cha.xMP - cha.equ[t].axMP)
		{
			cha.MP = cha.xMP-cha.equ[t].axMP+cha.equ[n].axMP;
		}
		cha.xMP = cha.xMP-cha.equ[t].axMP+cha.equ[n].axMP;
		cha.atc = cha.atc-cha.equ[t].aatc+cha.equ[n].aatc;
		cha.def = cha.def-cha.equ[t].adef+cha.equ[n].adef;
		p = cha.equ[t];
		cha.equ[t] = cha.equ[n];
		cha.equ[n] = p;
	}
	if (cha.equ[t].rank == ' ')
	{
	    p = cha.equ[t];
	    cha.equ[t] = cha.equ[n];
	    while(n<=cha.e-2)
	    {
	      cha.equ[n] = cha.equ[n+1];
	      n++;
	     }
	    cha.equ[cha.e-1] = p;
	    while(m<=cha.t-2)
	    {
	      cha.goods[m] = cha.goods[m+1];
	      m++;
	     }
	    cha.goods[cha.t-1].nam = '\0';
	    cha.t -= 1;
	    cha.e -= 1;
		if (cha.HP == cha.xHP)
		{
			cha.HP = cha.HP+cha.equ[t].axHP;
		}
		cha.xHP = cha.xHP+cha.equ[t].axHP;
		if (cha.MP == cha.xMP)
		{
			cha.MP = cha.MP+cha.equ[t].axMP;
		}
		cha.xMP = cha.xMP+cha.equ[t].axMP;
		cha.atc = cha.atc+cha.equ[t].aatc;
		cha.def = cha.def+cha.equ[t].adef;
	}
	return cha;
}

struct CHARACTER MakeEqu(struct CHARACTER cha)
{
 printf("1.(15Lv)��ͭ��װ\n");
 printf("2.(25Lv)������װ\n");
 printf("3.(40Lv)��ħ��װ\n");
 int m,n,a,t,e,i;
 t = cha.t-1;
 e = cha.e;
 printf("��ѡ��");
 scanf("%d",&m);
 getchar();
 if(m==1)
 {
  printf("1.��ͭͷ��\n");
  printf("2.��ͭ����\n");
  printf("3.��ͭ��\n");
  printf("4.��ͭ��\n");
  printf("5.��ͭЬ\n");
  printf("6.��ͭ��ָ\n");
  printf("��ѡ��");
  scanf("%d",&n);
  getchar();
  i=0;
  while(i<=t)
  {
	  if(cha.goods[i].nam=='a')
	  {
		  break;
	  }
	  i++;
  }
  if(n==1||n==3||n==5)
  {
   printf("��Ҫ2����ͭ\n");
   printf("������8���\n");
   printf("1.ȷ��  2.������\n");
   printf("��ѡ��");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-2<0||i==cha.t)
	{
	 printf("��ͭ����\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("�����ռ䲻��\n");
	  return cha;
	}
	if(cha.mny<8)
	{
	 printf("��Ҳ���\n");
	 return cha;
	}
	cha.mny -= 8;
	if(cha.goods[i].q==2)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>2)
	{
	 cha.goods[i].q -= 2;
	}
	if(n==1)
	{
	 printf("�����ͭͷ��\n");
	 strcpy(cha.equ[e].kind,"ͷ��");
	}
	if(n==3)
	{
	 printf("�����ͭ��\n");
	 strcpy(cha.equ[e].kind,"����");
	}
	if(n==5)
	{
	 printf("�����ͭЬ\n");
	 strcpy(cha.equ[e].kind,"Ь��");
	}
	cha.goods[t+1].nam = '*';
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 15;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
  if(n==2)
  {
   printf("��Ҫ8����ͭ\n");
   printf("������32���\n");
   printf("1.ȷ��  2.������\n");
   printf("��ѡ��");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-8<0||i==cha.t)
	{
	 printf("��ͭ����\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("�����ռ䲻��\n");
	  return cha;
	}
	if(cha.mny<32)
	{
	 printf("��Ҳ���\n");
	 return cha;
	}
	cha.mny -= 32;
	if(cha.goods[i].q==8)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>8)
	{
	 cha.goods[i].q -= 8;
	}
	printf("�����ͭ����\n");
	cha.goods[t+1].nam = '*';
	strcpy(cha.equ[e].kind,"����");
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 15;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
  if(n==4)
  {
   printf("��Ҫ12����ͭ\n");
   printf("������48���\n");
   printf("1.ȷ��  2.������\n");
   printf("��ѡ��");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-12<0||i==cha.t)
	{
	 printf("��ͭ����\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("�����ռ䲻��\n");
	  return cha;
	}
	if(cha.mny<48)
	{
	 printf("��Ҳ���\n");
	 return cha;
	}
	cha.mny -= 48;
	if(cha.goods[i].q==12)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>12)
	{
	 cha.goods[i].q -= 12;
	}
	printf("�����ͭ��\n");
	cha.goods[t+1].nam = '*';
	strcpy(cha.equ[e].kind,"����");
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 15;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
   if(n==6)
  {
   printf("��Ҫ4����ͭ\n");
   printf("������16���\n");
   printf("1.ȷ��  2.������\n");
   printf("��ѡ��");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-4<0||i==cha.t)
	{
	 printf("��ͭ����\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("�����ռ䲻��\n");
	  return cha;
	}
	if(cha.mny<16)
	{
	 printf("��Ҳ���\n\n");
	 return cha;
	}
	cha.mny -= 16;
	if(cha.goods[i].q==4)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>4)
	{
	 cha.goods[i].q -= 4;
	}
	printf("��ù�ͭ��ָ\n");
	cha.goods[t+1].nam = '*';
	strcpy(cha.equ[e].kind,"��ָ");
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 15;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
 }
 if(m==2)
 {
  printf("1.����ͷ��\n");
  printf("2.�������\n");
  printf("3.�����\n");
  printf("4.�����䵶\n");
  printf("5.����Ь\n");
  printf("6.ˮ����ָ\n");
  printf("��ѡ��");
  scanf("%d",&n);
  getchar();
  i=0;
  while(i<=t)
  {
	  if(cha.goods[i].nam=='b')
	  {
		  break;
	  }
	  i++;
  }
  if(n==1||n==3||n==5)
  {
   printf("��Ҫ2�����걦ʯ\n");
   printf("������14���\n");
   printf("1.ȷ��  2.������\n");
   printf("��ѡ��");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-2<0||i==cha.t)
	{
	 printf("���걦ʯ����\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("�����ռ䲻��\n");
	  return cha;
	}
	if(cha.mny<14)
	{
	 printf("��Ҳ���\n");
	 return cha;
	}
	cha.mny -= 14;
	if(cha.goods[i].q==2)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>2)
	{
	 cha.goods[i].q -= 2;
	}
	if(n==1)
	{
	 printf("�������ͷ��\n");
	 strcpy(cha.equ[e].kind,"ͷ��");
	}
	if(n==3)
	{
	 printf("��������\n");
	 strcpy(cha.equ[e].kind,"����");
	}
	if(n==5)
	{
	 printf("�������Ь\n");
	 strcpy(cha.equ[e].kind,"Ь��");
	}
	cha.goods[t+1].nam = '*';
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 25;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
  if(n==2)
  {
   printf("��Ҫ8�����걦ʯ\n");
   printf("������56���\n");
   printf("1.ȷ��  2.������\n");
   printf("��ѡ��");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-8<0||i==cha.t)
	{
	 printf("���걦ʯ����\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("�����ռ䲻��\n");
	  return cha;
	}
	if(cha.mny<56)
	{
	 printf("��Ҳ���\n");
	 return cha;
	}
	cha.mny -= 56;
	if(cha.goods[i].q==8)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>8)
	{
	 cha.goods[i].q -= 8;
	}
	printf("����������\n");
	cha.goods[t+1].nam = '*';
	strcpy(cha.equ[e].kind,"����");
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 25;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
  if(n==4)
  {
   printf("��Ҫ12�����걦ʯ\n");
   printf("������84���\n");
   printf("1.ȷ��  2.������\n");
   printf("��ѡ��");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-12<0||i==cha.t)
	{
	 printf("���걦ʯ����\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("�����ռ䲻��\n");
	  return cha;
	}
	if(cha.mny<84)
	{
	 printf("��Ҳ���\n");
	 return cha;
	}
	cha.mny -= 84;
	if(cha.goods[i].q==12)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>12)
	{
	 cha.goods[i].q -= 12;
	}
	printf("��ð����䵶\n");
	cha.goods[t+1].nam = '*';
	strcpy(cha.equ[e].kind,"����");
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 25;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
   if(n==6)
  {
   printf("��Ҫ4�����걦ʯ\n");
   printf("������28���\n");
   printf("1.ȷ��  2.������\n");
   printf("��ѡ��");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-4<0||i==cha.t)
	{
	 printf("���걦ʯ����\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("�����ռ䲻��\n");
	  return cha;
	}
	if(cha.mny<28)
	{
	 printf("��Ҳ���\n");
	 return cha;
	}
	cha.mny -= 28;
	if(cha.goods[i].q==4)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>4)
	{
	 cha.goods[i].q -= 4;
	}
	printf("���ˮ����ָ\n");
	cha.goods[t+1].nam = '*';
	strcpy(cha.equ[e].kind,"��ָ");
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 25;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
 }
 if(m==3)
 {
  printf("1.��ħͷ��\n");
  printf("2.��ħ����\n");
  printf("3.��ħ��\n");
  if(strcmp(cha.prof,"սʿ")==0)
  {
   printf("4.Ѫ��\n");
  }
  if(strcmp(cha.prof,"��ʦ")==0)
  {
   printf("4.�ɻ귨��\n");
  }
  if(strcmp(cha.prof,"��ʿ")==0)
  {
   printf("4.�޼���\n");
  }
  printf("5.��ħЬ\n");
  printf("6.ħѪ��ָ\n");
  printf("��ѡ��");
  scanf("%d",&n);
  getchar();
  i=0;
  while(i<=t)
  {
	  if(cha.goods[i].nam=='c')
	  {
		  break;
	  }
	  i++;
  }
  if(n==1||n==3||n==5)
  {
   printf("��Ҫ2����ħ��Ϣ\n");
   printf("������21���\n");
   printf("1.ȷ��  2.������\n");
   printf("��ѡ��");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-2<0||i==cha.t)
	{
	 printf("��ħ��Ϣ����\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("�����ռ䲻��\n");
	  return cha;
	}
	if(cha.mny<21)
	{
	 printf("��Ҳ���\n");
	 return cha;
	}
	cha.mny -= 21;
	if(cha.goods[i].q==2)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>2)
	{
	 cha.goods[i].q -= 2;
	}
	if(n==1)
	{
	 printf("��ö�ħͷ��\n");
	 strcpy(cha.equ[e].kind,"ͷ��");
	}
	if(n==3)
	{
	 printf("��ö�ħ��\n");
	 strcpy(cha.equ[e].kind,"����");
	}
	if(n==5)
	{
	 printf("��ö�ħЬ\n");
	 strcpy(cha.equ[e].kind,"Ь��");
	}
	cha.goods[t+1].nam = '*';
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 40;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
  if(n==2)
  {
   printf("��Ҫ8����ħ��Ϣ\n");
   printf("������85���\n");
   printf("1.ȷ��  2.������\n");
   printf("��ѡ��");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-8<0||i==cha.t)
	{
	 printf("��ħ��Ϣ����\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("�����ռ䲻��\n");
	  return cha;
	}
	if(cha.mny<85)
	{
	 printf("��Ҳ���\n");
	 return cha;
	}
	cha.mny -= 85;
	if(cha.goods[i].q==8)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>8)
	{
	 cha.goods[i].q -= 8;
	}
	printf("��ö�ħ����\n");
	cha.goods[t+1].nam = '*';
	strcpy(cha.equ[e].kind,"����");
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 40;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
  if(n==4)
  {
   printf("��Ҫ12����ħ��Ϣ\n");
   printf("������127���\n");
   printf("1.ȷ��  2.������\n");
   printf("��ѡ��");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-12<0||i==cha.t)
	{
	 printf("��ħ��Ϣ����\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("�����ռ䲻��\n");
	  return cha;
	}
	if(cha.mny<127)
	{
	 printf("��Ҳ���\n");
	 return cha;
	}
	cha.mny -= 127;
	if(cha.goods[i].q==12)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>12)
	{
	 cha.goods[i].q -= 12;
	}
	if(strcmp(cha.prof,"սʿ")==0)
	{
	 printf("���Ѫ��\n");
	}
	if(strcmp(cha.prof,"��ʦ")==0)
	{
	 printf("����ɻ귨��\n");
	}
	if(strcmp(cha.prof,"��ʿ")==0)
	{
	 printf("����޼���\n");
	}
	cha.goods[t+1].nam = '*';
	strcpy(cha.equ[e].kind,"����");
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 40;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
   if(n==6)
  {
   printf("��Ҫ4����ħ��Ϣ\n");
   printf("������42���\n");
   printf("1.ȷ��  2.������\n");
   printf("��ѡ��");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-4<0||i==cha.t)
	{
	 printf("��ħ��Ϣ����\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("�����ռ䲻��\n");
	  return cha;
	}
	if(cha.mny<42)
	{
	 printf("��Ҳ���\n");
	 return cha;
	}
	cha.mny -= 42;
	if(cha.goods[i].q==4)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>4)
	{
	 cha.goods[i].q -= 4;
	}
	printf("���ħѪ��ָ\n");
	cha.goods[t+1].nam = '*';
	strcpy(cha.equ[e].kind,"��ָ");
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 40;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
 }     //m=3
 return cha;
}

struct CHARACTER BuyEqu(struct CHARACTER cha)
{
	printf("1.ͷ��  2.����  3.����  4.����  5.Ь��\n");
	printf("��ѡ��");
	int n;
	scanf("%d", &n);
	getchar();
	if(n!=1&&n!=2&&n!=3&&n!=4&&n!=5)
	{
	 printf("\n");
	 return cha;
	}
	if (((n==1||n==3||n==5)&&cha.mny<cha.grd*4/17.0)||(n==2&&cha.mny<cha.grd*4/17.0*4)||
		(n==4&&cha.mny<cha.grd*4/17.0*6))
	{
		printf("��Ҳ���\n");
		printf("ȷ��");
		getchar();
		printf("\n");
		return cha;
	}
	else
	{
		int w,s,r;
		w = cha.t;
		if(w==17)
		{
			printf("�����ռ䲻��\n");
			printf("\n");
			return cha;
		}
		if(n==1||n==3||n==5)
		{
		 printf("��Ҫ %d���\n",(int)(cha.grd*4/17.0));
		}
		if(n==2)
		{
		 printf("��Ҫ %d���\n",(int)(cha.grd*4/17.0*4));
		}
		if(n==4)
		{
		 printf("��Ҫ %d���\n",(int)(cha.grd*4/17.0*6));
		}
		printf("�Ƿ����\n");
		printf("1.����  2.������\n");
		printf("��ѡ��");
		scanf("%d",&r);
		getchar();
		if(r!=1)
		{
			printf("\n");
			return cha;
		}
		cha.goods[w].nam = '*';
		cha.t += 1;
		s = cha.e;
		cha.equ[s].grd = cha.grd;
		if(n==1)
		{
			strcpy(cha.equ[s].kind,"ͷ��");
		}
		if(n==2)
		{
		    strcpy(cha.equ[s].kind,"����");
		}
		if(n==3)
		{
			strcpy(cha.equ[s].kind,"����");
		}
		if(n==4)
		{
			strcpy(cha.equ[s].kind,"����");
		}
		if(n==5)
		{
			strcpy(cha.equ[s].kind,"Ь��");
		}
		cha.e += 1;
		cha.equ[s].rank = 'D';
		cha = EquAtt(cha);
		if(n==1||n==3||n==5)
		{
		 cha.mny -= cha.grd*4/17.0;
		 printf("���� %d���\n",(int)(cha.grd*4/17.0));
		}
		if(n==2)
		{
		 cha.mny -= cha.grd*4/17.0*4;
		 printf("���� %d���\n",(int)(cha.grd*4/17.0*4));
		}
		if(n==4)
		{
		 cha.mny -= cha.grd*4/17.0*6;
		 printf("���� %d���\n",(int)(cha.grd*4/17.0*6));
		}
		printf("\n");
		return cha;
    }
}

struct CHARACTER BuyGoods(struct CHARACTER cha)
{
    printf("1.#  2.%%  3.@\n��ѡ��");
    int n,t,w,r,i;
    scanf("%d",&n);
    getchar();
    if(n!=1&&n!=2&&n!=3)
    {
      printf("\n");
      return cha;
     }
    printf("��������:");
    w = cha.t;
    scanf("%d",&t);
    getchar();
    if(t<0)
    {
      t = 0;
    }
    if((n==1&&cha.mny-cha.grd*3*t/3<0)||(n==2&&cha.mny-cha.grd*5*t/3<0)||(n==3&&cha.mny-cha.grd*10*t/3<0))
    {
      printf("��Ҳ���\n");
      printf("ȷ��");
      getchar();
      printf("\n");
      return cha;
     }
	if(w==17)
	{
	  printf("�����ռ䲻��\n");
	  printf("\n");
	  return cha;
	}
	if(n==1)
	{
	 printf("��Ҫ %d���\n",cha.grd*3*t/3);
	}
	if(n==2)
	{
	 printf("��Ҫ %d���\n",cha.grd*5*t/3);
	}
	if(n==3)
	{
	 printf("��Ҫ %d���\n",cha.grd*10*t/3);
	}
	printf("�Ƿ����\n");
    printf("1.����  2.������\n");
	printf("��ѡ��");
	scanf("%d",&r);
   	getchar();
	i = 0;
	if(r!=1)
	{
	 return cha;
	}
    if(n==1)
    {
	  while(i<=w-1)
	  {
	   if(cha.goods[i].nam=='#')
	   {
	    break;
	   }
	   i++;
	  }
	  if(i==w)
	  {
		strcpy(cha.goods[w].name,"�ͼ��ָ�ҩˮ");
	    cha.goods[w].nam = '#';
	    cha.goods[w].q = t;
		cha.t++;
	  }
	  else
	  {
	    cha.goods[i].q += t;
	  }
	  cha.mny -= cha.grd*3*t/3;
	  printf("���� %d���\n",cha.grd*3*t/3);
     }
     if(n==2)
    {
	  while(i<=w-1)
	  {
	   if(cha.goods[i].nam=='%')
	   {
	    break;
	   }
	   i++;
	  }
	  if(i==w)
	  {
	    strcpy(cha.goods[w].name,"�м��ָ�ҩˮ");
	    cha.goods[w].nam = '%';
	    cha.goods[w].q = t;
		cha.t++;
	  }
	  else
	  {
	    cha.goods[i].q += t;
	  }
	  cha.mny -= cha.grd*5*t/3;
	  printf("���� %d���\n",cha.grd*5*t/3);
	 }
	 if(n==3)
    {
	  while(i<=w-1)
	  {
	   if(cha.goods[i].nam=='@')
	   {
	    break;
	   }
	   i++;
	  }
	  if(i==w)
	  {
		strcpy(cha.goods[w].name,"�߼��ָ�ҩˮ");
	    cha.goods[w].nam = '@';
	    cha.goods[w].q = t;
		cha.t++;
	  }
	  else
	  {
	    cha.goods[i].q += t;
	  }
	  cha.mny -= cha.grd*10*t/3;
	  printf("���� %d���\n",cha.grd*10*t/3);
	 }
	printf("ȷ��");
    getchar();
    printf("\n");
    return cha;
}

double GoodPrice(struct GOODS good,int grd)
{
 double mny;
 if(good.nam=='#')
 {
  mny = grd*3/3.0;
 }
 if(good.nam=='%')
 {
  mny = grd*5/3.0;
 }
 if(good.nam=='@')
 {
  mny = grd*10/3.0;
 }
 if(good.nam=='a')
 {
  mny = 15*18/17.0/2;
 }
 if(good.nam=='b')
 {
  mny = 25*18/17.0/2;
 }
 if(good.nam=='$')
 {
  mny = 2;
 }
 return mny;
}

double EquPrice(struct EQUIPMENT equ)
{
	double t,mny;
	if(strcmp(equ.kind,"ͷ��")==0)
	{
		t = 1/17.0;
	}
	if(strcmp(equ.kind,"����")==0)
	{
		t = 4/17.0;
	}
	if(strcmp(equ.kind,"����")==0)
	{
		t = 1/17.0;
	}
	if(strcmp(equ.kind,"����")==0)
	{
		t = 6/17.0;
	}
	if(strcmp(equ.kind,"Ь��")==0)
	{
		t = 1/17.0;
	}
	if(strcmp(equ.kind,"��ָ")==0)
	{
		t = 2/17.0;
	}
	if(equ.rank == 'A')
	{
		mny = equ.grd*18*t;
	}
	if(equ.rank == 'B')
	{
		mny = equ.grd*12*t;
	}
	if(equ.rank == 'C')
	{
		mny = equ.grd*8*t;
	}
	if(equ.rank == 'D')
	{
		mny = equ.grd*4*t;
	}
	return mny;
}

struct CHARACTER Sell(struct CHARACTER cha)
{
    int i = 0,j = 0,n =6,s,m,w;
    double mny;
	printf("����\n");
	while (cha.goods[i].nam != '\0'&&i<=16)
	{
	    if(cha.goods[i].nam=='*')
	    {
		  printf("%d.%c\n", i + 1, cha.goods[i].nam);
		}
		else
		{
		  printf("%d.%c��%d\n", i + 1, cha.goods[i].nam,cha.goods[i].q);
		}
		i++;
	}
	printf("��ѡ����Ʒ");
    scanf("%d", &i);
	getchar();
    if(cha.goods[i-1].nam == '*')
    {
        for(;j<=i-1;j++)
        {
            if(cha.goods[j].nam=='*')
            {
              n++;
            }
        }
        cha.m = i-1;
        cha.n = n;
        cha = SeeEqu(cha);
		mny = EquPrice(cha.equ[n])/2.0;
		printf("��ֵ  %.0lf���\n",mny);
        printf("1.����   2.ȷ��\n");
        printf("��ѡ��");
        scanf("%d",&s);
		getchar();
        if(s==1)
        {
          printf("ȷ��");
		  getchar();
		  cha.mny += mny;
		  m = cha.m;
		  while(m<=cha.t-2)
		  {
		    cha.goods[m] = cha.goods[m+1];
		    m++;
		  }
		  cha.goods[cha.t-1].nam = '\0';
		  strcpy(cha.goods[cha.t-1].name,"\0'");
		  while(n<=cha.e-2)
		  {
			  cha.equ[n] = cha.equ[n+1];
			  n++;
		  }
		  cha.equ[cha.e-1].grd = 0;
		  strcpy(cha.equ[cha.e-1].name,"\0");
		  strcpy(cha.equ[cha.e-1].kind,"\0");
		  cha.equ[cha.e-1].rank = ' ';
		  cha.equ[cha.e-1].axHP = 0;
		  cha.equ[cha.e-1].axMP = 0;
		  cha.equ[cha.e-1].aatc = 0;
		  cha.equ[cha.e-1].adef = 0;
		  cha.t -= 1;
		  cha.e -= 1;
        }
        cha = Sell(cha);
        return cha;
    }
    if(cha.goods[i-1].nam != '*'&&cha.goods[i-1].nam!='\0')
    {
       cha.m = i-1;
       m = cha.m;
       SeeGood(cha);
	   mny = GoodPrice(cha.goods[i-1],cha.grd)/2.0;
	   if(m==-1)
	   {
	    mny = 0;
	   }
	   printf("����  %.0lf���\n",mny);
       printf("1.����    2.ȷ��\n");
       printf("��ѡ��");
       scanf("%d",&s);
	   getchar();
       if(s==1)
       {
         printf("������Ŀ:");
         scanf("%d",&w);
		 getchar();
		 if(w<0)
		 {
		   w = 0;
		 }
		 if(w>cha.goods[i-1].q)
		 {
		  w = cha.goods[i-1].q;
		 }
		 mny = mny*w;
         printf("��ֵ  %.0lf���\n",mny);
         printf("ȷ��");
		 getchar();
         cha.mny += mny;
	     cha.goods[i-1].q -= w;
		 if(cha.goods[i-1].q==0)
		 {
		   while(m<=cha.t-2)
		  {
		    cha.goods[m] = cha.goods[m+1];
		    m++;
		  }
		  cha.goods[cha.t-1].nam='\0';
		  strcpy(cha.goods[cha.t-1].name,"\0");
		  cha.t -= 1;
		 }
	   }
	   cha = Sell(cha);
	   return cha;
    }
    printf("\n");
    return cha;
}

struct CHARACTER Use(struct CHARACTER cha)
{
    int m,t;
    m = cha.m;
    t = cha.t;
    if(cha.goods[m].nam == '%')
    {
      if(cha.goods[m].q==1)
      {
        while(m<=t-2)
		  {
		    cha.goods[m] = cha.goods[m+1];
		    m++;
		  }
		  cha.goods[t-1].nam = '\0';
		  strcpy(cha.goods[t-1].name,"\0");
		  cha.t -= 1;
	  }
      cha.HP += cha.xHP*0.5;
	  cha.MP += cha.xMP*0.5;
      cha.goods[m].q -= 1;
    }
    if(cha.goods[m].nam == '#')
    {
      if(cha.goods[m].q==1)
      {
        while(m<=t-2)
		  {
		    cha.goods[m] = cha.goods[m+1];
		        m++;
		  }
		 cha.goods[t-1].nam = '\0';
		 strcpy(cha.goods[t-1].name,"\0");
		 cha.t -= 1;
	  }
      cha.HP += cha.xHP*0.3;
	  cha.MP += cha.xMP*0.3;
      cha.goods[m].q -= 1;
    }
    if(cha.goods[m].nam == '@')
    {
	  if(m<0)
	  {
	   cha.HP = cha.xHP;
	   cha.MP = cha.xMP;
	  }
	  else
	  {
       if(cha.goods[m].q==1)
       {
        while(m<=t-2)
		  {
		    cha.goods[m] = cha.goods[m+1];
		    m++;
		  }
		 cha.goods[t-1].nam = '\0';
		 strcpy(cha.goods[t-1].name,"\0");
		 cha.t -= 1;
	   }
       cha.HP = cha.xHP;
	   cha.MP = cha.xMP;
       cha.goods[m].q -= 1;
	  }
    }
    if(cha.HP>cha.xHP)
    {
      cha.HP = cha.xHP;
    }
	if(cha.MP>cha.xMP)
    {
      cha.MP = cha.xMP;
    }
    return cha;
}

struct CHARACTER UpEqu(struct CHARACTER cha)
{
	int s,t,m;
	char name[20];
	double a[4] = {1.0,1.0,1.0,1.0};
	m = cha.m;
	printf("      1.%c\n\n",cha.equ[0].rank);
	printf("2.%c          6.%c\n\n",cha.equ[1].rank,cha.equ[5].rank);
	printf("3.%c          7.%c\n\n",cha.equ[2].rank,cha.equ[6].rank);
	printf("4.%c   5.%c\n",cha.equ[3].rank,cha.equ[4].rank);
	printf("��ѡ��");
	scanf("%d",&s);
	getchar();
	if(s!=1&&s!=2&&s!=3&&s!=4&&s!=5&&s!=6&&s!=7)
	{
	   return cha;
	}
	if(strcmp(cha.equ[s-1].name,"\0")==0)
	{
	 printf("��װ��\n");
	 printf("ȷ��");
	 getchar();
	 return cha;
	}
	if(cha.goods[m].nam=='$'&&cha.equ[s-1].grd>25)
	{
	 printf("װ���ȼ�����\n");
	 printf("ȷ��");
	 getchar();
	 return cha;
	}
	strcpy(name,cha.equ[s-1].name);
	name[2] = '\0';
	if(strcmp(name,"+1")==0)
	{
	 printf("��װ����ǿ������\n");
	 printf("ȷ��");
	 getchar();
	 return cha;
	}
    t = rand()%4;
	a[t] = 1.5;
	strcpy(name,"+1");
	strcat(name,cha.equ[s-1].name);
	strcpy(cha.equ[s-1].name,name);
	cha.equ[s-1].axHP *= a[0];
	cha.equ[s-1].axMP *= a[1];
	cha.equ[s-1].aatc *= a[2];
	cha.equ[s-1].adef *= a[3];
	if(t==0)
	{
	 cha.xHP += cha.equ[s-1].axHP/3.0;
	 cha.HP += cha.equ[s-1].axHP/3.0;
	 printf("����HP%.0lf\n",cha.equ[s-1].axHP/3);
	}
	if(t==1)
	{
	 cha.xMP += cha.equ[s-1].axMP/3.0;
	 cha.MP += cha.equ[s-1].axMP/3.0;
	 printf("����MP%.0lf\n",cha.equ[s-1].axMP/3);
	}
	if(t==2)
	{
	 cha.atc += cha.equ[s-1].aatc/3.0;
	 printf("���ӹ�����%.0lf\n",cha.equ[s-1].aatc/3);
	}
	if(t==3)
	{
	 cha.def = cha.equ[s-1].adef/3.0;
	 printf("���ӷ�����%.0lf\n",cha.equ[s-1].adef/3);
	}
	cha.goods[m].q--;
	t = cha.t;
	if(cha.goods[m].q==0)
	{
		while(m<=t-2)
		{
			cha.goods[m] = cha.goods[m+1];
			m++;
		}
		cha.goods[t-1].nam = '\0';
		strcpy(cha.goods[t-1].name,"\0");
		cha.t -= 1;
	}
	printf("ȷ��");
	getchar();
	return cha;
}

struct CHARACTER SeeGoods(struct CHARACTER cha)
{
	int i = 0,j = 0,n =6,t,s,m,w;

	//printf("cha.t=%d\n",cha.t);
	//printf("cha.e=%d\n",cha.e);
	cqlog(cha.t,cha.e);
	
	printf("����\n");
	printf("���       %.0lf\n", cha.mny);
	while (cha.goods[i].nam != '\0'&&i<=16)
	{
	    if(cha.goods[i].nam=='*')
	    {
		  printf("%d.%c\n", i + 1, cha.goods[i].nam);
		}
		else
		{
		 printf("%d.%c��%d\n", i + 1, cha.goods[i].nam,cha.goods[i].q);
		}
		i++;
	}
	printf("\n1.��Ʒ���� 2.ȷ��\n");
	printf("��ѡ��");
	scanf("%d", &t);
	getchar();
	if (t == 1)
	{
		printf("��ѡ����Ʒ");
		scanf("%d", &i);
		getchar();
        if(cha.goods[i-1].nam == '*')
        {
            for(;j<=i-1;j++)
            {
                if(cha.goods[j].nam=='*')
                {
                  n++;
                }
            }
            cha.m = i-1;       //ѡ��ĵ�i����Ʒ
            cha.n = n;         //ѡ��ĵ�n��װ��
            cha = SeeEqu(cha);
			cha.n = n;
            printf("1.װ��    2.�ӵ�   3.ȷ��\n");
            printf("��ѡ��");
            scanf("%d",&s);
			getchar();
            if(s==1)
            {
              cha = Equip(cha);
              printf("ȷ��");
		      getchar();
			  printf("\n");
            }
            if(s==2)
            {
              printf("ȷ��");
		      getchar();
		      m = cha.m;
		      while(m<=cha.t-2)
		      {
		        cha.goods[m] = cha.goods[m+1];
		        m++;
		      }
		      cha.goods[cha.t-1].nam = '\0';
              strcpy(cha.goods[cha.t-1].name,"\0");
			  cha.goods[cha.t-1].q=0;
		      while(n<=cha.e-2)
	          {
	             cha.equ[n] = cha.equ[n+1];
	             n++;
	          }
	          cha.equ[cha.e-1].grd = 0;
			  strcpy(cha.equ[cha.e-1].name,"\0");
			  strcpy(cha.equ[cha.e-1].kind,"\0");
	          cha.equ[cha.e-1].rank = ' ';
	          cha.equ[cha.e-1].axHP = 0;
			  cha.equ[cha.e-1].axHP = 0;
	          cha.equ[cha.e-1].aatc = 0;
	          cha.equ[cha.e-1].adef = 0;
	          cha.t -= 1;
	          cha.e -= 1;
             }
            cha = SeeGoods(cha);
            return cha;
		}
        if(cha.goods[i-1].nam == '%'||cha.goods[i-1].nam == '#')
        {
           cha.m = i-1;
           m = cha.m;
           SeeGood(cha);
           printf("1.ʹ��    2.�ӵ�   3.ȷ��\n");
           printf("��ѡ��");
           scanf("%d",&s);
		   getchar();
           if(s==1)
           {
              cha = Use(cha);
              printf("ȷ��");
		      getchar();
           }
           if(s==2)
           {
             printf("�ӵ���Ŀ:");
             scanf("%d",&w);
			 getchar();
             printf("ȷ��");
		     getchar();
		     if(w<0)
		     {
		       w = 0;
		     }
		     cha.goods[i-1].q -= w;
		     if(cha.goods[i-1].q<=0)
		     {
		      while(m<=cha.t-2)
		      {
		        cha.goods[m] = cha.goods[m+1];
		        m++;
		      }
		      cha.goods[cha.t-1].nam='\0';
			  strcpy(cha.goods[cha.t-1].name,"\0");
		      cha.goods[cha.t-1].q = 0;
			  cha.t--;
		     }
		    }
		   cha = SeeGoods(cha);
		   return cha;
         }
        if(cha.goods[i-1].nam == '@')
        {
           cha.m = i-1;
           m = cha.m;
           SeeGood(cha);
		   if(m<0)
		   {
		    printf("1.ʹ��    2.ȷ��\n");
			printf("��ѡ��");
			scanf("%d",&s);
			getchar();
			if(s==1)
            {
              cha = Use(cha);
              printf("ȷ��");
	      	  getchar();
			}
		   }
		   else
		   {
            printf("1.ʹ��    2.�ӵ�   3.ȷ��\n");
            printf("��ѡ��");
            scanf("%d",&s);
			getchar();
            if(s==1)
            {
              cha = Use(cha);
              printf("ȷ��");
	      	  getchar();
            }
            if(s==2)
            {
             printf("�ӵ���Ŀ:");
             scanf("%d",&w);
			 getchar();
             printf("ȷ��");
		     getchar();
		     if(w<0)
		     {
		       w = 0;
		     }
		     cha.goods[i-1].q -= w;
		     if(cha.goods[i-1].q<=0)
		     {
		       while(m<=cha.t-2)
			   {
		        cha.goods[m] = cha.goods[m+1];
		        m++;
		       }
		      cha.goods[cha.t-1].nam='\0';
			  strcpy(cha.goods[cha.t-1].name,"\0");
		      cha.goods[cha.t-1].q = 0;
			  cha.t--;
		     }
		    }
		   }
		   cha = SeeGoods(cha);
		   return cha;
         }
		if(cha.goods[i-1].nam == 'a'||cha.goods[i-1].nam == 'b'||cha.goods[i-1].nam == 'c')
		{
		   cha.m = i-1;
           m = cha.m;
           SeeGood(cha);
           printf("1.�ӵ�   2.ȷ��\n");
           printf("��ѡ��");
           scanf("%d",&s);
		   getchar();
           if(s==1)
           {
             printf("�ӵ���Ŀ:");
             scanf("%d",&w);
			 getchar();
             printf("ȷ��");
		     getchar();
		     if(w<0)
		     {
		       w = 0;
		     }
		     cha.goods[i-1].q -= w;
		     if(cha.goods[i-1].q<=0)
		     {
		       while(m<=cha.t-2)
			   {
		        cha.goods[m] = cha.goods[m+1];
		        m++;
		       }
		      cha.goods[cha.t-1].nam='\0';
			  strcpy(cha.goods[cha.t-1].name,"\0");
		      cha.goods[cha.t-1].q = 0;
			  cha.t--;
		     }
		   }
		   cha = SeeGoods(cha);
		   return cha;
		}
		if(cha.goods[i-1].nam == '$')
        {
           cha.m = i-1;
           m = cha.m;
           SeeGood(cha);
           printf("1.ʹ��    2.�ӵ�   3.ȷ��\n");
           printf("��ѡ��");
           scanf("%d",&s);
		   getchar();
           if(s==1)
           {
              cha = UpEqu(cha);
           }
           if(s==2)
           {
             printf("�ӵ���Ŀ:");
             scanf("%d",&w);
			 getchar();
             printf("ȷ��");
		     getchar();
		     if(w<0)
		     {
		       w = 0;
		     }
		     cha.goods[i-1].q -= w;
		     if(cha.goods[i-1].q<=0)
		     {
		       while(m<=cha.t-2)
		      {
		        cha.goods[m] = cha.goods[m+1];
		        m++;
		      }
		      cha.goods[cha.t-1].nam='\0';
			  strcpy(cha.goods[cha.t-1].name,"\0");
		      cha.goods[cha.t-1].q = 0;
			  cha.t--;
		     }
		    }
		   cha = SeeGoods(cha);
		   return cha;
         }
	}
	return cha;
}

void SeeSkill(struct CHARACTER cha)
{
 int i,t=0;
 if(strcmp(cha.prof,"��ʦ")==0)
 {
	 while(t==0)
	 {
		 printf("1.С����\n");
		 printf("2.�׵���\n");
		 printf("3.���ѻ���\n");
		 printf("4.��ǽ\n");
		 printf("5.��������\n");
		 printf("6.ħ������\n");
		 printf("7.�����Ӱ\n");
		 printf("��ѡ��");
		 scanf("%d",&i);
		 getchar();
		 if(i==1)
		 {
			 printf("�ȼ� 5��\n");
			 printf("����%.0lfMP����ħ��������1.5������һ��Ŀ��\n",(double)cha.grd*1.5);
			 printf("ȷ��");
			 getchar();
			 printf("\n");
		 }
		 if(i==2)
		 {
			 printf("�ȼ� 10��\n");
			 printf("����%.0lfMP����ħ��������1.8������һ��Ŀ��\n",(double)(cha.grd)*1.8);
			 printf("ȷ��");
			 getchar();
			 printf("\n");
		 }
		 if(i==3)
		 {
			 printf("�ȼ� 15��\n");
			 printf("����%.0lfMP����ħ��������1.6����������Ŀ��\n",(double)(cha.grd)*2.625);
			 printf("ȷ��");
			 getchar();
			 printf("\n");
		 }
		 if(i==4)
		 {
			 printf("�ȼ� 20��\n");
			 printf("����%.0lfMP����ħ��������1.6����������Ŀ��\n",(double)(cha.grd)*3.5);
			 printf("ȷ��");
			 getchar();
			 printf("\n");
		 }
		 if(i==5)
		 {
			 printf("�ȼ� 25��\n");
			 printf("����%.0lfMP����ħ��������1.7����������Ŀ��\n",(double)(cha.grd)*4.125);
			 printf("ȷ��");
			 getchar();
			 printf("\n");
		 }
		 if(i==6)
		 {
			 printf("�ȼ� 30��\n");
			 printf("����%.0lfMP������%%50�˺�\n",(double)(cha.grd)*1.5);
			 printf("ȷ��");
			 getchar();
			 printf("\n");
		 }
		 if(i==7)
		 {
			 printf("�ȼ� 40��\n");
			 printf("����%.0lfMP����ħ��������1.7���������Ŀ��\n",(double)(cha.grd)*6.5);
			 printf("ȷ��");
			 getchar();
			 printf("\n");
		 }
		 if(i!=1&&i!=2&&i!=3&&i!=4&&i!=5&&i!=6&&i!=7)
		 {
			 t = 1;
		 }
	 }
 }
 if(strcmp(cha.prof,"սʿ")==0)
 {
	 while(t==0)
	 {
		 printf("1.�һ𽣷�\n");
		 printf("2.��ʥս��\n");
		 printf("3.�����䵶\n");
		 printf("4.������\n");
		 printf("5.������ʾ\n");
		 printf("��ѡ��");
		 scanf("%d",&i);
		 getchar();
		 if(i==1)
		 {
			 printf("�ȼ� 5��\n");
			 printf("����%.0lfMP���Թ�������1.2������Ŀ��\n",(double)(cha.grd)/5.0*2.0);
			 printf("ȷ��");
			 getchar();
			 printf("\n");
		 }
		 if(i==2)
		 {
			 printf("�ȼ� 15��\n");
			 printf("����%.0lfMP���Թ�������1.4������Ŀ��\n",(double)(cha.grd)/5.0*3.0);
			 printf("ȷ��");
			 getchar();
			 printf("\n");
		 }
		 if(i==3)
		 {
			 printf("�ȼ� 25��\n");
			 printf("����%dMP��Ϊ���أ��������ܹ�������Ŀ��\n",cha.grd);
			 printf("ȷ��");
			 getchar();
			 printf("\n");
		 }
		 if(i==4)
		 {
			 printf("�ȼ� 35��\n");
			 printf("����%.0lfMP���Թ�������3������Ŀ��\n",(double)(cha.grd)/5.0*6.0);
			 printf("ȷ��");
			 getchar();
			 printf("\n");
		 }
		 if(i==5)
		 {
			 printf("�ȼ� 40��\n");
			 printf("����%.0lfMP������%%30�˺�\n",(double)(cha.grd)/5.0*3.0);
			 printf("ȷ��");
			 getchar();
			 printf("\n");
		 }
		 if(i!=1&&i!=2&&i!=3&&i!=4&&i!=5)
		 {
			 t = 1;
		 }
	 }
 }
 if(strcmp(cha.prof,"��ʿ")==0)
 {
	 while(t==0)
	 {
		 printf("1.�ٻ�����\n");
		 printf("2.�����\n");
		 printf("3.�޼�����\n");
		 printf("4.������\n");
		 printf("5.ʥ����\n");
		 printf("6.����֮��\n");
		 printf("��ѡ��");
		 scanf("%d",&i);
		 getchar();
		 if(i==1)
		 {
			 printf("�ȼ� 5��\n");
			 printf("����%.0lfMP���ٻ��������Լ������ޣ�������ֻ���ٻ�һ��\n",(double)(cha.grd)*2.2);
			 printf("ȷ��");
			 getchar();
			 printf("\n");
		 }
		 if(i==2)
		 {
			 printf("�ȼ� 12��\n");
			 printf("����%.0lfMP����ħ��������1������һ��Ŀ��\n",(double)(cha.grd)*2.2);
			 printf("ȷ��");
			 getchar();
			 printf("\n");
		 }
		 if(i==3)
		 {
			 printf("�ȼ� 18��\n");
			 printf("������MP�����Լ��Ͷ��ѻָ�ħ��������0.5����MP\n");
			 printf("ȷ��");
			 getchar();
			 printf("\n");
		 }
		 if(i==4)
		 {
			 printf("�ȼ� 25��\n");
			 printf("����%.0lfMP�����Լ��Ͷ��ѻָ�ħ��������1����HP����������\n",(double)(cha.atc)*1.3);
			 printf("ȷ��");
			 getchar();
			 printf("\n");
		 }
		 if(i==5)
		 {
			 printf("�ȼ� 32��\n");
			 printf("����%.0lfMP���������޵��˺�%%30\n",(double)(cha.grd)*2.2);
			 printf("ȷ��");
			 getchar();
			 printf("\n");
		 }
		 if(i==6)
		 {
			 printf("�ȼ� 40��\n");
			 printf("����%.0lfMP�����ɱ���֮�ܱ�������\n",(double)(cha.atc)*0.75);
			 printf("ȷ��");
			 getchar();
			 printf("\n");
		 }
		 if(i!=1&&i!=2&&i!=3&&i!=4&&i!=5&&i!=6)
		 {
			 t = 1;
		 }
	 }
 }
}

struct CHARACTER Skill(struct CHARACTER cha)
{
 int i,k;
 k = 0;
 cha.n = 0;
 if(strcmp(cha.prof,"��ʦ")==0)
 {
  if(cha.grd>=5)
  {
   printf("1.(%.0lfMP)С����\n",(double)cha.grd*1.5);
   k++;
  }
  if(cha.grd>=10)
  {
   printf("2.(%.0lfMP)�׵���\n",(double)(cha.grd)*1.8);
   k++;
  }
  if(cha.grd>=15)
  {
   printf("3.(%.0lfMP)���ѻ���\n",(double)(cha.grd)*2.625);
   k++;
  }
  if(cha.grd>=20)
  {
   printf("4.(%.0lfMP)��ǽ\n",(double)(cha.grd)*3.5);
   k++;
  }
  if(cha.grd>=25)
  {
   printf("5.(%.0lfMP)��������\n",(double)(cha.grd)*4.125);
   k++;
  }
  if(cha.grd>=30)
  {
   printf("6.(%.0lfMP)ħ������\n",(double)(cha.grd)*1.5);
   k++;
  }
  if(cha.grd>=40)
  {
   printf("7.(%.0lfMP)�����Ӱ\n",(double)(cha.grd)*6.5);
   k++;
  }
  printf("��ѡ��");
  scanf("%d",&i);
  getchar();
  if(i>k||i<=0)
  {
   cha.n = 2;
   return cha;
  }
  if((i==1&&cha.MP<(double)cha.grd*1.5)||(i==2&&cha.MP<(double)(cha.grd)*1.8)||(i==3&&cha.MP<(double)(cha.grd)*2.625)||
	  (i==4&&cha.MP<(double)(cha.grd)*3.5)||(i==5&&cha.MP<(double)(cha.grd)*4.125)||(i==6&&cha.MP<(double)(cha.grd)*1.5)||
	  (i==7&&cha.MP<(double)(cha.grd)*6.5))
  {
   return cha;
  }
  cha.n++;
  if(i==1)
  {
   cha.MP -= (double)cha.grd*1.5;
   cha.h = 1.5;
   cha.q = 1;
  }
  if(i==2)
  {
   cha.MP -= (double)(cha.grd)*1.8;
   cha.h = 1.8;
   cha.q = 1;
  }
  if(i==3)
  {
   cha.MP -= (double)(cha.grd)*2.625;
   cha.h = 1.6;
   cha.q = 2;
  }
  if(i==4)
  {
   cha.MP -= (double)(cha.grd)*3.5;
   cha.h = 1.6;
   cha.q = 3;
  }
  if(i==5)
  {
   cha.MP -= (double)(cha.grd)*4.125;
   cha.h = 1.7;
   cha.q = 3;
  }
  if(i==6)
  {
   if(cha.k==1.501)
   {
    cha.n = 2;
	printf("�����ظ�����\n");
	printf("ȷ��");
	getchar();
	return cha;
   }
   cha.MP -= (double)(cha.grd)*1.5;
   cha.k = 1.5;
  }
  if(i==7)
  {
   cha.MP -= (double)(cha.grd)*6.5;
   cha.h = 1.7;
   cha.q = 5;
  }
 }
 if(strcmp(cha.prof,"սʿ")==0)
 {
  if(cha.grd>=5)
  {
   printf("1.(%.0lfMP)�һ𽣷�\n",(double)(cha.grd)/5.0*2.0);
   k++;
  }
  if(cha.grd>=15)
  {
   printf("2.(%.0lfMP)��ʥս��\n",(double)(cha.grd)/5.0*3.0);
   k++;
  }
  if(cha.grd>=25)
  {
   if(cha.q==1)
   {
    printf("3.(%dMP)�����䵶(��)\n",cha.grd);
   }
   if(cha.q==2)
   {
    printf("3.(%dMP)�����䵶(��)\n",cha.grd);
   }
   k++;
  }
  if(cha.grd>=35)
  {
   printf("4.(%.0lfMP)������\n",(double)(cha.grd)/5.0*6.0);
   k++;
  }
  if(cha.grd>=40)
  {
   printf("5.(%.0lfMP)������ʾ\n",(double)(cha.grd)/5.0*3.0);
   k++;
  }
  printf("��ѡ��");
  scanf("%d",&i);
  getchar();
  if(i>k||i<=0)
  {
   cha.n = 2;
   return cha;
  }
  if((i==1&&cha.MP<(double)(cha.grd)/5.0*2.0)||(i==2&&cha.MP<(double)(cha.grd)/5.0*3.0)||(i==3&&cha.MP<cha.grd)||
	  (i==4&&cha.MP<(double)(cha.grd)/5.0*6.0)||(i==5&&cha.MP<(double)(cha.grd)/5.0*3.0))
  {
   return cha;
  }
  cha.n++;
  if(i==1)
  {
   cha.MP -= (double)(cha.grd)/5.0*2.0;
   cha.h = 1.2;
   cha.q = 1;
  }
  if(i==2)
  {
   cha.MP -= (double)(cha.grd)/5.0*3.0;
   cha.h = 1.4;
   cha.q = 1;
  }
  if(i==3)
  {
   cha.MP -= cha.grd;
   cha.h = 1.0;
   if(cha.q==1)
   {
    printf("�ѿ���\n");
    cha.q = 2;
	return cha;
   }
   if(cha.q==2)
   {
    printf("�ѹر�\n");
    cha.q = 1;
   }
  }
  if(i==4)
  {
   cha.MP -= (double)(cha.grd)/5.0*6.0;
   cha.h = 3;
   cha.q = 1;
  }
  if(i==5)
  {
   if(cha.k==1.301)
   {
    cha.n = 2;
	printf("�����ظ�����\n");
	printf("ȷ��");
	getchar();
	return cha;
   }
   cha.MP -= (double)(cha.grd)/5.0*3.0;
   printf("�ѿ���\n");
   cha.k = 1.3;
  }
 }
 if(strcmp(cha.prof,"��ʿ")==0)
 {
  if(cha.grd>=5)
  {
   printf("1.(%.0lfMP)�ٻ�����\n",(double)(cha.grd)*2.2);
   k++;
  }
  if(cha.grd>=12)
  {
   printf("2.(%.0lfMP)�����\n",(double)(cha.grd)*2.2);
   k++;
  }
  if(cha.grd>=18)
  {
   printf("3.(0MP)�޼�����\n");
   k++;
  }
  if(cha.grd>=25)
  {
   printf("4.(%.0lfMP)������\n",(double)(cha.atc)*1.3);
   k++;
  }
  if(cha.grd>=32)
  {
   printf("5.(%.0lfMP)ʥ����\n",(double)(cha.grd)*2.2);
   k++;
  }
  if(cha.grd>=40)
  {
   printf("6.(%.0lfMP)����֮��\n",(double)(cha.atc)*0.75);
   k++;
  }
  printf("��ѡ��");
  scanf("%d",&i);
  getchar();
  if(i>k||i<=0)
  {
   cha.n = 2;
   return cha;
  }
  if((i==1&&cha.MP<(double)(cha.grd)*2.2)||(i==2&&cha.MP<(double)(cha.grd)*2.2)||
	  (i==4&&cha.MP<(double)(cha.atc)*1.3)||(i==5&&cha.MP<(double)(cha.grd)*2.2)||
	  (i==6&&cha.MP<(double)(cha.atc)*0.75))
  {
   return cha;
  }
  cha.n++;
  if(i==1)
  {
   if(cha.q==-1)
   {
    cha.n = 2;
	printf("�������ٻ�������\n");
	printf("ȷ��");
	getchar();
	return cha;
   }
   if(cha.q==-2)
   {
    cha.n = 2;
	printf("������һ��ս����ֻ���ٻ�һ��\n");
	printf("ȷ��");
	getchar();
	return cha;
   }
   cha.MP -= (double)(cha.grd)*2.2;
   cha.h = 1.0;
   cha.q = -1;
  }
  if(i==2)
  {
   cha.MP -= (double)(cha.grd)*2.2;
   cha.h = 1.0;
   cha.q = 1;
  }
  if(i==3)
  {
   cha.h = 1.0;
   cha.q = 3;
  }
  if(i==4)
  {
   cha.MP -= (double)(cha.atc)*1.3;
   cha.h = 1.0;
   cha.q = 4;
  }
  if(i==5)
  {
   if(cha.q!=-1)
   {
    cha.n = 2;
	printf("������\n");
	printf("ȷ��");
	getchar();
	return cha;
   }
   if(cha.k==1.301)
   {
    cha.n = 2;
	printf("�����ظ�����\n");
	printf("ȷ��");
	getchar();
	return cha;
   }
   cha.MP -= (double)(cha.grd)*2.2;
   printf("�ѿ���\n");
   cha.k = 1.3;
  }
  if(i==6)
  {
   if(cha.q!=-1)
   {
    cha.n = 2;
	printf("������\n");
	printf("ȷ��");
	getchar();
	return cha;
   }
   cha.MP -= (double)(cha.atc)*0.75;
   cha.h = 1.0;
   cha.q = 6;
  }
 }
 return cha;
}

struct CHARACTER Battle(struct CHARACTER cha, struct MONSTER mon[])
{
    int i=0,t,m,n,j,k,x;
	int y = 0;
	int g = 0,l=0;
	int wait = 0;
	double h;
	cha.k = 1;
	double a,b,c,d,e;
	char filename[100];
	double HP[3]={-1.0,-1.0,-1.0};
	double MP[3]={-1.0,-1.0,-1.0};
	int turn[3]={1,0,0};
	double anim = -1.0;          //����Ѫ��
	int freq = 1;                //���޴�����
	double ani[3]={-1.0,-1.0,-1.0};
	double mol=0;
	cha.q = 1;
	double value[6];

	FILE* f;
	if(cha.trp!=0)
	{
	 cha.HP = cha.xHP;
	 cha.MP = cha.xMP;
	 strcpy(filename,storyfolder);
	 strcat(filename,cha.trpname);
	 strcat(filename,".ys");
	 if(cha.trp==1)
	 {
	  f = fopen(filename,"wb");    //92�ֽ�
	  fwrite(&turn[0],4,1,f);
	  fwrite(&turn[1],4,1,f);
	  fwrite(&turn[2],4,1,f);
      fwrite(&cha.HP,8,1,f);
	  fwrite(&cha.MP,8,1,f);
	  fwrite(&anim,8,1,f);
	  fwrite(&HP[1],8,1,f);
	  fwrite(&MP[1],8,1,f);
	  fwrite(&ani[1],8,1,f);
	  fwrite(&HP[2],8,1,f);
	  fwrite(&MP[2],8,1,f);
	  fwrite(&ani[2],8,1,f);
	  fwrite(&mon[0].HP,8,1,f);
	  fclose(f);
	 }
	 else
	 {
	  f = fopen(filename,"rb+");
	  fseek(f,12L+(cha.trp-1)*24L,0);
	  fwrite(&cha.HP,8,1,f);
	  fwrite(&cha.MP,8,1,f);
	  fclose(f);
	 }
	 printf("��ȴ������볡...\n");
	 while(i==0)
	 {
		 cha = Uptrp(cha);
		 f = fopen(filename,"rb");
		 fread(&turn[0],4,1,f);
		 fread(&turn[1],4,1,f);
		 fread(&turn[2],4,1,f);
		 fread(&HP[0],8,1,f);
		 fread(&MP[0],8,1,f);
		 fread(&ani[0],8,1,f);
		 fread(&HP[1],8,1,f);
		 fread(&MP[1],8,1,f);
		 fread(&ani[1],8,1,f);
		 if(strcmp(cha.buddy2,"\0")==0&&HP[1]==-1.0)
		 {
			 fclose(f);
			 i = 1;
		 }
		 if((strcmp(cha.buddy2,"\0")!=0&&HP[1]!=-1.0))
		 {
			 fread(&HP[2],8,1,f);
			 fread(&MP[2],8,1,f);
			 fread(&ani[2],8,1,f);
			 if((strcmp(cha.buddy3,"\0")!=0&&HP[2]!=-1.0))
			 {
				 fclose(f);
				 i = 1;
			 }
			 if((strcmp(cha.buddy3,"\0")==0&&HP[2]==-1.0))
			 {
				 fclose(f);
				 i = 1;
			 }
		 }
		 if(i==0)
		 {
			 fclose(f);
		 }
		 value[0] = HP[0];
		 value[1] = MP[0];
		 value[2] = HP[1];
		 value[3] = MP[1];
		 value[4] = HP[2];
		 value[5] = MP[2];
	 }
	}
	printf("��������\n");
	if(cha.trp==0)
	{
	 strcpy(cha.buddy1,cha.name);
     cha.buddy1[9] = '\0';
	}
	else
	{
	 cha.buddy1[9] = '\0';
	 cha.buddy2[9] = '\0';
	 cha.buddy3[9] = '\0';
	}
loop0:
	if(g==0)
	{
		printf("%9s",cha.buddy1);            //����
		printf("%9s",cha.buddy2);
		printf("%9s",cha.buddy3);
		printf("    ");
		
		i = 0;                               //����
		while(i<=cha.m-1)
		{
			printf("%9s",mon[i].name);
			i++;
		}
		printf("\n");
	}
    
	if(cha.trp==0)                       //������ֵ
	{
	 if(anim==-1.0)
	 {
	  printf("   %4.0lf",cha.HP);
	  printf("  ");
	 }
	 else
	 {
	  printf("%4.0lf %4.0lf",cha.HP,anim);
	 }
	 printf("         ");
	 printf("         ");
	}
	else
	{
	  if(HP[0]==-1)
	  {
	   printf("         ");
	  }
	  else
	  {
	   if(ani[0]==-1.0)
	   {
	    printf("   %4.0lf",HP[0]);
	    printf("  ");
	   }
	   else
	   {
	    printf("%4.0lf %4.0lf",HP[0],ani[0]);
	   }
	  }
	  if(HP[1]==-1)
	  {
	   printf("         ");
	  }
	  else
	  {
	   if(ani[1]==-1.0)
	   {
	    printf("   %4.0lf",HP[1]);
	    printf("  ");
	   }
	   else
	   {
	    printf("%4.0lf %4.0lf",HP[1],ani[1]);
	   }
	  }
	  if(HP[2]==-1)
	  {
	   printf("         ");
	  }
	  else
	  {
	   if(ani[2]==-1.0)
	   {
	    printf("   %4.0lf",HP[2]);
	    printf("  ");
	   }
	   else
	   {
	    printf("%4.0lf %4.0lf",HP[2],ani[2]);
	   }
	  }
	}
	printf("    ");
    
	i = 0;
	while(i<=cha.m-1)              //������ֵ
	{
	 printf("  %-4.0lf",mon[i].HP);
	 printf("   ");
	 i++;
	}
	printf("\n");
    
	if(strcmp(cha.buddy1,"\0")!=0)         //��
	{
	 if(g==0)
	 {
	  if(cha.trp==0)
	  {
		  if(anim==-1.0)
		  {
			  printf("     ��  ");
		  }
		  else
		  {
			  printf(" ��   �� ");
		  }
	  }
	  if(cha.trp!=0)
	  {
	      if(ani[0]==-1.0)
		  {
		      printf("     ��  ");
		  }
		  else
		  {
			  printf(" ��   �� ");
		  }
	  }
	 }
	 if(g==1)
	 {
	  if(cha.trp==0)
	  {
		  if(strcmp(cha.prof,"սʿ")==0&&cha.k!=1.3)
		  {
			  printf("         ");
		  }
		  if(strcmp(cha.prof,"սʿ")==0&&cha.k==1.3)
		  {
			  printf("     ��  ");
		  }
		  if(strcmp(cha.prof,"��ʦ")==0&&t==0)
		  {
			  printf("         ");
		  }
		  if(strcmp(cha.prof,"��ʦ")==0&&t==1)
		  {
			  printf("     ��  ");
		  }
		  if(strcmp(cha.prof,"��ʿ")==0&&t==0)
		  {
			  if(anim==-1.0)
			  {
			   printf("         ");
			  }
			  else
			  {
				  if(l==0)
				  {
					  printf("      �� ");
				  }
				  if(l==1)
				  {
					  printf(" ��      ");
				  }
			  }
		  }
		  if(strcmp(cha.prof,"��ʿ")==0&&t==1)
		  {
			  if(cha.q==1||cha.q==-1||cha.k==1.3||cha.q==6)
			  {
			   if(anim==-1.0)
			   {
			    printf("     ��  ");
			   }
			   else
			   {
			    if(l==0)
				{
				 printf(" ��   �� ");
				}
				if(l==1)
				{
				 printf(" ��      ");
				}
			   }
			  }
			  if(cha.q==4||cha.q==3)
			  {
			   if(anim==-1.0)
			   {
			    printf("+%4.0lf��  ",a);
			   }
			   else
			   {
			    if(l==0)
				{
				 printf("+��%4.0lf��",a);
				}
				if(l==1)
				{
				 printf(" ��      ");
				}
			   }
			  }
		  }
	  }
	  else
	  {
	   if(turn[0]==1)
	   {
	      if(strcmp(cha.prof,"սʿ")==0&&cha.k!=1.3)
		  {
			  printf("         ");
		  }
		  if(strcmp(cha.prof,"սʿ")==0&&cha.k==1.3)
		  {
			  printf("     ��  ");
		  }
		  if(strcmp(cha.prof,"��ʦ")==0&&t==0)
		  {
			  printf("         ");
		  }
		  if(strcmp(cha.prof,"��ʦ")==0&&t==1)
		  {
			  printf("     ��  ");
		  }
		  if(strcmp(cha.prof,"��ʿ")==0&&t==0)
		  {
		      if(ani[0]==-1.0)
			  {
			   printf("         ");
			  }
			  else
			  {
				  if(l==0)
				  {
					  printf("      �� ");
				  }
				  if(l==1)
				  {
					  printf(" ��      ");
				  }
			  }
		  }
		  if(strcmp(cha.prof,"��ʿ")==0&&t==1)
		  {
			  if(cha.q==1||cha.q==-1||cha.k==1.3||cha.q==6)
			  {
			   if(ani[0]==-1.0)
			   {
			    printf("     ��  ");
			   }
			   else
			   {
			    if(l==0)
				{
				 printf(" ��   �� ");
				}
				if(l==1)
				{
				 printf(" ��      ");
				}
			   }
			  }
			  if(cha.q==4||cha.q==3)
			  {
			   if(ani[0]==-1.0)
			   {
			    printf("+%4.0lf��  ",a);
			   }
			   else
			   {
			    if(l==0)
				{
				 printf("+��%4.0lf��",a);
				}
				if(l==1)
				{
				 printf(" ��      ");
				}
			   }
			  }
		  }
	   }
	   else
	   {
	      if(ani[0]==-1.0)
		  {
		      printf("     ��  ");
		  }
		  else
		  {
			  printf(" ��   �� ");
		  }
	   }
	  }
	 }
	 if(g==2)
	 {
	  if(cha.trp==0)
	  {
		  if(strcmp(cha.prof,"��ʦ")==0&&t==1)
		  {
			  printf("     ��  ");
		  }
		  else
		  {
			  if(anim==-1.0)
			  {
			   if(strcmp(cha.prof,"��ʿ")==0&&t!=0&&cha.q!=3&&cha.q!=4&&cha.k!=1.3&&cha.q!=6)
			   {
			    printf("     ��  ");
			   }
			   else
			   {
			    printf("-%-4.0lf�˹�",a);
			   }
			  }
			  if(anim!=-1.0)
			  {
			   printf("-%-4.0lf�޹�",a);
			  }
		  }
	  }
	  else
	  {
	      if(turn[0]==1)
		  {
			  if(strcmp(cha.prof,"��ʦ")==0&&t==1)
			  {
			      printf("     ��  ");
			  }
			  else
			  {
				  if(ani[0]==-1.0)
				  {
					  if(strcmp(cha.prof,"��ʿ")==0&&t!=0&&cha.q!=3&&cha.q!=4&&cha.k!=1.3&&cha.q!=6)
					  {
						  printf("     ��  ");
					  }
					  else
					  {
						  printf("-%-4.0lf�˹�",a);
					  }
				  }
				  if(ani[0]!=-1.0)
				  {
					  printf("-%-4.0lf�޹�",a);
				  }
			  }
		  }
		  else
		  {
			  if(ani[0]==-1.0)
			  {
				  printf("     ��  ");
			  }
			  else
			  {
				  printf(" ��   �� ");
			  }
		  }
	  }
	 }
	}

	if(strcmp(cha.buddy2,"\0")!=0)
	{
	 if(g==0)
	 {
		 if(ani[1]==-1.0)
		 {
			 printf("     ��  ");
		 }
		 else
		 {
			 printf(" ��   �� ");
		 }
	 }
	 if(g==1)
	 {
	  if(turn[1]==1)
	  {
		  if(strcmp(cha.prof,"սʿ")==0&&cha.k!=1.3)
		  {
			  printf("         ");
		  }
		  if(strcmp(cha.prof,"սʿ")==0&&cha.k==1.3)
		  {
			  printf("     ��  ");
		  }
		  if(strcmp(cha.prof,"��ʦ")==0&&t==0)
		  {
			  printf("         ");
		  }
		  if(strcmp(cha.prof,"��ʦ")==0&&t==1)
		  {
			  printf("     ��  ");
		  }
		  if(strcmp(cha.prof,"��ʿ")==0&&t==0)
		  {
		      if(ani[1]==-1.0)
			  {
			   printf("         ");
			  }
			  else
			  {
				  if(l==0)
				  {
					  printf("      �� ");
				  }
				  if(l==1)
				  {
					  printf(" ��      ");
				  }
			  }
		  }
		  if(strcmp(cha.prof,"��ʿ")==0&&t==1)
		  {
			  if(cha.q==1||cha.q==-1||cha.k==1.3||cha.q==6)
			  {
			   if(ani[1]==-1.0)
			   {
			    printf("     ��  ");
			   }
			   else
			   {
			    if(l==0)
				{
				 printf(" ��   �� ");
				}
				if(l==1)
				{
				 printf(" ��      ");
				}
			   }
			  }
			  if(cha.q==4||cha.q==3)
			  {
			   if(ani[1]==-1.0)
			   {
			    printf("+%4.0lf��  ",a);
			   }
			   else
			   {
			    if(l==0)
				{
				 printf("+��%4.0lf��",a);
				}
				if(l==1)
				{
				 printf(" ��      ");
				}
			   }
			  }
		  }
	  }
	  else
	  {
		  if(ani[1]==-1.0)
		  {
			  printf("     ��  ");
		  }
		  else
		  {
			  printf(" ��   �� ");
		  }
	  }
	 }
	 if(g==2)
	 {
		 if(turn[1]==1)
		  {
			  if(strcmp(cha.prof,"��ʦ")==0&&t==1)
			  {
			      printf("     ��  ");
			  }
			  else
			  {
				  if(ani[1]==-1.0)
				  {
					  if(strcmp(cha.prof,"��ʿ")==0&&t!=0&&cha.q!=3&&cha.q!=4&&cha.k!=1.3&&cha.q!=6)
					  {
						  printf("     ��  ");
					  }
					  else
					  {
						  printf("-%-4.0lf�˹�",a);
					  }
				  }
				  if(ani[1]!=-1.0)
				  {
					  printf("-%-4.0lf�޹�",a);
				  }
			  }
		  }
		  else
		  {
			  if(ani[1]==-1.0)
			  {
				  printf("     ��  ");
			  }
			  else
			  {
				  printf(" ��   �� ");
			  }
		  }
	 }
	}
	else
	{
	 printf("         ");
	}

	if(strcmp(cha.buddy3,"\0")!=0)
	{
	 if(g==0)
	 {
		 if(ani[2]==-1.0)
		 {
			 printf("     ��  ");
		 }
		 else
		 {
			 printf(" ��   �� ");
		 }
	 }
	 if(g==1)
	 {
	  if(turn[2]==1)
	  {
		  if(strcmp(cha.prof,"սʿ")==0&&cha.k!=1.3)
		  {
			  printf("         ");
		  }
		  if(strcmp(cha.prof,"սʿ")==0&&cha.k==1.3)
		  {
			  printf("     ��  ");
		  }
		  if(strcmp(cha.prof,"��ʦ")==0&&t==0)
		  {
			  printf("         ");
		  }
		  if(strcmp(cha.prof,"��ʦ")==0&&t==1)
		  {
			  printf("     ��  ");
		  }
		  if(strcmp(cha.prof,"��ʿ")==0&&t==0)
		  {
		      if(ani[2]==-1.0)
			  {
			   printf("         ");
			  }
			  else
			  {
				  if(l==0)
				  {
					  printf("      �� ");
				  }
				  if(l==1)
				  {
					  printf(" ��      ");
				  }
			  }
		  }
		  if(strcmp(cha.prof,"��ʿ")==0&&t==1)
		  {
			  if(cha.q==1||cha.q==-1||cha.k==1.3||cha.q==6)
			  {
			   if(ani[2]==-1.0)
			   {
			    printf("     ��  ");
			   }
			   else
			   {
			    if(l==0)
				{
				 printf(" ��   �� ");
				}
				if(l==1)
				{
				 printf(" ��      ");
				}
			   }
			  }
			  if(cha.q==4||cha.q==3)
			  {
			   if(ani[2]==-1.0)
			   {
			    printf("+%4.0lf��  ",a);
			   }
			   else
			   {
			    if(l==0)
				{
				 printf("+��%4.0lf��",a);
				}
				if(l==1)
				{
				 printf(" ��      ");
				}
			   }
			  }
		  }
	  }
	  else
	  {
		  if(ani[2]==-1.0)
		  {
			  printf("     ��  ");
		  }
		  else
		  {
			  printf(" ��   �� ");
		  }
	  }
	 }
	 if(g==2)
	 {
		 if(turn[2]==1)
		  {
			  if(strcmp(cha.prof,"��ʦ")==0&&t==1)
			  {
			      printf("     ��  ");
			  }
			  else
			  {
				  if(ani[2]==-1.0)
				  {
					  if(strcmp(cha.prof,"��ʿ")==0&&t!=0&&cha.q!=3&&cha.q!=4&&cha.k!=1.3&&cha.q!=6)
					  {
						  printf("     ��  ");
					  }
					  else
					  {
						  printf("-%-4.0lf�˹�",a);
					  }
				  }
				  if(ani[2]!=-1.0)
				  {
					  printf("-%-4.0lf�޹�",a);
				  }
			  }
		  }
		  else
		  {
			  if(ani[2]==-1.0)
			  {
				  printf("     ��  ");
			  }
			  else
			  {
				  printf(" ��   �� ");
			  }
		  }
	 }
	}
	else
	{
	 printf("         ");
	}
	printf("    ");

	i = 0;                            //��
	while(i<=cha.m-1)
	{
	 if(g==1)
	 {
	     if(strcmp(cha.prof,"սʿ")==0&&cha.k!=1.3)
		 {
		     if(i==j-1)
			 {
			  printf("��");
			 }
			 else
			 {
			  printf("  ");
			 }
		 }
		 if(strcmp(cha.prof,"սʿ")==0&&cha.k==1.3)
		 {
		     printf("  ");
		 }
		 if(strcmp(cha.prof,"��ʦ")==0&&t==0)
		 {
		     if(i==j-1)
			 {
			  printf("��");
			 }
			 else
			 {
			  printf("  ");
			 }
		 }
		 if(strcmp(cha.prof,"��ʦ")==0&&t==1)
		 {
			 if(h==1.5&&i==j-1)
			 {
			  printf("-*");
			 }
			 if(h==1.8&&i==j-1)
			 {
			  printf("--");
			 }
			 if(h==1.6&&cha.q==2&&i==j-1)
			 {
			  printf("**");
			 }
			 if((h==1.6&&cha.q==3)||h==1.7||i!=j-1||cha.k==1.5||cha.q==5)
			 {
			  printf("  ");
			 }
		 }
		 if(strcmp(cha.prof,"��ʿ")==0&&t==0)
		 {
			 if(anim==-1.0)
			 {
				 if(i==j-1)
				 {
					 printf("��");
				 }
				 else
				 {
					 printf("  ");
				 }
			 }
			 if(anim!=-1.0)
			 {
				 if(i==0&&l==1)
				 {
				     printf("��");
				 }
				 if(i==j-1&&l==0)
				 {
					 printf("��");
				 }
				 if((i!=0&&l==1)||(i!=j-1&&l==0))
				 {
					 printf("  ");
				 }
			 }
		 }
		 if(strcmp(cha.prof,"��ʿ")==0&&t==1)
		 {
			 if(anim==-1.0)
			 {
				 if(i==j-1)
				 {
				  printf("==");
				 }
				 else
				 {
				  printf("  ");
				 }
			 }
			 if(anim!=-1.0)
			 {
				 if(i==0&&l==1)
				 {
				     printf("��");
				 }
				 if(i==j-1&&l==0)
				 {
				     printf("==");
				 }
				 if((i!=0&&l==1)||(i!=j-1&&l==0))
				 {
					 printf("  ");
				 }
			 }
		 }
	 }
	 if(g==0||g==2)
	 {
	  printf("  ");
	 }
	 if(i!=k)
	 {
	  printf("��");
	 }
	 if(i==k)      //�ֵ���k����ʱ
	 {
	   if((strcmp(cha.prof,"��ʦ")==0&&t==1)||(strcmp(cha.prof,"��ʿ")==0&&t==1&&anim==-1.0&&cha.q!=3&&cha.q!=4&&cha.k!=1.3&&cha.q!=6))
	   {
	    printf("��");
		k = cha.m-1;
	   }
	   else
	   {
	    printf("  ");
	   }
	 }
	 if(g==1)
	 {
		 if(strcmp(cha.prof,"սʿ")==0&&cha.k!=1.3)
		 {
			 if(i==j-2)
			 {
				 if(cha.q==2)
				 {
					 if(cha.m>1&&cha.m==j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
				 }
			 }
			 if(i==j-1)
			 {
				 printf("-%4.0lf",a);
				 i++;
				 continue;
			 }
			 if(i==j)
			 {
				 if(cha.q==2)
				 {
					 if(cha.m>1&&cha.m!=j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
				 }
			 }
		 }
		 if(strcmp(cha.prof,"��ʦ")==0)
		 {
			 if(cha.m==5&&cha.q==5)
			 {
				 if(i==0)
				 {
					 printf("-%4.0lf",a);
					 i++;
					 continue;
				 }
				 if(i==1)
				 {
					 printf("-%4.0lf",b);
					 i++;
					 continue;
				 }
				 if(i==2)
				 {
					 printf("-%4.0lf",c);
					 i++;
					 continue;
				 }if(i==3)
				 {
					 printf("-%4.0lf",d);
					 i++;
					 continue;
				 }
				 if(i==4)
				 {
					 printf("-%4.0lf",e);
					 i++;
					 continue;
				 }
			 }
			 if(i==j-4)
			 {
				 if(cha.q==5)
				 {
					 if(cha.m==4&&cha.m==j)
					 {
						 printf("-%4.0lf",d);
						 i++;
						 continue;
					 }
				 }
			 }
			 if(i==j-3)
			 {
				 if(cha.q==3)
				 {
					 if(cha.m>=3&&cha.m==j)
					 {
						 printf("-%4.0lf",c);
						 i++;
						 continue;
					 }
				 }
				 if(cha.q==5)
				 {
					 if(cha.m==3&&cha.m==j)
					 {
						 printf("-%4.0lf",c);
						 i++;
						 continue;
					 }
					 if(cha.m==4&&cha.m==j)
					 {
						 printf("-%4.0lf",c);
						 i++;
						 continue;
					 }
					 if(cha.m==4&&cha.m-1==j)
					 {
						 printf("-%4.0lf",d);
						 i++;
						 continue;
					 }
				 }
			 }
			 if(i==j-2)
			 {
				 if(cha.q==2)
				 {
					 if(cha.m>=2&&cha.m==j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
				 }
				 if(cha.q==3)
				 {
					 if(cha.m==2)
					 {
						 if(cha.m==j)
						 {
							 printf("-%4.0lf",b);
							 i++;
							 continue;
						 }
					 }
					 if(cha.m>=3&&cha.m==j+1)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
					 if(cha.m>=3&&cha.m==j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
				 }
				 if(cha.q==5)
				 {
					 if(cha.m==2&&cha.m==j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
					 if(cha.m==3&&cha.m==j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
					 if(cha.m==3&&cha.m-1==j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
					 if(cha.m==4&&cha.m==j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
					 if(cha.m==4&&cha.m-1==j)
					 {
						 printf("-%4.0lf",c);
						 i++;
						 continue;
					 }
					 if(cha.m==3&&cha.m-2==j)
					 {
						 printf("-%4.0lf",d);
						 i++;
						 continue;
					 }
				 }
			 }
			 if(i==j-1)
			 {
				 printf("-%4.0lf",a);
				 i++;
				 continue;
			 }
			 if(i==j)
			 {
				 if(cha.q==2)
				 {
					 if(cha.m>=2&&cha.m!=j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
				 }
				 if(cha.q==3)
				 {
					 if(cha.m==2)
					 {
						 if(cha.m!=j)
						 {
							 printf("-%4.0lf",b);
							 i++;
							 continue;
						 }
					 }
					 if(cha.m>=3&&cha.m-1==j)
					 {
						 printf("-%4.0lf",c);
						 i++;
						 continue;
					 }
					 if(cha.m>=3&&cha.m!=j&&cha.m!=j+1)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
				 }
				 if(cha.q==5)
				 {
					 if(cha.m==2&&cha.m!=j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
					 if(cha.m==3&&cha.m-1==j)
					 {
						 printf("-%4.0lf",c);
						 i++;
						 continue;
					 }
					 if(cha.m==3&&cha.m!=j&&cha.m!=j+1)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
					 if(cha.m==4&&cha.m-1==j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
					 if(cha.m==4&&cha.m-2==j)
					 {
						 printf("-%4.0lf",c);
						 i++;
						 continue;
					 }
					 if(cha.m==4&&cha.m-3==j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
				 }
			 }
			 if(i==j+1)
			 {
				 if(cha.q==3)
				 {
					 if(cha.m>=3&&cha.m!=j&&cha.m!=j+1)
					 {
						 printf("-%4.0lf",c);
						 i++;
						 continue;
					 }
				 }
				 if(cha.q==5)
				 {
					 if(cha.m==3&&cha.m!=j&&cha.m!=j+1)
					 {
						 printf("-%4.0lf",c);
						 i++;
						 continue;
					 }
					 if(cha.m==4&&cha.m-2==j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
					 if(cha.m==4&&cha.m-3==j)
					 {
						 printf("-%4.0lf",c);
						 i++;
						 continue;
					 }
				 }
			 }
			 if(i==j+2)
			 {
				 if(cha.q==5)
				 {
					 if(cha.m==4&&cha.m-3==j)
					 {
						 printf("-%4.0lf",d);
						 i++;
						 continue;
					 }
				 }
			 }
		 }
		 if(strcmp(cha.prof,"��ʿ")==0)
		 {
			 if(i==0&&anim!=-1.0&&l!=0)
			 {
			  printf("-%4.0lf",b);
			  i++;
			  continue;
			 }
			 if(i==j-1)
			 {
				 if(cha.q==1||t==0)
				 {
				  printf("-%4.0lf",a);
				  i++;
				  continue;
				 }
			 }
		 }
	 }
	 printf("     ");
	 i++;
	}
	k++;
	printf("\n");

	struct MONSTER mo;          //���ֵ�����ֵ
	i = 0;
    while(i<=cha.m-1)
	{
	 if(mon[i].HP==0)
	 {
	  strcpy(mon[i].name,"\0");
	  j=i;
	  while(j<=cha.m-2)
	  {
	   mo = mon[j];
	   mon[j] = mon[j+1];
	   mon[j+1] = mo;
	   j++;
	  }
	  cha.m--;
	  if(i==0&&cha.m==0)
	  {
	   if(cha.trp!=0)
	   {
		   i=0;
		   while(turn[i]!=1)
		   {
			   i++;
		   }
		   turn[i] = 0;
		   i++;
		   if(i==1&&strcmp(cha.buddy2,"\0")==0)
		   {
			   i = 0;
		   }
		   if(i==2&&strcmp(cha.buddy3,"\0")==0)
		   {
			   i = 0;
		   }
		   if(i==3)
		   {
			   i = 0;
		   }
		   turn[i] = 1;
		   f = fopen(filename,"wb");
		   fwrite(&turn[0],4,1,f);
		   fwrite(&turn[1],4,1,f);
		   fwrite(&turn[2],4,1,f);
		   fwrite(&HP[0],8,1,f);
		   fwrite(&MP[0],8,1,f);
		   fwrite(&ani[0],8,1,f);
		   fwrite(&HP[1],8,1,f);
		   fwrite(&MP[1],8,1,f);
		   fwrite(&ani[1],8,1,f);
		   fwrite(&HP[2],8,1,f);
		   fwrite(&MP[2],8,1,f);
		   fwrite(&ani[2],8,1,f);
		   fwrite(&mon[0].HP,8,1,f);
		   fclose(f);
		   printf("�������\n");
		   printf("ȷ��");
		   getchar();
		   if(cha.trp==1)
		   {
		    unlink(filename);
		   }
		   cha.HP = cha.xHP;
		   cha.MP = cha.xMP;
	   }
	   return cha;
	  }
	 }
	 else
	 {
	  i++;
	 }
	}
    
	if(cha.trp==0)           //����˵�����ֵ
	{
		if(cha.HP==0)
		{
			printf("��������\n");
			cha.mny -= (double)(cha.grd*10);
			if(cha.mny<0)
			{
				cha.mny = 0.0;
			}
			printf("��ʧ%.0lf���\n",(double)(cha.grd*10));
			printf("ȷ��");
			getchar();
			printf("\n");
			cha.HP = 1;
			cha.m = -1;
			cha.n = -1;
			return cha;
		}
		if(anim==0.0)
		{
	     anim = -1.0;
		 freq--;
		}
	}
	else
	{
		if(anim==0.0)
		{
			anim = -1.0;
			if(cha.trp!=0)
			{
				ani[cha.trp-1] = anim;
			}
			freq--;
		}
		i = 0;
		if(strcmp(cha.buddy2,"\0")==0&&HP[0]==0.0)
		{
			i = 1;
		}
		if((strcmp(cha.buddy2,"\0")!=0&&HP[1]==0.0)&&HP[0]==0.0)
		{
			if((strcmp(cha.buddy3,"\0")!=0&&HP[2]==0.0)||(strcmp(cha.buddy3,"\0")==0))
			{
				i = 1;
			}
		}
		if(i==1)
		{
			i=0;
			while(turn[i]!=1)
			{
				i++;
			}
			turn[i] = 0;
			i++;
			if(i==1&&strcmp(cha.buddy2,"\0")==0)
			{
				i = 0;
			}
			if(i==2&&strcmp(cha.buddy3,"\0")==0)
			{
				i = 0;
			}
			if(i==3)
			{
				i = 0;
			}
			turn[i] = 1;
			f = fopen(filename,"wb");
			fwrite(&turn[0],4,1,f);
			fwrite(&turn[1],4,1,f);
			fwrite(&turn[2],4,1,f);
			fwrite(&HP[0],8,1,f);
			fwrite(&MP[0],8,1,f);
			fwrite(&ani[0],8,1,f);
			fwrite(&HP[1],8,1,f);
			fwrite(&MP[1],8,1,f);
			fwrite(&ani[1],8,1,f);
			fwrite(&HP[2],8,1,f);
			fwrite(&MP[2],8,1,f);
			fwrite(&ani[2],8,1,f);
			fwrite(&mon[0].HP,8,1,f);
			fclose(f);
			printf("ȫ������\n");
			cha.mny -= (double)(cha.grd*10);
			if(cha.mny<0)
			{
				cha.mny = 0.0;
			}
			printf("��ʧ%.0lf���\n",(double)(cha.grd*10));
			printf("ȷ��");
			getchar();
			printf("\n");
			cha.HP = 1;
			cha.m = -1;
			cha.n = -1;
			if(cha.trp==1)
			{
				unlink(filename);
			}
			return cha;
		}
	}

	if(strcmp(cha.prof,"��ʿ")==0)
	{
	 if(anim!=-1.0)
	 {
	  if(l==0)
	  {
		  l = 1;
		  b = cha.atc*1.3 - mon[0].def;
		  n = -10 + rand()%21;
		  b += n/10.0*b/3.0;
		  b = (double)((int)(b*cha.k));
		  if(b<1)
		  {
			  b = 1;
		  }
		  mon[0].HP -= b;
		  if(mon[0].HP<0)
		  {
			  b = mon[0].HP + b;
			  mon[0].HP = 0;
		  }
		  printf("\n");
		  goto loop0;
	  }
	 }
	}
    
    if(g==1)                 //������ʾ
	{
	 g = 2;
	 k = 0;
	 if(strcmp(cha.prof,"��ʦ")==0 && t==1 && (cha.q==3 || cha.q==5))
	 {
	   printf("         ");
	   printf("         ");
	   printf("         ");
	   printf("    ");
	   i = 0;
	   while(i<=cha.m-1)
	   {
		x = 0;
		printf("  ");
		if(cha.q==5)
		{
		 printf("-- - - - -- - - - -- - - - -- - - - --");
		 i = cha.m;
		 continue;
		}
		if(i==j-3)
		{
		  if(cha.m>=3&&cha.m==j)
		  {
			if(h==1.6)
			{
			 printf("**");
			 x = 1;
			}
			if(h==1.7)
			{
			 printf("&&");
			 x = 1;
			}
		  }
		}
		if(i==j-2)
		{
		  if(cha.m==2)
		  {
		   if(cha.m==j)
		   {
		    if(h==1.6)
			{
			 printf("**");
			 x = 1;
			}
			if(h==1.7)
			{
			 printf("&&");
			 x = 1;
			}
		   }
		  }
		  if(cha.m>=3&&cha.m==j+1)
		  {
		   if(h==1.6)
			{
			 printf("**");
			 x = 1;
			}
			if(h==1.7)
			{
			 printf("&&");
			 x = 1;
			}
		  }
		  if(cha.m>=3&&cha.m==j)
		  {
		    if(h==1.6)
			{
			 printf("**");
			 x = 1;
			}
			if(h==1.7)
			{
			 printf("&&");
			 x = 1;
			}
		  }
		}
		if(i==j-1)
		{
			if(h==1.6)
			{
				printf("**");
				x = 1;
			}
			if(h==1.7)
			{
				printf("&&");
				x = 1;
			}
		}
		if(i==j)
		{
		  if(cha.m==2)
		  {
		   if(cha.m!=j)
		   {
		    if(h==1.6)
			{
				printf("**");
				x = 1;
			}
			if(h==1.7)
			{
				printf("&&");
				x = 1;
			}
		   }
		  }
		  if(cha.m>=3&&cha.m-1==j)
		  {
		    if(h==1.6)
			{
				printf("**");
				x = 1;
			}
			if(h==1.7)
			{
				printf("&&");
				x = 1;
			}
		  }
		  if(cha.m>=3&&cha.m!=j&&cha.m!=j+1)
		  {
		    if(h==1.6)
			{
				printf("**");
				x = 1;
			}
			if(h==1.7)
			{
				printf("&&");
				x = 1;
			}
		  }
		}
		if(i==j+1)
		{
		  if(cha.m>=3&&cha.m!=j&&cha.m!=j+1)
		  {
		    if(h==1.6)
			{
				printf("**");
				x = 1;
			}
			if(h==1.7)
			{
				printf("&&");
				x = 1;
			}
		  }
		}
		if(x!=1)
		{
		 printf("  ");
		}
		printf("     ");
	    i++;
	   }
	 }
	}

	if(g==2)
	{
	 printf("\n");
	 if(k==cha.m)
	 {
	  g = 0;
loop1:
	  i = 0;
	  if(cha.trp!=0)
	  {
	   while(turn[i]!=1)
	   {
		i++;
	   }
	   turn[i] = 0;
	   i++;
	   if(i==1&&strcmp(cha.buddy2,"\0")==0)
	   {
	     i = 0;
	   }
	   if(i==2&&strcmp(cha.buddy3,"\0")==0)
	   {
		 i = 0;
	   }
	   if(i==3)
	   {
	    i = 0;
	   }
	   turn[i] = 1;
	   f = fopen(filename,"wb");
	   fwrite(&turn[0],4,1,f);
       fwrite(&turn[1],4,1,f);
	   fwrite(&turn[2],4,1,f);
	   fwrite(&HP[0],8,1,f);
	   fwrite(&MP[0],8,1,f);
	   fwrite(&ani[0],8,1,f);
	   fwrite(&HP[1],8,1,f);
	   fwrite(&MP[1],8,1,f);
	   fwrite(&ani[1],8,1,f);
	   fwrite(&HP[2],8,1,f);
	   fwrite(&MP[2],8,1,f);
	   fwrite(&ani[2],8,1,f);
	   fwrite(&mon[0].HP,8,1,f);
	   fclose(f);
	  }
	  goto loop0;
	 }
	 if(strcmp(cha.prof,"սʿ")==0||(strcmp(cha.prof,"��ʦ")==0&&t==0)||
		 (strcmp(cha.prof,"��ʿ")==0&&(t==0||cha.q==3||cha.q==4||cha.k==1.3||cha.q==6)&&anim==-1.0)||(anim!=-1.0&&anim!=0.0))
	 {         //�ֶ��˵��˺�
		 a = mon[k].atc - cha.def;
		 n = -10 + rand()%21;
		 a += n/10.0*a/3.0;
		 a = (double)((int)(a));
		 if(a<1)
		 {
			 a = 1;
		 }
		 if(anim!=-1.0)
		 {
		  if(mol==0)
		  {
			  anim -= a;
			  if(anim<0)
			  {
				  a = anim + a;
				  anim = 0.0;
				  cha.q = 0;
			  }
		  }
		  if(mol!=0)
		  {
			  mol -= a;
			  if(mol<0)
			  {
				  a = mol + a;
				  mol = 0;
			  }
		  }
		 }
		 else
		 {
		  cha.HP -= a;
		  if(cha.HP<0)
		  {
			 a = cha.HP + a;
			 cha.HP = 0;
		  }
		 }
		 if(cha.trp!=0)
		 {
		  HP[cha.trp-1] = cha.HP;
		  ani[cha.trp-1] = anim;
		 }
	 }
	 goto loop0;
	}

	if(cha.trp==0)           //��
	{
	 if(mol==0)
	 {
	  printf("   %4.0lf",cha.MP);
	  printf("  ");
	 }
	 else
	 {
		 printf("%4.0lf",cha.MP);
		 printf(" ");
	     printf("%4.0lf",mol);
	 }
	 printf("         ");
	 printf("         ");
	}
	else
	{
	 if(MP[0]!=-1.0)
	 {
	  if(cha.trp==1)
	  {
		  if(mol==0)
		  {
			  printf("   %4.0lf",cha.MP);
			  printf("  ");
		  }
		  else
		  {
			  printf("%4.0lf",cha.MP);
			  printf(" ");
			  printf("%4.0lf",mol);
		  }
	  }
	  else
	  {
	      printf("   %4.0lf",MP[0]);
	      printf("  ");
	  }
	 }
	 else
	 {
	  printf("         ");
	 }
	 if(MP[1]!=-1.0)
	 {
	  if(cha.trp==2)
	  {
		  if(mol==0)
		  {
			  printf("   %4.0lf",cha.MP);
			  printf("  ");
		  }
		  else
		  {
			  printf("%4.0lf",cha.MP);
			  printf(" ");
			  printf("%4.0lf",mol);
		  }
	  }
	  else
	  {
	      printf("   %4.0lf",MP[0]);
	      printf("  ");
	  }
	 }
	 else
	 {
	  printf("         ");
	 }
	 if(MP[2]!=-1.0)
	 {
	  if(cha.trp==3)
	  {
		  if(mol==0)
		  {
			  printf("   %4.0lf",cha.MP);
			  printf("  ");
		  }
		  else
		  {
			  printf("%4.0lf",cha.MP);
			  printf(" ");
			  printf("%4.0lf",mol);
		  }
	  }
	  else
	  {
	      printf("   %4.0lf",MP[0]);
	      printf("  ");
	  }
	 }
	 else
	 {
	  printf("         ");
	 }
	 printf("   ");
	}
	printf("    ");

	for(i=0;i<=cha.m-1;i++)        //�ֵı��
	{
	 printf("   %d     ",i+1);
	}
	printf("\n");

	if(wait==0)
	{
	if(cha.trp!=0)
	{
		printf("��ȴ�...\n");
		i = 0;
		while(i==0)
		{
			f = fopen(filename,"rb");
			fread(&turn[0],4,1,f);
			fread(&turn[1],4,1,f);
			fread(&turn[2],4,1,f);
			fread(&HP[0],8,1,f);
			fread(&MP[0],8,1,f);
			fread(&ani[0],8,1,f);
			fread(&HP[1],8,1,f);
			fread(&MP[1],8,1,f);
			fread(&ani[1],8,1,f);
			fread(&HP[2],8,1,f);
			fread(&MP[2],8,1,f);
			fread(&ani[2],8,1,f);
			fread(&mon[0].HP,8,1,f);
			fclose(f);
			if(turn[cha.trp-1]==1)
			{
				i = 1;
				
				if(HP[cha.trp-1]!=0&&mon[0].HP!=0)
				{
				 wait = 1;
				 cha.HP = HP[cha.trp-1];
				 cha.MP = MP[cha.trp-1];
				 anim = ani[cha.trp-1];
				 goto loop0;
				}
			}
		}
		if(HP[cha.trp-1]==0.0||mon[0].HP==0.0)
		{
			goto loop1;
		}
	}
	}
	wait = 0;
	if(strcmp(cha.prof,"սʿ")==0)
	{
		if(cha.k==1.3)
		{
			cha.k = 1.301;
		}
	}
	if(strcmp(cha.prof,"��ʦ")==0)
	{
		if(cha.k==1.5)
		{
			cha.k = 1.501;
		}
	}
	if(strcmp(cha.prof,"��ʿ")==0)
	{
		if(cha.k==1.3)
		{
			cha.k = 1.301;
		}
	}
loop2:
	printf("\n  0.����  1.����   2.��Ʒ  3.����\n");
	printf("��ѡ��");
	scanf("%d", &t);
	getchar();
	if(t==0)
	{
     h = 1.0;
	 printf("��ѡ�����");
	 scanf("%d",&j);
	 getchar();
	 if(j>cha.m||j<1)
	 {
	  j = 1;
	 }
	}
	if(t==1)
	{
	 if(strcmp(cha.prof,"��ʿ")==0)
	 {
		 if(cha.trp==0)
		 {
			 if(anim!=-1.0)
			 {
				 cha.q = -1;
			 }
		 }
		 else
		 {
			 if(ani[cha.trp-1]!=-1.0)
			 {
				 cha.q = -1;
			 }
		 }
		 if(freq==0)
		 {
			 cha.q = -2;
		 }
	 }
	 cha = Skill(cha);
	 n = cha.n;
	 h = cha.h;
	 if(n==2)
	 {
	  goto loop0;
	 }
	 if(n==0)
	 {
	  printf("MP����\n");
	  printf("ȷ��");
	  getchar();
	  goto loop0;
	 }
	 if(cha.trp!=0)
	 {
	  MP[cha.trp-1] = cha.MP;
	 }
	 if((strcmp(cha.prof,"սʿ")==0&&cha.k!=1.3)||(strcmp(cha.prof,"��ʿ")==0&&cha.q==1)||
		 (strcmp(cha.prof,"��ʦ")==0&&cha.k!=1.5))
	 {
	  printf("��ѡ�����");
	  scanf("%d",&j);
	  getchar();
	  if(j>cha.m||j<1)
	  {
	   j = 1;
	  }
	 }
	 else
	 {
	  j = 0;
	 }
	}
	if(t==2)
	{
	 if(cha.trp!=0)
	 {
	  printf("����ʹ����Ʒ\n");
	  goto loop2;
	 }
	 m = cha.m;
	 cha = SeeGoods(cha);
	 cha.m = m;
	 goto loop0;
	}
	if(t==3)
	{
	 if(cha.trp!=0)
	 {
	  printf("�޷�����\n");
	  goto loop2;
	 }
	 printf("\n");
	 cha.m = -1;
	 return cha;
	}
	if(t!=1&&t!=2&&t!=3&&t!=0)
	{
	  goto loop0;
	}
    
	if(t==0||t==1)                   //�˶Թֵ��˺�
	{
	 g = 1;
	 l = 0;
     if(strcmp(cha.prof,"սʿ")==0)
	 {
	  if(cha.k==1.3)
	  {
	   goto loop0;
	  }
	  a = cha.atc - mon[j-1].def;     //a�ǶԵ�1��������˺�
	  n = -10 + rand()%21;
	  a += n/10.0*a/3.0;
	  a = (double)((int)(a*h*cha.k));
	  if(a<1)
	  {
		  a = 1;
	  }
	  mon[j-1].HP -= a;
	  if(mon[j-1].HP<0)
	  {
		  a = mon[j-1].HP + a;
		  mon[j-1].HP = 0;
	  }
	  if(cha.q==2)
	  {
	   if(cha.m>1&&cha.m==j)
	   {
		   b = cha.atc - mon[j-2].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j-2].HP -= b;
		   if(mon[j-2].HP<0)
		   {
			   b = mon[j-2].HP + b;
			   mon[j-2].HP = 0;
		   }
	   }
	   if(cha.m>1&&cha.m!=j)
	   {
		   b = cha.atc - mon[j].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j].HP -= b;
		   if(mon[j].HP<0)
		   {
			   b = mon[j].HP + b;
			   mon[j].HP = 0;
		   }
	   }
	  }
	 }
	 if(strcmp(cha.prof,"��ʦ")==0)
	 {
		if(cha.k==1.5)
		{
			goto loop0;
		}
		if(t==0)
		{
			a = cha.atc - mon[j-1].def;
			n = -10 + rand()%21;
			a += n/10.0*a/3.0;
			a = (double)((int)(a*h*cha.k));
			if(a<1)
			{
				a = 1;
			}
			mon[j-1].HP -= a;
			if(mon[j-1].HP<0)
			{
				a = mon[j-1].HP + a;
				mon[j-1].HP = 0;
			}
			goto loop0;
		}
		if(t!=0)     //t��ѡ��Ĺ������Ǽ���
		{
			a = cha.atc*2 - mon[j-1].def;
			n = -10 + rand()%21;
			a += n/10.0*a/3.0;
			a = (double)((int)(a*h*cha.k));
			if(a<1)
			{
				a = 1;
			}
			mon[j-1].HP -= a;
			if(mon[j-1].HP<0)
			{
				a = mon[j-1].HP + a;
				mon[j-1].HP = 0;
			}
		}
		if(cha.q==2)
		 {
		  if(cha.m>=2&&cha.m==j)
		  {
		   b = cha.atc*2 - mon[j-2].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j-2].HP -= b;
		   if(mon[j-2].HP<0)
		   {
			   b = mon[j-2].HP + b;
			   mon[j-2].HP = 0;
		   }
		  }
		  if(cha.m>=2&&cha.m!=j)
		  {
		   b = cha.atc*2 - mon[j].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j].HP -= b;
		   if(mon[j].HP<0)
		   {
			   b = mon[j].HP + b;
			   mon[j].HP = 0;
		   }
		  }
		 }
		 if(cha.q==3)
		 {
		  if(cha.m==2)
		  {
		   if(cha.m==j)
		   {
			   b = cha.atc*2 - mon[j-2].def;
			   n = -10 + rand()%21;
			   b += n/10.0*b/3.0;
			   b = (double)((int)(b*h*cha.k));
			   if(b<1)
			   {
				   b = 1;
			   }
			   mon[j-2].HP -= b;
			   if(mon[j-2].HP<0)
			   {
				   b = mon[j-2].HP + b;
				   mon[j-2].HP = 0;
			   }
		   }
		   if(cha.m!=j)
		   {
		       b = cha.atc*2 - mon[j].def;
			   n = -10 + rand()%21;
			   b += n/10.0*b/3.0;
			   b = (double)((int)(b*h*cha.k));
			   if(b<1)
			   {
				   b = 1;
			   }
			   mon[j].HP -= b;
			   if(mon[j].HP<0)
			   {
				   b = mon[j].HP + b;
				   mon[j].HP = 0;
			   }
		   }
		  }
		  if(cha.m>=3&&cha.m==j)
		  {
		   b = cha.atc*2 - mon[j-2].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j-2].HP -= b;
		   if(mon[j-2].HP<0)
		   {
			   b = mon[j-2].HP + b;
			   mon[j-2].HP = 0;
		   }
		   c = cha.atc*2 - mon[j-3].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[j-3].HP -= c;
		   if(mon[j-3].HP<0)
		   {
			   c = mon[j-3].HP + c;
			   mon[j-3].HP = 0;
		   }
		  }
		  if(cha.m>=3&&cha.m-1==j)
		  {
		   b = cha.atc*2 - mon[j-2].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j-2].HP -= b;
		   if(mon[j-2].HP<0)
		   {
			   b = mon[j-2].HP + b;
			   mon[j-2].HP = 0;
		   }
		   c = cha.atc*2 - mon[j].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[j].HP -= c;
		   if(mon[j].HP<0)
		   {
			   c = mon[j].HP + c;
			   mon[j].HP = 0;
		   }
		  }
		  if(cha.m>=3&&cha.m!=j&&cha.m!=j+1)
		  {
		   b = cha.atc*2 - mon[j].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j].HP -= b;
		   if(mon[j].HP<0)
		   {
			   b = mon[j].HP + b;
			   mon[j].HP = 0;
		   }
		   c = cha.atc*2 - mon[j+1].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[j+1].HP -= c;
		   if(mon[j+1].HP<0)
		   {
			   c = mon[j+1].HP + c;
			   mon[j+1].HP = 0;
		   }
		  }
		 }
		 if(cha.q==5)
		 {
		  if(cha.m==2)
		  {
		   if(cha.m==j)
		   {
			   b = cha.atc*2 - mon[j-2].def;
			   n = -10 + rand()%21;
			   b += n/10.0*b/3.0;
			   b = (double)((int)(b*h*cha.k));
			   if(b<1)
			   {
				   b = 1;
			   }
			   mon[j-2].HP -= b;
			   if(mon[j-2].HP<0)
			   {
				   b = mon[j-2].HP + b;
				   mon[j-2].HP = 0;
			   }
		   }
		   if(cha.m!=j)
		   {
		       b = cha.atc*2 - mon[j].def;
			   n = -10 + rand()%21;
			   b += n/10.0*b/3.0;
			   b = (double)((int)(b*h*cha.k));
			   if(b<1)
			   {
				   b = 1;
			   }
			   mon[j].HP -= b;
			   if(mon[j].HP<0)
			   {
				   b = mon[j].HP + b;
				   mon[j].HP = 0;
			   }
		   }
		  }
		  if(cha.m==3&&cha.m==j)
		  {
		   b = cha.atc*2 - mon[j-2].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j-2].HP -= b;
		   if(mon[j-2].HP<0)
		   {
			   b = mon[j-2].HP + b;
			   mon[j-2].HP = 0;
		   }
		   c = cha.atc*2 - mon[j-3].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[j-3].HP -= c;
		   if(mon[j-3].HP<0)
		   {
			   c = mon[j-3].HP + c;
			   mon[j-3].HP = 0;
		   }
		  }
		  if(cha.m==3&&cha.m-1==j)
		  {
		   b = cha.atc*2 - mon[j-2].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j-2].HP -= b;
		   if(mon[j-2].HP<0)
		   {
			   b = mon[j-2].HP + b;
			   mon[j-2].HP = 0;
		   }
		   c = cha.atc*2 - mon[j].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[j].HP -= c;
		   if(mon[j].HP<0)
		   {
			   c = mon[j].HP + c;
			   mon[j].HP = 0;
		   }
		  }
		  if(cha.m==3&&cha.m!=j&&cha.m!=j+1)
		  {
		   b = cha.atc*2 - mon[j].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j].HP -= b;
		   if(mon[j].HP<0)
		   {
			   b = mon[j].HP + b;
			   mon[j].HP = 0;
		   }
		   c = cha.atc*2 - mon[j+1].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[j+1].HP -= c;
		   if(mon[j+1].HP<0)
		   {
			   c = mon[j+1].HP + c;
			   mon[j+1].HP = 0;
		   }
		  }
		  if(cha.m==4&&cha.m==j)
		  {
		   b = cha.atc*2 - mon[j-2].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j-2].HP -= b;
		   if(mon[j-2].HP<0)
		   {
			   b = mon[j-2].HP + b;
			   mon[j-2].HP = 0;
		   }
		   c = cha.atc*2 - mon[j-3].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[j-3].HP -= c;
		   if(mon[j-3].HP<0)
		   {
			   c = mon[j-3].HP + c;
			   mon[j-3].HP = 0;
		   }
		   d = cha.atc*2 - mon[j-4].def;
		   n = -10 + rand()%21;
		   d += n/10.0*d/3.0;
		   d = (double)((int)(d*h*cha.k));
		   if(d<1)
		   {
			   d = 1;
		   }
		   mon[j-4].HP -= d;
		   if(mon[j-4].HP<0)
		   {
			   d = mon[j-4].HP + d;
			   mon[j-4].HP = 0;
		   }
		  }
		  if(cha.m==4&&cha.m-1==j)
		  {
		   b = cha.atc*2 - mon[j].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j].HP -= b;
		   if(mon[j].HP<0)
		   {
			   b = mon[j].HP + b;
			   mon[j].HP = 0;
		   }
		   c = cha.atc*2 - mon[j-2].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[j-2].HP -= c;
		   if(mon[j-2].HP<0)
		   {
			   c = mon[j-2].HP + c;
			   mon[j-2].HP = 0;
		   }
		   d = cha.atc*2 - mon[j-3].def;
		   n = -10 + rand()%21;
		   d += n/10.0*d/3.0;
		   d = (double)((int)(d*h*cha.k));
		   if(d<1)
		   {
			   d = 1;
		   }
		   mon[j-3].HP -= d;
		   if(mon[j-3].HP<0)
		   {
			   d = mon[j-3].HP + d;
			   mon[j-3].HP = 0;
		   }
		  }
		  if(cha.m==4&&cha.m-2==j)
		  {
		   b = cha.atc*2 - mon[j+1].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j+1].HP -= b;
		   if(mon[j+1].HP<0)
		   {
			   b = mon[j+1].HP + b;
			   mon[j+1].HP = 0;
		   }
		   c = cha.atc*2 - mon[j].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[j].HP -= c;
		   if(mon[j].HP<0)
		   {
			   c = mon[j].HP + c;
			   mon[j].HP = 0;
		   }
		   d = cha.atc*2 - mon[j-2].def;
		   n = -10 + rand()%21;
		   d += n/10.0*d/3.0;
		   d = (double)((int)(d*h*cha.k));
		   if(d<1)
		   {
			   d = 1;
		   }
		   mon[j-2].HP -= d;
		   if(mon[j-2].HP<0)
		   {
			   d = mon[j-2].HP + d;
			   mon[j-2].HP = 0;
		   }
		  }
		  if(cha.m==4&&cha.m-3==j)
		  {
		   b = cha.atc*2 - mon[j].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j].HP -= b;
		   if(mon[j].HP<0)
		   {
			   b = mon[j].HP + b;
			   mon[j].HP = 0;
		   }
		   c = cha.atc*2 - mon[j+1].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[j+1].HP -= c;
		   if(mon[j+1].HP<0)
		   {
			   c = mon[j+1].HP + c;
			   mon[j+1].HP = 0;
		   }
		   d = cha.atc*2 - mon[j+2].def;
		   n = -10 + rand()%21;
		   d += n/10.0*d/3.0;
		   d = (double)((int)(d*h*cha.k));
		   if(d<1)
		   {
			   d = 1;
		   }
		   mon[j+2].HP -= d;
		   if(mon[j+2].HP<0)
		   {
			   d = mon[j+2].HP + d;
			   mon[j+2].HP = 0;
		   }
		  }
		  if(cha.m==5)
		  {
		   a = cha.atc*2 - mon[0].def;
		   n = -10 + rand()%21;
		   a += n/10.0*a/3.0;
		   a = (double)((int)(a*h*cha.k));
		   if(a<1)
		   {
			   a = 1;
		   }
		   mon[0].HP -= a;
		   if(mon[0].HP<0)
		   {
			   a = mon[0].HP + a;
			   mon[0].HP = 0;
		   }
		   b = cha.atc*2 - mon[1].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[1].HP -= b;
		   if(mon[1].HP<0)
		   {
			   b = mon[1].HP + b;
			   mon[1].HP = 0;
		   }
		   c = cha.atc*2 - mon[2].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[2].HP -= c;
		   if(mon[2].HP<0)
		   {
			   c = mon[2].HP + c;
			   mon[2].HP = 0;
		   }
		   d = cha.atc*2 - mon[3].def;
		   n = -10 + rand()%21;
		   d += n/10.0*d/3.0;
		   d = (double)((int)(d*h*cha.k));
		   if(d<1)
		   {
			   d = 1;
		   }
		   mon[3].HP -= d;
		   if(mon[3].HP<0)
		   {
			   d = mon[3].HP + d;
			   mon[3].HP = 0;
		   }
		   e = cha.atc*2 - mon[4].def;
		   n = -10 + rand()%21;
		   e += n/10.0*e/3.0;
		   e = (double)((int)(e*h*cha.k));
		   if(e<1)
		   {
			   e = 1;
		   }
		   mon[4].HP -= e;
		   if(mon[4].HP<0)
		   {
			   e = mon[4].HP + e;
			   mon[4].HP = 0;
		   }
		  }
		 }
	 }
	 if(strcmp(cha.prof,"��ʿ")==0)
	 {
		 if(cha.k==1.3)
		 {
			 goto loop0;
		 }
	     if(t==0)
		 {
		  a = cha.atc - mon[j-1].def;
		  n = -10 + rand()%21;
		  a += n/10.0*a/3.0;
		  a = (double)((int)(a*h));
		  if(a<1)
		  {
			  a = 1;
		  }
		  mon[j-1].HP -= a;
		  if(mon[j-1].HP<0)
		  {
			  a = mon[j-1].HP + a;
			  mon[j-1].HP = 0;
		  }
		 }
		 if(t!=0)
		 {
		  if(cha.q==-1)
		  {
		    anim = cha.xHP*1.5;
			if(cha.trp!=0)
			{
			 ani[cha.trp-1] = anim;
			}
		  }
		  if(cha.q==1)
		  {
		   a = cha.atc*1.3 - mon[j-1].def;
		   n = -10 + rand()%21;
		   a += n/10.0*a/3.0;
		   a = (double)((int)(a*h));
		   if(a<1)
		   {
			  a = 1;
		   }
		   mon[j-1].HP -= a;
		   if(mon[j-1].HP<0)
		   {
			  a = mon[j-1].HP + a;
			  mon[j-1].HP = 0;
		   }
		  }
		  if(cha.q==3)
		  {
		   a = cha.atc*1.3/2.0;
		   cha.MP += a;
		   if(cha.trp!=0)
		   {
			if(HP[0]!=0)
			{
			 MP[0] += a;
			}
			if(HP[1]!=0)
			{
			 MP[1] += a;
			}
			if(HP[2]!=0)
			{
			 MP[2] += a;
			}
			if(MP[0]>value[1])
			{
			 MP[0] = value[1];
			}
			if(MP[1]>value[3])
			{
			 MP[1] = value[3];
			}
			if(MP[2]>value[5])
			{
			 MP[2] = value[5];
			}
		   }
		   if(cha.MP>cha.xMP)
		   {
			a = cha.xMP-(cha.MP-a)+0.001;
		    cha.MP = cha.xMP;
		   }
		  }
		  if(cha.q==4)
		  {
           a = cha.atc*1.3;
		   cha.HP += a;
		   if(cha.trp!=0)
		   {
			if(HP[0]!=0)
			{
			 HP[0] += a;
			}
			if(ani[0]!=-1.0)
			{
			 ani[0] += a;
			}
			if(HP[1]!=0)
			{
			 HP[1] += a;
			}
			if(ani[1]!=-1.0)
			{
			 ani[1] += a;
			}
			if(HP[2]!=0)
			{
			 HP[2] += a;
			}
			if(ani[2]!=-1.0)
			{
			 ani[2] += a;
			}
			if(HP[0]>value[0])
			{
			 HP[0] = value[0];
			}
			if(ani[0]>value[0]*1.5)
			{
			 ani[0] = value[0]*1.5;
			}
			if(HP[1]>value[2])
			{
			 HP[1] = value[2];
			}
			if(ani[1]>value[2]*1.5)
			{
			 ani[1] = value[2]*1.5;
			}
			if(HP[2]>value[4])
			{
			 HP[2] = value[4];
			}
			if(ani[2]>value[4]*1.5)
			{
			 ani[2] = value[4]*1.5;
			}
		   }
		   if(anim!=-1.0)
		   {
		    anim += a;
		    if(anim>cha.xHP*1.5)
			{
		     anim = cha.xHP*1.5;
			}
		   }
		   if(cha.HP>cha.xHP)
		   {
			a = cha.xHP-(cha.HP-a)+0.001;
		    cha.HP = cha.xHP;
		   }
		  }
		  if(cha.q==6)
		  {
		   mol = cha.xHP*0.75;
		  }
		 }
	 }
	 goto loop0;
	}
	return cha;
}

struct CHARACTER UpAbi(struct CHARACTER cha)
{
    if(strcmp(cha.prof,"սʿ")==0)
	{
	 cha.grd += 1;
	 cha.xHP += 19;
	 cha.HP = cha.xHP;
	 cha.xMP += 3;
	 cha.MP = cha.xMP;
	 cha.atc += 5;
	 cha.def += 3;
	 cha.exp = cha.exp - cha.xexp;
	}
	if(strcmp(cha.prof,"��ʦ")==0)
	{
	 cha.grd += 1;
	 cha.xHP += 5;
	 cha.HP = cha.xHP;
	 cha.xMP += 20;
	 cha.MP = cha.xMP;
	 cha.atc += 2;
	 cha.def += 3;
	 cha.exp = cha.exp - cha.xexp;
	}
	if(strcmp(cha.prof,"��ʿ")==0)
	{
	 cha.grd += 1;
	 cha.xHP += 12;
	 cha.HP = cha.xHP;
	 cha.xMP += 11;
	 cha.MP = cha.xMP;
	 cha.atc += 3.5;
	 cha.def += 3;
	 cha.exp = cha.exp - cha.xexp;
	}
	return cha;
}

struct CHARACTER UpExp(struct CHARACTER cha)
{
    if (cha.grd == grade)
	{
		cha.exp = 0;
	}
	if (cha.grd < 5)
	{
		cha.xexp += 10;
	}
	if (cha.grd >= 5 && cha.grd < 10)
	{
		cha.xexp += 20;
	}
	if (cha.grd >= 10 && cha.grd < 25)
	{
		cha.xexp += 50;
	}
	if (cha.grd >= 25 && cha.grd < 40)
	{
		cha.xexp += 500;
	}
	if (cha.grd >= 40 && cha.grd < 50)
	{
		cha.xexp += 2000;
	}
	if (cha.grd >= 50)
	{
		cha.xexp += 5000;
	}
	return cha;
}

struct CHARACTER Upgrade(struct CHARACTER cha)
{
	double t=0, s=0;
	double exp=cha.exp;
	int w,r,i,j,k,n,v;
	struct MONSTER mon[5];
	struct MONSTER m[5];

	if(exp<=cha.xexp)
	{
		int z=0,a,h;
		if(strcmp(cha.v,"��������")!=0)
		{
			printf("��1�����Ǵ�1Ⱥ\n");
			printf("1.1��  2.1Ⱥ\n");
			scanf("%d",&h);
			getchar();
			while(z>=0)
			{
				m[z] = Monster(cha);
				mon[z] = m[z];
				if(h==1)
				{
					z++;
				    break;
				}
				if(h==2)
				{
					z++;
					a = 1 + rand() % 100;
					if(a<=10+z*10||z==5)
					{
					  break;
					}
				}
				if(h!=1&&h!=2)
				{
				 return cha;
				}
			}
		}
		else
		{
			m[0] = Monbackup(cha);
			mon[0] = m[0];
			z++;
		}
		cha.m = z;
		cha = Battle(cha,m);

		if(cha.m==-1)
		{
		 cha.m = 0;
		 return cha;
		}

		i = 0;
		while(i<=z-1)
		{
		 t += mon[i].exp;
		 s += mon[i].mny;
		 i++;
		}
		cha.exp += t;
		cha.mny += s;
		printf("���Ӿ���%.0lf   ", t);
		printf("  �õ�%.0lf���\n", s);
		if (cha.grd==grade)
		{
			cha.exp = 0;
		}
		
		k = 0;
		while(k<=z-1)
		{
			i = 0;
			while(mon[k].out[i].nam != '\0')
			{
				w = cha.t;
				n = w;
				v = 0;
				if(mon[k].out[i].nam!='*')
				{
					for(j=0;j<=w-1;j++)
					{
						if(cha.goods[j].nam == mon[k].out[i].nam)
						{
							n = j;
							break;
						}
					}
					if(n==w)
					{
						if(w==17)
						{
							printf("�����ռ䲻��\n");
							v = 1;
						}
						else
						{
							cha.goods[w].nam = mon[k].out[i].nam;
							strcpy(cha.goods[w].name,mon[k].out[i].name);
							cha.t += 1;
							cha.goods[w].q = mon[k].out[i].q;
						}
					}
					else
					{
						cha.goods[n].q += mon[k].out[i].q;
					}
					if(v==0)
					{
						printf("�õ���Ʒ%c\n", mon[k].out[i].nam);
					}
					if(v==1)
					{
						printf("�޷��õ���Ʒ%c\n", mon[k].out[i].nam);
						printf("\n");
					}
				}
				if(mon[k].out[i].nam=='*')
				{
					if(w==17)
					{
						printf("�����ռ䲻��\n");
						printf("�޷��õ���Ʒ%c\n", mon[k].out[i].nam);
						printf("\n");
					}
					else
					{
						cha.goods[w].nam = mon[k].out[i].nam;
						cha.t += 1;
						r = cha.e;
						cha.equ[r].grd = mon[k].grd;
						cha.equ[r].rank = mon[k].oequ[i].rank;
						strcpy(cha.equ[r].kind,mon[k].oequ[i].kind);
						cha.e += 1;
						cha = EquAtt(cha);
						printf("�õ���Ʒ%c\n", mon[k].out[i].nam);
					}
				}
				i++;
			}
			k++;
		}
		printf("ȷ��");
		getchar();
		printf("\n\n");
		return cha;
	}
	printf("��ϲ����������\n");
	cha = UpAbi(cha);
	cha = UpExp(cha);
	printf("ȷ��");
	getchar();
	printf("\n\n");
	return cha;
}

struct CHARACTER Go(struct CHARACTER cha)
{
 int v=0,t;
 if(strcmp(cha.v,"����С��")==0)
 {
	printf("��ȥ������Ը���˵!\n");
	printf("1.�����ܱ�   (1~4��)\n");
	printf("2.ɭ��       (5~9��)\n");
    printf("3.��ʬ��     (10~15��)\n");
	printf("4.��򼶴     (16~20��)\n");
	printf("5.ʯ��       (21~25��)\n");
	printf("6.���븱�� ��������\n");
	printf("7.ȥ�������� �����\n");
	printf("��ѡ��");
	scanf("%d",&v);
	getchar();
	if(v==1)
	{
	  strcpy(cha.v,"�����ܱ�");
	}
	if(v==2)
	{
	  strcpy(cha.v,"ɭ��");
	}
	if(v==3)
	{
	  strcpy(cha.v,"��ʬ��");
	}
	if(v==4)
	{
	  strcpy(cha.v,"��򼶴");
	}
	if(v==5)
	{
	  strcpy(cha.v,"ʯ��");
	}
	if(v==6)
	{
	  if(cha.grd<25)
	  {
		printf("�ȼ���������25��\n");
		return cha;
	  }
	  strcpy(cha.v,"��������");
	}
	if(v==7)
	{
	  printf("��100��ң��Ƿ�ѡ��?\n");
	  printf("1.�� 2.��\n");
	  printf("��ѡ��");
	  scanf("%d",&t);
	  getchar();
	  if(t==1)
	  {
		  if(cha.mny<100)
		  {
			  printf("�����Ѳ���\n");
			  printf("ȷ��");
			  getchar();
			  return cha;
		  }
		  cha.mny -= 100;
		  printf("ȷ��");
		  getchar();
		  strcpy(cha.v,"�����");
		  return cha;
	  }
	}
	printf("\n");
	return cha;
 }
 if(strcmp(cha.v,"�����ܱ�")==0||strcmp(cha.v,"ɭ��")==0||strcmp(cha.v,"��ʬ��")==0||
	 strcmp(cha.v,"��򼶴")==0||strcmp(cha.v,"ʯ��")==0||strcmp(cha.v,"��������")==0)
 {
	 strcpy(cha.v,"����С��");
	 return cha;
 }
 if(strcmp(cha.v,"�����")==0)
 {
	printf("��������ٵĳ���!\n");
	printf("1.Ұ��     (26~32��)\n");
	printf("2.��ħ��     (33~40��)\n");
	printf("3.ȥ�������� ����С��\n");
	printf("��ѡ��");
	scanf("%d",&v);
	getchar();
	if(v==1)
	{
	  strcpy(cha.v,"Ұ��");
	}
	if(v==2)
	{
	  strcpy(cha.v,"��ħ��");
	}
	if(v==3)
	{
	  printf("��100��ң��Ƿ�ѡ��?\n");
	  printf("1.�� 2.��\n");
	  printf("��ѡ��");
	  scanf("%d",&t);
	  getchar();
	  if(t==1)
	  {
		  if(cha.mny<100)
		  {
			  printf("�����Ѳ���\n");
			  printf("ȷ��");
			  getchar();
			  return cha;
		  }
		  cha.mny -= 100;
		  printf("ȷ��");
		  getchar();
		  strcpy(cha.v,"����С��");
		  return cha;
	  }
	}
	printf("\n");
	return cha;
 }
 if(strcmp(cha.v,"Ұ��")==0||strcmp(cha.v,"��ħ��")==0)
 {
	 strcpy(cha.v,"�����");
	 return cha;
 }
 return cha;
}

struct CHARACTER Foundtroop(struct CHARACTER cha)
{
 FILE* fp;
 char troop[37];
 char name[20];
 char z = '0';
 char u;
 strcpy(name,"\0");
 int i,k;
 if(cha.trp>=1&&cha.trp<=3)
 {
  return cha;
 }
 printf("�������������:");
 gets(cha.trpname);
 fp = fopen(troopfile,"rb");
 if(fp==NULL)
 {
  fp = fopen(troopfile,"wb");
  i = 1;
  fwrite(&i,4,1,fp);
  fwrite(cha.trpname,37,1,fp);
  fwrite(cha.v,20,1,fp);
  fwrite(&z,1,1,fp);
  fwrite(cha.name,20,1,fp);
  fwrite(&z,1,1,fp);
  fwrite(name,20,1,fp);
  fwrite(&z,1,1,fp);
  fwrite(name,20,1,fp);
  fclose(fp);
 }
 else
 {
  fread(&i,4,1,fp);
  k = 1;
  while(k<=i)
  {
   fread(troop,37,1,fp);
   if(strcmp(cha.trpname,troop)==0)
   {
    printf("������������\n");
	fclose(fp);
	strcpy(cha.trpname,"\0");
	return cha;
   }
   fread(name,20,1,fp);
   fread(&u,1,1,fp);
   fread(name,20,1,fp);
   fread(&u,1,1,fp);
   fread(name,20,1,fp);
   fread(&u,1,1,fp);
   fread(name,20,1,fp);
   k++;
  }
  fclose(fp);
  strcpy(name,"\0");
  fp = fopen(troopfile,"ab");
  fwrite(cha.trpname,37,1,fp);
  fwrite(cha.v,20,1,fp);
  fwrite(&z,1,1,fp);
  fwrite(cha.name,20,1,fp);
  fwrite(&z,1,1,fp);
  fwrite(name,20,1,fp);
  fwrite(&z,1,1,fp);
  fwrite(name,20,1,fp);
  fclose(fp);
  fp = fopen(troopfile,"rb+");
  i++;
  fwrite(&i,4,1,fp);
  fclose(fp);
 }
 cha.trp = 1;
 strcpy(cha.buddy1,cha.name);
 return cha;
}

struct CHARACTER Uptrp(struct CHARACTER cha)
{
	FILE* fp;
	int k,i=1;
	char troop[37];
	char name[20];
	char u;
	fp = fopen(troopfile,"rb+");
	fread(&k,4,1,fp);
	while(i<=k)
	{
		fread(troop,37,1,fp);
		if(strcmp(troop,cha.trpname)==0)
		{
			fread(name,20,1,fp);
			fread(&cha.b1,1,1,fp);
			fread(cha.buddy1,20,1,fp);
			fread(&cha.b2,1,1,fp);
			fread(cha.buddy2,20,1,fp);
			fread(&cha.b3,1,1,fp);
			fread(cha.buddy3,20,1,fp);
			break;
		}
		fread(name,20,1,fp);
		fread(&u,1,1,fp);
		fread(name,20,1,fp);
		fread(&u,1,1,fp);
		fread(name,20,1,fp);
		fread(&u,1,1,fp);
		fread(name,20,1,fp);
		i++;
	}
	fclose(fp);
	if(strcmp(cha.buddy1,cha.name)==0)
	{
	 cha.trp = 1;
	}
	if(strcmp(cha.buddy2,cha.name)==0)
	{
	 cha.trp = 2;
	}
	if(strcmp(cha.buddy3,cha.name)==0)
	{
	 cha.trp = 3;
	}
	return cha;
}

struct CHARACTER Prepare(struct CHARACTER cha)
{
    FILE* fp;
	int k,i=1;
	char troop[37];
	char name[20];
	char u;
	char n;
	if((cha.trp==1&&cha.b1=='1')||(cha.trp==2&&cha.b2=='1')||(cha.trp==3&&cha.b3=='1'))
	{
	 n = '0';
	}
	else
	{
	 n = '1';
	 if(cha.b1=='2')
	 {
	  n = '2';
	 }
	}
	fp = fopen(troopfile,"rb+");
	fread(&k,4,1,fp);
	while(i<=k)
	{
		fread(troop,37,1,fp);
		if(strcmp(troop,cha.trpname)==0)
		{
			fread(name,20,1,fp);
			if(cha.trp==1)
			{
			 fseek(fp,61L+(i-1)*120L,0);
			 fwrite(&n,1,1,fp);
			 fseek(fp,62L+(i-1)*120L,0);
			}
			else
			{
			 fread(&u,1,1,fp);
			}
			fread(name,20,1,fp);
			if(cha.trp==2)
			{
			 fseek(fp,82L+(i-1)*120L,0);
			 fwrite(&n,1,1,fp);
			 fseek(fp,83L+(i-1)*120L,0);
			}
			else
			{
			 fread(&u,1,1,fp);
			}
			fread(name,20,1,fp);
			if(cha.trp==3)
			{
			 fseek(fp,103L+(i-1)*120L,0);
			 fwrite(&n,1,1,fp);
			 fseek(fp,104L+(i-1)*120L,0);
			}
			else
			{
			 fread(&u,1,1,fp);
			}
			fread(name,20,1,fp);
			break;
		}
		fread(name,20,1,fp);
		fread(&u,1,1,fp);
		fread(name,20,1,fp);
		fread(&u,1,1,fp);
		fread(name,20,1,fp);
		fread(&u,1,1,fp);
		fread(name,20,1,fp);
		i++;
	}
	return cha;
}

struct CHARACTER Outtrp(struct CHARACTER cha)
{
	FILE* fp;
	FILE* ft;
	int k,i=1;
	char troop[37];
	char name[20];
	char u;
	fp = fopen(troopfile,"rb+");
	fread(&k,4,1,fp);
	while(i<=k)
	{
		fread(troop,37,1,fp);
		if(strcmp(troop,cha.trpname)==0)
		{
			fread(name,20,1,fp);
			fread(&cha.b1,1,1,fp);
			fread(cha.buddy1,20,1,fp);
			fread(&cha.b2,1,1,fp);
			fread(cha.buddy2,20,1,fp);
			fread(&cha.b3,1,1,fp);
			fread(cha.buddy3,20,1,fp);
			break;
		}
		fread(name,20,1,fp);
		fread(&u,1,1,fp);
		fread(name,20,1,fp);
		fread(&u,1,1,fp);
		fread(name,20,1,fp);
		fread(&u,1,1,fp);
		fread(name,20,1,fp);
		i++;
	}
	if(strcmp(cha.buddy1,cha.name)==0)
	{
	 cha.trp = 1;
	}
	if(strcmp(cha.buddy2,cha.name)==0)
	{
	 cha.trp = 2;
	}
	if(strcmp(cha.buddy3,cha.name)==0)
	{
	 cha.trp = 3;
	}
   if(cha.trp==1)
   {
    fseek(fp,61L+(i-1)*120L,0);
	strcpy(cha.buddy1,cha.buddy2);
	cha.b1 = cha.b2;
	strcpy(cha.buddy2,cha.buddy3);
	cha.b2 = cha.b3;
	strcpy(cha.buddy3,"\0");
	cha.b3 = '0';
	fwrite(&cha.b1,1,1,fp);
	fwrite(cha.buddy1,20,1,fp);
	fwrite(&cha.b2,1,1,fp);
	fwrite(cha.buddy2,20,1,fp);
	fwrite(&cha.b3,1,1,fp);
	fwrite(cha.buddy3,20,1,fp);
	fclose(fp);
	if(strcmp(cha.buddy1,"\0")==0)
	{
	 fp = fopen(troopfile,"rb");
	 ft = fopen(tfile,"wb");
	 char t;
	 int n;
	 t = fgetc(fp);
	 while(!feof(fp))
	 {
	  fputc(t,ft);
	  t = fgetc(fp);
	 }
	 fclose(fp);
	 fclose(ft);
	 fp = fopen(troopfile,"wb");
	 ft = fopen(tfile,"rb");
     fread(&k,4,1,ft);
	 k = k-1;
	 fwrite(&k,4,1,fp);
	 n = 2;
	 while(n<=i)
	 {
	  fread(troop,37,1,ft);
	  fwrite(troop,37,1,fp);
	  fread(name,20,1,ft);
	  fwrite(name,20,1,fp);
	  fread(&u,1,1,ft);
	  fwrite(&u,1,1,fp);
	  fread(name,20,1,ft);
	  fwrite(name,20,1,fp);
	  fread(&u,1,1,ft);
	  fwrite(&u,1,1,fp);
	  fread(name,20,1,ft);
	  fwrite(name,20,1,fp);
	  fread(&u,1,1,ft);
	  fwrite(&u,1,1,fp);
	  fread(name,20,1,ft);
	  fwrite(name,20,1,fp);
	  n++;
	 }
	 n++;
	 fseek(ft,120L,1);
	 while(n<=k+2)
	 {
	  fread(troop,37,1,ft);
	  fwrite(troop,37,1,fp);
	  fread(name,20,1,ft);
	  fwrite(name,20,1,fp);
	  fread(&u,1,1,ft);
	  fwrite(&u,1,1,fp);
	  fread(name,20,1,ft);
	  fwrite(name,20,1,fp);
	  fread(&u,1,1,ft);
	  fwrite(&u,1,1,fp);
	  fread(name,20,1,ft);
	  fwrite(name,20,1,fp);
	  fread(&u,1,1,ft);
	  fwrite(&u,1,1,fp);
	  fread(name,20,1,ft);
	  fwrite(name,20,1,fp);
	  n++;
	 }
	 fclose(ft);
	 fclose(fp);
	 unlink(tfile);
	}
   }
   if(cha.trp==2)
   {
    fseek(fp,82L+(i-1)*120L,0);
	strcpy(cha.buddy2,cha.buddy3);
	cha.b2 = cha.b3;
	strcpy(cha.buddy3,"\0");
	cha.b3 = '0';
	fwrite(&cha.b2,1,1,fp);
	fwrite(cha.buddy2,20,1,fp);
	fwrite(&cha.b3,1,1,fp);
	fwrite(cha.buddy3,20,1,fp);
	fclose(fp);
   }
   if(cha.trp==3)
   {
    fseek(fp,103L+(i-1)*120L,0);
	strcpy(name,"\0");
	cha.b3 = '0';
	fwrite(&cha.b3,1,1,fp);
	fwrite(name,20,1,fp);
	fclose(fp);
   }
   strcpy(cha.trpname,"\0");
   cha.trp = 0;
   strcpy(cha.buddy1,"\0");
   strcpy(cha.buddy2,"\0");
   strcpy(cha.buddy3,"\0");
   cha.b1 = '0';
   cha.b2 = '0';
   cha.b3 = '0';
   return cha;
}

struct CHARACTER Troops(struct CHARACTER cha)
{
 FILE* fp;
 //char troop[37];
 char troop1[100][37];
 char troop2[100][37];
 char name[20];
 char name1[20];
 char name2[20];
 char name3[20];
 int i,k,j,t;
 char z = '0';
 char h = '1';
 char u;
 for(i=0;i<=99;i++)
 {
  strcpy(troop1[i],"\0");
  strcpy(troop2[i],"\0");
 }
 fp = fopen(troopfile,"rb");
 if(fp==NULL)
 {
  fp = fopen(troopfile,"wb");
  i = 0;
  fwrite(&i,4,1,fp);
 }
 fclose(fp);
  i = 0;
  fp = fopen(troopfile,"rb");
  fread(&k,4,1,fp);
  while(i<=k-1)
  {
   fread(troop1[i],37,1,fp);
   fread(name,20,1,fp);
   fread(&u,1,1,fp);
   fread(name1,20,1,fp);
   fread(&u,1,1,fp);
   fread(name2,20,1,fp);
   fread(&u,1,1,fp);
   fread(name3,20,1,fp);
   if(strcmp(name,cha.v)!=0||(strcmp(name1,"\0")!=0 && strcmp(name2,"\0")!=0 && strcmp(name3,"\0")!=0))
   {
	k--;
    continue;
   }
   printf("%d.%s\n",i+1,troop1[i]);
   printf("^1.%s",name1);
   printf(" 2.%s",name2);
   printf(" 3.%s\n",name3);
   i++;
  }
  printf("\n��ѡ�����");
  scanf("%d",&j);
  getchar();

  fseek(fp,0L,0);
  fread(&k,4,1,fp);
  i = 0;
  t = 0;
  int g = 1;
  while(i<=k-1)
  {
   fread(troop2[i],37,1,fp);
   if(strcmp(troop2[i],troop1[j-1])==0)
   {
    t = g;
   }
   fread(name,20,1,fp);
   fread(&u,1,1,fp);
   fread(name1,20,1,fp);
   fread(&u,1,1,fp);
   fread(name2,20,1,fp);
   fread(&u,1,1,fp);
   fread(name3,20,1,fp);
   g++;
   if(strcmp(name,cha.v)!=0||(strcmp(name1,"\0")!=0 && strcmp(name2,"\0")!=0 && strcmp(name3,"\0")!=0))
   {
	k--;
    continue;
   }
   i++;
  }
  fclose(fp);
  
  if(j<=k&&j>=1)
  {
   if(strcmp(troop1[j-1],troop2[j-1])!=0)
   {
    printf("�޷�����\n");
    return cha;
   }
   fp = fopen(troopfile,"rb+");
   fseek(fp,4L+(t-1)*120L,0);
   fread(cha.trpname,37,1,fp);
   fread(name,20,1,fp);
   fread(&u,1,1,fp);
   fread(name,20,1,fp);
   cha.b1 = u;
   strcpy(cha.buddy1,name);
   fread(&u,1,1,fp);
   fread(name,20,1,fp);
   if(strcmp(name,"\0")==0)
   {
    fseek(fp,83L+(t-1)*120L,0);
	fwrite(cha.name,20,1,fp);
	fclose(fp);
	cha.trp = 2;
	strcpy(cha.buddy2,cha.name);
   }
   else
   {
	cha.b2 = u;
	strcpy(cha.buddy2,name);
	fread(&u,1,1,fp);
    fread(name,20,1,fp);
    if(strcmp(name,"\0")==0)
    {
     fseek(fp,104L+(t-1)*100L,0);
	 fwrite(cha.name,20,1,fp);
	 fclose(fp);
	 cha.trp = 3;
	 strcpy(cha.buddy3,cha.name);
    }
	else
	{
	 cha.b3 = u;
	 strcpy(cha.buddy3,name);
	}
   }
  }      //j
 return cha;
}

struct CHARACTER Group(struct CHARACTER cha)
{
	int k,y=0;
	printf("1.�������\n");
	printf("2.�鿴���\n");
	printf("��ѡ��");
	scanf("%d",&k);
	getchar();
	if(k==1)
	{
		cha = Foundtroop(cha);
	}
	if(k==2)
	{
		cha = Troops(cha);
	}
	if(cha.trp==0)
	{
		return cha;
	}
	while(y==0)
	{
		printf("                              //��ӵȺ���//\n\n");
		printf("^1.%s",cha.buddy1);
		if(cha.b1=='1')
		{
			printf("* ");
		}
		else
		{
			printf("  ");
		}
		printf(" 2.%s",cha.buddy2);
		if(cha.b2=='1')
		{
			printf("* ");
		}
		else
		{
			printf("  ");
		}
		printf(" 3.%s",cha.buddy3);
		if(cha.b3=='1')
		{
			printf("* ");
		}
		else
		{
			printf("  ");
		}
		printf("\n");
		if((cha.trp==1&&cha.b1=='1')||(cha.trp==2&&cha.b2=='1')||(cha.trp==3&&cha.b3=='1'))
		{
		 printf("1.ˢ��  2.ȡ��׼��  3.�˶�  ");
		}
		else
		{
		 printf("1.ˢ��  2.׼��  3.�˶�  ");
		}
		if(((cha.b1=='1'&&cha.b2=='1'&&cha.b3=='1'&&strcmp(cha.buddy1,"\0")!=0&&strcmp(cha.buddy2,"\0")!=0&&strcmp(cha.buddy3,"\0")!=0)||
		   (cha.b1=='1'&&cha.b2=='1'&&cha.b3=='0'&&strcmp(cha.buddy1,"\0")!=0&&strcmp(cha.buddy2,"\0")!=0&&strcmp(cha.buddy3,"\0")==0)||
		   (cha.b1=='1'&&cha.b2=='0'&&cha.b3=='0'&&strcmp(cha.buddy1,"\0")!=0&&strcmp(cha.buddy2,"\0")==0&&strcmp(cha.buddy3,"\0")==0))&&
		   cha.trp==1)
		{
		 printf("4.����");
		}
		printf("\n");
		printf("��ѡ��");
		scanf("%d",&k);
		getchar();
		if(k==1)
		{
			cha = Uptrp(cha);
			if(cha.b1=='2')
			{
			 cha = Upgrade(cha);
			 cha = Prepare(cha);
			 cha = Uptrp(cha);
			 cha.b1 = '0';
			}
		}
		if(k==2)
		{
			if(cha.b1=='2')
			{
			 printf("�����ѽ��븱��\n");
			 cha = Upgrade(cha);
			 cha = Prepare(cha);
			 cha = Uptrp(cha);
			 cha.b1 = '0';
			}
			else
			{
		     cha = Prepare(cha);
			 cha = Uptrp(cha);
			}
		}
		if(k==3)
		{
		    cha = Outtrp(cha);
			y = 1;
		}
		if(k==4&&cha.trp==1)
		{
		    cha = Uptrp(cha);
			if((cha.b1=='1'&&cha.b2=='1'&&cha.b3=='1'&&strcmp(cha.buddy1,"\0")!=0&&strcmp(cha.buddy2,"\0")!=0&&strcmp(cha.buddy3,"\0")!=0)||
		      (cha.b1=='1'&&cha.b2=='1'&&cha.b3=='0'&&strcmp(cha.buddy1,"\0")!=0&&strcmp(cha.buddy2,"\0")!=0&&strcmp(cha.buddy3,"\0")==0)||
		      (cha.b1=='1'&&cha.b2=='0'&&cha.b3=='0'&&strcmp(cha.buddy1,"\0")!=0&&strcmp(cha.buddy2,"\0")==0&&strcmp(cha.buddy3,"\0")==0))
			{
			   cha.b1 = '2';
			   cha = Prepare(cha);
		       cha = Upgrade(cha);
			   cha.b1 = '1';
			   cha = Prepare(cha);
			   cha = Uptrp(cha);
			}
		}
	}
	return cha;
}

struct CHARACTER Player(struct CHARACTER cha)
{
	FILE* f3;
	//FILE* fp;
	int y,k,i,d,p,s;
	double a[12];
	struct GOODS c[17];
	char name[20];
    struct EQUIPMENT b[24];
	f3 = fopen(onlinefile,"rb");
	fread(&y,4,1,f3);
	k = 1;
	i = 1;
	struct MONSTER n[100];
	while(k<=y)
	{
		fread(name,20,1,f3);
		fread(n[i-1].name,20,1,f3);
		if(strcmp(n[i-1].name,"\0")!=0&&strcmp(cha.name,n[i-1].name)!=0)
		{
			printf("%d.%s\n",i,n[i-1].name);
			i++;
		}
		k++;
	}
	i--;
	printf("\n");
	fclose(f3);
	printf("��ѡ��");
	scanf("%d",&d);
	getchar();
	k = 1;
	while(k!=3&&d>=1&&d<=i)
	{
		printf("1.�鿴  2.����  3.�˳�\n");
		printf("��ѡ��");
		scanf("%d",&k);
		getchar();
		f3 = fopen(onlinefile,"rb");
		fseek(f3,4L,0);
		char filename[100];
		char fileroad[100];
		strcpy(filename,savefolder);
		char acct[20];
		if(k==1)
		{
			fread(acct,20,1,f3);
			fread(name,20,1,f3);
			while(strcmp(name,n[d-1].name)!=0)
			{
				fread(acct,20,1,f3);
				fread(name,20,1,f3);
			}
			strcat(filename,acct);
			strcpy(acct,".ys");
			strcat(filename,acct);
			fclose(f3);
			f3 = fopen(filename,"rb");
			fread(&p,4,1,f3);
			fread(name,20,1,f3);
			while(strcmp(name,n[d-1].name)!=0)
			{
				fseek(f3,size-20,1);
				fread(name,20,1,f3);
			}
			printf("\n");
			puts(name);
			fread(acct,20,1,f3);
			fread(name,20,1,f3);
			fread(a,8,12,f3);
			printf("�ȼ�       %d\n",(int)a[0]);
			printf("ְҵ       %s\n", acct);
			fread(c,sizeof(struct GOODS),17,f3);
			fread(b,sizeof(struct EQUIPMENT),24,f3);
			fclose(f3);
			i = 1;
			while(i==1)
			{
				printf("       1.%c\n\n",b[0].rank);
				printf("2.%c          6.%c\n\n",b[1].rank,b[5].rank);
				printf("3.%c          7.%c\n\n",b[2].rank,b[6].rank);
				printf("4.%c   5.%c\n",b[3].rank,b[4].rank);
				printf("��ѡ��");
				scanf("%d",&s);
				getchar();
				if(s!=1&&s!=2&&s!=3&&s!=4&&s!=5&&s!=6&&s!=7)
				{
					break;
				}
				s--;
				if(strcmp(b[s].name,"\0")!=0)
				{
					if(strcmp(cha.equ[s].name,"\0")==0)
					{
						printf("   ");
						printf("%s\n",b[s].name);
						printf("����:%s\n", b[s].kind);
						printf("װ������   %d\n", b[s].grd);
						printf("װ������   %c\n", b[s].rank);
						printf("HP         +%.0lf\n", b[s].axHP);
						printf("MP         +%.0lf\n", b[s].axMP);
						printf("������     +%.0lf\n", b[s].aatc);
						printf("������     +%.0lf\n", b[s].adef);
					}
					else
					{
						printf("   ");
						printf("%s",b[s].name);
						printf("           |   ");
						printf("%s\n",cha.equ[s].name);
						printf("����:%s             |����:%s\n", b[s].kind,cha.equ[s].kind);
						printf("װ������   %d         |װ������   %d\n", b[s].grd,cha.equ[s].grd);
						printf("װ������   %c          |װ������   %c\n", b[s].rank,cha.equ[s].rank);
						printf("HP         +%-5.0lf     |HP         +%.0lf\n", b[s].axHP,cha.equ[s].axHP);
						printf("MP         +%-5.0lf     |MP         +%.0lf\n", b[s].axMP,cha.equ[s].axMP);
						printf("������     +%-5.0lf     |������     +%.0lf\n", b[s].aatc,cha.equ[s].aatc);
						printf("������     +%-5.0lf     |������     +%.0lf\n", b[s].adef,cha.equ[s].adef);
					}
					printf("ȷ��");
					getchar();
					printf("\n");
				}
				if(strcmp(b[s].name,"\0")==0)
				{
					printf("��װ��\n");
					printf("ȷ��");
					getchar();
					printf("\n");
				}
			}  //i=1
		}   //k=1
		if(k==2)
		{
			FILE* fx;
			//FILE* f2;
			clock_t t1;
			clock_t t2;
			int ti;
			i = 0;
			s = 0;
			strcpy(acct,act);
			strcat(acct,".ys");
			strcpy(fileroad,storyfolder);
			strcat(fileroad,acct);
			fx = fopen(fileroad,"wb");
			i = 0;
			fwrite(&i,4,1,fx);
			fclose(fx);
			fread(acct,20,1,f3);
			fread(name,20,1,f3);
			while(strcmp(name,n[d-1].name)!=0)
			{
				fread(acct,20,1,f3);
				fread(name,20,1,f3);
			}
			strcpy(filename,storyfolder);
			strcpy(name,".ys");
			strcat(acct,name);
			strcat(filename,acct);
			fclose(f3);
			t1 = clock();
			printf("��ȴ�...10");
			t2 = clock();
			ti = 0;
			while((t2-t1)/1000<=10)
			{
				fx = fopen(filename,"rb");
				if(fx!=NULL)
				{
					fclose(fx);
					break;
				}
				if((t2-t1)/1000==ti)
				{
				 printf("\b \b\b \b%2d",10-ti);
				 ti++;
				}
				t2 = clock();
			}
			printf("\n");
			if((t2-t1)/1000<=10)
			{
              loop1:i = 0;
	          printf("����\n");
	          printf("0.���     %.0lf\n", cha.mny);
	          while (cha.goods[i].nam != '\0'&&i<=16)
			  {
				  if(cha.goods[i].nam=='*')
				  {
					  printf("%d.%c\n", i + 1, cha.goods[i].nam);
				  }
				  else
				  {
				      printf("%d.%c��%d\n", i + 1, cha.goods[i].nam,cha.goods[i].q);
				  }
				  i++;
			  }
			  i++;
			  printf("%d.ȷ�� %d.ȡ��\n",i,i+1);
			  int g;
			  g = i;
			  printf("��ѡ��");
			  scanf("%d",&i);
			  getchar();
			  int l;
			  int j=0,n=6,r;
			  struct CHARACTER give;
			  struct CHARACTER get;
			  if(i==0)
			  {
				  printf("����������:");
				  scanf("%lf",&give.mny);
				  getchar();
				  if(give.mny>cha.mny)
				  {
					  give.mny = cha.mny;
				  }
				  if(give.mny<0)
				  {
					  give.mny = 0;
				  }
				  printf("ȷ��?\n");
				  printf("1.�� 2.��");
				  scanf("%d",&l);
				  getchar();
				  if(l==1)
				  {
					  fx = fopen(fileroad,"ab");
					  fwrite(&give.mny,8,1,fx);
					  fclose(fx);
					  s = 1;           //1Ϊ���
					  r = s;
					  t1 = clock();
					  fx = fopen(fileroad,"rb+");
					  fwrite(&s,4,1,fx);
					  fclose(fx);
					  printf("��ȴ��Է���10");
					  t2 = clock();
					  ti = 0;
					  while((t2-t1)/1000<=10)
					  {
						  fx = fopen(filename,"rb");
						  if(fx==NULL)
						  {
							  printf("\n�����ѱ�ȡ��\n");
							  goto loop3;
						  }
						  fread(&s,4,1,fx);
						  fclose(fx);
						  if(s>=1)
						  {
							  if(s==9)
							  {
								  printf("\n�����ѱ�ȡ��\n");
								  break;
							  }
							  cha.mny -= give.mny;
							  goto loop2;
						  }
						  if((t2-t1)/1000==ti)
						  {
							  printf("\b \b\b \b%2d",10-ti);
							  ti++;
						  }
						  t2 = clock();
					  }
					  printf("\n");
					  unlink(fileroad);
				  }
				  else
				  {
					  goto loop1;
				  }
			  }
			  if(cha.goods[i-1].nam == '@'||cha.goods[i-1].nam == '%'||cha.goods[i-1].nam == '#'||cha.goods[i-1].nam == '*')
			  {
				  printf("����Ʒ���ܽ���\n");
				  printf("ȷ��");
				  getchar();
				  printf("\n");
				  goto loop1;
			  }
			  if(cha.goods[i-1].nam == 'a'||cha.goods[i-1].nam == 'b'||cha.goods[i-1].nam == '$'||cha.goods[i-1].nam == 'c')
			  {
				  printf("����������:");
				  scanf("%d",&give.goods[0].q);
				  getchar();
				  if(give.goods[0].q>cha.goods[i-1].q)
				  {
					  give.goods[0].q = cha.goods[i-1].q;
				  }
				  if(give.goods[0].q<0)
				  {
					  give.goods[0].q = 0;
				  }
				  give.goods[0].nam = cha.goods[i-1].nam;
				  strcpy(give.goods[0].name,cha.goods[i-1].name);
				  printf("ȷ��?\n");
				  printf("1.�� 2.��");
				  scanf("%d",&l);
				  getchar();
				  if(l==1)
				  {
					  fx = fopen(fileroad,"ab");
					  fwrite(&give.goods[0],sizeof(struct GOODS),1,fx);
					  fclose(fx);
					  s = 3;
					  r = s;
					  t1 = clock();
					  n = i-1;
					  fx = fopen(fileroad,"rb+");
					  fwrite(&s,4,1,fx);
					  fclose(fx);
					  printf("��ȴ��Է���10");
					  t2 = clock();
					  ti = 0;
					  while((t2-t1)/1000<=10)
					  {
						  fx = fopen(filename,"rb");
						  if(fx==NULL)
						  {
							  printf("\n�����ѱ�ȡ��\n");
							  goto loop3;
						  }
						  fread(&s,4,1,fx);
						  fclose(fx);
						  if(s>=1)
						  {
							  if(s==9)
							  {
								  printf("\n�����ѱ�ȡ��\n");
								  break;
							  }
						      cha.goods[i-1].q -= give.goods[0].q;
							  if(cha.goods[i-1].q==0)
							  {
								  j = i-1;
								  while(j<=cha.t-2)
								  {
									  cha.goods[j] = cha.goods[j+1];
									  j++;
								  }
								  cha.goods[j].nam = '\0';
								  strcpy(cha.goods[j].name,"\0");
								  cha.goods[j].q = 0;
								  cha.t--;
							  }
							  goto loop2;
						  }
						  if((t2-t1)/1000==ti)
						  {
							  printf("\b \b\b \b%2d",10-ti);
							  ti++;
						  }
						  t2 = clock();
					  }
					  printf("\n");
					  unlink(fileroad);
				  }
				  else
				  {
					  goto loop1;
				  }
			  }
			  if(i==g)
			  {
				  s = 10;
				  r = s;
				  t1 = clock();
				  fx = fopen(fileroad,"rb+");
				  fwrite(&s,4,1,fx);
				  fclose(fx);
				  printf("��ȴ��Է���10");
				  t2 = clock();
				  ti = 0;
				  while((t2-t1)/1000<=10)
				  {
					  fx = fopen(filename,"rb");
					  if(fx==NULL)
					  {
						  goto loop3;
					  }
					  fread(&s,4,1,fx);
					  fclose(fx);
					  if(s>=1)
					  {
						  if(s==9)
						  {
						   printf("\n�����ѱ�ȡ��\n");
						   goto  loop3;
						  }
						  goto loop2;
					  }
					  if((t2-t1)/1000==ti)
					  {
						  printf("\b \b\b \b%2d",10-ti);
						  ti++;
					  }
					  t2 = clock();
				  }     //while
				  printf("\n");
				  unlink(fileroad);
			  }
        loop2:if(s>=1&&s!=9)
			  {
				  fx = fopen(filename,"rb");
				  fseek(fx,4L,0);
				  if(s==1)
				  {
					  fread(&get.mny,8,1,fx);
					  fclose(fx);
					  printf("\n�Է�����\n");
					  printf("���%.0lf\n",get.mny);
					  printf("ȷ��?\n");
					  printf("1.�� 2.��");
					  scanf("%d",&n);
					  getchar();
				  }
				  if(s==3)
				  {
					  fread(&get.goods[0],sizeof(struct GOODS),1,fx);
					  fclose(fx);
					  printf("\n�Է�����\n");
					  printf("��Ʒ%c��%d\n",get.goods[0].nam,get.goods[0].q);
					  printf("ȷ��?\n");
					  printf("1.�� 2.��");
					  scanf("%d",&n);
					  getchar();
				  }
				  if(s==10)
				  {
					  fclose(fx);
					  printf("\n�Է�����\n");
					  printf("��\n");
					  printf("ȷ��?\n");
					  printf("1.�� 2.��");
					  scanf("%d",&n);
					  getchar();
				  }
				  if(n==1)
				  {
					  fx = fopen(fileroad,"rb");
					  fread(&s,4,1,fx);
					  fclose(fx);
					  fx = fopen(fileroad,"rb+");
					  s = 10+s;
					  fwrite(&s,4,1,fx);
					  fclose(fx);
					  t1 = clock();
					  printf("��ȴ��Է���10");
					  t2 = clock();
					  ti = 0;
					  while((t2-t1)/1000<=10)
					  {
						  fx = fopen(filename,"rb");
						  if(fx==NULL)
						  {
							  printf("\n�����ѱ�ȡ��\n");
							  s = 9;
							  goto loop4;
						  }
						  fread(&s,4,1,fx);
						  fclose(fx);
						  if(s==9)
						  {
							  printf("\n�����ѱ�ȡ��\n");
							  goto loop4;
						  }
						  if(s>=11)
						  {
							  break;
						  }
						  if((t2-t1)/1000==ti)
						  {
							  printf("\b \b\b \b%2d",10-ti);
							  ti++;
						  }
						  t2 = clock();
					  }
					  printf("\n");
					  if((t2-t1)/1000>10)
					  {
					   goto loop4;
					  }
					  if(s>=11)
					  {
						  if(s==11)
						  {
							  cha.mny += get.mny;
							  printf("�õ����%.0lf\n",get.mny);
						  }
						  if(s==13)
						  {
							  n = cha.t;
							  if(get.goods[0].nam=='a'||get.goods[0].nam=='b'||get.goods[0].nam=='$'||cha.goods[i-1].nam == 'c')
							  {
								  i=0;
								  while(i<=cha.t-1)
								  {
									  if(cha.goods[i].nam==get.goods[0].nam)
									  {
										  break;
									  }
									  i++;
								  }
								  if(i<cha.t)
								  {
									  cha.goods[i].q += get.goods[0].q;
								  }
								  else
								  {
									  cha.goods[n].nam = get.goods[0].nam;
									  cha.goods[n].q = get.goods[0].q;
									  strcpy(cha.goods[n].name,get.goods[0].name);
									  cha.t += 1;
								  }
							  }
							  printf("�õ���Ʒ%c��%d\n",get.goods[0].nam,get.goods[0].q);
						  }
						  t1 = clock();
						  t2 = clock();
						  while((t2-t1)/1000<1)
						  {
							  t2 = clock();
						  }
						  unlink(fileroad);
					  }
				  }
				  else
				  {
                loop4:if(r==1)
					  {
						  cha.mny += give.mny;
					  }
					  if(r==3)
					  {
						  n = cha.t;
						  cha.goods[n].nam = give.goods[0].nam;
						  strcpy(cha.goods[n].name,give.goods[0].name);
						  cha.goods[n].q = give.goods[0].q;
						  cha.t++;
					  }
					  i = g;
					  i++;
				  }
			   }
			  if(i>g)
			  {
				s = 9;
				fx = fopen(fileroad,"rb+");
				fwrite(&s,4,1,fx);
				fclose(fx);
				t1 = clock();
				t2 = clock();
				while((t2-t1)/1000<1)
				{
					t2 = clock();
				}
                loop3:unlink(fileroad);
			  }
			}
			else
			{
				unlink(fileroad);
			}
			return cha;
		}   //k=2
	}      //while
	return cha;
}

void Save(struct CHARACTER cha)
{
    double a[12];
	struct GOODS c[17];
    struct EQUIPMENT b[24];
    int i,p;
    FILE* fp;
	
	fp = fopen(cha.filename,"rb+");
	fread(&p,4,1,fp);
	fseek(fp,(cha.p-1)*size,1);
	fwrite(cha.name,20,1,fp);
	fwrite(cha.prof,20,1,fp);
	fwrite(cha.v,20,1,fp);
	a[0]=(double)cha.grd;
	a[1]=cha.HP;
	a[2]=cha.xHP;
	a[3]=cha.MP;
	a[4]=cha.xMP;
	a[5]=cha.atc;
	a[6]=cha.def;
	a[7]=cha.mny;
	a[8]=cha.exp;
	a[9]=cha.xexp;
	a[10]=(double)cha.t;
	a[11]=(double)cha.e;
	i=0;
	while(i<=16)
	{
		c[i]=cha.goods[i];
		b[i]=cha.equ[i];
		i++;
	}
	while(i<=23)
	{
		b[i]=cha.equ[i];
		i++;
	}
	fwrite(a,8,12,fp);
	fwrite(c,sizeof(struct GOODS),17,fp);
	fwrite(b,sizeof(struct EQUIPMENT),24,fp);
	fclose(fp);
}

void SelePla(struct CHARACTER cha)
{
	FILE* f;
	int k;
	char name[20];
	printf("\n");
	f = fopen(onlinefile,"rb+");
	fseek(f,4L,0);
	k = 1;
	fread(name,20,1,f);
	while(strcmp(act,name)!=0)
	{
		fread(name,20,1,f);
		k++;
		fread(name,20,1,f);
	}
	strcpy(name,"\0");
	fseek(f,4L+k*40L-20L,0);
	fwrite(name,20,1,f);
	fclose(f);
}

void GameOver()
{
	int i,y,k,d;
	FILE* f3;
	FILE* fp;
	char name[20];
	printf("ȷ��?\n");
	printf("1.�� 2.��");
	scanf("%d",&i);
	getchar();
	if(i==1)
	{
		printf("��Ϸ����\n");
		f3 = fopen(onlinefile,"rb");
		fp = fopen(tfile,"wb");
		char ch;
		ch = fgetc(f3);
		while(!feof(f3))
		{
			fputc(ch,fp);
			ch = fgetc(f3);
		}
		fclose(f3);
		fclose(fp);
		f3 = fopen(onlinefile,"wb");
		fp = fopen(tfile,"rb");
		fread(&y,4,1,fp);
		y--;
		fwrite(&y,4,1,f3);
		y++;
		d = 1;
		fread(name,20,1,fp);
		while(strcmp(act,name)!=0)
		{
			fread(name,20,1,fp);
			d++;
			fread(name,20,1,fp);
		}
		fseek(fp,4L,0);
		k = 1;
		while(k<=d-1)
		{
			fread(name,20,1,fp);
			fwrite(name,20,1,f3);
			fread(name,20,1,fp);
			fwrite(name,20,1,f3);
			k++;
		}
		fseek(fp,40L,1);
		while(k<=y-1)
		{
			fread(name,20,1,fp);
			fwrite(name,20,1,f3);
			fread(name,20,1,fp);
			fwrite(name,20,1,f3);
			k++;
		}
		fclose(f3);
		fclose(fp);
		unlink(tfile);
		exit(0);
	}
}

void Printf(struct CHARACTER cha)
{
    int i,k,n,t;
	int des=0;
	
    while(cha.grd<=grade)
	{
     printf("                              //%s//\n\n",cha.v);
	 printf("%s",cha.name);
	 printf("   %d��\n", cha.grd);
	 if(strcmp(cha.v,"����С��")==0||strcmp(cha.v,"�����")==0)
	 {
		cha.HP = cha.xHP;
		cha.MP = cha.xMP;
		des=0;
	 }
	 else
	 {
		des=1;
	 }
	 printf("HP         %.0lf/%.0lf\n", cha.HP, cha.xHP);
	 printf("MP         %.0lf/%.0lf\n", cha.MP, cha.xMP);
	 printf("����       %.2lf%%\n", cha.exp/cha.xexp*100);
	 
	 Save(cha);
	 
	 if (cha.exp>cha.xexp)
	 {
		 cha = Upgrade(cha);
	 }
	 else
	 {
	   if(des==0)
	   {
		printf(" 1.����Ա    2.�̵�    3.�鿴��ɫ    4.�鿴����    5.���߲���\n");
		printf(" 7.������ɫ    8.������Ϸ\n��ѡ��");
	   }
	   if(des==1)
	   {
		printf(" 1.���    2.�س�    3.�鿴��ɫ    4.�鿴����");
	    if(strcmp(cha.v,"��������")==0)
		{
		  printf("    5.��Ӳ���");
		}
	    printf("\n");
	    printf(" 7.������ɫ    8.������Ϸ\n��ѡ��");
	   }
	   scanf("%d", &n);
	   getchar();
	   if(des==0)
	   {
		   if(n==1)
		   {
			   cha = Go(cha);
		   }
		   if(n==2)
		   {
			   t = 0;
			   while(t==0)
			   {
				   printf("�����������������Ҷ�׬�ˣ��ǺǺ�!\n");
				   printf("1.����װ��  2.������Ʒ  3.������Ʒ  4.����װ��\n��ѡ��");
				   scanf("%d", &k);
				   getchar();
				   if(k==1)
				   {
					   printf("������˼��������ֻ��D��װ���ˣ�����Ҫ��һ��\n");
					   cha = BuyEqu(cha);
				   }
				   if(k==2)
				   {
					   cha = BuyGoods(cha);
				   }
				   if(k==3)
				   {
					   cha = Sell(cha);
				   }
				   if(k==4)
				   {
					   cha = MakeEqu(cha);
					   printf("ȷ��");
					   getchar();
					   printf("\n");
				   }
				   if(k!=1&&k!=2&&k!=3&&k!=4)
				   {
					   t = 1;
					   printf("\n");
				   }
			   }
		   }
	   }
	   if(des==1)
	   {
		   if(n==1)
		   {
			   cha = Upgrade(cha);
			   if(cha.n==-1)
			   {
				   cha.n = 0;
				   strcpy(cha.v,"����С��");
				   continue;
			   }
		   }
		   if(n==2)
		   {
			   cha = Go(cha);
		   }
	   }
	   if(n==3)
	   {
		   i = 0;
		   while(i==0)
		   {
			   printf("1.�鿴����  2.�鿴װ��  3.�鿴����\n");
			   printf("��ѡ��");
			   scanf("%d",&k);
			   getchar();
			   if(k==1)
			   {
				   SeeAbi(cha);
			   }
			   if(k==2)
			   {
				   printf("\n");
				   cha.n = 0;
				   cha = SeeEqu(cha);
				   printf("\n");
			   }
			   if(k==3)
			   {
				   SeeSkill(cha);
				   printf("\n");
			   }
			   if(k!=1&&k!=2&&k!=3)
			   {
				   i = 1;
			   }
		   }
	   }
	   if(n==4)
	   {
		   cha = SeeGoods(cha);
		   printf("\n");
	   }
	   if(des==0)
	   {
		   if(n==5)
		   {
			   printf("1.�������\n");
			   printf("��ѡ��");
			   scanf("%d",&k);
			   getchar();
			   if(k==1)
			   {
				   cha = Player(cha);
			   }
		   }
	   }
	   if(des==1)
	   {
		   if(strcmp(cha.v,"��������")==0)
		   {
			   if(n==5)
			   {
				   cha = Group(cha);
			   }
		   }
	   }
	   if(n==7)
	   {
		   SelePla(cha);
		   return;
	   }
	   if(n==8)
	   {
		   GameOver();
	   }
	   if(n!=1&&n!=2&&n!=3&&n!=4&&n!=5&&n!=6&&n!=7&&n!=8)
	   {
		   printf("\n");
	   }
     }
	}
}

void Choice(struct CHARACTER cha)
{
    FILE* fr;
	FILE* f1;
    FILE* f2;
	FILE* f3;
    double a[12];
    struct GOODS c[17];
    struct EQUIPMENT b[24];
	char name[20];
	//char filename[100];
    int k,t=0,d,s,j,i=0;
	int p;
	strcpy(cha.filename,savefolder);
	strcat(cha.filename,act);
	strcat(cha.filename,".ys");
	
    fr = fopen(cha.filename,"rb");
    if(fr==NULL)
	{
     p = 0;
	}
	else
	{
	 fread(&p,4,1,fr);
	 fclose(fr);
	}
    
    while(t==0)
	{
     printf("1.ѡ���ɫ  2.������ɫ  3.ɾ����ɫ  4.������Ϸ\n");
	 printf("��ѡ��");
     scanf("%d",&t);
	 getchar();

     while(t==1)
	 {
	  fr = fopen(cha.filename,"rb");
      if(fr==NULL)
	  {
	   printf("�޽�ɫ\n");
	   printf("\n");
	   t = 0;
	  }
	  else
	  {
	   fread(&p,4,1,fr);
	   j = 1;
	   while(j<=p)
	   {
	    printf("%d.",j);
	    fread(cha.name,20,1,fr);
		fread(cha.prof,20,1,fr);
		fseek(fr,20L,1);
		fread(a,8,12,fr);
		printf("%s    %s  %d��\n",cha.name,cha.prof,(int)a[0]);
		fseek(fr,(size-156),1);
		j++;
	   }
	   printf("��ѡ��");
	   scanf("%d",&d);
	   getchar();
	   if(d<=p && d>=1)
	   {
		f3 = fopen(onlinefile,"rb+");
		fseek(f3,4L,0);
		k = 1;
		fread(name,20,1,f3);
        while(strcmp(act,name)!=0)
		{
		 fread(name,20,1,f3);
		 k++;
		 fread(name,20,1,f3);
		}
		cha.p = d;
		fseek(fr,4L+((d-1)*size),0);
		fread(cha.name,20,1,fr);
		fseek(f3,4L+k*40L-20L,0);
		fwrite(cha.name,20,1,f3);
		fclose(f3);
		fread(cha.prof,20,1,fr);
		fread(cha.v,20,1,fr);
	    fread(a,8,12,fr);
	    fread(c,sizeof(struct GOODS),17,fr);
	    fread(b,sizeof(struct EQUIPMENT),24,fr);
	    cha.grd=(int)a[0];
	    cha.HP=a[1];
	    cha.xHP=a[2];
		cha.MP=a[3];
		cha.xMP=a[4];
	    cha.atc=a[5];
	    cha.def=a[6];
	    cha.mny=a[7];
	    cha.exp=a[8];
	    cha.xexp=a[9];
	    cha.t=(int)a[10];
	    cha.e=(int)a[11];
	    k=0;
	    while(k<=16)
		{
		 cha.goods[k] = c[k];
		 cha.equ[k] = b[k];
		 k++;
		}
		while(k<=23)
		{
		 cha.equ[k] = b[k];
		 k++;
		}
	    fclose(fr);

		cha.trp = 0;
		strcpy(cha.trpname,"\0");
		strcpy(cha.buddy1,"\0");
		strcpy(cha.buddy2,"\0");
		strcpy(cha.buddy3,"\0");
		cha.b1 = '0';
		cha.b2 = '0';
		cha.b3 = '0';

		/*
		if(strcmp(cha.name,"angk")==0)
		{
		 k = cha.t;
		 cha.goods[k].nam = '$';
		 strcpy(cha.goods[k].name,"25��װ��ǿ������");
		 cha.goods[k].q = 2;
		 cha.t++;
		}
		*/

		printf("\n");
	    break;
	   }
	   else
	   {
		fclose(fr);
		printf("\n");
	    t = 0;
	   }
	  }
	 }    //t=1
     
     while(t==2)
	 {
      printf("1.սʿ  2.��ʦ  3.��ʿ\n");
      printf("��ѡ��");
	  scanf("%d",&d);
	  getchar();
	  if(d!=1&&d!=2&&d!=3)
	  {
	   t = 0;
	   break;
	  }
	  if(d==1)
	  {
	   printf("������ɭ�ֵ���ʿ��\n���ڽ����������������\n");
	   printf("�Ƿ�ѡ��\n1.�� 2.��");
	  }
	  if(d==2)
	  {
	   printf("������������ʿ��\n����Զ�̹�����Ⱥ��������ɲ��ᱻ�ִ�\n");
	   printf("�Ƿ�ѡ��\n1.�� 2.��");
	  }
	  if(d==3)
	  {
	   printf("�о���ѧ����ѧ�ߣ�\n�����ٻ����������ٻ�����\n");
	   printf("�Ƿ�ѡ��\n1.�� 2.��");
	  }
	  scanf("%d",&s);
	  getchar();
	  if(s==1)
	  {
		  int o=0;
		  while(o==0)
		  {
			  printf("�������ɫ��:");
			  gets(cha.name);
			  o = 1;
			  if(strlen(cha.name)>=20)
			  {
				  printf("��ɫ������\n\n");
				  o = 0;
			  }
			  if(strlen(cha.name)==0)
			  {
				  printf("������\n\n");
				  o = 0;
			  }
			  if(o==1)
			  {
				  k = 0;
				  while(k<=strlen(cha.name)-1)
				  {
					  if(cha.name[k]!=' ')
					  {
						  break;
					  }
					  k++;
				  }
				  if(k==strlen(cha.name))
				  {
					  printf("��ɫ�����Ϸ�\n\n");
					  o = 0;
				  }
			  }
			  int h;
			  f1 = fopen(namefile,"rb+");
			  if(f1==NULL)
			  {
				  f1 = fopen(namefile,"wb");
				  h = 0;
				  fwrite(&h,4,1,f1);
				  fclose(f1);
				  f1 = fopen(namefile,"rb+");
			  }
			  fread(&h,4,1,f1);
			  for(int x=1;x<=h;x++)
			  {
				  fread(name,20,1,f1);
				  if(strcmp(cha.name,name)==0)
				  {
					  printf("��ɫ���Ѵ���\n\n");
					  o = 0;
					  break;
				  }
			  }
			  if(o==1)
			  {
				  fclose(f1);
				  f1 = fopen(namefile,"ab");
				  fwrite(cha.name,20,1,f1);
				  fclose(f1);
				  f1 = fopen(namefile,"rb+");
				  h += 1;
				  fwrite(&h,4,1,f1);
			  }
			  fclose(f1);
		  }
		  p += 1;
		  fr = fopen(cha.filename,"rb");
		  if(fr==NULL)
		  {
			  fr = fopen(cha.filename,"wb");
			  fwrite(&p,4,1,fr);
		  }
		  else
		  {
			  if(p==6)
			  {
				  printf("��ɫ������\n");
				  printf("ȷ��");
				  getchar();
				  fclose(fr);
				  t = 0;
				  printf("\n");
				  break;
			  }
			  fclose(fr);
			  fr = fopen(cha.filename,"rb+");
			  fwrite(&p,4,1,fr);
			  fclose(fr);
			  fr = fopen(cha.filename,"ab");
		  }
		  if(d==1)
		  {
			  fwrite(cha.name,20,1,fr);
			  strcpy(cha.prof,"սʿ");
			  fwrite(cha.prof,20,1,fr);
			  strcpy(cha.v,"����С��");
			  fwrite(cha.v,20,1,fr);
			  cha.grd = 1;
			  cha.xHP = 19;
			  cha.HP = 19;
			  cha.xMP = 3;
			  cha.MP = 3;
			  cha.atc = 5;
			  cha.def = 3;
			  cha.mny = 0;
		  }
		  if(d==2)
		  {
			  fwrite(cha.name,20,1,fr);
			  strcpy(cha.prof,"��ʦ");
			  fwrite(cha.prof,20,1,fr);
			  strcpy(cha.v,"����С��");
			  fwrite(cha.v,20,1,fr);
			  cha.grd = 1;
			  cha.xHP = 5;
			  cha.HP = 5;
			  cha.xMP = 20;
			  cha.MP = 20;
			  cha.atc = 2;
			  cha.def = 3;
			  cha.mny = 0;
		  }
		  if(d==3)
		  {
			  fwrite(cha.name,20,1,fr);
			  strcpy(cha.prof,"��ʿ");
			  fwrite(cha.prof,20,1,fr);
			  strcpy(cha.v,"����С��");
			  fwrite(cha.v,20,1,fr);
			  cha.grd = 1;
			  cha.xHP = 12;
			  cha.HP = 12;
			  cha.xMP = 11;
			  cha.MP = 11;
			  cha.atc = 3.5;
			  cha.def = 3;
			  cha.mny = 0;
		  }
		  i = 0; 
		  while(i<=23)
		  {
			  cha.equ[i].grd = 0;
			  strcpy(cha.equ[i].name,"\0");
			  strcpy(cha.equ[i].kind,"\0");
			  cha.equ[i].rank = ' ';
			  cha.equ[i].axHP = 0;
			  cha.equ[i].axMP = 0;
			  cha.equ[i].aatc = 0;
			  cha.equ[i].adef = 0;
			  i++;
		  }
		  cha.xexp = 10;
		  cha.exp = 0;
		  i = 0;
		  while(i<=16)
		  {
			  cha.goods[i].nam = '\0';
			  strcpy(cha.goods[i].name,"\0");
			  cha.goods[i].q = 0;
			  i++;
		  }
		  cha.t = 0;
		  cha.e = 7;
		  
		  a[0]=(double)cha.grd;
		  a[1]=cha.HP;
		  a[2]=cha.xHP;
		  a[3]=cha.MP;
		  a[4]=cha.xMP;
		  a[5]=cha.atc;
		  a[6]=cha.def;
		  a[7]=cha.mny;
		  a[8]=cha.exp;
		  a[9]=cha.xexp;
		  a[10]=(double)cha.t;
		  a[11]=(double)cha.e;
		  i=0;
		  while(i<=16)
		  {
			  c[i]=cha.goods[i];
			  b[i]=cha.equ[i];
			  i++;
		  }
		  while(i<=23)
		  {
			  b[i]=cha.equ[i];
			  i++;
		  }
		  
		  fwrite(a,8,12,fr);
		  fwrite(c,sizeof(struct GOODS),17,fr);
		  fwrite(b,sizeof(struct EQUIPMENT),24,fr);
		  fclose(fr);
		  
		  printf("�����ɹ�\n");
		  printf("ȷ��");
		  getchar();
		  printf("\n");
		  t = 0;
	  }
	  else
	  {
		   printf("\n");
		   t = 2;
	  }
	 }      //t=2

	 while(t==3)
	 {
	  fr = fopen(cha.filename,"rb");
      if(fr==NULL)
	  {
	   printf("�޽�ɫ\n");
	   printf("\n");
	   t = 0;
	  }
	  else
	  {
	   fread(&p,4,1,fr);
	   j = 1;
	   while(j<=p)
	   {
	    printf("%d.",j);
	    fread(cha.name,20,1,fr);
	    puts(cha.name);
		fseek(fr,(size-20),1);
		j++;
	   }
	   printf("��ѡ��");
	   scanf("%d",&d);
	   getchar();
	   if(d<=p && d>=1)
	   {
	    printf("ȷ��ɾ��?\n");
        printf("1.ȷ�� 2.ȡ��");
		scanf("%d",&s);
		if(s==1)
		{
         p -= 1;
		 if(p==0)
		 {
		  strcpy(name,cha.name);
		  fclose(fr);
		  unlink(cha.filename);
		  t = 3;
		 }
		 else
		 {
		  FILE* fp;
		  fp = fopen(tfile,"wb");
		  rewind(fr);
		  char ch;
		  ch = fgetc(fr);
		  while(!feof(fr))
		  {
		   fputc(ch,fp);
		   ch = fgetc(fr);
		  }
		  fclose(fp);
		  fclose(fr);
		  fr = fopen(cha.filename,"wb");
		  fp = fopen(tfile,"rb");
		  fwrite(&p,4,1,fr);
		  fseek(fp,4L,0);
		  int z=1;
		  while(z<=d-1)
		  {
		   fread(cha.name,20,1,fp);
		   fread(cha.prof,20,1,fp);
		   fread(cha.v,20,1,fp);
	       fread(a,8,12,fp);
	       fread(c,sizeof(struct GOODS),17,fp);
	       fread(b,sizeof(struct EQUIPMENT),24,fp);
		   fwrite(cha.name,20,1,fr);
		   fwrite(cha.prof,20,1,fr);
		   fwrite(cha.v,20,1,fr);
		   fwrite(a,8,12,fr);
		   fwrite(c,sizeof(struct GOODS),17,fr);
		   fwrite(b,sizeof(struct EQUIPMENT),24,fr);
		   z++;
		  }
		  fread(name,20,1,fp);
          fseek(fp,4L+(d*size),0);
		  while(z<=p)
		  {
		   fread(cha.name,20,1,fp);
		   fread(cha.prof,20,1,fp);
		   fread(cha.v,20,1,fp);
	       fread(a,8,12,fp);
	       fread(c,sizeof(struct GOODS),17,fp);
	       fread(b,sizeof(struct EQUIPMENT),24,fp);
		   fwrite(cha.name,20,1,fr);
		   fwrite(cha.prof,20,1,fr);
		   fwrite(cha.v,20,1,fr);
		   fwrite(a,8,12,fr);
		   fwrite(c,sizeof(struct GOODS),17,fr);
		   fwrite(b,sizeof(struct EQUIPMENT),24,fr);
		   z++;
		  }
		  fclose(fp);
		  fclose(fr);
		  unlink(tfile);
		 }
		 int h,g;
		 char nam[20];
		 f1 = fopen(namefile,"rb");
		 FILE* fp;
		 fp = fopen(tfile,"wb");
		 fread(&h,4,1,f1);
		 for(int x=1;x<=h;x++)
		 {
		  fread(nam,20,1,f1);
		  if(strcmp(name,nam)==0)
		  {
		   g = x;
		   break;
		  }
		 }
         rewind(f1);
		 char ch;
		 ch = fgetc(f1);
		 while(!feof(f1))
		 {
		   fputc(ch,fp);
		   ch = fgetc(f1);
		 }
		 fclose(fp);
		 fclose(f1);
		 f1 = fopen(namefile,"wb");
		 fp = fopen(tfile,"rb");
		 h -= 1;
		 fwrite(&h,4,1,f1);
		 fseek(fp,4L,0);
		 x = 1;
		 while(x<=g-1)
		 {
		  fread(name,20,1,fp);
		  fwrite(name,20,1,f1);
		  x++;
		 }
		 fseek(fp,4L+g*20L,0);
		 while(x<=h)
		 {
		  fread(name,20,1,fp);
		  fwrite(name,20,1,f1);
		  x++;
		 }
		 fclose(fp);
		 fclose(f1);
		 unlink(tfile);
		 printf("\n");
		}    //s=1
		else
		{
		 fclose(fr);
		 t = 3;
		}
	   }    //d
	   else
	   {
	    fclose(fr);
		t = 0;
	   }
	  }
	 }
     
	 if(t==4)
	 {
	  GameOver();
	  t=0;
	  printf("\n");
	 }

	 while(t!=1 && t!=2 && t!=3 && t!=4)
	 {
	  t = 0;
	  break;
	 }
	}
	Printf(cha);
}

int cqmain(char loginname[20])
{
	strcpy(act,loginname);
    struct CHARACTER cha;
	srand(time(NULL));
	while(1)
	{
		Choice(cha);
	}
	return 0;
}

struct USERINFO Pwd(void)
{
 struct USERINFO pwd;
 char c;
 int i=0,k=0;
 while(i<=19)
 {
  pwd.userpwd[i] = '\0';
  i++;
 }
 i=0;
 while(i<=19)
   {
    c = getch();
    if(c=='\b') //�˸�ɾ��
	{
	 if(i!=0)
	 {
	  printf("\b \b");
	  if(i>0)
	  {
	   pwd.userpwd[i-1] = '\0';
	   i--;
	  }
	 }
	}
	if(c=='\r'||c==9)  //�س�ʱ����
	{
	 break;
	}
	if(i!=19)
	{
	 if(c!='\b'&&c!='\r')
	 {
	  pwd.userpwd[i] = c;
	  printf("*");
	  i++;
	 }
	}
   }
 printf("\n");
 return pwd;
}

bool Register(struct USERINFO newu)                  //ע��
{
 struct USERINFO pwd;
 struct USERINFO chg;
 int i=0,l;
 if(CurCounts==100)
 {
  printf("                 ע��������\n\n");
  return false;
 }
 printf("                 ����дҪע����ʺź�����\n");
 printf("                 �ʺ�:");
 gets(newu.username);
 if(newu.username[0]<'a'||newu.username[0]>'z')
 {
  printf("                 �ʺ���λ��ΪСд��ĸ\n\n");
  return false;
 }
 l = strlen(newu.username);
 if(l<6)
 {
  printf("                 �ʺŲ�������6λ\n\n");
  return false;
 }
 while(i<=CurCounts-1)
 {
  if(strcmp(newu.username,USER[i].username)==0)
  {
   printf("                 �û��Ѵ���\n\n");
   return false;
  }
  i++;
 }
 for(i=0;i<=l-1;i++)
 {
  if((newu.username[i]<'a'||newu.username[i]>'z')&&(newu.username[i]<'0'||newu.username[i]>'9'))
  {
   printf("                 �ʺ��в����������ַ�\n\n");
   return false;
  }
 }
 if(strlen(newu.username)>=20)
 {
  printf("                 �ʺŹ���\n\n");
  return false;
 }
 printf("                 ��\n");

 printf("                 ����:");
 pwd = Pwd();
 strcpy(newu.userpwd,pwd.userpwd);
 l = strlen(newu.userpwd);
 if(l<6)
 {
  printf("                 ���벻������6λ\n\n");
  return false;
 }
 if(l>=20)
 {
  printf("                 �������\n\n");
  return false;
 }
 for(i=0;i<=l-1;i++)
 {
  if((newu.userpwd[i]<'a'||newu.userpwd[i]>'z')&&(newu.userpwd[i]<'0'||newu.userpwd[i]>'9')&&
	  (newu.userpwd[i]<'A'||newu.userpwd[i]>'Z'))
  {
   printf("                 �����в����������ַ�\n\n");
   return false;
  }
 }
 printf("                 ��\n");
 printf("                 ��������һ��\n");
 printf("                 ����:");
 chg = Pwd();
 if(strcmp(chg.userpwd,pwd.userpwd)!=0)
 {
  printf("                 ���벻һ��\n\n");
  return false;
 }
 for(i=0;i<=strlen(newu.userpwd)-1;i++)
 {
  newu.userpwd[i] += jiami[i];
 }
 printf("                 ��\n");

 printf("                 ע��ɹ�\n\n");
 USER[CurCounts] = newu;
 CurCounts++;
 FILE *f1;
 f1 = fopen(accountfile,"wb");
 fwrite(&CurCounts,4,1,f1);
 fwrite(USER,sizeof(struct USERINFO),CurCounts,f1);
 fclose(f1);
 return true;
}

bool Login(struct USERINFO login)                //��¼
{
 struct USERINFO pwd;
 char act[20];
 char name[20];
 int i=0,t,k;
 printf("                 ������\n");
 printf("                 �ʺ�:");
 gets(login.username);
 while(i<=CurCounts-1)
 {
  if(strcmp(login.username,USER[i].username)==0)
  {
   break;
  }
  i++;
 }
 if(i==CurCounts)
 {
  printf("                 �ʻ�������\n\n");
  return false;
 }

 printf("                 ����:");
 pwd = Pwd();
 strcpy(login.userpwd,pwd.userpwd);
 for(k=0;k<=strlen(login.userpwd)-1;k++)
 {
  login.userpwd[k] += jiami[k];
 }
 if(strcmp(login.userpwd,USER[i].userpwd)!=0)
 {
  printf("                 �������\n\n");
  return false;
 }
 i = 1;
 FILE *f3;
 f3 = fopen(onlinefile,"rb+");
 if(f3!=NULL)
 {
  fread(&t,4,1,f3);
  while(i<=t)
  {
   fread(act,20,1,f3);
   if(strcmp(act,login.username)==0)
   {
    printf("                 ���˺����ڵ�¼��\n\n");
	fclose(f3);
	return false;
   }
   fseek(f3,20L,1);
   i++;
  }
  t++;
  rewind(f3);
  fwrite(&t,4,1,f3);
  fclose(f3);
  f3 = fopen(onlinefile,"ab");
  fwrite(login.username,20,1,f3);
  strcpy(name,"\0");
  fwrite(name,20,1,f3);
  fclose(f3);
 }
 if(f3==NULL)
 {
  f3 = fopen(onlinefile,"wb");
  t = 1;
  fwrite(&t,4,1,f3);
  fwrite(login.username,20,1,f3);
  strcpy(name,"\0");
  fwrite(name,20,1,f3);
  fclose(f3);
 }
 printf("                               ��¼�ɹ�\n\n");
 cqmain(login.username);
 return true;
}

void main()
{
 printf("              *         *                                *                  \n");
 printf("             *          *                                *                  \n");
 printf("            *     * * * * * * *               * * * * * * * * * * * *       \n");
 printf("           *           *                               *   *                \n");
 printf("         *             *                          * *         *  *          \n");
 printf("       *  * * * * * * * * * * * * * *    * * * * * * * * * * * * * * * * * *\n");
 printf("    *     *           *                                         *           \n");
 printf("          *          *                                          *           \n");
 printf("          *         * * * * * **                 * * * * * *    *           \n");
 printf("          *                    *                 *         *    *           \n");
 printf("          *         *        *                   *         *    *           \n");
 printf("          *           *    *                     * * * * * *    *           \n");
 printf("          *             **                                      *           \n");
 printf("          *               *                                  *  *           \n");
 printf("          *                *                                   **           \n");
 char version[10]=ver;
 printf("  v%s                                             Copyright 2013-2016 Yuer\n\n",version);
 printf("                                                                  40������\n\n");
 //ʼ����2013��4��16��
 _mkdir(storyfolder);        //�����ļ���
 _mkdir(savefolder);        //�����ļ���

 struct USERINFO use;
 FILE *f1;
 f1 = fopen(accountfile,"rb");
 if(f1==NULL)
 {
  CurCounts=0;
  f1 = fopen(accountfile,"wb");
  fwrite(&CurCounts,4,1,f1);
  fclose(f1);
 }
 else
 {
  fread(&CurCounts,4,1,f1);
  fread(USER,sizeof(struct USERINFO),CurCounts,f1);
  fclose(f1);
 }
 int i,n,t=0;
 bool del;
 while(t==0)
 {
  printf("                               1.��¼��Ϸ\n");
  printf("                               2.ע���˺�\n");
  printf("                               3.�˳���Ϸ\n");
  printf("                               ��ѡ��");
  scanf("%d",&n);
  getchar();
  if(n==1)
  {
	t=1;
	while(t==1)
	{
		del = Login(use);
		if(!del)
		{
		 printf("                 �Ƿ������\n");
		 printf("                 1.����  2.�˳�");
		 scanf("%d",&i);
		 getchar();
		 printf("\n");
		 if(i!=1)
		 {
		  printf("\n");
		  t=0;
		 }
		}
		else
		{
		 t=2;
		}
	}
  }
  if(n==2)
  {
	t=1;
	while(t==1)
	{
		del = Register(use);
		if(!del)
		{
		 printf("                 �Ƿ������\n");
		 printf("                 1.����  2.�˳�");
		 scanf("%d",&i);
		 getchar();
		 printf("\n");
		 if(i!=1)
		 {
		  printf("\n");
		  t=0;
		 }
		}
		else
		{
		 printf("\n");
		 t=0;
		}
	}
  }
  if(n==3)
  {
	   printf("                               ȷ���˳�?\n");
       printf("                               1.��  2.��");
	   scanf("%d",&i);
	   getchar();
	   if(i==1)
	   {
		   printf("                               ��Ϸ���˳�\n");
		   exit(0);
	   }
	   if(i!=1)
	   {
	    printf("\n");
	   }
  }
  if(n!=1&&n!=2&&n!=3)
  {
   printf("\n");
  }
 }
}