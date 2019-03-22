clear all
close all
clc



[Nx_mpiStatus Nx_mpi] = system('grep \ Nx example/input/PARAMETERS.h | cut -d "(" -f2 | cut -d ")" -f1');
Nx_mpi = str2num(Nx_mpi);
nproc=9;
Nx = Nx_mpi*nproc;

[NyStatus Ny] = system('grep \ Ny example/input/PARAMETERS.h | cut -d "(" -f2 | cut -d ")" -f1');
Ny = str2num(Ny)

x= transpose([0:Nx-1]);
x_min = min(x);
x_max = max(x);
x_middle = (x_min + x_max)/2;

% gauss topography
topoHight=300;
topo = Nx-1 -topoHight + round(gausswin(Nx)*topoHight);


fileID = fopen(['example/input/topo'],'w');

for i = [1:Nx]
  fprintf(fileID, '%i %i\n', x(i), topo(i));
end

fclose(fileID);
