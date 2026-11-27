/** Public C API of librecompachievements, the RecompAchievements client SDK.
 *  This header is the SDK's only binary interface: it declares plain C functions and types
 *  so any C or C++ recomp can use it, whatever compiler built the library.
**/
#ifndef RCA_RCA_H
#define RCA_RCA_H

#include "rca/export.h"
#include "rca/version.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Returns the version of the linked library as "MAJOR.MINOR.PATCH" or
 *  "MAJOR.MINOR.PATCH-PRERELEASE". Compare it with RCA_VERSION_STRING to detect a game built
 *  against different headers than the library it loads. The string is static; never free it.
**/
RCA_API const char* rca_version(void);

#ifdef __cplusplus
}
#endif

#endif
