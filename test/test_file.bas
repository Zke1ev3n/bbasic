
OPEN "demo.sav" FOR BINARY AS #1        '打开文件

PUT #1,g_Name$        '写入玩家姓名

PUT #1,g_Score        '写入玩家分数

CLOSE #1