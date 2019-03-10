/////////////////////////////////////////////////////////////////////
// evolve.h
/////////////////////////////////////////////////////////////////////

void evolve()
{

int i,in,j,jn,n,k;
double dxx,dyy,f,dist,a,b;
double ctheta,stheta;

for(i=0; i<Ny; i++)
{
   temp_forcel[i][0]=0;
   temp_forcel[i][1]=0;
   temp_forcer[i][0]=0;
   temp_forcer[i][1]=0;
  
for(j=0; j<Nx; j++)
{
   // Advance the positions by integrating the velocities:
   posn[i][j][0]=posn[i][j][0]+dt*upx[i][j]+(dt2*dt*force[i][j][0])/(dens[i][j]*dx*dx);
   posn[i][j][1]=posn[i][j][1]+dt*upy[i][j]+(dt2*dt*force[i][j][1])/(dens[i][j]*dx*dx);

   // Work out displacements
   disp[i][j][0]=posn[i][j][0]-eqposn[i][j][0];
   disp[i][j][1]=posn[i][j][1]-eqposn[i][j][1];

   //  HALF-ADVANCE VELOCITIES
   upx[i][j]=upx[i][j]+(dt2*force[i][j][0])/(dens[i][j]*dx*dx);
   upy[i][j]=upy[i][j]+(dt2*force[i][j][1])/(dens[i][j]*dx*dx);
   force[i][j][0]=force[i][j][1]=0;
}
}

/////////////////////////////////////////////////////////////////////////////////////
         // CALCULATE NEIGHBOUR FORCES
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
// Source
 a=0.0;
 if(input_source==1 && sdir==3)
 { 
   if(locate_node(source[0][0])==my_rank)
   {
      if( j==(source[0][0]%Nx) && i==source[1][0] )
      {
        a=sscale*psource[run_time];
      }
      if( jn==(source[0][0]%Nx) && in==source[1][0] )
      {
        a=sscale*psource[run_time];
      }
    }
}   
/////////////////////////////////////////////////////////////////////////////////////
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

          force[i][j][0] = force[i][j][0] + f*ctheta ;
          force[i][j][1] = force[i][j][1] + f*stheta ;
          temp_forcel[in][0] = temp_forcel[in][0] - f*ctheta;
          temp_forcel[in][1] = temp_forcel[in][1] - f*stheta;
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
          force[i][j][1] = force[i][j][1] + f*stheta ;
          force[in][jn][0] = force[in][jn][0] - f*ctheta;
          force[in][jn][1] = force[in][jn][1] - f*stheta;
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

          force[i][j][0] = force[i][j][0] + f*ctheta ;
          force[i][j][1] = force[i][j][1] + f*stheta ;
          temp_forcer[in][0] = temp_forcer[in][0] - f*ctheta;
          temp_forcer[in][1] = temp_forcer[in][1] - f*stheta;
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
          force[i][j][1] = force[i][j][1] + f*stheta ;
          force[in][jn][0] = force[in][jn][0] - f*ctheta;
          force[in][jn][1] = force[in][jn][1] - f*stheta;
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
          force[i][j][1] = force[i][j][1] + f*stheta ;
          force[in][jn][0] = force[in][jn][0] - f*ctheta;
          force[in][jn][1] = force[in][jn][1] - f*stheta;
    }
  }//end of in>0 loop

      } // end for n4  
//--------------------------------------------------------------------------
for(n=0; n<8; n++)
{  
   in=Index_NeighY(n)+i;
   jn=Index_NeighX(n)+j; 
   b=0.0;
   
if(in>=0 && in<Ny )
{  
    if(j==0)                                                //j==0
    {
      if(n==0 )
      {
       if(my_rank!=0)
       {
      dxx=-posn[i][j][0]+left_p[in][0];
      dyy=-posn[i][j][1]+left_p[in][1];  b=1.0; 
        }
      }
      else if( n==1 || n==2 || n==3 || n==4 )
      {
      dxx=-posn[i][j][0]+posn[in][jn][0];
      dyy=-posn[i][j][1]+posn[in][jn][1]; b=1.0; 
     }
      else if(n==5 )
      { 
       if(my_rank!=0)
       {
        dxx=-posn[i][j][0]+posn[in][jn][0];
        dyy=-posn[i][j][1]+posn[in][jn][1]; b=1.0; 
        }
      }
      else if(n==6 )
      {
        if(my_rank!=0)
	{
        dxx=-posn[i][j][0]+left_p[in][0];
        dyy=-posn[i][j][1]+left_p[in][1]; b=1.0; 
	  }
      }
      else if(n==7)
      {
        if(my_rank!=0)
	{
        dxx=-posn[i][j][0]+left_p[in][0];
        dyy=-posn[i][j][1]+left_p[in][1]; b=1.0; 
	}
      }
    }                                               //  end j==0
    else if(j==(Nx-1))
    {
      if( n==0 || n==5 || n==6 || n==7 )
      {
      dxx=-posn[i][j][0]+posn[in][jn][0];
      dyy=-posn[i][j][1]+posn[in][jn][1]; b=1.0; 
      }
      else if( n==1 )
      {
       if(my_rank!=(my_size-1) )
       {
      dxx=-posn[i][j][0]+posn[in][jn][0];
      dyy=-posn[i][j][1]+posn[in][jn][1]; b=1.0; 
        }
      }
      else if( n==2 )
      {
       if(my_rank!=(my_size-1) )
       {
      dxx=-posn[i][j][0]+right_p[in][0];
      dyy=-posn[i][j][1]+right_p[in][1]; b=1.0; 
         }
      }
      else if( n==3)
      { 
       if(my_rank!=(my_size-1) )
       {
      dxx=-posn[i][j][0]+right_p[in][0];
      dyy=-posn[i][j][1]+right_p[in][1]; b=1.0; 
         }
      } 
      else if( n==4  )
      {
       if(my_rank!=(my_size-1) )
       {
      dxx=-posn[i][j][0]+right_p[in][0];
      dyy=-posn[i][j][1]+right_p[in][1]; b=1.0; 
       }
      }
    }
    else //if(j>0 &&  j<(Nx-1) )                                             
    {
      dxx=-posn[i][j][0]+posn[in][jn][0];
      dyy=-posn[i][j][1]+posn[in][jn][1];
      b=1.0; 
    }
 
//--------------------------------------------------------
//  vgss
dist=sqrt((dxx*dxx)+(dyy*dyy));
force[i][j][0]=force[i][j][0]+0.5*b*cbond[i][j][n]*(dxx-ux[n])/(dist*dist);            
force[i][j][1]=force[i][j][1]+0.5*b*cbond[i][j][n]*(dyy-uz[n])/(dist*dist);

//--------------------------------------------------------

    } // end in>0
    } // end nn loop
//-----------------------------------------------------------------------------------
} // end posn>0 loop
} // end for j
} // end for i

send_forces();
for(i=0; i<Ny; i++)
{
// update left forces
  if(posn[i][0]>=0)
  {
    force[i][0][0]=force[i][0][0]+left_f[i][0];
    force[i][0][1]=force[i][0][1]+left_f[i][1];
  }
// update right forces
  if(posn[i][Nx-1]>=0)
  {
    force[i][Nx-1][0]=force[i][Nx-1][0]+right_f[i][0];
    force[i][Nx-1][1]=force[i][Nx-1][1]+right_f[i][1];
  }
}


///////////////////////////////////////////////////////////////////////////////
   if(bound==1)
   {
     absorb();
   }
   else if(bound==2)
   {
     absorb_free();
   }
//////////////////////////////////////////////////////////////////////////////////

//  COMPLETE ADVANCEMENT OF VELOCITIES
for(i=0; i<Ny; i++)
{
for(j=0; j<Nx; j++)
{

// source term in here
   if(input_source==1)
   {
    if(sdir==0)
    {
      for(k=0; k<NumSource; k++)
      {
        if(locate_node(source[0][k])==my_rank)
        {
	  if(source[1][k]==i && (source[0][k]%Nx)==j)
	  {
             force[ source[1][k] ][ source[0][k]%Nx ][0]
            =force[ source[1][k] ][ source[0][k]%Nx ][0]+psource[run_time]*sscale;
	  }
        }
      }
    }
    else if(sdir==1)
    {
      for(k=0; k<NumSource; k++)
      {
        if(locate_node(source[0][k])==my_rank)
        {
	   if(source[1][k]==i && (source[0][k]%Nx)==j)
	   {
              force[ source[1][k] ][ source[0][k]%Nx ][1]
             =force[ source[1][k] ][ source[0][k]%Nx ][1]+psource[run_time]*sscale;
	   }
        }
      }
    }
   }
   
   upx[i][j]=upx[i][j]+(dt2*force[i][j][0])/(dens[i][j]*dx*dx);
   upy[i][j]=upy[i][j]+(dt2*force[i][j][1])/(dens[i][j]*dx*dx);
}
}



}


