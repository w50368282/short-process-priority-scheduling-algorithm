#include "stdio.h" 
#include <stdlib.h> 
#include <conio.h> 

#define getpch(type) (type*)malloc(sizeof(type)) 
#define NULL 0 
struct pcb { 
	char name[10];
	char state;
	int ntime;
	int rtime;
	int atime;
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
	if (ready == NULL)
	{
		p->link = ready;
		ready = p;
	}
	else {
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
void sort() { 
	PCB *first, *second;
	if (ready == NULL || space() == 1)
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
void input() 
{
	int i, num;
	//clrscr(); 
	system("cls");
	printf("            ***************************짧은 프로세스 우선 순위 알고리즘******************************");
	printf("\n 실행할 프로세스의 총 수를 입력하세요：");
	scanf("%d", &num);
	for (i = 0; i < num; i++)
	{
		
		p = getpch(PCB);
		printf("\n 프로세스 이름 입력하세요:");
		scanf("%s", p->name);
		printf("\n 프로세스 도착 시간 입력하세요:");
		scanf("%d", &p->atime);
		printf("\n 프로세스 실행에 필요한 시간을 입력하세요:");
		scanf("%d", &p->ntime);
		printf("\n");
		p->rtime = 0;
		p->state = 'w';
		p->link = NULL;
		linkpcb();
	}

}

void disp(PCB * pr) 
{
	printf("\n 프로세스 이름 \t 프로세스 상태 \t 도착 시간 \t 운행 소요 시간 \t 이미 가동 시간 \n");
	printf("|%s\t", pr->name);
	printf("|%c\t", pr->state);
	printf("|%d\t", pr->atime);
	printf("|%d\t", pr->ntime);
	printf("|%d\t", pr->rtime);
	printf("\n");
}
void check() 
{
	PCB* pr;
	printf("\n **** 현재 실행 중인 프로세스는:%s", p->name); 
	disp(p);
	pr = ready;
	printf("\n ****현재 착서 대열의 상태는:\n");
	if (pr == NULL)printf("\n 전열이 허사가 되다. \n ");
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
void destroy()
{
	printf("\n 프로세스[%s] 완료됨.\n", p->name);
	free(p);
}
void running() 
{
	runningTime += p->ntime;
	p->rtime = p->ntime;
	if (ready != NULL && runningTime < ready->atime) {
		runningTime = ready->atime;
	}
	destroy(); 
	sort();
}
int main()
{
	int len, h = 0;
	char ch;
	input();
	len = space();

	while ((len != 0) && (ready != NULL))
	{
		printf("********************************\n");
		printf("현시점%d\n", h++);
		p = ready;
		ready = p->link;
		p->link = NULL;
		p->state = 'R';
		check();
		running();
	
	}
	printf("\n\n 프로세스가 이미 완료되었습니다.\n");
	ch = getchar();
	system("Pause");
	return 0;
}
