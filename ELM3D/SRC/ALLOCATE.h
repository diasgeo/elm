 // Allocation of memory for undefined array sizes 1d  doubles
double *v_alloc1d(int n1)
{
 double *v;

 v=(double *) calloc(n1,sizeof(double ));
 if (v==NULL)
 {
    printf(" Could not allocate memory 101\n");
    exit(1);
 }
  return v;

}

void free_array1d(double *a)
{
 free(a);
}

// Allocation of memory for undefined array sizes 1d integers
int *alloc_int(int n1)
{
  int *v;

 v=(int *) calloc(n1,sizeof(int ) );
 if (v==NULL)
 {
    printf(" Could not allocate memory 102\n");
    exit(1);
 }
 return v;

}

void free_int1d(int *a)
{
 free(a);
}

// Allocation of memory for undefined array sizes 2d doubles
double **v_alloc2d(int n1,int n2)
{
  int i;
  double **v;

 v=(double **) calloc(n1,sizeof(double *));
 if (v==NULL)
 {
    printf(" Could not allocate memory 201\n");
    exit(1);
 }
 for(i=0; i<n1; i++)
 {
   v[i]=(double *) calloc(n2,sizeof(double ));
   if (v[i]==NULL)
   {
      printf(" Could not allocate memory 202\n");
      exit(1);
   }
 }

 return v;

}

// Freeing 2d array
void free_array2d(double **a,int n)
{
  int i;
 for(i=0; i<n; i++)
 {
    free(a[i]);
 }
 free(a);

}
///////////////////////////////////////////////////////////
// Allocation of memory for undefined array sizes 2d ints
///////////////////////////////////////////////////////////
int **alloc2d_int(int n1,int n2)
{
  int i;
  int **v;

 v=(int **) calloc(n1,sizeof(int *));
 if (v==NULL)
 {
    printf(" Could not allocate memory 301\n");
    exit(1);
 }
 for(i=0; i<n1; i++)
 {
   v[i]=(int *) calloc(n2,sizeof(int ));
   if (v[i]==NULL)
   {
      printf(" Could not allocate memory 302\n");
      exit(1);
   }
 }

 return v;

}

// Freeing 2d array
void free_int2d(int **a,int n)
{
  int i;
 for(i=0; i<n; i++)
 {
    free(a[i]);
 }
 free(a);

}

/////////////////////////////////////////////////////////////////////////////
///////////
/////////////////////////////////////////////////////////////////////////////
double ***v_alloc3d(int n1,int n2,int n3)
{
  int i,j;
  double ***v;

 v=(double ***) calloc(n1,sizeof(double **));
 if (v==NULL)
 {
    printf(" Could not allocate memory 401\n");
    exit(1);
 }
 for(i=0; i<n1; i++)
 {
   v[i]=(double **) calloc(n2,sizeof(double *));
   if (v[i]==NULL)
   {
      printf(" Could not allocate memory 402\n");
      exit(1);
   }
   for(j=0; j<n2; j++)
   {
    v[i][j]=(double *) calloc(n3,sizeof(double ));
    if (v[i][j]==NULL)
    {
      printf(" Could not allocate memory 403\n");
      exit(1);
    }
   }
}

  return v;

}


void free_array3d(double ***a,int n,int m)
{
  int i,j;
 for(i=0; i<n; i++)
 {
   for(j=0; j<m; j++)
    free(a[i][j]);
    free(a[i]);
 }
 free(a);

}

double ****v_alloc4d(int n1,int n2,int n3,int n4)
{
  int i,j,k;
  double ****v;

 v=(double ****) calloc(n1,sizeof(double ***));
 if (v==NULL)
 {
    printf(" Could not allocate memory 501\n");
    exit(1);
 }
 for(i=0; i<n1; i++)
 {
    v[i]=(double ***) calloc(n2,sizeof(double **));
    if (v[i]==NULL)
    {
      printf(" Could not allocate memory 502\n");
      exit(1);
    }
  for(j=0; j<n2; j++)
  {
     v[i][j]=(double **) calloc(n3,sizeof(double *));
     if (v[i][j]==NULL)
     {
      printf(" Could not allocate memory 503\n");
      exit(1);
     }
   for(k=0; k<n3; k++)
   {
     v[i][j][k]=(double *) calloc(n4,sizeof(double ));
     if (v[i][j][k]==NULL)
     {
       printf(" Could not allocate memory 504\n");
       exit(1);
     }
   } //k
  }  //j
 }   //i

   return v;
}  //end function

void free_array4d(double ****a,int n,int m,int o)
{
  int i,j,k;
for(i=0; i<n; i++)
 {
  for(j=0; j<m; j++)
  {
    for(k=0; k<o; k++)
    {
    free(a[i][j][k]);
    }
    free(a[i][j]);
  }
    free(a[i]);
 }
 free(a);

}


