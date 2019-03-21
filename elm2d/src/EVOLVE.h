
void evolve()
{

int i,in,j,jn,n,k;
double dxx,dyy,f,dist,a,b;
double ctheta,stheta,cbx,cbz;

for(i=0; i<Ny; i++)
{
   temp_forcel[i][0]=0;
   temp_forcel[i][1]=0;
   temp_forcer[i][0]=0;
   temp_forcer[i][1]=0;

for(j=0; j<Nx; j++)
{
   // Advance the positions by integrating the velocities:
   posn[i][j][0]=posn[i][j][0]+dt*upx[i][j]+(0.5*dt*dt*force[i][j][0])/(dens[i][j]*dx*dx);
   posn[i][j][1]=posn[i][j][1]+dt*upy[i][j]+(0.5*dt*dt*force[i][j][1])/(dens[i][j]*dx*dx);

   // Work out displacements
   disp[i][j][0]=posn[i][j][0]-eqposn[i][j][0];
   disp[i][j][1]=posn[i][j][1]-eqposn[i][j][1];

   //  HALF-ADVANCE VELOCITIES
   upx[i][j]=upx[i][j]+(0.5*dt*force[i][j][0])/(dens[i][j]*dx*dx);
   upy[i][j]=upy[i][j]+(0.5*dt*force[i][j][1])/(dens[i][j]*dx*dx);

   force[i][j][0]=force[i][j][1]=0;
}
}

/////////////////////////////////////////////////////////////////////////////////////
//           CALCULATE NEIGHBOUR FORCES

send_posn();
for(i=0; i<Ny; i++)
{
for(j=0; j<Nx; j++)
{
if(vp[i][j]>=0)
{
//-----------------------------------------------------------------------
  for(n=0; n<4; n++)
  {
   in=Index_NeighY(n)+i;
   jn=Index_NeighX(n)+j;
/////////////////////////////////////////////////////////////////////////////////////
 a=0.0; b=1.0; 
 
   if(in>=0 && in<Ny)
   {
    if(j==0)
    {
      if(n==0)
      {
        if(my_rank!=0)
	{
	  dxx=-posn[i][j][0]+left_p[in][0];
          dyy=-posn[i][j][1]+left_p[in][1];
          dist=sqrt((dxx*dxx)+(dyy*dyy));

	  ctheta = dxx/dist;
          stheta = dyy/dist;
          f=kspring[i][j][n]*(dist-r0[i][j][n])+a;
          
          force[i][j][0] = force[i][j][0] + f*ctheta  ;
          force[i][j][1] = force[i][j][1] + f*stheta  ;
          temp_forcel[in][0] = temp_forcel[in][0] - f*ctheta ;
          temp_forcel[in][1] = temp_forcel[in][1] - f*stheta ;
	}
      }
      else
      {
       dxx=-posn[i][j][0]+posn[in][jn][0];
       dyy=-posn[i][j][1]+posn[in][jn][1];
       dist=sqrt((dxx*dxx)+(dyy*dyy));
          ctheta = dxx/dist;
          stheta = dyy/dist;
          f=kspring[i][j][n]*(dist-r0[i][j][n])+a;

          force[i][j][0] = force[i][j][0] + f*ctheta ;
          force[i][j][1] = force[i][j][1] + f*stheta  ;
          force[in][jn][0] = force[in][jn][0] - f*ctheta ;
          force[in][jn][1] = force[in][jn][1] - f*stheta ;
      }
    }
    else if(j==Nx-1)
    {
      if(n==2 || n==3)
      {
        if(my_rank!=(my_size-1) )
        {
           dxx=-posn[i][j][0]+right_p[in][0];
           dyy=-posn[i][j][1]+right_p[in][1];
           dist=sqrt((dxx*dxx)+(dyy*dyy)); 
	  ctheta = dxx/dist;
          stheta = dyy/dist;
          f=kspring[i][j][n]*(dist-r0[i][j][n])+a;

          force[i][j][0] = force[i][j][0] + f*ctheta  ;
          force[i][j][1] = force[i][j][1] + f*stheta  ;
          temp_forcer[in][0] = temp_forcer[in][0] - f*ctheta ;
          temp_forcer[in][1] = temp_forcer[in][1] - f*stheta ;
	}
      }
      else
      {
       dxx=-posn[i][j][0]+posn[in][jn][0];
       dyy=-posn[i][j][1]+posn[in][jn][1];
       dist=sqrt((dxx*dxx)+(dyy*dyy));
          ctheta = dxx/dist;
          stheta = dyy/dist;
          f=kspring[i][j][n]*(dist-r0[i][j][n])+a;

          force[i][j][0] = force[i][j][0] + f*ctheta  ;
          force[i][j][1] = force[i][j][1] + f*stheta ;
          force[in][jn][0] = force[in][jn][0] - f*ctheta ;
          force[in][jn][1] = force[in][jn][1] - f*stheta ;
      }
    }
    else
    {
      dxx=-posn[i][j][0]+posn[in][jn][0];
      dyy=-posn[i][j][1]+posn[in][jn][1];
      dist=sqrt((dxx*dxx)+(dyy*dyy));
          ctheta = dxx/dist;
          stheta = dyy/dist;
          f=kspring[i][j][n]*(dist-r0[i][j][n])+a;

          force[i][j][0] = force[i][j][0] + f*ctheta  ;
          force[i][j][1] = force[i][j][1] + f*stheta  ;

          force[in][jn][0] = force[in][jn][0] - f*ctheta ;
          force[in][jn][1] = force[in][jn][1] - f*stheta;
    }
  }//end of in>0 loop

      } // end for n4
//-----------------------------------------------------------------------------------
} // end posn>0 loop
} // end for j
} // end for i


///----------------------
 if(sdir==4)
 {
  stress_source();
 }
 if(sdir==3)
 {
  vol_source();
 }
send_forces();
for(i=0; i<Ny; i++)
{
// update left forces
    force[i][0][0]=force[i][0][0]+left_f[i][0];
    force[i][0][1]=force[i][0][1]+left_f[i][1];
  
// update right forces
    force[i][Nx-1][0]=force[i][Nx-1][0]+right_f[i][0];
    force[i][Nx-1][1]=force[i][Nx-1][1]+right_f[i][1];
 
}

///////////////////////////////////////////////////////////////////////////////
  absorb();
///////////////////////////////////////////////////////////////////////////////
 if(sdir<2)
 {
 force_source();
 } 

//  COMPLETE ADVANCEMENT OF VELOCITIES
for(i=0; i<Ny; i++)
{
for(j=0; j<Nx; j++)
{
   upx[i][j]=upx[i][j]+(0.5*dt*force[i][j][0])/(dens[i][j]*dx*dx);
   upy[i][j]=upy[i][j]+(0.5*dt*force[i][j][1])/(dens[i][j]*dx*dx);
}
}


}


