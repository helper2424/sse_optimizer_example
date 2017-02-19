## Example of assembler injection with SSE for calculations speedy

We have file `test` with 1gb of data. There are some randoms bytes.

```
dd if=/dev/urandom of=./test count=1 bs=1073741824
```

Next compile reference program.

```
gcc -o ref ./main.c 
```

Start several times this: 

```
time ./ref test
```

You will get results.
Next, generate optimized version:

```
gcc -o asm ./main_asm.c 
```

And try several times this program:

```
time ./asm test
```

You will get really better results. Here the SSE magic (: