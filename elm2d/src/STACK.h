/////////////////////////
// merge.h
////////////////////////
double vxS[Ny][Nx],vyS[Ny][Nx],vmagS[Ny][Nx];
#define outputS "Stackvel"


void sum_vel()
{

 int i,j;
 if(run_time==0)
 {
  for(i=0; i<Ny; i++)
  {
  for(j=0; j<Nx; j++)
  {
    vxS[i][j]=0.0;
    vyS[i][j]=0.0;
    vmagS[i][j]=0.0;
  }
  }
 }

 send_up();
 for(i=1; i<Ny-1; i++)
 {
 for(j=0; j<Nx; j++)
 {
  // vxS[i][j]=vxS[i][j] + upx[i][j] ;
  // vyS[i][j]=vyS[i][j] + upy[i][j] ;   

//left_p[i][0]=0; right_p[i][0]=0;
//left_p[i][1]=0; right_p[i][1]=0;

   if(j==0)
   {
    vxS[i][j]=vxS[i][j] + (upx[i][j+1]-left_p[i][0])/2.0/dx + (upy[i+1][j]-upy[i-1][j])/2.0/dx ;
    vyS[i][j]=vyS[i][j] + (upy[i][j+1]-left_p[i][1])/2.0/dx - (upx[i+1][j]-upx[i-1][j])/2.0/dx ;
   }
   else if(j==Nx-1)
   {
    vxS[i][j]=vxS[i][j] + (right_p[i][0]-upx[i][j-1])/2.0/dx + (upy[i+1][j]-upy[i-1][j])/2.0/dx ;
    vyS[i][j]=vyS[i][j] + (right_p[i][1]-upy[i][j-1])/2.0/dx - (upx[i+1][j]-upx[i-1][j])/2.0/dx ;
   }
   else
   {
    vxS[i][j]=vxS[i][j] + (upx[i][j+1]-upx[i][j-1])/2.0/dx + (upy[i+1][j]-upy[i-1][j])/2.0/dx ;
    vyS[i][j]=vyS[i][j] + (upy[i][j+1]-upy[i][j-1])/2.0/dx - (upx[i+1][j]-upx[i-1][j])/2.0/dx ;
   }

   vmagS[i][j]=vmagS[i][j]+(upx[i][j]*upx[i][j] + upy[i][j]*upy[i][j] );
 }
 }

}

void snap_velS()
{
int i, j;
FILE *out;
char  string[50];

   sprintf( string,"%s_%d",outputS,my_rank);
   if(( out = fopen( string,"w")) ==NULL )
   {
      printf("Error opening file %s_%d  \n",string,my_rank);
      MPI_Finalize();
      exit(0);
      fclose(out);
   }

// data output on each node:
   for(j=0; j<Nx; j++)
   { 
   for(i=0; i<Ny; i++)
   {
      fprintf(out,"%e %e %e\n",vmagS[i][j],vxS[i][j] , vyS[i][j]); 

   }
   }
   fclose(out);
   MPI_Barrier(new_comm);

}

void merge_velS()
{
int i, j, k, n;
int nosnaps;
double a1, a2,a3,a4,aa[3];
char string[50];
FILE *out;

   sprintf(string,"%s",outputS );
   if( (out = fopen( string,"w")) ==NULL )
   {
         printf("Error opening  file %s  \n",string);
         MPI_Finalize();
         exit(0); fclose(out);
   }

  for(j=0; j<my_size; j++)
  {
    sprintf(string,"%s_%d",outputS,j);
    if((input[j] = fopen(string,"r")) ==NULL )
    {
      printf("Error 3 opening file %s \n",string);
      MPI_Finalize(); exit(0);
    }
  }

  for(n = 0; n < my_size; n++)
  {
  for(i = 0; i < Ny; i++)
  {
  for(j = 0; j < Nx; j++)
  {
    fscanf( input[n],"%lf %lf %lf\n", &a1, &a2, &a3);
    aa[0]=a1; aa[1]=a2; aa[2]=a3;
    fwrite(&aa, sizeof(double), 3, out);
  }
  }
  }
  


 // close files
  for (j = 0; j < my_size; j++)
  {
   fclose(input[j]);
   sprintf(string,"%s_%d",outputS,j);
   remove(string);
  }

 fclose(out);



}

