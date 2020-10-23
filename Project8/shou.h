void loadimage(IMAGE *pDstImg, LPCTSTR pImgFile, int nWidth = 0, int nHeight = 0, bool bResize = false);
// 从图片文件获取图像(bmp/gif/jpg/png/tif/emf/wmf/ico)

void loadimage(IMAGE *pDstImg, LPCTSTR pResType, LPCTSTR pResName, int nWidth = 0, int nHeight = 0, bool bResize = false);
// 从资源文件获取图像(bmp/gif/jpg/png/tif/emf/wmf/ico)
