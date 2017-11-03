# limpa plotagens previas
clear

# reseta todas as variaveis para o default
reset

# desliga a legenda
set key off

#seta o titulo para a imagem
set title "Retrato de Fase"

#seta rotulo para eixo x  e y
set xlabel "x"
set ylabel "y"

# desliga tick-marks
set xtics
set ytics

set term jpeg
set out "x-axis.jpg" 
plot "dots.txt" using 1:2 with line lt -1

set out "y-axis.jpg"
plot "dots.txt" using 1:3 with line lt -1

set out "z-axis.jpg"
plot "dots.txt" using 1:4 with line lt -1
