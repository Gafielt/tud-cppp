#include <iostream>

/**
 *****************************************
 Aufgabe 1 Teil b)
 *****************************************
 *&intVal	Wert von intVal
 *&pIntVal	Wert von pIntVal (Adresse von intVal)
 &*pIntVal	Wert von pIntVal (Adresse von intVal)
 **&pIntVal	Wert von intVal
 *&*&intVal	Wert von intVal
 &*&pIntVal	Adresse von pIntVal (Adresse von intVal)
 *&*pIntVal	Wert von intVal
 *****************************************
 Aufgabe 1 Teil c)
 *****************************************
 *intVal		intVal ist kein Zeiger, kann also auch nicht dereferenziert werden
 **pIntVal	*pIntVal ist ein int, also kein Zeiger und kann somit auch nicht weiter dereferenziert werden
 **&*pIntVal	*pIntVal ist ein int, &*pIntVal ist ein Zeiger auf einen int, *&*pIntVal ist wieder ein int,
 also kann er nicht weiter derefernziert werden
 &*intVal	intVal ist ein int, kann also nicht dereferenziert werden.
 &42			42 ist ein Literal vom Typ int und keine Variable. Nur Variablen haben Adressen im Speicher.
 */

void swapPointer(int *i1, int *i2) {
	int tmp = *i1;
	*i1 = *i2;
	*i2 = tmp;
}

void swapReference(int& i1, int& i2) {
	int tmp = i1;
	i1 = i2;
	i2 = tmp;
}

void foo(int& i) {
	int i2 = i;
	int& i3 = i;
	std::cout << "i = " << i << std::endl;
	std::cout << "i2 = " << i2 << std::endl;
	std::cout << "i3 = " << i3 << std::endl;
	std::cout << "&i = " << &i << std::endl;
	std::cout << "&i2 = " << &i2 << std::endl;
	std::cout << "&i3 = " << &i3 << std::endl;
}

void constCorrectnessWithVariables() {
	int i = 1;
	int j = 2;

	int *iP = &i;

	const int *ciP = &i;
	ciP = &j;
//	*ciP = -1; // Error

	int const *ciP2 = &i; // Equivalent to ciP ("to-the-right" style)
	ciP2 = &j;
//	*ciP2 = -1; // Error

	int * const icP = &i;
	*icP = -2;
//	icP = ciP; // Error

	const int * const cicP = &i;
//	*cicP = -3; // Error
//	cicP = ciP; // Error

// Advanced const correctness

	int **iPP = &iP;
//	const int **ciPP = &iP; // Error

	const int * const *cicPP = &iP;
//	**cicPP = 3; // Error
//	*cicPP = &iP; // Error
	cicPP = iPP;

	int ** const iPcP = &iP;
	**iPcP = 3;
//	*iPcP = &iP; //Error
//	iPcP = iPP; //Error

}

////////////////////////////////////////////////////////////////////////////////
// exercise uebergabewerte
////////////////////////////////////////////////////////////////////////////////

int op1(int *param) {
    std::cout << "works1" << std::endl;
}

int op2(int param) {
    std::cout << "works2" << std::endl;
}

void op3(int &param) {
    std::cout << "works3" << std::endl;
}

void op4(const int **param) {
    std::cout << "works4" << std::endl;
}

void ex_uebergabewerte() {
    int i = 0;
    int *j = &i;
    int const *const k = &i;
    int **l = &j;
    const int *m = &i;
    
    op1(&i);
    op1(j);
    // op1(k); // does not work because of const -> invalid conversion from 'const int*' to 'int*'
    op1(*l);
    // op1(m); // does not work because of const

    op2(i);
    op2(*j);
    op2(*k); 
    op2(**l);
    op2(*m);

    op3(i);
    op3(*j);
    // op3(k); // cannot convert const int* to int* -> const correctness
    op3(**l);
    // op3(*m); // does not work because of const

    // op4(&&i);
    // op4(*j);
    // op4(&k); // invalid conversion from ‘const int* const*’ to ‘const int**’ -> const correctness
    // op4(l);
    op4(&m);
}

////////////////////////////////////////////////////////////////////////////////

int main() {
// Teil d)
	int i1 = 3, i2 = 5;
	std::cout << i1 << " " << i2 << std::endl;
	swapPointer(&i1, &i2);
	std::cout << i1 << " " << i2 << std::endl;
	swapReference(i1, i2);
	std::cout << i1 << " " << i2 << std::endl;
// Teil f)
	int var = 42;
	std::cout << "&var = " << &var << std::endl;
	foo(var);

    ex_uebergabewerte();
}

