clear all
close all
clc

Nx = 800;
x= transpose([0:Nx-1]);

topo = ones(size(x))*(Nx-1);

fileID = fopen(['topography'],'w');

for i = [1:Nx]
  fprintf(fileID, '%i %i\n', x(i), topo(i));
end

fclose(fileID);