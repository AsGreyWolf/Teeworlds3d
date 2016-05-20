gprof teeworlds3d > out.gprof
gprof2dot out.gprof > out.dot
dot -Tpng out.dot -O