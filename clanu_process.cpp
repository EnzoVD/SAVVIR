// Clanu 2015 - 2016
// T. Grenier : thomas.grenier@insa-lyon.fr

#include "clanu_process.h";
#include <math.h>;
float ** Matrice_A(float **, float **, int, int);

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


  float**b;
  float**xk;
  float**dk;
  float**rk;
  float alphak;
  float**prov;

  b=Iin;
  xk=b;
  dk=SoustractionMatrice(b,Matrice_A(Iin,Mask,width,height);




  while(res>param){
      rk=SoustractionMatrice(b,Matrice_A(xk,Mask,width,height));
      Ark=Matrice_A(rk,Mask);
      alphak=0;

  }




}


// to do ... IF Q3
void InpaintingColor(float **Rout, float **Gout, float **Bout, float **Rin, float **Gin, float **Bin, float **Mask, int width, int height, double param)
{

}


// Gradient conjugué











// Opérations sur les matrices
// Somme

// /////// Transposition

float** TranspositionMatrice(float **Matrice, float **MatriceT)
{
    MatriceT[i][j] = Matrice[j][i];

    return MatriceT;
}

//************Addition************
float** AdditionMatrice(float **Matrice1, float **Matrice2)
{
    w=sizeof(Matrice1[][1]);
    h=sizeof(Matrice1[1][]);

    float **Matrice[w][h];

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            Matrice[i][j] = Matrice1[i][j] + Matrice2[i][j];
        }
    }

    return Matrice;
}

//************Addition************
float** SoustractionMatrice(float **Matrice1, float **Matrice2)
{
    w=sizeof(Matrice1[][1]);
    h=sizeof(Matrice1[1][]);

    float **Matrice[w][h];

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            Matrice[i][j] = Matrice1[i][j] - Matrice2[i][j];
        }
    }

    return Matrice;
}


//Multiplication terme à terme

float** Matrice_Mult_Tat(float** A, float** B){
    //Pas besoin de vérifier les tailles, bonnes tailles par construction

    w=sizeof(A[][1]);
    h=sizeof(A[1][]);
    R=new float[w][h];

    for(int x=0; x<w;x++){

        for(int y=0; y<h;y++){

            R[x][y]=A[x][y]*B[x][y];
        }

    }
    return R;

}



//Multiplication

float** Matrice_Mult_Scal(float scal, float** A){
    //Pas besoin de vérifier les tailles, bonnes tailles par construction

    w=sizeof(A[][1]);
    h=sizeof(A[1][]);
    R=new float[w][h];

    for(int x=0; x<w;x++){

        for(int y=0; y<h;y++){

            R[x][y]=scal*A[x][y];
        }

    }
    return R;

}


//Somme de tous les éléments d'une matrice

float Sum_Elements_Matrice(float** Mat){
    float R=0;

}


//PDS

