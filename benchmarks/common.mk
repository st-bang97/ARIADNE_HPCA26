all:
	nvcc ${CUFILES} ${DEF} -o ${EXECUTABLE} 
clean:
	rm -f *~ *.exe
