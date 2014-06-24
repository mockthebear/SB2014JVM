#ifndef ACCESS_FLAG
#define ACCESS_FLAG

#ifndef __cplusplus

#include <stdbool.h>

#endif

#include "definition.hpp"

#define ACC_PUBLIC		0x0001
#define ACC_PRIVATE		0x0002
#define ACC_PROTECTED	0x0004
#define ACC_STATIC		0x0008
#define ACC_FINAL		0x0010
#define ACC_SUPER		0x0020
#define ACC_BRIDGE		0x0040
#define ACC_VORATILE	0x0040
#define ACC_VARARGS		0x0080
#define ACC_NATIVE		0x0100
#define ACC_INTERFACE	0x0200
#define ACC_ABSTRACT	0x0400
#define ACC_STRICT		0x0800
#define ACC_SYNTHETIC	0x1000
#define ACC_ENUM		0x4000

bool isPublic(u2);
bool isPrivate(u2);
bool isProtected(u2);
bool isStatic(u2);
bool isFinal(u2);
bool isSuper(u2);
bool isBridge(u2);
bool isVoratile(u2);
bool isVarargs(u2);
bool isNative(u2);
bool isInterface(u2);
bool isAbstract(u2);
bool isSrict(u2);
bool isSynthetic(u2);
bool isEnum(u2);

#endif
