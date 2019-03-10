
/////////////////////////////////////////////////////////////////////
// evolve.h
/////////////////////////////////////////////////////////////////////

void evolve()
{
int i,in,j,jn,n,nn,k,kn;
double dxx,dyy,dzz,f,bbx,bby,bbz,dist;
double xcomp,ycomp,zcomp,t;
double add_on1=0,add_on2=0,a;

for(i=0; i<Ny; i++)
{
for(j=0; j<Nx; j++)
{
for(k=0; k<Nz; k++)
{
///////////////////////////////////////////////////////////////////////////////////////////

   // Advance the positions by integrating the velocities:
   posn[i][j][k][0]=posn[i][j][k][0]+dt*upx[i][j][k]+(dt2*dt*force[i][j][k][0])/(dens[i][j][k]*dx*dx*dx);
   posn[i][j][k][1]=posn[i][j][k][1]+dt*upy[i][j][k]+(dt2*dt*force[i][j][k][1])/(dens[i][j][k]*dx*dx*dx);
   posn[i][j][k][2]=posn[i][j][k][2]+dt*upz[i][j][k]+(dt2*dt*force[i][j][k][2])/(dens[i][j][k]*dx*dx*dx);

   //  HALF-ADVANCE VELOCITIES
   upx[i][j][k]=upx[i][j][k]+(dt2*force[i][j][k][0])/(dens[i][j][k]*dx*dx*dx);
   upy[i][j][k]=upy[i][j][k]+(dt2*force[i][j][k][1])/(dens[i][j][k]*dx*dx*dx);
   upz[i][j][k]=upz[i][j][k]+(dt2*force[i][j][k][2])/(dens[i][j][k]*dx*dx*dx);
   
   force[i][j][k][0]=force[i][j][k][1]=force[i][j][k][2]=0.0;
   temp_left_f[i][k][0]=temp_left_f[i][k][1]=temp_left_f[i][k][2]=0.0;   
   temp_right_f[i][k][0]=temp_right_f[i][k][1]=temp_right_f[i][k][2]=0.0;

}
}
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
         // CALCULATE NEIGHBOUR FORCES
send_posn();
for(i=0; i<Ny; i++)
{
for(j=0; j<Nx; j++)
{
for(k=0; k<Nz; k++)
{
  for(n=0; n<9; n++)
  {
   in=IndexY(n)+i;
   jn=IndexX(n)+j;
   kn=IndexZ(n)+k;
     
    // if(in==Ny) { in=0;  }
    // if(in==-1) { in=Ny-1; } 
    // if(kn==Nz) { kn=0;  }
    // if(kn==-1) { kn=Nz-1; } 
///////////////////////////////////////////////////////////
a=0.0;  
if(input_source==1 && sdir==3)
{
    for(nn=0; nn<NumSource; nn++)
    {
        if(locate_node(source[0][nn])==my_rank)
        {
	 if(i==source[1][nn] && j==source[0][nn]%Nx && k==source[2][nn])
	 {
             a=sscale*psource[run_time];

	 }
	 if(in==source[1][nn] && jn==source[0][nn]%Nx && kn==source[2][nn])
	 {
             a=sscale*psource[run_time];

	 }
        }
      }
}
//////////////////////////////////////////////////////////////////

   if(in>=0 && in<Ny && kn>=0 && kn<Nz)
   {
    if(j==0)
    {
      if(IndexX(n)==-1)
      {
       if(my_rank==0)
       {
        add_on1=(dx*my_size*Nx);
       }
       else
       {
        add_on1=0;
       }
       dxx=-posn[i][j][k][0]+left_p[in][kn][0]-add_on1;
       dyy=-posn[i][j][k][1]+left_p[in][kn][1];
       dzz=-posn[i][j][k][2]+left_p[in][kn][2];
       dist=sqrt(dxx*dxx+dyy*dyy+dzz*dzz);
	  xcomp = dxx/dist;
          ycomp = dyy/dist;
	  zcomp = dzz/dist;
          f=kspring[i][j][k][n]*(dist-r0[n]+a);
          bbx=iroot2*cbond[i][j][k][n]*(dxx-ux[n])/(dist*dist);
	  bby=iroot2*cbond[i][j][k][n]*(dyy-uy[n])/(dist*dist);
	  bbz=iroot2*cbond[i][j][k][n]*(dzz-uz[n])/(dist*dist); 
	  
	  force[i][j][k][0] = force[i][j][k][0] + f*xcomp + bbx;
          force[i][j][k][1] = force[i][j][k][1] + f*ycomp + bby;
          force[i][j][k][2] = force[i][j][k][2] + f*zcomp + bbz;

	  temp_left_f[in][kn][0]=temp_left_f[in][kn][0] - f*xcomp - bbx;
	  temp_left_f[in][kn][1]=temp_left_f[in][kn][1] - f*ycomp - bby;
	  temp_left_f[in][kn][2]=temp_left_f[in][kn][2] - f*zcomp - bbz;
      }
      else
      {
       dxx=-posn[i][j][k][0]+posn[in][jn][kn][0];
       dyy=-posn[i][j][k][1]+posn[in][jn][kn][1];
       dzz=-posn[i][j][k][2]+posn[in][jn][kn][2];
       dist=sqrt(dxx*dxx+dyy*dyy+dzz*dzz);
	  xcomp = dxx/dist;
          ycomp = dyy/dist;
	  zcomp = dzz/dist;
          f=kspring[i][j][k][n]*(dist-r0[n]+a);
          bbx=iroot2*cbond[i][j][k][n]*(dxx-ux[n])/(dist*dist);
	  bby=iroot2*cbond[i][j][k][n]*(dyy-uy[n])/(dist*dist);
	  bbz=iroot2*cbond[i][j][k][n]*(dzz-uz[n])/(dist*dist); 

	  force[i][j][k][0] = force[i][j][k][0] + f*xcomp+ bbx ;
          force[i][j][k][1] = force[i][j][k][1] + f*ycomp+ bby ;
          force[i][j][k][2] = force[i][j][k][2] + f*zcomp+ bbz ;
	  
	  force[in][jn][kn][0] = force[in][jn][kn][0] - f*xcomp- bbx ;
          force[in][jn][kn][1] = force[in][jn][kn][1] - f*ycomp- bby ;
          force[in][jn][kn][2] = force[in][jn][kn][2] - f*zcomp- bbz ;

      }
    }
    else if(j==Nx-1)
    {
      if(IndexX(n)==1)
      {
        if( my_rank==(my_size-1) )
       {
        add_on2=(dx*my_size*Nx);
       }
       else
       {
        add_on2=0;
       }
       dxx=-posn[i][j][k][0]+right_p[in][kn][0]+add_on2;
       dyy=-posn[i][j][k][1]+right_p[in][kn][1];
       dzz=-posn[i][j][k][2]+right_p[in][kn][2];
       dist=sqrt(dxx*dxx+dyy*dyy+dzz*dzz);
	  xcomp = dxx/dist;
          ycomp = dyy/dist;
	  zcomp = dzz/dist;
          f=kspring[i][j][k][n]*(dist-r0[n]+a);
          bbx=iroot2*cbond[i][j][k][n]*(dxx-ux[n])/(dist*dist);
	  bby=iroot2*cbond[i][j][k][n]*(dyy-uy[n])/(dist*dist);
	  bbz=iroot2*cbond[i][j][k][n]*(dzz-uz[n])/(dist*dist); 


	  force[i][j][k][0] = force[i][j][k][0] + f*xcomp+ bbx ;
          force[i][j][k][1] = force[i][j][k][1] + f*ycomp+ bby ;
          force[i][j][k][2] = force[i][j][k][2] + f*zcomp+ bbz ;

	  temp_right_f[in][kn][0]=temp_right_f[in][kn][0] - f*xcomp- bbx;
	  temp_right_f[in][kn][1]=temp_right_f[in][kn][1] - f*ycomp- bby;
	  temp_right_f[in][kn][2]=temp_right_f[in][kn][2] - f*zcomp- bbz;
      }
      else
      {
       dxx=-posn[i][j][k][0]+posn[in][jn][kn][0];
       dyy=-posn[i][j][k][1]+posn[in][jn][kn][1];
       dzz=-posn[i][j][k][2]+posn[in][jn][kn][2];
       dist=sqrt(dxx*dxx+dyy*dyy+dzz*dzz);
	  xcomp = dxx/dist;
          ycomp = dyy/dist;
	  zcomp = dzz/dist;
          f=kspring[i][j][k][n]*(dist-r0[n]+a);
          bbx=iroot2*cbond[i][j][k][n]*(dxx-ux[n])/(dist*dist);
	  bby=iroot2*cbond[i][j][k][n]*(dyy-uy[n])/(dist*dist);
	  bbz=iroot2*cbond[i][j][k][n]*(dzz-uz[n])/(dist*dist); 


	  force[i][j][k][0] = force[i][j][k][0] + f*xcomp + bbx;
          force[i][j][k][1] = force[i][j][k][1] + f*ycomp + bby;
          force[i][j][k][2] = force[i][j][k][2] + f*zcomp + bbz; 
	  
	  force[in][jn][kn][0] = force[in][jn][kn][0] - f*xcomp - bbx;
          force[in][jn][kn][1] = force[in][jn][kn][1] - f*ycomp - bby;
          force[in][jn][kn][2] = force[in][jn][kn][2] - f*zcomp - bbz;
      }
    }
    else
    {
       dxx=-posn[i][j][k][0]+posn[in][jn][kn][0];
       dyy=-posn[i][j][k][1]+posn[in][jn][kn][1];
       dzz=-posn[i][j][k][2]+posn[in][jn][kn][2];
       dist=sqrt(dxx*dxx+dyy*dyy+dzz*dzz);
	  xcomp = dxx/dist;
          ycomp = dyy/dist;
	  zcomp = dzz/dist;
          f=kspring[i][j][k][n]*(dist-r0[n]+a);
          bbx=iroot2*cbond[i][j][k][n]*(dxx-ux[n])/(dist*dist);
	  bby=iroot2*cbond[i][j][k][n]*(dyy-uy[n])/(dist*dist);
	  bbz=iroot2*cbond[i][j][k][n]*(dzz-uz[n])/(dist*dist); 

	  force[i][j][k][0] = force[i][j][k][0] + f*xcomp + bbx;
          force[i][j][k][1] = force[i][j][k][1] + f*ycomp + bby;
          force[i][j][k][2] = force[i][j][k][2] + f*zcomp + bbz; 
	  
	  force[in][jn][kn][0] = force[in][jn][kn][0] - f*xcomp - bbx;
          force[in][jn][kn][1] = force[in][jn][kn][1] - f*ycomp - bby;
          force[in][jn][kn][2] = force[in][jn][kn][2] - f*zcomp - bbz;
    }

  }//end of in>0 loop
 } // end for n
} // end k loop
} // end for j
} // end for i
//////////////////////////////////////////////////////////////////////////////
send_forces();
for(i=0; i<Ny; i++)
{
for(k=0; k<Nz; k++)
{
  force[i][0][k][0]=force[i][0][k][0]+left_f[i][k][0];
  force[i][0][k][1]=force[i][0][k][1]+left_f[i][k][1];
  force[i][0][k][2]=force[i][0][k][2]+left_f[i][k][2];
 
  force[i][Nx-1][k][0]=force[i][Nx-1][k][0]+right_f[i][k][0];
  force[i][Nx-1][k][1]=force[i][Nx-1][k][1]+right_f[i][k][1];
  force[i][Nx-1][k][2]=force[i][Nx-1][k][2]+right_f[i][k][2];

}
}


//////////////////////////////////////////////////////////////////////////////////
///  COMPLETE ADVANCEMENT OF VELOCITIES
for(i=0; i<Ny; i++)
{
for(j=0; j<Nx; j++)
{
for(k=0; k<Nz; k++)
{
// source term in here
////////////////////////////////////////////////////////////////////////
   if(input_source==1 && sdir!=3)
   {
      for(n=0; n<NumSource; n++)
      {
        if(locate_node(source[0][n])==my_rank)
        {
	 if(source[1][n]==i)
	 {
	 if(source[0][n]%Nx==j)
	 {
	 if(source[2][n]==k)
         {
 force[ source[1][n] ][ source[0][n]%Nx ][ source[2][n] ][sdir]
=force[ source[1][n] ][ source[0][n]%Nx ][ source[2][n] ][sdir]+sscale*psource[run_time];
	 }
	 }
	 }
        }
      }
   }
   
   if(input_source==1 && sdir==4)
   {
      for(n=0; n<NumSource; n++)
      {
        if(locate_node(source[0][n])==my_rank)
        {
	 if(source[1][n]==i)
	 {
	 if(source[0][n]%Nx==j)
	 {
	 if(source[2][n]==k)
         {
 force[ source[1][n] ][ source[0][n]%Nx ][ source[2][n] ][0]
=force[ source[1][n] ][ source[0][n]%Nx ][ source[2][n] ][0]+sscale*psource[run_time];
 force[ source[1][n] ][ source[0][n]%Nx ][ source[2][n] ][1]
=force[ source[1][n] ][ source[0][n]%Nx ][ source[2][n] ][1]+sscale*psource[run_time];
 force[ source[1][n] ][ source[0][n]%Nx ][ source[2][n] ][2]
=force[ source[1][n] ][ source[0][n]%Nx ][ source[2][n] ][2]+sscale*psource[run_time];
	 }
	 }
	 }
        }
      }
   }
////////////////////////////////////////////////////////////////////////
   upx[i][j][k]=upx[i][j][k]+(dt2*force[i][j][k][0])/(dens[i][j][k]*dx*dx*dx);
   upy[i][j][k]=upy[i][j][k]+(dt2*force[i][j][k][1])/(dens[i][j][k]*dx*dx*dx);
   upz[i][j][k]=upz[i][j][k]+(dt2*force[i][j][k][2])/(dens[i][j][k]*dx*dx*dx);
  
}
}
}

 absorb();
  

}
