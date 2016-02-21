// config.cpp : Implement of config.h
// Mainly about class IMAGE.

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <set>

#include "../include/config.h"

/********* Class IMAGE *********/

IMAGE::IMAGE() {
	size.width=size.height=0;
	buf=NULL;
}

IMAGE::~IMAGE() {
	if(buf) delete buf;
}

const COLOR* IMAGE::operator [] (int p) const {
	return buf+size.width*p;
}

int IMAGE::setBuf(const SIZE & _size,const COLOR * _buf) {
	size=_size;
	if(buf) delete buf;
	buf=new COLOR[size.width*size.height];
	if(NULL==buf) return NEW_MEM_ERROR;

	int cou=0;
	for(int i=0;i<size.height;++i)
		for(int j=0;j<size.width;++j) {
			buf[cou]=_buf[cou];
			++cou;
		}

	return NO_ERROR;
}

//////////////////////////////

// Function about XPM.

// Write to the xpm file.
int IMAGE::writeXPM(const char name[]) {
	return 0;
/*
	if(NULL==buf) return NO_DATA_ERROR;

	FILE *outfile;
	outfile=fopen(name,"w");
	if(NULL==outfile) return FILE_OPEN_ERROR;

	char pic_name[256]={};
	for(int i=0;isalnum(name[i]) || name[i]=='_';++i) pic_name[i]=name[i];
	fprintf(outfile,"static char * %s[] = {\n",pic_name);

	// The char that will be output is ascii_62 to ascii_(62+64-1).
	const char ch_len=64;
	const char ch_base=62;

	int cou,len;
	std::map <COLOR,int> rem;

	// Get the number of different color, and the length to represent them.
	getImageColor(rem);
	cou=rem.size();
	len=1;
	for(int base=ch_len;len<4 && base<cou;++len,base*=ch_len);

	fprintf(outfile,"\"%d %d %d %d \",\n",size.width,size.height,cou,len);
	for(std::map <COLOR,int> ::iterator it=rem.begin();it!=rem.end();++it) {
		fprintf(outfile,"\"");
		
	}
*/
}

//////////////////////////////

// Function about JPEG.
// Need the library libJpeg
// you can find it in http://www.ijg.org/
// Or the command : sudo apt-get install libjpeg8-dev
// if you are Ubuntu.
// Need the library -ljpeg for compiler.

#include <jpeglib.h>
#include <jerror.h>

// Read the jpg file.
// Only Support RGB mode and 1-byte mode.
int IMAGE::readJPG(const char name[]) {
	if(buf) { delete buf; buf=NULL; }

	unsigned char *linebuf;
	jpeg_decompress_struct cinfo;
	jpeg_error_mgr err_mgr;
	int components;
	FILE *infile;

	infile=fopen(name,"rb");
	if(NULL==infile) return FILE_OPEN_ERROR;
	
	cinfo.err=jpeg_std_error(&err_mgr);
	// maybe need a function for err_mgr.error_exit.	!!!!!
	err_mgr.error_exit=NULL;

	// init for decompress of jpeg file.
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo,infile);
	jpeg_read_header(&cinfo,true);
	cinfo.do_fancy_upsampling=false;
	cinfo.do_block_smoothing=false;
	jpeg_start_decompress(&cinfo);

	// get information of jpeg file.
	size=SIZE(cinfo.output_width,cinfo.output_height);
	components=cinfo.output_components;
	if(1!=components && 3!=components) return NOSUP_JPG_ERROR;

	int numPerLine=size.width*components;
	int cou=0;

	linebuf=new unsigned char[numPerLine];
	if(NULL==linebuf) return NEW_MEM_ERROR;
	buf=new COLOR [size.width*size.height];
	if(NULL==buf) return NEW_MEM_ERROR;

	// Read by lines.
	for(int r=0;r<size.height;++r) {
		jpeg_read_scanlines(&cinfo,&linebuf,1);

		for(int c=0;c<numPerLine;c+=components) {
			buf[cou].color=0;
			for(int i=0;i<components;++i) buf[cou].color_8[i]=linebuf[c+i];
			++cou;
		}
	}

	// Finish.
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(infile);

	delete linebuf;

	return NO_ERROR;
}

// Write to jpg file.
// Only Support RGB mode.
int IMAGE::writeJPG(const char name[]) {
	if(NULL==buf) return NO_DATA_ERROR;

	unsigned char *linebuf;
	jpeg_compress_struct cinfo;
	jpeg_error_mgr err_mgr;
	FILE *outfile;

	outfile=fopen(name,"wb");
	if(NULL==outfile) return FILE_OPEN_ERROR;

	cinfo.err=jpeg_std_error(&err_mgr);
	// maybe need a function for err_mgr.error_exit.	!!!!!
	err_mgr.error_exit=NULL;

	// init for compress of image.
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo,outfile);

	// the information of image.
	cinfo.image_width=size.width;
	cinfo.image_height=size.height;
	cinfo.input_components=3;						// Only support components==3.
	cinfo.in_color_space=JCS_RGB;			// Only support RGB mode.

	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo,100,true);		// [0,100] for quality. There only support 100.
	jpeg_start_compress(&cinfo,true);

	int numPerLine=cinfo.image_width*cinfo.input_components;
	int cou=0;

	linebuf=new unsigned char[numPerLine];
	if(NULL==linebuf) return NEW_MEM_ERROR;

	// Write.
	for(int r=0;r<cinfo.image_height;++r) {
		for(int c=0;c<numPerLine;c+=cinfo.input_components) {
			for(int i=0;i<cinfo.input_components;++i) linebuf[c+i]=buf[cou].color_8[i];
			++cou;
		}

		jpeg_write_scanlines(&cinfo,&linebuf,1);
	}

	// Finish.
	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
	fclose(outfile);

	delete linebuf;

	return NO_ERROR;
}

//////////////////////////////

/*******************************/
