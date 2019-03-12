
/////////////////////////////////////////////////////////////////////
// evolve.h
void evolve()
{
  int i,in,j,jn,n,nn,k,kn;
  double dxx,dyy,dzz,f,bbx,bby,bbz,dist;
  double xcomp,ycomp,zcomp,t,ax,ay;
  int in1,jn1;
  double dxx1,dyy1,dist1,costheta,cons;

  for(i=0; i<Nx; i++)
  {
  for(j=0; j<Ny; j++)
  {
     // Advance the positions by integrating the velocities:
     posn[i+1][j][0] = posn[i+1][j][0]+dt*up[i][j][0]+(dt2*dt*force[i+ff][j][0])/(dens[i+1][j]*dx*dx);
     posn[i+1][j][1] = posn[i+1][j][1]+dt*up[i][j][1]+(dt2*dt*force[i+ff][j][1])/(dens[i+1][j]*dx*dx);

      //  HALF-ADVANCE VELOCITIES
     up[i][j][0]=up[i][j][0]+(dt2*force[i + ff][j][0])/(dens[i+1][j]*dx*dx);
     up[i][j][1]=up[i][j][1]+(dt2*force[i + ff][j][1])/(dens[i+1][j]*dx*dx);

     force[i+ff][j][0]=force[i+ff][j][1]=0.0;
  }
  }


//////////////////////////////////////////////////////////////////////////////////
// CALCULATE NEIGHBOUR FORCES
 send_posn();

 for(i=0; i<Nx; i++)
 {
 for(j=0; j<Ny; j++)
 {
   for(n=0; n<Pl; n++)
   {
     in=IndexX[n]+i; jn=IndexY[n]+j;
     in1=IndexX[(n+1)%Pl]+i; jn1=IndexY[(n+1)%Pl]+j;

     ax=0.0; ay=0.0;
     if( jn==-1 ) { jn=Ny-1; ay =-(Ny)*dx; }
     if( jn==Ny ) { jn=0;    ay = (Ny)*dx; }

     if( in==-1 && my_rank==0)            { ax =-Nx*my_size*dx; }
     if( in==Nx && my_rank==(my_size-1) ) { ax = Nx*my_size*dx; }

     dxx=-posn[i+1][j][0] + posn[in+1][jn][0] + ax;
     dyy=-posn[i+1][j][1] + posn[in+1][jn][1] + ay;
     dist=sqrt(dxx*dxx+dyy*dyy);
     xcomp = dxx/dist;
     ycomp = dyy/dist;
     f=kspring[i][j][n]*(dist-ra[n]);

     dist=sqrt((ux[n]*ux[n])+(uy[n]*uy[n]));
     bbx=0.5*cbond[i][j][n]*(dxx-ux[n])/(dist*dist);
     bby=0.5*cbond[i][j][n]*(dyy-uy[n])/(dist*dist);

     //if(j==Ny-1 )
     //bby=0.5*0.5*cbond[i][j][n]*(dyy-uy[n])/(dist*dist);

     force[i+ff][j][0] = force[i+ff][j][0] + f*xcomp + bbx ;
     force[i+ff][j][1] = force[i+ff][j][1] + f*ycomp + bby ;

    }
 }
 }
//////////////////////////////////////////////////////////////////////////////////

 if(input_source==1 && sdir<2)
 {
   force_source();
 }
 if(input_source==1 && sdir==2)
 {
   vol_source();
 }
/* if(input_source==1 && sdir==4)
 {
   moment_source();
 }
*/

 //////////////////////////////////////////////////////////////////////////////////
 //  COMPLETE ADVANCEMENT OF VELOCITIES
 for(i=0; i<Nx; i++)
 {
 for(j=0; j<Ny; j++)
 {
    up[i][j][0]=up[i][j][0]+(dt2*force[i+ff][j][0])/(dens[i+1][j]*dx*dx);
    up[i][j][1]=up[i][j][1]+(dt2*force[i+ff][j][1])/(dens[i+1][j]*dx*dx);
 }
 }

//////////////////////////////////////////////////////////////////////////////////
  j=0;
  for(i=0; i<Nx; i++)
  {
     // Advance the positions by integrating the velocities:
     posn[i+1][j][0] = eqposn[i][j][0];
     posn[i+1][j][1] = eqposn[i][j][1];
     up[i][j][0]=up[i][j][1]=0.0;
     force[i+ff][j][0]=force[i+ff][j][1]=0.0;
  }
 /* j=Ny-1;
  for(i=0; i<Nx; i++)
  {
     // Advance the positions by integrating the velocities:
     posn[i+1][j][0] = eqposn[i][j][0];
     posn[i+1][j][1] = eqposn[i][j][1];
     up[i][j][0]=up[i][j][1]=0.0;
     force[i+ff][j][0]=force[i+ff][j][1]=0.0;
  }*/
  if(my_rank == 0)
  {
  i=0;
  for(j=0; j<Ny; j++)
  {
     // Advance the positions by integrating the velocities:
     posn[i+1][j][0] = eqposn[i][j][0];
     posn[i+1][j][1] = eqposn[i][j][1];
     up[i][j][0]=up[i][j][1]=0.0;
     force[i+ff][j][0]=force[i+ff][j][1]=0.0;
  }
  }
  if(my_rank == my_size-1)
  {
  i=Nx-1;
  for(j=0; j<Ny; j++)
  {
     // Advance the positions by integrating the velocities:
     posn[i+1][j][0] = eqposn[i][j][0];
     posn[i+1][j][1] = eqposn[i][j][1];
     up[i][j][0]=up[i][j][1]=0.0;
     force[i+ff][j][0]=force[i+ff][j][1]=0.0;
  }
  }
 //////////////////////////////////////////////////////////////////////////////////


 //absorb();

}
