#include <stdio.h>
#include <stdlib.h>

#define amax 2047
#define levmax 3
#define cxmax 2047
#define stacksize 500

enum fct{LIT, OPR, LOD, STO, CAL, INT, JMP, JPC};

typedef struct{
	enum fct f;
	int l;
	int a;
}Instruction;

Instruction code[cxmax];
int s[stacksize];

int b, p, t;

int base(int l){
	int b1 = b;

	while(l--)  b1 = s[b1];

	return b1;
}


void p_code_machine(){
	p=b=0;
	t=-1;

	Instruction i;

	printf(" start pl/0\n");
	printf("\n t   b   p     f   l   a                 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14");
 	printf("\n === === ===   === === ===             === === === === === === === === === === === === === === ===");
	
	s[1]=s[2]=s[3]=0;

	do{
		printf("\n %3d %3d %3d   ", t, b, p);
		i = code[p++]; 

		switch(i.f){
			case LIT:
				printf("LIT %3d %3d", i.l, i.a);
				++t;
				s[t] = i.a;
				break;
			case OPR:
				printf("OPR %3d %3d", i.l, i.a);
				switch(i.a){
					case 0:
						t = b-1;
						p = s[t+3];
						b = s[t+2];
						break;
					case 1:
						s[t] = -s[t];
						break;
					case 2:
						t--;
						s[t] = s[t] + s[t+1];
						break;
					case 3:
						t--;
						s[t] = s[t] - s[t+1];
						break;
					case 4:
						t--;
						s[t] = s[t] * s[t+1];
						break;
					case 5:
						t--;
						s[t] = s[t] / s[t+1];
						break;
					case 6:
						s[t] = !(s[t]%2);
						break;
					case 8:
						t--;
						s[t] = (s[t] == s[t+1]);
						break;
					case 9:
						t--;
						s[t] = (s[t] != s[t+1]);
						break;
					case 10:
						t--;
						s[t] = (s[t] < s[t+1]);
						break;
					case 11:
						t--;
						s[t] = (s[t] >= s[t+1]);
						break;
					case 12:
						t--;
						s[t] = (s[t] > s[t+1]);
						break;
					case 13:
						t--;
						s[t] = (s[t] <= s[t+1]);
					default:
						break;
				}
				break;
			case LOD:
				printf("LOD %3d %3d", i.l, i.a);
				t++;
				s[t] = s[base(i.l) + i.a];
				break;
			case STO:
				printf("STO %3d %3d", i.l, i.a);
				s[base(i.l)+i.a] = s[t];
				t--;
				break;
			case CAL:
				printf("CAL %3d %3d", i.l, i.a);
				s[t+1] = base(i.l);
				s[t+2] = b;
				s[t+3] = p;
				b = t+1;
				p = i.a;
				break;
			case INT:
				printf("INT %3d %3d", i.l, i.a);
				t += i.a;
				break;
			case JMP:
				printf("JMP %3d %3d", i.l, i.a);
				p = i.a;
				break;
			case JPC:
				printf("JPC %3d %3d", i.l, i.a);
				if(s[t] == 1){
					p = i.a;
					t--;
				}
				break;
			default:
			
				break;
		}

		printf("      s[] : ");
		for (int h=0; h<=t; h++) { 
			printf(" %3d", s[h]); 
		}
	}
	while(p != 0);

	printf("\n === === ===   === === ===             === === === === === === === === === === === === === === ==="); 
	printf("\n t   b   p     f   l   a                 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14");
	printf("\n\n end pl/0");
}


int main(){
	// Instructions here...
	code[0].f = OPR; code[0].l = 0; code[0].a = 0;

	p_code_machine();

	return 0;
}