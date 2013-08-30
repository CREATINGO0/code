/*
casear encode.
shifts letters according to the alphabetical order
*/
#include <stdio.h>
#include <ctype.h>

int encode( int enc_ch, int enc_shift );
int rotate_right(int rot_right);	
int rotate_left(int rot_left);
	
int main(void) {
	char ch;
	int shift;
	printf("Enter shift:");
	scanf("%d",&shift);
	while((ch = getchar())!= EOF) {
		putchar(encode(ch,shift));
	}
	printf("\n");
	return 0;
}

int encode( int enc_ch, int enc_shift ) {
	int i;
	if(enc_shift > 0 ) {
		for(i=0;i<enc_shift;i++) {
			enc_ch = rotate_right(enc_ch);
		}
	} else if (enc_shift < 0) {
		for(i=0;i>enc_shift;i--) {
			enc_ch = rotate_left(enc_ch);
		}
	}
	return enc_ch;
}

int rotate_right(int rot_right) {	
	if(isalpha(rot_right)) {
		rot_right++;
		if( rot_right == 'Z'+1 || rot_right == 'z'+1 ) {
			//in case exceed Z or z
			rot_right = rot_right - 26;
		}
	}
	return rot_right;
}

int rotate_left(int rot_left) {
	if(isalpha(rot_left)) {
		rot_left--;
		if( rot_left == 'A'-1 || rot_left == 'a'-1 ) {
			//in case exceeds A or a
			rot_left = rot_left + 26;
		}
	}
	return rot_left;
}
