CXX = g++-5
CXXFLAGS = -std=c++14 -Werror=vla
EXEC = final
OBJECTS = main.o game2.o floor2.o object.o cell.o character.o player.o enemy.o shade.o vampire.o drow.o goblin.o troll.o item.o treasure.o potion.o human.o dwarf.o halfling.o elf.o orc.o merchant.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
