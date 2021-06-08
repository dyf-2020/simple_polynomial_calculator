#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#define NUM 5
#define LEN sizeof(list)

char k[7][20]={"\0","语文","数学","外语","物理","化学","总成绩"};

typedef struct student
{
    int seq_num;        //序号
    char stu_num[20];    //学号
    char name[10];      //姓名
    float score[5];     //各科目成绩
    float total;        //总成绩
}student; 

typedef struct linklist
{
    student stu;
    struct linklist *next;
}list;

list *score_head;       //按成绩由高到低排列的头节点
list *num_head;         //按学号由低到高排列的头节点

int menu_select()       //cmd中输入数字，选择增删查改退出操作
{
    /*printf("\n\t\t这是学生管理系统");
    printf("\n\t\t建立学生信息表：1");
    printf("\n\t\t插入学生信息：2");
    printf("\n\t\t删除对应学号数据：3");
    printf("\n\t\t按成绩由高到低输出当前表：4");
    printf("\n\t\t按学号由高到低输出当前表：5");
    printf("\n\t\t退出管理系统：0");
    printf("\n\n\t\t请输入数字：");
    */
   printf("\t\t这是学生管理系统\n");
    printf("\t\t建立学生信息表：1\n");
    printf("\t\t插入学生信息：2\n");
    printf("\t\t删除对应学号数据：3\n");
    printf("\t\t按成绩由高到低输出当前表：4\n");
    printf("\t\t按学号由高到低输出当前表：5\n");
    printf("\t\t退出管理系统：0\n");
    printf("\t\t请输入数字：\n");
    int kk;
    do
    {
        scanf("%d",&kk);
    }while((0>kk)&&(kk>5));
    return kk;
}

void create()                                           //创建学生成绩表-提示信息部分
{
    list*hsort_create();
    printf("\n将创建一个按学生成绩降序的单链表");
    score_head=hsort_create();
}
list* hsort_create()                                    //创建学生成绩表-功能主体部分
{
    printf("\n输入一组学生记录，输入学号为*表示结束");
    list*head,*p,*q,*rear,*findnode(),*input_record();
    void *flag;
    int seq_num;
    char name[10],stu_num[20];
    float score[NUM],total=0;
    head=(list*)malloc(LEN);
    head->next=NULL;
    head->stu.total=999;
    rear=head;
    p=input_record();
    while(p!=NULL)
    {
        if(p->stu.total<rear->stu.total)
        {
            p->next=rear->next;
            rear->next=p;
            rear=p;
        }
        else
        {
            q=findnode(head,p);                 //在链表中寻找p的前驱节点
            p->next=q->next;
            q->next=p;
        }
        p=input_record();
    }
    return head;
}

list*input_record()                             //从命令行输入一个学生的数据
{ 
    int i,n=1;
    list*s=(list*)malloc(LEN);
    s->stu.seq_num=n;
    n++;
    printf("\n输入学号：");
    gets(s->stu.stu_num);
    printf("\n输入姓名：");
    gets(s->stu.name);
    printf("\n输入学生成绩，依次为 语文 数学 外语 物理 化学");
    for(i=0;i<NUM;i++)
    {
        scanf("%d",&s->stu.score[i]);
        s->stu.total +=s->stu.score[i];
    }
    if(strcmp("stu_num","*")==0)return NULL;                   //当输入学号为*时，返回空指针
    else return s;
}


list* findnode(list *head,list *p)                              //找恰好总成绩比p节点大的前驱节点
{
    list *s;
    s=head;
    while((s!=NULL)&&(s->next->stu.total>p->stu.total))
    {
        s=s->next;
    }
    return s;
}
void insert()
{}
void data_insert()
{}
void printlist()
{}
void delete()
{}
void key_delete()
{}
void selesort()
{}


void main()                     
{
    system("cls");
    int kk;
    do
    {
        kk=menu_select();               //从命令行中给出操作序号
        switch(kk)
        {
            case 1:create();break;      //输入为1，建立按学生成绩由高到低排列的单向链表
            case 2:insert();break;      //输入为2，插入数据，并且按照不改变学生成绩由高到低的顺序
            case 3:delete();break;      //输入为3，删除对应学号的数据
            case 4:printlist();break;  //输入为4，按成绩由高到低输出当前表
            case 5:selesort();break;    //输入为5，按学号由低到高输出当前表
            case 0:exit(0);             //输入为0，退出程序，返回0
        }
    }while(kk!=0);
    
}


