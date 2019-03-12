
void set_up_geometry_and_neighbours()
{
 int i,j,k,n;
 int in,jn,kn;
 double dist,dxx,dyy,dzz;
 double g=1.0;
 double lamA, muA;
 double da,vpa,vsa;

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

     g=1.0;
     if(n==0 || n==2 || n==4 || n==6)
     { g=0.5; }

     in=IndexX[n]+i;  jn=IndexY[n]+j;
     if( jn == -1) { jn=Ny-1;}
     if( jn == Ny) { jn=0;   }

    //vpa = (vp[i+1][j]+vp[in+1][jn])*0.5;
    //vsa = (vs[i+1][j]+vs[in+1][jn])*0.5;
    //da  = (dens[i+1][j]+dens[in+1][jn])*0.5;

    vpa = 1.0/(1.0/vp[i+1][j] + 1.0/vp[in+1][jn])*2.0;
    vsa = 1.0/(1.0/vs[i+1][j] + 1.0/vs[in+1][jn])*2.0;
    da  =1.0/(1.0/dens[i+1][j] + 1.0/dens[in+1][jn])*2.0;

    kspring[i][j][n]=g*( vpa*vpa - vsa*vsa )*da;
    cbond[i][j][n]=( -vpa*vpa + 3.0*vsa*vsa )*da*dx*dx/2.0;

     if(vp[i+1][j]==-1974.0 || vp[in+1][jn]==-1974.0)
     {
       kspring[i][j][n]=0.0; cbond[i][j][n]=0.0;
     }
 
  }
 }
 }

 for(n=0; n<Pl; n++)
 {
  ux[n]=dx*IndexX[n];
  uy[n]=dx*IndexY[n];
  ra[n]=sqrt( ux[n]*ux[n]+uy[n]*uy[n] );
 }

////////////////////////////////////////////////////////////////////
/*
 for(i=0; i<Nx; i++)
 {
 for(j=0; j<Ny; j++)
 {
   if( kspring[i][j][1]==0.0 )
   {
      kspring[i][j][0]=0.0; cbond[i][j][0]=0.0;
      kspring[i][j][2]=0.0; cbond[i][j][2]=0.0;
   }
   if( kspring[i][j][7]==0.0 )
   {
      kspring[i][j][0]=0.0; cbond[i][j][0]=0.0;
      kspring[i][j][6]=0.0; cbond[i][j][6]=0.0;
   }
   if( kspring[i][j][3]==0.0 )
   {
      kspring[i][j][4]=0.0; cbond[i][j][4]=0.0;
      kspring[i][j][2]=0.0; cbond[i][j][2]=0.0;
   }
   if( kspring[i][j][5]==0.0 )
   {
      kspring[i][j][4]=0.0; cbond[i][j][4]=0.0;
      kspring[i][j][6]=0.0; cbond[i][j][6]=0.0;
   }

 }
 }*/
////////////////////////////////////////////////////////////////////
double mult, mult1, mult2, multk, multk1;

mult  = 0.0;
mult1 = 0.0;
mult2 = 0.0;

multk= 2.0;
multk1=1.0;

////////////////////////////////////////////////////////////////////

 if(my_rank==0)
 {
  i=0;
  for(j=0; j<Ny; j++)
  {
    // lamA=dens[i+1][j]*(vp[i+1][j]*vp[i+1][j]-2.0*vs[i+1][j]*vs[i+1][j]);
    // muA=dens[i+1][j]*(vs[i+1][j]*vs[i+1][j]);

     cbond[i][j][0]=mult2*cbond[i][j][0];
     cbond[i][j][6]=mult2*cbond[i][j][6];
     cbond[i][j][7]=mult2*cbond[i][j][7];

    /* cbond[i][j][2]=mult*cbond[i][j][2];
     cbond[i][j][3]=mult*cbond[i][j][3];
     cbond[i][j][4]=mult*cbond[i][j][4];

     cbond[i][j][5]=mult1*cbond[i][j][5];
     cbond[i][j][1]=mult1*cbond[i][j][1];*/
 ////////////////////////////////////////////////////////////////////// 

    kspring[i][j][0]=0.0;
    kspring[i][j][6]=0.0;
    kspring[i][j][7]=0.0;

  /*  //lamA=muA=1.0;
    kspring[i][j][2]=(lamA/muA)*multk*kspring[i][j][2];
    kspring[i][j][3]=multk*kspring[i][j][3];
    kspring[i][j][4]=(lamA/muA)*multk*kspring[i][j][4];

    kspring[i][j][1]=multk1*kspring[i][j][1];
    kspring[i][j][5]=multk1*kspring[i][j][5];
*/
     if(vp[i+1][j]==-1974.0 )
     {
       for(n=0; n<Pl; n++)
       { kspring[i][j][n]=0.0; cbond[i][j][n]=0.0; }
     }

  }
 }
 if(my_rank==my_size-1)
 {
  i=Nx-1;
  for(j=0; j<Ny; j++)
  {
    lamA=dens[i+1][j]*(vp[i+1][j]*vp[i+1][j]-2.0*vs[i+1][j]*vs[i+1][j]);
    muA=dens[i+1][j]*(vs[i+1][j]*vs[i+1][j]);

    cbond[i][j][2]=mult2*cbond[i][j][2];
    cbond[i][j][3]=mult2*cbond[i][j][3];
    cbond[i][j][4]=mult2*cbond[i][j][4];

   /* cbond[i][j][0]=mult*cbond[i][j][0];
    cbond[i][j][6]=mult*cbond[i][j][6];
    cbond[i][j][7]=mult*cbond[i][j][7];

    cbond[i][j][1]=mult1*cbond[i][j][1];
    cbond[i][j][5]=mult1*cbond[i][j][5];*/
////////////////////////////////////////////////////////////////////// 

    kspring[i][j][2]=0.0;
    kspring[i][j][3]=0.0;
    kspring[i][j][4]=0.0;

    //lamA=muA=1.0;
   /* kspring[i][j][0]=(lamA/muA)*multk*kspring[i][j][0];
    kspring[i][j][7]=multk*kspring[i][j][7];
    kspring[i][j][6]=(lamA/muA)*multk*kspring[i][j][6];

    kspring[i][j][1]=multk1*kspring[i][j][1];
    kspring[i][j][5]=multk1*kspring[i][j][5];
*/
     if(vp[i+1][j]==-1974.0 )
     {
       for(n=0; n<Pl; n++)
       { kspring[i][j][n]=0.0; cbond[i][j][n]=0.0; }
     }
  }
 }

 j=0;
 for(i=0; i<Nx; i++)
 { 
    lamA=dens[i+1][j]*(vp[i+1][j]*vp[i+1][j]-2.0*vs[i+1][j]*vs[i+1][j]);
    muA=dens[i+1][j]*(vs[i+1][j]*vs[i+1][j]);

    cbond[i][j][4]=mult2*cbond[i][j][4];
    cbond[i][j][5]=mult2*cbond[i][j][5];
    cbond[i][j][6]=mult2*cbond[i][j][6];

  /*  cbond[i][j][0]=mult*cbond[i][j][0];
    cbond[i][j][1]=mult*cbond[i][j][1];
    cbond[i][j][2]=mult*cbond[i][j][2];

    cbond[i][j][3]=mult1*cbond[i][j][3];
    cbond[i][j][7]=mult1*cbond[i][j][7];*/
////////////////////////////////////////////////////////////////////// 

    //lamA=muA=1.0;
    kspring[i][j][4]=0.0;
    kspring[i][j][5]=0.0;
    kspring[i][j][6]=0.0;

   /* kspring[i][j][0]=(lamA/muA)*multk*kspring[i][j][0];
    kspring[i][j][1]=multk*kspring[i][j][1];
    kspring[i][j][2]=(lamA/muA)*multk*kspring[i][j][2];

    kspring[i][j][3]=multk1*kspring[i][j][3];
    kspring[i][j][7]=multk1*kspring[i][j][7];
*/
     if(vp[i+1][j]==-1974.0 )
     {
       for(n=0; n<Pl; n++)
       { kspring[i][j][n]=0.0; cbond[i][j][n]=0.0; }
     }
 }

 j=Ny-1;
 for(i=0; i<Nx; i++)
 { 
    lamA=dens[i+1][j]*(vp[i+1][j]*vp[i+1][j]-2.0*vs[i+1][j]*vs[i+1][j]);
    muA=dens[i+1][j]*(vs[i+1][j]*vs[i+1][j]);

    cbond[i][j][0]=mult2*cbond[i][j][0];
    cbond[i][j][1]=mult2*cbond[i][j][1];
    cbond[i][j][2]=mult2*cbond[i][j][2];

   /* cbond[i][j][4]=mult*cbond[i][j][4];
    cbond[i][j][5]=mult*cbond[i][j][5];
    cbond[i][j][6]=mult*cbond[i][j][6];

    cbond[i][j][7]=mult1*cbond[i][j][7];
    cbond[i][j][3]=mult1*cbond[i][j][3];*/

////////////////////////////////////////////////////////////////////// 

    kspring[i][j][0]=0.0; 
    kspring[i][j][1]=0.0; 
    kspring[i][j][2]=0.0; 

    //lamA=muA=1.0;
   /* kspring[i][j][4]=(lamA/muA)*multk*kspring[i][j][4];
    kspring[i][j][5]=multk*kspring[i][j][5];
    kspring[i][j][6]=(lamA/muA)*multk*kspring[i][j][6];

    kspring[i][j][3]=multk1*kspring[i][j][3];
    kspring[i][j][7]=multk1*kspring[i][j][7]; 
 */
     if(vp[i+1][j]==-1974.0 )
     {
       for(n=0; n<Pl; n++)
       { kspring[i][j][n]=0.0; cbond[i][j][n]=0.0; }
     }

////////////////////////////////////////////////////////////////////// 

 }
////////////////////////////////////////////////////////////////////// 

 double any_zero=1.0;
 multk=2.0;  multk1=1.0;
 double count;

 for(i=0; i<Nx; i++)
 {
 for(j=0; j<Ny; j++)
 {
    lamA=dens[i+1][j]*(vp[i+1][j]*vp[i+1][j]-2.0*vs[i+1][j]*vs[i+1][j]);
    muA=dens[i+1][j]*(vs[i+1][j]*vs[i+1][j]);

    /*count=1;
    for(n=0; n<Pl; n++)
    {
       if( kspring[i][j][n]==0.0 )
       count=count+1;
    }
    multk=Pl/count;*/

    if( kspring[i][j][0]==0.0 )
    kspring[i][j][4]=(lamA/muA)*multk*kspring[i][j][4];

    if( kspring[i][j][2]==0.0 )
    kspring[i][j][6]=(lamA/muA)*multk*kspring[i][j][6];

    if( kspring[i][j][4]==0.0 )
    kspring[i][j][0]=(lamA/muA)*multk*kspring[i][j][0];

    if( kspring[i][j][6]==0.0 )
    kspring[i][j][2]=(lamA/muA)*multk*kspring[i][j][2];

    if( kspring[i][j][1]==0.0 )
    kspring[i][j][5]=multk*kspring[i][j][5];

    if( kspring[i][j][3]==0.0 )
    kspring[i][j][7]=multk*kspring[i][j][7];

    if( kspring[i][j][5]==0.0 )
    kspring[i][j][1]=multk*kspring[i][j][1];

    if( kspring[i][j][7]==0.0 )
    kspring[i][j][3]=multk*kspring[i][j][3];

 /*   any_zero=kspring[i][j][0]*kspring[i][j][2]*kspring[i][j][4]*kspring[i][j][6];
    if( any_zero==0.0 )
    {
      kspring[i][j][0]=(lamA/muA)*multk*kspring[i][j][0];
      kspring[i][j][2]=(lamA/muA)*multk*kspring[i][j][2];
      kspring[i][j][4]=(lamA/muA)*multk*kspring[i][j][4];
      kspring[i][j][6]=(lamA/muA)*multk*kspring[i][j][6];
    }

    any_zero=kspring[i][j][1]*kspring[i][j][3]*kspring[i][j][5]*kspring[i][j][7];
    if( any_zero==0.0 )
    {
      kspring[i][j][1]=multk*kspring[i][j][1];
      kspring[i][j][3]=multk*kspring[i][j][3];
      kspring[i][j][5]=multk*kspring[i][j][5];
      kspring[i][j][7]=multk*kspring[i][j][7];
    }*/

    any_zero=kspring[i][j][0]*kspring[i][j][1]*kspring[i][j][2]*kspring[i][j][3]
            *kspring[i][j][4]*kspring[i][j][5]*kspring[i][j][6]*kspring[i][j][7];

    if( any_zero == 0.0 )
    {
     cbond[i][j][0]=0.0;
     cbond[i][j][1]=0.0;
     cbond[i][j][2]=0.0;
     cbond[i][j][4]=0.0;
     cbond[i][j][5]=0.0;
     cbond[i][j][6]=0.0;
     cbond[i][j][7]=0.0;
     cbond[i][j][3]=0.0;
    }

 }
 }
////////////////////////////////////////////////////////////////////// 



}

