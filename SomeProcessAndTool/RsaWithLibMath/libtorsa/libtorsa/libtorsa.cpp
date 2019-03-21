// https://www.cnblogs.com/linxr/archive/2010/11/10/1927003.html

#include "stdafx.h"

//º”√‹£∫
//
//c = m^d mod n
//
//Ω‚√‹£∫
//
//m = c^e mod n

#include "tommath.h"
typedef struct {
	int bits;           /* bits in key */
	mp_int n;           /* modulus */
	mp_int e;           /* public exponent */
	mp_int d;           /* private exponent */
}rsa_key;
int rsa_rng(unsigned char *dst, int len, void *dat)
{
	int x;
	for (x = 0; x < len; x++)   dst[x] = rand() & 0xFF;
	return len;
}
int rsa_preme_random(mp_int *a, int bits)
{
	int err = mp_prime_random_ex(a, 8, bits, LTM_PRIME_2MSB_ON | LTM_PRIME_SAFE, rsa_rng, NULL);
	if (err != MP_OKAY) {
		return -1;
	}
	return 0;
}
int rsa_gen_key(rsa_key *key, int bits)
{
	mp_int p, q;
	mp_int sp, sq;
	mp_int n, m;
	mp_int e, d;
	mp_int t;
	//init mp_ints
	mp_init(&p);  mp_init(&q);  mp_init(&sp); mp_init(&sq);
	mp_init(&n);  mp_init(&m);  mp_init(&e);  mp_init(&d);  mp_init(&t);
	//genarate p & q
	rsa_preme_random(&p, bits / 2);
	rsa_preme_random(&q, bits / 2);
	//make n & m
	mp_sub_d(&p, 1, &sp);
	mp_sub_d(&q, 1, &sq);
	mp_mul(&p, &q, &n);
	mp_mul(&sp, &sq, &m);

	//make e & d 
	mp_set(&e, 127);
retry_e:
	mp_gcd(&e, &m, &t);
	if ((mp_cmp_d(&t, 1)) > 0){
		mp_add_d(&e, 2, &e);
		goto retry_e;
	}
	mp_invmod(&e, &m, &d);
	//copy n d e to key struct
	mp_init(&key->n);
	mp_init(&key->d);
	mp_init(&key->e);
	key->bits = bits;
	mp_copy(&n, &key->n);
	mp_copy(&d, &key->d);
	mp_copy(&e, &key->e);

	mp_clear(&p); mp_clear(&q); mp_clear(&sp); mp_clear(&sq);
	mp_clear(&n); mp_clear(&m); mp_clear(&e); mp_clear(&d); mp_clear(&t);
	return 0;
}
/*set rsa key by string */
int rsa_set_key(rsa_key *key, char *sn, char *se, char *sd, int bits, int radix)
{
	key->bits = bits;
	mp_init(&key->n);
	mp_init(&key->d);
	mp_init(&key->e);
	if (sn)    mp_read_radix(&key->n, sn, radix);
	if (se)    mp_read_radix(&key->e, se, radix);
	if (sd)    mp_read_radix(&key->d, sd, radix);

	return 0;
}
/*encrypt by private key */
int rsa_encrypt(mp_int *c, mp_int *m, rsa_key *key)
{
	mp_exptmod(c, &key->d, &key->n, m);
	return 0;
}
/*decrypt by public key */
int rsa_decrypt(mp_int *m, mp_int *c, rsa_key *key)
{
	mp_exptmod(m, &key->e, &key->n, c);
	return 0;
}
int rsa_test()
{
	mp_int  c, m;
	rsa_key key;
	char sn[] = "F574FD11";
	char se[] = "2BBE7481";
	char sm[] = "0D48";
	char sc[1024];
	mp_init(&c);
	mp_init(&m);
	rsa_set_key(&key, sn, se, NULL, 128, 16);
	mp_read_radix(&m, sm, 16);
	rsa_decrypt(&m, &c, &key);
	mp_toradix(&c, sc, 16);
	printf("%s\n", sc);
	return 0;
}


int main()
{
	rsa_test();
	return 0;
}