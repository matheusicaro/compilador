package Compilador;

public class Sintatico {
    
    Lexico aux = new Lexico ();
    //int avancaI = 0;
    //int controleLoop=0;
    int i=0;
    char entrada[];
    
    int A (char ent[], int j)
    {
        i = j;
        String str = String.valueOf(ent);
        entrada = str.toCharArray();
        
            if (B () == 1){
                if (R1 () == 1){
                    if((i+2) == entrada.length)
                        {return 1;}
                    System.out.println("\n* Erro na posicao: "+i+" = '"+entrada[i]+"'");
                    return 0;
                }
            }
            System.out.println("\n* Erro na posicao: "+i+" = '"+entrada[i]+"'");
            return 0; //sintaticamente incorreto
    }

    int R1 ()
    {
        int guarda = i;
        /*
        1: if(analisaLexico() == ',')
        {
        2:    if (B() == 1){
        3:        if(R1 () == 1)
        4:            return 1;
            }
        }
        else {return 1;} //lambda
        */
        if(true){                           /*  1:  Linha 1 da condição do comentario acima */
            aux.analisaLexico(entrada,i);
            if (aux.retornoToken == 88)     //88 == Virgula
            {                               /*  1:  Fim */
                i = aux.avancaI; //depois que leu a ',' avança para proxima posicao do vetor
                if(B() == 1)
                {
                    if(R1 () == 1)
                        return 1; 
                }
            }
        }
        i = guarda;
        return 1; //lambda
    }

    int B ()
    {
        int guarda = i;
        
        if (C() == 1)
        {
            if(true)
            {
                aux.analisaLexico(entrada, i);
                if(aux.retornoToken == 33)  // 33 == RELOP
                {
                    i = aux.avancaI;
                    if(C() == 1){return 1;}
                } 
            }
        } 
        
        i = guarda;
        if (C() == 1)
        {
            return 1;
        }
        
        return 0;
    }

    int C()
    {
        if(D() == 1)
        {
            if (R2() == 1)
                return 1;
        }
        return 0;
    }

    int R2 ()
    {
        int guarda = i;
        
        if(true)
        {
            aux.analisaLexico(entrada, i);
            if(aux.retornoToken == 44)  // 44 == ADDOP
            {
                i = aux.avancaI;
                if(D() == 1)
                {
                   if(R2 () == 1)
                         return 1;
                }
            }
        }
        
        i = guarda;
        return 1; //lambda
    } 

    int D ()
    {
        if (E() == 1)
        {   
            if(R3 () == 1)
                return 1;
        }
        
        return 0;
    }

    int R3 ()
    {
        int guarda = i;
        if(true)
        {
            aux.analisaLexico(entrada, i);
            i = aux.avancaI;
            if(aux.retornoToken == 55)  // 55 == MULOP
            {
                if(E() == 1)
                {
                    if(R3() == 1)
                    { return 1; }
                }
                //else return 0; //retirei o erro da entrada id ** id, not id! AQUI!!
            }
        }
        i = guarda;
        return 1;
    } 

    int  E ()
    {
        int Break = 0;
        int guarda = i;
        
        if(true)            
        {
            aux.analisaLexico(entrada, i);
            if(aux.retornoToken == 70){  // 70 == '('
                i = aux.avancaI;
                if (B() == 1)     // 'B'
                {
                    aux.analisaLexico(entrada, i);  
                    if(aux.retornoToken == 60){         // 60 == ')'
                        i = aux.avancaI;
                        return 1;
                    }
                }
            }
        }
        
        i = guarda;
        guarda = i;
        
        if(true){
            aux.analisaLexico(entrada, i);
                if(aux.retornoToken == 100){  // 100 == 'not'
                    i = aux.avancaI;
                    if (E() == 1)     // 'E'
                    { return 1; }
                }
                 
        }            
        
        i = guarda;
        guarda = i;    
        
        if(true)       //reconhecendo regra IDENTIFICADOR
        { 
            aux.analisaLexico(entrada, i);
            if (aux.retornoToken == 11) // IDENTIFICADOR == 11
            { 
                i = aux.avancaI; 
                return 1;
            }    
        }
        
        i = guarda;
        guarda = i;
        
        if(true)       //reconhecendo regra CONSTANTE
        { 
            aux.analisaLexico(entrada, i);
            if (aux.retornoToken == 22) // CONSTANTE == 22
            { 
                i = aux.avancaI;
                return 1; 
            }
        }
        
        return 0;
    }
}
