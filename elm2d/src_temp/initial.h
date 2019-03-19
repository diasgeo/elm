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


///----------------------------------------------
/* for(i=0; i<Nx+2; i++)
 {
 for(j=0; j<101; j++)
 {
   dens[i][j]=2500.0;
   vp[i][j]=3500.0;
   vs[i][j]=3500.0/sqrt(3.0);
 }
 }
 for(i=0; i<Nx+2; i++)
 {
 for(j=100; j<201; j++)
 {
   dens[i][j]=2500.0;
   vp[i][j]=3000.0;
   vs[i][j]=3000.0/sqrt(3.0);
 }
 }
 for(i=0; i<Nx+2; i++)
 {
 for(j=200; j<Ny; j++)
 {
   dens[i][j]=2500.0;
   vp[i][j]=2500.0;
   vs[i][j]=2500.0/sqrt(3.0);
 }
 }
 for(i=250; i<Nx*my_size; i++)
 {
 for(j=0; j<Ny; j++)
 {
   if(locate_node(i)==my_rank )
   { 
     ii=i%Nx;
     dens[ii+1][j]=2200.0;
     vp[ii+1][j]=3250.0;
     vs[ii+1][j]=3250.0/sqrt(3.0);
  }
 }
 }*/

/*
 for(i=200; i<Nx*my_size; i++)
 {
 for(j=0; j<Ny; j++)
 {
   if(locate_node(i)==my_rank )
   { 
     ii=i%Nx;
     dens[ii+1][j]=2500.0;
     vp[ii+1][j]=3000.0;
     vs[ii+1][j]=3000.0/sqrt(3.0);
  }
 }
 }*/
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


