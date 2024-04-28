
# cleanup
rm -f *.o jroad.neo jroad.map neo6502.lib{,.temp}

#compile
#/Users/giovanni.pozzobon/Documents/GitHub/llvm-mos-sdk/bin/mos-neo6502-clang -Os -v -fverbose-asm -mcpu=mosw65c02 -D__NEO6502__ -mlto-zp=224 \
#-I /Users/giovanni.pozzobon/Documents/GitHub/llvm-mos-sdk/mos-platform/neo6502/asminc \
#-L /Users/giovanni.pozzobon/Documents/GitHub/llvm-mos-sdk/mos-platform/neo6502/lib \
#-isystem Users/giovanni.pozzobon/Documents/GitHub/llvm-mos-sdk/mos-platform/neo6502/include \
#main.c utility.c api.c quicksort.c sprite.c -o main.neo 
#-v -fverbose-asm


# cleanup
rm -f *.o mapper.neo mapper.map {,.temp}

/Users/giovanni.pozzobon/Documents/GitHub/llvm-mos-sdk/bin/mos-neo6502-clang++ -Os  main.cpp api.cpp gui.cpp mouse.cpp console.cpp util.cpp -o mapper.neo 


# launch emulator
test -f mapper.neo && ./neo mapper.neo@800 cold