#include "stdio.h" 
#include <stdlib.h> 

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
	printf("            *************************Short process priority scheduling algorithm***********************");
	printf("\n Please enter the total number of processes to run：");
	scanf("%d", &num);
	for (i = 0; i < num; i++)
	{
		
		p = getpch(PCB);
		printf("\n Please enter a process name:");
		scanf("%s", p->name);
		printf("\n Please enter the process arrival time:");
		scanf("%d", &p->atime);
		printf("\n Please enter the time required for the process to run:");
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
	printf("\n Process name \t Process status \t Time of arrival \t Running time \t Already running time \n");
	printf("%s\t", pr->name);
	printf("%c\t", pr->state);
	printf("%d\t", pr->atime);
	printf("%d\t", pr->ntime);
	printf("%d\t", pr->rtime);
	printf("\n");
}
void check()
{
	PCB* pr;
	printf("\n **** The currently running process is:%s", p->name);
	disp(p);
	pr = ready;
	printf("\n ****The current ready queue state is:\n");
	if (pr == NULL)printf("\n The ready queue is empty.\n ");
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
	printf("\n Process [%s] has been completed.\n", p->name);
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
		printf("The current moment:%d\n", h++);
		p = ready;
		ready = p->link;
		p->link = NULL;
		p->state = 'R';
		check();
		running();
	
	}
	printf("\n\n The process is complete.\n");
	ch = getchar();
	system("Pause");
	return 0;
}
