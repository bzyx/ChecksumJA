// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CHECKSUMJADLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CHECKSUMJADLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef CHECKSUMJADLL_EXPORTS
#define CHECKSUMJADLL_API __declspec(dllexport)
#else
#define CHECKSUMJADLL_API __declspec(dllimport)
#endif

// This class is exported from the ChecksumJaDll.dll
class CHECKSUMJADLL_API CChecksumJaDll {
public:
	CChecksumJaDll(void);
	// TODO: add your methods here.
};

extern CHECKSUMJADLL_API int nChecksumJaDll;

CHECKSUMJADLL_API int fnChecksumJaDll(void);
