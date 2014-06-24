#include "access_flag.hpp"

bool isPublic(u2 flags) {
	if(flags & ACC_PUBLIC)
		return true;	
	return false;
}

bool isPrivate(u2 flags)  {
	if(flags & ACC_PRIVATE)
		return true;	
	return false;
}

bool isProtected(u2 flags)  {
	if(flags & ACC_PROTECTED)
		return true;	
	return false;
}

bool isStatic(u2 flags)  {
	if(flags & ACC_STATIC)
		return true;	
	return false;
}

bool isFinal(u2 flags)  {
	if(flags & ACC_FINAL)
		return true;	
	return false;
}

bool isSuper(u2 flags)  {
	if(flags & ACC_SUPER)
		return true;	
	return false;
}

bool isBridge(u2 flags)  {
	if(flags & ACC_BRIDGE)
		return true;	
	return false;
}

bool isVoratile(u2 flags)  {
	if(flags & ACC_VORATILE)
		return true;	
	return false;
}

bool isVarargs(u2 flags)  {
	if(flags & ACC_VARARGS)
		return true;	
	return false;
}

bool isNative(u2 flags)  {
	if(flags & ACC_NATIVE)
		return true;	
	return false;
}

bool isInterface(u2 flags)  {
	if(flags & ACC_INTERFACE)
		return true;	
	return false;
}

bool isAbstract(u2 flags)  {
	if(flags & ACC_ABSTRACT)
		return true;	
	return false;
}

bool isSrict(u2 flags)  {
	if(flags & ACC_STRICT)
		return true;	
	return false;
}

bool isSynthetic(u2 flags)  {
	if(flags & ACC_SYNTHETIC)
		return true;	
	return false;
}

bool isEnum(u2 flags)  {
	if(flags & ACC_ENUM)
		return true;	
	return false;
}

