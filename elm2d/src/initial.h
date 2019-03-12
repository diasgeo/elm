///////////////////////////////////////////////////////////////////
#define Ltop 640
void load_surface()
{

 int i,j,k,n,p;
 FILE *input;

 if(( input= fopen("../sem5/etna_surf1.dat","r"))==NULL )
 {
     printf("Error 5001: opening topography file on node %d\n",my_rank);
     MPI_Finalize();
     exit(0);
 }
 for (n=0; n<(Ltop); n++)
 {
    fscanf(input,"%lf %lf\n",&topo1[n][0],&topo1[n][1]);
 }
 fclose(input);
 //printf("loaded 1 %d\n",my_rank);

 if(( input= fopen("../sem5/etna_surf2.dat","r"))==NULL )
 {
     printf("Error 5002: opening topography file on node %d\n",my_rank);
     MPI_Finalize();
     exit(0);
 }
 for (n=0; n<(Ltop); n++)
 {
    fscanf(input,"%lf %lf\n",&topo2[n][0],&topo2[n][1]);
 }
 fclose(input);
 //printf("loaded 2 %d\n",my_rank);

if(( input= fopen("../sem5/etna_surf3.dat","r"))==NULL )
 {
     printf("Error 5003: opening topography file on node %d\n",my_rank);
     MPI_Finalize();
     exit(0);
 }
 for (n=0; n<(Ltop); n++)
 {
    fscanf(input,"%lf %lf\n",&topo3[n][0],&topo3[n][1]);
 }
 fclose(input);
 //printf("loaded 3 %d\n",my_rank);

}

///////////////////////////////////////////////////////////////////

int locate_node(int coord)
{
  int i,node=0;

  for(i=0; i<my_size; i++)
  {
    if( coord < ((Nx)*i+Nx) && coord >= (Nx*i) )
    {
      node=i;
    }
  }
  return node;

}

///////////////////////////////////////////////////////////////////

void initial_lattice_setup()
{
 int i,j,k,ii;
 double fake1,fake2,fake3,aa[3];
 FILE *inputvel[my_size];
 char string[50];

 iroot2=(1.0/sqrt(2.0));
 dt2=(dt*0.5);

 NumSnaps=0;
 NumSnapsS=0;

///////////////////////////////////////////////////////////////////

 IndexX[0]=-1;
 IndexX[1]=0;
 IndexX[2]=1;
 IndexX[3]=1;
 IndexX[4]=1;
 IndexX[5]=0;
 IndexX[6]=-1;
 IndexX[7]=-1;

 IndexY[0]=1;
 IndexY[1]=1;
 IndexY[2]=1;
 IndexY[3]=0;
 IndexY[4]=-1;
 IndexY[5]=-1;
 IndexY[6]=-1;
 IndexY[7]=0;

///////////////////////////////////////////////////////////////////
 // Assigning Initial Homogeneous Values
 for(i=0; i<Nx+2; i++)
 {
 for(j=0; j<Ny; j++)
 {
   if(i<Nx)
   {
   up[i][j][0]=0.0;
   up[i][j][1]=0.0; 
   }

   dens[i][j]=density;
   vp[i][j]=velp;
   vs[i][j]=vels;
 }
 }

//////////////////////////////////////////////////////////////////
/*&MATERIAL tag=1, kind='ELAST' /
&MAT_ELASTIC rho=2000.d0, cp=2000.d0, cs=1250.d0 /

&MATERIAL tag=2, kind='ELAST' /
&MAT_ELASTIC rho=2300.d0, cp=3000.d0, cs=2000.d0 /

&MATERIAL tag=3, kind='ELAST' /
&MAT_ELASTIC rho=2500.d0, cp=4000.d0, cs=2750.d0 /
*/

 for(i=0; i<Nx*my_size; i++)
 {
 for(j=0; j<Ny; j++)
 {
  if(locate_node(i)==my_rank )
  {
  ii=i%Nx;
  if(j*dx>topo1[i][1] + dx )
  {
   vp[ii+1][j]=-1974.0;
  }

 /* if(j*dx<=topo2[i][1] && j*dx>topo3[i][1]+1)
  {
     dens[ii+1][j]=2300.0;
     vp[ii+1][j]=3000.0;
     vs[ii+1][j]=2000.0;
  }

  if(j*dx<=topo3[i][1] )
  {
     dens[ii+1][j]=2500.0;
     vp[ii+1][j]=4000.0;
     vs[ii+1][j]=2750.0;
  }*/

  }
 }
 }
///----------------------------------------------


 for(i=0; i<Nx; i++)
 {
 for(j=0; j<Ny; j++)
 {
    posn[i+1][j][0]=i*dx+my_rank*dx*Nx;
    posn[i+1][j][1]=dx*j;

    eqposn[i][j][0]=posn[i+1][j][0];
    eqposn[i][j][1]=posn[i+1][j][1];
 }
 }

}


