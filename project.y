%{
	#define alloca malloc
	
	#define _CRT_SECURE_NO_WARNINGS
	#include <stdio.h>
	#include <stdlib.h>
	#include <ctype.h>
	#include <string.h>

	#define SIZE 1000
	
	void debug(int num, int *coefs)
	{
		printf("#%d:\t", num);
		for (int i = 0; i < 8; i++)
			printf("%d\t", coefs[i]);
		printf("\n");
	}
	
	void error(char *str)
	{
		printf("ERROR: %s\n", str);
	}
	
	void finalOutput(int *pcoefs)
	{
		printf("Your result: ");
		char buf[SIZE*5];
		char *p = buf;
		memset(buf, 0, sizeof(buf));
		
		for (int i = SIZE - 1; i >= 0; i--)
		{
			int coef = pcoefs[i];
			if (coef == 0) continue;
			
			if (i == 0)
			{
				if (coef > 0)
				{ sprintf(p, "+"); p += 1; }
			
				sprintf(p, "%d", coef);
				p = buf + strlen(buf);
				continue;
			}
			
			if (coef > 0)
			{ sprintf(p, "+"); p += 1; }
			else
			{ sprintf(p, "-"); p += 1; }
			
			if (abs(coef) != 1)
			{
				sprintf(p, "%d", abs(coef));
				p = buf + strlen(buf);
			}
			
			sprintf(p, "%s", "x");
			p = buf + strlen(buf);
			
			if (i > 1)
			{
				sprintf(p, "^%d", i);
				p = buf + strlen(buf);
			}
		}
		
		if (p == buf) printf("0\n");
		else printf("%s\n", *buf == '+' ? buf + 1 : buf);
	}
%}

%union { int num; int coef_arr[SIZE]; char var_name; }

%start main

%token 	<num>		DIGIT
%token 	<var_name>	LETTER
%type 	<coef_arr> 	convol
%type	<coef_arr>	var_convol
%type	<num>		num_convol
%type 	<num> 		main
%type 	<num> 		number

%left '+' '-'
%left '*' '/'
%right '^'
%left UMINUS

%%     /* начало секции правил */

main	:	convol
			{
				finalOutput($1);
			}
		;

convol	:	num_convol
			{
				memset($$, 0, sizeof($$));
				$$[0] = $1;
				
				debug(1, $$);
			}
		|	var_convol
			{
				memcpy($$, $1, sizeof($$));
				
				debug(2, $$);
			}
			// +,-
		|	var_convol '+' num_convol
			{
				memcpy($$, $1, sizeof($$));
				$$[0] += $3;
				
				debug(3, $$);
			}
		|	var_convol '-' num_convol
			{
				memcpy($$, $1, sizeof($$));
				$$[0] -= $3;
				
				debug(4, $$);
			}
		|	num_convol '+' var_convol
			{
				memcpy($$, $3, sizeof($$));
				$$[0] += $1;
				
				debug(5, $$);
			}
		|	num_convol '-' var_convol
			{
				for (int i = 0; i < SIZE; i++)
					$$[i] = -1 * $3[i];
				
				$$[0] += $1;
				
				debug(6, $$);
			}
		;
		
var_convol	:

			LETTER
			{
				memset($$, 0, sizeof($$));
				$$[1] = 1;
				
				debug(11, $$);
			}
		|	LETTER '^' num_convol
			{
				memset($$, 0, sizeof($$));
				$$[$3] = 1;
				
				debug(12, $$);
			}
		|	'-' var_convol %prec UMINUS
			{
				for (int i = 0; i < SIZE; i++)
					$$[i] = -1 * $2[i];
				
				debug(13, $$);
			}
		|	var_convol '+' var_convol
			{
				for (int i = 0; i < SIZE; i++)
					$$[i] = $1[i] + $3[i];
				
				debug(13, $$);
			}
		|	var_convol '-' var_convol
			{
				for (int i = 0; i < SIZE; i++)
					$$[i] = $1[i] - $3[i];
				
				debug(14, $$);
			}
		|	var_convol '*' var_convol
			{
				memset($$, 0, sizeof($$));
				for (int i = 0; i < SIZE; i++)
					for (int j = 0; j < SIZE; j++)
					{
						int coef = $1[i] * $3[j];
						if (i + j < SIZE)
							$$[i+j] += coef;
						else if (coef != 0)
						{
							error("Too much degree!");
							break;
						}
					}
					
				debug(15, $$);
			}
		|	num_convol '*' var_convol
			{
				for (int i = 0; i < SIZE; i++)
					$$[i] = $1 * $3[i];
				
				debug(16, $$);
			}
		|	var_convol '*' num_convol
			{
				for (int i = 0; i < SIZE; i++)
					$$[i] = $3 * $1[i];
				
				debug(17, $$);
			}
		|	num_convol '/' var_convol
			{
				memcpy($$, $3, sizeof($$));
				error("Wrong expression: NUM / VAR!");
				
				debug(18, $$);
			}
		|	var_convol '/' num_convol
			{
				memcpy($$, $1, sizeof($$));
				for (int i = 0; i < SIZE; i++)
					$$[i] /= $3;
				
				debug(19, $$);
			}
		|	'(' var_convol ')'
			{
				memcpy($$, $2, sizeof($$));
				
				debug(20, $$);
			}
		;
		
num_convol	:
			
			'(' num_convol ')'
			{
				$$ = $2;
				//debug(100, $$);
			}
		|	num_convol '+' num_convol
			{
				$$ = $1 + $3;
				//debug(11, $$);
			}
		|	num_convol '-' num_convol
			{
				$$ = $1 - $3;
				//debug(22, $$);
			}
		|	num_convol '*' num_convol
			{
				$$ = $1 * $3;
				//debug(33, $$);
			}
		|	num_convol '/' num_convol
			{
				$$ = $1 / $3;
				//debug(44, $$);
			}
		|	num_convol '^' num_convol
			{
				$$ = $1;
				for (int j = 1; j < $3; j++)
					$$ *= $1;
				//debug(55, $$);
			}
		|	'-' num_convol %prec UMINUS // Ставим наивысший приоритет.
			{
				$$ = -1 * $2;
				//debug(66, $$);
			}
		|	number
		;
		
number	:	DIGIT
			{
				$$ = $1;
			}
		|	number DIGIT
			{
				$$ = $1 * 10 + $2;
			}
		;
		
%%      /* начало секции подпрограмм */

	int yyerror(char *str)
	{
		printf("Error: \"%s\"\n", str);
		return 0;
	}

	FILE *yyin = NULL;

	int yylex()
	{
		int c = fgetc(yyin);

		if (isdigit(c))
		{
			yylval.num = c - '0';
			return (DIGIT);
		}

		if (c == 'x')
		{
			yylval.var_name = c;
			return (LETTER);
		}

		return (c);
	}

	int main()
	{	
		yyin = fopen("../input.txt", "r");
		if (yyin == NULL)
		{
			yyerror("file was not opened");
			system("pause");
			return 0;
		}

		yyparse();
		fclose(yyin);

		system("pause");
		return 0;
	}