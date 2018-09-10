#include <iostream>

#define USE_VIRTUAL_INHERITANCE 0
#if USE_VIRTUAL_INHERITANCE
  #define VIRTUAL virtual
#else
  #define VIRTUAL
#endif

class S {
int s;
};

class A : public S {
int a;
};

class B : VIRTUAL public A {
int b;
};

class C : VIRTUAL public A {
int c;
};

class BC : public B, public C {
int bc;
};

template<class S, class T>
unsigned int offset(S *subPointer, T *basePointer) {
	return ((unsigned int)subPointer) - ((unsigned int)basePointer);
}

int main(void)
{
	BC bc;
	BC *bcP = &bc;
	std::cout << "Address of BC     " << bcP << "    " << offset(bcP, bcP) << std::endl;
	
	std::cout <<  std::endl;
	std::cout << "Address of B      " << (B*)bcP << "    " << offset((B*)bcP, bcP) << std::endl;
	std::cout << "Address of C      " << (C*)bcP << "    " << offset((C*)bcP, bcP) << std::endl;
	
	std::cout <<  std::endl;
	#if USE_VIRTUAL_INHERITANCE
	std::cout << "Address of A      " << (A*)bcP << "    " << offset((A*)bcP, bcP) << std::endl;
	#endif
	std::cout << "Address of A as B " << (A*)(B*)bcP << "    " << offset((A*)(B*)bcP, bcP) << std::endl;
	std::cout << "Address of A as C " << (A*)(C*)bcP << "    " << offset((A*)(C*)bcP, bcP) << std::endl;
	
	std::cout <<  std::endl;
	#if USE_VIRTUAL_INHERITANCE
	std::cout << "Address of S      " << (S*)bcP << "    " << offset((S*)bcP, bcP) << std::endl;
	#endif
	std::cout << "Address of S as B " << (S*)(B*)bcP << "    " << offset((S*)(B*)bcP, bcP) << std::endl;
	std::cout << "Address of S as C " << (S*)(C*)bcP << "    " << offset((S*)(C*)bcP, bcP) << std::endl;
	return 0;
}

