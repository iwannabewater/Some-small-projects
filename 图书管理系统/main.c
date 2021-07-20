#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct student
{
    char name[10];//�û���
    char id[10];//�˺�
    char password[8];//����
    char type[10];//����
    struct student *next;
};
typedef struct student lnode, *linklist;

struct book
{
    int  id;
	char name[20];
	char author[20];
	char publisher[20];
	char type[20];
	int pubtime;
	int price;
	int Num;
    struct book *next;
};
typedef struct book LNode, *LinkList;

void load(LinkList head,linklist head1);//���ļ��е���Ϣ���ص������еĺ���
void test(linklist k,char str1[],char str2[]);//�����˺���Ϣ����
void librarian(LinkList head, linklist head1);//ͼ�����Ա����
void SMS (linklist head1);//�û�������
void print(linklist head1);//������ж����˺���Ϣ
void printsms(linklist head1);
void printread(linklist head1);
void addread(linklist head1);//��Ӷ����˺���Ϣ
void addallread(linklist head1);//������Ӷ�����Ϣ
void save(linklist head1);//�������˺�д���ļ�
void deleteread(linklist head1);//ɾ�������˺�
void deleteallread(linklist head1);//����ɾ��������Ϣ
void change(linklist head1);//���õ����û�����

void information(LinkList head);//ͼ����Ϣ������
void newbook(LinkList head);//�������
void allinput(LinkList head);//��������
void Input(LinkList head);//��������
void Save(LinkList head);//��ͼ����Ϣд���ļ���
void Output(LinkList head);//���ͼ����Ϣ
void Sort(LinkList head);//ͼ������
void oldbook(LinkList head);//�����¼�
void titledelete(LinkList head);//������ɾ��
void timedelete(LinkList head);//������ʱ��ɾ��
void modify(LinkList head);//ͼ����Ϣ�޸�

void reader(LinkList head,linklist head1);//��ͨ���ߺ���
void password(linklist head1);//���߸�������
void query(LinkList head);//��ѯͼ����Ϣ
void borrow(LinkList head);//����ͼ��
void titlequery(LinkList head);//��������
void authorquery(LinkList head);//����������
void pressquery(LinkList head);//���������
void titleauthor(LinkList head);//��������������ѯ
int compare(char k[],char m[], char n[], char str[], char password[]);
int select, b=0;
LinkList head;
linklist head1;

int main()
{
    system("color 3a");
    head1=(linklist)malloc(sizeof(lnode));
    head=(LinkList)malloc(sizeof(LNode));
    head1->next=NULL;
    head->next=NULL;
    load(head,head1);
    char str1[10],str2[10];
    linklist k=head1->next;
    while(1)
    {
        printf("***************************************************\n");
        printf("*               ��ӭ����ͼ�����ϵͳ              *\n");
        printf("***************************************************\n\n");
        printf("�������û�����������˺ź����룺\n");
        printf("�û������˺ţ�");
        scanf("%s",str1);
        printf("���룺");
        scanf("%s",str2);
        test(k,str1,str2);
    }
   return 0;
}
void load(LinkList head,linklist head1)
{
    LinkList p,rear=head;
	char name[20],author[20],publisher[20],type[20];
	int id, pubtime,price,Num;
    FILE *fp;
    if((fp=fopen("bookinfo.txt","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}

	while(fscanf(fp,"%d%s%s%s%s%d%d%d",&id,name,author,publisher,type,&pubtime,&price,&Num)!=EOF)
    {
      p=(LinkList)malloc(sizeof(LNode));
	  p->id=id;
	  strcpy(p->name,name);
	  strcpy(p->author,author);
	  strcpy(p->publisher,publisher);
	  strcpy(p->type,type);
	  p->pubtime=pubtime;
	  p->price=price;
      p->Num=Num;
	  rear->next=p;
	  rear=p;
    }
    rear->next=NULL;
    linklist q, rear1=head1;
	char name1[10],ID[10], password[10],type1[10];
    if((fp=fopen("userinfo.txt","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}
	while(fscanf(fp,"%s %s %s %s",name1,ID, password,type1)!=EOF)
    {
      q=(linklist)malloc(sizeof(lnode));
      strcpy(q->name,name1);
	  strcpy(q->id,ID);
	  strcpy(q->password,password);
	  strcpy(q->type,type1);
	  rear1->next=q;
	  rear1=q;
    }
    rear1->next=NULL;
}

void test(linklist k,char str1[],char str2[])
{
    while(k)
        {
            b=0;
            b=compare(k->name,k->id,k->password,str1,str2);
            if(b==1)
            {
               if(strcmp(k->type,"����Ա")==0)
               {
                   librarian(head, head1);//ͼ�����Ա����
               }
               if(strcmp(k->type,"�û�")==0)
               {
                   reader(head, head1);//��ͨ���ߺ���
               }
               break;
            }
            k=k->next;
        }
        int b1;
        while(b!=1)
        {
            printf("������Ϣ�����˳��밴0���ٴ����밴1��\n");
            scanf("%d",&b1);
            if(b1==1)
            {
                printf("������������Ϣ��\n");
                printf("�û������˺ţ�");
                scanf("%s",str1);
                printf("���룺");
                scanf("%s",str2);
                k=head1->next;
                while(k)
                {
                    b=0;
                    b=compare(k->name,k->id,k->password,str1,str2);
                    if(b==1)
                    {
                        if(strcmp(k->type,"����Ա")==0)
                        {
                            librarian(head, head1);//ͼ�����Ա����
                        }
                        if(strcmp(k->type,"�û�")==0)
                        {
                            reader(head, head1);//��ͨ���ߺ���
                        }
                        break;
                    }
                    k=k->next;
                }
            }
            else
                exit(0);
        }
}

int compare(char k[],char m[], char n[], char str[], char password[])
{
    if((strcmp(str,k)==0||strcmp(str,m)==0)&&(strcmp(password,n)==0))
    {
        printf("������Ϣ��ȷ,��������ϵͳ\n\n");
        return 1;
    }

    return 0;
}

void librarian(LinkList head, linklist head1)//ͼ�����Ա����
{
    do{
    printf("******************************************\n");
    printf("*             1:�û�����                 *\n");
    printf("*             2:ͼ����Ϣ����             *\n");
    printf("*             3:�˳�                     *\n");
    printf("******************************************\n\n");
    printf("��������Ҫ���е���Ŀѡ��\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            SMS (head1);//�û�������
            break;
        case 2:
            information(head);//ͼ����Ϣ������
            break;
    }}while(select!=3);
}

void SMS(linklist head1)//�û�������
{
    do{
    printf("************************************\n");
    printf("*        1:��������˺�            *\n");
    printf("*        2:��������˺�            *\n");
    printf("*        3:����ɾ���˺�            *\n");
    printf("*        4:����ɾ���˺�            *\n");
    printf("*        5:��������˺�            *\n");
    printf("*        6:���õ����û�����        *\n");
    printf("*        7:�˳�                    *\n");
    printf("************************************\n\n");
    printf("��������Ҫ���е���Ŀѡ��\n");
    scanf("%d", &select);

    switch(select)
    {
        case 1:
            addread(head1);//�������
            break;
        case 2:
            addallread(head1);//�������
            break;
        case 3:
            deleteread(head1);//ɾ�������˺�
            break;
        case 4:
            deleteallread(head1);//����ɾ��
            break;
        case 5:
            print(head1);//���������Ϣ
            break;
        case 6:
            change(head1);//���õ����û�����
            break;
        default:return;
    }}while(select!=7);
}
void print(linklist head1)//��ʾ���ж�����Ϣ
{
    do{
    printf("************************************\n");
    printf("*        1:�������Ա�˺�            *\n");
    printf("*        2:����û��˺�              *\n");
    printf("*        3:�˳�                    *\n");
    printf("************************************\n\n");
    printf("��������Ҫ���е���Ŀѡ��\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            printsms(head1);//�������
            break;
        case 2:
            printread(head1);//�������
            break;
        default:return;
    }}while(select!=3);
}
void printsms(linklist head1)
{
    linklist q=head1->next;
    int i=0;
    while(q)
    {
        if(strcmp(q->type,"����Ա")==0)
        {
            printf("%s %s %s\n",q->name,q->id,q->password);
            i++;
        }
        q=q->next;
    }
    if(i==0)
        printf("û�й���Ա��Ϣ��");
}
void printread(linklist head1)
{
    linklist q=head1->next;
    int i=0;
    while(q)
    {
        if(strcmp(q->type,"�û�")==0)
        {
            printf("%s %s %s\n",q->name,q->id,q->password);
            i++;
        }
        q=q->next;
    }
    if(i==0)
    {
        printf("û���û���Ϣ��");
    }
    return;
}
void addread(linklist head1)
{
    linklist p,rear=head1;
    char name[10];
    char id[20];
    char password[20];
    char type[10];
    FILE *fp;
    if((fp=fopen("userinfo.dat","r+"))==NULL)
    {
        printf("File Open Error!\n");
        exit(0);
    }

    while(fscanf(fp,"%s %s %s %s",name,id,password,type)!=EOF)
        {
            p=(linklist)malloc(sizeof(lnode));
            strcpy(p->name,name);
            strcpy(p->id,id);
            strcpy(p->password,password);
            strcpy(p->type,type);
            rear->next=p;
            rear=p;
        }
    printf("�����������û������˺š�������������#��ʾ�������\n");
    printf("����ʾ�������� 1 111111 �û�\n");
        while(scanf("%s",name)!=EOF&&strcmp(name,"#")!=0)
        {
            p=(linklist)malloc(sizeof(lnode));
            scanf("%s",id);
            scanf("%s",password);
            scanf("%s",type);
            strcpy(p->name,name);
            strcpy(p->id,id);
            strcpy(p->password,password);
            strcpy(p->type,type);
            rear->next=p;
            rear=p;
        }
        rear->next=NULL;
        printf("������ͨ�����û���Ϣ:\n");
        printread(head1);
        save(head1);
}

void addallread(linklist head1)
{
    linklist p,rear=head1;
	char name[10],id[20],password[20],type[10];
    FILE *fp;

    if((fp=fopen("userinfo.dat","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}

	while(fscanf(fp,"%s %s %s %s",name,id,password,type)!=EOF)
    {
      p=(linklist)malloc(sizeof(lnode));
      strcpy(p->name,name);
	  strcpy(p->id,id);
	  strcpy(p->password,password);
	  strcpy(p->type,type);
	  rear->next=p;
	  rear=p;
    }
    if((fp=fopen("��������ӵĶ����˺�����.txt","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}

	while(fscanf(fp,"%s %s %s %s",name,id,password,type)!=EOF)
    {
      p=(linklist)malloc(sizeof(lnode));
      strcpy(p->name,name);
	  strcpy(p->id,id);
	  strcpy(p->password,password);
	  strcpy(p->type,type);
	  rear->next=p;
	  rear=p;
    }
    rear->next=NULL;
    save(head1);
    printf("����ӵĶ�����Ϣ���������룡\n");
    printf("��ǰ������ϢΪ��\n");
    printread(head1);
}
void deleteread(linklist head1)//ɾ�������˺�
{
    printf("�������ɾ���Ķ����û������˺���Ϣ\n");
    linklist p=head1,pre;
    char Delete[20];
    int flag=0;
    scanf("%s",Delete);
    while(p)
    {
        pre=p;
        p=p->next;
        if(p)
        {
                if(strcmp(Delete,p->name)==0||strcmp(Delete,p->id)==0)
                {
                    printf("��ɾ���Ķ�����ϢΪ��\n");
                    printf("%s %s %s %s\n",p->name,p->id,p->password,p->type);
                    pre->next=p->next;
                    flag=1;
                    free(p);
                    printf("������Ϣ��ɾ��\n");
                }
        }

    }
    if(flag==0)
    {

        printf("���޶�����Ϣ���޷�ɾ��\n");

    }
    save(head1);
}
void deleteallread(linklist head1)
{
    linklist p,rear=head1,pre,q;
    char name[10],str[10],id[20],password[20],type[10];
    FILE *fp;
    if((fp=fopen("userinfo.dat","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}
	while(fscanf(fp,"%s %s %s %s",name,id,password,type)!=EOF)
    {
      p=(linklist)malloc(sizeof(lnode));
      strcpy(p->name,name);
	  strcpy(p->id,id);
	  strcpy(p->password,password);
	  strcpy(p->type,type);
	  rear->next=p;
	  rear=p;
    }
    rear->next=NULL;
    if((fp=fopen("������ɾ�������˺�����.txt","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}
    while(fscanf(fp,"%s",str)!=EOF)
    {
        pre=head1;
        q=pre;
        pre=pre->next;
      while(pre)
      {
          if(strcmp(pre->name,str)==0||strcmp(pre->id,str)==0)
          {
              q->next=pre->next;
              break;
          }
          q=pre;
          pre=pre->next;
      }
    }
    printf("������ɾ��������Ϣ\n");
    printf("��ǰ������ϢΪ��\n");
    printread(head1);
    save(head1);
}

void change(linklist head1)
{
    linklist p=head1->next;
    char str[10];
    int flag=0;
    printf("������Ҫ����������û������˺ţ�\n");
    scanf("%s",str);
    while(p)
    {
        if(strcmp(p->type,"�û�")==0)
        {
            if(strcmp(p->name,str)==0||strcmp(p->id,str)==0)
            {
                printf("�������������룺\n");
                scanf("%s",p->password);
                printf("�������û����룡\n");
                flag=1;
            }
        }
       p=p->next;
    }
    if(flag==0)
    {
        printf("δ�ҵ���Ӧ���û������˺ţ�\n");
    }
    printf("��ǰ������ϢΪ��\n");
    printread(head1);
    save(head1);
}
void save(linklist head1)
{
    FILE *fp;
    linklist p;
    if((fp=fopen("userinfo.dat","w"))==NULL)
    {
        printf("File Open Error!\n");
        exit(0);
    }
    for(p=head1->next;p;p=p->next)
        {
            fprintf(fp,"%s %s %s %s\n",p->name,p->id,p->password,p->type);
        }
        fclose(fp);
}
void information(LinkList head)//ͼ����Ϣ������
{
      do{
      printf("**********************************************\n");
	  printf("*         ��ӭ����ͼ�����Ա����             *\n");
	  printf("*         1�������ϼ�                        *\n");
	  printf("*         2�����ͼ����Ϣ                    *\n");
	  printf("*         3����ѯ                            *\n");
	  printf("*         4������                            *\n");
	  printf("*         5�������¼�                        *\n");
	  printf("*         6���޸�ͼ����Ϣ                    *\n");
	  printf("*         7���˳�                            *\n");
	  printf("**********************************************\n");

	  printf("     ���������ѡ��\n");
      scanf("%d",&select);

    switch(select)
    {
        case 1:newbook(head);//�����ϼ�
		       break;
	    case 2:Output(head);//ͼ�����
		       break;
	    case 3:query(head);//ͼ�����
		       break;
        case 4:Sort(head);//ͼ������
			   break;
	    case 5:oldbook(head);//�����¼�
		       break;
	    case 6:modify(head);//�޸�ͼ����Ϣ
		       break;

    }}while(select!=7);
}
void newbook(LinkList head)//�������
{
    do{
    printf("******************************************\n");
    printf("*              1:��������                *\n");
    printf("*              2:�������롡����          *\n");
    printf("*              3:�˳�                    *\n");
    printf("******************************************\n\n");
    printf("��������Ҫ���е���Ŀѡ��\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            Input(head);
            break;
        case 2:
            allinput(head);
            break;
        default:return;
    }}while(select!=3);
}

void Input(LinkList head)//�������ͼ����Ϣ
{
	LinkList p,rear=head;
	char name[20],author[20],publisher[20],type[20];
	int id,pubtime,price,Num;
    FILE *fp;

    if((fp=fopen("bookinfo.dat","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}

	while(fscanf(fp,"%d%s%s%s%s%d%d%d",&id,name,author,publisher,type,&pubtime,&price,&Num)!=EOF)
    {
      p=(LinkList)malloc(sizeof(LNode));
	  p->id=id;
	  strcpy(p->name,name);
	  strcpy(p->author,author);
	  strcpy(p->publisher,publisher);
	  strcpy(p->type,type);
	  p->pubtime=pubtime;
	  p->price=price;
	  p->Num=Num;
	  rear->next=p;
	  rear=p;
    }

	printf("����������ͼ���š����������ߡ������硢��𡢳��������ա��۸�,����-1��ʾ�������\n");
    printf("����ʾ����201501 ���μ� ��ж� �л�  ���� 19580624 56\n");
    while(scanf("%d",&id),id!=-1)
    {
      p=(LinkList)malloc(sizeof(LNode));
      scanf("%s%s%s%s%d%d%d",name,author,publisher,type,&pubtime,&price,&Num);
	  p->id=id;
	  strcpy(p->name,name);
	  strcpy(p->author,author);
	  strcpy(p->publisher,publisher);
	  strcpy(p->type,type);
	  p->pubtime=pubtime;
	  p->price=price;
	  p->Num=Num;
	  rear->next=p;
	  rear=p;
	}

   rear->next=NULL;
   Save(head);
   printf("���ڵ�ͼ����ϢΪ��\n");
   Output(head);
}
void allinput(LinkList head)//�������ͼ����Ϣ
{
    LinkList p,rear=head;
	char name[20],author[20],publisher[20],type[20];
	int id,pubtime,price,Num;
    FILE *fp;

    if((fp=fopen("bookinfo.dat","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}

	while(fscanf(fp,"%d%s%s%s%s%d%d%d",&id,name,author,publisher,type,&pubtime,&price,&Num)!=EOF)
    {
      p=(LinkList)malloc(sizeof(LNode));
	  p->id=id;
	  strcpy(p->name,name);
	  strcpy(p->author,author);
	  strcpy(p->publisher,publisher);
	  strcpy(p->type,type);
	  p->pubtime=pubtime;
	  p->price=price;
	  p->Num=Num;
	  rear->next=p;
	  rear=p;
    }
    if((fp=fopen("��������ӵ�������Ϣ.txt","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}

	while(fscanf(fp,"%d%s%s%s%s%d%d%d",&id,name,author,publisher,type,&pubtime,&price,&Num)!=EOF)
    {
      p=(LinkList)malloc(sizeof(LNode));
	  p->id=id;
	  strcpy(p->name,name);
	  strcpy(p->author,author);
	  strcpy(p->publisher,publisher);
	  strcpy(p->type,type);
	  p->pubtime=pubtime;
	  p->price=price;
	  p->Num=Num;
	  rear->next=p;
	  rear=p;
    }
    rear->next=NULL;
    Save(head);
    printf("�������������룡\n");
    printf("��ǰͼ����ϢΪ��\n");
    Output(head);
}
void Save(LinkList head)//��ͼ�����Ϣ�����ļ���
{
	FILE *fp;
	LinkList p;

	if((fp=fopen("bookinfo.dat","w"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}
    for(p=head->next;p;p=p->next)
	{
	   fprintf(fp,"%d%10s%10s%10s%10s%10d%8d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
	}
	fclose(fp);
}

void Output(LinkList head)//���ͼ����Ϣ
{
   LinkList p=head->next;

   if(p==NULL)
   {
	   printf("û��ͼ����Ϣ\n");
   }
   else
   {
       printf("���      ����    ����     ������   ��� ���������� �۸�   ���\n");
	   while(p)
	   {
         printf("%d%8s%10s%8s%8s%10d%4d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
         p=p->next;
	   }
   }
}

void Sort(LinkList head)//ͼ�����򣨰���ţ�
{
   LinkList p1=head,p2,q=NULL;
   p2=p1;
   while(p1)
   {
       printf("OK");
       p1=p1->next;
       p2=p1->next;
       while(p2)
       {
           if(p1->id>p2->id)
		   {
		       q=p1;
		       p1=p2;
		       p2=q;
		       printf("xuhaihu ");
		   }
		   p2=p2->next;
       }
    }
   printf("������ͼ����ϢΪ��\n");
   Output(head);
   Save(head);
}

void oldbook(LinkList head)//�����¼�
{
    do{
    printf("************************************\n");
    printf("*         1:������ɾ��             *\n");
    printf("*         2:������ʱ��ɾ��         *\n");
    printf("*         3���˳�                  *\n");
    printf("************************************\n\n");
    printf("      ��������Ҫ���е���Ŀѡ��\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            titledelete(head);//������ɾ��
            break;
        case 2:
            timedelete(head);//������ʱ��ɾ��
            break;
        default:return;
    }}while(select!=3);
}

void titledelete(LinkList head)//������ɾ��
{
    LinkList p1=head,p3=head->next;
    char name[10];
	int  k=0;

	printf("������Ҫɾ��ͼ���������\n");
	scanf("%s",name);
	while(p3)
	{
	    LinkList p2=p3;
		if(strcmp(p2->name,name)==0)
		{
		   k=1;
		   p3=p2->next;
		   p1->next=p2->next;
		   free(p2);
		}
		else
		{
			p1=p3;
			p3=p3->next;
		}
	}
	if(k==0)
	{
		printf("��ͼ����Ϣ������\n");
	}
	if(k==1)
	{
	  printf("ɾ�����ͼ����ϢΪ:\n");
	  Output(head);
	  Save(head);
	}
}

void timedelete(LinkList head)//������ʱ��ɾ��
{
    LinkList p1=head,p3=head->next;
    int pubtime,k=0;

	printf("������Ҫɾ��ͼ��ĳ���ʱ�䣺\n");
	scanf("%d",&pubtime);
	while(p3)
	{
	    LinkList p2=p3;
		if(p2->pubtime<=pubtime)
		{
		  k=1;
		  p3=p2->next;
		  p1->next=p2->next;
		  free(p2);
		}
		else
		{
			p1=p3;
			p3=p3->next;
		}
	}
	if(k==0)
	{
		printf("����������ͼ����Ϣ������\n");
	}
	if(k==1)
	{
		printf("ɾ�����ͼ����ϢΪ:\n");
	    Output(head);
		Save(head);
	}
}

void modify(LinkList head)//ͼ����Ϣ�޸�
{
    int  id,pubtime,price,Num;
	int  flag=0;
	char sel,name[20],author[20],publisher[20],type[20];
    LinkList p;

	printf("������Ҫ�޸�ͼ��ı�ţ�\n");
	scanf("%d",&id);

	if(head==NULL)
	{
		printf("û��ͼ����Ϣ\n");
	}
	for(p=head;p!=NULL;p=p->next)
	{
		if(p->id==id)
		{
			flag=1;
			break;
		}
	}
	if(flag==0)
		printf("ͼ����Ϣ������\n");
	if(flag==1)
	{
		printf("��ͼ�����Ϣ�Ѳ�ѯ������Ϣ���£�\n");
		printf("���      ����    ����     ������    ���    ����������   �۸�   ���\n");
	    printf("%d%8s%10s%8s%10s%10d%8d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
        //�޸�����
		printf("�Ƿ��޸������������� y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("������������\n");
			scanf("%s",name);
			strcpy(p->name,name);;
		}
		//�޸�������
		printf("�Ƿ��޸��������������� y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("��������������\n");
			scanf("%s",author);
			strcpy(p->author,author);
		}
		//�޸ĳ�����
	    printf("�Ƿ��޸ĳ����磬������ y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("����������磺\n");
			scanf("%s",publisher);
			strcpy(p->publisher,publisher);
		}
		//�޸�ͼ������
	    printf("�Ƿ��޸�ͼ�����ͣ������� y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("������ͼ�����ͣ�\n");
			scanf("%s",type);
			strcpy(p->type,type);
		}
		//�޸ĳ���ʱ��
        printf("�Ƿ��޸ĳ���ʱ�䣬������ y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("���������ʱ�䣺\n");
			scanf("%d",&pubtime);
			p->pubtime=pubtime;
		}
		//�Ƿ��޸ļ۸�
		printf("�Ƿ��޸ļ۸������� y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("������۸�\n");
			scanf("%d",&price);
			p->price=price;
		}
		printf("�Ƿ��޸Ŀ�棬������ y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("�������棺\n");
			scanf("%d",&Num);
			p->Num=Num;
		}
		printf("�޸ĺ��ͼ����ϢΪ��\n");
        printf("���      ����    ����     ������    ���    ����������   �۸�   ���\n");
	    printf("%d%8s%10s%8s%10s%10d%8d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);

		Save(head);
	}
}

void reader(LinkList head, linklist head1)//��ͨ���ߺ���
{
    do{
    printf("************************************\n");
    printf("*          1:��������              *\n");
    printf("*          2:��ѯͼ����Ϣ          *\n");
    printf("*          3:����ͼ��              *\n");
    printf("*          4:�˳�                  *\n");
    printf("************************************\n\n");
    printf("   ��������Ҫ���е���Ŀѡ��\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            password(head1);//���߸�������
            break;
        case 2:
            query(head);//��ѯͼ����Ϣ
            break;
        case 3:
            borrow(head);
            break;
        default:return;
    }}while(select!=4);
}

void password(linklist head1)//���߸�������
{
    linklist p=head1->next;
    int flge=0;
    char str[10], password[10];
    printf("�����������û������˺�\n");
    scanf("%s",str);
    int m=1;
    while(p)
	{
		if(strcmp(p->name,str)==0||strcmp(p->id,str)==0)
		{
		    while(m==1)
            {
                printf("��������ԭ��������\n");
                scanf("%s", password);
                if(strcmp(p->password, password)!=0)
                {
                    printf("����������������밴1�� �˳��밴2\n");
                    scanf("%d", &m);
                }
                if(strcmp(p->password, password)==0)
                    break;
		    }

		    if(m==2)
                break;
			printf("����������������\n");
	        scanf("%s", password);
	        strcpy(p->password,password);
	        save(head1);
	        flge=1;
	        break;
		}
		p=p->next;
	}
	if(flge==0)
		printf("�˺���Ϣ������\n");
}

void query(LinkList head)//��ѯͼ����Ϣ
{
    do{
    printf("***********************************\n");
    printf("*         1:����������            *\n");
    printf("*         2:����������            *\n");
    printf("*         3:�����������          *\n");
    printf("*         4:����������������      *\n");
    printf("*         5:�˳�                  *\n");
    printf("***********************************\n\n");
    printf("     ��������Ҫ���е���Ŀѡ��\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            titlequery(head);//��������
            break;
        case 2:
            authorquery(head);//����������
            break;
        case 3:
            pressquery(head);//���������
            break;
        case 4:
            titleauthor(head);//����������������
            break;
        default:return;
    }}while(select!=5);
}

void titlequery(LinkList head)//��������
{
    LinkList p=head->next;
	char name[20];
	int flge=0;

    printf("������Ҫ��ѯ��������\n");
	scanf("%s",name);
    while(p)
	{
		if(strstr(p->name,name)!=NULL||strstr(name,p->name)!=NULL)
		{
			printf("%d%8s%10s%8s%10s%10d%4d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
		    flge=1;
		}
		  p=p->next;
	}
	if(flge==0)
	 printf("������Ϣ������\n");

	return;
}

void authorquery(LinkList head)//����������
{
	LinkList p=head->next;
	char author[20];
	int flge=0;

    printf("������Ҫ��ѯ���������֣�\n");
	scanf("%s",author);
    while(p)
	{
		if(strstr(p->author,author)!=NULL||strstr(author,p->author)!=NULL)
		{
			printf("%d%8s%10s%8s%10s%10d%4d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
		    flge=1;
		}
		  p=p->next;
	}
	if(flge==0)
	 printf("������Ϣ������\n");

	return;
}

void pressquery(LinkList head)//���������
{
    LinkList p=head->next;
	char publisher[20];
	int flge=0;

    printf("������Ҫ��������������֣�\n");
	scanf("%s",publisher);
    while(p)
	{
		if(strstr(p->publisher,publisher)!=NULL||strstr(publisher,p->publisher)!=NULL)
		{
			printf("%d%8s%10s%8s%10s%10d%4d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
		    flge=1;
		}
		  p=p->next;
	}
	if(flge==0)
	 printf("������Ϣ������\n");
	return;
}
void titleauthor(LinkList head)
{
    LinkList p=head->next;
	char name[20],author[20];
	int flge=0;
	printf("������Ҫ��ѯ���������������֣�\n");
	scanf("%s %s",name,author);
    while(p)
	{
		if((strcmp(p->name,name)==0)&&(strcmp(p->author,author)==0))
		{
			printf("%d%8s%10s%8s%10s%10d%4d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
		    flge=1;
		}
		  p=p->next;
	}
	if(flge==0)
	   printf("������Ϣ������\n");
    return ;
}

void borrow(LinkList head)
{
    LinkList p=head->next;
    int ID,flge=0,a=0;
    char sel;
    printf("������Ҫ����ͼ��ı�ţ�\n");
    scanf("%d",&ID);
    while(p)
	{
		if(p->id==ID)
		{
		    if(p->Num==0)
            {
                printf("��ȫ�������");
            }
            else
            {
                a=p->Num;
                printf("��ȷ��ͼ����Ϣ��\n");
                printf("���      ����    ����     ������   ��� ���������� �۸�   ���\n");
                printf("%d%8s%10s%8s%10s%10d%4d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
            }
            flge=1;
            break;
		}
		  p=p->next;
	}
	if(flge==0)
    {
        printf("������Ϣ������\n");
    }
    if(flge!=0&&a!=0)
    {
        printf("ȷ������ô(һ���ʺ�ֻ�ܽ�һ��)�������� y or n:\n");
        scanf(" %c",&sel);
        if(sel=='y')
		{
			p->Num=p->Num-1;
			printf("��ǰ��ͼ����ϢΪ��\n");
			printf("���      ����    ����     ������   ��� ���������� �۸�   ���\n");
            printf("%d%8s%10s%8s%10s%10d%4d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
		}
		if(sel=='n')
        {
            system("pause");
        }
        Save(head);
    }
}
