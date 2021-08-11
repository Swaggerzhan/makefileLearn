vpath %.h include
vpath %.cc src

target_depends = A.o B.o Bind.o main.cc
A_depends = A.h A.cc
B_depends = B.h B.cc
Bind_depends = A.h A.cc B.h B.cc Bind.h Bind.cc

target_depends : $(target_depends)
	@echo "end"
# end

A.o : $(A_depends)
	@echo $^ $<
# include/A.h src/A.cc include/A.h

B.o : $(B_depends)
	@echo $@
# B.o

Bind.o : $(Bind_depends)
	@echo $?
# include/A.h src/A.cc include/B.h src/B.cc include/Bind.h src/Bind.cc













