echo '' > tidy.out
for i
do
	clang-tidy $i -fix -fix-errors -- -Isrc -Iother/glm -Iother/sdl/include -Iother/glew/include -std=c++11 -x c++ >> tidy.out
done
