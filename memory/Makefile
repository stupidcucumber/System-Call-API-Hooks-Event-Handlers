build:
	g++ consumer.cpp -o consumer -sectcreate __TEXT __info_plist ./Info.plist
	g++ -o producer producer.cpp
run: build
	sudo ./consumer
	./producer
clean:
	rm consumer producer