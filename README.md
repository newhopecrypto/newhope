# NewHope

Implementations of the NewHope key-encapsulation mechanism specified in the submission to the 
[NIST Post-Quantum Cryptography Standardization Project](https://csrc.nist.gov/Projects/Post-Quantum-Cryptography/).

## Build instructions
To obtain and build the code, run the following sequence of commands:
```
 git clone https://github.com/newhopecrypto/newhope.git
 cd newhope/ref && make
 cd ../avx2 && make
```
 This will build the binaries
* `ref/PQCgenKAT_cpakem512`,
* `ref/PQCgenKAT_cpakem1024`,
* `ref/PQCgenKAT_ccakem512`,
* `ref/PQCgenKAT_ccakem1024`,
* `ref/test_cpakem512`,
* `ref/test_cpakem1024`,
* `ref/test_ccakem512`,
* `ref/test_ccakem1024`,
* `ref/speed_cpakem512`,
* `ref/speed_cpakem1024`,
* `ref/speed_ccakem512`,
* `ref/speed_ccakem1024`,
* `avx2/PQCgenKAT_cpakem512`,
* `avx2/PQCgenKAT_cpakem1024`,
* `avx2/PQCgenKAT_ccakem512`,
* `avx2/PQCgenKAT_ccakem1024`,
* `avx2/test_cpakem512`,
* `avx2/test_cpakem1024`,
* `avx2/test_ccakem512`,
* `avx2/test_ccakem1024`,
* `avx2/speed_cpakem512`,
* `avx2/speed_cpakem1024`,
* `avx2/speed_ccakem512`, and
* `avx2/speed_ccakem1024`.

The `PQCgenKAT` binaries produce test-vector files
as specified in the NIST submission requirements.
The `test` binaries perform various key exchanges 
and output only the sizes of keys and ciphertexts if they are successful. 
The `speed` binaries perform benchmarks of key encapsulation
and various subroutines.
Binaries containing the string `cpakem` implement KEM variant without CCA security;
binaries containing the string `ccakem` implement KEM variant with CCA security.
Binaries ending on `512` implement the NewHope512 parameter set;
binaries ending on `1024` implement the NewHope1024 parameter set.


## License
All code in this repository is in the public domain,
except for the files `PQCgenKAT.c`, `rng.c` and `rng.h`, 
which are copyrighted by NIST with "All rights reserved".
For Keccak, we are using public-domain
code from sources and by authors listed in 
comments on top of the respective files.
