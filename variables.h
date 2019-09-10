#ifndef VARIABLES_H
#define VARIABLES_H

#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QArrayData>

struct alerta {


    QString titulo;
    QString contenido;
};


struct coor{


    int x;
    int y;
};
class Varmas
{
public:
    Varmas();
    Varmas(QString valor);
    QString valor;

};


class  posicion{

private:
    int dimen;
public :
    posicion(int dimen, int x);
    posicion(int dimen, int x, int y);
    posicion(int dimen, int x, int y, int z);
    int x;
    int y;
    int z;

    int getdimen();
    void setdimen(int d);
};



class Variable
{
public:
    int tipo_;
    QString valor;

    Variable(int tipo_, QString valor);
    Variable();
};




class array1{

public:
    int tipo;
    int tamanio;
    QStringList arreglo;

    array1(int tipo, int taminaio);
    array1();
    bool anadir(int index, QString valor);

    QString obtener(int index);

};


class array2{

public:

    int tipo;
    QStringList arreglo;

    array2(int tipo , int unsigned tamFila,int unsigned tamCol);
    array2();

    bool anadir(int unsigned fila, int unsigned  col, QString valor);
    bool anadir(int num, QString valor);
    QString obtener(int unsigned fila, int unsigned col);
    QString obtener(int index );


    unsigned int getTamanio() const;
    void setTamanio(unsigned int value);

    unsigned int getTamFila() const;
    void setTamFila(unsigned int value);

    unsigned int getTamCol() const;
    void setTamCol(unsigned int value);

    coor toCoordenadas(int index);

private:

    int unsigned mapeo(int unsigned x, int unsigned y);
    int unsigned_to_signed(unsigned n);
    int unsigned tamanio;
    int unsigned tamFila;
    int unsigned tamCol;



};
class array3{};

#endif // VARIABLES_H
