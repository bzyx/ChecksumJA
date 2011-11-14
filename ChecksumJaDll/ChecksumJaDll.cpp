// ChecksumJaDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ChecksumJaDll.h"


// This is an example of an exported variable
CHECKSUMJADLL_API int nChecksumJaDll=0;

// This is an example of an exported function.
CHECKSUMJADLL_API int fnChecksumJaDll(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see ChecksumJaDll.h for the class definition
CChecksumJaDll::CChecksumJaDll()
{
	return;
}
