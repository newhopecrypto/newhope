#include "api.h"
#include "poly.h"
#include "cpucycles.h"
#include <stdlib.h>
#include <stdio.h>

#define NTESTS 10000

static int cmp_llu(const void *a, const void*b)
{
  if(*(unsigned long long *)a < *(unsigned long long *)b) return -1;
  if(*(unsigned long long *)a > *(unsigned long long *)b) return 1;
  return 0;
}

static unsigned long long median(unsigned long long *l, size_t llen)
{
  qsort(l,llen,sizeof(unsigned long long),cmp_llu);

  if(llen%2) return l[llen/2];
  else return (l[llen/2-1]+l[llen/2])/2;
}

static unsigned long long average(unsigned long long *t, size_t tlen)
{
  unsigned long long acc=0;
  size_t i;
  for(i=0;i<tlen;i++)
    acc += t[i];
  return acc/(tlen);
}

static void print_results(const char *s, unsigned long long *t, size_t tlen)
{
  size_t i;
  printf("%s", s);
  for(i=0;i<tlen-1;i++)
  {
    t[i] = t[i+1] - t[i];
  //  printf("%llu ", t[i]);
  }
  printf("\n");
  printf("median: %llu\n", median(t, tlen));
  printf("average: %llu\n", average(t, tlen-1));
  printf("\n");
}


unsigned long long t[NTESTS];
unsigned char seed[32] = {0};

int main()
{
  unsigned char sk_a[CRYPTO_SECRETKEYBYTES];
  unsigned char seed[NEWHOPE_SYMBYTES];
  
  unsigned char key_a[CRYPTO_BYTES], key_b[CRYPTO_BYTES];
  unsigned char* senda = (unsigned char*) malloc(NTESTS*CRYPTO_PUBLICKEYBYTES);
  unsigned char* sendb = (unsigned char*) malloc(NTESTS*CRYPTO_CIPHERTEXTBYTES);

  poly ap;

  int i;

  for(i=0; i<NTESTS; i++)
  {
    t[i] = cpucycles();
    poly_ntt(&ap);
  }
  print_results("NTT:           ", t, NTESTS);
 
  for(i=0; i<NTESTS; i++)
  {
    t[i] = cpucycles();
    poly_invntt(&ap);
  }
  print_results("INVNTT:        ", t, NTESTS);
 
  for(i=0; i<NTESTS; i++)
  {
    t[i] = cpucycles();
    poly_uniform(&ap, seed);
  }
  print_results("gen_a:         ", t, NTESTS);
 
  for(i=0; i<NTESTS; i++)
  {
    t[i] = cpucycles();
    poly_sample(&ap, seed, 0);
  }

  for(i=0; i<NTESTS; i++)
  {
    t[i] = cpucycles();
    crypto_kem_keypair(senda+i*CRYPTO_PUBLICKEYBYTES, sk_a);
  }
  print_results("keypair: ", t, NTESTS);

  for(i=0; i<NTESTS; i++)
  {
    t[i] = cpucycles();
    crypto_kem_enc(sendb+i*CRYPTO_CIPHERTEXTBYTES, key_b, senda+i*CRYPTO_PUBLICKEYBYTES);
  }
  print_results("encaps:  ", t, NTESTS);

  for(i=0; i<NTESTS; i++)
  {
    t[i] = cpucycles();
    crypto_kem_dec(key_a, sendb+i*CRYPTO_CIPHERTEXTBYTES, sk_a);
  }
  print_results("decaps:  ", t, NTESTS);
 
  
  // Cleaning
  free(senda);
  free(sendb);
  
  return 0;
}
