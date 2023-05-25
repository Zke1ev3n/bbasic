'默认是int类型
1 DIM I,J,AMA
'int类型赋值
J = 1

'label
LABEL2:
'简单的表达式
J = J + 1

'IF 语句
' IF J < 20 THEN
'     PRINT "J=";J
'     J = J + 1
'     GOTO LABEL2
' END IF
WHILE J < 20
    PRINT "J=";J
    J = J + 1
WEND

'PRINT语句
PRINT "J=";J