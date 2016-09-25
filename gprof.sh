gprof teeworlds3d > out.gprof
gprof2dot -n 3.0 -s out.gprof > out.dot
dot -Tpng out.dot -O
