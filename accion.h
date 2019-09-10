#ifndef ACCION_H
#define ACCION_H
#include <NodoAST.h>
#include <resultado.h>
#include <QString>
#include <iostream>
#include <QHash>
#include <QTextStream>
#include <QChar>
#include <QtMath>
#include <variables.h>

enum Choice
{
    //para verifcar si las variables no han sindo declaradas
    ERROR =-1,

    //--inicio
    INICIO =1 ,

    //--listas principales
    LISTA_CUERPO = 2,
    LISTA_REPETIR=3,
    LISTA_FOR=4,
    LISTA_MOSTRAR=5,
    LISTA_IMPRIMIR=6,
    LISTA_ASIGNACION=7,
    LISTA_DECLARACION=8,
    LISTA_IF=9,

    //Declaracion var
    DECLARACIONVAR1=10,
    DECLARACIONVAR2=11,
    DECLARACIONARRAY1=12,
    DECLARACIONARRAY2=13,
    DECLARACIONARRAY3=14,

    //--tipo de dato
    STRING =15,
    BOOL =16,
    INT = 17,
    DOUBLE =18,
    CHAR =19,

    //valores de operaciones y condiciones
    IDENTIFICADOR =20,
    CADENA =21,
    ENTERO=22,
    DECIMAL = 23,
    BOOLEANO=24,
    CARACTER=25,
    ARREGLO=26,

    //--cont valor
    AND =27,
    OR =28,
    MAYORQUE=29,
    MENORQUE=30,
    MAYORIGUAL=31,
    MENORIGUAL=32,
    IGUALACION=33,
    DIFERENCIACION=34,


    //--operacion
    SUMA = 35,
    RESTA = 36,
    POR = 37,
    DIV = 38,
    POTENCIA = 39,
    MENOS =40,
    AUMENTO =41,
    DECREMENTO =42,
    LISTA_VALORES =43,

    //-sentencia if
    IF =44,
    IF_SIN_CUERPO =45,
    ELSE_IF =46,
    ELSE =47,


    //--repetir
    REPETIR_CUERPO=48,
    REPETIR_VACIO=49,

    //---para el disque ciclo for
    ASIG=50,
    DECLARA=51,
    FOR =52,
    FOR_VACIO =53,
};




class accion
{
public:

    QString  resultado;
    QHash<QString,Variable*>listaVariables;
    QHash<QString,array1*>listaarray;
    QHash<QString,array2*>listaarray2;
    QList<alerta> listaarlerta;
    QString VariableActual="";

    accion();

    //-----inicio del documento
    void init(NodoAST *raiz);
    void Cuerpo(NodoAST*raiz);
    void ListaCuerpo(NodoAST* raiz);

    //-------------------Acciones y sentencias
    void declaracion(NodoAST* raiz);
    void asignacion(NodoAST* raiz);
    void imprimir(NodoAST* raiz);
    void sentenciaMostrar(NodoAST* raiz);
    void sentenciaIf(NodoAST* raiz);
    void sentenciaElse(NodoAST* raiz);
    void sentenciaFor(NodoAST* raiz);
    void sentendiaRepetir(NodoAST* raiz);

    //--para la declaracion
    Resultado tipoDato(NodoAST* raiz);
    void  declaracionVariable(NodoAST* raiz, int tipo,int tipo_valor, QString valor );
    Resultado contValor(NodoAST* raiz);
    Resultado OPERACION(NodoAST* raiz);
    Resultado VALOR(NodoAST* raiz);
    //para almacenar las variables


    //----acciones que se repiten xd
    void Msgerror(Resultado r, QString Msg);
    bool condBool(QString valor);
    bool divCero(QString valor);
    bool esEntero(Resultado r);
    bool validaArray(NodoAST*raiz,Resultado r);
    void aumentoVar(Resultado r);



    //----declaracion y inicializacion de arreglos
    void  InicializarArrayUnaDimension(int tipo, NodoAST* fila, int tamanio, NodoAST* listaid );
    void AsignacionArreglo(NodoAST *raiz, NodoAST* dimension,Resultado tk_valor);
    void declaracionArrayMultidimension(int  tipo , posicion* pos, QStringList ListaId);
    void inicializarArrayMulltidimension(int tipo, NodoAST* array, posicion* pos, QStringList ListaId );
    posicion*  coordenadas(NodoAST* ListaDimension);
    QStringList getListaid(NodoAST* ListaId);
    void imprimiarMatriz();
    Resultado obtenerValorArray(NodoAST* identificador , posicion* pos);



    //-- para imprimir
    QString getValores(NodoAST* raiz);
    bool condIf(NodoAST* Condicion);


    ///----para la sentencia for
    void forCond(NodoAST* raiz);


    //---limpiar
    void limpiar();

};




#endif // ACCION_H
