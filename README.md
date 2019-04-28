# Polynomial calculator

Steps to success:
1. bison.exe -y -d ../project.y (this is optional, already in VS settings)
2. VS -> run project

An example of an entry of the polynomial (lab 1):
```
 x^2+3x^5-1                                  ->	3x^5+x^2-1
 (4x^3-10x^3)^2                              ->	36x^6
 (4x^3-10x^3)*(4^5-4^5)^2                    ->	0
 2x(4x^3-10x^3)(4^2^2^2+5x^5-4^2^2)          ->	-60x^9-783360x^4
 -4+(-2x^2+4x^3*(x^(2*2-1)*2+1))(x^2+1)+7*1  ->	8x^8+8x^6+4x^5-2x^4+4x^3-2x^2+3
```
Or you can use lab 2 features (example of input.txt):
```
// You can leave comments here
$A=x^2+3x^5-1
print $A
$B=10x+2-3x^5+7x^6
print $B
$C=($A+$B)+3x^7
// Note for this assignment:
$D=$C
print $D+10*3+7
// Here we use another variable:
$G=(21z^10-4z)^1
$G=$G-$G
print $G
```
And output for this:
```
[OUT]: 3x^5+x^2-1
[OUT]: 7x^6-3x^5+10x+2
[OUT]: 3x^7+7x^6+x^2+10x+38
[OUT]: 0
```

Please, note:
 * Max. degree of a polynomial = SIZE;
 * For remove debug messages just remove "#define DEBUG" in .y file.

The following errors will be caught:
 * Lexical:
    * only [A-Z] after $;
    * use '//' instead of '#' for comments;
 * Syntax:
    * numerical expression / expression with a var.;
    * expression with a var. / expression with a var.;
 * Semantic:
    * too much degree (> SIZE);
    * different types of variables in an expression;
    * variable $[A-Z] might not have been initialized.