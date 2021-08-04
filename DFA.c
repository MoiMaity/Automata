#include<stdio.h>
#include<stdlib.h>

void main()
{
	int s,n,i,j,l,st,f,present_state,swit,t;
	char ch,string[100];
	printf("\n-----------------------DECLARATION OF DFA-----------------------\n");
	while (1)
	{
		printf("\nEnter number of states:");
		scanf("%d",&s);
		fflush(stdin);
		if (s == 0)
			printf("\nDFA with no state is valid. But it cannot be used to check the strings.\n");
		else if (s < 0)
			printf("\nDFA with negative number of state is invalid.\n");
		else
			break;
	}
	while (1)
	{
		printf("\nEnter number of symbols:");
		scanf("%d",&n);
		fflush(stdin);
		if (n == 0)
			printf("\nDFA with no symbol is valid. But it cannot be used to check the strings.\n");
		else if (n < 0)
			printf("\nDFA with negative number of symbols is invalid.\n");
		else
			break;
	}
	
	printf("\nEnter the symbols:(NOTE: Don't give empty symbols)\n\n");
	char *symbol = (char *)malloc(n*sizeof(char));
	for (i = 0; i < n; i++)
	{
		printf("Symbol %d:",i+1);
		scanf(" %c",&ch);
		fflush(stdin);
		*(symbol + i) = ch;
	}
	printf("-----------------------\n\nEnter the mapping:\n");
	int *map = (int *)malloc(s * n *sizeof(int));
	for(i = 0; i < s; i++)
	{
		printf("-----------------------For STATE %d-----------------------\n\n",i + 1);
		for(j = 0; j < n; j++)
		{
			ch = *(symbol + j);
			while (1)
			{
				printf("\nWith input %c:",ch);
				scanf("%d",&l);
				fflush(stdin);
				if ((l <= 0) || (l > s))
					printf("\nInvalid state.\n");
				else
					break;
			}
			*(map + i*n + j) = l - 1;
		}
		printf("\n----------------------------------------------\n");
	}
	while (1)
	{
		printf("\nEnter start state:");
		scanf("%d",&st);
		fflush(stdin);
		if ((st <= 0) || (st > s))
			printf("\nInvalid state.\n");
		else
			break;
	}
	st = st - 1;
	while (1)
	{
		printf("\nEnter number of final states:");
		scanf("%d",&f);
		if (f < 0)
			printf("\nNegative number of final states are invalid.\n");
		else if (f == 0)
		{
			printf("\nIrrespective of input the string is invalid.\n");
			exit(0);
		}
		else if (f > n)
			printf("\nNumber of final states cannot be greater than number of total states.");
		else
			break;
	}
	fflush(stdin);
	int *final = (int *)malloc(f * sizeof(int));
	for (i = 0; i < f; i++)
	{
		while (1)
		{
			t = 0;
			printf("\nFinal state number %d:",i+1);
			scanf(" %d",&l);
			fflush(stdin);
			if ((l <= 0) || (l > s))
				printf("\nInvalid state.\n");
			else
				if (i == 0)
					break;
				else
				{
					for (j = 0; j <= i; j++)
					{
						if (*(final + j) == l - 1)
						{
							printf("\nSame final state cannot be added again.\n");
							t = 1;
							break;
						}
						if (t == 0)
							break;
					}
				}
		}
		*(final + i) = l - 1;
	}
	printf("\n-----------------------DFA is made-----------------------\n");
	do
	{
		printf("\nEnter the string to check:");
		fgets(string, 100, stdin);
		fflush(stdin);
		ch = string[0];
		j = 0;
		present_state = st;
		t = 0;
		while(ch != '\n')
		{
			for (i = 0; i < s; i++)
			{
				if (*(symbol + i) == ch)
				{
					l = i;
					t = 1;
					break;
				}
			}
			if (t == 0)
			{
				printf(" %c",ch);
				printf("\nString contains invalid symbols. DFA crashes.\n");
				exit(0);
			}
			t = 0;
			present_state = *(map + present_state * n + l);
			j = j + 1;
			ch = string[j];
		}
		j = 0;
		for (i = 0; i < f; i++)
			{
				if (*(final + i) == present_state)
				{
					printf("\nThe string is accepted.\n");
					j = 1;
					break;
				}
			}
		if ( j == 0)
			printf("\nThe string is rejected.\n");
		printf("\n(Press any number to continue. Press 0 to exit.)\n");
		scanf("%d",&swit);
		fflush(stdin);
	}while(swit != 0);
	getch();
}
