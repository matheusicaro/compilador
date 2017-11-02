#include <iostream>
#include <string.h>
#define identificador 256	//defini constante para reconhecimento de ID
#define MULOP 257	//defini constante para reconhecimento de MULOP
#define ADDOP 258	//defini constante para reconhecimento de ADDOP
using namespace std;

	bool desempenho = false;  //variavel global para controle de desempenho


//FUNÇÕES: Tabela das Palavras Reservadas ################################################################################################################################################################### 

//Amarrando os dados em uma tabela de sinais.  struct: função para criação de tipo de dado
	struct Dado{
		char lexem [1000]; 	//vetor para guardar as palavras reservadas do analisador
		int tipo;			//token para definição do tipo das palavras reservadas
	};

	Dado ts[100];		//vetor de tipo DADO, tabela.
	int t=0; 			//variavel global para controle da tabela
	
//Função para cadastrar as palavras reservadas do compilador
	void instala () {
			
		ts[t].tipo = ADDOP;																    //         entrada |  tipo
		strcpy(ts[t].lexem, "or"); //instalando and na posição da tabela de registro		//		  ---------|-----------	
		t++;																				//     0 |   or    |   addop  |
																							// 	   1 |  and    |   mulop  |
		ts[t].tipo = MULOP;																	//	   2 |  mod    |   mulop  |
		strcpy(ts[t].lexem, "and"); //instalando and na posição da tabela de registro		//	   3 |  div    |   mulop  |
		t++;																				//        --------------------
		
		ts[t].tipo = MULOP;
		strcpy (ts[t].lexem, "mod"); //instalando and na posição da tabela de registro
		t++;
		
		ts[t].tipo = MULOP;
		strcpy (ts[t].lexem, "div"); //instalando and na posição da tabela de registro
		t++;
	}

//função para realizar a busca na tabela de simbolos para o tipo da token recebida na entrada.	
	busca (char entrada[]){
		int cont=0;
		for (int k=0; k<t; k++){
			
			if (strcmp (ts[k].lexem, entrada) == 0){	//se a entrada constar na tabela, é mostrado o tipo da token. f(strcmp): compara string com string, e char com char.
				return ts[k].tipo;
				break;
			}else{
				cont++;
			}
		}
		if (cont > 3){
			return identificador; //se não é encontrado na tabela, logo é um identificador
		}
	}

//FUNÇÃO: Analisador Lexico ################################################################################################################################################################################# 
	
	analisaLexico(char entrada[]){
		
		char lexeme[1000];
		int i,j,estado, ponto=0; //i caminha em entrada e j em lexeme

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
						if (isdigit(entrada[i])){ desempenho = true; }		//caso contenha algum digito, não precisa chamar a tabela de sinais
						lexeme[j] = entrada[i];
						i++;
						j++;
					}
					estado = 3;
					break;
				
				case 3:
//* depois de encontrado a token, completa com o \0 que representa fim de caracter para a função isalpha				
					lexeme [j] = '\0';
					
					if(desempenho == true) {			//caso contenha digito na em alguma parte da entrada, é um identificador. Caso contrario, verifica-se qual o tipo da token
						
						cout<<"\nTOKEN......: IDENTIFICADOR"<< "\n";
						cout<<"LEXEME.....: " << lexeme << "\n"; 
						desempenho = false;
					}else{
						
						instala();
						
						if (busca(lexeme) == 256 ) {
			
							cout<<"\nTOKEN......: IDENTIFICADOR "<< "\n";
							cout<<"LEXEME.....: " << lexeme << "\n"; 
						}
						else if(busca(lexeme) == 258){
	
							cout<<"\nTOKEN......: ADDOP "<< "\n";
							cout<<"LEXEME.....: " << lexeme << "\n"; 
		
						}else{
		
							cout<<"\nTOKEN......: MULOP "<< "\n";
							cout<<"LEXEME.....: " << lexeme << "\n";
						}
					}
			
//Reinicio da maquina
					estado = 1;  
					j = 0;
					break;
				
//___________________________________________________________________________________________________CONSTANTE_______________________________________________________________
//maquina para analise lexica de uma CONSTANTE				
				case 4:
	 				
					 if (isdigit(entrada[i]) || entrada[i] == '+' || entrada[i] == '-'){
						if(isdigit(entrada[i+ 1]) || isdigit(entrada[i])){
							lexeme[j] = entrada[i];
							estado = 5;
							break;
						}
						else if(isdigit(entrada[i-1]) && isdigit(entrada[i+1])){
							estado = 11; //caso o proximo não seja um digito, assegura que + é um ADDOP
							break;
						}else{
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
							if(isdigit(entrada[i+1]) == false){ //na regra de negocio, so aceita um digito + ponto + digito, caso seja digito + ponto + outro, o ponto é um lexeme.
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
						lexeme[j] = entrada[i];
						i++;
						cout<<"\n** LEXEME.....: "<<lexeme[j]<<"\n";
						estado = 1;  
						j = 0;
						break;
					}
				
				case 14:
					
					lexeme [j]='\0';
					cout<<"\nTOKEN......: MULOP"<< "\n";
					cout<<"LEXEME.....: " << lexeme << "\n"; 
//Reinicio da maquina
					estado = 1;  
					j = 0;
					break;
				
			}
		
		}
		
	
	}//end lexico




int main(int argc, char** argv) {
	
		char entrada[1000];
		cout<<"----------------------------\n";	
		cout<<"ATENCAO: Regras da Linguagem\n"<<"----------------------------\n"<<"1) A Entrada tem que terminar com 'ESPACO' + '!'"<<"\n2) Operadores ''Mulop' e 'Addop' sao reconhecidos\n   em minusculo, caso contrario sera constante"<<"\n----------------------------";
	 	cout<<"\n\nDigite sua entrada:";
		gets(entrada); //GETS faz a leitura de todos caracteres ate enter.
	
		analisaLexico(entrada);
		
		
	return 0;
}
