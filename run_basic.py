import os
print('Input the test case you want to run!')
x = int(input())

os.system('./clean.sh')

if x == 1:
    com = 'rm BasicDataSet/my.out'
    os.system(com)
    os.system('time ./code < BasicDataSet/testcase1.txt > BasicDataSet/my.out')
    os.system('diff BasicDataSet/testcase1_ans.txt BasicDataSet/my.out')
	
if x == 2:
    com = 'rm BasicDataSet/my.out'
    os.system(com)
    os.system('time ./code < BasicDataSet/testcase2.txt > BasicDataSet/my.out')
    os.system('diff BasicDataSet/testcase2_ans.txt BasicDataSet/my.out')
	
if x == 3:
    com = 'rm BasicDataSet/my.out'
    os.system(com)
    os.system('time ./code < BasicDataSet/testcase3.txt > BasicDataSet/my.out')
    os.system('diff BasicDataSet/testcase3_ans.txt BasicDataSet/my.out')

if x == 4:
    com = 'rm BasicDataSet/my.out'
    os.system(com)
    os.system('time ./code < BasicDataSet/testcase4.txt > BasicDataSet/my.out')
    os.system('diff BasicDataSet/testcase4_ans.txt BasicDataSet/my.out')

if x == 5:
    com = 'rm BasicDataSet/my.out'
    os.system(com)
    os.system('time ./code < BasicDataSet/testcase5.txt > BasicDataSet/my.out')
    os.system('diff BasicDataSet/testcase5_ans.txt BasicDataSet/my.out')

if x == 6:
    com = 'rm BasicDataSet/my.out'
    os.system(com)
    os.system('time ./code < BasicDataSet/testcase6.txt > BasicDataSet/my.out')
    os.system('diff BasicDataSet/testcase6_ans.txt BasicDataSet/my.out')
	
if x == 7:
    com = 'rm BasicDataSet/testcase7/my.out'
    os.system(com)
    for i in range(1, 4):
        print('Running test data', i)
        com = 'time ./code < BasicDataSet/testcase7/' + str(i) + '.txt >> BasicDataSet/testcase7/my.out'
        os.system(com)
    com = 'diff BasicDataSet/testcase7/ans.txt BasicDataSet/testcase7/my.out'
    os.system(com)

if x == 8:
    com = 'rm BasicDataSet/testcase8/my.out'
    os.system(com)
    for i in range(1, 101):
        print('Running test data', i)
        com = 'time ./code < BasicDataSet/testcase8/' + str(i) + '.txt >> BasicDataSet/testcase8/my.out'
        os.system(com)
    com = 'diff BasicDataSet/testcase8/ans.txt BasicDataSet/testcase8/my.out'
    os.system(com)