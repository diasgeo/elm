
void set_up_geometry_and_neighbours()
{
 int i,j,k,n;
 int in,jn,kn;
 double dist,dxx,dyy,dzz;
 double g=1.0;

 dens_mpi();
 vs_mpi();
 vp_mpi();
 send_posn();

 for(i=0; i<Nx; i++)
 {
 for(j=0; j<Ny; j++)
 {
  for(n=0; n<Pl; n++)
  {
   kspring[i][j][n]=0.0;
   cbond[i][j][n]=0.0;
   r0[i][j][n]=0.0;

   /*g=(1.0);
   if(n==0 || n==2)
   { g=(0.5); }

     in=IndexX[n]+i;  jn=IndexY[n]+j;
   //  if( (IndexY[n]+j)==-1) { jn=Ny-1;}
     if( (IndexY[n]+j)==Ny) { jn=0;   }*/

     g=1.0;
     if(n==0 || n==2 || n==4 || n==6)
     { g=0.5; }

     in=IndexX[n]+i;  jn=IndexY[n]+j;
     if( jn == -1) { jn=Ny-1;}
     if( jn == Ny) { jn=0;   }

    // if( in == -1) { in=Nx-1;}
    // if( in == Nx) { in=0;   }

     dxx=posn[i+1][j][0]-posn[in+1][jn][0];
     dyy=posn[i+1][j][1]-posn[in+1][jn][1];

     dist=sqrt(dxx*dxx+dyy*dyy);
     //r0[i][j][n]=dist;

     kspring[i][j][n]=g*( (vp[i+1][j]+vp[in+1][jn])*(vp[i+1][j]+vp[in+1][jn])/4.0
		-(vs[i+1][j]+vs[in+1][jn])*(vs[i+1][j]+vs[in+1][jn])/4.0 )
		*((dens[i+1][j]+dens[in+1][jn])/2.0);

     cbond[i][j][n]=(dx*dx*(dens[i+1][j]+dens[in+1][jn])/4.0)
		*( -(vp[i+1][j]+vp[in+1][jn])*(vp[i+1][j]+vp[in+1][jn])/4.0
		 +3.0*(vs[i+1][j]+vs[in+1][jn])*(vs[i+1][j]+vs[in+1][jn])/4.0  );

  /*   if(vp[i+1][j]==-1974.0 || vp[in+1][jn]==-1974.0)
     {
       kspring[i][j][n]=0.0; cbond[i][j][n]=0.0;
     }*/
 
  }
 }
 }


 for(n=0; n<Pl; n++)
 {
  ux[n]=dx*IndexX[n];
  uy[n]=dx*IndexY[n];
  ra[n]=sqrt( ux[n]*ux[n]+uy[n]*uy[n] );
 }

 if(my_rank==0)
 {
  i=0;
  for(j=0; j<Ny; j++)
  {
    kspring[i][j][0]=0.0; cbond[i][j][0]=0.0;
    kspring[i][j][6]=0.0; cbond[i][j][6]=0.0;
    kspring[i][j][7]=0.0; cbond[i][j][7]=0.0;
  }
 }
 if(my_rank==my_size-1)
 {
  i=Nx-1;
  for(j=0; j<Ny; j++)
  {
    kspring[i][j][2]=0.0; cbond[i][j][2]=0.0;
    kspring[i][j][3]=0.0; cbond[i][j][3]=0.0;
    kspring[i][j][4]=0.0; cbond[i][j][4]=0.0;
  }
 }
 j=0;
 for(i=0; i<Nx; i++)
 {
   kspring[i][j][4]=0.0; cbond[i][j][4]=0.0;
   kspring[i][j][5]=0.0; cbond[i][j][5]=0.0;
   kspring[i][j][6]=0.0; cbond[i][j][6]=0.0;
 }
 j=Ny-1;
 for(i=0; i<Nx; i++)
 {
   kspring[i][j][0]=0.0; cbond[i][j][0]=0.0;
   kspring[i][j][1]=0.0; cbond[i][j][1]=0.0;
   kspring[i][j][2]=0.0; cbond[i][j][2]=0.0;
 }

}








