// Clanu 2015 - 2016
// T. Grenier : thomas.grenier@insa-lyon.fr

#include "clanu_process.h"
#include "imageconvert.h"
#include <math.h>

//test


float ** Matrice_A(float **, float **, int, int);
float** Transposition_Matrice(float **Matrice,int width,int height);
float** Addition_Matrice(float **Matrice1, float **Matrice2,int width,int height);
float** Soustraction_Matrice(float **Matrice1, float **Matrice2,int width,int height);
float** Multiplication_TaT_Matrice(float** A, float** B,int width,int height);
float** Multiplication_Scalaire_Matrice(float scal, float** A,int width,int height);
float** Multiplication_Matrice(float** A, float** B,int width,int height);
float Sum_Elements_Matrice(float** Mat,int width,int height);
void GetSizeTab(float** Mat, int* width, int* height);
void Copie_Matrice(float** Mat1,float** Mat2,int w, int h);

// to complete for Q1
void Question1(float **Rout, float **Gout, float **Bout, float **Rin, float **Gin, float **Bin, float **Mask, int width, int height, double param)
{
    for(int x=0; x<width; x++)
        for(int y=0;y<height; y++)
        {
            if(Mask [x][y] !=0) Rout[x][y] = 255 -  Rin[x][y];
            if(Mask [x][y]!= 0) Gout[x][y] = 255 -  Gin[x][y];
            if(Mask [x][y] != 0) Bout[x][y] = 255 - Bin[x][y];
        }

}

// Matrice du produit A*B

float ** Matrice_A(float **Mask, float **Input, int width, int height)
{
    float** J = AllocateFloatArray(width,height);

    for(int i=0; i<width; i++){
        bool bool_iplus = (i<width);
        int iplus = fmin(i+1,width);
        bool bool_imoins = (i>1);
        int imoins = fmax(i-1,1);

        for(int j=0; j<height; j++){
            bool bool_jplus = (j<height);
            int jplus = fmin(j+1,height);
            bool bool_jmoins = (j>1);
            int jmoins = fmax(j-1,1);

            if(Mask[i][j]>0){
                 J[i][j]=(1/36)*(16*Input[i][j] + 4*(bool_iplus*Input[iplus][j]+bool_imoins*Input[imoins][j]+ bool_jplus*Input[i][jplus] + bool_jmoins*Input[i][jmoins] + (bool_iplus*bool_jplus*Input[iplus][jplus] + bool_imoins*bool_jplus*Input[imoins][jplus]+ bool_imoins*bool_jmoins*Input[imoins][jmoins])+bool_iplus*bool_jmoins*Input[iplus][jmoins]));
            }
            else{
                J[i][j]= -height*width*(-8*Input[i][j]+ 1*(Input[iplus][j] + Input[imoins][j] + Input[i][jplus] + Input[i][jmoins])+ (Input[iplus][jplus] + Input[imoins][jplus] + Input[imoins][jmoins]) + Input[iplus][jmoins]);

            }
        }

    }

    return J;
}

// to do ... IF Q2
void InpaintingBW(float **Iout, float **Iin, float **Mask, int width, int height, double param)
{


    float**b=AllocateFloatArray(width,height);
    float**xk=AllocateFloatArray(width,height);
    float**xk2=AllocateFloatArray(width,height);
    float**dk=AllocateFloatArray(width,height);
    float**rk=AllocateFloatArray(width,height);
    float alphak;
    float betak;
    float**Ark=AllocateFloatArray(width,height);
    float**prov=AllocateFloatArray(width,height);
    float res;

    b=Iin;
    xk=b;
    dk=Soustraction_Matrice(b,Matrice_A(Iin,Mask,width,height),width,height);
    res=100;



            while(res>param){

            rk=Soustraction_Matrice(b,Matrice_A(xk,Mask,width,height),width,height);
            Ark=Matrice_A(rk,Mask,width,height);
            alphak = Sum_Elements_Matrice(Multiplication_TaT_Matrice(rk,rk,width,height),width,height)/Sum_Elements_Matrice(Multiplication_TaT_Matrice(Ark,rk,width,height),width,height);
            xk2 = Addition_Matrice(xk, Multiplication_Scalaire_Matrice(alphak,dk,width,height),width,height);
            xk=xk2;
            prov=rk;
            rk=Soustraction_Matrice(b,Matrice_A(xk,Mask,width,height),width,height);
            betak=Sum_Elements_Matrice(Multiplication_TaT_Matrice(rk,rk,width,height),width,height)/Sum_Elements_Matrice(Multiplication_TaT_Matrice(prov,prov,width,height),width,height);
            dk=Addition_Matrice(rk,Multiplication_Scalaire_Matrice(betak,dk,width,height),width,height);

            //Calcul de res
            res = Sum_Elements_Matrice(Multiplication_Scalaire_Matrice(1/(height*width),Multiplication_TaT_Matrice(Transposition_Matrice(dk,width,height), dk,width,height),width,height),width,height);
}

            Copie_Matrice(Iout,xk,width,height);



}


// to do ... IF Q3
void InpaintingColor(float **Rout, float **Gout, float **Bout, float **Rin, float **Gin, float **Bin, float **Mask, int width, int height, double param)
{

}


// Gradient conjugué











// Opérations sur les matrices


// /////// Transposition

float** Transposition_Matrice(float **Matrice,int w,int h)
{




    float** MatriceT = AllocateFloatArray(w,h);

    for(int i=0; i<w; i++)
    {
        for(int j=0; j<h; j++)
        {
    MatriceT[i][j] = Matrice[j][i];
        }
    }

    return MatriceT;
}

//************Addition************
float** Addition_Matrice(float **Matrice1, float **Matrice2,int w,int h)
{


    float ** Matrice = AllocateFloatArray(w,h);

    for(int i=0; i<w; i++)
    {
        for(int j=0; j<h; j++)
        {
            Matrice[i][j] = Matrice1[i][j] + Matrice2[i][j];
        }
    }

    return Matrice;
}

//************Addition************
float** Soustraction_Matrice(float **Matrice1, float **Matrice2,int w,int h)
{


    float **Matrice = AllocateFloatArray(w,h);

    for(int i=0; i<w; i++)
    {
        for(int j=0; j<h; j++)
        {
            Matrice[i][j] = Matrice1[i][j] - Matrice2[i][j];
        }
    }

    return Matrice;
}


//Multiplication terme à terme

float** Multiplication_TaT_Matrice(float** A, float** B,int w,int h){
    //Pas besoin de vérifier les tailles, bonnes tailles par construction

     float** R = AllocateFloatArray(w,h);

    for(int x=0; x<w;x++){

        for(int y=0; y<h;y++){

            R[x][y]=A[x][y]*B[x][y];
        }

    }
    return R;

}



//Multiplication

float** Multiplication_Scalaire_Matrice(float scal, float** A,int w,int h){
    //Pas besoin de vérifier les tailles, bonnes tailles par construction


    float** R = AllocateFloatArray(w,h);

    for(int x=0; x<w;x++){

        for(int y=0; y<h;y++){

            R[x][y]=scal*A[x][y];
        }

    }
    return R;

}

float** Multiplication_Matrice(float** A, float** B,int w,int h){


    float** R= AllocateFloatArray(w,h);



    for(int y1=0; y1<h;y1++){
        for(int y2=0; y2<h;y2++){
            R[y2][y1]=0;
            for(int x=0; x<w;x++){

            R[y2][y1]=R[y2][y1]+A[x][y1]*B[y2][x];


            }
        }
    }


    return R;
}

//Somme de tous les éléments d'une matrice

float Sum_Elements_Matrice(float** Mat,int w,int h){
    float R=0;



    for(int x=0; x<w;x++){

        for(int y=0; y<h;y++){

            R=R + Mat[x][y];
        }

    }
    return R;


}


void Copie_Matrice(float** Mat1,float** Mat2,int w, int h){
    //copie Mat2 dans Mat1

    for(int x=0; x<w;x++){

        for(int y=0; y<h;y++){

            Mat1[x][y]=Mat2[x][y];
        }

    }

}

//void GetSizeTab(float** Mat, int* width, int* height){

//    *width=sizeof(Mat)/sizeof(Mat[0]);

//    *height=sizeof(Mat[0])/sizeof(Mat[0][0]);

//}






//PDS

