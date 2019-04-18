
/* Coded by Eldar Timraleev (aka CRaFT4ik) © 2019 */

%{
	#define alloca malloc

	#define _CRT_SECURE_NO_WARNINGS
	#include <stdio.h>
	#include <stdlib.h>
	#include <ctype.h>
	#include <string.h>

	#define SIZE 1000
	#define DEBUG

	void debug(int num, int *coefs)
	{
		#ifdef DEBUG
		printf("#%d:\t", num);
		for (int i = 0; i < 9; i++)
			printf("%d\t", coefs[i]);
		printf("\n");
		#endif
	}

	void debugN(int num, int val)
	{
		#ifdef DEBUG
		printf("#%d:\t%d\n", num, val);
		#endif
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
%type	<coef_arr>	mult_simpl
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
		;

var_convol	: // Калькулятор числа + переменные.

			LETTER
			{
				memset($$, 0, sizeof($$));
				$$[1] = 1;

				debug(10, $$);
			}
		|	LETTER '^' num_convol
			{
				memset($$, 0, sizeof($$));
				$$[$3] = 1;

				debug(11, $$);
			}
		|	'(' var_convol ')'
			{
				memcpy($$, $2, sizeof($$));

				debug(12, $$);
			}
		|	'-' var_convol %prec UMINUS
			{
				for (int i = 0; i < SIZE; i++)
					$$[i] = -1 * $2[i];

				debug(13, $$);
			}
		|	mult_simpl // Сокращенное умножение (2x, 2x^2(3x+1), ...).
			{
				memcpy($$, $1, sizeof($$));

				debug(14, $$);
			}
			// Операции типа "выражение с переменной + выражение с переменной".
		|	var_convol '+' var_convol
			{
				for (int i = 0; i < SIZE; i++)
					$$[i] = $1[i] + $3[i];

				debug(20, $$);
			}
		|	var_convol '-' var_convol
			{
				for (int i = 0; i < SIZE; i++)
					$$[i] = $1[i] - $3[i];

				debug(21, $$);
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

				debug(22, $$);
			}
		|	var_convol '/' var_convol
			{
				memset($$, 0, sizeof($$));
				error("You're going to divide a polynomial into a polynomial!");

				debug(24, $$);
			}
			// Операции типа "числовое выражение + выражение с переменной".
		|	num_convol '*' var_convol
			{
				for (int i = 0; i < SIZE; i++)
					$$[i] = $1 * $3[i];

				debug(30, $$);
			}
		|	var_convol '*' num_convol
			{
				for (int i = 0; i < SIZE; i++)
					$$[i] = $3 * $1[i];

				debug(31, $$);
			}
		|	num_convol '/' var_convol
			{
				memcpy($$, $3, sizeof($$));
				error("Wrong expression: NUM / VAR!");

				debug(32, $$);
			}
		|	var_convol '/' num_convol
			{
				memcpy($$, $1, sizeof($$));
				for (int i = 0; i < SIZE; i++)
					$$[i] /= $3;

				debug(33, $$);
			}
		|	var_convol '+' num_convol
			{
				memcpy($$, $1, sizeof($$));
				$$[0] += $3;

				debug(34, $$);
			}
		|	var_convol '-' num_convol
			{
				memcpy($$, $1, sizeof($$));
				$$[0] -= $3;

				debug(35, $$);
			}
		|	num_convol '+' var_convol
			{
				memcpy($$, $3, sizeof($$));
				$$[0] += $1;

				debug(36, $$);
			}
		|	num_convol '-' var_convol
			{
				for (int i = 0; i < SIZE; i++)
					$$[i] = -1 * $3[i];

				$$[0] += $1;

				debug(37, $$);
			}
		|	'(' var_convol ')' '^' num_convol
			{
				int buf[SIZE];
				memcpy($$, $2, sizeof($$));

				for (int k = 1; k < $5; k++)
				{
					memset(buf, 0, sizeof(buf));
					for (int i = SIZE - 1; i >= 0; i--)
					{
						if ($$[i] == 0) continue;
						for (int j = SIZE - 1; j >= 0; j--)
						{
							if ($2[j] == 0) continue;
							int coef = $$[i] * $2[j];
							if (i + j < SIZE)
								buf[i+j] += coef;
							else if (coef != 0)
							{
								error("Too much degree!");
								break;
							}
						}
					}
					memcpy($$, buf, sizeof($$));
				}

				debug(38, $$);
			}
		;

num_convol	: // Калькулятор чисел.

			'(' num_convol ')'
			{
				$$ = $2;
				debugN(101, $$);
			}
		|	num_convol '+' num_convol
			{
				$$ = $1 + $3;
				debugN(102, $$);
			}
		|	num_convol '-' num_convol
			{
				$$ = $1 - $3;
				debugN(103, $$);
			}
		|	num_convol '*' num_convol
			{
				$$ = $1 * $3;
				debugN(104, $$);
			}
		|	num_convol '/' num_convol
			{
				$$ = $1 / $3;
				debugN(105, $$);
			}
		|	num_convol '^' num_convol
			{
				$$ = $1;
				for (int j = 1; j < $3; j++)
					$$ *= $1;
				debugN(106, $$);
			}
		|	'-' num_convol %prec UMINUS // Ставим наивысший приоритет.
			{
				$$ = -1 * $2;
				debugN(107, $$);
			}
		|	number
		;

mult_simpl	: // Сокращенная запись умножения (2x, 2x^2(3x+1), ...).

			number LETTER
			{
				memset($$, 0, sizeof($$));
				$$[1] = $1;

				debug(200, $$);
			}
		|	number LETTER '^' num_convol
			{
				memset($$, 0, sizeof($$));
				$$[$4] = $1;

				debug(201, $$);
			}
		|	mult_simpl '(' var_convol ')'
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

				debug(202, $$);
			}
		|	'(' var_convol ')' '(' var_convol ')'
			{
				memset($$, 0, sizeof($$));
				for (int i = 0; i < SIZE; i++)
					for (int j = 0; j < SIZE; j++)
					{
						int coef = $2[i] * $5[j];
						if (i + j < SIZE)
							$$[i+j] += coef;
						else if (coef != 0)
						{
							error("Too much degree!");
							break;
						}
					}

				debug(203, $$);
			}
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
