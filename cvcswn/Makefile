CXX = g++

cvcswn:
	g++ -c storage_manager/storage_manager.cpp
	g++ -c serializer/serializer.cpp
	g++ -c storage/storage.cpp
	g++ -c cvcswn_main.cpp
	g++ -o cvcswn storage_manager.o serializer.o storage.o cvcswn_main.o
	rm storage_manager.o
	rm serializer.o
	rm storage.o
	rm cvcswn_main.o
