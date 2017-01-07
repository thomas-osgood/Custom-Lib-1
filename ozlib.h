/*
 * Created By : Thomas Osgood
 * Date Created : 2015 11 18 
 *
 * Thomas Osgood's Custom Library Header File.
 *
 * Note :
 * Must attempt to organize functions in both
 * this file and the C file.
 * The most user-friendly method would be 
 * organizing them by alphabet. 
 * Can also organize them by their return types.
 */

#ifndef OZLIB_H_
#define OZLIB_H_

#ifdef __cplusplus
extern "C" {
#endif

#define BYTE2BIT(x) x*8
#define NUMELEMS(arr) sizeof(arr)/sizeof(arr[0])

	extern void DispUserInfo(void);
	extern void PrintChar(const char c, const int amt);
	extern int Write2File(const char *f);
	extern int DispFileInfo(const char *f);
	extern int LogVars(const int *varArr, const int numElems);
	extern void SysMsg(const char *str);

#ifdef __cplusplus
}
#endif

#endif
