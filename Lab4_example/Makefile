TARGET=main
test:$(TARGET)
	bash createFile.sh
	./$(TARGET) `cat /tmp/${USER}/esllab20140411.sp`

$(TARGET): main.c error.c path_alloc.c
	gcc $^ -o $@

clean:
	rm -f main
