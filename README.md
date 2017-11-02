# compilador

Construção de um compilador composto por (1) Analisador Léxico, Analisador Sintático, Analisador Semântico.
________________________________________________________________________________________________________________________________________
1. Analisador Léxico - Codigo em C - DevC++
   
  Primeira etapa do projeto, foi o desenvolvimento do algoritimo conforme a gramatica dada, no qual retornar as tokes encontradas como     IDENTIFICADOR, CONSTANTE, RELOP, ADDOP, MULOP. Conforme abaixo:

                                                    Avaliador de Expressão:	 

  Considere a Seguinte Gramática:
  
                             expr_list :=	    expr |	expr_list  ,  expr
                             expr := 	    simple_expr  |	simple_expr    RELOP   simple_expr
                             simple_expr :=     term |	simple_expr   ADDOP   term
                             term :=	    factor |	term  MULOP  factor
                             factor :=	    identifier |	constant |	(  expr  ) | 	not   factor
	
  Considere as seguintes convenções léxicas:

            1.1 Identificadores são definidos pelas seguintes expressões regulares:

                  letter  :=	A  |  B  |  ...  |  Z   |  a  |  b  | ... |  z 
                  digit  :=	        0  |  1  |  ...  |  9
                  identifier  :=	letter  (  letter  |  digit  )*

            1.2 Constantes são definidas da seguinte forma:

                  unsigned_integer	:=	digit   digit*
                  unsigned_real	:=  	digit   digit* .  digit   digit*
                  constant	    :=	    ( + | -  | lambda) ( unsigned_integer  |  unsigned_real )

            1.3 Os operadores de relação  ( RELOP ) são:

                  RELOP	:=	<  |  <= |  >  | >=  |  =  | <>

            1.4 Os operadores de adição ( ADDOP ) são:

                  ADDOP	:=	+  |  -  |  or

            1.5 Os operadores ( MULOP ) são:

                  MULOP	:= 	*  |  /  |  div  |  mod  |  and
________________________________________________________________________________________________________________________________________
