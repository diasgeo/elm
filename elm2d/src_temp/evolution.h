
/////////////////////////////////////////////////////////////////////
// evolve.h
void evolve()
{
  int i,in,j,jn,n,nn,k,kn;
  double dxx,dyy,dzz,f,bbx,bby,bbz,dist;
  double xcomp,ycomp,zcomp,t,ax,ay;

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


  for(i=0; j<Ny; j++)
  {
    force[0][j][0]=force[0][j][1]=0.0;
    force[1][j][0]=force[1][j][1]=0.0;
    force[Nx+2][j][0]=force[Nx+2][j][1]=0.0;
    force[Nx+3][j][0]=force[Nx+3][j][1]=0.0;
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

//if(i==Nx-1 && j==10 && my_rank==7)
//printf("%e %e | %e | %e %e | %e %d %d %d %d \n", dxx,dyy,dist-ra[n] , posn[i+1][j][0] , //posn[in+1][jn][0],ax,i,in,n,my_size);

      dist=sqrt((ux[n]*ux[n])+(uy[n]*uy[n]));
      bbx=0.5*cbond[i][j][n]*(dxx-ux[n])/(dist*dist);
      bby=0.5*cbond[i][j][n]*(dyy-uy[n])/(dist*dist);

      force[i+ff][j][0] = force[i+ff][j][0] + f*xcomp + bbx ;
      force[i+ff][j][1] = force[i+ff][j][1] + f*ycomp + bby ;

     //force[in+ff][jn][0] = force[in+ff][jn][0] - f*xcomp ;//- bbx ;
     //force[in+ff][jn][1] = force[in+ff][jn][1] - f*ycomp ;//- bby ;
    }
 }
 }
//////////////////////////////////////////////////////////////////////////////////

 send_force();
 for(j=0; j<Ny; j++)
 {
   i=2;
   force[i][j][0] = force[i-ff][j][0] + force[i][j][0];
   force[i][j][1] = force[i-ff][j][1] + force[i][j][1];

   i=Nx+1;
   force[i][j][0] = force[i+ff][j][0] + force[i][j][0];
   force[i][j][1] = force[i+ff][j][1] + force[i][j][1];
 }

 //plane_waveX(); 
 //plane_waveY(); 
 //plane_waveZ();
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

 absorb();

}
