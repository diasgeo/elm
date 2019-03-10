////////////////////////////////////////////////////////////////////
// initial.h
/////////////////////////////////////////////////////////////////////

void initial_lattice_setup()
{
 int i,j,k,m;
 NumSnaps=0;

/////////////////////////////////////////////////////////////////
// Setting Up the SN Scheme
/////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////

force=v_alloc4d(Ny,Nx,Nz,3);
posn=v_alloc4d(Ny,Nx,Nz,3);
eqposn=v_alloc4d(Ny,Nx,Nz,3);
upx=v_alloc3d(Ny,Nx,Nz);
upy=v_alloc3d(Ny,Nx,Nz);
upz=v_alloc3d(Ny,Nx,Nz);
vp=v_alloc3d(Ny,Nx,Nz);    // can go after set up
dens=v_alloc3d(Ny,Nx,Nz);  // can go after set up
vs=v_alloc3d(Ny,Nx,Nz);

kspring=v_alloc4d(Ny,Nx,Nz,9);
cbond=v_alloc4d(Ny,Nx,Nz,9);

 // Assigning Initial Homogeneous Values
for(i=0; i<Ny; i++)
{
for(j=0; j<Nx; j++)
{
for(k=0; k<Nz; k++)
{
 dens[i][j][k]=density;
 vp[i][j][k]=velp;
 vs[i][j][k]=vels;

   
  if(flat==1)
  {
   if(k==Nz-1 || k==Nz-2 || k==Nz-3)
   {
    vp[i][j][k]=-1974.0;
   }
  }

 upx[i][j][k]=0.0;
 upy[i][j][k]=0.0; 
 upz[i][j][k]=0.0;

 for(m=0; m<3; m++)
 {
   force[i][j][k][m]=0.0;
 }

}
}
}

  for(i=0; i<Ny; i++)
  {
  for(j=0; j<Nx; j++)
  {
  for(k=0; k<Nz; k++)
  {
    posn[i][j][k][0]=j*dx+my_rank*dx*Nx;
    posn[i][j][k][1]=dx*i;
    posn[i][j][k][2]=dx*k;

    eqposn[i][j][k][0]=posn[i][j][k][0];
    eqposn[i][j][k][1]=posn[i][j][k][1];
    eqposn[i][j][k][2]=posn[i][j][k][2];

  }
  }
  }
  

}


void setup_top()
{

 int k,n,p;
 FILE *input;
 int **topo;

 topo=alloc2d_int(Nx*Ny*my_size,3);

  if(( input= fopen(input5,"r"))==NULL )
  {
     printf("Error 5001: opening topography file on node %d\n",my_rank);
     MPI_Finalize();
     exit(0);
  }

   // scan in topography file
 for (n=0; n<(Nx*Ny*my_size); n++)
 {
    fscanf(input,"%d %d %d\n",&topo[n][1],&topo[n][0],&topo[n][2]);
 }
 fclose(input);

 for(n=0; n<Nx*Ny*my_size; n++)
 {
   if(my_rank==locate_node(topo[n][1]))
   {
     p=(topo[n][1]%Nx);
     for(k=topo[n][2]; k<Nz; k++)
     {
        vp[topo[n][0]][p][k]=-1974.0;
     }
   }
 }
 //free_array2d_int_other(topo);

}
