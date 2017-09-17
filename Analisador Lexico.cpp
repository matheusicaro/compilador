#include <iostream>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
		char entrada[80],lexeme[40];
		int i,j,estado, ponto; //i caminha em entrada e j em lexeme
		cout<<"Digite uma sequencia termine com 'ESPACO' + '!'"<<"\n";
	
	
		gets(entrada); //GETS faz a leitura de todos caracteres ate enter.
		i = j = 0;
		estado = 1;
		
		
		while(entrada [i] != '!'){
			switch(estado){
//________________________________________________________________________________________________________IDENTIFICADOR_______________________________________________________________	
				
				case 1:  
					while(entrada[i] == ' '){
					i++;
					}
					// * * * * * * função isalpha testa caracter se é letra
					if(isalpha(entrada[i])){
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
// * função isdigit testa o caracter se é digito
					while(isalpha(entrada[i]) || (isdigit(entrada[i]))){
						lexeme[j] = entrada[i];
						i++;
						j++;
					}
					estado = 3;
					break;
				
				case 3:
//* depois de encontrado a token, completa com o \0 que representa fim de caracter para a função isalpha				
					lexeme [j] = '\0'; 
					cout<<"\nTOKEN......: IDENTIFICADOR"<< "\n";
					cout<<"LEXEME.....: " << lexeme << "\n"; 
//Reinicio da maquina
					estado = 1;  
					j = 0;
					break;
				
//___________________________________________________________________________________________________CONSTANTE_______________________________________________________________
//maquina para analise lexica de uma CONSTANTE				
				case 4:
	 				
					 if (isdigit(entrada[i]) || entrada[i] == '+' || entrada[i] == '-'){
						if(isdigit(entrada[i+ 1])){
							lexeme[j] = entrada[i];
							estado = 5;
							break;
						}
						else{
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
					while (isdigit(entrada[i]) || entrada[i] == '.'){
//tratamento de ponto, caso ocorra entrada com 2 pontos seguidos
						if(entrada[i] == '.'){
							ponto++;
							if(ponto > 1){ 
								estado = 13; //infomar erro do analisador lexico
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
					
					lexeme [j]='\0';
					cout<<"\nTOKEN......: CONSTANTE"<< "\n";
					cout<<"LEXEME.....: " << lexeme << "\n"; 
//Reinicio da maquina
					estado = 1;  
					j = 0;
					break;	
				
//___________________________________________________________________________________________________RELOP_______________________________________________________________
//maquina para analise lexica de um RELOP				
				case 7:
				
					if (entrada[i] == '<'){
						lexeme[j] = entrada[i];
						i++;
						j++;
						estado = 8; //estado que verifica se tem '>' ou '=', que completa o RELOP: <>, <=
						break;	
					}
					else if (entrada[i] == '>'){
						lexeme[j] = entrada[i];
						i++;
						j++;
						estado = 9; //estado que verifica se tem '=', que completa o RELOP: >=
						break;
					}
					else if (entrada[i] == '='){
						lexeme[j] = entrada[i];
						i++;
						j++;
						estado = 10; //estado de final com o RELOP: =
						break;
					}
					else estado = 11;//* * * * * * caso não seja constante, vai para proxima maquina
					break;
	
				case 8:
					if(entrada[i] =='>'){
						lexeme[j] = entrada[i];
						estado = 10; //estado final com o RELOP: <>
						i++;
						j++;
						break;
					}
					else if (entrada[i] =='='){
						lexeme[j] = entrada[i];
						estado = 10; //estado final com o RELOP: <=
						i++;
						j++;
						break;
					}else{
						estado = 10; //estado final com o RELOP: <
						break;
					}
						
				case 9:
					
					if (entrada[i] == '='){
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
					
					lexeme [j]='\0';
					cout<<"\nTOKEN......: RELOP"<< "\n";
					cout<<"LEXEME.....: " << lexeme << "\n"; 
					
					estado = 1;  
					j = 0;
					break;
//___________________________________________________________________________________________________ADDOP_______________________________________________________________
//maquina para analise lexica de um ADDOP			
				case 11:
					
					if (entrada[i] == '+' || entrada[i] == '-'){
						lexeme[j] = entrada[i];
						i++;
						j++;
						estado = 12; //estado final com o ADDOP: + ou -
						break;	
					}
					else estado = 13; //Caso não seja ADDOP, proxima maquina
					break;
				
				case 12:

					lexeme [j]='\0';
					cout<<"\nTOKEN......: ADDOP"<< "\n";
					cout<<"LEXEME.....: " << lexeme << "\n"; 
//Reinicio da maquina
					estado = 1;  
					j = 0;
					break;
//___________________________________________________________________________________________________MULOP_______________________________________________________________
//maquina para analise lexica de um MULOP
				case 13:
					
					if (entrada[i] == '*' || entrada[i] == '/'){
						lexeme[j] = entrada[i];
						i++;
						j++;
						estado = 14;
						break;	
					} else {
						cout<<"\n\n\nERRO LEXICO, REVISE SEU CODIGO"<< "\n";
						gets(entrada);
					}
				
				case 14:
					
					lexeme [j]='\0';
					cout<<"\nTOKEN......: ADDOP"<< "\n";
					cout<<"LEXEME.....: " << lexeme << "\n"; 
//Reinicio da maquina
					estado = 1;  
					j = 0;
					break;
				
			}
		
		}
	return 0;
}

