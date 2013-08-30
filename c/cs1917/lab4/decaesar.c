/*
decaesar.c by xirui luo
works with c1.in and c2.in but failed with c3.in
*/
#include <stdio.h>
#include <ctype.h>

int encode( int enc_ch, int enc_shift );
int rotate_right(int rot_right);	
int rotate_left(int rot_left);

int main(int argc, char *argv[]) {
	FILE *fp;
	int ch,i,j;
	int count[26]={0},countMax = 0,indexMax = 0;

	// open the file whose name is given as a command-line argument
	fp = fopen(argv[1],"r");
	while(( ch = getc(fp)) != EOF ) {
		ch = toupper( ch );
		if(ch >= 'A' && ch <= 'Z') {
			i = ch - 'A';
			count[i]++;
		}
	}

	// close the file and re-open it from the beginning
	fclose(fp);
	for(j=0;j<26;j++) {
		if(countMax <= count[j]){
			countMax = count[j];
			indexMax = j;
		}
	}
	indexMax = 4- indexMax;
	fp = fopen(argv[1],"r");
	while(( ch = getc(fp)) != EOF ) {
		putchar(encode(ch,indexMax));
	}

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
