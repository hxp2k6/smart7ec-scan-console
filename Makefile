objects=main.c lib/luado.c lib/pubdo.c lib/strdo.c lib/pydo.c
name_for_software = Smart7ec-scan-console

#ZHUSHI
edit:$(objects)
	cc ${objects} -L lib -o ${name_for_software} -llua -lcurl -I/usr/include/python2.6 -lpython2.6 -I lib -Wl,-rpath=lib

clean:
	-rm $(name_for_software) $(objects)