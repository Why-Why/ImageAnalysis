// config.h : Base data structure for image.

#ifndef CONFIG_H
#define CONFIG_H

// Some const number.
const int INF=0x3f3f3f3f;
const long long LINF=1000000000000000000LL;
const double DINF=1e300;

// Some define:
// Error:
#define NO_ERROR 0
#define FILE_OPEN_ERROR 1
#define NOSUP_JPG_ERROR 2
#define NEW_MEM_ERROR 3
#define NO_DATA_ERROR 4
#define NO_IMAGE_ERROR 5

// Size Structure.
struct SIZE {
	unsigned int width,height;
	SIZE(unsigned int w=0,unsigned int h=0):width(w),height(h) {}
};

// Pos Structure.
struct POS {
	int x,y;
	POS(int _x=0,int _y=0):x(_x),y(_y) {}
};

// Color Structure, a 32-bit color or RGB color.
union COLOR {
	unsigned int color;
	unsigned char color_8[4];			// 0 is R, 1 is G, 2 is B.

	// Is this OK ?
	COLOR & operator = (unsigned int x) { color=x; }
	// Get the Luminance of RGB color, or called Gray ?
	unsigned int getYColor() const
	{ return (299*color_8[0]+587*color_8[1]+114*color_8[2]+500)/1000; }
};

// Image Structure, include the size of the image, the color of each pixel about the image.
class IMAGE {
	private:
		SIZE size;
		COLOR * buf;

	public:
		IMAGE();
		~IMAGE();

		SIZE getSize() const { return size; }
		const COLOR * getBuf() const { return buf; }
		const COLOR * operator[] (int) const;

		int setBuf(const SIZE &,const COLOR *);

		// Function about JPEG.
		int readJPG(const char *);
		int writeJPG(const char *);

		// Function about XPM.
		int writeXPM(const char *);

		void test() {
			size=SIZE(8,8);
			buf=new COLOR[64];
			for(int i=0;i<64;++i) buf[i]=0;
			buf[6]=buf[13]=buf[21]=buf[29]=buf[38]=buf[47]=1;
			buf[33]=buf[34]=buf[41]=buf[49]=buf[57]=1;
		}
};

#endif
