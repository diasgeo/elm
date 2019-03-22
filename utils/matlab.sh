#!/bin/bash
matlabScript=$1

#matlab -nodisplay -nosplash -nodesktop -r "run('$matlabScript');exit"
matlab -nodisplay -nosplash -nodesktop -r "run('$matlabScript')"


