////////////////////////////////////////////////////////////////////
// initial.h
/////////////////////////////////////////////////////////////////////

void initial_lattice_setup()
{
 int i,j,jj,n,m,p;
 double vp_in;
 FILE *in;
 char string[50];
 NumSnaps=0;
 
/////////////////////////////////////////////////////////////////
// Setting Up the DP Scheme
/////////////////////////////////////////////////////////////////
r0=v_alloc3d(Ny,Nx,4);
kspring=v_alloc3d(Ny,Nx,4);
force=v_alloc3d(Ny,Nx,2);
posn=v_alloc3d(Ny,Nx,2);
eqposn=v_alloc3d(Ny,Nx,2);
upx=v_alloc2d(Ny,Nx);
upy=v_alloc2d(Ny,Nx);
vp=v_alloc2d(Ny,Nx);    // can go after set up
vs=v_alloc2d(Ny,Nx);    // can go after set up
dens=v_alloc2d(Ny,Nx);  // can go after set up
/////////////////////////////////////////////////////////////////

ux[0]=-dx;		uz[0]=dx;
ux[1]=0; 		uz[1]=dx;
ux[2]=dx;  	uz[2]=dx;
ux[3]=dx; 		uz[3]=0;
ux[4]=dx;  	uz[4]=-dx;
ux[5]=0; 		uz[5]=-dx;
ux[6]=-dx;  	uz[6]=-dx;
ux[7]=-dx; 	uz[7]=0;

//-----------------------------------------------------------------------

 // Assigning Initial Homogeneous Values
for(i=0; i<Ny; i++)
{
for(j=0; j<Nx; j++)
{
 dens[i][j]=density;
 vp[i][j]=velp;
 vs[i][j]=vels;
 upx[i][j]=0.0;
 upy[i][j]=0.0;
 
 for(m=0; m<2; m++)
 {
   force[i][j][m]=0.0;
   disp[i][j][m]=0.0;
 }

}
}

if(velocity_model==1)
{
   sprintf(string,"%s",input4);
   if(( in= fopen(string,"r")) ==NULL)
   {
      printf("Error opening file %s \n", string);
      MPI_Finalize();
      fclose(in);
      exit(1);
   }
   for(m=0; m<Ny*Nx*(my_size); m++)
   {
     fscanf(in,"%d %d %lf\n",&j,&i,&vp_in);
     //printf("%d %d %lf\n",j,i,vp_in);
     if( my_rank==locate_node(j) )
     {
      jj=j%Nx;
      vp[i][jj]=vp_in;
      vs[i][jj]=vp[i][jj]/sqrt(3.0);
      dens[i][jj]=1700.0+0.2*vp[i][jj];
      if(vp[i][jj]>4000)
      {
      dens[i][jj]=2900;
      }
     }    
    }
    fclose(in);
}

if(flat_surface==1)
{
  for(i=0; i<Ny; i++)
  {
  for(j=0; j<Nx; j++)
  {
     if(i==Ny-1 || i==Ny-2 || i==Ny-3)
     {
       vp[i][j]=-1974.0;
     }
  }
  }
}
  for(j=0; j<Nx; j++)
  {
  for(i=0; i<Ny; i++)
  {
    posn[i][j][0]=j*dx+my_rank*dx*Nx;
    posn[i][j][1]=dx*i;
    
    eqposn[i][j][0]=posn[i][j][0];  eqposn[i][j][1]=posn[i][j][1];

  }
  }
  

}


void setup_top()
{

 int i,j,k,n,p;
 FILE *input;
 int **topo;

 topo=alloc2d_int(Nx*my_size,2);

  if(( input= fopen(input5,"r"))==NULL )
  {
     printf("Error 5001: opening topography file on node %d\n",my_rank);
     MPI_Finalize();
     exit(0);
  }

   // scan in topography file
 for (n=0; n<(Nx*my_size); n++)
 {
    fscanf(input,"%d %d\n",&topo[n][0],&topo[n][1]);    
    //printf("%d %d %d\n",topo[n][0],topo[n][1],my_rank);
 }
 fclose(input);

 for(n=0; n<Nx*my_size; n++)
 {
   if( my_rank==locate_node(topo[n][0]) )
   {
     p=(topo[n][0]%Nx);
     for(k=topo[n][1]; k<Ny; k++)
     {
       vp[k][p]=-1974.0;
     }
   }
 }
 free_array2d_int_other(topo);

}

void setup_layer1()
{

 int i,j,k,n,p;
 FILE *input;
 int **topo;

 topo=alloc2d_int(Nx*my_size,2);

  if(( input= fopen(input5,"r"))==NULL )
  {
     printf("Error 5001: opening topography file on node %d\n",my_rank);
     MPI_Finalize();
     exit(0);
  }

   // scan in topography file
 for (n=0; n<(Nx*my_size); n++)
 {
    fscanf(input,"%d %d\n",&topo[n][0],&topo[n][1]);
 }
 fclose(input);


 for(n=0; n<Nx*my_size; n++)
 {
   if(my_rank==locate_node(topo[n][0]))
   {
     p=(topo[n][0]%Nx);
     for(k=topo[n][1]-1; k>=topo[n][1]-11; k--)
     {
       vp[k][p]=2000;
       vs[k][p]=1200;
       dens[k][p]=2420;
     }
   }
 }
 free_array2d_int_other(topo);

}

void setup_layer2()
{

 int i,j,k,n,p;
 FILE *input;
 int **topo;

 topo=alloc2d_int(Nx*my_size,2);

  if(( input= fopen(input5,"r"))==NULL )
  {
     printf("Error 5001: opening topography file on node %d\n",my_rank);
     MPI_Finalize();
     exit(0);
  }

   // scan in topography file
 for (n=0; n<(Nx*my_size); n++)
 {
    fscanf(input,"%d %d\n",&topo[n][0],&topo[n][1]);
 }
 fclose(input);

 for(n=0; n<Nx*my_size; n++)
 {
   if(my_rank==locate_node(topo[n][0]))
   {
     p=(topo[n][0]%Nx);
     for(k=topo[n][1]-7; k>=topo[n][1]-19; k--)
     {
       vp[k][p]=2500;
       vs[k][p]=1750;
       dens[k][p]=2500;
     }

   }
 }
 free_array2d_int_other(topo);


}
