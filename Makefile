CXX = g++-5
CXXFLAGS = -std=c++14 -Werror=vla
EXEC = a4q4
OBJECTS = main.o cell.o .oamber.o .oaracter.o dragon.o drow.o dwarf.o elf.o enemy.o floor.o game.o goblin.o.oalfling.o.ouman.o item.o mer.oant.o object.o observer.o orc.o player.o potion.o .oade.o subject.o treasure.o troll.o vampire.o

DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
