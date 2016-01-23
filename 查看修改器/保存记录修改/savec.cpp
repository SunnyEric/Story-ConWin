#include<stdio.h>
#include<string.h>

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

struct CHARACTER
{
	char name[20];               // ����
	int grd;				   	 // �ȼ�
	char prof[20];               // ְҵ
	double xHP;	      	         // Ѫ����
	double HP;
	double xMP;                  // ������
	double MP;
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
	int n,m;                     // ��ʱ����
	char filename[100];          // �ļ�
	int p;                       // ��ɫ��
};

void main()
{
	struct CHARACTER cha;
	double a[12];
	struct GOODS c[17];
	struct EQUIPMENT b[24];
 
	int i,k,p;
	FILE* fr;
	FILE* fp;
	//printf("%d\n",sizeof(struct GOODS));    //28
	//printf("%d\n",sizeof(struct EQUIPMENT));    //80
	
	fr = fopen("aaaaaa.ys","rb");
	fp = fopen("1.ys","wb");
	fread(&p,4,1,fr);
	fwrite(&p,4,1,fp);

	i=1;
	while(i<=p)
	{
	fread(cha.name,20,1,fr);
	fread(cha.prof,20,1,fr);
	fread(cha.v,20,1,fr);
	fread(a,8,12,fr);
	fread(c,sizeof(struct GOODS),17,fr);
	fread(b,sizeof(struct EQUIPMENT),24,fr);

	for(k=0;k<=16;k++)
	{
		strcpy(c[k].name,"\0");
		c[k].nam='\0';
		c[k].q = 0;
	}

	for(k=0;k<=23;k++)
	{
		strcpy(b[k].name,"\0");
		strcpy(b[k].kind,"\0");
		b[k].grd = 0;
		b[k].rank = ' ';
		b[k].axHP = 0;
		b[k].axHP = 0;
		b[k].aatc = 0;
		b[k].adef = 0;
	}

	fwrite(cha.name,20,1,fp);
	fwrite(cha.prof,20,1,fp);
	fwrite(cha.v,20,1,fp);
	fwrite(a,8,12,fp);
	fwrite(c,sizeof(struct GOODS),17,fp);
	fwrite(b,sizeof(struct EQUIPMENT),24,fp);
	i++;
	}

	fclose(fr);
	fclose(fp);
}