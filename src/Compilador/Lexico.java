package Compilador;

import java.util.Arrays;

public class Lexico {
    
        public static int retornoToken = 0, avancaI = 0;
	static boolean desempenho = false;  //variavel global para controle de desempenho
	//char entrada[] = new char [1000];
	//int i=0;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ANALISADOR LEXICO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//FUNÇÕES: Tabela das Palavras Reservadas ################################################################################################################################################################### 
        //função para realizar a busca na tabela de simbolos para o tipo da token recebida na entrada.	
	public int busca (char lexeme[])
        {
		char mulop_OU_not[] = new char [3];
                char addop [] = new char [2];
                
                for (int i=0; i<3; i++){
                    mulop_OU_not [i] = lexeme[i];
                }
                
                for (int i=0; i<2; i++){
                    addop[i] = lexeme[i];
                }
/*  
                #define identificador 256   Retorno é identificador
                #define MULOP 257           Retorno é MULOP
                #define ADDOP 258           Retorno é ADDOP
*/
                char [] mulopDiv = new char [] {'d','i','v'};
                char [] mulopMod = new char [] {'m','o','d'};
                char [] mulopAnd = new char [] {'a','n','d'};
                char [] not = new char []{'n','o','t'};
                char [] addopOr = new char [] {'o','r'};
                
                if(Arrays.equals(addop, addopOr)){
                    return 258;
                }
                else if (Arrays.equals(mulop_OU_not, mulopDiv)){
                    return 257;                    
                }else if (Arrays.equals(mulop_OU_not, mulopMod)){
                    return 257;
                }else if (Arrays.equals(mulop_OU_not, mulopAnd)){
                    return 257;
                }else if (Arrays.equals(mulop_OU_not, not)){
                    return 100;
                }else{
			return 256; //se não é encontrado na tabela, logo é um identificador
		}
        }

//FUNÇÃO: Analisador Lexico ################################################################################################################################################################################# 

	public void analisaLexico(char entrada[], int i)
        {
		
		char lexeme [] = new char [40];
		//int i,j,estado, ponto=0; //i caminha em entrada e j em lexeme
		//int i = 0;
		int j = 0, estado = 1, ponto = 0;
		
		int reconheceu = 0;
                
		while(entrada [i] != '!' || reconheceu != 0)
                {
                    if(reconheceu != 0){break;}
                    
                    switch(estado)
                        {
//________________________________________________________________________________________________________IDENTIFICADOR_______________________________________________________________	
				
				case 1:  
					while(entrada[i] == ' '){
                                            i++;
					}
					// * * * * * * função isalpha testa caracter se é letra
                                        // * * * * * * || em java = Character.isLetter(letra);
                                        //Character.isDigit(letra);*/
                                        
					if(Character.isLetter(entrada[i])){
						lexeme[j] = entrada[i];
						i++;
						j++;
						estado = 2;
					}
					else{ 
						estado = 4; //caso não seja letra, vai para proxima maquina
						break;
					}
					
				case 2:	
                                        // * * * * * * || em java = Character.isLetter(letra);
					while(Character.isLetter(entrada[i]) || (Character.isDigit(entrada[i]))){
						if (Character.isDigit(entrada[i])){ desempenho = true; }		//caso contenha algum digito, não precisa chamar a tabela de sinais
						lexeme[j] = entrada[i];
						i++;
						j++;
					}
					estado = 3;
					break;
				
				case 3:
//* depois de encontrado a token, completa com o \0 que representa fim de caracter para a função isalpha				
					//lexeme [j] = '\0';
					
                                    if(desempenho == true)
                                    {			//caso contenha digito na em alguma parte da entrada, é um identificador. Caso contrario, verifica-se qual o tipo da token
/* ^^^*/ 					reconheceu = 11;
                                        desempenho = false;
                                        
//                                        return reconheceu = 11; // IDENTIFICADOR == 11
                                        
                                        //System.out.println("\nTOKEN......: IDENTIFICADOR");
					//System.out.println("LEXEME.....: " + lexeme); 
					                                                
                                    }else{
					if (busca(lexeme) == 256 )
                                        {
/* ^^^*/                                            reconheceu = 11; // IDENTIFICADOR == 11
                                            //System.out.println("\nTOKEN......: IDENTIFICADOR");
                                            //System.out.println("LEXEME.....: " + lexeme);         
                                        }
                                        else if(busca(lexeme) == 258)
                                        {
/* ^^^*/                                            reconheceu = 44; // ADDOP == 44
                                            //System.out.println("\nTOKEN......: ADDOP");
                                            //System.out.println("LEXEME.....: " + lexeme);  
                                        }
                                        else if(busca(lexeme) == 100)
                                        {
/* ^^^*/                                            reconheceu = 100; // not == 100
                                            //System.out.println("\nTOKEN......: ADDOP");
                                            //System.out.println("LEXEME.....: " + lexeme);  
                                        }
                                        else
                                        {
/* ^^^*/                                            reconheceu = 55; // MULOP == 55
                                            //System.out.println("\nTOKEN......: MULOP");
                                            // System.out.println("LEXEME.....: " + lexeme);  
                                        }
                                    }
//Reinicio da maquina               
                                    i--;
                                    estado = 1;  
                                    j = 0;
                                    break;
				
                                    
//___________________________________________________________________________________________________CONSTANTE_______________________________________________________________
//maquina para analise lexica de uma CONSTANTE				
				case 4:
	 			    if (Character.isDigit(entrada[i]) || entrada[i] == '+' || entrada[i] == '-')
                                    {
					if(Character.isDigit(entrada[i+ 1]) || Character.isDigit(entrada[i]))
                                        {
                                            lexeme[j] = entrada[i];
                                            estado = 5;
                                            break;
					}
                                        else if(Character.isDigit(entrada[i-1]) && Character.isDigit(entrada[i+1]))
                                        {
                                            estado = 11; //caso o proximo não seja um digito, assegura que + é um ADDOP
                                            break;
					}
                                        else
                                        {
                                            estado = 11; //caso o proximo não seja um digito, assegura que + é um ADDOP
                                            break;
					}
                                    }
                                    else estado = 7;
                                    break;
				
				case 5:
                                    i++;
                                    j++;
                                    ponto = 0;
                                    while (Character.isDigit(entrada[i]) || entrada[i] == '.')
                                    {
                                        //tratamento de ponto, caso ocorra entrada com 2 pontos seguidos
					if(entrada[i] == '.')
                                        {
                                            if(Character.isDigit(entrada[i+1]) == false)
                                            { 
                                                //na regra de negocio, so aceita um digito + ponto + digito, caso seja digito + ponto + outro, o ponto é um lexeme.
                                                estado = 13; //detectado lexeme sem token
                                                break; 
                                            }
                                            ponto++;
                                            if (ponto>1)	//tratamento para não identificar '123.45.6789.0' como contastante, pois a regra é: 12 ou 12.34 
                                            {
                                                ponto = 0;
                                                break;
                                            }
					}
					lexeme[j] = entrada[i];
					i++; 
					j++;
                                    }
                                    estado = 6; //estado final da CONSTANTE
                                    break;
					
				case 6:	
/* ^^^*/                                    reconheceu = 22; // CONSTANTE == 22
                                    //lexeme [j]='\0';
                                    //System.out.println("\nTOKEN......: CONSTANTE");
                                    //System.out.println("LEXEME.....: " + lexeme);
                                    
                                    //Reinicio da maquina
                                    i--;
                                    estado = 1;  
                                    j = 0;
                                    break;	
//___________________________________________________________________________________________________RELOP_______________________________________________________________
//maquina para analise lexica de um RELOP				
				case 7:
                                    if (entrada[i] == '<')
                                    {
					lexeme[j] = entrada[i];
					i++;
					j++;
					estado = 8; //estado que verifica se tem '>' ou '=', que completa o RELOP: <>, <=
					break;	
                                    }
                                    else if (entrada[i] == '>')
                                    {
					lexeme[j] = entrada[i];
					i++;
					j++;
					estado = 9; //estado que verifica se tem '=', que completa o RELOP: >=
					break;
                                    }
                                    else if (entrada[i] == '=')
                                    {
					lexeme[j] = entrada[i];
					i++;
					j++;
					estado = 10; //estado de final com o RELOP: =
					break;
                                    }
                                    else    estado = 11;//* * * * * * caso não seja constante, vai para proxima maquina
                                    break;
                                    
	
				case 8:
                                    if(entrada[i] =='>')
                                    {
                                    	lexeme[j] = entrada[i];
					estado = 10; //estado final com o RELOP: <>
                                            i++;
                                            j++;
                                            break;
                                    }
                                    else if (entrada[i] =='=')
                                    {
					lexeme[j] = entrada[i];
					estado = 10; //estado final com o RELOP: <=
					i++;
					j++;
					break;
                                    }else{
                                        //i++;
					estado = 10; //estado final com o RELOP: <
					break;
                                    }
						
				case 9:
                                    if (entrada[i] == '=')
                                    {
                                        lexeme[j] = entrada[i];
                                        estado = 10; //estado final com o RELOP: =
                                        i++;
                                        j++;
                                        break;
                                    }else{
                                        estado = 10;
                                        break;
                                    }
				
				case 10:
/* ^^^*/                                    reconheceu = 33; // RELOP == 33
                                    
                                    //lexeme [j]='\0';
                                    //System.out.println("\nTOKEN......: RELOP");
                                    //System.out.println("LEXEME.....: " + lexeme);
                                    i--;
                                    estado = 1;  
                                    j = 0;
                                    break;
//___________________________________________________________________________________________________ADDOP_______________________________________________________________
//maquina para analise lexica de um ADDOP			
				case 11:
                                    if (entrada[i] == '+' || entrada[i] == '-')
                                    {
					lexeme[j] = entrada[i];
					i++;
					j++;
					estado = 12; //estado final com o ADDOP: + ou -
					break;	
                                    }
                                    else estado = 13; //Caso não seja ADDOP, proxima maquina
                                    break;
				
				case 12:
/* ^^^*/                                    reconheceu = 44; // ADDOP == 44
                                    //lexeme [j]='\0';
                                    //System.out.println("\nTOKEN......: ADDOP");
                                    //System.out.println("LEXEME.....: " + lexeme); 
                                    
                                    //Reinicio da maquina
                                    i--;
                                    estado = 1;  
                                    j = 0;
                                    break;
//___________________________________________________________________________________________________MULOP_______________________________________________________________
//maquina para analise lexica de um MULOP
				case 13:
                                    if (entrada[i] == '*' || entrada[i] == '/')
                                    {
                                        lexeme[j] = entrada[i];
					i++;
					j++;
					estado = 14;
					break;	
                                    } else {
                                        if (entrada [i] == '!'){
                                            if(entrada [i-1] == ' '){break;}
                                        }
					lexeme[j] = entrada[i];
                                        
                                        if(entrada[i] == ','){
/* ^^^*/                                            reconheceu = 88;      // VIRGULA , == 88
                                                    i++;
                                                    i--;
                                                    estado = 1;  
                                                    j = 0;
                                                    break;                                                    
                                        }else if( entrada [i] == '('){
/* ^^^*/                                            reconheceu = 70;       // PARENTESES '(' == 70
                                                    i++;
                                                    i--;
                                                    estado = 1;  
                                                    j = 0;
                                                    break;                                           
                                        }else if( entrada [i] == ')'){
/* ^^^*/                                            reconheceu = 60;       // PARENTESES ')' == 60
                                                    i++;
                                                    i--;
                                                    estado = 1;  
                                                    j = 0;
                                                    break;   
                                        }					
                                        i++;
/* ^^^*/                                        reconheceu = 9090; // OUTRO LEXEME == 9090
                                        //System.out.println("\n**LEXEME.....: " + lexeme);
					i--;
                                        estado = 1;  
					j = 0;
					break;
                                    }
				
				case 14:
/* ^^^*/                                    reconheceu = 55; // MULOP == 55
                                    
                                    //lexeme [j]='\0';
                                    //System.out.println("\nTOKEN......: MULOP");
                                    //System.out.println("LEXEME.....: " + lexeme);
                                    
                                    //Reinicio da maquina
                                    i--;
                                    estado = 1;  
                                    j = 0;
                                    break;
				
			}
		
		}
                
                
            retornoToken = reconheceu;
            avancaI = i+1;
	
	}//end lexico
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FIM ~~~ ANALISADOR LEXICO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  
    
}//end class lexico
