# Polynomial calculator

Steps to success:
1. bison.exe -y -d ../project.y
2. VS -> run project

An example of an entry of the polynomial:
```
 x^2+3x^5-1                                  ->	3x^5+x^2-1
 (4x^3-10x^3)^2                              ->	36x^6
 (4x^3-10x^3)*(4^5-4^5)^2                    ->	0
 2x(4x^3-10x^3)(4^2^2^2+5x^5-4^2^2)          ->	-60x^9-783360x^4
 -4+(-2x^2+4x^3*(x^(2*2-1)*2+1))(x^2+1)+7*1  ->	8x^8+8x^6+4x^5-2x^4+4x^3-2x^2+3
```