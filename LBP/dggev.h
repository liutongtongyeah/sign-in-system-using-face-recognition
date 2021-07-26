////#include <f2c.h>
//#include <process.h>
//extern "C"
//{
//#include <f2c.h>
//#include <clapack.h>
//}
#pragma comment(linker, "/NODEFAULTLIB:msvcrtd.lib")
//#pragma comment(linker, "/NODEFAULTLIB:libcmt.lib")
extern "C" int __declspec(dllimport) GeneralEig(double *A, double *B, int dim, double *Evecs,
	double *alphaR, double *alphaI, double *beta);