parallel: Bag.cpp Pennant.cpp bagbfs.cpp
	icc -o parallel Bag.cpp Pennant.cpp bagbfs.cpp

clean:
	rm parallel *~	