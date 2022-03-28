build: 
	gcc lista.c f-thash.c functiiStiva-L.c functiiCoada-L.c tema2.c -o tema2 -Wall
run:
	./tema2 in_file out_file
clean:
	rm -rf tema1