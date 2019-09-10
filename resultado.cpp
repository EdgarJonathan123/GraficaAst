#include "resultado.h"

Resultado::Resultado()
{
    linea = 0;
    columna = 0;
    tipo = 0;
    valor = "";
    //variable="";
   // variable = Varmas("null");

}

Resultado::Resultado(int l, int c, int t, QString v)
{
    linea = l;
    columna = c;
    tipo = t;
    valor = v;
   // variable="";
   // variable = Varmas("null");
}
