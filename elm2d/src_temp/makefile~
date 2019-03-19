

MPICC = mpicc
#MPICC =/opt/intel/impi/3.1/bin64/mpiicc

#CFLAGS =  -lm 

3D-ELM: 3D-ELM.o 
	$(MPICC) $(CFLAGS) -o 3D-ELM 3D-ELM.o 

3D-ELM.o: 3D-ELM.c 
	$(MPICC) $(CFLAGS) -c 3D-ELM.c 

clean:
	rm -rf *o 3D-ELM
