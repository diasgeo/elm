
void set_up_geometry_and_neighbours()
{
 int i,j,k,n;
 int in,jn,kn;
 double dist,dxx,dyy,dzz;

 dens_mpi();
 vs_mpi();
 vp_mpi();
 send_posn();

 for(i=0; i<Nx; i++)
 {
 for(j=0; j<Ny; j++)
 {
 for(k=0; k<Nz; k++)
 {
  for(n=0; n<9; n++)
  {
   kspring[i][j][k][n]=0.0;
   cbond[i][j][k][n]=0.0;

   in=IndexX[n]+i;  jn=IndexY[n]+j;   kn=IndexZ[n]+k;
   if(jn>=0 && jn<Ny && kn<Nz)
   {
     dxx=posn[i+1][j][k][0]-posn[in+1][jn][kn][0];
     dyy=posn[i+1][j][k][1]-posn[in+1][jn][kn][1];
     dzz=posn[i+1][j][k][2]-posn[in+1][jn][kn][2];
     dist=sqrt(dxx*dxx+dyy*dyy+dzz*dzz);

     kspring[i][j][k][n]=dx*( (vp[i+1][j][k]+vp[in+1][jn][kn])*(vp[i+1][j][k]+vp[in+1][jn][kn])/4.0
		-(vs[i+1][j][k]+vs[in+1][jn][kn])*(vs[i+1][j][k]+vs[in+1][jn][kn])/4.0 )
		*((dens[i+1][j][k]+dens[in+1][jn][kn])/4.0);

     cbond[i][j][k][n]=(dx*dx*dx*(dens[i+1][j][k]+dens[in+1][jn][kn])/8.0)
		*( -(vp[i+1][j][k]+vp[in+1][jn][kn])*(vp[i+1][j][k]+vp[in+1][jn][kn])/4.0
		 +3.0*(vs[i+1][j][k]+vs[in+1][jn][kn])*(vs[i+1][j][k]+vs[in+1][jn][kn])/4.0  );

     if(vp[i+1][j][k]==-1974.0 || vp[in+1][jn][kn]==-1974.0)
     {
       kspring[i][j][k][n]=0.0;cbond[i][j][k][n]=0.0;
     }
   }
  }
 }
 }
 }

 for(n=0; n<9; n++)
 {
  r0[n]=sqrt(IndexY[n]*IndexY[n]*dx*dx+IndexX[n]*IndexX[n]*dx*dx+IndexZ[n]*IndexZ[n]*dx*dx);
  ux[n]=dx*IndexX[n];
  uy[n]=dx*IndexY[n];
  uz[n]=dx*IndexZ[n];
 }

 if(my_rank==0)
 {
  for(j=0; j<Ny; j++)
  {
  for(k=0; k<Nz; k++)
  {
  for(n=0; n<9; n++)
  {
   if(IndexX[n]==-1)
   {
     kspring[0][j][k][n]=0.0; cbond[0][j][k][n]=0.0; 
   }
  }
  }
  }
 }

 if(my_rank==(my_size-1) )
 {
  for(j=0; j<Ny; j++)
  {
  for(k=0; k<Nz; k++)
  {
  for(n=0; n<9; n++)
  {
   if(IndexX[n]==1)
   {
     kspring[Nx-1][j][k][n]=0.0; cbond[Nx-1][j][k][n]=0.0; 
   }
  }
  }
  }
 }

}

