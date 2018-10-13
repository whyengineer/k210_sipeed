sipeed m1 / lichee dan
# example 
the k210 example code based on sipeed m1
## how to build
1.  git clone the k210 freetros sdk
    git clone https://github.com/kendryte/kendryte-freertos-sdk
2.  cd example/hello_wordk
3.  mkdir build
4.  cd build 
5.  cmake .. -DSDK=the-sdk-path -DTOOLCHAIN=risc-v-tool-chain
    eg. cmake .. -DSDK=/Users/frankie/k210/kendryte-freertos-sdk -DTOOLCHAIN=/Users/frankie/k210/riscv64-toolchain/bin/
    


