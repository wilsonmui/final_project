parallel: Bag.hpp Pennant.hpp bagbfs.cpp
	icc -o parallel Bag.hpp Pennant.hpp bagbfs.cpp

clean:
	rm parallel *~	