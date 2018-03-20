parallel: parallel_bfs.cpp
	icc -o parallel parallel_bfs.cpp

clean:
	rm parallel *~	