cmake_minimum_required(VERSION 3.20)
project(PNDI_in_C C)

set(CMAKE_C_STANDARD 11)

add_executable(PNDI_in_C main.c phase_1.c phase_2.c tool.c Biblio.h)
