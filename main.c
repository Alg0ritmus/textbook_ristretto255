#include "ristretto255.h"



int main(){

	const u8 in[32] = {2,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,16,16};
	field_elem out, a, a_out;
	field_elem inv_sq_field_elem;

	// negative vectors
	u8 test_vectors[8][32] = {
		{0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,},
		{0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f,},
		{0xed, 0x57, 0xff, 0xd8, 0xc9, 0x14, 0xfb, 0x20, 0x14, 0x71, 0xd1, 0xc3, 0xd2, 0x45, 0xce, 0x3c, 0x74, 0x6f, 0xcb, 0xe6, 0x3a, 0x36, 0x79, 0xd5, 0x1b, 0x6a, 0x51, 0x6e, 0xbe, 0xbe, 0x0e, 0x20, },
		{0xc3, 0x4c, 0x4e, 0x18, 0x26, 0xe5, 0xd4, 0x03, 0xb7, 0x8e, 0x24, 0x6e, 0x88, 0xaa, 0x05, 0x1c, 0x36, 0xcc, 0xf0, 0xaa, 0xfe, 0xbf, 0xfe, 0x13, 0x7d, 0x14, 0x8a, 0x2b, 0xf9, 0x10, 0x45, 0x62, },
		{0xc9, 0x40, 0xe5, 0xa4, 0x40, 0x41, 0x57, 0xcf, 0xb1, 0x62, 0x8b, 0x10, 0x8d, 0xb0, 0x51, 0xa8, 0xd4, 0x39, 0xe1, 0xa4, 0x21, 0x39, 0x4e, 0xc4, 0xeb, 0xcc, 0xb9, 0xec, 0x92, 0xa8, 0xac, 0x78, },
		{0x47, 0xcf, 0xc5, 0x49, 0x7c, 0x53, 0xdc, 0x8e, 0x61, 0xc9, 0x1d, 0x17, 0xfd, 0x62, 0x6f, 0xfb, 0x1c, 0x49, 0xe2, 0xbc, 0xa9, 0x4e, 0xed, 0x05, 0x22, 0x81, 0xb5, 0x10, 0xb1, 0x11, 0x7a, 0x24, },
		{0xf1, 0xc6, 0x16, 0x5d, 0x33, 0x36, 0x73, 0x51, 0xb0, 0xda, 0x8f, 0x6e, 0x45, 0x11, 0x01, 0x0c, 0x68, 0x17, 0x4a, 0x03, 0xb6, 0x58, 0x12, 0x12, 0xc7, 0x1c, 0x0e, 0x1d, 0x02, 0x6c, 0x3c, 0x72, },
		{0x87, 0x26, 0x0f, 0x7a, 0x2f, 0x12, 0x49, 0x51, 0x18, 0x36, 0x0f, 0x02, 0xc2, 0x6a, 0x47, 0x0f, 0x45, 0x0d, 0xad, 0xf3, 0x4a, 0x41, 0x3d, 0x21, 0x04, 0x2b, 0x43, 0xb9, 0xd9, 0x3e, 0x13, 0x09,}
	};

	// P - negative vector
	u8 test_vectors_compl[8][32] = {
		{0xec, 0xff, 0xff, 0xff,0xff, 0xff, 0xff, 0xff,0xff, 0xff, 0xff, 0xff,0xff, 0xff, 0xff, 0xff,0xff, 0xff, 0xff, 0xff,0xff, 0xff, 0xff, 0xff,0xff, 0xff, 0xff, 0xff,0xff, 0xff, 0xff, 0x7f},
		{0xec, 0x0, 0x0, 0x0,0x0, 0x0, 0x0, 0x0,0x0, 0x0, 0x0, 0x0,0x0, 0x0, 0x0, 0x0,0x0, 0x0, 0x0, 0x0,0x0, 0x0, 0x0, 0x0,0x0, 0x0, 0x0, 0x0,0x0, 0x0, 0x0, 0x0},
		{0x0, 0xa8, 0x0, 0x27,0x36, 0xeb, 0x4, 0xdf,0xeb, 0x8e, 0x2e, 0x3c,0x2d, 0xba, 0x31, 0xc3,0x8b, 0x90, 0x34, 0x19,0xc5, 0xc9, 0x86, 0x2a,0xe4, 0x95, 0xae, 0x91,0x41, 0x41, 0xf1, 0x5f},
		{0x2a, 0xb3, 0xb1, 0xe7,0xd9, 0x1a, 0x2b, 0xfc,0x48, 0x71, 0xdb, 0x91,0x77, 0x55, 0xfa, 0xe3,0xc9, 0x33, 0xf, 0x55,0x1, 0x40, 0x1, 0xec,0x82, 0xeb, 0x75, 0xd4,0x6, 0xef, 0xba, 0x1d},
		{0x24, 0xbf, 0x1a, 0x5b,0xbf, 0xbe, 0xa8, 0x30,0x4e, 0x9d, 0x74, 0xef,0x72, 0x4f, 0xae, 0x57,0x2b, 0xc6, 0x1e, 0x5b,0xde, 0xc6, 0xb1, 0x3b,0x14, 0x33, 0x46, 0x13,0x6d, 0x57, 0x53, 0x7},
		{0xa6, 0x30, 0x3a, 0xb6,0x83, 0xac, 0x23, 0x71,0x9e, 0x36, 0xe2, 0xe8,0x2, 0x9d, 0x90, 0x4,0xe3, 0xb6, 0x1d, 0x43,0x56, 0xb1, 0x12, 0xfa,0xdd, 0x7e, 0x4a, 0xef,0x4e, 0xee, 0x85, 0x5b},
		{0xfc, 0x38, 0xe9, 0xa2,0xcc, 0xc9, 0x8c, 0xae,0x4f, 0x25, 0x70, 0x91,0xba, 0xee, 0xfe, 0xf3,0x97, 0xe8, 0xb5, 0xfc,0x49, 0xa7, 0xed, 0xed,0x38, 0xe3, 0xf1, 0xe2,0xfd, 0x93, 0xc3, 0xd},
		{0x66, 0xd9, 0xf0, 0x85,0xd0, 0xed, 0xb6, 0xae,0xe7, 0xc9, 0xf0, 0xfd,0x3d, 0x95, 0xb8, 0xf0,0xba, 0xf2, 0x52, 0xc,0xb5, 0xbe, 0xc2, 0xde,0xfb, 0xd4, 0xbc, 0x46,0x26, 0xc1, 0xec, 0x76},
	};



	/*
	printf("inv_sqrt( out, u, const, v)\n");
	// out u v
	for (int i = 0; i < 8; ++i){
		unpack25519(out,test_vectors_compl[i]);
		inv_sqrt(inv_sq_field_elem,F_ONE,out);
		printf("inv_sq_field_elem in main:\n");
		print(inv_sq_field_elem);
		printf("\n........................\n");
	}
	
	*/


	unpack25519(a,test_vectors_compl[7]); // posledny vector
	fcopy(out,a); // out = a

	for (int i = 2; i < 8; ++i)
	{

		fmul(out,out,a); // a*a -> fmul prevziaty z PDF Kleppmann
		printf("\na^%d:\n",i);
		print(out);
		printf("\n-------------\n");

	}

	printf("a^7 z funkcie pow7:\n");
	pow7(a_out,a);
	print(a_out);



	/* testing negative vectors 


	printf("\n\ntesting negative vectors:\n");
	int is_negative=1;

	for (int i = 0; i < 8; ++i){
		field_elem temp;
		unpack25519(temp,test_vectors[i]);
		is_negative = is_negative & is_neg(temp);
		printf("vector:%d, is:%d\n",i,is_neg(temp));
	}

	if (is_negative){
		printf("SUCCESS, all are negative\n");
	}
	else{
		printf("FAILED, NOT all are negative\n");	
	}
	*/




	/* testing complements of negative vectors 
	printf("\n\ntesting complements of negative vectors:\n");
	is_negative=1;

	for (int i = 0; i < 8; ++i){
		field_elem temp;
		unpack25519(temp,test_vectors_compl[i]);
		is_negative = is_negative & is_neg(temp);
		printf("vector:%d, is:%d\n",i,is_neg(temp));
	}

	if (!is_negative){
		printf("SUCCESS, all complements are positive\n");
	}
	else{
		printf("FAILED, NOT all complements are positive\n");	
	}
	
	*/
	
	/*
	// skuska modulus
	
	field_elem A;
	u8 A_pack[32];
	u8 A_pack_out[32];
	fcopy(A,_121665);
	pack25519(A_pack,A);
	print_32(A_pack);


	
	ristretto255_point *temp_rp;
	ristretto255_decode(&temp_rp, in);
	printf("point cords \n");
	print(&temp_rp->x);
	print(&temp_rp->y);
	print(&temp_rp->z);
	print(&temp_rp->t);


	printf("\nA_pack_out before encoding:\n");
	print_32(A_pack_out);
	ristretto255_encode(A_pack_out, temp_rp);
	printf("\nA_pack_out after encoding:\n");
	print_32(A_pack_out);
	*/
	

	return 0;
}


