/*
gcc `MagickWand-config --cflags --cppflags` -O2 -o resize resize.c `MagickWand-config --ldflags --libs` 

to compile


c00f3r@gmail.com

exemplo bobo resize

aptitude install libmagickwand-dev
 */
#include <ImageMagick/wand/magick_wand.h>

main()
{
 MagickWand *m_wand = NULL;
 int width,height;	
 MagickWandGenesis();
	
 m_wand = NewMagickWand();
 MagickReadImage(m_wand,"logo:");
 width = MagickGetImageWidth(m_wand);
 height = MagickGetImageHeight(m_wand);
	
// corta metade
 if((width /= 2) < 1)width = 1;
 if((height /= 2) < 1)height = 1;
	

 MagickResizeImage(m_wand,width,height,LanczosFilter,1);
// qualidade 93 quanto mais alta mais ruim fica lol
 MagickSetImageCompressionQuality(m_wand,93);
 MagickWriteImage(m_wand,"logo_resize.jpg");
 if(m_wand)m_wand = DestroyMagickWand(m_wand);	
 MagickWandTerminus();
}

