cd android/jni
ndk-build
cd ..
ant debug
cd ..
mv android/bin/SDLActivity-debug.apk SDLActivity-debug.apk
mkdir tee3d
mv data/shaders data/shaders-gl
mv data/shaders-gles data/shaders
mv data tee3d/data
zip -r AndroidData.zip tee3d
mv tee3d/data data
mv data/shaders data/shaders-gles
mv data/shaders-gl data/shaders
rm -r tee3d
