MOV x, 10
MOV y, 20
MOV w, 0.700000
MOV z, 3.140000
ADD x, y, sum1
SUB sum1, x, sum1
MUL sum1, 2, sum1
DIV sum1, 2, sum1
MUL x, y, sum2
ADD sum2, w, sum2
SUB sum2, z, sum2
DIV sum2, y, sum2
;print routine start
MOV stdout, "this line and the following lines"
MOV interrupt, 1
syscall
;print routine end
;print routine start
MOV stdout, "will be evaluated and printed to stdout"
MOV interrupt, 1
syscall
;print routine end
;print routine start
MOV stdout, "because they are not assigned to anything"
MOV interrupt, 1
syscall
;print routine end
;print routine start
MOV stdout, 3.800000
MOV interrupt, 1
syscall
;print routine end
;print routine start
MOV stdout, 100
MOV interrupt, 1
syscall
;print routine end
;print routine start
MOV stdout, 4.485714
MOV interrupt, 1
syscall
;print routine end
;print routine start
MOV stdout, 3
MOV interrupt, 1
syscall
;print routine end
;print routine start
MOV stdout, 'f'
MOV interrupt, 1
syscall
;print routine end
