
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
  for(n=0; n<P; n++)
  {
   kspring[i][j][k][n]=0.0;
   cbond[i][j][k][n]=0.0;

   in=IndexX[n]+i;  jn=IndexY[n]+j;   kn=IndexZ[n]+k;
   if(jn>=0 && jn<Ny && kn>=0 && kn<Nz)
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

 for(n=0; n<P; n++)
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
  for(n=0; n<P; n++)
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
  for(n=0; n<P; n++)
  {
   if(IndexX[n]==1)
   {
     kspring[Nx-1][j][k][n]=0.0; cbond[Nx-1][j][k][n]=0.0; 
   }
  }
  }
  }
 }

//////////////////////////////////////////////////////////////////////

 double lamA,muA, multk,multk1,any_zero=1.0;
 multk=2.0; multk1=1.0;
 double m1,m2 ,m3,m4; 


//////////////////////////////////////////////////////////////////////

 for(i=0; i<Nx; i++)
 {
 for(j=0; j<Ny; j++)
 {
 for(k=0; k<Nz; k++)
 {
    lamA = dens[i+1][j][k]*(vp[i+1][j][k]*vp[i+1][j][k]-2.0*vs[i+1][j][k]*vs[i+1][j][k]);
    muA  = dens[i+1][j][k]*(vs[i+1][j][k]*vs[i+1][j][k]);
    ////////////////////////////////////////////////////////////////////////////////

    any_zero=kspring[i][j][k][0]*kspring[i][j][k][1]*kspring[i][j][k][2]*kspring[i][j][k][3]
            *kspring[i][j][k][4]*kspring[i][j][k][5]*kspring[i][j][k][6]*kspring[i][j][k][7]
            *kspring[i][j][k][8]*kspring[i][j][k][9]*kspring[i][j][k][10]*kspring[i][j][k][11]
            *kspring[i][j][k][12]*kspring[i][j][k][13]*kspring[i][j][k][14]*kspring[i][j][k][15]
            *kspring[i][j][k][16]*kspring[i][j][k][17];

    m1=1.0;
    m2=1.0;
    m3=1.0;
    m4=1.0;

    if( kspring[i][j][k][1]==0.0 )
    kspring[i][j][k][5]=(m1)*multk*kspring[i][j][k][5];

    if( kspring[i][j][k][3]==0.0 )
    kspring[i][j][k][7]=(m1)*multk*kspring[i][j][k][7];

    if( kspring[i][j][k][5]==0.0 )
    kspring[i][j][k][1]=(m1)*multk*kspring[i][j][k][1];

    if( kspring[i][j][k][7]==0.0 )
    kspring[i][j][k][3]=(m1)*multk*kspring[i][j][k][3];

    if( kspring[i][j][k][8]==0.0 )
    kspring[i][j][k][11]=(m1)*multk*kspring[i][j][k][11];

    if( kspring[i][j][k][10]==0.0 )
    kspring[i][j][k][13]=(m1)*multk*kspring[i][j][k][13];

    if( kspring[i][j][k][11]==0.0 )
    kspring[i][j][k][8]=(m1)*multk*kspring[i][j][k][8];

    if( kspring[i][j][k][13]==0.0 )
    kspring[i][j][k][10]=(m1)*multk*kspring[i][j][k][10];

    if( kspring[i][j][k][14]==0.0 )
    kspring[i][j][k][16]=(m1)*multk*kspring[i][j][k][16];

    if( kspring[i][j][k][15]==0.0 )
    kspring[i][j][k][17]=(m1)*multk*kspring[i][j][k][17];

    if( kspring[i][j][k][16]==0.0 )
    kspring[i][j][k][14]=(m1)*multk*kspring[i][j][k][14];

    if( kspring[i][j][k][17]==0.0 )
    kspring[i][j][k][15]=(m1)*multk*kspring[i][j][k][15];
    ////////////////////////////////////////////////////////////////////////////////

    if( kspring[i][j][k][1]!=0.0 && kspring[i][j][k][5]!=0.0 && any_zero==0.0)
    {
      kspring[i][j][k][1]=(m2)*kspring[i][j][k][1];
      kspring[i][j][k][5]=(m2)*kspring[i][j][k][5];
    }
    if( kspring[i][j][k][3]!=0.0 && kspring[i][j][k][7]!=0.0 && any_zero==0.0)
    {
      kspring[i][j][k][3]=(m2)*kspring[i][j][k][3];
      kspring[i][j][k][7]=(m2)*kspring[i][j][k][7];
    }
    if( kspring[i][j][k][8]!=0.0 && kspring[i][j][k][11]!=0.0 && any_zero==0.0)
    {
      kspring[i][j][k][8]=(m2)*kspring[i][j][k][8];
      kspring[i][j][k][11]=(m2)*kspring[i][j][k][11];
    }
    if( kspring[i][j][k][13]!=0.0 && kspring[i][j][k][10]!=0.0 && any_zero==0.0)
    {
      kspring[i][j][k][13]=(m2)*kspring[i][j][k][13];
      kspring[i][j][k][10]=(m2)*kspring[i][j][k][10];
    }
    if( kspring[i][j][k][14]!=0.0 && kspring[i][j][k][16]!=0.0 && any_zero==0.0)
    {
      kspring[i][j][k][14]=(m2)*kspring[i][j][k][14];
      kspring[i][j][k][16]=(m2)*kspring[i][j][k][16];
    }
    if( kspring[i][j][k][17]!=0.0 && kspring[i][j][k][15]!=0.0 && any_zero==0.0)
    {
      kspring[i][j][k][17]=(m2)*kspring[i][j][k][17];
      kspring[i][j][k][15]=(m2)*kspring[i][j][k][15];
    }
    ////////////////////////////////////////////////////////////////////////////////

    if( kspring[i][j][k][0]==0.0 )
    kspring[i][j][k][4]=(m3)*2.0*kspring[i][j][k][4];

    if( kspring[i][j][k][2]==0.0 )
    kspring[i][j][k][6]=(m3)*2.0*kspring[i][j][k][6];

    if( kspring[i][j][k][4]==0.0 )
    kspring[i][j][k][0]=(m3)*2.0*kspring[i][j][k][0];

    if( kspring[i][j][k][6]==0.0 )
    kspring[i][j][k][2]=(m3)*2.0*kspring[i][j][k][2];

    if( kspring[i][j][k][9]==0.0 )
    kspring[i][j][k][12]=(m3)*2.0*kspring[i][j][k][12];

    if( kspring[i][j][k][12]==0.0 )
    kspring[i][j][k][9]=(m3)*2.0*kspring[i][j][k][9];

  ////////////////////////////////////////////////////////////////////////////////

    if( kspring[i][j][k][2]!=0.0 && kspring[i][j][k][6]!=0.0 && any_zero==0.0)
    {
      kspring[i][j][k][2]=(m4)*kspring[i][j][k][2];
      kspring[i][j][k][6]=(m4)*kspring[i][j][k][6];
    }
    if( kspring[i][j][k][0]!=0.0 && kspring[i][j][k][4]!=0.0 && any_zero==0.0)
    {
      kspring[i][j][k][0]=(m4)*kspring[i][j][k][0];
      kspring[i][j][k][4]=(m4)*kspring[i][j][k][4];
    }
    if( kspring[i][j][k][9]!=0.0 && kspring[i][j][k][12]!=0.0 && any_zero==0.0)
    {
      kspring[i][j][k][12]=(m4)*kspring[i][j][k][12];
      kspring[i][j][k][9]= (m4)*kspring[i][j][k][9];
    }

  ////////////////////////////////////////////////////////////////////////////////


    if( any_zero == 0.0 )
    { 
     for(n=0; n<P; n++)
     cbond[i][j][k][n]=0.0;
    }

 }
 }
 }

//////////////////////////////////////////////////////////////////

}

