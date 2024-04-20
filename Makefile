build:
	g++ -o consumer consumer.cpp
	g++ -o producer producer.cpp
run: build
	./consumer
	./producer
clean:
	rm consumer producer