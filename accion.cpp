#include "accion.h"

//******************************************************************************
//*************************** Constructor **************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
accion::accion(){ resultado="";}
//******************************************************************************
//***************************Iniciar ************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
void accion::init(NodoAST *raiz)
{

    //limpiar();
    if(raiz->hijos.at(0).tipo_ == LISTA_CUERPO)
    {

        NodoAST lista = raiz->hijos.at(0);
        ListaCuerpo(&lista);

    }

}
//******************************************************************************
//*************************** LIsta_CUerpo *************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void accion::ListaCuerpo(NodoAST *raiz){

    for (int x= 0; x<  raiz->hijos.size(); x++)
    {
        NodoAST cuerpo = raiz->hijos.at(x);
        Cuerpo(&cuerpo);
    }

}

//******************************************************************************
//*************************** CUerpo *******************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
void accion::Cuerpo(NodoAST*raiz)
{

    switch (raiz->tipo_)
    {

    case LISTA_DECLARACION:
    {
        for (int x= 0; x< raiz->hijos.size(); x++)
        {
            NodoAST nodo = raiz->hijos.at(x);
            declaracion(&nodo);
        }
    }
        break;

    case LISTA_ASIGNACION:
    {
        for (int x= 0; x< raiz->hijos.size(); x++)
        {
            NodoAST nodo = raiz->hijos.at(x);
            asignacion(&nodo);
            //  QTextStream(stdout) << "Asig-> "+QString::number(x)+"valor-> "+raiz->hijos.at(x).valor << endl;
        }


    }
        break;

    case LISTA_IMPRIMIR:
    {
        for (int x= 0; x< raiz->hijos.size(); x++)
        {
            NodoAST nodo = raiz->hijos.at(x);
            imprimir(&nodo);
        }

    }
        break;

    case LISTA_MOSTRAR:
    {
        for (int x= 0; x< raiz->hijos.size(); x++)
        {
            NodoAST nodo = raiz->hijos.at(x);
            sentenciaMostrar(&nodo);
        }
    }
        break;

    case LISTA_IF:
    {
        for (int x= 0; x< raiz->hijos.size(); x++)
        {
            NodoAST nodo = raiz->hijos.at(x);
            sentenciaIf(&nodo);
        }

    }
        break;

    case LISTA_FOR:
    {
        for (int x= 0; x< raiz->hijos.size(); x++)
        {
            NodoAST nodo = raiz->hijos.at(x);
            sentenciaFor(&nodo);
        }

    }
        break;

    case LISTA_REPETIR:
    {
        for (int x= 0; x< raiz->hijos.size(); x++)
        {
            NodoAST nodo = raiz->hijos.at(x);
            sentendiaRepetir(&nodo);
        }

    }
        break;

    }
}
//******************************************************************************
//*************************** Declaracion ************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
void accion::declaracion(NodoAST* raiz)
{

    switch (raiz->tipo_) {

    case DECLARACIONVAR1:
    {
        NodoAST tk_tipo = raiz->hijos.at(0);
        NodoAST listId = raiz->hijos.at(1);
        NodoAST tk_valor = raiz->hijos.at(2);


        int tipo_= tipoDato(&tk_tipo).tipo;

        Resultado r1 =contValor(&tk_valor);
        QString valor = r1.valor;
        int tipo_valor = r1.tipo;

        QTextStream(stdout) << "Valor: ["+valor+"]" << endl;

        declaracionVariable(&listId,tipo_,tipo_valor,valor);

    }
        break;
    case DECLARACIONVAR2:
    {
        NodoAST tk_tipo = raiz->hijos.at(0);
        NodoAST listId = raiz->hijos.at(1);

        int tipo_= tipoDato(&tk_tipo).tipo;
        QString valor = "null";
        declaracionVariable(&listId,tipo_,tipo_,valor);

    }
        break;
    case DECLARACIONARRAY1:
    {
        NodoAST tk_tipo = raiz->hijos.at(0);
        NodoAST listid = raiz->hijos.at(1);
        NodoAST listdimen  = raiz->hijos.at(2);

        QStringList ListaId = getListaid(&listid);
        posicion* coor = coordenadas(&listdimen);
        int tipo = tipoDato(&tk_tipo).tipo;

        declaracionArrayMultidimension(tipo,coor,ListaId);
    }
        break;
    case DECLARACIONARRAY2:
    {
        NodoAST tk_tipo = raiz->hijos.at(0);
        NodoAST listid = raiz->hijos.at(1);
        NodoAST listdimen  = raiz->hijos.at(2);
        NodoAST ARRAY =raiz->hijos.at(3);

        QStringList ListaId = getListaid(&listid);
        posicion* coor = coordenadas(&listdimen);
        int tipo = tipoDato(&tk_tipo).tipo;

        inicializarArrayMulltidimension(tipo,&ARRAY,coor,ListaId);

        // imprimiarMatriz();

    }
        break;
    case DECLARACIONARRAY3:
    {

        NodoAST tk_tipo = raiz->hijos.at(0);
        int tipo_= tipoDato(&tk_tipo).tipo;
        NodoAST listId = raiz->hijos.at(1);
        NodoAST fila = raiz->hijos.at(3);
        NodoAST tam = raiz->hijos.at(2).hijos.at(0);
        Resultado tama = OPERACION(&tam);

        if(esEntero(tama)){
            int tamanio = tama.valor.toInt();
            InicializarArrayUnaDimension(tipo_,&fila,tamanio,&listId);
        }

    }
        break;

    }


}
//******************************************************************************
//*************************** Asignacion ************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
void accion::asignacion(NodoAST* raiz){

    NodoAST aux = raiz->hijos.at(raiz->hijos.size()-1);
    Resultado tk_valor = contValor(&aux);
    Variable* var = new Variable(tk_valor.tipo,tk_valor.valor);


    for (int x= 0; x<  raiz->hijos.size()-1; x++)
    {
        NodoAST actual =  raiz->hijos.at(x);
        if(actual.hijos.size()>0){
            NodoAST dimen = actual.hijos.first();
            AsignacionArreglo(&actual , &dimen,tk_valor);
        }else{

            Variable* VariableDeclarada = listaVariables.value(actual.valor);

            if(VariableDeclarada!= nullptr){

                if(VariableDeclarada->tipo_ == tk_valor.tipo){

                    listaVariables.insert(actual.valor,var);
                    QTextStream(stdout) << "Variable ["+actual.valor+"] asignada con exito"<< endl;

                }else{

                    Resultado r = Resultado();
                    r.linea = actual.linea;
                    r.columna = actual.columna;
                    Msgerror(r,"El tipo declarado en  \""+actual.valor+"\" no coincide con el tipo asignado");
                }

            }else{

                Resultado r = Resultado();
                r.linea = actual.linea;
                r.columna = actual.columna;
                Msgerror(r,"No existe una declaracion de \""+actual.valor+"\"");

            }

        }

    }

}
//******************************************************************************
//*************************** Imprimir ************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
void accion::imprimir(NodoAST* raiz){

    NodoAST LISTA_VALORES =raiz->hijos.at(0);

    resultado+=getValores(&LISTA_VALORES);

}

QString accion::getValores(NodoAST* raiz){

    QString result="";
    for (int x= 0; x< raiz->hijos.size(); x++)
    {
        NodoAST nodo = raiz->hijos.at(x);
        Resultado r1 =contValor(&nodo);
        QString valor = r1.valor;
        result+=valor;
    }

    result+="\n";


    return result;
}

//******************************************************************************
//*************************** Mostrar ************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
void accion::sentenciaMostrar(NodoAST* raiz){


    NodoAST LISTA_VALORES =raiz->hijos.at(1);
    NodoAST TITULO = raiz->hijos.at(0);
    Resultado r = contValor(&TITULO);

    QString title = r.valor;
    QString Valores = getValores(&LISTA_VALORES);


    alerta mialerta;
    mialerta.titulo = title;
    mialerta.contenido =Valores;
    listaarlerta.append(mialerta);

}
//******************************************************************************
//*************************** if ************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
void accion::sentenciaIf(NodoAST* raiz){


    switch (raiz->tipo_) {

    case IF:{
        NodoAST cond = raiz->hijos.at(0);
        bool    condicion = condIf(&cond);

        if(condicion){
            NodoAST cuerpo = raiz->hijos.at(1);
            ListaCuerpo(&cuerpo);

        }else {

            NodoAST entonces = raiz->hijos.at(2);
            sentenciaElse(&entonces);
        }

        break;
    }
    case IF_SIN_CUERPO :{

        NodoAST cond = raiz->hijos.at(0);
        bool    condicion = condIf(&cond);

        if(condicion){

        }else {
            NodoAST entonces = raiz->hijos.at(1);
            sentenciaElse(&entonces);

        }

        break;
    }

    }


}

void accion::sentenciaElse(NodoAST *raiz){


    switch (raiz->tipo_) {
    case ELSE:{

        NodoAST cuerpo = raiz->hijos.at(0);
        ListaCuerpo(&cuerpo);

        break;
    }
    case ELSE_IF: {

        NodoAST sentIF = raiz->hijos.at(0);
        sentenciaIf(&sentIF);
        break;
    }

    }




}
//******************************************************************************
//*************************** for ************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
void accion::sentenciaFor(NodoAST* raiz){


    switch (raiz->tipo_) {

    case FOR:{

        NodoAST Forcond = raiz->hijos.at(0);
        NodoAST cond = raiz->hijos.at(1);
        NodoAST actualizacion = raiz->hijos.at(2);
        NodoAST listaCuerpo = raiz->hijos.at(3);
        forCond(&Forcond);

        while (condIf(&cond)){

            ListaCuerpo(&listaCuerpo);
            QTextStream(stdout) << "Estamos en el bucle" << endl;
            contValor(&actualizacion);

        }


        break;
    }
    case FOR_VACIO:{

        break;
    }


    }



}




void accion::forCond(NodoAST* raiz){

    switch (raiz->tipo_) {
    case ASIG:{

        NodoAST asig = raiz->hijos.at(0);
        asignacion(&asig);
        break;
    }
    case DECLARA:{
        NodoAST declara = raiz->hijos.at(0);
        declaracion(&declara);
        break;
    }


    }

}



//******************************************************************************
//*************************** repetir ************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
void accion::sentendiaRepetir(NodoAST* raiz){


    switch (raiz->tipo_) {

    case REPETIR_VACIO:{

        break;
    }
    case REPETIR_CUERPO:{

        NodoAST   num = raiz->hijos.at(0);
        Resultado tama = OPERACION(&num);

        if(esEntero(tama)){
            int tamanio = tama.valor.toInt();
            NodoAST listaCuepo = raiz->hijos.at(1);

            for (int i=0;i<tamanio;i++) {
                ListaCuerpo(&listaCuepo);
            }
        }



        break;
    }

    }

}
//******************************************************************************
//*************************** tipo Dato ************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
Resultado accion::tipoDato(NodoAST* raiz){

    Resultado r = Resultado();
    r.linea = raiz->linea;
    r.columna = raiz->columna;

    switch (raiz->tipo_) {

    case STRING:
        r.tipo =STRING ;
        r.valor = raiz->valor;
        break;
    case BOOL:
        r.tipo =BOOL ;
        r.valor = raiz->valor;
        break;
    case INT:
        r.tipo =INT ;
        r.valor = raiz->valor;
        break;
    case DOUBLE:
        r.tipo =DOUBLE ;
        r.valor = raiz->valor;
        break;
    case CHAR:
        r.tipo =CHAR ;
        r.valor = raiz->valor;
        break;
    }

    return r;
}
//******************************************************************************
//*************************** listaid ************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
void accion::declaracionVariable(NodoAST *raiz, int tipo, int tipo_valor, QString valor){

    for (int x= 0; x< raiz->hijos.size(); x++)
    {
        if(tipo!=ERROR){
            if(tipo==tipo_valor){

                NodoAST nodo = raiz->hijos.at(x);
                listaVariables.insert(nodo.valor,new Variable(tipo,valor));

            }else{

                if(tipo==DOUBLE){

                    if(tipo_valor==DOUBLE || tipo_valor == INT){
                        NodoAST nodo = raiz->hijos.at(x);
                        listaVariables.insert(nodo.valor,new Variable(tipo,valor));
                    }else{

                         resultado+="No se puede declarar  el tipo de dato no coincide con el valor";
                    }

                }


            }


        }else{

            resultado+="Existe en un error en el valor de la declaracion";
        }

    }

}
//******************************************************************************
//*************************** contValor ***************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
Resultado accion::contValor(NodoAST* raiz){


    Resultado r = Resultado();
    r.linea = raiz->linea;
    r.columna = raiz->columna;

    switch (raiz->tipo_) {

    case AND :
    {
        NodoAST iz = raiz->hijos.at(0);
        Resultado op1 = contValor(&iz);
        NodoAST der = raiz->hijos.at(1);
        Resultado op2 = contValor(&der);

        switch (op1.tipo) {
        case BOOL:{

            switch (op2.tipo) {

            case BOOL:{
                r.tipo = BOOL;
                if(condBool(op1.valor) && condBool(op2.valor))
                {
                    r.valor ="true";

                }else{

                    r.valor="false";

                }

                break;
            }
            default:{
                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"no se pueden comparar los tipos");

                break;
            }

            }

            break;
        }
        default:{

            r.tipo =ERROR;
            r.valor="null";
            Msgerror(r,"no se pueden comparar los tipos");
            break;
        }
        }

        break;
    }
    case OR :
    {
        NodoAST iz = raiz->hijos.at(0);
        Resultado op1 = contValor(&iz);
        NodoAST der = raiz->hijos.at(1);
        Resultado op2 = contValor(&der);

        switch (op1.tipo) {

        case BOOL:{

            switch (op2.tipo) {

            case BOOL:{
                r.tipo = BOOL;
                if(condBool(op1.valor)||condBool(op2.valor))
                {
                    r.valor ="true";

                }else{

                    r.valor="false";

                }

                break;
            }default:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"no se pueden comparar los tipos");

                break;
            }

            }

            break;
        }
        default:{

            r.tipo =ERROR;
            r.valor="null";
            Msgerror(r,"no se pueden comparar los tipos");
            break;
        }

        }

        break;
    }
    case MAYORQUE :
    {
        NodoAST iz = raiz->hijos.at(0);
        Resultado op1 = contValor(&iz);
        NodoAST der = raiz->hijos.at(1);
        Resultado op2 = contValor(&der);

        switch (op1.tipo) {

        case INT:{

            switch (op2.tipo) {

            case INT:{
                r.tipo =BOOL;
                if(op1.valor.toInt()> op2.valor.toInt())
                {
                    r.valor ="true";

                }else{
                    r.valor="false";
                }

                break;
            }
            case DOUBLE:{
                r.tipo =BOOL;
                if(op1.valor.toDouble()> op2.valor.toDouble())
                {
                    r.valor ="true";

                }else{
                    r.valor="false";
                }


                break;
            }
            case CHAR:{

                r.tipo =BOOL;
                if(op1.valor.toInt() > op2.valor.at(0).toLatin1())
                {
                    r.valor ="true";

                }else{
                    r.valor="false";
                }
                break;
            }default:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"NO se pueden comparar los tipos");

                break;
            }

            }

            break;
        }
        case STRING:{

            switch (op2.tipo) {

            case STRING:{
                r.tipo =BOOL;
                if(op1.valor > op2.valor)
                {
                    r.valor ="true";

                }else{
                    r.valor="falso";
                }

                break;
            }default:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"NO se pueden comparar los tipos");
                break;
            }

            }

            break;
        }
        case DOUBLE:{

            switch (op2.tipo) {

            case INT:{
                r.tipo = BOOL;

                if(op1.valor.toDouble()> op2.valor.toDouble())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }

                break;
            }
            case DOUBLE:{
                r.tipo = BOOL;

                if(op1.valor.toDouble()> op2.valor.toDouble())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }

                break;
            }
            case CHAR:{

                r.tipo = BOOL;

                if(op1.valor.toDouble() > op2.valor.at(0).toLatin1())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }

                break;
            }default:{
                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"NO se pueden comparar los tipos");

                break;
            }

            }

            break;
        }
        case CHAR:{

            switch (op2.tipo) {

            case INT:{
                r.tipo = BOOL;

                if(op1.valor.at(0).toLatin1() > op2.valor.toInt())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }
                break;
            }
            case DOUBLE:{
                r.tipo = BOOL;

                if(op1.valor.at(0).toLatin1() > op2.valor.toDouble())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }

                break;
            }
            case CHAR:{
                r.tipo = BOOL;

                if(op1.valor.at(0).toLatin1() > op2.valor.at(0).toLatin1())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }
                break;
            }default:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"No se pueden comparar los tipos");
                break;
            }

            }

            break;
        }
        case BOOL:{

            switch (op2.tipo) {

            case BOOL:{
                r.tipo = BOOL;
                if(condBool(op1.valor)> condBool(op2.valor))
                {

                    r.valor="true";
                }else {
                    r.valor="false";
                }

                break;
            }default:{
                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"no se pueden comparar los tipos");
                break;
            }

            }

            break;
        }
        default:{

            r.tipo =ERROR;
            r.valor="null";
            Msgerror(r,"no se puede comparar los tipos");
            break;
        }

        }

        break;
    }
    case MENORQUE :
    {
        NodoAST iz = raiz->hijos.at(0);
        Resultado op1 = contValor(&iz);
        NodoAST der = raiz->hijos.at(1);
        Resultado op2 = contValor(&der);

        switch (op1.tipo) {

        case INT:{

            switch (op2.tipo) {

            case INT:{
                r.tipo =BOOL;
                if(op1.valor.toInt()< op2.valor.toInt())
                {
                    r.valor ="true";

                }else{
                    r.valor="false";
                }

                break;
            }
            case DOUBLE:{
                r.tipo =BOOL;
                if(op1.valor.toDouble()< op2.valor.toDouble())
                {
                    r.valor ="true";

                }else{
                    r.valor="false";
                }


                break;
            }
            case CHAR:{

                r.tipo =BOOL;
                if(op1.valor.toInt() < op2.valor.at(0).toLatin1())
                {
                    r.valor ="true";

                }else{
                    r.valor="false";
                }
                break;
            }default:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"NO se pueden comparar los tipos");

                break;
            }

            }

            break;
        }
        case STRING:{

            switch (op2.tipo) {

            case STRING:{
                r.tipo =BOOL;
                if(op1.valor < op2.valor)
                {
                    r.valor ="true";

                }else{
                    r.valor="falso";
                }

                break;
            }
            default:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"NO se pueden comparar los tipos");
                break;
            }

            }

            break;
        }
        case DOUBLE:{

            switch (op2.tipo) {

            case INT:{
                r.tipo = BOOL;

                if(op1.valor.toDouble()< op2.valor.toDouble())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }

                break;
            }
            case DOUBLE:{
                r.tipo = BOOL;

                if(op1.valor.toDouble()< op2.valor.toDouble())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }

                break;
            }
            case CHAR:{

                r.tipo = BOOL;

                if(op1.valor.toDouble() < op2.valor.at(0).toLatin1())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }

                break;
            }
            default:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"NO se pueden comparar los tipos");

                break;
            }

            }

            break;
        }
        case CHAR:{

            switch (op2.tipo) {

            case INT:{
                r.tipo = BOOL;

                if(op1.valor.at(0).toLatin1() < op2.valor.toInt())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }
                break;
            }
            case DOUBLE:{
                r.tipo = BOOL;

                if(op1.valor.at(0).toLatin1() < op2.valor.toDouble())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }

                break;
            }
            case CHAR:{
                r.tipo = BOOL;

                if(op1.valor.at(0).toLatin1() < op2.valor.at(0).toLatin1())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }
                break;
            }default:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"No se pueden comparar los tipos");
                break;
            }

            }

            break;
        }
        case BOOL:{

            switch (op2.tipo) {

            case BOOL:{
                r.tipo = BOOL;
                if(condBool(op1.valor)< condBool(op2.valor))
                {

                    r.valor="true";
                }else {
                    r.valor="false";
                }

                break;
            }default:{
                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"no se pueden comparar los tipos");
                break;
            }

            }

            break;
        }
        default:{

            r.tipo =ERROR;
            r.valor="null";
            Msgerror(r,"no se pueden comparar los tipos");
            break;
        }

        }

        break;
    }
    case MAYORIGUAL :
    {
        NodoAST iz = raiz->hijos.at(0);
        Resultado op1 = contValor(&iz);
        NodoAST der = raiz->hijos.at(1);
        Resultado op2 = contValor(&der);

        switch (op1.tipo) {

        case INT:{

            switch (op2.tipo) {

            case INT:{
                r.tipo =BOOL;
                if(op1.valor.toInt()>= op2.valor.toInt())
                {
                    r.valor ="true";

                }else{
                    r.valor="false";
                }

                break;
            }
            case DOUBLE:{
                r.tipo =BOOL;
                if(op1.valor.toDouble()>= op2.valor.toDouble())
                {
                    r.valor ="true";

                }else{
                    r.valor="false";
                }


                break;
            }
            case CHAR:{

                r.tipo =BOOL;
                if(op1.valor.toInt() >= op2.valor.at(0).toLatin1())
                {
                    r.valor ="true";

                }else{
                    r.valor="false";
                }
                break;
            }default:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"NO se pueden comparar los tipos");

                break;
            }

            }

            break;
        }
        case STRING:{

            switch (op2.tipo) {

            case STRING:{
                r.tipo =BOOL;
                if(op1.valor >= op2.valor)
                {
                    r.valor ="true";

                }else{
                    r.valor="falso";
                }

                break;
            }default:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"NO se pueden comparar los tipos");
                break;
            }

            }

            break;
        }
        case DOUBLE:{

            switch (op2.tipo) {

            case INT:{
                r.tipo = BOOL;

                if(op1.valor.toDouble()>= op2.valor.toDouble())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }

                break;
            }
            case DOUBLE:{
                r.tipo = BOOL;

                if(op1.valor.toDouble()>= op2.valor.toDouble())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }

                break;
            }
            case CHAR:{

                r.tipo = BOOL;

                if(op1.valor.toDouble() >= op2.valor.at(0).toLatin1())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }

                break;
            }default:{
                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"NO se pueden comparar los tipos");

                break;
            }

            }

            break;
        }
        case CHAR:{

            switch (op2.tipo) {

            case INT:{
                r.tipo = BOOL;

                if(op1.valor.at(0).toLatin1() >= op2.valor.toInt())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }
                break;
            }
            case DOUBLE:{
                r.tipo = BOOL;

                if(op1.valor.at(0).toLatin1() >= op2.valor.toDouble())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }

                break;
            }
            case CHAR:{
                r.tipo = BOOL;

                if(op1.valor.at(0).toLatin1() >= op2.valor.at(0).toLatin1())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }
                break;
            }
            default:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"No se pueden comparar los tipos");
                break;
            }

            }

            break;
        }
        case BOOL:{

            switch (op2.tipo) {

            case BOOL:{
                r.tipo = BOOL;
                if(condBool(op1.valor)>= condBool(op2.valor))
                {

                    r.valor="true";
                }else {
                    r.valor="false";
                }

                break;
            }default:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"no se pueden comparar los tipos");
                break;
            }

            }

            break;
        }
        default:{


            r.tipo =ERROR;
            r.valor="null";
            Msgerror(r,"error en la comparacion");
            break;
        }

        }

        break;

    }
    case MENORIGUAL :
    { NodoAST iz = raiz->hijos.at(0);
        Resultado op1 = contValor(&iz);
        NodoAST der = raiz->hijos.at(1);
        Resultado op2 = contValor(&der);

        switch (op1.tipo) {

        case INT:{

            switch (op2.tipo) {

            case INT:{
                r.tipo =BOOL;
                if(op1.valor.toInt()<= op2.valor.toInt())
                {
                    r.valor ="true";

                }else{
                    r.valor="false";
                }

                break;
            }
            case DOUBLE:{
                r.tipo =BOOL;
                if(op1.valor.toDouble()<= op2.valor.toDouble())
                {
                    r.valor ="true";

                }else{
                    r.valor="false";
                }


                break;
            }
            case CHAR:{

                r.tipo =BOOL;
                if(op1.valor.toInt() <= op2.valor.at(0).toLatin1())
                {
                    r.valor ="true";

                }else{
                    r.valor="false";
                }
                break;
            }default:{
                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"NO se pueden comparar los tipos");

                break;
            }

            }

            break;
        }
        case STRING:{

            switch (op2.tipo) {

            case STRING:{
                r.tipo =BOOL;
                if(op1.valor <= op2.valor)
                {
                    r.valor ="true";

                }else{
                    r.valor="falso";
                }

                break;
            }default:{
                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"NO se pueden comparar los tipos");
                break;
            }

            }

            break;
        }
        case DOUBLE:{

            switch (op2.tipo) {

            case INT:{
                r.tipo = BOOL;

                if(op1.valor.toDouble()<= op2.valor.toDouble())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }

                break;
            }
            case DOUBLE:{
                r.tipo = BOOL;

                if(op1.valor.toDouble()<= op2.valor.toDouble())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }

                break;
            }
            case CHAR:{

                r.tipo = BOOL;

                if(op1.valor.toDouble() <= op2.valor.at(0).toLatin1())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }

                break;
            }default:{
                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"NO se pueden comparar los tipos");

                break;
            }

            }

            break;
        }
        case CHAR:{

            switch (op2.tipo) {

            case INT:{
                r.tipo = BOOL;

                if(op1.valor.at(0).toLatin1() <= op2.valor.toInt())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }
                break;
            }
            case DOUBLE:{
                r.tipo = BOOL;

                if(op1.valor.at(0).toLatin1() <= op2.valor.toDouble())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }

                break;
            }
            case CHAR:{
                r.tipo = BOOL;

                if(op1.valor.at(0).toLatin1() <= op2.valor.at(0).toLatin1())
                {
                    r.valor="true";

                }else{
                    r.valor="false";

                }
                break;
            }default:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"No se pueden comparar los tipos");
                break;
            }

            }

            break;
        }
        case BOOL:{

            switch (op2.tipo) {

            case BOOL:{
                r.tipo = BOOL;
                if(condBool(op1.valor)<= condBool(op2.valor))
                {

                    r.valor="true";
                }else {
                    r.valor="false";
                }

                break;
            }default:{
                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"no se pueden comparar los tipos");
                break;
            }

            }

            break;
        }
        default:{

            r.tipo =ERROR;
            r.valor="null";
            Msgerror(r,"error en comparacion");
            break;
        }

        }

        break;
    }
    case IGUALACION :
    { NodoAST iz = raiz->hijos.at(0);
        Resultado op1 = contValor(&iz);
        NodoAST der = raiz->hijos.at(1);
        Resultado op2 = contValor(&der);

        switch (op1.tipo) {

        case INT:{

            switch (op2.tipo) {

            case INT:{
                r.tipo =BOOL;
                if(op1.valor.toInt()==op2.valor.toInt())
                {
                    r.valor ="true";

                }else{
                    r.valor="falso";
                }


                break;
            }
            case CHAR:{

                r.tipo =BOOL;
                if(op1.valor.at(0).toLatin1() ==op2.valor.at(0).toLatin1())
                {
                    r.valor ="true";

                }else{
                    r.valor="falso";
                }


                break;
            }default:{
                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"NO se pueden diferenciar los tipos" );

                break;
            }

            }

            break;
        }
        case STRING:{

            switch (op2.tipo) {


            case STRING:{
                r.tipo =BOOL;
                if(op1.valor ==op2.valor)
                {
                    r.valor ="true";

                }else{
                    r.valor="falso";
                }


                break;
            }default:{
                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"NO se pueden comparar los tipos");
                break;
            }

            }

            break;
        }
        case DOUBLE:{

            switch (op2.tipo) {


            case DOUBLE:{
                r.tipo =BOOL;
                if(op1.valor.toDouble() == op2.valor.toDouble())
                {
                    r.valor ="true";

                }else{
                    r.valor="falso";
                }

                break;
            }default:{
                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"NO se pueden comparar los tipos");

                break;
            }

            }

            break;
        }
        case CHAR:{

            switch (op2.tipo) {

            case INT:
            case CHAR:
                r.tipo =BOOL;
                if(op1.valor.at(0).toLatin1() ==op2.valor.at(0).toLatin1())
                {
                    r.valor ="true";

                }else{
                    r.valor="falso";
                }

                break;
            default:{
                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"NO se pueden comparar los tipos");
                break;
            }

            }

            break;
        }
        case BOOL:{

            switch (op2.tipo) {


            case BOOL:{
                r.tipo =BOOL;
                if(condBool(op1.valor) ==condBool(op2.valor))
                {
                    r.valor ="true";

                }else{
                    r.valor="falso";
                }

                break;
            }default:{
                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"NO se pueden diferenciar los tipos");
                break;
            }

            }

            break;
        }
        default:{

            r.tipo =ERROR;
            r.valor="null";
            Msgerror(r,"error en la igualaciona" );
            break;
        }


        }

        break;
    }
    case DIFERENCIACION :
    {
        NodoAST iz = raiz->hijos.at(0);
        Resultado op1 = contValor(&iz);
        NodoAST der = raiz->hijos.at(1);
        Resultado op2 = contValor(&der);

        switch (op1.tipo) {

        case INT:{

            switch (op2.tipo) {

            case INT:{
                r.tipo =BOOL;
                if(op1.valor.toInt()!=op2.valor.toInt())
                {
                    r.valor ="true";

                }else{
                    r.valor="falso";
                }

                break;
            }

            case CHAR:{
                r.tipo =BOOL;
                if(op1.valor.at(0).toLatin1()!=op2.valor.at(0).toLatin1())
                {
                    r.valor ="true";

                }else{
                    r.valor="falso";
                }


                break;
            }
            default:{
                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"NO se pueden diferenciar los tipos");
                break;
            }


            }

            break;
        }
        case STRING:{

            switch (op2.tipo) {


            case STRING:{

                r.tipo =BOOL;
                if(op1.valor!=op2.valor)
                {
                    r.valor ="true";

                }else{
                    r.valor="falso";
                }

                break;
            }default:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"No se pueden diferenciar los tipo");
                break;
            }

            }

            break;
        }
        case DOUBLE:{

            switch (op2.tipo) {

            case DOUBLE:{
                r.tipo =BOOL;
                if(op1.valor.toDouble()!=op2.valor.toDouble())
                {
                    r.valor ="true";

                }else{
                    r.valor="falso";
                }

                break;
            }default:{

                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r, "error de tipos");

                break;
            }

            }

            break;
        }
        case CHAR:{

            switch (op2.tipo) {

            case INT:{

                r.tipo =BOOL;
                if(op1.valor.at(0).toLatin1() !=op2.valor.toInt())
                {
                    r.valor ="true";

                }else{
                    r.valor="falso";
                }


                break;
            }
            case CHAR:{
                r.tipo =BOOL;
                if(op1.valor.at(0).toLatin1() !=op2.valor.at(0).toLatin1() )
                {
                    r.valor ="true";

                }else{
                    r.valor="falso";
                }


                break;
            }default:{
                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"no se pueden diferenciar los tipos ");

                break;
            }

            }

            break;
        }
        case BOOL:{

            switch (op2.tipo) {


            case BOOL:{
                r.tipo =BOOL;
                if(condBool(op1.valor)!=condBool(op2.valor))
                {
                    r.valor ="true";

                }else{
                    r.valor="falso";
                }



                break;
            }default:{
                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"no se pueden diferenciar los tipos");
                break;
            }

            }

            break;
        }
        default:{


            r.tipo =ERROR;
            r.valor="null";
            Msgerror(r,"error en le difereciacion");
        }

        }

        break;
    }
    default:{
        Resultado r1 =OPERACION(raiz);
        r.tipo = r1.tipo;
        r.valor = r1.valor;

        break;
    }


    }

    return r;
}
//******************************************************************************
//*************************** contValor ***************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
Resultado accion::OPERACION(NodoAST* raiz){

    Resultado r = Resultado();
    r.linea = raiz->linea;
    r.columna = raiz->columna;

    switch (raiz->tipo_) {
    case SUMA :
    {
        NodoAST iz = raiz->hijos.at(0);
        Resultado op1 = OPERACION(&iz);
        NodoAST der = raiz->hijos.at(1);
        Resultado op2 = OPERACION(&der);

        switch (op1.tipo) {

        case INT:{

            switch (op2.tipo) {

            case INT:{

                r.tipo = INT;
                int result = op1.valor.toInt() +op2.valor.toInt();
                r.valor = QString::number(result);
                break;
            }
            case STRING:{

                r.tipo = STRING;
                r.valor = op1.valor + op2.valor;

                break;
            }
            case BOOL:{

                r.tipo = INT;
                QString valor = op2.valor;

                if( ( valor.toLower().compare("true") ==0) ||  (valor.toLower().compare("verdadero")==0) ){

                    int result = op1.valor.toInt() +1;
                    r.valor = QString::number(result);

                }else{
                    r.valor = op1.valor;

                }

                break;
            }
            case DOUBLE:{

                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() + op2.valor.toDouble();
                r.valor = QString::number(result);
                break;
            }
            case CHAR:{
                r.tipo = INT;
                char  aux = op2.valor.at(0).toLatin1();
                int result = op1.valor.toInt()+ aux;
                r.valor = QString::number(result);
                break;
            }
            default:{

                r.tipo = ERROR;
                r.valor ="null";

                QTextStream(stdout) << "Error Semantico" << endl;
            }

            }

            break;
        }

        case STRING:{

            switch (op2.tipo) {

            case INT:{

                r.tipo = STRING;
                r.valor = op1.valor + op2.valor;
                break;
            }
            case STRING:{
                r.tipo = STRING;
                r.valor = op1.valor + op2.valor;
                break;
            }
            case DOUBLE:{
                r.tipo = STRING;
                r.valor = op1.valor + op2.valor;
                break;
            }
            case CHAR:{
                r.tipo = STRING;
                r.valor = op1.valor + op2.valor;
                break;
            }
            case BOOL:{

                r.tipo = ERROR;
                r.valor ="null";
                resultado+="Error Semantico: linea:"+QString::number(r.linea);
                resultado+=" col:"+QString::number(r.columna)+"  no se puede sumar string y bool \n";
                QTextStream(stdout) << "Error Semantico" << endl;
                break;
            }
            default:{


                r.tipo = ERROR;
                r.valor ="null";
                QTextStream(stdout) << "Error Semantico" << endl;
            }

            }

            break;
        }

        case DOUBLE:{

            switch (op2.tipo) {

            case INT:{
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() + op2.valor.toDouble();
                r.valor = QString::number(result);
                break;
            }
            case STRING:{
                r.tipo = STRING;
                r.valor = op1.valor+op2.valor;
                break;
            }
            case DOUBLE:{
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() + op2.valor.toDouble();
                r.valor = QString::number(result);
                break;
            }
            case CHAR:{
                r.tipo = DOUBLE;
                char  aux = op2.valor.at(0).toLatin1();
                int result = op1.valor.toInt()+ aux;
                r.valor = QString::number(result);
                break;
            }
            case BOOL:{
                r.tipo = DOUBLE;
                QString valor = op2.valor;

                if( ( valor.toLower().compare("true") ==0)||  (valor.toLower().compare("verdadero")==0) ){

                    int result = op1.valor.toInt() +1;
                    r.valor = QString::number(result);

                }else{
                    r.valor = op1.valor;
                }

                break;

            } default:

                r.tipo = ERROR;
                r.valor ="null";
                QTextStream(stdout) << "Error Semantico" << endl;
                break;
            }

            break;
        }

        case CHAR:{

            switch (op2.tipo) {

            case INT:{

                r.tipo = INT;
                char  aux = op1.valor.at(0).toLatin1();
                int result = op2.valor.toInt()+ aux;
                r.valor = QString::number(result);

                break;
            }
            case STRING:{
                r.tipo = STRING;
                r.valor = op1.valor+op2.valor;
                break;
            }
            case DOUBLE:{
                r.tipo = DOUBLE;
                char  aux = op1.valor.at(0).toLatin1();
                double result = op2.valor.toDouble()+ aux;
                r.valor = QString::number(result);
                break;
            }
            case CHAR:{
                r.tipo = INT;
                char  aux1 = op1.valor.at(0).toLatin1();
                char aux2 = op2.valor.at(0).toLatin1();
                int result = aux1+aux2;
                r.valor =QString::number(result);
                break;
            }
            case BOOL:{

                r.tipo = INT;
                QString valor = op2.valor;

                if( ( valor.toLower().compare("true") ==0) ||  (valor.toLower().compare("verdadero")==0) ){

                    char  aux1 = op1.valor.at(0).toLatin1();
                    int result =1+ aux1;
                    r.valor = QString::number(result);

                }else{
                    char  aux1 = op1.valor.at(0).toLatin1();
                    int result =0+ aux1;
                    r.valor = QString::number(result);

                }

                break;
            }default:{

                r.tipo = ERROR;
                r.valor ="null";
                resultado+="Error Semantico ";

                break;
            }

            }

            break;
        }

        case BOOL:{

            switch (op2.tipo) {

            case INT:{
                r.tipo = INT;
                QString valor = op1.valor;

                if( ( valor.toLower().compare("true") ==0) ||  (valor.toLower().compare("verdadero")==0) ){

                    int result = op2.valor.toInt() +1;
                    r.valor = QString::number(result);

                }else{
                    r.valor = op2.valor;

                }
                break;
            }
            case STRING:{

                r.tipo = ERROR;
                r.valor ="null";
                resultado+="Error Semantico: linea:"+QString::number(r.linea);
                resultado+=" col:"+QString::number(r.columna)+"  no se puede sumar string y bool \n";
                QTextStream(stdout) << "Error Semantico" << endl;
                break;
            }
            case BOOL:{

                r.tipo =BOOL;
                QString valor1 = op1.valor;
                QString valor2 = op2.valor;

                if(  ((valor1.toLower().compare("true") ==0) ||  (valor1.toLower().compare("verdadero")==0))||
                     ((valor2.toLower().compare("true") ==0) ||  (valor2.toLower().compare("verdadero")==0))
                     ){

                    r.valor ="true";

                }else{
                    r.valor ="false";

                }


                break;
            }
            case DOUBLE:{

                r.tipo = DOUBLE;
                QString valor = op1.valor;

                if( ( valor.toLower().compare("true") ==0) ||  (valor.toLower().compare("verdadero")==0) ){

                    double result = op1.valor.toDouble() +1;
                    r.valor = QString::number(result);

                }else{
                    r.valor = op1.valor;

                }

                break;
            }
            case CHAR:{

                QString valor = op1.valor;

                if( ( valor.toLower().compare("true") ==0) ||  (valor.toLower().compare("verdadero")==0) ){

                    char aux = op1.valor.at(0).toLatin1();
                    int result = aux +1;
                    r.valor = QString::number(result);

                }else{
                    char aux = op1.valor.at(0).toLatin1();
                    int result = aux;
                    r.valor = QString::number(result);

                }


                break;
            }
            default:{


                r.tipo = ERROR;
                r.valor ="null";
                Msgerror(r,"No se pueden sumar los tipos");
                break;
            }

            }

            break;
        }

        default:{

            r.tipo = ERROR;
            r.valor ="null";

            break;
        }
        }


        break;
    }
    case RESTA :
    {

        NodoAST iz = raiz->hijos.at(0);
        Resultado op1 = OPERACION(&iz);
        NodoAST der = raiz->hijos.at(1);
        Resultado op2 = OPERACION(&der);

        switch (op1.tipo) {

        case INT:{

            switch (op2.tipo) {
            case INT:{
                r.tipo = INT;
                int result = op1.valor.toInt()- op2.valor.toInt();
                r.valor = QString::number(result);
                break;
            }
            case STRING:{
                r.tipo = ERROR;
                r.valor ="null";
                resultado+="Error Semantico: linea:"+QString::number(r.linea);
                resultado+=" col:"+QString::number(r.columna)+" no se  pueden restar int string\n";
                QTextStream(stdout) << "Error Semantico" << endl;
                break;
            }
            case DOUBLE:{

                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() - op2.valor.toDouble();
                r.valor = QString::number(result);

                break;
            }
            case CHAR:{

                r.tipo = INT;
                char aux= op2.valor.at(0).toLatin1();
                int result = op1.valor.toInt()  - aux;
                r.valor = QString::number(result);

                break;
            }
            case BOOL:{

                r.tipo = INT;
                QString valor = op2.valor;

                if( (valor.toLower().compare("true")==0)||(valor.toLower().compare("verdadero")==0)  )
                {
                    int result = op1.valor.toInt() +1;
                    r.valor = QString::number(result);
                }
                else{
                    r.valor = op1.valor;
                }


                break;
            }default:{
                r.tipo = ERROR;
                r.valor ="null";
                Msgerror(r,"NO se pueden restar los tipos");
                break;
            }
            }
            break;
        }

        case STRING:{

            switch (op2.tipo) {
            case INT:{
                r.tipo = ERROR;
                r.valor ="null";
                resultado+="Error Semantico: linea:"+QString::number(r.linea);
                resultado+=" col:"+QString::number(r.columna)+" no se  pueden restar un string a un int \n";
                QTextStream(stdout) << "Error Semantico" << endl;

                break;
            }
            case STRING:{
                r.tipo = ERROR;
                r.valor ="null";
                resultado+="Error Semantico: linea:"+QString::number(r.linea);
                resultado+=" col:"+QString::number(r.columna)+" no se  pueden restar un string a un string \n";
                QTextStream(stdout) << "Error Semantico" << endl;

                break;
            }
            case DOUBLE:{
                r.tipo = ERROR;
                r.valor ="null";
                resultado+="Error Semantico: linea:"+QString::number(r.linea);
                resultado+=" col:"+QString::number(r.columna)+" no se  pueden restar un string a un double \n";
                QTextStream(stdout) << "Error Semantico" << endl;

                break;
            }
            case CHAR:{
                r.tipo = ERROR;
                r.valor ="null";
                resultado+="Error Semantico: linea:"+QString::number(r.linea);
                resultado+=" col:"+QString::number(r.columna)+" no se  pueden restar un string a un char \n";
                QTextStream(stdout) << "Error Semantico" << endl;

                break;
            }
            case BOOL:{
                r.tipo = ERROR;
                r.valor ="null";
                resultado+="Error Semantico: linea:"+QString::number(r.linea);
                resultado+=" col:"+QString::number(r.columna)+" no se  pueden restar un string a un bool \n";
                QTextStream(stdout) << "Error Semantico" << endl;

                break;
            }
            default:{
                r.tipo = ERROR;
                r.valor ="null";
                Msgerror(r,"no se puedne restar los tipos");
                break;
            }


            }
            break;
        }

        case DOUBLE:{

            switch (op2.tipo) {
            case INT:{

                r.tipo = DOUBLE;
                double result = op1.valor.toDouble()- op2.valor.toInt();
                r.valor= QString::number(result);

                break;
            }
            case STRING:{
                r.tipo = ERROR;
                r.valor ="null";
                resultado+="Error Semantico: linea:"+QString::number(r.linea);
                resultado+=" col:"+QString::number(r.columna)+" no se  pueden restar double a un  string\n";
                QTextStream(stdout) << "Error Semantico" << endl;
                break;
            }
            case DOUBLE:{
                r.tipo = DOUBLE;
                double result= op1.valor.toDouble()-op2.valor.toDouble();
                r.valor = QString::number(result);

                break;
            }
            case CHAR:{

                r.tipo = DOUBLE;
                double result= op1.valor.toDouble() - op2.valor.at(0).toLatin1();
                r.valor = QString::number(result);

                break;
            }
            case BOOL:{

                r.tipo = DOUBLE;
                QString valor = op2.valor.toLower();

                if( (valor.compare("true")==0||(valor.compare("verdadero")==0)) )
                {
                    double result = op1.valor.toDouble()-1;
                    r.valor = QString::number(result);

                }else{
                    r.valor = op1.valor;
                }


                break;
            }
            default:{
                r.tipo = ERROR;
                r.valor ="null";
                Msgerror(r,"no se pueden restar  los tipos");

                break;
            }


            }
            break;
        }

        case CHAR:{

            switch (op2.tipo) {
            case INT:{

                r.tipo = INT;
                int result = op1.valor.at(0).toLatin1()-op2.valor.toInt();
                r.valor = QString::number(result);
                break;
            }
            case STRING:{
                r.tipo = ERROR;
                r.valor ="null";
                Msgerror(r, "no se puede restar un chara un string");
                break;
            }
            case DOUBLE:{
                r.tipo =DOUBLE;
                double result =op1.valor.at(0).toLatin1()- op2.valor.toDouble();
                r.valor = QString::number(result);

                break;
            }
            case CHAR:{
                r.tipo =INT;
                int result = op1.valor.at(0).toLatin1()-op2.valor.at(0).toLatin1();
                r.valor =QString::number(result);
                break;
            }
            case BOOL:{
                r.tipo = ERROR;
                r.valor ="null";
                Msgerror(r,"NO se puede restar un bool a un char");
                break;
            }
            default:{

                r.tipo = ERROR;
                r.valor ="null";
                Msgerror(r,"no se pueden restar los tipos");
                break;
            }


            }
            break;
        }

        case BOOL:{

            switch (op2.tipo) {
            case INT:{
                r.tipo = INT;

                if(condBool(op1.valor))
                {
                    int result = 1-op2.valor.toInt();
                    r.valor = QString::number(result);

                }else{

                    int result = op2.valor.toInt()*(-1);
                    r.valor = QString::number(result);

                }

                break;
            }
            case STRING:{
                r.tipo = ERROR;
                r.valor ="null";
                Msgerror(r,"No se puede restar un string a un bool");

                break;
            }
            case DOUBLE:{
                r.tipo =DOUBLE;

                if(condBool(op1.valor))
                {
                    double result = 1- op2.valor.toDouble();
                    r.valor = QString::number(result);
                }else{
                    double result = op2.valor.toDouble()*(-1);
                    r.valor = QString::number(result);
                }


                break;
            }
            case CHAR:{
                r.tipo = ERROR;
                r.valor ="null";
                Msgerror(r,"NO se puede restar char a un bool");
                break;
            }
            case BOOL:{
                r.tipo = ERROR;
                r.valor ="null";
                Msgerror(r,"NO se puede restar bool a un boll");
                break;
            }
            default:{
                r.tipo = ERROR;
                r.valor ="null";
                Msgerror(r,"no se pueden restar lor tipos");
                break;
            }

            }
            break;
        }

        default:{

            r.tipo = ERROR;
            r.valor ="null";
            Msgerror(r,"no se puden resta los tipos");
            break;
        }

        }

        break;
    }
    case POR :
    {
        NodoAST iz = raiz->hijos.at(0);
        Resultado op1 = OPERACION(&iz);
        NodoAST der = raiz->hijos.at(1);
        Resultado op2 = OPERACION(&der);
        switch (op1.tipo) {

        case INT:{

            switch (op2.tipo) {

            case INT:{
                r.tipo = INT;
                int result = op1.valor.toInt() * op2.valor.toInt();
                r.valor = QString::number(result);
                break;
            }
            case STRING:{

                r.tipo = ERROR;
                r.valor ="null";
                Msgerror(r,"No de puede multiplicar un int con un string");
                break;
            }
            case DOUBLE:{
                r.tipo = STRING;
                double result = op1.valor.toDouble()* op2.valor.toDouble();
                r.valor = QString::number(result);
                break;
            }
            case CHAR:{
                r.tipo = INT;
                int result = op1.valor.toInt()* op2.valor.at(0).toLatin1();
                r.valor = QString::number(result);
                break;
            }
            case BOOL:{
                r.tipo = INT;

                if(condBool(op2.valor)){
                    r.valor = op1.valor;
                }else{

                    r.valor = "0";
                }

                break;
            }
            default:{

                r.tipo = ERROR;
                r.valor ="null";
                Msgerror(r,"no se pueden multiplicar los tipos");

                break;
            }
            }
            break;
        }
        case STRING:{

            switch (op2.tipo) {

            case INT:{
                r.tipo = STRING;
                Msgerror(r,"No se puede MULTIPLICAR  un string y un int");

                break;
            }
            case STRING:{
                r.tipo = STRING;
                Msgerror(r,"No se puede MULTIPLICAR  un string y un string");

                break;
            }
            case DOUBLE:{
                r.tipo = STRING;
                Msgerror(r,"No se puede MULTIPLICAR  un string y un double");

                break;
            }
            case CHAR:{
                r.tipo = STRING;
                Msgerror(r,"No se puede MULTIPLICAR  un string y un char");

                break;
            }
            case BOOL:{
                r.tipo = STRING;
                Msgerror(r,"No se puede MULTIPLICAR  un string y un bool");

                break;
            }default:{

                r.tipo=ERROR;
                r.valor="null";
                Msgerror(r,"NO se pueden multiplicar los tipos");
                break;
            }


            }
            break;
        }
        case DOUBLE:{

            switch (op2.tipo) {

            case INT:{

                r.tipo= DOUBLE;
                double result = op1.valor.toDouble()* op2.valor.toDouble();
                r.valor = QString::number(result);

                break;
            }
            case STRING:{

                r.tipo = ERROR;
                r.valor ="null";
                Msgerror(r,"NO se puede multplicar un double con un string");

                break;
            }
            case DOUBLE:{
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble()* op2.valor.toDouble();
                r.valor = QString::number(result);

                break;
            }
            case CHAR:{
                r.tipo= DOUBLE;
                double result=op1.valor.toDouble()* op2.valor.at(0).toLatin1();
                r.valor = QString::number(result);

                break;
            }
            case BOOL:{
                r.tipo = DOUBLE;

                if(condBool(op2.valor)){
                    r.valor = op1.valor;
                }else{

                    r.valor ="0";
                }

                break;
            }
            default:{
                r.tipo = ERROR;
                r.valor ="null";
                Msgerror(r,"no se pueden multiplicar los tipos");
                break;
            }
            }
            break;
        }
        case CHAR:{

            switch (op2.tipo) {

            case INT:{
                r.tipo = INT;
                int result = op1.valor.at(0).toLatin1() * op2.valor.toInt();
                r.valor = QString::number(result);

                break;
            }
            case STRING:{
                r.tipo = ERROR;
                r.valor ="null";
                Msgerror(r,"NO se puede multiplicar un char con un string");

                break;
            }
            case DOUBLE:{
                r.tipo =DOUBLE;
                double result = op1.valor.at(0).toLatin1() * op2.valor.toDouble();
                r.valor = QString::number(result);

                break;
            }
            case CHAR:{
                r.tipo=INT;
                int result = op1.valor.at(0).toLatin1()* op2.valor.at(0).toLatin1();
                r.valor = QString::number(result);

                break;
            }
            case BOOL:{
                r.tipo =INT;

                if(condBool(op2.valor))
                {
                    r.valor = op1.valor;
                }else{
                    r.valor = "0";

                }

                break;
            }
            default:{
                r.tipo = ERROR;
                r.valor ="null";
                Msgerror(r,"no se pueden multiplicar los tipos");
                break;
            }
            }
            break;
        }
        case BOOL:{

            switch (op2.tipo) {

            case INT:{

                r.tipo = INT;

                if(condBool(op1.valor))
                {
                    r.valor = op2.valor;
                }else{

                    r.valor ="0";
                }
                break;
            }
            case STRING:{
                r.tipo = ERROR;
                r.valor ="null";
                Msgerror(r, "NO se puede multiplicar un Bool y un string " );

                break;
            }
            case DOUBLE:{

                r.tipo = DOUBLE;

                if(condBool(op1.valor))
                {
                    r.valor = op2.valor;
                }else{

                    r.valor ="0";
                }

                break;
            }
            case CHAR:{
                r.tipo = INT;

                if(condBool(op1.valor))
                {
                    r.valor = op2.valor.at(0).toLatin1();
                }else{

                    r.valor ="0";
                }

                break;
            }
            case BOOL:{

                r.tipo =BOOL;
                if( condBool(op1.valor) && condBool(op2.valor) )
                {
                    r.valor ="true";

                }else{

                    r.valor ="false";

                }

                break;
            }
            default:{
                r.tipo = ERROR;
                r.valor ="null";
                Msgerror(r,"no se pueden multiplicar los tipos");
                break;
            }
            }
            break;
        }
        default:{

            r.tipo = ERROR;
            r.valor ="null";
            Msgerror(r,"no se pueden multiplicar los tipos");
            break;
        }
        }

        break;
    }
    case DIV :
    {
        NodoAST iz = raiz->hijos.at(0);
        Resultado op1 = OPERACION(&iz);
        NodoAST der = raiz->hijos.at(1);
        Resultado op2 = OPERACION(&der);

        switch (op1.tipo) {

        case INT:{

            switch (op2.tipo) {

            case INT:{
                r.tipo= INT;

                if(divCero(op2.valor)){

                    int result =op1.valor.toInt()/op2.valor.toInt();
                    r.valor =QString::number(result);

                }else{
                    r.tipo =ERROR;
                    r.valor="null";
                    Msgerror(r,"no se puede dividir por cero");
                }
                
                break;
            }
            case STRING:{

                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"No se puede dividir un entero y un string");
                break;
            }
            case DOUBLE:{
                r.tipo =DOUBLE;

                if(divCero(op2.valor)){
                    double result = op1.valor.toDouble()/ op2.valor.toDouble();
                    r.valor = QString::number(result);

                }else{

                    r.tipo =ERROR;
                    r.valor="null";

                    Msgerror(r,"no se puede dividr por cero");
                }

                break;
            }
            case CHAR:{

                r.tipo = INT;

                if(op2.valor.at(0).toLatin1()!=0)
                {
                    int result = op1.valor.toInt()/ op2.valor.at(0).toLatin1();
                    r.valor =QString::number(result);

                }else{

                    r.tipo =ERROR;
                    r.valor="null";

                    Msgerror(r,"no se puede dividir entre cero");
                }

                break;
            }
            case BOOL:{
                r.tipo = INT;

                if(condBool(op2.valor))
                {
                    r.valor = op1.valor;

                }else{

                    r.tipo =ERROR;
                    r.valor="null";


                    Msgerror(r,"no se puede dividir entre cero");

                }

                break;
            }
            default:{

                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"no se pueden dividir los tipos");
                break;
            }
            }
            break;
        }
        case STRING:{

            switch (op2.tipo) {

            case INT:{

                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"no de puede dividir un string con un entero");
                break;
            }
            case STRING:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"no de puede dividir un string con un string");

                break;
            }
            case DOUBLE:{
                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"no de puede dividir un string con un double");

                break;
            }
            case CHAR:{
                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"no de puede dividir un string con un char");
                break;
            }
            case BOOL:{
                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"no de puede dividir un string con un bool");

                break;
            }

            default:{

                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"no se pueden dividir los tipos");

                break;
            }

            }
            break;
        }
        case DOUBLE:{

            switch (op2.tipo) {

            case INT:{
                r.tipo =DOUBLE;
                if(divCero(op2.valor))
                {
                    r.tipo = DOUBLE;
                    double result= op1.valor.toDouble()/ op2.valor.toDouble();
                    r.valor = QString::number(result);

                }else {

                    r.tipo =ERROR;
                    r.valor="null";

                    Msgerror(r,"NO se pude dividir por cero");

                }

                break;
            }
            case STRING:{

                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"NO se pude dividir  un double con un string");
                break;
            }
            case DOUBLE:{
                r.tipo= DOUBLE;

                if(divCero(op2.valor)){
                    double result = op1.valor.toDouble()/op2.valor.toDouble();
                    r.valor = QString::number(result);

                }else{

                    r.tipo =ERROR;
                    r.valor="null";

                    Msgerror(r,"NO se puede dividir por cero");
                }


                break;
            }
            case CHAR:{
                r.tipo = DOUBLE;
                if(op2.valor.at(0).toLatin1()==0){

                    double result = op1.valor.toDouble()/op2.valor.at(0).toLatin1();
                    r.valor = QString::number(result);

                }else{

                    r.tipo =ERROR;
                    r.valor="null";


                    Msgerror(r,"NO se puede dividir por cero");
                }
                break;
            }
            case BOOL:{
                r.tipo =DOUBLE;
                if(condBool(op2.valor))
                {
                    r.valor = op1.valor;
                }else{

                    r.tipo =ERROR;
                    r.valor="null";

                    Msgerror(r,"NO se pude dividir por cero");

                }

                break;
            }
            default:{

                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"no se pueden dividir los tipos");
                break;
            }
            }
            break;
        }
        case CHAR:{

            switch (op2.tipo) {

            case INT:{
                r.tipo = INT;

                if(divCero(op2.valor))
                {
                    int result = op1.valor.at(0).toLatin1() / op2.valor.toInt();
                    r.valor = QString::number(result);

                }else{

                    r.tipo =ERROR;
                    r.valor="null";


                    Msgerror(r,"NO se pude dividr por cero");
                }
                break;
            }
            case STRING:{

                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"No se puede dividir un char con string");
                break;
            }
            case DOUBLE:{
                r.tipo = DOUBLE;
                if(divCero(op2.valor))
                {
                    double result = op1.valor.at(0).toLatin1()/op2.valor.toDouble();
                    r.valor = QString::number(result);

                }else{

                    r.tipo =ERROR;
                    r.valor="null";

                    Msgerror(r,"NO se pude dividir por cero ");
                }

                break;
            }
            case CHAR:{

                r.tipo = CHAR;

                if(op2.valor.at(0).toLatin1()!=0)
                {
                    int result = op1.valor.at(0).toLatin1()/op2.valor.at(0).toLatin1();
                    r.valor = QString::number(result);
                }else{
                    r.tipo =ERROR;
                    r.valor="null";


                    Msgerror(r,"NO se pude dividir por cero" );
                }

                break;
            }
            case BOOL:{
                r.tipo = INT;

                if(condBool(op2.valor))
                {
                    r.valor = op1.valor;

                }else{

                    r.tipo =ERROR;
                    r.valor="null";

                    Msgerror(r,"NO se puede dividir por cero");
                }

                break;
            }
            default:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"no se pueden dividir los tipos");
                break;
            }
            }
            break;
        }
        case BOOL:{

            switch (op2.tipo) {

            case INT:{
                r.tipo =INT;
                if(condBool(op1.valor))
                {
                    int result = 1/op2.valor.toInt();
                    r.valor = QString::number(result);
                }else{
                    r.valor = "0";
                }

                break;
            }
            case STRING:{

                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"NO se puede dividir un bool con un string");
                break;
            }
            case DOUBLE:{
                r.tipo =DOUBLE;
                if(condBool(op1.valor))
                {
                    double result = 1/op2.valor.toDouble();
                    r.valor = QString::number(result);
                }else{
                    r.valor = "0";
                }

                break;
            }
            case CHAR:{
                r.tipo = DOUBLE;

                if(op2.valor.at(0).toLatin1()!=0)
                {
                    if(condBool(op1.valor))
                    {
                        double result =1/op2.valor.at(0).toLatin1();
                        r.valor = QString::number(result);

                    }else
                    {
                        r.valor = "0";

                    }

                }else{

                    r.tipo =ERROR;
                    r.valor="null";

                    Msgerror(r,"NO se puede dividir por cero");
                }

                break;
            }
            case BOOL:{

                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"NO se puede divir un bool con un bool");
                break;
            }
            default:{

                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"no se pueden dividir los tipos");
                break;
            }

            }
            break;
        }
        default:{

            r.tipo =ERROR;
            r.valor="null";
            Msgerror(r,"no se pueden dividr lor tipos");
            break;
        }
        }

        break;
    }
    case POTENCIA :
    {

        NodoAST iz = raiz->hijos.at(0);
        Resultado op1 = OPERACION(&iz);
        NodoAST der = raiz->hijos.at(1);
        Resultado op2 = OPERACION(&der);

        switch (op1.tipo) {

        case INT:{

            switch (op2.tipo) {

            case INT:{
                r.tipo =INT;
                qreal result =  qPow(op1.valor.toInt(),op2.valor.toInt());
                r.valor = QString::number(result);
                break;
            }
            case STRING:{

                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"NO SE PUEDE ELEVAR UN INT A UN STRING");
                break;
            }
            case DOUBLE:{
                r.tipo =DOUBLE;
                qreal result =  qPow(op1.valor.toDouble(),op2.valor.toDouble());
                r.valor = QString::number(result);

                break;
            }
            case CHAR:{
                r.tipo =INT;
                qreal result =  qPow(op1.valor.toInt(),op2.valor.at(0).toLatin1());
                r.valor = QString::number(result);

                break;
            }
            case BOOL:{
                r.tipo =INT;

                if(condBool(op2.valor))
                {
                    r.valor = op1.valor;
                }else{
                    qreal result =  qPow(op1.valor.toInt(),0);
                    r.valor = QString::number(result);

                }

                break;
            }
            default:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"no se pueden optenciar los tipos ");
                break;
            }
            }
            break;
        }
        case STRING:{

            switch (op2.tipo) {

            case INT:{
                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"no se puede elevar un int a un string");

                break;
            }
            case STRING:{

                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"no se puede elevar un string a un string");
                break;
            }
            case DOUBLE:{
                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"no se puede elevar un double a un string");

                break;
            }
            case CHAR:{
                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"no se puede elevar un char a un string");

                break;
            }
            case BOOL:{
                r.tipo =ERROR;
                r.valor="null";

                Msgerror(r,"no se puede elevar un bool a un string");

                break;
            }
            default:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"no se pueden potenciar los tipos" );
                break;
            }
            }
            break;
        }
        case DOUBLE:{

            switch (op2.tipo) {

            case INT:{
                r.tipo =DOUBLE;
                qreal result =  qPow(op1.valor.toDouble(),op2.valor.toDouble());
                r.valor = QString::number(result);
                break;
            }
            case STRING:{
                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"NO se puede elevar un string a un double");

                break;
            }
            case DOUBLE:{
                r.tipo =ERROR;
                r.valor="null";
                qreal result =  qPow(op1.valor.toDouble(),op2.valor.toDouble());
                r.valor = QString::number(result);

                break;
            }
            case CHAR:{

                r.tipo =DOUBLE;
                qreal result =  qPow(op1.valor.toDouble(),op2.valor.at(0).toLatin1());
                r.valor = QString::number(result);
                break;
            }
            case BOOL:{

                r.tipo =DOUBLE;
                if(condBool(op2.valor))
                {
                    r.valor = op1.valor;

                }else{

                    qreal result =  qPow(op1.valor.toDouble(),0);
                    r.valor = QString::number(result);
                }
                break;
            }
            default:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"no se pueden potenciar los tipos");
                break;
            }
            }
            break;
        }
        case CHAR:{

            switch (op2.tipo) {

            case INT:{

                r.tipo =INT;
                qreal result =  qPow(op1.valor.at(0).toLatin1()  ,op2.valor.toInt());
                r.valor = QString::number(result);
                break;
            }
            case STRING:{
                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"no se puede elevar un string a un char");

                break;
            }
            case DOUBLE:{

                r.tipo =DOUBLE;
                qreal result =  qPow(op1.valor.at(0).toLatin1()  ,op2.valor.toDouble());
                r.valor = QString::number(result);
                break;
            }
            case CHAR:{

                r.tipo =INT;
                qreal result =  qPow(op1.valor.at(0).toLatin1()  ,op2.valor.at(0).toLatin1());
                r.valor = QString::number(result);
                break;
            }
            case BOOL:{

                r.tipo =INT;

                if(condBool(op2.valor)){
                    qreal result =  qPow(op1.valor.at(0).toLatin1()  ,1);
                    r.valor = QString::number(result);

                }else{

                    qreal result =  qPow(op1.valor.at(0).toLatin1()  ,0);
                    r.valor = QString::number(result);
                }

                break;
            }
            default:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"no se pueden potenciar los tipos");
                break;
            }

            }
            break;
        }
        case BOOL:{

            switch (op2.tipo) {

            case INT:{

                r.tipo =INT;
                if(condBool(op1.valor))
                {
                    qreal result =  qPow(1 ,op2.valor.toInt());
                    r.valor = QString::number(result);
                }else{
                    qreal result =  qPow(0 ,op2.valor.toInt());
                    r.valor = QString::number(result);
                }

                break;
            }
            case STRING:{
                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"no se pude elvar un string a un bool");
                break;
            }
            case DOUBLE:{
                r.tipo =DOUBLE;
                if(condBool(op1.valor))
                {
                    qreal result =  qPow(1 ,op2.valor.toDouble());
                    r.valor = QString::number(result);
                }else{
                    qreal result =  qPow(0 ,op2.valor.toDouble());
                    r.valor = QString::number(result);
                }

                break;
            }
            case CHAR:{
                r.tipo =INT;
                if(condBool(op1.valor))
                {
                    qreal result =  qPow(1 ,op2.valor.at(0).toLatin1());
                    r.valor = QString::number(result);
                }else{

                    qreal result =  qPow(0,op2.valor.at(0).toLatin1());
                    r.valor = QString::number(result);

                }

                break;
            }
            case BOOL:{
                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"no se pude elvar un bool a un bool");

                break;
            }

            default:{

                r.tipo =ERROR;
                r.valor="null";
                Msgerror(r,"no se pueden potenciar los tipos");
                break;
            }

            }
            break;
        }
        default:{

            r.tipo =ERROR;
            r.valor="null";
            Msgerror(r,"no se pueden potenciar los tipos" );
            break;
        }
        }

        break;
    }
    case MENOS :
    {
        NodoAST hijo = raiz->hijos.at(0);
        Resultado op1 = OPERACION(&hijo);

        switch (op1.tipo) {

        case INT:{
            r.tipo =INT;
            int result = op1.valor.toInt()*(-1);
            r.valor =QString::number(result);
            break;
        }case STRING:{

            r.tipo =ERROR;
            r.valor="null";
            Msgerror(r,"no se convertir a negativo un string");
            break;
        }
        case DOUBLE:{
            r.tipo =DOUBLE;
            double result = op1.valor.toDouble()*(-1);
            r.valor =QString::number(result);
            break;
        }
        case CHAR:{
            r.tipo =ERROR;
            r.valor="null";
            Msgerror(r,"no se puede covertir a negativo un char");
            break;
        }
        case BOOL:{
            r.tipo =ERROR;
            r.valor="null";
            Msgerror(r,"no se puede convertir a nevativo un bool");
            break;
        }
        default:{


            r.tipo =ERROR;
            r.valor="null";
            Msgerror(r,"no se comvertir a negativo los valores");
            break;

        }



        }


        break;

    }
    case AUMENTO :
    {

        NodoAST hijo = raiz->hijos.at(0);
        Resultado op1 = OPERACION(&hijo);

        switch (op1.tipo) {

        case INT:{
            r.tipo =INT;
            int result = op1.valor.toInt()+1;
            r.valor =QString::number(result);

            aumentoVar(r);


            break;
        }
        case STRING:{

            r.tipo =ERROR;
            r.valor="null";
            Msgerror(r,"no se puede aumentar un string");
            break;
        }
        case DOUBLE:{
            r.tipo =DOUBLE;
            double result = op1.valor.toDouble()+1;
            r.valor =QString::number(result);
            aumentoVar(r);
            break;
        }
        case CHAR:{
            r.tipo =CHAR;
            int result =op1.valor.at(0).toLatin1()+1;
            r.valor =QString::number(result);
            aumentoVar(r);
            break;
        }
        case BOOL:{
            r.tipo =ERROR;
            r.valor="null";
            Msgerror(r,"no se puede aumentar un bool");
            break;
        }
        default:{

            r.tipo =ERROR;
            r.valor="null";
            Msgerror(r,"no se puede aumentar el valor");
            break;
        }


        }

        break;
    }
    case DECREMENTO :
    {
        NodoAST hijo = raiz->hijos.at(0);
        Resultado op1 = OPERACION(&hijo);

        switch (op1.tipo) {

        case INT:{
            r.tipo =INT;
            int result = op1.valor.toInt()-1;
            r.valor =QString::number(result);
            aumentoVar(r);
            break;
        }
        case STRING:{

            r.tipo =ERROR;
            r.valor="null";
            Msgerror(r,"no se puede decrementar un string");
            break;
        }
        case DOUBLE:{
            r.tipo =DOUBLE;
            double result = op1.valor.toDouble()-1;
            r.valor =QString::number(result);
            aumentoVar(r);
            break;
        }
        case CHAR:{
            r.tipo =CHAR;
            int result =op1.valor.at(0).toLatin1()-1;
            r.valor =QString::number(result);
            aumentoVar(r);
            break;
        }
        case BOOL:{
            r.tipo =ERROR;
            r.valor="null";
            Msgerror(r,"no se puede decrementar un bool");
            break;
        }
        default:{

            r.tipo =ERROR;
            r.valor="null";
            Msgerror(r,"no s epuede aumentar los valores" );
            break;
        }


        }



        break;
    }
    default:{

        Resultado r1 =VALOR(raiz);
        r.tipo = r1.tipo;
        r.valor = r1.valor;

        break;
    }
    }

    return r;
}
//******************************************************************************
//*************************** contValor ****************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
Resultado accion::VALOR(NodoAST* raiz){

    Resultado r = Resultado();
    r.linea = raiz->linea;
    r.columna = raiz->columna;

    switch (raiz->tipo_) {

    case IDENTIFICADOR :
    {


        Variable* VariableDeclarada = listaVariables.value(raiz->valor);
        if(VariableDeclarada!= nullptr){
            r.tipo =VariableDeclarada->tipo_;
            r.valor =VariableDeclarada->valor;
            VariableActual = raiz->valor;


        }else{

            r.tipo = ERROR;
            r.valor="null";
            Msgerror(r,"No existe una declaracion de \""+raiz->valor+"\"");

        }



        break;
    }

    case CADENA :
    {
        r.tipo = STRING;
        r.valor = raiz->valor.replace("\"","");
        break;
    }
    case ENTERO :
    {
        r.tipo = INT;
        r.valor = raiz->valor;
        break;
    }
    case DECIMAL :
    {
        r.tipo = DOUBLE;
        r.valor = raiz->valor;
        break;
    }
    case BOOLEANO :
    {
        r.tipo = BOOL;
        r.valor = raiz->valor;
        break;
    }
    case CARACTER :
    {
        r.tipo = CHAR;
        r.valor = raiz->valor.replace("\'","");
        break;
    }
    case ARREGLO :
    {
        r.tipo = ARREGLO;

        NodoAST listDimen = raiz->hijos.at(0);
        posicion* pos = coordenadas(&listDimen);

        Resultado result = obtenerValorArray(raiz,pos);

        r.tipo = result.tipo;
        r.valor = result.valor;

        break;
    }


    }


    return r;
}
//******************************************************************************
//**************** COsas que se repiten ****************************************
//******************************************************************************
//******************************************************************************
void accion::Msgerror(Resultado r, QString Msg){


    resultado+="Error Semantico: linea: "+QString::number(r.linea);
    resultado+=" col: "+QString::number(r.columna)+Msg+"\n";
    QTextStream(stdout) << "Error Semantico" << endl;


}

bool accion::condBool(QString valor){


    if((valor.toLower().compare("true")==0)||(valor.toLower().compare("verdadero")==0)){
        return true;
    }else{

        return false;
    }
}

bool accion::divCero(QString valor){

    if(valor.toInt()==0){

        return false;
    }else{

        return  true;
    }


}

bool accion::validaArray(NodoAST *raiz, Resultado r){

    //verificamos si el valor que hay en el indice es un entero
    if(esEntero(r)){
        int i = r.valor.toInt();
        array1* arr = listaarray.value(raiz->valor);

        //verficamos si exite el array
        if(arr){

            QString valor = arr->obtener(i);

            //verificamos si no  nos pasamos de posicion
            if(valor!="vacio")
            {
                return true;
            }else{
                Msgerror(r," Posicion ["+QString::number(i)+"] esta fuera de rango");
                return false;
            }

        }else{
            Msgerror(r," No existe el array ["+raiz->valor+"]");
            return false;
        }

    }else{

        return false;
    }

}

bool accion::esEntero(Resultado r){


    if(r.tipo ==INT){

        return true;
    }else{
        Msgerror(r,"El tamanio del vector no es un entero");
        return  false;
    }

}

void accion::aumentoVar(Resultado r){

    try {

        Variable* varActual = new Variable(r.tipo,r.valor);
        listaVariables.insert(VariableActual,varActual);


    } catch (int e) {

    }



}

//******************************************************************************
//**************** DImensiones ****************************************
//******************************************************************************
//******************************************************************************
void accion::AsignacionArreglo(NodoAST *raiz, NodoAST* dimension,Resultado tk_valor){

    int tamanio = dimension->hijos.size();


    switch (tamanio) {

    case 1:{

        NodoAST auxIndex = dimension->hijos.at(0);
        Resultado Index = OPERACION(&auxIndex);

        if(validaArray(raiz,Index)){
            int i = Index.valor.toInt();
            array1* lol = listaarray.value(raiz->valor);
            lol->anadir(i,tk_valor.valor);
        }

        break;
    }
    case 2:{
        posicion* pos = coordenadas(dimension);

        if(pos){

            array2* arr = listaarray2.value(raiz->valor);

            //verficamos si exite el array
            if(arr){

                QString valor = arr->obtener(pos->x, pos->y);

                //verificamos si no  nos pasamos de posicion
                if(valor!="vacio")

                    arr->anadir(pos->x,pos->y,tk_valor.valor);


            }else{

                QString x = QString::number(pos->x);
                QString y = QString::number(pos->y);
                resultado+=" Posicion ["+x+"]["+y+"] esta fuera de rango\n";

            }

        }else{
            resultado+=" No existe el array ["+raiz->valor+"]\n";
        }



        break;
    }
    case 3:{

        resultado+="estamos trabajando en vectores de tres dimensiones!!!";
        break;
    }default :{

        resultado+="No podes usar arrary mayor a tres dimensiones crack :v";
        break;
    }

    }




}
//******************************************************************************
//**************** declarArray1 ****************************************
//******************************************************************************
//******************************************************************************
void  accion::InicializarArrayUnaDimension(int tipo, NodoAST* fila, int tamanio, NodoAST* listaid ){



    if(tamanio == fila->hijos.size()){



        QList<Resultado> cont =QList<Resultado>();

        for (int y= 0; y< fila->hijos.size(); y++)
        {
            NodoAST celda = fila->hijos.at(y);
            Resultado r = Resultado();
            r = contValor(&celda);
            cont.append(r);
        }


        for (int x= 0; x< listaid->hijos.size(); x++)
        {
            NodoAST id = listaid->hijos.at(x);
            array1* arr = new array1(tipo,tamanio);

            for (int y= 0; y< cont.size(); y++)
            {

                Resultado actual = cont.at(y);
                if(tipo == actual.tipo){
                    arr->anadir(y,actual.valor);

                    //agregamos el arreglo al final de todos los valores del arreglo
                    if(y == cont.size()-1){
                        listaarray.insert(id.valor,arr);
                    }

                }else {

                    if(x==0){

                        Msgerror(actual," EL tipo  de la celda ["+QString::number(y)+"] no es compatible con el tipo declarado");
                    }



                }

            }

        }



    }else{
        resultado+="El tamanio declarado no es igual al tamanio del vector";
    }




}
//******************************************************************************
//*******Declaracion de arrays multidimensionales*******************************
//******************************************************************************
//******************************************************************************
posicion*  accion::coordenadas(NodoAST* ListaDimension){

    int dimen = ListaDimension->hijos.size();

    //obtenes mos la dimension del array declarado
    switch (dimen) {

    case 1:{

        NodoAST tam = ListaDimension->hijos.at(0);//si es de una dimension obtenemos su hijo
        Resultado posx = OPERACION(&tam);// obtenemos el resultado de la operacion correspondientes

        // verficamos si la operacion nos arroja un entero
        if(esEntero(posx)){
            int tamaniox = posx.valor.toInt();

            return new posicion(dimen,tamaniox);

        }else {
            resultado+="el valor de la posicion no es un entero";
        }

        break;
    }
    case 2:{

        NodoAST tamx = ListaDimension->hijos.at(0);//si es de una dimension obtenemos su hijo
        Resultado posx = OPERACION(&tamx);// obtenemos el resultado de la operacion correspondientes
        NodoAST tamy = ListaDimension->hijos.at(1);//si es de una dimension obtenemos su hijo
        Resultado posy = OPERACION(&tamy);// obtenemos el resultado de la operacion correspondientes

        // verficamos si la operacion nos arroja un entero
        if(esEntero(posx) && esEntero(posy)){
            int tamaniox = posx.valor.toInt();
            int tamanioy = posy.valor.toInt();

            return new posicion(dimen,tamaniox,tamanioy);
        }else{
            resultado+="el valor de la posicion no es un entero";
        }

        break;
    }
    case 3:{
        NodoAST tamx = ListaDimension->hijos.at(0);//si es de una dimension obtenemos su hijo
        Resultado posx = OPERACION(&tamx);// obtenemos el resultado de la operacion correspondientes
        NodoAST tamy = ListaDimension->hijos.at(1);//si es de una dimension obtenemos su hijo
        Resultado posy = OPERACION(&tamy);// obtenemos el resultado de la operacion correspondientes
        NodoAST tamz = ListaDimension->hijos.at(2);//si es de una dimension obtenemos su hijo
        Resultado posz = OPERACION(&tamz);// obtenemos el resultado de la operacion correspondientes

        // verficamos si la operacion nos arroja un entero
        if(esEntero(posx) && esEntero(posy)){
            int tamaniox = posx.valor.toInt();
            int tamanioy = posy.valor.toInt();
            int tamanioz = posz.valor.toInt();

            return new posicion(dimen,tamaniox,tamanioy,tamanioz);
        }else{
            resultado+="el valor de la posicion no es un entero";
        }
        break;
    }
    default:{

        resultado+="No puedes trabajar con arrays de mas de tres dimensiones";
        return nullptr;
    }
    }

    return nullptr;
}
QStringList accion::getListaid(NodoAST* ListaId){

    int tamanio = ListaId->hijos.size();
    QStringList result = QStringList();

    for(int i=0; i< tamanio; i++){

        NodoAST actual = ListaId->hijos.at(i);
        QString id = actual.valor;
        result.append(id);
    }


    return result;

}
void accion::declaracionArrayMultidimension(int  tipo, posicion* pos, QStringList ListaId){


    switch (pos->getdimen()) {

    case 1:{

        int tamanio = ListaId.size();

        for (int i=0;i< tamanio  ;i++) {

            QString id = ListaId.at(i);
            array1* arr = new array1(tipo,pos->x);
            listaarray.insert(id,arr);

            if(i==tamanio-1){

                QTextStream(stdout) << "Arreglo creado con exito" << endl;
            }

        }

        break;
    }
    case 2:  {

        int tamanio = ListaId.size();

        for (int i=0;i< tamanio  ;i++) {

            QString id = ListaId.at(i);
            array2* arr = new array2(tipo,pos->x, pos->y);
            listaarray2.insert(id,arr);

            if(i==tamanio-1){

                QTextStream(stdout) << "Arreglo  de dos dimensiones creado " << endl;

            }


        }



        break;
    }
    case 3:{

        break;
    }
    }

}
void accion::inicializarArrayMulltidimension(int tipo, NodoAST* array, posicion* pos, QStringList ListaId ){


    int tamFila = array->hijos.size();
    array2* arr = new array2(tipo,pos->x, pos->y);


    if(tamFila == pos->x){

        for (int i =0 ;i<tamFila;i++) {

            NodoAST FilaActual = array->hijos.at(i);
            int tamCol = FilaActual.hijos.size();

            if(tamCol == pos->y){

                for (int j=0;j<tamCol;j++) {

                    NodoAST ColActual = FilaActual.hijos.at(j);

                    Resultado r = Resultado();
                    r = contValor(&ColActual);

                    if(tipo == r.tipo){
                        arr->anadir(i,j,r.valor);

                    }else{

                        resultado +=  "La posicion  ("+QString::number(i)+","+QString::number(j)+") no coincide con el tipo declarado \n";
                    }


                }

            }else{

                resultado+="EL numero de columnas de la Fila["+QString::number(i)+"] no es el correcto\n";
            }

        }


    }else{

        resultado+="Las numero de Filas no es el correcto\n";

    }


    for (int z=0;z<ListaId.size();z++) {

        QString id = ListaId.at(z);

        listaarray2.insert(id,arr);
        QTextStream(stdout) << "arreglo inicializo fila = "+QString::number(z)+"" << endl;



    }



}

//******************************************************************************
//****** Imprimir Matriz********************************************************
//******************************************************************************
//******************************************************************************
void accion::imprimiarMatriz(){

    QHash<QString,array2*>::iterator i;
    for (i = listaarray2.begin(); i != listaarray2.end(); ++i){

        QString id = i.key();

        QTextStream(stdout) << "id: " +id+"\n"<< endl;

        array2* arr=  arr= i.value();

        if(arr){

            for (int i=0;i<arr->getTamanio();i++) {

                QString valor = arr->obtener(i);
                coor coordenada = arr->toCoordenadas(i);
                QString x = QString::number(coordenada.x);
                QString y = QString::number(coordenada.y);

                QTextStream(stdout) << "id["+x+"]["+y+"]= "+valor+""<< endl;


            }


        }else{

            QTextStream(stdout) << "la variable no contiene nada men\n"<< endl;
        }


    }


}

//******************************************************************************
//****** Limpiar ***************************************************************
//******************************************************************************
//******************************************************************************
void accion::limpiar(){
    listaarray.clear();
    listaarray2.clear();
    listaVariables.clear();

}

//******************************************************************************
//******  Obtner el valor de un array ******************************************
//******************************************************************************
//******************************************************************************
Resultado accion::obtenerValorArray(NodoAST *identificador, posicion *pos){


    Resultado r =Resultado();
    r.linea = identificador->linea;
    r.columna = identificador->columna;


    switch (pos->getdimen()) {

    case 1:{

        QString id =identificador->valor;
        array1* arr = listaarray.value(id);

        if(arr){

            QString valor = arr->obtener(pos->x);

            if(valor!="vacio"){

                r.valor = valor;
                r.tipo = arr->tipo;


            }else{
                r.tipo=ERROR;
                r.valor="null";
                Msgerror(r," La posicion del arreglo  "+id+" esta fuera del rango \n");
            }
        }else{
            r.tipo=ERROR;
            r.valor="null";
            Msgerror(r," El arreglo: "+id+" no ha sido declarado \n");
        }

        break;
    }
    case 2:{


        QString id =identificador->valor;
        array2* arr = listaarray2.value(id);

        if(arr){

            QString valor = arr->obtener(pos->x, pos->y);

            if(valor!="vacio"){

                r.valor = valor;
                r.tipo = arr->tipo;


            }else{
                r.tipo=ERROR;
                r.valor="null";
                Msgerror(r," La posicion del arreglo  "+id+" esta fuera del rango \n");
            }
        }else{

            r.tipo=ERROR;
            r.valor="null";
            Msgerror(r," El arreglo: "+id+" no ha sido declarado \n");
        }

        break;


    }

    default:{

        r.tipo=ERROR;
        r.valor="null";
        break;
    }


    }




    return r;

}
//******************************************************************************
//******  Obtner el valor de un array ******************************************
//******************************************************************************
//******************************************************************************
bool accion::condIf(NodoAST* Condicion){



    Resultado r = contValor(Condicion);

    if(r.tipo==BOOL)
    {

        if(condBool(r.valor)){

            return true;
        }else{

            return false;

        }


    }else{

        Msgerror(r,"La condicion  no es de tipo booleano");

        return false;
    }


}









