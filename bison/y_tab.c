
/*  A Bison parser, made from ../project.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	DIGIT	258
#define	LETTER	259
#define	UMINUS	260

#line 4 "../project.y"

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

#line 86 "../project.y"
typedef union { int num; int coef_arr[SIZE]; char var_name; } YYSTYPE;

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		72
#define	YYFLAG		-32768
#define	YYNTBASE	13

#define YYTRANSLATE(x) ((unsigned)(x) <= 260 ? yytranslate[x] : 19)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    11,
    12,     7,     5,     2,     6,     2,     8,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     9,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,    10
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     4,     6,     8,    12,    16,    19,    21,    25,
    29,    33,    37,    41,    45,    49,    53,    57,    61,    65,
    69,    75,    79,    83,    87,    91,    95,    99,   102,   104,
   107,   112,   117,   124,   126
};

static const short yyrhs[] = {    14,
     0,    16,     0,    15,     0,     4,     0,     4,     9,    16,
     0,    11,    15,    12,     0,     6,    15,     0,    17,     0,
    15,     5,    15,     0,    15,     6,    15,     0,    15,     7,
    15,     0,    15,     8,    15,     0,    16,     7,    15,     0,
    15,     7,    16,     0,    16,     8,    15,     0,    15,     8,
    16,     0,    15,     5,    16,     0,    15,     6,    16,     0,
    16,     5,    15,     0,    16,     6,    15,     0,    11,    15,
    12,     9,    16,     0,    11,    16,    12,     0,    16,     5,
    16,     0,    16,     6,    16,     0,    16,     7,    16,     0,
    16,     8,    16,     0,    16,     9,    16,     0,     6,    16,
     0,    18,     0,    18,     4,     0,    18,     4,     9,    16,
     0,    17,    11,    15,    12,     0,    11,    15,    12,    11,
    15,    12,     0,     3,     0,    18,     3,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   106,   112,   119,   127,   136,   143,   149,   156,   163,   170,
   177,   195,   203,   210,   217,   224,   232,   239,   246,   253,
   262,   293,   300,   305,   310,   315,   320,   327,   332,   335,
   344,   351,   369,   389,   393
};

static const char * const yytname[] = {   "$","error","$undefined.","DIGIT",
"LETTER","'+'","'-'","'*'","'/'","'^'","UMINUS","'('","')'","main","convol",
"var_convol","num_convol","mult_simpl","number",""
};
#endif

static const short yyr1[] = {     0,
    13,    14,    14,    15,    15,    15,    15,    15,    15,    15,
    15,    15,    15,    15,    15,    15,    15,    15,    15,    15,
    15,    16,    16,    16,    16,    16,    16,    16,    16,    17,
    17,    17,    17,    18,    18
};

static const short yyr2[] = {     0,
     1,     1,     1,     1,     3,     3,     2,     1,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     5,     3,     3,     3,     3,     3,     3,     2,     1,     2,
     4,     4,     6,     1,     2
};

static const short yydefact[] = {     0,
    34,     4,     0,     0,     1,     3,     2,     8,    29,     0,
     7,    28,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    35,    30,     0,     0,     5,    29,
     6,    22,     9,    17,    10,    18,    11,    14,    12,    16,
    19,    23,    20,    24,    13,    25,    15,    26,    27,     0,
     0,     0,    28,     0,     0,     0,     0,     0,     0,     0,
    32,    31,    23,    24,    25,    26,    21,     0,    33,     0,
     0,     0
};

static const short yydefgoto[] = {    70,
     5,     6,    51,     8,     9
};

static const short yypact[] = {     2,
-32768,     5,     2,     2,-32768,    25,   108,    24,     8,    23,
-32768,-32768,    78,    61,     2,     2,     2,     2,     2,     2,
     2,     2,    23,     2,-32768,    35,    23,    23,    42,    43,
    -2,-32768,    -6,    41,    -6,    41,-32768,    42,-32768,    42,
    -6,    41,    -6,    41,-32768,    42,-32768,    42,    42,    92,
   108,    23,-32768,    70,    23,    23,    23,    23,    23,     2,
-32768,    42,    54,    54,    42,    42,    42,   100,-32768,    53,
    71,-32768
};

static const short yypgoto[] = {-32768,
-32768,    21,     0,-32768,    37
};


#define	YYLAST		117


static const short yytable[] = {     7,
    17,    18,    12,    14,     1,     2,    59,     3,    60,    29,
    25,    26,     4,    10,    34,    36,    38,    40,    42,    44,
    46,    48,    49,    11,    13,     1,    53,    54,    27,    15,
    16,    17,    18,    28,    24,    33,    35,    37,    39,    41,
    43,    45,    47,    52,    50,    25,    30,    21,    22,    23,
    23,    62,    71,     0,    63,    64,    65,    66,    67,    30,
    57,    58,    23,    30,    30,    19,    20,    21,    22,    23,
    72,     0,    32,     0,    55,    56,    57,    58,    23,     0,
    68,    32,    15,    16,    17,    18,     0,     0,    30,    31,
     0,    30,    30,    30,    30,    30,    15,    16,    17,    18,
     0,     0,     0,    61,    15,    16,    17,    18,     0,     0,
     0,    69,    19,    20,    21,    22,    23
};

static const short yycheck[] = {     0,
     7,     8,     3,     4,     3,     4,     9,     6,    11,    10,
     3,     4,    11,     9,    15,    16,    17,    18,    19,    20,
    21,    22,    23,     3,     4,     3,    27,    28,     6,     5,
     6,     7,     8,    11,    11,    15,    16,    17,    18,    19,
    20,    21,    22,     9,    24,     3,    10,     7,     8,     9,
     9,    52,     0,    -1,    55,    56,    57,    58,    59,    23,
     7,     8,     9,    27,    28,     5,     6,     7,     8,     9,
     0,    -1,    12,    -1,     5,     6,     7,     8,     9,    -1,
    60,    12,     5,     6,     7,     8,    -1,    -1,    52,    12,
    -1,    55,    56,    57,    58,    59,     5,     6,     7,     8,
    -1,    -1,    -1,    12,     5,     6,     7,     8,    -1,    -1,
    -1,    12,     5,     6,     7,     8,     9
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */
   
#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 107 "../project.y"
{
				finalOutput(yyvsp[0].coef_arr);
			;
    break;}
case 2:
#line 113 "../project.y"
{
				memset(yyval.coef_arr, 0, sizeof(yyval.coef_arr));
				yyval.coef_arr[0] = yyvsp[0].num;

				debug(1, yyval.coef_arr);
			;
    break;}
case 3:
#line 120 "../project.y"
{
				memcpy(yyval.coef_arr, yyvsp[0].coef_arr, sizeof(yyval.coef_arr));

				debug(2, yyval.coef_arr);
			;
    break;}
case 4:
#line 130 "../project.y"
{
				memset(yyval.coef_arr, 0, sizeof(yyval.coef_arr));
				yyval.coef_arr[1] = 1;

				debug(10, yyval.coef_arr);
			;
    break;}
case 5:
#line 137 "../project.y"
{
				memset(yyval.coef_arr, 0, sizeof(yyval.coef_arr));
				yyval.coef_arr[yyvsp[0].num] = 1;

				debug(11, yyval.coef_arr);
			;
    break;}
case 6:
#line 144 "../project.y"
{
				memcpy(yyval.coef_arr, yyvsp[-1].coef_arr, sizeof(yyval.coef_arr));

				debug(12, yyval.coef_arr);
			;
    break;}
case 7:
#line 150 "../project.y"
{
				for (int i = 0; i < SIZE; i++)
					yyval.coef_arr[i] = -1 * yyvsp[0].coef_arr[i];

				debug(13, yyval.coef_arr);
			;
    break;}
case 8:
#line 157 "../project.y"
{
				memcpy(yyval.coef_arr, yyvsp[0].coef_arr, sizeof(yyval.coef_arr));

				debug(14, yyval.coef_arr);
			;
    break;}
case 9:
#line 164 "../project.y"
{
				for (int i = 0; i < SIZE; i++)
					yyval.coef_arr[i] = yyvsp[-2].coef_arr[i] + yyvsp[0].coef_arr[i];

				debug(20, yyval.coef_arr);
			;
    break;}
case 10:
#line 171 "../project.y"
{
				for (int i = 0; i < SIZE; i++)
					yyval.coef_arr[i] = yyvsp[-2].coef_arr[i] - yyvsp[0].coef_arr[i];

				debug(21, yyval.coef_arr);
			;
    break;}
case 11:
#line 178 "../project.y"
{
				memset(yyval.coef_arr, 0, sizeof(yyval.coef_arr));
				for (int i = 0; i < SIZE; i++)
					for (int j = 0; j < SIZE; j++)
					{
						int coef = yyvsp[-2].coef_arr[i] * yyvsp[0].coef_arr[j];
						if (i + j < SIZE)
							yyval.coef_arr[i+j] += coef;
						else if (coef != 0)
						{
							error("Too much degree!");
							break;
						}
					}

				debug(22, yyval.coef_arr);
			;
    break;}
case 12:
#line 196 "../project.y"
{
				memset(yyval.coef_arr, 0, sizeof(yyval.coef_arr));
				error("You're going to divide a polynomial into a polynomial!");

				debug(24, yyval.coef_arr);
			;
    break;}
case 13:
#line 204 "../project.y"
{
				for (int i = 0; i < SIZE; i++)
					yyval.coef_arr[i] = yyvsp[-2].num * yyvsp[0].coef_arr[i];

				debug(30, yyval.coef_arr);
			;
    break;}
case 14:
#line 211 "../project.y"
{
				for (int i = 0; i < SIZE; i++)
					yyval.coef_arr[i] = yyvsp[0].num * yyvsp[-2].coef_arr[i];

				debug(31, yyval.coef_arr);
			;
    break;}
case 15:
#line 218 "../project.y"
{
				memcpy(yyval.coef_arr, yyvsp[0].coef_arr, sizeof(yyval.coef_arr));
				error("Wrong expression: NUM / VAR!");

				debug(32, yyval.coef_arr);
			;
    break;}
case 16:
#line 225 "../project.y"
{
				memcpy(yyval.coef_arr, yyvsp[-2].coef_arr, sizeof(yyval.coef_arr));
				for (int i = 0; i < SIZE; i++)
					yyval.coef_arr[i] /= yyvsp[0].num;

				debug(33, yyval.coef_arr);
			;
    break;}
case 17:
#line 233 "../project.y"
{
				memcpy(yyval.coef_arr, yyvsp[-2].coef_arr, sizeof(yyval.coef_arr));
				yyval.coef_arr[0] += yyvsp[0].num;

				debug(34, yyval.coef_arr);
			;
    break;}
case 18:
#line 240 "../project.y"
{
				memcpy(yyval.coef_arr, yyvsp[-2].coef_arr, sizeof(yyval.coef_arr));
				yyval.coef_arr[0] -= yyvsp[0].num;

				debug(35, yyval.coef_arr);
			;
    break;}
case 19:
#line 247 "../project.y"
{
				memcpy(yyval.coef_arr, yyvsp[0].coef_arr, sizeof(yyval.coef_arr));
				yyval.coef_arr[0] += yyvsp[-2].num;

				debug(36, yyval.coef_arr);
			;
    break;}
case 20:
#line 254 "../project.y"
{
				for (int i = 0; i < SIZE; i++)
					yyval.coef_arr[i] = -1 * yyvsp[0].coef_arr[i];

				yyval.coef_arr[0] += yyvsp[-2].num;

				debug(37, yyval.coef_arr);
			;
    break;}
case 21:
#line 263 "../project.y"
{
				int buf[SIZE];
				memcpy(yyval.coef_arr, yyvsp[-3].coef_arr, sizeof(yyval.coef_arr));

				for (int k = 1; k < yyvsp[0].num; k++)
				{
					memset(buf, 0, sizeof(buf));
					for (int i = SIZE - 1; i >= 0; i--)
					{
						if (yyval.coef_arr[i] == 0) continue;
						for (int j = SIZE - 1; j >= 0; j--)
						{
							if (yyvsp[-3].coef_arr[j] == 0) continue;
							int coef = yyval.coef_arr[i] * yyvsp[-3].coef_arr[j];
							if (i + j < SIZE)
								buf[i+j] += coef;
							else if (coef != 0)
							{
								error("Too much degree!");
								break;
							}
						}
					}
					memcpy(yyval.coef_arr, buf, sizeof(yyval.coef_arr));
				}

				debug(38, yyval.coef_arr);
			;
    break;}
case 22:
#line 296 "../project.y"
{
				yyval.num = yyvsp[-1].num;
				debugN(101, yyval.num);
			;
    break;}
case 23:
#line 301 "../project.y"
{
				yyval.num = yyvsp[-2].num + yyvsp[0].num;
				debugN(102, yyval.num);
			;
    break;}
case 24:
#line 306 "../project.y"
{
				yyval.num = yyvsp[-2].num - yyvsp[0].num;
				debugN(103, yyval.num);
			;
    break;}
case 25:
#line 311 "../project.y"
{
				yyval.num = yyvsp[-2].num * yyvsp[0].num;
				debugN(104, yyval.num);
			;
    break;}
case 26:
#line 316 "../project.y"
{
				yyval.num = yyvsp[-2].num / yyvsp[0].num;
				debugN(105, yyval.num);
			;
    break;}
case 27:
#line 321 "../project.y"
{
				yyval.num = yyvsp[-2].num;
				for (int j = 1; j < yyvsp[0].num; j++)
					yyval.num *= yyvsp[-2].num;
				debugN(106, yyval.num);
			;
    break;}
case 28:
#line 328 "../project.y"
{
				yyval.num = -1 * yyvsp[0].num;
				debugN(107, yyval.num);
			;
    break;}
case 30:
#line 338 "../project.y"
{
				memset(yyval.coef_arr, 0, sizeof(yyval.coef_arr));
				yyval.coef_arr[1] = yyvsp[-1].num;

				debug(200, yyval.coef_arr);
			;
    break;}
case 31:
#line 345 "../project.y"
{
				memset(yyval.coef_arr, 0, sizeof(yyval.coef_arr));
				yyval.coef_arr[yyvsp[0].num] = yyvsp[-3].num;

				debug(201, yyval.coef_arr);
			;
    break;}
case 32:
#line 352 "../project.y"
{
				memset(yyval.coef_arr, 0, sizeof(yyval.coef_arr));
				for (int i = 0; i < SIZE; i++)
					for (int j = 0; j < SIZE; j++)
					{
						int coef = yyvsp[-3].coef_arr[i] * yyvsp[-1].coef_arr[j];
						if (i + j < SIZE)
							yyval.coef_arr[i+j] += coef;
						else if (coef != 0)
						{
							error("Too much degree!");
							break;
						}
					}

				debug(202, yyval.coef_arr);
			;
    break;}
case 33:
#line 370 "../project.y"
{
				memset(yyval.coef_arr, 0, sizeof(yyval.coef_arr));
				for (int i = 0; i < SIZE; i++)
					for (int j = 0; j < SIZE; j++)
					{
						int coef = yyvsp[-4].coef_arr[i] * yyvsp[-1].coef_arr[j];
						if (i + j < SIZE)
							yyval.coef_arr[i+j] += coef;
						else if (coef != 0)
						{
							error("Too much degree!");
							break;
						}
					}

				debug(203, yyval.coef_arr);
			;
    break;}
case 34:
#line 390 "../project.y"
{
				yyval.num = yyvsp[0].num;
			;
    break;}
case 35:
#line 394 "../project.y"
{
				yyval.num = yyvsp[-1].num * 10 + yyvsp[0].num;
			;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 399 "../project.y"
      /* начало секции подпрограмм */

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
