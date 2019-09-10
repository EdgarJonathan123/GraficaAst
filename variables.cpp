#include "variables.h"

//******************************************************************************
//***************************Variables ************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
Variable::Variable(int tipo_, QString valor)
{
    this->tipo_ = tipo_;
    this->valor =valor;



}

//******************************************************************************
//*************************** Array1************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************


array1::array1(int tipo, int tamanio){


    this->tamanio = tamanio;
    this->tipo =tipo;
    for (int x= 0; x< tamanio; x++)
    {
        arreglo.append("null");

    }


    QTextStream(stdout) << "tamanio: "+QString::number(arreglo.size()) << endl;

}

bool array1::anadir(int index, QString valor){

    if(index<tamanio){

        arreglo.insert(index,valor);
        arreglo.removeLast();
        return true;
    }else{

        return false;
    }

}

QString array1::obtener(int index){

    if(index<tamanio){

        return  arreglo.at(index);


    }else{

        return "vacio";
    }

}

//******************************************************************************
//*************************** Array1********************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

posicion::posicion(int dimen, int x){

    this->dimen = dimen;
    this->x =x;
    this->y=0;
    this->z=0;


}
posicion::posicion(int dimen, int x, int y){

    this->dimen = dimen;
    this->x =x;
    this->y=y;
    this->z=0;

}
posicion::posicion(int dimen, int x, int y, int z){

    this->dimen = dimen;
    this->x =x;
    this->y=y;
    this->z=z;
}


int posicion::getdimen(){

    return dimen;
}
void posicion::setdimen(int d){

    this->dimen = d;
}

//******************************************************************************
//***************************Array2********************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************




array2::array2(int tipo , int unsigned tamFila,int unsigned tamCol){

    setTamCol(tamFila);
    setTamFila(tamCol);
    this->tipo = tipo;
    //--restamos uno a la fila y columna para
    //--  que que empieze a contar en 0,0
    //-- y sumamos a uno al final para que nos de
    //-- el tamaniao de la lista a utilizar
    this->tamanio = mapeo(tamFila-1, tamCol-1)+1;

    for (int unsigned  x= 0; x< tamanio; x++)
    {
        arreglo.append("null");

    }


}

bool array2::anadir(int unsigned fila, int unsigned  col, QString valor){

    int  unsigned index = mapeo(fila,col);

    if(index<tamanio){

        int aux = unsigned_to_signed(index);
        arreglo.insert(aux,valor);
        arreglo.removeLast();
        return true;
    }else{

        return false;
    }

}

bool array2::anadir(int num, QString valor){


     coor coordenada =toCoordenadas(num);

    return  anadir(coordenada.x, coordenada.y, valor);

}

QString array2::obtener(int index ){

    if(index<tamanio){
        int aux = unsigned_to_signed(index);
        return  arreglo.at(aux);
    }else{

        return "vacio";
    }


}





QString array2::obtener(int unsigned fila, int unsigned col){

    int unsigned index = mapeo(fila,col);

    if(index<tamanio){
        int aux = unsigned_to_signed(index);
        return  arreglo.at(aux);
    }else{

        return "vacio";
    }

}


int unsigned array2::mapeo(int unsigned x, int unsigned y){

    int unsigned result =x*getTamCol()+y;
    return  result;
}


unsigned int array2::getTamanio() const
{
    return tamanio;
}

void array2::setTamanio(unsigned int value)
{
    tamanio = value;
}

unsigned int array2::getTamFila() const
{
    return tamFila;
}

void array2::setTamFila(unsigned int value)
{
    tamFila = value;
}

unsigned int array2::getTamCol() const
{
    return tamCol;
}

void array2::setTamCol(unsigned int value)
{
    tamCol = value;
}


int array2::unsigned_to_signed(unsigned n)
{
    int int_n = static_cast<int>(n);

    if (n == static_cast<unsigned>(int_n)){
        return int_n;
    }
    else {

        return -1;
    }

}


coor array2::toCoordenadas(int index){


    double auxFila = index/unsigned_to_signed(tamCol);
    int fila = int (auxFila);
    double auxCol = index- tamCol*fila;
    int col = int (auxCol);

    coor micoordenada;
    micoordenada.x=fila;
    micoordenada.y =col;

    return micoordenada;

}


//******************************************************************************
//***************************Var********************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

Varmas::Varmas(){

}

Varmas::Varmas(QString valor)
{
    this->valor = valor;
}



