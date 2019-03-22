clear all
close all
clc



[NxStatus Nx] = system('grep \ Nx example/input/PARAMETERS.h | cut -d "(" -f2 | cut -d ")" -f1');
Nx_mpi = str2num(Nx);
nproc=9;
Nx = Nx_mpi*nproc;

x= transpose([0:Nx-1]);
x_min = min(x);
x_max = max(x);
x_middle = (x_min + x_max)/2;

%topo = ones(size(x))*(Nx-100);
topoHight=200;
topo = Nx-100 -topoHight + round(gausswin(Nx)*topoHight);


fileID = fopen(['example/input/topo'],'w');

for i = [1:Nx]
  fprintf(fileID, '%i %i\n', x(i), topo(i));
end

fclose(fileID);
