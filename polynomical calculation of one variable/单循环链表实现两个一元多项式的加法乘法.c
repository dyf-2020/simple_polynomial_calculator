#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define LEN sizeof(polynode)
char a[5][30]={"\0","多项式A为:","多项式B为:","多项式A与B的乘积为:","多项式A与B的和为:"};


/*函数声明*/
typedef struct pnode polynode; 
polynode*mergepoly(polynode*head);               //将指数从小到大排列的多项式中相同指数的项合并，得到最简形式
void sortpoly(polynode*head);        //将输入的多项式每一项按照指数从小到大重新排序
polynode *polyadd(polynode *ha,polynode *hb);        //两个多项式相加




typedef struct pnode            //定义多项式循环链式存储结构    指数从高到低排列
{   
    double coef;                //多项式其中一项的系数
    int exp;                    //多项式其中一项的指数
    struct pnode *next;         //多项式指针域
}polynode;                          //多项式类型名




void gotoxy(int x, int y)               //定位控制台光标位置
{
    COORD pos;
    pos.X = x - 1;
    pos.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void clear()                            //清空屏幕并且重新定位光标
{
    system("cls");
    gotoxy(16,5);
}



   
polynode *polyadd(polynode *ha,polynode *hb)        //两个多项式相加
{
    polynode *head,*p,*pa,*pb;
    double x;
    pa=ha->next;
    pb=hb->next;
    head=(polynode*)malloc(LEN);
    head->coef=0;
    head->exp=-99;
    p=head;
    while((pa!=ha)&&(pb!=hb))       //原来两个多项式均未被读取完   
    {
        if(pa->exp==pb->exp)        //指数相等的情况  
        {
            x=pa->coef+pb->coef;
            if(x!=0)
            {
                p->next=(polynode*)malloc(LEN);
                p=p->next;
                p->exp=pa->exp;
                p->coef=x;
            }
            pa=pa->next;
            pb=pb->next; 
        }
        else                    //指数不相等的情况
        {
            if(pa->exp<pb->exp)
            {
                p->next=(polynode*)malloc(LEN);
                p=p->next;
                p->exp=pa->exp;
                p->coef=pa->coef;
                pa=pa->next;
            }
            else
            {
                p->next=(polynode*)malloc(LEN);
                p=p->next;
                p->coef=pb->coef;
                p->exp=pb->exp;
                pb=pb->next;
            }
        }
    }
    while(pa!=ha)                   //第一个多项式未读完，第二个多项式已经读完
    {
        p->next=(polynode*)malloc(LEN);
        p=p->next;
        p->exp=pa->exp;
        p->coef=pa->coef;
        pa=pa->next;
    }
    while(pb!=hb)                   //第二个多项式未读完，第一个多项式已经读完
    {
        p->next=(polynode*)malloc(LEN);
        p=p->next;
        p->exp=pb->exp;
        p->coef=pb->coef;
        pb=pb->next;
    }

    p->next=head;
    return head;
}




polynode* creat_hsortcircle()       //尾插法建立有序的循环单链表，系数和对应的指数一组一组的输入
{
    polynode *head,*rear,*p,*s;
    double coef;
    int exp,k=0;
    head=(polynode*)malloc(LEN);
    rear=head;
    head->exp=-99;
    printf("\n\n请输入系数:");
    scanf("%lf",&coef);
    printf("\n请输入指数:");
    scanf("%d",&exp);
    printf("\n循环下去以0作为结束符");
  
    
    while(coef!=0)                  //判断输入否结束
    {
        if(exp>rear->exp)           //若输入的指数比尾节点指数更大，就插到尾节点后
        { 
            rear->next=(polynode*)malloc(LEN);
            rear=rear->next;
            rear->coef=coef;
            rear->exp=exp;
        }
        else                            //若输入指数没有尾节点指数大，就开始寻找插入位置
        {
            p=head;
            while((p->next!=head)&&(p->next->exp<exp))
            { p=p->next;}
            s=(polynode*)malloc(LEN);
            s->coef=coef;
            s->exp=exp;
            s->next=p->next;
            p->next=s;
        }
        printf("\n\n请输入系数:");
        scanf("%lf",&coef);
        printf("\n请输入指数:");
        scanf("%d",&exp);
        printf("\n循环下去以0作为结束符\n");
        k++;
    }
    rear->next=head;
    head->coef=k;                   //k记录输入了几组系数指数，k值存放在头节点的系数域中
    return head;
}


void printc_poly(polynode *head,char name[30])      //输出该多项式每一项系数指数
{
    polynode *p;
    int j=0;
    p=head->next;
    printf("\n\t%s\n",name);
    while(p!=head)
    {
        
        printf("\t系数：%6.2lf   指数：%4d\n",p->coef,p->exp);
        j++;
        p=p->next;
    }
    printf("\t项数为:%d\n\n",j);
}


void sortpoly(polynode*head)        //将输入的多项式每一项按照指数从小到大重新排序
{
    polynode *p,*q;
    int texp;
    double tcoef;
    p=head->next;
    while(p->next!=head)
    {
        q=p->next;
        while(q!=head)
        {
            if(p->exp>q->exp)
            {
                tcoef=p->coef;
                p->coef=q->coef;
                q->coef=tcoef;
                texp=p->exp;
                p->exp=q->exp;
                q->exp=texp;
            }
            q=q->next;
        }
        p=p->next;
    }
}


polynode*polymulti(polynode*heada,polynode*headb)           //多项式相乘的计算
{
    int texp;
    double tcoef;
    polynode *head,*pa,*pb,*rear;                  //head为多项式heada和headb相乘后未化简的多项式的表头节点
    pa=heada->next;
    head=(polynode*)malloc(LEN);
    rear=head;
    head->coef=-999;
    head->exp=-999;
    while(pa!=heada)
    {
        pb=headb->next;
        while(pb!=headb)
        {
            texp=pa->exp+pb->exp;
            tcoef=pa->coef*pb->coef;
            rear->next=(polynode*)malloc(LEN);
            rear=rear->next;
            rear->exp=texp;
            rear->coef=tcoef;
            pb=pb->next;
        }
        pa=pa->next;
    }
    rear->next=head;
    sortpoly(head);                                     //将相乘后多项式按指数从小到大排列
    polynode *final_head=mergepoly(head);               //将指数从小到大排列的多项式中相同项合并
    return final_head;
}


polynode*mergepoly(polynode*head)               //将指数从小到大排列的多项式中相同指数的项合并，得到最简形式
{
    polynode *final_head,*final_rear,*p,*q;
    int y;                                      //y存放指数
    double sum;                                 //sum存放当前相同指数项系数的和
    final_head=(polynode*)malloc(LEN);
    final_head->coef=head->coef;
    final_head->exp=head->exp;
    final_rear=final_head;
    p=head->next;
    while(p!=head)
    {
        sum=0;
        q=p;
        y=p->exp;
        while((y==q->exp)&&(q!=head))
        {
            sum+=q->coef;
            q=q->next;
        }  
        final_rear->next=(polynode*)malloc(LEN);
        final_rear=final_rear->next;
        final_rear->exp=y;
        final_rear->coef=sum;
        p=p->next;
    }
    final_rear->next=final_head;
    return final_head;
}


int main()                      //主函数
{
    system("cls");
    printf("\n输入多项式A");
    polynode*heada=creat_hsortcircle();
    printf("\n输入多项式B");
    polynode*headb=creat_hsortcircle();
    polynode*head_add=polyadd(heada,headb);
    polynode*head_multi=polymulti(heada,headb);
    clear();
    printc_poly(head_multi,a[3]);
    printc_poly(head_add,a[4]);
    return 0;
}   