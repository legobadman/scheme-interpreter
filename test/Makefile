test_Fraction_obj=\
	test_fraction.o Fraction.o

test_Number_obj=\
	test_Number.o Number.o Fraction.o

alltest:

test_fraction.o:

Fraction.o: ../Fraction.h ../Fraction.cpp
	g++ -c ../Fraction.h ../Fraction.cpp

Number.o:  ../Number.h ../Number.cpp
	g++ -c ../Number.h ../Number.cpp

testFraction:\
	$(test_Fraction_obj) 
	g++ $(test_Fraction_obj) -o testFraction
	rm $(test_Fraction_obj)

testNumber:\
	$(test_Number_obj)
	g++ $(test_Number_obj) -o testNumber
	rm $(test_Number_obj)