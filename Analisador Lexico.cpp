#include <iostream>
#include <string.h>
#define identificador 256
#define MULOP 257
#define ADDOP 258
using namespace std;

	
	
int t=0;

//criando struck para amarrar os dados em uma identificação
struct Dado{
	char lexem [40]; //vetor para guardar as palavras reservadas do analisador
	int tipo;	//token para definição do tipo das palavras reservadas
};

Dado ts[100];//vetor para armazernar as identificações.
	
	//cadastro de todas as palavras reservadas do analisador
	void instala () {
			
		ts[t].tipo = ADDOP;
		strcpy(ts[t].lexem, "or"); //instalando and na posição da tabela de registro
		t++;
		
		ts[t].tipo = MULOP;
		strcpy(ts[t].lexem, "and"); //instalando and na posição da tabela de registro
		t++;
		
		ts[t].tipo = MULOP;
		strcpy (ts[t].lexem, "mod"); //instalando and na posição da tabela de registro
		t++;
		
		ts[t].tipo = MULOP;
		strcpy (ts[t].lexem, "div"); //instalando and na posição da tabela de registro
		t++;
	}
	
	busca (char entrada[]){
		int cont=0;
		for (int k=0; k<t; k++){
			
			if (strcmp (ts[k].lexem, entrada) == 0){
				return ts[k].tipo;
				break;
			}else{
				cont++;
			}
		}
		if (cont > 3){
			return identificador;
		}
	}
		

// apenas testes de funcionalidade
int main(int argc, char** argv) {
	
	char entrada[80],lexeme[40];
	int i,j,estado, ponto; //i caminha em entrada e j em lexeme
	cout<<"Digite uma sequencia termine com 'ESPACO' + '!'"<<"\n";
		
	gets(entrada); //GETS faz a leitura de todos caracteres ate enter.
	i = j = 0;
	estado = 1;
	
	instala();
	
	
	if (busca(entrada) == 256 ) {
			
		cout<<"\nTOKEN......: IDENTIFICADOR "<< "\n";
		cout<<"LEXEME.....: " << lexeme << "\n"; 
	}
	else if(busca(entrada) == 258){
	
		cout<<"\nTOKEN......: ADDOP "<< "\n";
		cout<<"LEXEME.....: " << lexeme << "\n"; 
		
	}else{
		
		cout<<"\nTOKEN......: MULOP "<< "\n";
		cout<<"LEXEME.....: " << lexeme << "\n";
	}
				
		


	return 0;
}
