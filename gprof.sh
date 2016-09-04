gprof teeworlds3d > out.gprof
../gprof2dot.py -n 3.0 -s out.gprof > out.dot
dot -Tpng out.dot -O
