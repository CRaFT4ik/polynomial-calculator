
/* Coded by Eldar Timraleev (aka CRaFT4ik) © 2019 */

%{
	#define alloca malloc

	#define _CRT_SECURE_NO_WARNINGS
	#include <stdio.h>
	#include <stdlib.h>
	#include <ctype.h>
	#include <string.h>

	#define SIZE		1000
	#define VARS_SIZE	26
	// #define DEBUG

	void error(char *str)
	{
		printf("ERROR: %s\n", str);
	}

	// Описывает полином.
	struct polynomial
	{
		int name;	// Имя переменной, вовлеченной в полином. Если '\0', то
					// возможно полином никогда не видел свою переменную.
		int coefs[SIZE]; // Коэффициенты полинома.
	};

	// Описывает переменную вида $[smthg] = polynomial.
	struct variable
	{
		int name; // Имя переменной вида $[smthg].
		int is_init; // Была ли переменная проиницилизирована.
		struct polynomial polynom; // Полином, присвоенный данной переменной.
	};

	// Массив всех допустимых переменных.
	struct variable vars[VARS_SIZE];

	// Возвращает указатель на переменную из общего массива по ее названию.
	// Индекс соответствует названию переменной: $A->[0], $B->[1], ..., $Z->[25].
	struct variable * get_variable_by_name(char ch)
	{
		if (!isupper(ch)) return NULL;
		else return (vars + (ch - 'A'));
	}

	// Инициализирует структуру глобальной переменной.
	void init_variable(struct variable *dest, char name, struct polynomial *polynom)
	{
		if (dest == NULL) return;

		memset(dest, 0, sizeof(struct variable));
		dest->is_init = 1;

		if (isupper(name)) dest->name = name;
		if (polynom != NULL)
			memcpy(&dest->polynom, polynom, sizeof(dest->polynom));
	}

	// Инициализирует структуру полинома.
	void init_polynomial(struct polynomial *dest, char name, int *coefs)
	{
		if (dest == NULL) return;

		memset(dest, 0, sizeof(struct polynomial));
		if (islower(name)) dest->name = name;
		if (coefs != NULL) memcpy(dest->coefs, coefs, sizeof(dest->coefs));
	}

	void copy_polynomial(struct polynomial *dest, struct polynomial *src)
	{
		if (dest == NULL || src == NULL) return;

		memcpy(dest, src, sizeof(struct polynomial));
	}

	// Устанавливает коэффицент coef для степени i полинома dest.
	void set_coef(struct polynomial *dest, int i, int coef)
	{
		if (dest == NULL) return;
		if (i >= SIZE) { error("set_coef(): i >= SIZE"); return; }

		dest->coefs[i] = coef;
	}

	void debug(int num, struct polynomial *dest)
	{
		#ifdef DEBUG
		int *coefs = dest->coefs;
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

	void print(struct polynomial *polynom)
	{
		int *pcoefs = polynom->coefs;

		printf("[OUT]: ");
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

			sprintf(p, "%c", polynom->name);
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

%union
{
	int num;
	char ch;
	struct polynomial st_poly;
}

%start main

%token	<num>		CMD_PRINT	// Команда печати на экран значения переменной.
%token	<ch>		GL_VAR		// $A, $B, $F, ... .
%token 	<num>		DIGIT		// Цифра.
%token 	<ch>		LETTER		// Строчная буква.

%type	<ch>		input		// Входной файл (с переносами строк..).
%type	<ch>		gl_var		// Калькулятор полиномов (с переменными вида $A).
%type 	<st_poly> 	convol		// Упрощение полинома (выход: число или полином).
%type	<st_poly>	var_convol	// Калькулятор с одной переменной.
%type	<st_poly>	mult_simpl	// Сокращенная запись умножения.
%type	<num>		num_convol	// Калькулятор с числами (без переменных).
%type 	<num> 		main		// Конечная свертка, точка входа.
%type 	<num> 		number		// Число.

%right	'='
%left	'+' '-'
%left	'*' '/'
%right	'^'
%left	UMINUS

%%     /* начало секции правил */

main	:	convol
			{
				print(&$1);
			}
		|	input
		;

input	:	// Обработка входного документа с глобальными переменными (калькулятор полиномов).

			gl_var
		|	input gl_var
		;

gl_var	:	// Обработка выражений с глобальными переменными.

			CMD_PRINT ' ' convol
			{
				print(&$3);
				debug(1001, &$3);
			}
		|	GL_VAR '=' convol
			{
				struct variable *var = get_variable_by_name($1);
				init_variable(var, $1, &$3);

				debug(1002, &var->polynom);
			}
		;

convol	:	// Обработка выражения с переменной или без.

			num_convol
			{
				init_polynomial(&$$, '\0', NULL);
				set_coef(&$$, 0, $1);

				debug(1, &$$);
			}
		|	var_convol
			{
				init_polynomial(&$$, $1.name, $1.coefs);

				debug(2, &$$);
			}
		;

var_convol	: // Калькулятор числа + переменные.

			GL_VAR	// Да да. Мы оперируем калькулятором "числа + переменные"
			{		// как калькулятором полиномов ($A + $B). И это работает!
				struct variable *var = get_variable_by_name($1);

				if (!var->is_init)
				{
					char str[128];
					sprintf(str, "Variable '$%c' might not have been initialized!", $1);
					error(str);
					YYABORT;
				} else
					copy_polynomial(&$$, &var->polynom);

				debug(10, &$$);
			}
		|	GL_VAR '^' num_convol
			{
				struct variable *var = get_variable_by_name($1);

				if (!var->is_init)
				{
					char str[128];
					sprintf(str, "Variable '$%c' might not have been initialized!", $1);
					error(str);
					YYABORT;
				}

				if ($3 == 0)
				{
					init_polynomial(&$$, var->polynom.name, NULL);
					$$.coefs[0] = 1;
				} else
				{
					copy_polynomial(&$$, &var->polynom);
					int buf[SIZE];

					for (int k = 1; k < $3; k++)
					{
						memset(buf, 0, sizeof(buf));
						for (int i = SIZE - 1; i >= 0; i--)
						{
							if ($$.coefs[i] == 0) continue;
							for (int j = SIZE - 1; j >= 0; j--)
							{
								if (var->polynom.coefs[j] == 0) continue;
								int coef = $$.coefs[i] * var->polynom.coefs[j];
								if (i + j < SIZE)
									buf[i+j] += coef;
									else if (coef != 0)
									{
										error("Too much degree!");
										YYABORT;
									}
							}
						}
						memcpy($$.coefs, buf, sizeof($$.coefs));
					}
				}

				debug(11, &$$);
			}
		|	LETTER
			{
				init_polynomial(&$$, $1, NULL);
				$$.coefs[1] = 1;

				debug(12, &$$);
			}
		|	LETTER '^' num_convol
			{
				init_polynomial(&$$, $1, NULL);
				if ($3 == 0) $$.coefs[0] = 1;
				else $$.coefs[$3] = 1;

				debug(13, &$$);
			}
		|	'(' var_convol ')'
			{
				copy_polynomial(&$$, &$2);

				debug(14, &$$);
			}
		|	'-' var_convol %prec UMINUS
			{
				copy_polynomial(&$$, &$2);
				for (int i = 0; i < SIZE; i++)
					$$.coefs[i] *= -1;

				debug(15, &$$);
			}
		|	mult_simpl // Сокращенное умножение (2x, 2x^2(3x+1), ...).
			{
				copy_polynomial(&$$, &$1);

				debug(16, &$$);
			}
			// Операции типа "выражение с переменной + выражение с переменной".
		|	var_convol '+' var_convol
			{
				if ($1.name != $3.name && ($1.name != '\0' && $3.name != '\0'))
				{
					error("Expressions have different types of variables!");
					YYABORT;
				}

				$$.name = ($1.name != '\0') ? $1.name : $3.name;
				for (int i = 0; i < SIZE; i++)
				 	$$.coefs[i] = $1.coefs[i] + $3.coefs[i];

				debug(20, &$$);
			}
		|	var_convol '-' var_convol
			{
				if ($1.name != $3.name && ($1.name != '\0' && $3.name != '\0'))
				{
					error("Expressions have different types of variables!");
					YYABORT;
				}

				$$.name = ($1.name != '\0') ? $1.name : $3.name;
				for (int i = 0; i < SIZE; i++)
					$$.coefs[i] = $1.coefs[i] - $3.coefs[i];

				debug(21, &$$);
			}
		|	var_convol '*' var_convol
			{
				if ($1.name != $3.name && ($1.name != '\0' && $3.name != '\0'))
				{
					error("Expressions have different types of variables!");
					YYABORT;
				}

				char name = ($1.name != '\0') ? $1.name : $3.name;
				init_polynomial(&$$, name, NULL);
				for (int i = 0; i < SIZE; i++)
					for (int j = 0; j < SIZE; j++)
					{
						int coef = $1.coefs[i] * $3.coefs[j];
						if (i + j < SIZE)
							$$.coefs[i+j] += coef;
						else if (coef != 0)
						{
							error("Too much degree!");
							YYABORT;
						}
					}

				debug(22, &$$);
			}
		|	var_convol '/' var_convol
			{
				error("You're going to divide a polynomial into a polynomial!");
				YYABORT;

				debug(24, &$$);
			}
			// Операции типа "числовое выражение + выражение с переменной".
		|	num_convol '*' var_convol
			{
				copy_polynomial(&$$, &$3);
				for (int i = 0; i < SIZE; i++)
					$$.coefs[i] *= $1;

				debug(30, &$$);
			}
		|	var_convol '*' num_convol
			{
				copy_polynomial(&$$, &$1);
				for (int i = 0; i < SIZE; i++)
					$$.coefs[i] *= $3;

				debug(31, &$$);
			}
		|	num_convol '/' var_convol
			{
				error("Wrong expression: NUM / VAR!");
				YYABORT;

				debug(32, &$$);
			}
		|	var_convol '/' num_convol
			{
				copy_polynomial(&$$, &$1);
				for (int i = 0; i < SIZE; i++)
					$$.coefs[i] /= $3;

				debug(33, &$$);
			}
		|	var_convol '+' num_convol
			{
				copy_polynomial(&$$, &$1);
				$$.coefs[0] += $3;

				debug(34, &$$);
			}
		|	var_convol '-' num_convol
			{
				copy_polynomial(&$$, &$1);
				$$.coefs[0] -= $3;

				debug(35, &$$);
			}
		|	num_convol '+' var_convol
			{
				copy_polynomial(&$$, &$3);
				$$.coefs[0] += $1;

				debug(36, &$$);
			}
		|	num_convol '-' var_convol
			{
				copy_polynomial(&$$, &$3);
				for (int i = 0; i < SIZE; i++)
					$$.coefs[i] *= -1;

				$$.coefs[0] += $1;

				debug(37, &$$);
			}
		|	'(' var_convol ')' '^' num_convol
			{
				if ($5 == 0)
				{
					init_polynomial(&$$, $2.name, NULL);
					$$.coefs[0] = 1;
				} else
				{
					copy_polynomial(&$$, &$2);
					int buf[SIZE];

					for (int k = 1; k < $5; k++)
					{
						memset(buf, 0, sizeof(buf));
						for (int i = SIZE - 1; i >= 0; i--)
						{
							if ($$.coefs[i] == 0) continue;
							for (int j = SIZE - 1; j >= 0; j--)
							{
								if ($2.coefs[j] == 0) continue;
								int coef = $$.coefs[i] * $2.coefs[j];
								if (i + j < SIZE)
									buf[i+j] += coef;
									else if (coef != 0)
									{
										error("Too much degree!");
										YYABORT;
									}
							}
						}
						memcpy($$.coefs, buf, sizeof($$.coefs));
					}
				}

				debug(38, &$$);
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
				if ($3 == 0)
					$$ = 1;
				else
				{
					$$ = $1;
					for (int j = 1; j < $3; j++)
						$$ *= $1;
				}

				debugN(106, $$);
			}
		|	'-' num_convol %prec UMINUS // Ставим наивысший приоритет.
			{
				$$ = -1 * $2;
				debugN(107, $$);
			}
		|	number
		;

mult_simpl	:	// Сокращенная запись умножения (2x, 2x^2(3x+1), ...).
				// TODO: Исправить - со скобками может работать не стабильно.

			number LETTER
			{
				init_polynomial(&$$, $2, NULL);
				$$.coefs[1] = $1;

				debug(200, &$$);
			}
		|	number LETTER '^' num_convol
			{
				init_polynomial(&$$, $2, NULL);
				if ($4 == 0) $$.coefs[0] = $1;
				else $$.coefs[$4] = $1;

				debug(201, &$$);
			}
		|	mult_simpl '(' var_convol ')'
			{
				if ($1.name != $3.name && ($1.name != '\0' && $3.name != '\0'))
				{
					error("Expressions have different types of variables!");
					YYABORT;
				}

				char name = ($1.name != '\0') ? $1.name : $3.name;
				init_polynomial(&$$, name, NULL);
				for (int i = 0; i < SIZE; i++)
					for (int j = 0; j < SIZE; j++)
					{
						int coef = $1.coefs[i] * $3.coefs[j];
						if (i + j < SIZE)
							$$.coefs[i+j] += coef;
						else if (coef != 0)
						{
							error("Too much degree!");
							YYABORT;
						}
					}

				debug(202, &$$);
			}
		|	'(' var_convol ')' '(' var_convol ')'
			{
				if ($2.name != $5.name && ($2.name != '\0' && $5.name != '\0'))
				{
					error("Expressions have different types of variables!");
					YYABORT;
				}

				char name = ($2.name != '\0') ? $2.name : $5.name;
				init_polynomial(&$$, name, NULL);
				for (int i = 0; i < SIZE; i++)
					for (int j = 0; j < SIZE; j++)
					{
						int coef = $2.coefs[i] * $5.coefs[j];
						if (i + j < SIZE)
							$$.coefs[i+j] += coef;
						else if (coef != 0)
						{
							error("Too much degree!");
							YYABORT;
						}
					}

				debug(203, &$$);
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
		error(str);
		return 0;
	}

	FILE *yyin = NULL;

	int yylex()
	{
		int c;
start:	c = fgetc(yyin);

		// Убираем пустые строки.
		while (c == '\r' || c == '\n')
			c = fgetc(yyin);

		// Определяем однострочный комментарий.
		if (c == '/')
		{
			int c_next = fgetc(yyin);
			if (c_next == '/')
			{
				while (c != '\n' && c != EOF)
					c = fgetc(yyin);

				goto start;
			} else
				ungetc(c_next, yyin);
		}

		// Проверяем на команду.
		char cmd[5] = { 'p', 'r', 'i', 'n', 't' };
		for (int i = 0; i < sizeof(cmd); i++)
		{
			if (c != cmd[i]) break;
			if (i + 1 == sizeof(cmd))
				return (CMD_PRINT);
			c = fgetc(yyin);
		}

		if (c == '#')
		{
			error("Use '//' instead of '#' for comments!");
			YYABORT;
		} else if (c == '$')
		{
			if (isupper(c = fgetc(yyin)))
			{
				yylval.ch = c;
				return (GL_VAR);
			} else
			{
				error("Expected '[A-Z]' after '$'!");
				YYABORT;
				// ungetc(c, yyin);
			}
		} else if (isdigit(c))
		{
			yylval.num = c - '0';
			return (DIGIT);
		} else if (islower(c))
		{
			yylval.ch = c;
			return (LETTER);
		}

		return (c);
	}

	void init()
	{
		memset(vars, 0, sizeof(vars));
		for (int i = 0; i < VARS_SIZE; i++)
			vars[i].name = 'A' + i;
	}

	int main()
	{
		init();

		yyin = fopen("../input.txt", "r");
		if (yyin == NULL)
		{
			yyerror("file was not opened");
			system("pause");
			return 0;
		}

		if (!yyparse())
			printf("\nyyparse(): parsing successful! :)\n\n");
		else
			printf("\nyyparse(): error during parsing! :(\n\n");

		fclose(yyin);
		system("pause");
		return 0;
	}
