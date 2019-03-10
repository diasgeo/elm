////////////////////////////////////////////////////////////////////
// initial.h
/////////////////////////////////////////////////////////////////////

void initial_lattice_setup()
{
 int i,j,n,m,p;
 NumSnaps=0;
 
/////////////////////////////////////////////////////////////////
// Setting Up the DP Scheme
/////////////////////////////////////////////////////////////////
r0=v_alloc3d(Ny,Nx,4);
kspring=v_alloc3d(Ny,Nx,4);
cbond=v_alloc3d(Ny,Nx,8);
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

if(flat_surface==1)
{
/*  for(i=Ny-2; i<Ny; i++)
  {
  for(j=0; j<Nx; j++)
  {
    vp[i][j]=-1974.0;
  }
  }*/
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
