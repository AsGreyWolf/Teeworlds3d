gprof teeworlds3d > out.gprof
../gprof2dot.py out.gprof > out.dot
dot -Tpng out.dot -O
