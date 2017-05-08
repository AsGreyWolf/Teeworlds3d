echo '' > out.tidy
#for i
#do
	for j in $(find src -name '*.cpp' -or -name '*.h');#$i
	do
		if test -f "$j"
		then
			printf "\n\nProcessing $j\n\n"
			printf "\n\nProcessing $j\n\n" >> out.tidy
			clang-tidy $j -fix -fix-errors -- -Isrc -Iother/glm -Iother/sdl/include -Iother/glew/include -std=c++14 -x c++ >> out.tidy
			clang-format $j > $j.tidy
			rm $j
			mv $j.tidy $j
		fi
	done
#done
