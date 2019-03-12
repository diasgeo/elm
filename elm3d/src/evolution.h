
/////////////////////////////////////////////////////////////////////
// evolve.h
void evolve()
{
  int i,in,j,jn,n,nn,k,kn;
  double dxx,dyy,dzz,f,bbx,bby,bbz,dist;
  double xcomp,ycomp,zcomp,t;

  for(i=0; i<Nx; i++)
  {
  for(j=0; j<Ny; j++)
  {
  for(k=0; k<Nz; k++)
  {
     // Advance the positions by integrating the velocities:
     posn[i+1][j][k][0] = posn[i+1][j][k][0]+dt*up[i][j][k][0]+(dt2*dt*force[i+ff][j][k][0])/(dens[i+1][j][k]*dx*dx*dx);
     posn[i+1][j][k][1] = posn[i+1][j][k][1]+dt*up[i][j][k][1]+(dt2*dt*force[i+ff][j][k][1])/(dens[i+1][j][k]*dx*dx*dx);
     posn[i+1][j][k][2] = posn[i+1][j][k][2]+dt*up[i][j][k][2]+(dt2*dt*force[i+ff][j][k][2])/(dens[i+1][j][k]*dx*dx*dx);

      //  HALF-ADVANCE VELOCITIES
     up[i][j][k][0]=up[i][j][k][0]+(dt2*force[i + ff][j][k][0])/(dens[i+1][j][k]*dx*dx*dx);
     up[i][j][k][1]=up[i][j][k][1]+(dt2*force[i + ff][j][k][1])/(dens[i+1][j][k]*dx*dx*dx);
     up[i][j][k][2]=up[i][j][k][2]+(dt2*force[i + ff][j][k][2])/(dens[i+1][j][k]*dx*dx*dx);

     force[i+ff][j][k][0]=force[i+ff][j][k][1]=force[i+ff][j][k][2]=0.0;
  }
  }
  }

  for(j=0; j<Ny; j++)
  {
  for(k=0; k<Nz; k++)
  {
    force[0][j][k][0]=force[0][j][k][1]=force[0][j][k][2]=0.0;
    force[1][j][k][0]=force[1][j][k][1]=force[1][j][k][2]=0.0;
    force[Nx+2][j][k][0]=force[Nx+2][j][k][1]=force[Nx+2][j][k][2]=0.0;
    force[Nx+3][j][k][0]=force[Nx+3][j][k][1]=force[Nx+3][j][k][2]=0.0;
  }
  }

//////////////////////////////////////////////////////////////////////////////////
// CALCULATE NEIGHBOUR FORCES
 send_posn();

 for(i=0; i<Nx; i++)
 {
 for(j=1; j<Ny-1; j++)
 {
 for(k=0; k<Nz-1; k++)
 {
   for(n=0; n<9; n++)
   {
     in=IndexX[n]+i; jn=IndexY[n]+j; kn=IndexZ[n]+k;
            dxx=-posn[i + 1][j][k][0] + posn[in + 1][jn][kn][0];
	    dyy=-posn[i + 1][j][k][1] + posn[in + 1][jn][kn][1];
	    dzz=-posn[i + 1][j][k][2] + posn[in + 1][jn][kn][2];
	    dist=sqrt(dxx*dxx+dyy*dyy+dzz*dzz);
	    xcomp = dxx/dist;
	    ycomp = dyy/dist;
	    zcomp = dzz/dist;
	    f=kspring[i][j][k][n]*(dist-r0[n]);
            dist=sqrt((ux[n]*ux[n])+(uy[n]*uy[n])+(uz[n]*uz[n]));
	    bbx=iroot2*cbond[i][j][k][n]*(dxx-ux[n])/(dist*dist);
	    bby=iroot2*cbond[i][j][k][n]*(dyy-uy[n])/(dist*dist);
	    bbz=iroot2*cbond[i][j][k][n]*(dzz-uz[n])/(dist*dist); 

	   force[i+ff][j][k][0] = force[i+ff][j][k][0] + f*xcomp + bbx ;
	   force[i+ff][j][k][1] = force[i+ff][j][k][1] + f*ycomp + bby ;
	   force[i+ff][j][k][2] = force[i+ff][j][k][2] + f*zcomp + bbz ;

	   force[in+ff][jn][kn][0] = force[in+ff][jn][kn][0] - f*xcomp - bbx ;
	   force[in+ff][jn][kn][1] = force[in+ff][jn][kn][1] - f*ycomp - bby ;
	   force[in+ff][jn][kn][2] = force[in+ff][jn][kn][2] - f*zcomp - bbz ;
    }
 }
 }
 }
 j=0;
 for(i=0; i<Nx; i++)
 {
 for(k=0; k<Nz-1; k++)
 {
   for(n=0; n<4; n++)
   {
     in=IndexX[n]+i; jn=IndexY[n]+j; kn=IndexZ[n]+k;
            dxx=-posn[i + 1][j][k][0] + posn[in + 1][jn][kn][0];
	    dyy=-posn[i + 1][j][k][1] + posn[in + 1][jn][kn][1];
	    dzz=-posn[i + 1][j][k][2] + posn[in + 1][jn][kn][2];
	    dist=sqrt(dxx*dxx+dyy*dyy+dzz*dzz);
	    xcomp = dxx/dist;
	    ycomp = dyy/dist;
	    zcomp = dzz/dist;
	    f=kspring[i][j][k][n]*(dist-r0[n]);
            dist=sqrt((ux[n]*ux[n])+(uy[n]*uy[n])+(uz[n]*uz[n]));
	    bbx=iroot2*cbond[i][j][k][n]*(dxx-ux[n])/(dist*dist);
	    bby=iroot2*cbond[i][j][k][n]*(dyy-uy[n])/(dist*dist);
	    bbz=iroot2*cbond[i][j][k][n]*(dzz-uz[n])/(dist*dist); 

	   force[i+ff][j][k][0] = force[i+ff][j][k][0] + f*xcomp + bbx ;
	   force[i+ff][j][k][1] = force[i+ff][j][k][1] + f*ycomp + bby ;
	   force[i+ff][j][k][2] = force[i+ff][j][k][2] + f*zcomp + bbz ;

	   force[in+ff][jn][kn][0] = force[in+ff][jn][kn][0] - f*xcomp - bbx ;
	   force[in+ff][jn][kn][1] = force[in+ff][jn][kn][1] - f*ycomp - bby ;
	   force[in+ff][jn][kn][2] = force[in+ff][jn][kn][2] - f*zcomp - bbz ;
    }
    for(n=5; n<9; n++)
    {
     in=IndexX[n]+i; jn=IndexY[n]+j; kn=IndexZ[n]+k;
            dxx=-posn[i + 1][j][k][0] + posn[in + 1][jn][kn][0];
	    dyy=-posn[i + 1][j][k][1] + posn[in + 1][jn][kn][1];
	    dzz=-posn[i + 1][j][k][2] + posn[in + 1][jn][kn][2];
	    dist=sqrt(dxx*dxx+dyy*dyy+dzz*dzz);
	    xcomp = dxx/dist;
	    ycomp = dyy/dist;
	    zcomp = dzz/dist;
	    f=kspring[i][j][k][n]*(dist-r0[n]);
            dist=sqrt((ux[n]*ux[n])+(uy[n]*uy[n])+(uz[n]*uz[n]));
	    bbx=iroot2*cbond[i][j][k][n]*(dxx-ux[n])/(dist*dist);
	    bby=iroot2*cbond[i][j][k][n]*(dyy-uy[n])/(dist*dist);
	    bbz=iroot2*cbond[i][j][k][n]*(dzz-uz[n])/(dist*dist); 

	   force[i+ff][j][k][0] = force[i+ff][j][k][0] + f*xcomp + bbx ;
	   force[i+ff][j][k][1] = force[i+ff][j][k][1] + f*ycomp + bby ;
	   force[i+ff][j][k][2] = force[i+ff][j][k][2] + f*zcomp + bbz ;

	   force[in+ff][jn][kn][0] = force[in+ff][jn][kn][0] - f*xcomp - bbx ;
	   force[in+ff][jn][kn][1] = force[in+ff][jn][kn][1] - f*ycomp - bby ;
	   force[in+ff][jn][kn][2] = force[in+ff][jn][kn][2] - f*zcomp - bbz ;
    }
 }
 }
j=Ny-1;
 for(i=0; i<Nx; i++)
 {
 for(k=0; k<Nz-1; k++)
 {
   for(n=3; n<6; n++)
   {
     in=IndexX[n]+i; jn=IndexY[n]+j; kn=IndexZ[n]+k;
            dxx=-posn[i + 1][j][k][0] + posn[in + 1][jn][kn][0];
	    dyy=-posn[i + 1][j][k][1] + posn[in + 1][jn][kn][1];
	    dzz=-posn[i + 1][j][k][2] + posn[in + 1][jn][kn][2];
	    dist=sqrt(dxx*dxx+dyy*dyy+dzz*dzz);
	    xcomp = dxx/dist;
	    ycomp = dyy/dist;
	    zcomp = dzz/dist;
	    f=kspring[i][j][k][n]*(dist-r0[n]);
            dist=sqrt((ux[n]*ux[n])+(uy[n]*uy[n])+(uz[n]*uz[n]));
	    bbx=iroot2*cbond[i][j][k][n]*(dxx-ux[n])/(dist*dist);
	    bby=iroot2*cbond[i][j][k][n]*(dyy-uy[n])/(dist*dist);
	    bbz=iroot2*cbond[i][j][k][n]*(dzz-uz[n])/(dist*dist); 

	   force[i+ff][j][k][0] = force[i+ff][j][k][0] + f*xcomp + bbx ;
	   force[i+ff][j][k][1] = force[i+ff][j][k][1] + f*ycomp + bby ;
	   force[i+ff][j][k][2] = force[i+ff][j][k][2] + f*zcomp + bbz ;

	   force[in+ff][jn][kn][0] = force[in+ff][jn][kn][0] - f*xcomp - bbx ;
	   force[in+ff][jn][kn][1] = force[in+ff][jn][kn][1] - f*ycomp - bby ;
	   force[in+ff][jn][kn][2] = force[in+ff][jn][kn][2] - f*zcomp - bbz ;
    }
    for(n=7; n<9; n++)
    {
     in=IndexX[n]+i; jn=IndexY[n]+j; kn=IndexZ[n]+k;
            dxx=-posn[i + 1][j][k][0] + posn[in + 1][jn][kn][0];
	    dyy=-posn[i + 1][j][k][1] + posn[in + 1][jn][kn][1];
	    dzz=-posn[i + 1][j][k][2] + posn[in + 1][jn][kn][2];
	    dist=sqrt(dxx*dxx+dyy*dyy+dzz*dzz);
	    xcomp = dxx/dist;
	    ycomp = dyy/dist;
	    zcomp = dzz/dist;
	    f=kspring[i][j][k][n]*(dist-r0[n]);
            dist=sqrt((ux[n]*ux[n])+(uy[n]*uy[n])+(uz[n]*uz[n]));
	    bbx=iroot2*cbond[i][j][k][n]*(dxx-ux[n])/(dist*dist);
	    bby=iroot2*cbond[i][j][k][n]*(dyy-uy[n])/(dist*dist);
	    bbz=iroot2*cbond[i][j][k][n]*(dzz-uz[n])/(dist*dist); 

	   force[i+ff][j][k][0] = force[i+ff][j][k][0] + f*xcomp + bbx ;
	   force[i+ff][j][k][1] = force[i+ff][j][k][1] + f*ycomp + bby ;
	   force[i+ff][j][k][2] = force[i+ff][j][k][2] + f*zcomp + bbz ;

	   force[in+ff][jn][kn][0] = force[in+ff][jn][kn][0] - f*xcomp - bbx ;
	   force[in+ff][jn][kn][1] = force[in+ff][jn][kn][1] - f*ycomp - bby ;
	   force[in+ff][jn][kn][2] = force[in+ff][jn][kn][2] - f*zcomp - bbz ;
    }
 }
 }
 k=Nz-1; 
 for(i=0; i<Nx; i++)
 {
 for(j=1; j<Ny-1; j++)
 {
   for(n=0; n<4; n++)
   {
     in=IndexX[n]+i; jn=IndexY[n]+j; kn=IndexZ[n]+k;
            dxx=-posn[i + 1][j][k][0] + posn[in + 1][jn][kn][0];
	    dyy=-posn[i + 1][j][k][1] + posn[in + 1][jn][kn][1];
	    dzz=-posn[i + 1][j][k][2] + posn[in + 1][jn][kn][2];
	    dist=sqrt(dxx*dxx+dyy*dyy+dzz*dzz);
	    xcomp = dxx/dist;
	    ycomp = dyy/dist;
	    zcomp = dzz/dist;
	    f=kspring[i][j][k][n]*(dist-r0[n]);
            dist=sqrt((ux[n]*ux[n])+(uy[n]*uy[n])+(uz[n]*uz[n]));
	    bbx=iroot2*cbond[i][j][k][n]*(dxx-ux[n])/(dist*dist);
	    bby=iroot2*cbond[i][j][k][n]*(dyy-uy[n])/(dist*dist);
	    bbz=iroot2*cbond[i][j][k][n]*(dzz-uz[n])/(dist*dist); 

	   force[i+ff][j][k][0] = force[i+ff][j][k][0] + f*xcomp + bbx ;
	   force[i+ff][j][k][1] = force[i+ff][j][k][1] + f*ycomp + bby ;
	   force[i+ff][j][k][2] = force[i+ff][j][k][2] + f*zcomp + bbz ;

	   force[in+ff][jn][kn][0] = force[in+ff][jn][kn][0] - f*xcomp - bbx ;
	   force[in+ff][jn][kn][1] = force[in+ff][jn][kn][1] - f*ycomp - bby ;
	   force[in+ff][jn][kn][2] = force[in+ff][jn][kn][2] - f*zcomp - bbz ;
    }
 }
 }
//////////////////////////////////////////////////////////////////////////////////

 send_force();
 for(j=0; j<Ny; j++)
 {
 for(k=0; k<Nz; k++)
 {
   i=2;
   force[i][j][k][0] = force[i-ff][j][k][0] + force[i][j][k][0];
   force[i][j][k][1] = force[i-ff][j][k][1] + force[i][j][k][1];
   force[i][j][k][2] = force[i-ff][j][k][2] + force[i][j][k][2];

   i=Nx+1;
   force[i][j][k][0] = force[i+ff][j][k][0] + force[i][j][k][0];
   force[i][j][k][1] = force[i+ff][j][k][1] + force[i][j][k][1];
   force[i][j][k][2] = force[i+ff][j][k][2] + force[i][j][k][2];

 }
 }

 //plane_waveX(); 
 //plane_waveY(); 
 //plane_waveZ();
 if(input_source==1 && sdir<3)
 {
   force_source();
 }
 if(input_source==1 && sdir==3)
 {
   vol_source();
 }
 if(input_source==1 && sdir==4)
 {
   moment_source();
 }

 //////////////////////////////////////////////////////////////////////////////////
 //  COMPLETE ADVANCEMENT OF VELOCITIES
 for(i=0; i<Nx; i++)
 {
 for(j=0; j<Ny; j++)
 {
 for(k=0; k<Nz; k++)
 {
    up[i][j][k][0]=up[i][j][k][0]+(dt2*force[i+ff][j][k][0])/(dens[i+1][j][k]*dx*dx*dx);
    up[i][j][k][1]=up[i][j][k][1]+(dt2*force[i+ff][j][k][1])/(dens[i+1][j][k]*dx*dx*dx);
    up[i][j][k][2]=up[i][j][k][2]+(dt2*force[i+ff][j][k][2])/(dens[i+1][j][k]*dx*dx*dx);
 }
 }
 }

 absorb();

}
