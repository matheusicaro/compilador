package Compilador;

import java.util.Arrays;
import java.util.Scanner;


public class Main {

   
    
    public static void main(String[] args) {
        
    	Scanner ler = new Scanner(System.in);	
        Sintatico aux = new Sintatico ();
        
        System.out.println("-----------------------------------------------");	
	System.out.println("ATENCAO: Regras da Linguagem"+
                "\n-----------------------------------------------\n"+
                "1) A Entrada tem que terminar com: 'ESPACO' + '!'"
                +"\n2) Operadores ''Mulop' e 'Addop' sao reconhecidos\n"+
                "  em minusculo, caso "+"contrario, será constante."+"\n----------------------------");
	System.out.println("\nDIGITE SUA ENTRADA:");
        String n = ler.nextLine();  
        
        char entrada [] = n.toCharArray();
        int i=0;
        int c =0;
        c = aux.A(entrada,i);
        
        if (c == 1){ System.out.println("\n\tSINTATICAMENTE CORRETO");}
        else if(c == 0) { System.out.println("\n\tERRO SINTATICO");}
    }
}
