vpath %.h include
vpath %.cc src
depends = main.cc A.o B.o Bind.o
A_depends = A.h A.cc
B_depends = B.h B.cc
Bind_depends = Bind.h Bind.cc A.h B.h \
	A.cc B.cc

chapter01: $(depends)
	g++ -o chapter01 $(depends)
    
A.o: $(A_depends)
	g++ -c $^
    
B.o: $(B_depends)
	g++ -c $^
    
Bind.o: $(Bind_depends)
	g++ -c $^

.PHONY : clean debug
clean:
	-rm -f A.o B.o Bind.o


debug:
	@echo $(depends)