#include "stdio.h" 
#include <stdlib.h> 

#define getpch(type) (type*)malloc(sizeof(type)) 
#define NULL 0 
struct pcb { /* 定义进程控制块PCB */
	char name[10];
	char state;//进程状态
	int ntime;//需要时间
	int rtime;//已经执行时间
	int atime;//到达时间 
	struct pcb* link;
}*ready = NULL, *p;
typedef struct pcb PCB;
int runningTime = 0;
int space()
{
	int l = 0; PCB* pr = ready;
	while (pr != NULL)
	{
		l++;
		pr = pr->link;
	}
	return(l);
}
void linkpcb() {
	PCB *first, *second;
	int insert = 0;
	if (ready == NULL) /*,插入队首*/
	{
		p->link = ready;
		ready = p;
	}
	else {//插入队尾 
		first = ready;
		second = first->link;
		while (second != NULL)
		{
			first = first->link;
			second = second->link;
		}
		first->link = p;
	}
}
void sort() { /* 建立对进程进行短进程排列函数*/
	PCB *first, *second;
	if (ready == NULL || space() == 1) /*,插入队首*/
	{
		return;
	}
	else
	{
		first = ready->link;
		while (first != NULL && first->atime <= runningTime) {
			second = first->link;
			if (first->ntime < ready->ntime) {
				PCB *temp = ready;
				while (temp != NULL) {
					if (temp->link == first)break;
					temp = temp->link;
				}
				temp->link = second;
				first->link = ready;
				ready = first;
			}
			first = second;
		}
	}
}
void input() /* 建立进程控制块函数*/
{
	int i, num;
	//clrscr(); /*清屏*/
	system("cls");
	printf("            ***************************短进程优先调度算法******************************");
	printf("\n 请输入即将运行的进程总数目：");
	scanf("%d", &num);
	for (i = 0; i < num; i++)
	{
		
		p = getpch(PCB);//申请空间，指针 
		printf("\n 请输入进程名称:");
		scanf("%s", p->name);
		printf("\n 请输入进程到达时间:");
		scanf("%d", &p->atime);
		printf("\n 请输入进程运行所需时间:");
		scanf("%d", &p->ntime);
		printf("\n");
		p->rtime = 0;
		p->state = 'w';
		p->link = NULL;
		linkpcb();
	}

}

void disp(PCB * pr) /*建立进程显示函数,用于显示当前进程*/
{
	printf("\n 进程名称 \t 进程状态 \t 到达时间 \t 运行所需时间 \t 已经运行时间 \n");
	printf("|%s\t", pr->name);
	printf("|%c\t", pr->state);
	printf("|%d\t", pr->atime);
	printf("|%d\t", pr->ntime);
	printf("|%d\t", pr->rtime);
	printf("\n");
}
void check() /* 建立进程查看函数 */
{
	PCB* pr;
	printf("\n **** 当前正在运行的进程是:%s", p->name); /*显示当前运行进程*/
	disp(p);
	pr = ready;
	printf("\n ****当前就绪队列状态为:\n"); /*显示就绪队列状态*/
	if (pr == NULL)printf("\n 就绪队列为空。\n ");
	while (pr != NULL)
	{
		if (pr->atime <= runningTime) {
			disp(pr);
			pr = pr->link;
		}
		else {
			break;
		}
	}
}
void destroy() /*建立进程撤消函数(进程运行结束,撤消进程)*/
{
	printf("\n 进程 [%s] 已完成.\n", p->name);
	free(p);
}
void running() /* 建立进程就绪函数(进程运行时间到,置就绪状态*/
{
	runningTime += p->ntime;
	p->rtime = p->ntime;
	if (ready != NULL && runningTime < ready->atime) {
		runningTime = ready->atime;
	}
	destroy(); /* 调用destroy函数*/
	sort(); /*调用sort函数*/
}
int main() /*主函数*/
{
	int len, h = 0;
	char ch;
	input();
	len = space();

	while ((len != 0) && (ready != NULL))
	{
		printf("********************************\n");
		printf("当前时刻%d\n", h++);
		p = ready;
		ready = p->link;
		p->link = NULL;
		p->state = 'R';
		check();
		running();
	
	}
	printf("\n\n 进程已经完成.\n");
	ch = getchar();
	system("Pause");
	return 0;
}
