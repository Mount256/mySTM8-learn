BCD码：用4位二进制数值来表示一个0-9中的数字，
例如： 0000=0 0001=1 0010=2 0011=3
也就是说如果把一个数字作为一个BCD码，例如： 11 22
那么他应该展开为: 00010001 00100010
也就是对应为十进制: 17 34
所以一个BCD码转为十进制数据的思想是：将BCD码每个数字分离出来，例如上面的11
将十位的1分离出来然后左移4位乘上一个10 在加上 个位的数字即可。十进制转BCD码的
思想：将这个十进制数字用二进制表示，高4位表示的数字是多少 * 10再加上低四位表示

