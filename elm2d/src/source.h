// Source Routine

void source_routine()
{
 int i,j,n;
 double aaa,ss1,ss2,dist_so;
 FILE *in;
 char  string[50];

  // psource=v_alloc1d(Max_Time);
   //psource1=v_alloc1d(Max_Time);

   sprintf( string,"%s",input2);
   if(( in= fopen(string,"r")) ==NULL)
   {
      printf("Error opening file %s \n", string);
      MPI_Finalize();
      fclose(in);
      exit(1);
   }
  for(i=0; i<Max_Time; i++)
  {
    fscanf(in,"%lf %lf \n",&aaa,&psource[i]);
    //fscanf(in,"%lf %lf\n",&psource[i],&psource1[i]);
  }
  fclose(in);


   // Read in the x and y positions of sources:
   sprintf( string,"%s",input1);
   if(( in= fopen(string,"r")) ==NULL)
   {
      printf("Error opening file %s \n", string);
      MPI_Finalize();
      fclose(in);
      exit(1);
   }
   for (i = 0; i < NumSource; i++)
   {
      source[0][i]=source[1][i]=0;
      fscanf( in,"%lf %lf\n", &ss1, &ss2);
      //fscanf( in,"%lf %lf\n", &source[0][i], &source[1][i]);
      source[0][i]=round(ss1/dx);
      source[1][i]=round(ss2/dx);
   }
   fclose(in);


 for (n = 0; n < NumSource; n++)
 {
 for(i=0; i<Nx; i++)
 {
 for(j=0; j<Ny; j++)
 {
   gauss[i][j]=Gauss( dx*(source[0][n]-i-Nx*my_rank),dx*(source[1][n]-j),0.01*dx);
 }
 }
 }

 for(i=0; i<Nx; i++)
 {
 for(j=0; j<Ny; j++)
 {
   gauss[i][j]=0.0;
 }
 }
 for (n = 0; n < NumSource; n++)
 {
   if(locate_node(source[0][n])==my_rank) 
   gauss[source[0][n]%Nx][source[1][n]]=1.0;
 }

  n=0;
  for(i=0; i<Nx; i++)
  {
  for(j=0; j<Ny; j++)
  {
   dist_so = sqrt( (source[0][n]*dx-eqposn[i][j][0])*(source[0][n]*dx-eqposn[i][j][0])+
                   (source[1][n]*dx-eqposn[i][j][1])*(source[1][n]*dx-eqposn[i][j][1]) );
   if(dist_so < 2.0*dx)
   {
     gauss[i][j] = 1.0;
   }
  }
  }

}

void force_source()
{
  int i,j,n;
 n=0;

 for(i=0; i<Nx; i++)
 {
 for(j=0; j<Ny; j++)
 {
   force[i+ff][j][sdir] = force[i+ff][j][sdir] + sscale*psource[run_time]*gauss[i][j];
   //up[i][j][sdir] = up[i][j][sdir] + sscale*psource[run_time]*gauss[i][j];
 }
 }

 /*j=source[1][n];
 for(i=0; i<Nx; i++)
 {
   force[i+ff][j][sdir] = force[i+ff][j][sdir] + sscale*psource[run_time];
 }*/

}

void vol_source()
{
  int i,j,ip1,im1,jp1,jm1,n;

  for (n = 0; n < NumSource; n++)
  {

   jp1=source[1][n]+1;
   jm1=source[1][n]-1;
   ip1=(source[0][n]+1)%Nx;
   im1=(source[0][n]-1)%Nx;

   if(jp1==Ny) { jp1=0;  }
   if(jm1==-1) { jm1=Ny-1; }

   if(locate_node(source[0][n]+1)==my_rank)
   {
          force[ip1+ff][jp1][0] = force[ip1+ff][jp1][0] + sscale*psource[run_time];
          force[ip1+ff][jp1][1] = force[ip1+ff][jp1][1] + sscale*psource[run_time];

          force[ip1+ff][jm1][0] = force[ip1+ff][jm1][0] + sscale*psource[run_time];
          force[ip1+ff][jm1][1] = force[ip1+ff][jm1][1] - sscale*psource[run_time];
   }
   if(locate_node(source[0][n]-1)==my_rank)
   {
          force[im1+ff][jp1][0] = force[im1+ff][jp1][0] - sscale*psource[run_time];
          force[im1+ff][jp1][1] = force[im1+ff][jp1][1] + sscale*psource[run_time];

          force[im1+ff][jm1][0] = force[im1+ff][jm1][0] - sscale*psource[run_time];
          force[im1+ff][jm1][1] = force[im1+ff][jm1][1] - sscale*psource[run_time];
   }

 /*  jp1=source[1][n]+1;
   jm1=source[1][n];
   ip1=(source[0][n]+1)%Nx;
   im1=(source[0][n])%Nx;

   if(jp1==Ny) { jp1=0;  }
   if(jm1==-1) { jm1=Ny-1; }

   if(locate_node(source[0][n]+1)==my_rank)
   {
          force[ip1+ff][jp1][0] = force[ip1+ff][jp1][0] + sscale*psource[run_time];
          force[ip1+ff][jp1][1] = force[ip1+ff][jp1][1] + sscale*psource[run_time];

          force[ip1+ff][jm1][0] = force[ip1+ff][jm1][0] + sscale*psource[run_time];
          force[ip1+ff][jm1][1] = force[ip1+ff][jm1][1] - sscale*psource[run_time];
   }
   if(locate_node(source[0][n])==my_rank)
   {
          force[im1+ff][jp1][0] = force[im1+ff][jp1][0] - sscale*psource[run_time];
          force[im1+ff][jp1][1] = force[im1+ff][jp1][1] + sscale*psource[run_time];

          force[im1+ff][jm1][0] = force[im1+ff][jm1][0] - sscale*psource[run_time];
          force[im1+ff][jm1][1] = force[im1+ff][jm1][1] - sscale*psource[run_time];
   }*/

  }
}


double ranf()
{
const int ia=16807,ic=2147483647,iq=127773,ir=2836;
int il,ih,it;
double rc;
int t1,t2,t3,t4,t5,t6;
time_t ts,tp;
struct tm t;
int iseed;

/* Initial seed from the system time and and forced to be odd */

ts = time(&tp);
t  = *gmtime(&tp);
t1 = t.tm_sec+2*my_rank;
t2 = t.tm_min+3*my_rank;
t3 = t.tm_hour;
t4 = t.tm_mday;
t5 = t.tm_mon;
t6 = t.tm_year;
iseed = t6+70*(t5+2*my_rank+12*(t4+31*(t3+23*(t2+59*t1))));
iseed=iseed*drand48();
ih = iseed/iq;
il = iseed%iq;
it = ia*il-ir*ih;
if (it > 0)
  {
  iseed = it;
  }
else
  {
iseed = ic+it;
  }
rc = ic;
return iseed/rc;
}

